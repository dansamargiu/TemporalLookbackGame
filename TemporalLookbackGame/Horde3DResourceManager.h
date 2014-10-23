#pragma once
#include "IResourceManager.h"

namespace NEngine
{
	class Horde3DResourceManager : public IResourceManager
	{
	public:
		virtual bool Initialize() override
		{
			return true;
		}
	};
}