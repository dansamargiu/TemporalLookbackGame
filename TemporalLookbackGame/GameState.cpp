#include "stdafx.h"
#include "GameState.h"
#include "glfw.h" // TODO: remove once we abstract this away
#include "Horde3DUtils.h"
#include "IResourceManager.h"
#include "CallbackContainer.h"
#include "IInputManager.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "glm/gtc/type_ptr.hpp"

using namespace NEngine;

GameState::~GameState()
{
	glfwEnable(GLFW_MOUSE_CURSOR);

	// Destroy the CallbackContainer
	CallbackContainer::destroy_instance();

	// The Game state is effectively responsible for managing this object.
	// We should only call this here.
	if (m_renderer) m_renderer->Release();
}

bool GameState::Initialize(const EngineParams& params)
{
	glfwDisable(GLFW_MOUSE_CURSOR);

	// Make the Callbacks point to this object.
	CallbackContainer::destroy_instance();
	CallbackContainer::get_instance(this);

	// Initialize members
	m_shouldRun = true;

	// Get the renderer object and initialize it. 
	// This should be the only place we initialize this object.
	m_renderer = m_factory.Resolve<IRenderer>();
	if (!m_renderer || !m_renderer->Initialize()) return false;

	// Initialize Camera node
	m_camera = m_factory.Resolve<ICameraNode>();
	if (!m_camera || !m_camera->Initialize()) return false;
	m_camera->ResizeViewport(params.winWidth, params.winHeight);

	// Initialize demo app. TODO: Remove this once everything is flushed out.
	m_knightDemo = std::make_shared<KnightDemoApp>(m_factory);
	if (!m_knightDemo->init()) return false;

	// Initialize Input manager
	m_inputManager = m_factory.Resolve<IInputManager>();
	if (!m_inputManager || !m_inputManager->Initialize()) return false;

	// Set key bindings
	m_inputManager->BindCallbackKeyAction(GLFW_KEY_ESC, GLFW_PRESS, [&] { m_shouldRun = false; });
	m_inputManager->BindHoldKeyDownAction('W', [&] { 
		const float* camMatrix;
		m_camera->GetMatrix(&camMatrix, 0x0);
		auto translateMat = glm::translate(glm::make_mat4(camMatrix), glm::vec3(0.0f, 0.0f, -1.0f));
		m_camera->SetMatrix(glm::value_ptr(translateMat));
	});
	m_inputManager->BindHoldKeyDownAction('A', [&] {
		const float* camMatrix;
		m_camera->GetMatrix(&camMatrix, 0x0);
		auto translateMat = glm::translate(glm::make_mat4(camMatrix), glm::vec3(-1.0f, 0.0f, 0.0f));
		m_camera->SetMatrix(glm::value_ptr(translateMat));
	});
	m_inputManager->BindHoldKeyDownAction('D', [&] {
		const float* camMatrix;
		m_camera->GetMatrix(&camMatrix, 0x0);
		auto translateMat = glm::translate(glm::make_mat4(camMatrix), glm::vec3(1.0f, 0.0f, 0.0f));
		m_camera->SetMatrix(glm::value_ptr(translateMat));
	});
	m_inputManager->BindHoldKeyDownAction('S', [&] {
		const float* camMatrix;
		m_camera->GetMatrix(&camMatrix, 0x0);
		auto translateMat = glm::translate(glm::make_mat4(camMatrix), glm::vec3(0.0f, 0.0f, 1.0f));
		m_camera->SetMatrix(glm::value_ptr(translateMat));
	});	

	return true;
}

bool GameState::ShouldRun() const
{
	return m_shouldRun;
}

void GameState::StateLoop(float fps)
{
	// Update key states
	m_inputManager->UpdateKeyStates();
	
	// Camera Render
	m_camera->Render();

	// Render Demo
	m_knightDemo->mainLoop(fps);

	m_renderer->FinalizeFrame();
}

int GameState::WindowCloseCallback()
{
	m_shouldRun = false;
	return 0;
}

void GameState::KeyCallback(int key, int action)
{
	if (!m_shouldRun) return; // TODO: what does this do? maybe not needed.
	m_inputManager->KeyAction(key, action);
}

void GameState::MousePosCallback(int x, int y)
{
	if (!m_shouldRun) return;
	m_inputManager->MousePos(x, y);
}
