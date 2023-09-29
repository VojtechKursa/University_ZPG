// Student: Vojtěch Kursa (KUR0170)



//Include GLEW
#include <GL/glew.h>
//Include GLFW
#include <GLFW/glfw3.h>

//Include the standard C++ headers  
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