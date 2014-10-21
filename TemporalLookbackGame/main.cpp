// *************************************************************************************************
//
// Horde3D
//   Next-Generation Graphics Engine
//
// Sample Application
// --------------------------------------
// Copyright (C) 2006-2011 Nicolas Schulz
//
//
// This sample source file is not covered by the EPL as the rest of the SDK
// and may be used without any restrictions. However, the EPL's disclaimer of
// warranty and liability shall be in effect for this file.
//
// *************************************************************************************************

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <functional>
#include "glfw.h"
#include "app.h"
#include "AppState.h"

bool setupWindow(int, int, bool);

// Configuration
const int kAppWidth = 1024;
const int kAppHeight = 576;

static AppState gAppState;

const auto windowCloseCallback = []()
{
	gAppState.running = false;
	return 0;
};

const auto keyCallback = [](int key, int action)
{
	if (!gAppState.running) return;

	if (action == GLFW_PRESS)
	{
		int width = kAppWidth, height = kAppHeight;

		switch (key)
		{
		case GLFW_KEY_ESC:
			gAppState.running = false;
			break;
		case GLFW_KEY_F1:
			gAppState.app->release();
			glfwCloseWindow();

			// Toggle fullscreen mode
			gAppState.fullScreen = !gAppState.fullScreen;

			if (gAppState.fullScreen)
			{
				GLFWvidmode mode;
				glfwGetDesktopMode(&mode);

				float aspect = mode.Width / (float)mode.Height;
				if ((int)(aspect * 100) == 133 || (int)(aspect * 100) == 125)  // Standard
				{
					width = 1280; height = 1024;
				}
				else if ((int)(aspect * 100) == 177)                           // Widescreen 16:9
				{
					width = 1280; height = 720;
				}
				else if ((int)(aspect * 100) == 160)                           // Widescreen 16:10
				{
					width = 1280; height = 800;
				}
				else                                                            // Unknown
				{
					// Use desktop resolution
					width = mode.Width; height = mode.Height;
				}
			}

			if (!setupWindow(width, height, gAppState.fullScreen))
			{
				glfwTerminate();
				exit(-1);
			}

			gAppState.app->init();
			gAppState.app->resize(width, height);
			gAppState.t0 = glfwGetTime();
			break;
		}
	}
};

const auto mouseMoveCallback = [](int x, int y)
{
	if (!gAppState.running)
	{
		gAppState.mx0 = x;
		gAppState.my0 = y;
		return;
	}

	gAppState.app->mouseMoveEvent((float)(x - gAppState.mx0), (float)(gAppState.my0 - y));
	gAppState.mx0 = x;
	gAppState.my0 = y;
};

std::string extractAppPath( char *fullPath )
{
	const std::string s( fullPath );
	if( s.find( "/" ) != std::string::npos )
		return s.substr( 0, s.rfind( "/" ) ) + "/";
	else if( s.find( "\\" ) != std::string::npos )
		return s.substr( 0, s.rfind( "\\" ) ) + "\\";
	else
		return "";
}

bool setupWindow( int width, int height, bool fullscreen )
{
	// Create OpenGL window
	if( !glfwOpenWindow( width, height, 8, 8, 8, 8, 24, 8, fullscreen ? GLFW_FULLSCREEN : GLFW_WINDOW ) )
	{
		glfwTerminate();
		return false;
	}
	
	// Disable vertical synchronization
	glfwSwapInterval( 0 );

	// Set listeners
	glfwSetWindowCloseCallback(windowCloseCallback);	
	glfwSetKeyCallback(keyCallback);
	glfwSetMousePosCallback(mouseMoveCallback);
	
	return true;
}

int main( int argc, char** argv )
{
	// Initialize GLFW
	glfwInit();
	glfwEnable( GLFW_STICKY_KEYS );
	if (!setupWindow(kAppWidth, kAppHeight, gAppState.fullScreen)) return -1;
	
	// Initialize application and engine
	Application app(extractAppPath(argv[0]));
	gAppState.app = &app;

	if (!gAppState.fullScreen) glfwSetWindowTitle(app.getTitle());
	
	if ( !app.init() )
	{
		// Fake message box
		glfwCloseWindow();
		glfwOpenWindow( 800, 16, 8, 8, 8, 8, 24, 8, GLFW_WINDOW );
		glfwSetWindowTitle( "Unable to initialize engine - Make sure you have an OpenGL 2.0 compatible graphics card" );
		double startTime = glfwGetTime();
		while( glfwGetTime() - startTime < 5.0 ) {}  // Sleep
		
		std::cout << "Unable to initialize engine" << std::endl;
		std::cout << "Make sure you have an OpenGL 2.0 compatible graphics card";
		glfwTerminate();
		return -1;
	}
	app.resize( kAppWidth, kAppHeight );

	glfwDisable( GLFW_MOUSE_CURSOR );

	int frames = 0;
	float fps = 30.0f;
	gAppState.t0 = glfwGetTime();
	gAppState.running = true;

	// Game loop
	while (gAppState.running)
	{	
		// Calc FPS
		++frames;
		if( frames >= 3 )
		{
			double t = glfwGetTime();
			fps = frames / (float)(t - gAppState.t0);
			if( fps < 5 ) fps = 30;  // Handle breakpoints
			frames = 0;
			gAppState.t0 = t;
		}

		// Update key states
		for (int i = 0; i < 320; ++i)
		{
			app.setKeyState(i, glfwGetKey(i) == GLFW_PRESS);
		}
			
		app.keyStateHandler();

		// Render
		app.mainLoop( fps );
		glfwSwapBuffers();
	}

	glfwEnable( GLFW_MOUSE_CURSOR );

	// Quit
	app.release();	
	glfwTerminate();

	return 0;
}
