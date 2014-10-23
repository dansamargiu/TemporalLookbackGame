#pragma once

namespace NEngine 
{
	class FactoryRegistry
	{
	public:
		static void SetupEngineFactories(NUtility::FancyFactory& factory);
	};
}
