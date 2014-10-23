#include "stdafx.h"
#include "GameState.h"
#include "glfw.h" // TODO: remove once we abstract this away
#include "Horde3DUtils.h"

using namespace NEngine;

bool GameState::Initialize(const EngineParams& params)
{
	// Initialize members
	m_shouldRun = true;

	// Get the renderer object
	m_renderer = m_factory.Resolve<IRenderer>();
	if (!m_renderer) return false;

	// Initialize Camera node
	m_camera = m_factory.Resolve<ICameraNode>();
	if (!m_camera || !m_camera->Initialize()) return false;
	m_camera->Resize(params.winWidth, params.winHeight);

	// Initialize demo app. TODO: Remove this once everything is flushed out.
	m_knightDemo = std::make_shared<KnightDemoApp>(params.appPath);
	if (!m_knightDemo->init()) return false;
	return true;
}

bool GameState::ShouldRun() const
{
	return m_shouldRun;
}

void GameState::StateLoop(float fps)
{
	// Update key states
	for (int i = 0; i < 320; ++i)
		m_knightDemo->setKeyState(i, glfwGetKey(i) == GLFW_PRESS);
	m_knightDemo->keyStateHandler();

	// Camera Render
	m_camera->Render();

	// Render
	m_knightDemo->mainLoop(fps);

	// Finish rendering of frame
	m_renderer->FinalizeFrame();
}

int GameState::WindowCloseCallback()
{
	m_shouldRun = false;
	return 0;
}

void GameState::SetKeyCallback(int key, int action)
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

void GameState::SetMousePosCallback(int x, int y)
{
	(void)x;
	(void)y;
}
