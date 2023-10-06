#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <vector>

#include "Renderer.h"
#include "IKeyCallbackListener.h"
#include "ICursorCallbackListener.h"



class Application
{
private:
	static Application instance;

	GLFWwindow* window;
	Renderer* renderer;

	static void error_callback(int error, const char* description);
	static void key_callback_static(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void window_focus_callback_static(GLFWwindow* window, int focused);
	static void window_iconify_callback_static(GLFWwindow* window, int iconified);
	static void window_size_callback_static(GLFWwindow* window, int width, int height);
	static void cursor_callback_static(GLFWwindow* window, double x, double y);
	static void button_callback_static(GLFWwindow* window, int button, int action, int mode);

	void bindCallbacks();

	std::vector<IKeyCallbackListener*> keyListeners;
	std::vector<ICursorCallbackListener*> cursorListeners;

	Application();

public:
	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	void window_focus_callback(GLFWwindow* window, int focused);
	void window_iconify_callback(GLFWwindow* window, int iconified);
	void window_size_callback(GLFWwindow* window, int width, int height);
	void cursor_callback(GLFWwindow* window, double x, double y);
	void button_callback(GLFWwindow* window, int button, int action, int mode);

	~Application();

	static Application getInstance();

	void init();
	void terminate();

	void createWindow(int width = 800, int height = 800, const char* title = "ZPG", GLFWmonitor* monitor = nullptr, GLFWwindow* share = nullptr);
	void destroyWindow();

	void printVersionInfo();

	void loadDefaultScene();

	void run();

	void registerKeyListener(IKeyCallbackListener* listener);
	void registerCursorListener(ICursorCallbackListener* listener);

	void unregisterKeyListener(IKeyCallbackListener* listener);
	void unregisterCursorListener(ICursorCallbackListener* listener);
};

