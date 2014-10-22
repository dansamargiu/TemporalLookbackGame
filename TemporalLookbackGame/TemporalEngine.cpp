#include "stdafx.h"
#include "TemporalEngine.h"
#include "IGraphics.h"

using namespace NEngine;

bool TemporalEngine::Initialize(const EngineParams&)
{
	auto pGraphics = mFactory.Resolve<IGraphics>();
	if (!pGraphics)
	{
		return false;
	}

	// Initialize Graphics
	if (!pGraphics->Init())
	{
		return false;
	}

	// Open the main window
	const int kAppWidth = 1024;
	const int kAppHeight = 576;
	const bool kFullscreen = false;
	if (!pGraphics->OpenWindow({ kAppWidth, kAppHeight, 8, 8, 8, 8, 24, 8, kFullscreen ? GLFW_FULLSCREEN : GLFW_WINDOW }))
	{
		return false;
	}

	return true;
}

bool TemporalEngine::SetState(const std::string&)
{
	return true;
}

bool TemporalEngine::Launch()
{

	// End of application
	return true;
}

TemporalEngine::TemporalEngine(const NUtility::FancyFactory& factory)
	: mFactory(factory)
{
}

TemporalEngine::~TemporalEngine()
{
	auto pGraphics = mFactory.Resolve<IGraphics>();
	if (!pGraphics)
	{
		return;
	}

	pGraphics->Terminate();
}
