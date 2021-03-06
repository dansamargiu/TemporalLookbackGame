#pragma once
#include "IGraphics.h"
#include "CallbackContainer.h"

namespace NEngine
{
	class GLFWGraphics : public IGraphics
	{
	public:
		virtual bool Initialize() override;
		virtual void Terminate() override;
		virtual bool OpenWindow(const GraphicsOpenWindowParams& params) override;
		virtual void PollEvents() override;
		virtual void SetCallbacks() override;
		virtual double GetTime() override;
	};
}