#include "stdafx.h"
#include "TemporalEngine.h"
#include "TemporalLookbackFactories.h"

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
	TemporalLookbackFactories::SetupEngineFactories(factory);

	// Initialize Engine
	TemporalEngine engine(factory);
	EngineParams params = { ExtractAppPath(argv[0]) };
	if (!engine.Initialize(params))
	{
		return -1;
	}

	// Set first engine state to main menu.
	if (!engine.SetState("MAIN_MENU"))
	{
		return -1;
	}

	// Launch the engine.
	if (!engine.Launch())
	{
		return -1;
	}

	return 0;
}
