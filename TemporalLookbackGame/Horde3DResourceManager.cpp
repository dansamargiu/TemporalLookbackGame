#include "stdafx.h"
#include "Horde3DResourceManager.h"
#include "Horde3DUtils.h"

using namespace NEngine;

Horde3DResourceManager::Horde3DResourceManager(std::string contentDir) : m_contentDir(contentDir)
{

}

bool Horde3DResourceManager::Initialize()
{
	return true;
}

bool Horde3DResourceManager::LoadResources()
{
	return h3dutLoadResourcesFromDisk(m_contentDir.c_str());
}


