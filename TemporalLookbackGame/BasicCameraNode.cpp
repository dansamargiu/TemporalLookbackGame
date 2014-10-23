#include "stdafx.h"
#include "BasicCameraNode.h"
#include "IRenderer.h"
#include "IResourceManager.h"
#include "Horde3D.h" // Need it for the enums.

using namespace NEngine;

bool BasicCameraNode::Initialize()
{
	auto m_resourceManager = m_factory.Resolve<IResourceManager>();
	if (!m_resourceManager || !m_resourceManager->Initialize()) return false;

	m_renderer = m_factory.Resolve<IRenderer>();
	if (!m_renderer) return false;

	m_pipelineHandle = m_resourceManager->AddResource(H3DResTypes::Pipeline, "pipelines/hdr.pipeline.xml", 0);
	if (!m_resourceManager->LoadResources()) return false;
	m_camHandle = m_renderer->AddCameraNode(m_renderer->GetRootNode(), "Camera", m_pipelineHandle);

	// Initial TSR
	m_camTSR = { 
		{ 5, 3, 19 },
		{ 7, 15, 0 },
		{ 1, 1, 1 }
	};

	return true;
}

void BasicCameraNode::Resize(int width, int height)
{
	// Resize viewport
	m_renderer->SetNodeParamI(m_camHandle, H3DCamera::ViewportXI, 0);
	m_renderer->SetNodeParamI(m_camHandle, H3DCamera::ViewportYI, 0);
	m_renderer->SetNodeParamI(m_camHandle, H3DCamera::ViewportWidthI, width);
	m_renderer->SetNodeParamI(m_camHandle, H3DCamera::ViewportHeightI, height);

	// Set virtual camera parameters
	m_renderer->SetupCameraView(m_camHandle, 45.0f, (float)width / height, 0.1f, 1000.0f);
	m_renderer->ResizePipelineBuffers(m_pipelineHandle, width, height);
}

void BasicCameraNode::Render()
{
	m_renderer->SetTransform(m_camHandle, m_camTSR);
	m_renderer->Render(m_camHandle);
}

ObjectTSR* NEngine::BasicCameraNode::TSR()
{
	return &m_camTSR;
}
