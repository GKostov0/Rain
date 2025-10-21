#include "EntryPoint.h"
#include "framework/Application.h"

int main()
{
	rn::Application* app = GetApplication();
	app->Run();

	delete app;
}