#pragma once
#include "IRenderer.h"

namespace NEngine
{
	class Horde3DRenderer : public IRenderer
	{
	public:
		virtual bool Initialize() override;
		virtual void Release() override;
		virtual int GetRootNode() override;
		virtual int AddCameraNode(int parent, const char *name, int pipelineRes) override;
		virtual void SetNodeParamI(int node, int param, int value) override;
		virtual void SetupCameraView(int cameraNode, float fov, float aspect, float nearDist, float farDist) override;
		virtual void ResizePipelineBuffers(int pipeRes, int width, int height) override;
		virtual void Render(int cameraNode) override;
		virtual void SetTransform(int node, const ObjectTSR& transform) override;
		virtual void GetTransformMatrix(int node, const float** relMatrix, const float** absMatrix) override;
		virtual void SetTransformMatrix(int node, const float* transformMatrix) override;
		virtual void FinalizeFrame() override;
	};
}