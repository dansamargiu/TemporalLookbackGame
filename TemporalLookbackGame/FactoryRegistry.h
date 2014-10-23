#pragma once
#include "IGraphics.h"
#include "GameState.h"

namespace NEngine 
{
	class FactoryRegistry
	{
	public:
		static void SetupEngineFactories(NUtility::FancyFactory& factory);
	};
}
