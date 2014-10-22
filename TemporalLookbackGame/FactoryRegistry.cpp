#include "stdafx.h"
#include "FactoryRegistry.h"

using namespace NEngine;

void FactoryRegistry::SetupEngineFactories(NUtility::FancyFactory& factory)
{
	factory.RegisterType<IGraphics, GLFWGraphics>();
	factory.RegisterTypeWithFactoryReference<IEngineState, MenuState>(MAIN_MENU);
}
