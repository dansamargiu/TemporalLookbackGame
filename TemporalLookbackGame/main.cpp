#include "stdafx.h"
#include "TemporalEngine.h"
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
	TemporalEngine engine(factory);
	if (!engine.Initialize({ ExtractAppPath(argv[0]) }))
	{
		return -1;
	}

	// Set first engine state to main menu.
	if (!engine.SetState(MAIN_MENU))
	{
		return -1;
	}

	// Launch the engine.
	engine.Launch();

	return 0;
}
