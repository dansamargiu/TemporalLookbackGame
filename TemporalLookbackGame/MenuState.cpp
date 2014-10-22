#include "stdafx.h"
#include "MenuState.h"

using namespace NEngine;

MenuState::MenuState(const NUtility::FancyFactory& factory)
: m_factory(factory), m_shouldRun(true)
{

}

MenuState::~MenuState()
{
}

bool MenuState::ShouldRun() const
{
	return m_shouldRun;
}

void MenuState::Draw()
{	
}

int NEngine::MenuState::WindowCloseCallback()
{
	m_shouldRun = false;
	return 0;
}

void NEngine::MenuState::SetKeyCallback(int key, int action)
{
	(void)key;
	(void)action;
}

void NEngine::MenuState::SetMousePosCallback(int x, int y)
{
	(void)x;
	(void)y;
}
