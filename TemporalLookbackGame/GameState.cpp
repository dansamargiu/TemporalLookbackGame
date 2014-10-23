#include "stdafx.h"
#include "GameState.h"
#include "glfw.h" // TODO: remove once we abstract this away

using namespace NEngine;

GameState::GameState(const NUtility::FancyFactory& factory)
:
m_factory(factory),
m_shouldRun(true),
m_knightDemo(nullptr),
m_renderer(nullptr),
m_camera(nullptr)
{
}

GameState::~GameState()
{
	m_knightDemo->release();
}

bool NEngine::GameState::Initialize(const EngineParams& params)
{
	// Initialize Renderer
	m_renderer = m_factory.Resolve<IRenderer>();
	if (!m_renderer || !m_renderer->Initialize())
	{
		return false;
	}

	// Initialize Camera
	m_camera = m_factory.Resolve<ICameraNode>();
	if (!m_camera || !m_camera->Initialize())
	{
		return false;
	}

	// Initialize demo app. TODO: Remove this once everything is flushed out.
	m_knightDemo = std::make_shared<KnightDemoApp>(params.appPath);
	if (!m_knightDemo->init())
	{
		return false;
	}

	m_knightDemo->resize(params.winWidth, params.winHeight);
	return true;
}

bool GameState::ShouldRun() const
{
	return m_shouldRun;
}

void GameState::Draw(float fps)
{
	// Update key states
	for (int i = 0; i < 320; ++i)
		m_knightDemo->setKeyState(i, glfwGetKey(i) == GLFW_PRESS);
	m_knightDemo->keyStateHandler();

	// Render
	m_knightDemo->mainLoop(fps);
}

int NEngine::GameState::WindowCloseCallback()
{
	m_shouldRun = false;
	return 0;
}

void NEngine::GameState::SetKeyCallback(int key, int action)
{
	if (!m_shouldRun) return;

	if (action == GLFW_PRESS)
	{
		switch (key)
		{
		case GLFW_KEY_ESC:
			m_shouldRun = false;
			break;
		}
	}
}

void NEngine::GameState::SetMousePosCallback(int x, int y)
{
	(void)x;
	(void)y;
}
