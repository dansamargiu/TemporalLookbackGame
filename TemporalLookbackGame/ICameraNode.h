#pragma once

namespace NEngine
{
	class ICameraNode
	{
	public:
		virtual ~ICameraNode() {}
		virtual bool Initialize() = 0;
	};
}