#pragma once

#include "glfw.h"
#include "CallbackContainer.h"
#include "EngineGlobals.h"

namespace NEngine
{
	struct GraphicsOpenWindowParams
	{
		int width;
		int height;
		int redbits;
		int greenbits;
		int bluebits;
		int alphabits;
		int depthbits;
		int stencilbits;
		int mode;
	};

	class IGraphics
	{
	public:
		virtual ~IGraphics() {};
		virtual bool Init() = 0;
		virtual bool OpenWindow(const GraphicsOpenWindowParams& params) = 0;
		virtual void Terminate() = 0;
		virtual void PollEvents() = 0;
		virtual void SetWindowCloseCallback() = 0;
		virtual void SetKeyCallback() = 0;
		virtual void SetMousePosCallback() = 0;
		virtual double GetTime() = 0;
	};

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
