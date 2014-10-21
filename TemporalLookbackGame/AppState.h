#pragma once

class Application;

struct AppState {
	bool fullScreen = false;
	bool running = false;
	double t0 = 0;
	int mx0 = 0;
	int my0 = 0;
	Application *app = nullptr;
};