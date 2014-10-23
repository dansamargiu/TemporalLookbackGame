#pragma once
#include "IGraphics.h"
#include "IRenderer.h"
#include "ICameraNode.h"

// TODO: Remove
#include "KnightDemoApp.h"

namespace NEngine 
{
	class GameState : public IEngineState
	{
	public:
		GameState(const NUtility::FancyFactory& factory);
		virtual ~GameState();

		virtual bool Initialize(const EngineParams& params) override;
		virtual void Draw(float fps) override;
		virtual bool ShouldRun() const override;

		virtual int WindowCloseCallback() override;
		virtual void SetKeyCallback(int key, int action) override;
		virtual void SetMousePosCallback(int x, int y) override;
	private:
		const NUtility::FancyFactory& m_factory;
		bool m_shouldRun;
		std::shared_ptr<KnightDemoApp> m_knightDemo;
		std::shared_ptr<IRenderer> m_renderer;
		std::shared_ptr<ICameraNode> m_camera;

		DISALLOW_COPY_AND_ASSIGN(GameState);
		
	};
}
