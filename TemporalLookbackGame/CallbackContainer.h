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

		CallbackContainer(std::shared_ptr<IEngineState> engineState) : m_engineState(engineState)
		{
		}

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
			if (m_engineState) m_engineState->SetKeyCallback(key, action);
		}

		void SetMousePos(int x, int y)
		{
			if (m_engineState) m_engineState->SetMousePosCallback(x, y);
		}

	private:
		std::shared_ptr<IEngineState> m_engineState;
	};
}
