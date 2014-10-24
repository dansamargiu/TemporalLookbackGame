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

		virtual ~CallbackContainer() {}

	public:
		int WindowClose()
		{
			if (m_engineState)
			{
				return m_engineState->WindowCloseCallback();
			}

			return 0;
		}

		void SetKey(int key, int action)
		{
			if (m_engineState) m_engineState->KeyCallback(key, action);
		}

		void SetMousePos(int x, int y)
		{
			if (m_engineState) m_engineState->MousePosCallback(x, y);
		}

	private:
		IEngineState* m_engineState;
	};
}
