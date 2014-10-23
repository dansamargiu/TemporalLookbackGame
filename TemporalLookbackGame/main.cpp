#include "stdafx.h"
#include "GameEngine.h"
#include "FactoryRegistry.h"
#include <iostream>
#include "Horde3DResourceManager.h"

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
	auto appPath = ExtractAppPath(argv[0]);

	// Initialize Factory Pattern
	NUtility::FancyFactory factory;
	FactoryRegistry::SetupEngineFactories(factory);
	factory.RegisterInstance<IResourceManager>(std::make_shared<Horde3DResourceManager>(appPath + "..\\..\\..\\Content"));

	// Initialize Engine
	GameEngine engine(factory);
	const int kAppWidth = 1024;
	const int kAppHeight = 576;
	const bool kFullscreen = false;
	if (!engine.Initialize({ appPath, kAppWidth, kAppHeight, kFullscreen }))
	{
		return -1;
	}

	// Set first engine state to main menu.
	if (!engine.SetState(GAME_STATE))
	{
		return -1;
	}

	if (!engine.SetState(GAME_STATE))
	{
		return -1;
	}

	// Launch the engine.
	engine.GameLoop();

	return 0;
}
