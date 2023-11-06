#include "Application.h"

#include <stdio.h>
#include <stdlib.h>

#ifdef _MSC_VER 
#define strncasecmp _strnicmp
#define strcasecmp _stricmp
#endif

#include "SceneLoader.h"

#include "Events/KeyEventData.h"
#include "Events/ViewPortChangedEventData.h"
#include "Events/CursorEventData.h"
#include "Events/MouseButtonEventData.h"
#include "Events/FrameEventData.h"



Application Application::instance = Application();



void Application::error_callback(int error, const char* description)
{
	fputs(description, stderr);
}

void Application::key_callback_static(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	(static_cast<Application*>(glfwGetWindowUserPointer(window)))->key_callback(window, key, scancode, action, mods);
}

void Application::window_focus_callback_static(GLFWwindow* window, int focused)
{
	(static_cast<Application*>(glfwGetWindowUserPointer(window)))->window_focus_callback(window, focused);
}

void Application::window_iconify_callback_static(GLFWwindow* window, int iconified)
{
	(static_cast<Application*>(glfwGetWindowUserPointer(window)))->window_iconify_callback(window, iconified);
}

void Application::window_size_callback_static(GLFWwindow* window, int width, int height)
{
	(static_cast<Application*>(glfwGetWindowUserPointer(window)))->window_size_callback(window, width, height);
}

void Application::cursor_callback_static(GLFWwindow* window, double x, double y)
{
	(static_cast<Application*>(glfwGetWindowUserPointer(window)))->cursor_callback(window, x, y);
}

void Application::button_callback_static(GLFWwindow* window, int button, int action, int mode)
{
	(static_cast<Application*>(glfwGetWindowUserPointer(window)))->button_callback(window, button, action, mode);
}



void Application::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	//printf("key_callback [%d,%d,%d,%d] \n", key, scancode, action, mods);

	const KeyEventData eventData(key, scancode, action, mods);
	const Event event(EVENT_KEY, (EventData*)&eventData);
	this->notifyAll(&event);
}

void Application::window_focus_callback(GLFWwindow *window, int focused)
{
	//printf("window_focus_callback \n");
}

void Application::window_iconify_callback(GLFWwindow *window, int iconified)
{
	//printf("window_iconify_callback \n");
}

void Application::window_size_callback(GLFWwindow *window, int width, int height)
{
	//printf("resize %d, %d \n", width, height);
	glViewport(0, 0, width, height);

	const ViewPortChangedEventData eventData(width, height);
	const Event event(EVENT_VIEWPORT, (EventData*)&eventData);
	this->notifyAll(&event);
}

void Application::cursor_callback(GLFWwindow *window, double x, double y)
{
	//printf("cursor_callback \n");

	const CursorEventData eventData(x, y);
	const Event event(EVENT_CURSOR, (EventData*)&eventData);
	this->notifyAll(&event);
}

void Application::button_callback(GLFWwindow *window, int button, int action, int mode)
{
	//printf("button_callback [%d,%d,%d]\n", button, action, mode);

	const MouseButtonEventData eventData(button, action, mode);
	const Event event(EVENT_MOUSE_BUTTON, (EventData*)&eventData);
	this->notifyAll(&event);
}



void Application::notifyFrameObservers(double timeSinceLastFrameSec)
{
	const FrameEventData eventData(timeSinceLastFrameSec);
	const Event event(EVENT_FRAME, (EventData*)&eventData);
	this->notifyAll(&event);
}



Application::Application()
{
	this->window = nullptr;
	this->renderer = nullptr;
}

Application::~Application()
{
	if (this->renderer != nullptr)
	{
		delete this->renderer;
		this->renderer = nullptr;
	}

	this->destroyWindow();
	this->terminate();
}



Application* Application::getInstance()
{
	return &Application::instance;
}

Renderer *Application::getRenderer()
{
	return this->renderer;
}



void Application::init()
{
	glfwSetErrorCallback(error_callback);
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		exit(EXIT_FAILURE);
	}

	/*
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE,
		GLFW_OPENGL_CORE_PROFILE);
	*/

	this->renderer = new Renderer();
}

void Application::terminate()
{
	glfwTerminate();
}



void Application::bindCallbacks()
{
	glfwSetWindowUserPointer(this->window, this);

	glfwSetKeyCallback(this->window, this->key_callback_static);
	glfwSetCursorPosCallback(this->window, this->cursor_callback_static);
	glfwSetMouseButtonCallback(this->window, this->button_callback_static);
	glfwSetWindowFocusCallback(this->window, this->window_focus_callback_static);
	glfwSetWindowIconifyCallback(this->window, this->window_iconify_callback_static);
	glfwSetWindowSizeCallback(this->window, this->window_size_callback_static);
}



void Application::createWindow(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share)
{
	this->window = glfwCreateWindow(width, height, title, monitor, share);
	if (!this->window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	this->bindCallbacks();

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	
	// start GLEW extension handler
	glewExperimental = GL_TRUE;
	glewInit();

	glfwGetFramebufferSize(this->window, &width, &height);
	glViewport(0, 0, width, height);
}

void Application::destroyWindow()
{
	if (this->window != nullptr)
	{
		glfwDestroyWindow(this->window);

		this->window = nullptr;
	}
}



void Application::printVersionInfo()
{
	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
	printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
	printf("Vendor %s\n", glGetString(GL_VENDOR));
	printf("Renderer %s\n", glGetString(GL_RENDERER));
	printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	int major, minor, revision;
	glfwGetVersion(&major, &minor, &revision);
	printf("Using GLFW %i.%i.%i\n", major, minor, revision);
}



void Application::loadDefaultScene(const char* scene)
{
	if (scene == nullptr)
		scene = "forest";
	
	if(!strcasecmp(scene, "rotate"))
		SceneLoader::loadRotatingSquare(this->renderer);
	else if(!strcasecmp(scene, "3d"))
		SceneLoader::loadDefault3DScene(this->renderer);
	else if(!strcasecmp(scene, "cont"))
		SceneLoader::loadContinuousMovementDemo(this->renderer);
	else if(!strcasecmp(scene, "solar"))
		SceneLoader::loadSolarSystem(this->renderer);
	else if(!strcasecmp(scene, "sphere"))
		SceneLoader::loadSphereWithLight(this->renderer, BLINN);
	else if(!strcasecmp(scene, "spheres"))
		SceneLoader::loadSpheresWithLight(this->renderer, BLINN);
	else if(!strcasecmp(scene, "lights"))
		SceneLoader::loadLightsDemoScene(this->renderer);
	else if(!strcasecmp(scene, "forest"))
		SceneLoader::loadForest(this->renderer);
	else if(!strcasecmp(scene, "spotlight"))
		SceneLoader::loadSpotlightTest(this->renderer);
	else if(!strcasecmp(scene, "texture"))
		SceneLoader::loadTextureTest(this->renderer);
	else
		SceneLoader::loadForest(this->renderer);
}



void Application::run()
{
	glEnable(GL_DEPTH_TEST);
	
	double lastFrameTime = glfwGetTime();
	double currentTime, elapsedTime;

	while (!glfwWindowShouldClose(this->window))
	{
		currentTime = glfwGetTime();
		elapsedTime = currentTime - lastFrameTime;
		lastFrameTime = currentTime;

		this->notifyFrameObservers(elapsedTime);

		this->renderer->renderNextFrame(this->window);

		glfwPollEvents();
	}
}
