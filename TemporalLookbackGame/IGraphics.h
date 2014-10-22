#pragma once

#include "glfw.h"

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
		virtual bool OpenWindow(GraphicsOpenWindowParams params) = 0;
		virtual void Terminate() = 0;

	private:

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

		virtual bool OpenWindow(GraphicsOpenWindowParams params) override
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
	};
}
