#pragma once
#include "IGraphics.h"
#include "MenuState.h"

namespace NEngine 
{
	class FactoryRegistry
	{
	public:
		static void SetupEngineFactories(NUtility::FancyFactory& factory);
	};
}
