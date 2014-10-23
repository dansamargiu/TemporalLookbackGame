#pragma once
#include "IRenderer.h"

namespace NEngine
{
	class Horde3DRenderer : public IRenderer
	{
	public:
		virtual bool Initialize() override;
		virtual void Release() override;
	};
}