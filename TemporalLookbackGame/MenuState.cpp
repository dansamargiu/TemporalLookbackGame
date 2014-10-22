#include "stdafx.h"
#include "MenuState.h"

using namespace NEngine;

MenuState::MenuState(const NUtility::FancyFactory& factory)
: m_factory(factory), m_graphics(nullptr), m_shouldRun(true)
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

void MenuState::RegisterCallbacks()
{
	m_graphics = m_factory.Resolve<IGraphics>();
	if (!m_graphics)
	{
		return;
	}

	CallbackContainer::destroy_instance();
	CallbackContainer::get_instance(this);
	m_graphics->SetWindowCloseCallback();
	m_graphics->SetKeyCallback();
	m_graphics->SetMousePosCallback();
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
