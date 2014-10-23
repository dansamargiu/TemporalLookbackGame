#pragma once
#include "TSRStructs.h"

namespace NEngine
{
	class ICameraNode
	{
	public:
		virtual ~ICameraNode() {}
		virtual bool Initialize() = 0;
		virtual void Resize(int width, int height) = 0;
		virtual void Render() = 0;
		virtual ObjectTSR* TSR() = 0;
	};
}