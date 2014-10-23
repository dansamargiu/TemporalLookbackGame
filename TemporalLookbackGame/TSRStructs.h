#pragma once

namespace NEngine
{
	struct ObjectTranslation
	{
		float x;
		float y;
		float z;
	};

	struct ObjectRotation
	{
		float x;
		float y;
		float z;
	};

	struct ObjectScale
	{
		float x;
		float y;
		float z;
	};

	struct ObjectTSR
	{
		ObjectTranslation t;
		ObjectRotation r;
		ObjectScale s;
	};
}