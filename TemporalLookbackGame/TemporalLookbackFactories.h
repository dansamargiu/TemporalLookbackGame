#pragma once
#include "IGraphics.h"

using namespace NEngine;

class TemporalLookbackFactories
{
public:
	static void SetupEngineFactories(NUtility::FancyFactory& factory)
	{
		factory.RegisterType<IGraphics, GLFWGraphics>();
	}
};