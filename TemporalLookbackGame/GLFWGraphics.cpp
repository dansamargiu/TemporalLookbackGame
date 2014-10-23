#include "stdafx.h"
#include "GLFWGraphics.h"
#include "glfw.h"

using namespace NEngine;

bool GLFWGraphics::Initialize()
{
	return GL_TRUE == glfwInit();
}

double GLFWGraphics::GetTime()
{
	return glfwGetTime();
}

void GLFWGraphics::SetMousePosCallback()
{
	glfwSetMousePosCallback([](int x, int y) { CallbackContainer::get_instance()->SetMousePos(x, y); });
}

void GLFWGraphics::SetKeyCallback()
{
	glfwSetKeyCallback([](int key, int action) { CallbackContainer::get_instance()->SetKey(key, action); });
}

void GLFWGraphics::SetWindowCloseCallback()
{
	glfwSetWindowCloseCallback([]() { return CallbackContainer::get_instance()->WindowClose(); });
}

void GLFWGraphics::PollEvents()
{
	glfwSwapBuffers();
}

bool GLFWGraphics::OpenWindow(const GraphicsOpenWindowParams& params)
{
	return GL_TRUE == glfwOpenWindow(
		params.width,
		params.height,
		params.redbits,
		params.greenbits,
		params.bluebits,
		params.alphabits,
		params.depthbits,
		params.stencilbits,
		params.mode);
}

void GLFWGraphics::Terminate()
{
	glfwTerminate();
}
