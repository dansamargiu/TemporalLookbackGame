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
	(void)x;
	(void)y;
	/*static int mx0, my0;

	float dX = (float)(x - mx0);
	float dY = (float)(my0 - y);

	// Look left/right
	m_camera->TSR()->r.y -= dX / 100 * 30;

	// Loop up/down but only in a limited range
	m_camera->TSR()->r.x += dY / 100 * 30;
	if (m_camera->TSR()->r.x > 90) m_camera->TSR()->r.x = 90;
	if (m_camera->TSR()->r.x < -90) m_camera->TSR()->r.x = -90;

	mx0 = x; my0 = y;*/
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

void NEngine::GameInputManager::BindHoldKeyDownAction(int key, std::function<void() > binding)
{
	m_holdKeyDownBinds[key] = binding;
}


