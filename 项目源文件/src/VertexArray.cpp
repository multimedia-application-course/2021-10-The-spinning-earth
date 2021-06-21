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
        GLCall(glVertexAttribPointer(i/*����location=i�Ķ�������*/, element.count/*2��*/, element.type/*float��*/, 
            element.normalized/*����׼��*/,
            layout.GetStride()/*2*sizeof(float)+2*sizeof(float)=16������һ�����ݵĵ�ַ��ڶ������ݵĵ�ַ���16�ֽ�*/,
            (const void*)offset)/*��ʼλ�ô�offset��ʼ*/);
        /*
            "layout(location = 0) in vec4 position;" ÿ��position�����Ԫ�ظ���Ϊ2����Ԫ������Ϊfloat�ͣ�����׼����
                ��������һ������������"float positions[]"�еĵ�ַ���16�ֽڣ�����ռ2*sizeof(float)�ֽ�+"texCoord"ռ2*sizeof(float)�ֽڣ���16�ֽڣ�
                ��һ��������"float positions[]"�еĵ�ַΪ0
            "layout(location = 1) in vec2 texCoord;" ÿ��position�����Ԫ�ظ���Ϊ2����Ԫ������Ϊfloat�ͣ�����׼����
                ��������һ������������"float positions[]"�еĵ�ַ���16�ֽڣ�����ռ2*sizeof(float)�ֽ�+"position"ռ2*sizeof(float)�ֽڣ���16�ֽڣ�
                ��һ��������"float positions[]"�еĵ�ַΪ8��"position"ռ2*sizeof(float)�ֽڣ�
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