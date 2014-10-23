#include "stdafx.h"
#include "GLFWGraphics.h"
#include "glfw.h"

using namespace NEngine;

bool GLFWGraphics::Initialize()
{
	if (GL_TRUE != glfwInit()) return false;
	return true;
}

double GLFWGraphics::GetTime()
{
	return glfwGetTime();
}

void GLFWGraphics::SetCallbacks()
{
	glfwSetMousePosCallback([](int x, int y) { CallbackContainer::get_instance()->SetMousePos(x, y); });
	glfwSetKeyCallback([](int key, int action) { CallbackContainer::get_instance()->SetKey(key, action); });
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
