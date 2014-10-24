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
		virtual void ResizeViewport(int width, int height) override;
		virtual void GetMatrix(const float ** relMatrix, const float ** absMatrix) override;
		virtual void SetMatrix(const float *matrix) override;
		virtual void Render() override;
	private:
		std::shared_ptr<IRenderer> m_renderer;
		int m_pipelineHandle;
		int m_camHandle;
		DISALLOW_COPY_AND_ASSIGN(BasicCameraNode);
	};
}