#pragma once
#include "IGraphics.h"
#include "CallbackContainer.h"

namespace NEngine
{
	class GLFWGraphics : public IGraphics
	{
	public:
		virtual bool Init() override;
		virtual void Terminate() override;
		virtual bool OpenWindow(const GraphicsOpenWindowParams& params) override;
		virtual void PollEvents() override;
		virtual void SetWindowCloseCallback() override;
		virtual void SetKeyCallback() override;
		virtual void SetMousePosCallback() override;
		virtual double GetTime() override;
	};
}