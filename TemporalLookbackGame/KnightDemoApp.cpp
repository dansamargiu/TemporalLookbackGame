// *************************************************************************************************
//
// Horde3D
//   Next-Generation Graphics Engine
//
// Sample Application
// --------------------------------------
// Copyright (C) 2006-2011 Nicolas Schulz
//
//
// This sample source file is not covered by the EPL as the rest of the SDK
// and may be used without any restrictions. However, the EPL's disclaimer of
// warranty and liability shall be in effect for this file.
//
// *************************************************************************************************

#include "stdafx.h"
#include "KnightDemoApp.h"
#include "Horde3D.h"
#include "Horde3DUtils.h"
#include <math.h>
#include <iomanip>
#include "IResourceManager.h"

using namespace std;

// Convert from degrees to radians
inline float degToRad(float f)
{
	return f * (3.1415926f / 180.0f);
}

bool KnightDemoApp::init()
{
	// Initialize members.
	for (unsigned int i = 0; i < 320; ++i)
	{
		_keys[i] = false;
		_prevKeys[i] = false;
	}

	_x = 5; _y = 3; _z = 19; _rx = 7; _ry = 15; _velocity = 10.0f;
	_curFPS = 30;

	_statMode = 0;
	_freezeMode = 0; _debugViewMode = false; _wireframeMode = false;
	_animTime = 0; _weight = 1.0f;

	// Set options
	h3dSetOption(H3DOptions::LoadTextures, 1);
	h3dSetOption(H3DOptions::TexCompression, 0);
	h3dSetOption(H3DOptions::FastAnimation, 0);
	h3dSetOption(H3DOptions::MaxAnisotropy, 4);
	h3dSetOption(H3DOptions::ShadowMapSize, 2048);

	// Add resources
	// Overlays
	_fontMatRes = h3dAddResource(H3DResTypes::Material, "overlays/font.material.xml", 0);
	_panelMatRes = h3dAddResource(H3DResTypes::Material, "overlays/panel.material.xml", 0);
	_logoMatRes = h3dAddResource(H3DResTypes::Material, "overlays/logo.material.xml", 0);
	// Environment
	H3DRes envRes = h3dAddResource(H3DResTypes::SceneGraph, "models/sphere/sphere.scene.xml", 0);
	// Knight
	H3DRes knightRes = h3dAddResource(H3DResTypes::SceneGraph, "models/knight/knight.scene.xml", 0);
	H3DRes knightAnim1Res = h3dAddResource(H3DResTypes::Animation, "animations/knight_order.anim", 0);
	H3DRes knightAnim2Res = h3dAddResource(H3DResTypes::Animation, "animations/knight_attack.anim", 0);
	// Particle system
	H3DRes particleSysRes = h3dAddResource(H3DResTypes::SceneGraph, "particles/particleSys1/particleSys1.scene.xml", 0);

	auto m_resourceManager = m_factory.Resolve<NEngine::IResourceManager>();
	if (!m_resourceManager || !m_resourceManager->Initialize()) return false;
	if (!m_resourceManager->LoadResources()) return false;

	// Add scene nodes
	// Add environment
	H3DNode env = h3dAddNodes(H3DRootNode, envRes);
	h3dSetNodeTransform(env, 0, -20, 0, 0, 0, 0, 20, 20, 20);
	// Add knight
	_knight = h3dAddNodes(H3DRootNode, knightRes);
	h3dSetNodeTransform(_knight, 0, 0, 0, 0, 180, 0, 0.1f, 0.1f, 0.1f);
	h3dSetupModelAnimStage(_knight, 0, knightAnim1Res, 0, "", false);
	h3dSetupModelAnimStage(_knight, 1, knightAnim2Res, 0, "", false);
	// Attach particle system to hand joint
	h3dFindNodes(_knight, "Bip01_R_Hand", H3DNodeTypes::Joint);
	H3DNode hand = h3dGetNodeFindResult(0);
	_particleSys = h3dAddNodes(hand, particleSysRes);
	h3dSetNodeTransform(_particleSys, 0, 40, 0, 90, 0, 0, 1, 1, 1);

	// Add light source
	H3DNode light = h3dAddLightNode(H3DRootNode, "Light1", 0, "LIGHTING", "SHADOWMAP");
	h3dSetNodeTransform(light, 0, 15, 10, -60, 0, 0, 1, 1, 1);
	h3dSetNodeParamF(light, H3DLight::RadiusF, 0, 30);
	h3dSetNodeParamF(light, H3DLight::FovF, 0, 90);
	h3dSetNodeParamI(light, H3DLight::ShadowMapCountI, 1);
	h3dSetNodeParamF(light, H3DLight::ShadowMapBiasF, 0, 0.01f);
	h3dSetNodeParamF(light, H3DLight::ColorF3, 0, 1.0f);
	h3dSetNodeParamF(light, H3DLight::ColorF3, 1, 0.8f);
	h3dSetNodeParamF(light, H3DLight::ColorF3, 2, 0.7f);
	h3dSetNodeParamF(light, H3DLight::ColorMultiplierF, 0, 1.0f);

	// Customize post processing effects
	H3DNode matRes = h3dFindResource(H3DResTypes::Material, "pipelines/postHDR.material.xml");
	h3dSetMaterialUniform(matRes, "hdrExposure", 2.5f, 0, 0, 0);
	h3dSetMaterialUniform(matRes, "hdrBrightThres", 0.5f, 0, 0, 0);
	h3dSetMaterialUniform(matRes, "hdrBrightOffset", 0.08f, 0, 0, 0);

	return true;
}


