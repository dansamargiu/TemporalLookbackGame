#include "stdafx.h"
#include "MenuState.h"

using namespace NEngine;

MenuState::MenuState(const NUtility::FancyFactory& factory)
: m_factory(factory), m_shouldRun(true), m_knightDemo(nullptr)
{
}

MenuState::~MenuState()
{
	m_knightDemo->release();
}

bool NEngine::MenuState::Initialize(const EngineParams& params)
{
	m_knightDemo = std::make_shared<KnightDemoApp>(params.appPath);
	if (!m_knightDemo->init())
	{
		return false;
	}

	m_knightDemo->resize(params.winWidth, params.winHeight);
	return true;
}

bool MenuState::ShouldRun() const
{
	return m_shouldRun;
}

void MenuState::Draw(float fps)
{
	// Update key states
	for (int i = 0; i < 320; ++i)
		m_knightDemo->setKeyState(i, glfwGetKey(i) == GLFW_PRESS);
	m_knightDemo->keyStateHandler();

	// Render
	m_knightDemo->mainLoop(fps);
}

int NEngine::MenuState::WindowCloseCallback()
{
	m_shouldRun = false;
	return 0;
}

void NEngine::MenuState::SetKeyCallback(int key, int action)
{
	if (!m_shouldRun) return;

	if (action == GLFW_PRESS)
	{
		switch (key)
		{
		case GLFW_KEY_ESC:
			m_shouldRun = false;
			break;
		}
	}
}

void NEngine::MenuState::SetMousePosCallback(int x, int y)
{
	(void)x;
	(void)y;
}
