#include "stdafx.h"
#include "FactoryRegistry.h"

using namespace NEngine;

void FactoryRegistry::SetupEngineFactories(NUtility::FancyFactory& factory)
{
	factory.RegisterType<IGraphics, GLFWGraphics>();
	factory.RegisterTypeWithFactoryRef<IEngineState, GameState>(GAME_STATE);
}
