#pragma once
#include <functional>

namespace NEngine
{
	class IInputManager
	{
	public:
		virtual ~IInputManager() {}
		virtual bool Initialize() = 0;
		virtual void UpdateKeyStates() = 0;
		virtual void BindCallbackKeyAction(int key, int action, std::function<void()> binding) = 0;
		virtual void BindHoldKeyDownAction(int key, std::function<void()> binding) = 0;
		virtual void KeyAction(int key, int action) = 0;
		virtual void MousePos(int x, int y) = 0;
	};
}