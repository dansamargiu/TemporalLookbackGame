#include "stdafx.h"
#include "TemporalEngine.h"
#include "IGraphics.h"
#include "IEngineState.h"
#include "EngineGlobals.h"

using namespace NEngine;

TemporalEngine::TemporalEngine(const NUtility::FancyFactory& factory)
: m_Factory(factory), m_graphics(nullptr), m_currentEngineState(nullptr)
{
}

TemporalEngine::~TemporalEngine()
{
	if (m_graphics)
	{
		m_graphics->Terminate();
	}

	CallbackContainer::destroy_instance();
}

bool TemporalEngine::Initialize(const EngineParams&)
{
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
	const int kAppWidth = 1024;
	const int kAppHeight = 576;
	const bool kFullscreen = false;
	if (!m_graphics->OpenWindow({ kAppWidth, kAppHeight, 8, 8, 8, 8, 24, 8, kFullscreen ? GLFW_FULLSCREEN : GLFW_WINDOW }))
	{
		return false;
	}

	return true;
}

bool TemporalEngine::SetState(const std::string& strState)
{
	// Clear the previous engine state object ptr and resolve the new one.
	m_currentEngineState.reset();
	m_currentEngineState = m_Factory.Resolve<IEngineState>(strState);
	if (!m_currentEngineState)
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

void TemporalEngine::Launch()
{
	while (m_currentEngineState->ShouldRun())
	{
		m_currentEngineState->Draw();
		m_graphics->PollEvents();
	}
}
