#include "stdafx.h"
#include "GameState.h"
#include "glfw.h" // TODO: remove once we abstract this away
#include "Horde3DUtils.h"
#include "IResourceManager.h"
#include "CallbackContainer.h"

using namespace NEngine;

GameState::~GameState()
{
	// Destroy the CallbackContainer
	CallbackContainer::destroy_instance();

	// The Game state is effectively responsible for managing this object.
	// We should only call this here.
	if (m_renderer) m_renderer->Release();
}

bool GameState::Initialize(const EngineParams& params)
{
	// Initialize members
	m_shouldRun = true;

	// Point the CallbackContainer at the right engine state obj.
	CallbackContainer::get_instance(this);

	// Get the renderer object and initialize it. 
	// This should be the only place we initialize this object.
	m_renderer = m_factory.Resolve<IRenderer>();
	if (!m_renderer || !m_renderer->Initialize()) return false;

	// Initialize Camera node
	m_camera = m_factory.Resolve<ICameraNode>();
	if (!m_camera || !m_camera->Initialize()) return false;
	m_camera->Resize(params.winWidth, params.winHeight);

	// Initialize demo app. TODO: Remove this once everything is flushed out.
	m_knightDemo = std::make_shared<KnightDemoApp>(m_factory);
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

	// Render Demo
	m_knightDemo->mainLoop(fps);

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
