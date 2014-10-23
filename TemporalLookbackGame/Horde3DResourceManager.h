#pragma once
#include "IResourceManager.h"

namespace NEngine
{
	class Horde3DResourceManager : public IResourceManager
	{
	public:
		Horde3DResourceManager(std::string contentDir);
		virtual bool Initialize() override;
		virtual int AddResource(int type, const char *name, int flags) override;
		virtual bool LoadResources() override;
	private:
		std::string m_contentDir;
	};
}