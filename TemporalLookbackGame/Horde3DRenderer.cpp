#include "stdafx.h"
#include "Horde3DRenderer.h"
#include "Horde3D.h"
#include "Horde3DUtils.h"

using namespace NEngine;

bool Horde3DRenderer::Initialize()
{
	return h3dInit();
}

void Horde3DRenderer::Release()
{
	h3dRelease();
}

int Horde3DRenderer::GetRootNode()
{
	return H3DRootNode;
}

int Horde3DRenderer::AddCameraNode(int parent, const char *name, int pipelineRes)
{
	return h3dAddCameraNode(parent, name, pipelineRes);
}

void Horde3DRenderer::SetNodeParamI(int node, int param, int value)
{
	h3dSetNodeParamI(node, param, value);
}

void Horde3DRenderer::SetupCameraView(int cameraNode, float fov, float aspect, float nearDist, float farDist)
{
	h3dSetupCameraView(cameraNode, fov, aspect, nearDist, farDist);
}

void Horde3DRenderer::ResizePipelineBuffers(int pipeRes, int width, int height)
{
	h3dResizePipelineBuffers(pipeRes, width, height);
}

void Horde3DRenderer::Render(int cameraNode)
{
	h3dRender(cameraNode);
}

void Horde3DRenderer::SetTransform(int node, const ObjectTSR& transform)
{
	h3dSetNodeTransform( 
		node,
		transform.t.x, transform.t.y, transform.t.z,
		transform.r.x, transform.r.y, transform.r.z,
		transform.s.x, transform.s.y, transform.s.z);
}

void NEngine::Horde3DRenderer::FinalizeFrame()
{
	// Finish rendering of frame
	h3dFinalizeFrame();

	// Remove all overlays
	h3dClearOverlays();

	// Write all messages to log file
	h3dutDumpMessages();
}

void NEngine::Horde3DRenderer::GetTransformMatrix(int node, const float** relMatrix, const float** absMatrix)
{
	h3dGetNodeTransMats(node, relMatrix, absMatrix);
}


void Horde3DRenderer::SetTransformMatrix(int node, const float* transformMatrix)
{
	h3dSetNodeTransMat(node, transformMatrix);
}
