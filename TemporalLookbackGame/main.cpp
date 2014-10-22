// *************************************************************************************************
//
// Horde3D
//   Next-Generation Graphics Engine
//
// Sample Application
// --------------------------------------
// Copyright (C) 2006-2011 Nicolas Schulz
//
//
// This sample source file is not covered by the EPL as the rest of the SDK
// and may be used without any restrictions. However, the EPL's disclaimer of
// warranty and liability shall be in effect for this file.
//
// *************************************************************************************************

#include "stdafx.h"

#define _CRT_SECURE_NO_WARNINGS

#include "TemporalEngine.h"
#include "FancyFactory.h"
#include "TemporalLookbackFactories.h"

static std::string ExtractAppPath(char *fullPath)
{
	const std::string s(fullPath);
	if (s.find("/") != std::string::npos)
		return s.substr(0, s.rfind("/")) + "/";
	else if (s.find("\\") != std::string::npos)
		return s.substr(0, s.rfind("\\")) + "\\";
	else
		return "";
}

int main(int argc, char** argv)
{
	// Initialize Factory Pattern
	NUtility::FancyFactory factory;
	TemporalLookbackFactories::SetupEngineFactories(factory);

	// Initialize Engine
	NEngine::TemporalEngine engine(factory);

	NEngine::EngineParams params = { ExtractAppPath(argv[0]) };
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