void KnightDemoApp::mainLoop(float fps)
{
	_curFPS = fps;

	h3dSetOption(H3DOptions::DebugViewMode, _debugViewMode ? 1.0f : 0.0f);
	h3dSetOption(H3DOptions::WireframeMode, _wireframeMode ? 1.0f : 0.0f);

	if (!_freezeMode)
	{
		_animTime += 1.0f / _curFPS;

		// Do animation blending
		h3dSetModelAnimParams(_knight, 0, _animTime * 24.0f, _weight);
		h3dSetModelAnimParams(_knight, 1, _animTime * 24.0f, 1.0f - _weight);

		// Animate particle systems (several emitters in a group node)
		unsigned int cnt = h3dFindNodes(_particleSys, "", H3DNodeTypes::Emitter);
		for (unsigned int i = 0; i < cnt; ++i)
			h3dAdvanceEmitterTime(h3dGetNodeFindResult(i), 1.0f / _curFPS);
	}

	// Show stats
	h3dutShowFrameStats(_fontMatRes, _panelMatRes, _statMode);
	if (_statMode > 0)
	{
		// Display weight
		_text.str("");
		_text << fixed << setprecision(2) << "Weight: " << _weight;
		h3dutShowText(_text.str().c_str(), 0.03f, 0.24f, 0.026f, 1, 1, 1, _fontMatRes);
	}
}

void KnightDemoApp::keyStateHandler()
{
	// ----------------
	// Key-press events
	// ----------------
	if (_keys[32] && !_prevKeys[32])  // Space
	{
		if (++_freezeMode == 3) _freezeMode = 0;
	}

	if (_keys[264] && !_prevKeys[264])  // F7
		_debugViewMode = !_debugViewMode;

	if (_keys[265] && !_prevKeys[265])  // F8
		_wireframeMode = !_wireframeMode;

	if (_keys[263] && !_prevKeys[263])  // F6
	{
		_statMode += 1;
		if (_statMode > H3DUTMaxStatMode) _statMode = 0;
	}

	// --------------
	// Key-down state
	// --------------
	if (_freezeMode != 2)
	{
		float curVel = _velocity / _curFPS;

		if (_keys[287]) curVel *= 5;	// LShift

		if (_keys['W'])
		{
			// Move forward
			_x -= sinf(degToRad(_ry)) * cosf(-degToRad(_rx)) * curVel;
			_y -= sinf(-degToRad(_rx)) * curVel;
			_z -= cosf(degToRad(_ry)) * cosf(-degToRad(_rx)) * curVel;
		}
		if (_keys['S'])
		{
			// Move backward
			_x += sinf(degToRad(_ry)) * cosf(-degToRad(_rx)) * curVel;
			_y += sinf(-degToRad(_rx)) * curVel;
			_z += cosf(degToRad(_ry)) * cosf(-degToRad(_rx)) * curVel;
		}
		if (_keys['A'])
		{
			// Strafe left
			_x += sinf(degToRad(_ry - 90)) * curVel;
			_z += cosf(degToRad(_ry - 90)) * curVel;
		}
		if (_keys['D'])
		{
			// Strafe right
			_x += sinf(degToRad(_ry + 90)) * curVel;
			_z += cosf(degToRad(_ry + 90)) * curVel;
		}
		if (_keys['1'])
		{
			// Change blend weight
			_weight += 2 / _curFPS;
			if (_weight > 1) _weight = 1;
		}
		if (_keys['2'])
		{
			// Change blend weight
			_weight -= 2 / _curFPS;
			if (_weight < 0) _weight = 0;
		}
	}
}