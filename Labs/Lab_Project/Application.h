#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <vector>

#include "Renderer.h"
#include "Interfaces/IKeyCallbackObserver.h"
#include "Interfaces/ICursorCallbackObserver.h"
#include "Interfaces/IViewPortChangedObserver.h"
#include "Interfaces/IMouseButtonObserver.h"
#include "Interfaces/IFrameObserver.h"



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

	std::vector<IKeyCallbackObserver*> keyObservers;
	std::vector<ICursorCallbackObserver*> cursorObservers;
	std::vector<IViewPortChangedObserver*> windowSizeObservers;
	std::vector<IMouseButtonObserver*> buttonCallbackObservers;
	std::vector<IFrameObserver*> frameObservers;

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

	void printVersionInfo();

	void loadDefaultScene();

	void run();

	bool registerKeyObserver(IKeyCallbackObserver* observer);
	bool registerCursorObserver(ICursorCallbackObserver* observer);
	bool registerViewPortChangedObserver(IViewPortChangedObserver* observer);
	bool registerButtonObserver(IMouseButtonObserver* observer);
	bool registerFrameObserver(IFrameObserver* observer);

	bool unregisterKeyObserver(IKeyCallbackObserver* observer);
	bool unregisterCursorObserver(ICursorCallbackObserver* observer);
	bool unregisterViewPortChangedObserver(IViewPortChangedObserver* observer);
	bool unregisterButtonObserver(IMouseButtonObserver* observer);
	bool unregisterFrameObserver(IFrameObserver* observer);
};

