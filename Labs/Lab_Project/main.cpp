// Student: Vojtěch Kursa (KUR0170)

#include "Application.h"



int main(const int argc, const char** argv)
{
	Application* app = Application::getInstance();

	app->init();

	app->createWindow();

	app->printVersionInfo();

	if(argc > 1)
		app->loadDefaultScene(argv[1]);
	else
		app->loadDefaultScene();

	app->run();

	return 0;
}