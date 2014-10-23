#pragma once
#include "ICameraNode.h"
#include "IRenderer.h"
#include "TSRStructs.h"

namespace NEngine
{
	class BasicCameraNode : public ICameraNode
	{
	public:
		FACTORY_HOLDER(BasicCameraNode);		
		virtual bool Initialize() override;
		virtual void Resize(int width, int height) override;
		virtual void Render() override;

		virtual ObjectTSR* TSR() override;
	private:
		std::shared_ptr<IRenderer> m_renderer;
		ObjectTSR m_camTSR;
		int m_pipelineHandle;
		int m_camHandle;
		DISALLOW_COPY_AND_ASSIGN(BasicCameraNode);
	};
}