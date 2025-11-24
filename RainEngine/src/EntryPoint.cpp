#include "EntryPoint.h"
#include "framework/Application.h"

#include <iostream>

int main()
{

#ifdef _WIN32
#ifdef _DEBUG
#pragma comment(linker, "/SUBSYSTEM:console")
#else
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif
#endif

	rn::Application* app = GetApplication();
	app->Run();

	delete app;

	//std::cin.get();
}