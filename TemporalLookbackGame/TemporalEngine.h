#pragma once
#include <string>

namespace NEngine
{
	struct EngineParams
	{
		std::string appPath;
	};

	class TemporalEngine
	{
	public:
		TemporalEngine(const NUtility::FancyFactory& factory);
		virtual ~TemporalEngine();

		bool Initialize(const EngineParams& params);
		bool SetState(const std::string& stateName);
		bool Launch();
	private:
		const NUtility::FancyFactory& mFactory;

		DISALLOW_COPY_AND_ASSIGN(TemporalEngine);
	};
}
