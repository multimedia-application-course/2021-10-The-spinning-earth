
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

static char msg[128] = { 0 };
GLfloat xpos = 0, ypos = 0;
float width, height;

bool isPress = false;
bool mouseLeftDown;
bool mouseRightDown;
float mouseX = 0.0f, mouseY = 0.0f;
float cameraDistance;
float cameraAngleX;
float cameraAngleY;
float dx = 0.0f;
float dy = 0.0f;
bool isFirst = true;//点击鼠标键后第一次

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action != GLFW_PRESS)
		return;
	switch (key)
	{
	case GLFW_KEY_ESCAPE:
		glfwSetWindowShouldClose(window, GL_TRUE);
		break;
	default:
		break;
	}
}
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (action == GLFW_PRESS) 
	{
		isPress = true;
		switch (button)
		{
		case GLFW_MOUSE_BUTTON_LEFT:
			mouseLeftDown = true;
			strcpy(msg, "Mosue left button clicked!");
			std::cout << msg << std::endl;
			break;
		case GLFW_MOUSE_BUTTON_MIDDLE:
			strcpy(msg, "Mosue middle button clicked!");
			std::cout << msg << std::endl;
			break;
		case GLFW_MOUSE_BUTTON_RIGHT:
			mouseRightDown = true;
			strcpy(msg, "Mosue right button clicked!");
			std::cout << msg << std::endl;
			break;
		default:
			return;
		}
	}
	else
	{
		isPress = false;
		mouseLeftDown = false;
		mouseRightDown = false;
	}
	return;
}
void cursor_position_callback(GLFWwindow* window, double x, double y)
{
	if (isPress)
	{
		//std::cout <<"鼠标坐标："<< mouseX << "  " << mouseY << std::endl;
	}
	if (mouseLeftDown)
	{
		cameraAngleY += (x - mouseX) ;
		cameraAngleX += (y - mouseY) ;
		//cameraAngleX -= dx;
		//cameraAngleY -= dy;
		if (isFirst)
		{
			dx = x;
			dy = y;
			//std::cout << "鼠标坐标：" << dx << "  " << dy << std::endl;
			isFirst = false;
			//std::cout << "鼠标坐标：" << mouseX << "  " << mouseY << std::endl;
		}
		mouseX = x - dx;
		mouseY = y - dy;
		//std::cout << "鼠标坐标：" << mouseX << "  " << mouseY << std::endl;
	}
	if (!mouseLeftDown)
	{
		isFirst = true;
	}
	if (mouseRightDown)
	{
		cameraDistance += (y - mouseY) * 0.2f;
		mouseY = y;
	}
	//sprintf(msg, "Mouse position move to [%d:%d]", int(x), int(y));
	//xpos = float(x/width);
	//ypos = float(1-y/height);
	return;
}
void scroll_callback(GLFWwindow* window, double x, double y)
{
	return;
}