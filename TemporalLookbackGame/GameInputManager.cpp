#include "stdafx.h"
#include "GameInputManager.h"
#include "glfw.h"

using namespace NEngine;

bool GameInputManager::Initialize()
{
	return true;
}

void GameInputManager::MousePos(int x, int y)
{
	if (m_mouseMoveBinding)	m_mouseMoveBinding(x, y);
}

void GameInputManager::KeyAction(int key, int action)
{
	auto binding = m_callbackKeyBinds.find(std::make_pair(key, action));
	if (binding != m_callbackKeyBinds.end())
	{
		binding->second();
	}
}

// This gets called once per game loop.
void GameInputManager::UpdateKeyStates()
{
	for (int i = 0; i < GLFW_KEY_LAST; ++i)
	{
		if (GLFW_PRESS == glfwGetKey(i))
		{
			auto binding = m_holdKeyDownBinds.find(i);
			if (binding != m_holdKeyDownBinds.end())
			{
				binding->second();
			}
		}
	}
}

void GameInputManager::BindCallbackKeyAction(int key, int action, std::function<void()> binding)
{
	m_callbackKeyBinds[std::make_pair(key, action)] = binding;
}

void GameInputManager::BindHoldKeyDownAction(int key, std::function<void() > binding)
{
	m_holdKeyDownBinds[key] = binding;
}

void NEngine::GameInputManager::BindMouseMove(std::function<void(int, int) > binding)
{
	m_mouseMoveBinding = binding;
}


