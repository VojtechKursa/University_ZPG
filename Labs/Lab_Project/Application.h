#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Renderer.h"
#include "Subject.h"
#include "DrawableObject.h"

#include "ObjectProperties.h"



class Application : public Subject
{
private:
	static Application instance;

	GLFWwindow* window;
	Renderer* renderer;

	DrawableObject* selectedObject = nullptr;
	double lastCursorPosition[2];

	ObjectProperties placeObjectProperties;
	bool placeObjectPropertiesInitialized = false;
	void initPlaceObjectProperties();

	bool placingBezier = false;
	std::vector<glm::vec3> bezierPositions;

	static void error_callback(int error, const char* description);
	static void key_callback_static(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void window_focus_callback_static(GLFWwindow* window, int focused);
	static void window_iconify_callback_static(GLFWwindow* window, int iconified);
	static void window_size_callback_static(GLFWwindow* window, int width, int height);
	static void cursor_callback_static(GLFWwindow* window, double x, double y);
	static void button_callback_static(GLFWwindow* window, int button, int action, int mode);

	void bindCallbacks();

	void notifyFrameObservers(double timeSinceLastFrameSec);

	Application();

public:
	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	void window_focus_callback(GLFWwindow* window, int focused);
	void window_iconify_callback(GLFWwindow* window, int iconified);
	void window_size_callback(GLFWwindow* window, int width, int height);
	void cursor_callback(GLFWwindow* window, double x, double y);
	void button_callback(GLFWwindow* window, int button, int action, int mode);

	~Application();

	static Application* getInstance();

	Renderer* getRenderer();

	void init();
	void terminate();

	void createWindow(int width = 800, int height = 600, const char* title = "ZPG", GLFWmonitor* monitor = nullptr, GLFWwindow* share = nullptr);
	void destroyWindow();
	void setWindowSize(int width, int height);

	void printVersionInfo();

	void loadDefaultScene(const char* scene = nullptr);

	void run();
};

