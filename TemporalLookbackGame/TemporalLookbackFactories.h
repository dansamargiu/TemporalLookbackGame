#pragma once
#include "IGraphics.h"

namespace NEngine 
{
	class TemporalLookbackFactories
	{
	public:
		static void SetupEngineFactories(NUtility::FancyFactory& factory)
		{
			factory.RegisterType<IGraphics, GLFWGraphics>();
		}
	};
}
