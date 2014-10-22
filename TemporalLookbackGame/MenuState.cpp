#include "stdafx.h"
#include "MenuState.h"

using namespace NEngine;

MenuState::MenuState(const NUtility::FancyFactory& factory)
: m_factory(factory), m_shouldRun(true), m_model(0), m_cam(0), m_time(0)
{

}

MenuState::~MenuState()
{
	// Release engine
	h3dRelease();
}

bool NEngine::MenuState::Initialize(const EngineParams& params)
{
	// Initialize engine
	if (!h3dInit())
	{
		h3dutDumpMessages();
		return false;
	}

	// Add pipeline resource
	H3DRes pipeRes = h3dAddResource(H3DResTypes::Pipeline, "pipelines/hdr.pipeline.xml", 0);
	// Add model resource
	H3DRes modelRes = h3dAddResource(H3DResTypes::SceneGraph, "models/man/man.scene.xml", 0);
	// Add animation resource
	H3DRes animRes = h3dAddResource(H3DResTypes::Animation, "animations/man.anim", 0);
	// Load added resources
	std::string content(params.appPath + "..\\..\\..\\Content");
	if (!h3dutLoadResourcesFromDisk(content.c_str()))
	{
		return false;
	}

	// Add model to scene
	m_model = h3dAddNodes(H3DRootNode, modelRes);
	// Apply animation
	h3dSetupModelAnimStage(m_model, 0, animRes, 0, "", false);

	// Add light source
	H3DNode light = h3dAddLightNode(H3DRootNode, "Light1", 0, "LIGHTING", "SHADOWMAP");
	// Set light position and radius
	h3dSetNodeTransform(light, 0, 20, 0, 0, 0, 0, 1, 1, 1);
	h3dSetNodeParamF(light, H3DLight::RadiusF, 0, 50.0f);

	// Add camera
	m_cam = h3dAddCameraNode(H3DRootNode, "Camera", pipeRes);

	// Setup viewport and render target sizes
	h3dSetNodeParamI(m_cam, H3DCamera::ViewportXI, 0);
	h3dSetNodeParamI(m_cam, H3DCamera::ViewportYI, 0);
	h3dSetNodeParamI(m_cam, H3DCamera::ViewportWidthI, params.winWidth);
	h3dSetNodeParamI(m_cam, H3DCamera::ViewportHeightI, params.winHeight);
	h3dSetupCameraView(m_cam, 45.0f, (float)params.winWidth / params.winHeight, 0.5f, 2048.0f);
	h3dResizePipelineBuffers(pipeRes, params.winWidth, params.winHeight);
	
	return true;
}

bool MenuState::ShouldRun() const
{
	return m_shouldRun;
}

void MenuState::Draw(float fps)
{
	// Increase animation time
	m_time = m_time + 10.0f * (1 / fps);
	
	// Render scene
	h3dRender(m_cam);

	// Finish rendering of frame
	h3dFinalizeFrame();

	// Write all messages to log file
	h3dutDumpMessages();
}

int NEngine::MenuState::WindowCloseCallback()
{
	m_shouldRun = false;
	return 0;
}

void NEngine::MenuState::SetKeyCallback(int key, int action)
{
	(void)key;
	(void)action;
}

void NEngine::MenuState::SetMousePosCallback(int x, int y)
{
	(void)x;
	(void)y;
}
