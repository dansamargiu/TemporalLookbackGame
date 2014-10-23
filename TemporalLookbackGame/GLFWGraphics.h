#pragma once
#include "IGraphics.h"
#include "glfw.h"
#include "CallbackContainer.h"

namespace NEngine
{
	class GLFWGraphics : public IGraphics
	{
	public:
		virtual bool Init() override
		{
			return GL_TRUE == glfwInit();
		}

		virtual void Terminate() override
		{
			glfwTerminate();
		}

		virtual bool OpenWindow(const GraphicsOpenWindowParams& params) override
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

		virtual void PollEvents() override
		{
			glfwSwapBuffers();
		}

		virtual void SetWindowCloseCallback() override
		{
			glfwSetWindowCloseCallback([]() { return CallbackContainer::get_instance()->WindowClose(); });
		}

		virtual void SetKeyCallback() override
		{
			glfwSetKeyCallback([](int key, int action) { CallbackContainer::get_instance()->SetKey(key, action); });
		}

		virtual void SetMousePosCallback() override
		{
			glfwSetMousePosCallback([](int x, int y) { CallbackContainer::get_instance()->SetMousePos(x, y);  });
		}

		virtual double GetTime() override
		{
			return glfwGetTime();
		}
	};
}