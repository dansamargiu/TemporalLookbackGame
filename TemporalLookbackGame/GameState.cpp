#include "stdafx.h"
#include "GameState.h"
#include "glfw.h" // TODO: remove once we abstract this away
#include "Horde3DUtils.h"
#include "IResourceManager.h"
#include "CallbackContainer.h"

using namespace NEngine;

GameState::~GameState()
{
	glfwEnable(GLFW_MOUSE_CURSOR);

	// Destroy the CallbackContainer
	CallbackContainer::destroy_instance();

	// The Game state is effectively responsible for managing this object.
	// We should only call this here.
	if (m_renderer) m_renderer->Release();
}

bool GameState::Initialize(const EngineParams& params)
{
	glfwDisable(GLFW_MOUSE_CURSOR);

	// Make the Callbacks point to this object.
	CallbackContainer::destroy_instance();
	CallbackContainer::get_instance(this);

	// Initialize members
	m_shouldRun = true;

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
	static int mx0, my0;
	if (!m_shouldRun)
	{
		mx0 = x; my0 = y;
		return;
	}

	float dX = (float)(x - mx0);
	float dY = (float)(my0 - y);

	// Look left/right
	m_camera->TSR()->r.y -= dX / 100 * 30;

	// Loop up/down but only in a limited range
	m_camera->TSR()->r.x += dY / 100 * 30;
	if (m_camera->TSR()->r.x > 90) m_camera->TSR()->r.x = 90;
	if (m_camera->TSR()->r.x < -90) m_camera->TSR()->r.x = -90;

	mx0 = x; my0 = y;
}
