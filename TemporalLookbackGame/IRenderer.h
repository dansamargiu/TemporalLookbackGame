#pragma once
#include "TSRStructs.h"

namespace NEngine
{
	class IRenderer
	{
	public:
		virtual ~IRenderer() {}
		virtual bool Initialize() = 0;
		virtual void Release() = 0;
		virtual int GetRootNode() = 0;
		virtual int AddCameraNode(int parent, const char *name, int pipelineRes) = 0;
		virtual void SetNodeParamI(int node, int param, int value) = 0;
		virtual void SetupCameraView(int cameraNode, float fov, float aspect, float nearDist, float farDist) = 0;
		virtual void ResizePipelineBuffers(int pipeRes, int width, int height) = 0;
		virtual void Render(int cameraNode) = 0;
		virtual void SetTransform(int node, const ObjectTSR& transform) = 0;
		virtual void FinalizeFrame() = 0;
	};
}
