#include "stdafx.h"
#include "FactoryRegistry.h"
#include "GLFWGraphics.h"
#include "GameState.h"
#include "Horde3DRenderer.h"
#include "Horde3DResourceManager.h"
#include "BasicCameraNode.h"

using namespace NEngine;

void FactoryRegistry::SetupEngineFactories(NUtility::FancyFactory& factory)
{
	factory.RegisterType<IGraphics, GLFWGraphics>();
	factory.RegisterType<IRenderer, Horde3DRenderer>();
	factory.RegisterTypeWithFactoryRef<IEngineState, GameState>(GAME_STATE);
	factory.RegisterTypeWithFactoryRef<ICameraNode, BasicCameraNode>();
}
