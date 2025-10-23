#include "EntryPoint.h"
#include "framework/Application.h"

#include <iostream>

int main()
{
	rn::Application* app = GetApplication();
	app->Run();

	delete app;

	//std::cin.get();
}