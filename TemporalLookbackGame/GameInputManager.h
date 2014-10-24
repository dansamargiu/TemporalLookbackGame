#pragma once
#include "IInputManager.h"
#include <vector>

namespace NEngine
{
	class GameInputManager : public IInputManager
	{
	public:		
		virtual bool Initialize() override;
		virtual void UpdateKeyStates() override;
		virtual void KeyAction(int key, int action) override;
		virtual void MousePos(int x, int y) override;
		virtual void BindCallbackKeyAction(int key, int action, std::function<void()> binding) override;
		virtual void BindHoldKeyDownAction(int key, std::function<void() > binding) override;
		virtual void BindMouseMove(std::function<void(int, int) > binding) override;
	private:
		std::map<std::pair<int, int>, std::function<void()>> m_callbackKeyBinds;
		std::map<int, std::function<void()>> m_holdKeyDownBinds;
		std::function<void(int, int)> m_mouseMoveBinding;
	};
}