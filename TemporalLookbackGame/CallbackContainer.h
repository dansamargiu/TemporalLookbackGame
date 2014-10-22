#pragma once
#include "IEngineState.h"

namespace NEngine
{	
	class CallbackContainer : public NUtility::Singleton<CallbackContainer>
	{
		friend class NUtility::Singleton<CallbackContainer>;
	private:
		CallbackContainer() : m_engineState(nullptr)
		{
		}

		CallbackContainer(IEngineState* engineState) : m_engineState(engineState)
		{
		}

	public:
		int WindowClose()
		{
			return m_engineState->WindowCloseCallback();
		}

		void SetKey(int key, int action)
		{
			m_engineState->SetKeyCallback(key, action);
		}

		void SetMousePos(int x, int y)
		{
			m_engineState->SetMousePosCallback(x, y);
		}

	private:
		IEngineState* m_engineState;
	};
}
