#pragma once
#include "EngineParams.h"

namespace NEngine
{
	class IEngineState
	{
	public:
		virtual ~IEngineState() {};
		virtual bool Initialize(const EngineParams& params) = 0;
		virtual void Draw(float fps) = 0;
		virtual bool ShouldRun() const = 0;

		// Callbacks
		virtual int WindowCloseCallback() = 0;
		virtual void SetKeyCallback(int key, int action) = 0;
		virtual void SetMousePosCallback(int x, int y) = 0;
	};
}
