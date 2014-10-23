#pragma once
#include "ICameraNode.h"

namespace NEngine
{
	class BasicCameraNode : public ICameraNode
	{
	public:
		FACTORY_HOLDER(BasicCameraNode);		
		virtual bool Initialize() override;
	private:

		DISALLOW_COPY_AND_ASSIGN(BasicCameraNode);
	};
}