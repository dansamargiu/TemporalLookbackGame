#include "stdafx.h"
#include "Horde3DRenderer.h"
#include "Horde3D.h"

using namespace NEngine;

bool Horde3DRenderer::Initialize()
{
	return h3dInit();
}

void Horde3DRenderer::Release()
{
	h3dRelease();
}
