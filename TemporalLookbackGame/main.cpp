#include "stdafx.h"
#include "GameEngine.h"
#include "FactoryRegistry.h"
#include <iostream>

static std::string ExtractAppPath(char *fullPath)
{
	const std::string s(fullPath);
	if (s.find("/") != std::string::npos)
	{
		return s.substr(0, s.rfind("/")) + "/";
	}
	else if (s.find("\\") != std::string::npos)
	{
		return s.substr(0, s.rfind("\\")) + "\\";
	}

	return "";
}

using namespace NEngine;

int main(int, char** argv)
{
	// Initialize Factory Pattern
	NUtility::FancyFactory factory;
	FactoryRegistry::SetupEngineFactories(factory);

	// Initialize Engine
	GameEngine engine(factory);
	const int kAppWidth = 1024;
	const int kAppHeight = 576;
	const bool kFullscreen = false;
	if (!engine.Initialize({ ExtractAppPath(argv[0]), kAppWidth, kAppHeight, kFullscreen }))
	{
		return -1;
	}

	// Set first engine state to main menu.
	if (!engine.SetState(GAME_STATE))
	{
		return -1;
	}

	// Launch the engine.
	engine.Launch();

	return 0;
}
