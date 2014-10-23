#pragma once
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
		virtual bool Initialize() = 0;
		virtual bool OpenWindow(const GraphicsOpenWindowParams& params) = 0;
		virtual void Terminate() = 0;
		virtual void PollEvents() = 0;
		virtual void SetWindowCloseCallback() = 0;
		virtual void SetKeyCallback() = 0;
		virtual void SetMousePosCallback() = 0;
		virtual double GetTime() = 0;
	};
}
