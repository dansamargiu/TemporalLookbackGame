#pragma once
#include "IGraphics.h"
#include "TemporalEngine.h"

#include <Horde3D.h>
#include <Horde3DUtils.h>

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
		H3DNode m_model;
		H3DNode m_cam;
		float m_time;

		DISALLOW_COPY_AND_ASSIGN(MenuState);
	};
}
