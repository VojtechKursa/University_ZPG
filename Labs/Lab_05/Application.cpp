#include "Application.h"

#include <stdio.h>
#include <stdlib.h>

#include "DrawableObjectFactory.h"
#include "ObservedSubjectHelper.h"



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

	printf("key_callback [%d,%d,%d,%d] \n", key, scancode, action, mods);

	for(auto observer : this->keyObservers)
	{
		observer->keyHandler(window, key, scancode, action, mods);
	}
}

void Application::window_focus_callback(GLFWwindow *window, int focused)
{
	printf("window_focus_callback \n");
}

void Application::window_iconify_callback(GLFWwindow *window, int iconified)
{
	printf("window_iconify_callback \n");
}

void Application::window_size_callback(GLFWwindow *window, int width, int height)
{
	printf("resize %d, %d \n", width, height);
	glViewport(0, 0, width, height);

	for (auto observer : this->windowSizeObservers)
	{
		observer->viewPortChangedHandler(width, height);
	}
}

void Application::cursor_callback(GLFWwindow *window, double x, double y)
{
	printf("cursor_callback \n");

	for(auto observer : this->cursorObservers)
	{
		observer->cursorMovedHandler(window, x, y);
	}
}

void Application::button_callback(GLFWwindow *window, int button, int action, int mode)
{
	printf("button_callback [%d,%d,%d]\n", button, action, mode);

	for(auto observer : this->buttonCallbackObservers)
	{
		observer->mouseButtonPressedHandler(window, button, action, mode);
	}
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
	//float ratio = width / (float)height;
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



void Application::loadDefaultScene()
{
	//this->renderer->addObject(DrawableObjectFactory::createRotatingSquare());

	/*
	this->renderer->addObject(DrawableObjectFactory::createDefaultSphere());
	this->renderer->addObject(DrawableObjectFactory::createDefaultSmoothSuzi());
	this->renderer->addObject(DrawableObjectFactory::createDefaultFlatSuzi());

	this->renderer->addObject(DrawableObjectFactory::createObject(glm::vec3(0, 0, -2)));
	*/

	DrawableObject** arr = DrawableObjectFactory::create4SpheresWithLight();

	for(int i = 0; i < 4; i++)
	{
		this->renderer->addObject(arr[i]);
	}

	delete[] arr;

	Camera* camera = this->renderer->getCamera();
	camera->setPosition(glm::vec3(0,2,0));
	camera->setRotation(Rotation(0,180,0));
}



void Application::run()
{
	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(this->window))
	{
		this->renderer->renderNextFrame(this->window);

		glfwPollEvents();
	}
}



bool Application::registerKeyObserver(IKeyCallbackObserver *observer)
{
	return ObservedSubjectHelper::registerObserver(this->keyObservers, observer);
}

bool Application::registerCursorObserver(ICursorCallbackObserver *observer)
{
	return ObservedSubjectHelper::registerObserver(this->cursorObservers, observer);
}

bool Application::registerViewPortChangedObserver(IViewPortChangedObserver* observer)
{
	return ObservedSubjectHelper::registerObserver(this->windowSizeObservers, observer);
}

bool Application::registerButtonObserver(IMouseButtonObserver *observer)
{
	return ObservedSubjectHelper::registerObserver(this->buttonCallbackObservers, observer);
}



bool Application::unregisterKeyObserver(IKeyCallbackObserver *observer)
{
	return ObservedSubjectHelper::unregisterObserver(this->keyObservers, observer);
}

bool Application::unregisterCursorObserver(ICursorCallbackObserver *observer)
{
	return ObservedSubjectHelper::unregisterObserver(this->cursorObservers, observer);
}

bool Application::unregisterViewPortChangedObserver(IViewPortChangedObserver* observer)
{
	return ObservedSubjectHelper::unregisterObserver(this->windowSizeObservers, observer);
}

bool Application::unregisterButtonObserver(IMouseButtonObserver *observer)
{
	return ObservedSubjectHelper::unregisterObserver(this->buttonCallbackObservers, observer);
}
