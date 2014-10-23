#pragma once
#include "IGraphics.h"
#include "TemporalEngine.h"
#include "KnightDemoApp.h"

namespace NEngine 
{
	class MenuState : public IEngineState
	{
	public:
		MenuState(const NUtility::FancyFactory& factory);
		virtual ~MenuState();

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

		DISALLOW_COPY_AND_ASSIGN(MenuState);
		
	};
}
