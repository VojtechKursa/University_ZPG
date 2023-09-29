// Student: Vojtěch Kursa (KUR0170)

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdlib.h>

#include "Application.h"



int main(void)
{
	Application app = Application();

	app.init();

	app.createWindow();

	app.printVersionInfo();

	app.loadDefaultScene();

	app.run();
}