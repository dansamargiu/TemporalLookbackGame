#include "stdafx.h"
#include "FactoryRegistry.h"
#include "GLFWGraphics.h"
#include "GameState.h"
#include "Horde3DRenderer.h"
#include "Horde3DResourceManager.h"
#include "BasicCameraNode.h"
#include "GameInputManager.h"

using namespace NEngine;

void FactoryRegistry::SetupEngineFactories(NUtility::FancyFactory& factory)
{
	factory.RegisterType<IGraphics, GLFWGraphics>();
	factory.RegisterType<IRenderer, Horde3DRenderer>();
	factory.RegisterType<IInputManager, GameInputManager>();
	factory.RegisterTypeWithFactoryRef<IEngineState, GameState>(GAME_STATE);
	factory.RegisterTypeWithFactoryRef<ICameraNode, BasicCameraNode>();
}
