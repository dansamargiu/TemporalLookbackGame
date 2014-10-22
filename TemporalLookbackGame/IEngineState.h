#pragma once

class IEngineState
{
public:
	virtual ~IEngineState() {};
	virtual void RegisterCallbacks() = 0;
	virtual void Draw() = 0;
	virtual bool ShouldRun() const = 0;

	// Callbacks
	virtual int WindowCloseCallback() = 0;
	virtual void SetKeyCallback(int key, int action) = 0;
	virtual void SetMousePosCallback(int x, int y) = 0;
};