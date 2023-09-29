#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Renderer.h"



class Application
{
private:
	GLFWwindow* window;
	Renderer* renderer;

	static void error_callback(int error, const char* description);
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void window_focus_callback(GLFWwindow* window, int focused);
	static void window_iconify_callback(GLFWwindow* window, int iconified);
	static void window_size_callback(GLFWwindow* window, int width, int height);
	static void cursor_callback(GLFWwindow* window, double x, double y);
	static void button_callback(GLFWwindow* window, int button, int action, int mode);

	void bindCallbacks();

public:
	Application();
	~Application();

	void init();
	void terminate();

	void createWindow(int width = 800, int height = 600, const char* title = "ZPG", GLFWmonitor* monitor = nullptr, GLFWwindow* share = nullptr);
	void destroyWindow();

	void printVersionInfo();

	void loadDefaultScene();

	void run();
};

