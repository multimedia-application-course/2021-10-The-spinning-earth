#include"VertexArray.h"

#include"VertexBufferLayout.h"
#include"Renderer.h"

VertexArray::VertexArray()
{
    GLCall(glGenVertexArrays(1, &m_RendererID));
}

VertexArray::~VertexArray()
{
    GLCall(glDeleteVertexArrays(1, &m_RendererID));
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
    Bind();
	vb.Bind();
    const auto& elements = layout.GetElements();
    unsigned int offset = 0;
    for (unsigned int i = 0; i < elements.size(); i++)
    {
        const auto& element = elements[i];
        GLCall(glEnableVertexAttribArray(i));
        GLCall(glVertexAttribPointer(i/*设置location=i的顶点属性*/, element.count/*2个*/, element.type/*float型*/, 
            element.normalized/*不标准化*/,
            layout.GetStride()/*2*sizeof(float)+2*sizeof(float)=16——第一组数据的地址与第二组数据的地址相差16字节*/,
            (const void*)offset)/*起始位置从offset开始*/);
        /*
            "layout(location = 0) in vec4 position;" 每个position顶点的元素个数为2个，元素类型为float型，不标准化，
                顶点与下一个顶点在数组"float positions[]"中的地址相差16字节（自身占2*sizeof(float)字节+"texCoord"占2*sizeof(float)字节，共16字节）
                第一个顶点在"float positions[]"中的地址为0
            "layout(location = 1) in vec2 texCoord;" 每个position顶点的元素个数为2个，元素类型为float型，不标准化，
                顶点与下一个顶点在数组"float positions[]"中的地址相差16字节（自身占2*sizeof(float)字节+"position"占2*sizeof(float)字节，共16字节）
                第一个顶点在"float positions[]"中的地址为8（"position"占2*sizeof(float)字节）
        */
        offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
    }
}

void VertexArray::Bind() const
{
    GLCall(glBindVertexArray(m_RendererID));
}

void VertexArray::Unbind() const
{
    GLCall(glBindVertexArray(0));
}