#pragma once
#include "IEngineState.h"
#include "IRenderer.h"
#include "ICameraNode.h"
#include "IInputManager.h"

#include "KnightDemoApp.h" // TODO: Remove once we abstract it out.


namespace NEngine 
{
	class GameState : public IEngineState
	{
	public:
		FACTORY_HOLDER(GameState);
		virtual ~GameState();
		virtual bool Initialize(const EngineParams& params) override;
		virtual void StateLoop(float fps) override;
		virtual bool ShouldRun() const override;

		virtual int WindowCloseCallback() override;
		virtual void KeyCallback(int key, int action) override;
		virtual void MousePosCallback(int x, int y) override;
	private:
		bool m_shouldRun;
		std::shared_ptr<KnightDemoApp> m_knightDemo;
		std::shared_ptr<IRenderer> m_renderer;
		std::shared_ptr<ICameraNode> m_camera;
		std::shared_ptr<IInputManager> m_inputManager;

		DISALLOW_COPY_AND_ASSIGN(GameState);
	};
}
