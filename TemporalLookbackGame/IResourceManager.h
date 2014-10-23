#pragma once

namespace NEngine
{
	class IResourceManager
	{
	public:
		virtual ~IResourceManager() {}
		virtual bool Initialize() = 0;
	};
}