#pragma once

namespace NEngine
{
	class IRenderer
	{
	public:
		virtual ~IRenderer() {}
		virtual bool Initialize() = 0;
		virtual void Release() = 0;
	};
}