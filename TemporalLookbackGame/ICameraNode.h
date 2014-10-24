#pragma once
#include "TSRStructs.h"

namespace NEngine
{
	class ICameraNode
	{
	public:
		virtual ~ICameraNode() {}
		virtual bool Initialize() = 0;
		virtual void ResizeViewport(int width, int height) = 0;
		virtual void Render() = 0;
		virtual void GetMatrix(const float ** relMatrix, const float ** absMatrix) = 0;
		virtual void SetMatrix(const float *matrix) = 0;
	};
}