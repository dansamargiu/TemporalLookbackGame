#include "stdafx.h"
#include "GameEngine.h"
#include "CallbackContainer.h"
#include "glfw.h"

using namespace NEngine;

GameEngine::~GameEngine()
{
	if (m_graphics) m_graphics->Terminate();
}

bool GameEngine::Initialize(const EngineParams& params)
{
	// Copy the params
	m_params = params;

	// Initialize graphics
	m_graphics = m_factory.Resolve<IGraphics>();
	if (!m_graphics || !m_graphics->Initialize()) return false;

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
	m_currentEngineState = m_factory.Resolve<IEngineState>(strState);
	if (!m_currentEngineState)
	{
		return false;
	}

	// Initialize State
	if (!m_currentEngineState->Initialize(m_params))
	{
		return false;
	}

	// Register the graphics callbacks.
	m_graphics->SetCallbacks();
	return true;
}

void GameEngine::GameLoop()
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

		m_currentEngineState->StateLoop(fps);
		m_graphics->PollEvents();
	}
}
