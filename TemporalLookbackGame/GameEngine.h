#pragma once
#include <string>
#include "IGraphics.h"
#include "IRenderer.h"
#include "IEngineState.h"

namespace NEngine
{
	class GameEngine
	{
	public:
		FACTORY_HOLDER(GameEngine);
		virtual ~GameEngine();

		bool Initialize(const EngineParams& params);
		bool SetState(const std::string& stateName);
		void Launch();
	private:
		EngineParams m_params;
		std::shared_ptr<IGraphics> m_graphics;
		std::shared_ptr<IRenderer> m_renderer;
		std::shared_ptr<IEngineState> m_currentEngineState;

		DISALLOW_COPY_AND_ASSIGN(GameEngine);
	};
}
