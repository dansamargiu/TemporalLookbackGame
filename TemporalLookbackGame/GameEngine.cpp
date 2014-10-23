#include "stdafx.h"
#include "GameEngine.h"

using namespace NEngine;

GameEngine::GameEngine(const NUtility::FancyFactory& factory)
: m_Factory(factory), m_graphics(nullptr), m_currentEngineState(nullptr)
{
}

GameEngine::~GameEngine()
{
	if (m_graphics)
	{
		m_graphics->Terminate();
	}

	CallbackContainer::destroy_instance();
}

bool GameEngine::Initialize(const EngineParams& params)
{
	// Copy the params
	m_params = params;

	m_graphics = m_Factory.Resolve<IGraphics>();
	if (!m_graphics)
	{
		return false;
	}

	// Initialize Graphics
	if (!m_graphics->Init())
	{
		return false;
	}

	// Open the main window
	if (!m_graphics->OpenWindow({ params.winWidth, params.winHeight, 8, 8, 8, 8, 24, 8, params.fullscreen ? GLFW_FULLSCREEN : GLFW_WINDOW }))
	{
		return false;
	}

	return true;
}

bool GameEngine::SetState(const std::string& strState)
{
	// Clear the previous engine state object ptr and resolve the new one.
	m_currentEngineState.reset();
	m_currentEngineState = m_Factory.Resolve<IEngineState>(strState);
	if (!m_currentEngineState)
	{
		return false;
	}

	// Initialize State
	if (!m_currentEngineState->Initialize(m_params))
	{
		return false;
	}

	// Point the CallbackContainer at the right engine state obj.
	CallbackContainer::destroy_instance();
	CallbackContainer::get_instance(m_currentEngineState);

	// Register the graphics callbacks.
	m_graphics->SetWindowCloseCallback();
	m_graphics->SetKeyCallback();
	m_graphics->SetMousePosCallback();
	return true;
}

void GameEngine::Launch()
{
	int frames = 0;
	float fps = 30.0f;
	static double t0 = m_graphics->GetTime();
	while (m_currentEngineState->ShouldRun())
	{
		// Calculate FPS
		++frames;
		if (frames >= 3)
		{
			double t = m_graphics->GetTime();
			fps = frames / (float)(t - t0);
			if (fps < 5) fps = 30;  // Handle breakpoints
			frames = 0;
			t0 = t;
		}

		m_currentEngineState->Draw(fps);
		m_graphics->PollEvents();
	}
}
