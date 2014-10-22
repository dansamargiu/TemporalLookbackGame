#pragma once
#include <string>
#include "IGraphics.h"
#include "IEngineState.h"

namespace NEngine
{
	class TemporalEngine
	{
	public:
		TemporalEngine(const NUtility::FancyFactory& factory);
		virtual ~TemporalEngine();

		bool Initialize(const EngineParams& params);
		bool SetState(const std::string& stateName);
		void Launch();
	private:
		EngineParams m_params;
		const NUtility::FancyFactory& m_Factory;
		std::shared_ptr<IGraphics> m_graphics;
		std::shared_ptr<IEngineState> m_currentEngineState;

		DISALLOW_COPY_AND_ASSIGN(TemporalEngine);
	};
}
