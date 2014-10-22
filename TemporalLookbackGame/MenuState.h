#pragma once
#include "IEngineState.h"
#include "IGraphics.h"

namespace NEngine 
{
	class MenuState : public IEngineState
	{
	public:
		MenuState(const NUtility::FancyFactory& factory);
		virtual ~MenuState();

		virtual void RegisterCallbacks() override;
		virtual void Draw() override;
		virtual bool ShouldRun() const override;

		virtual int WindowCloseCallback() override;
		virtual void SetKeyCallback(int key, int action) override;
		virtual void SetMousePosCallback(int x, int y) override;
	private:
		const NUtility::FancyFactory& m_factory;
		std::shared_ptr<IGraphics> m_graphics;
		bool m_shouldRun;

		DISALLOW_COPY_AND_ASSIGN(MenuState);
	};
}
