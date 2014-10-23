#pragma once

namespace NEngine
{
	class IResourceManager
	{
	public:
		virtual ~IResourceManager() {}
		virtual bool Initialize() = 0;
		virtual bool LoadResources() = 0;
	};
}