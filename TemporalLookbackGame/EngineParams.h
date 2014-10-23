#pragma once
#include <string>

namespace NEngine
{
	struct EngineParams
	{
		std::string appPath;
		int winWidth;
		int winHeight;
		bool fullscreen;
	};
}