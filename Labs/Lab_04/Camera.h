#pragma once

#include <glm/ext.hpp>

#include <vector>

#include "ICursorCallbackObserver.h"
#include "IKeyCallbackObserver.h"
#include "IViewPortChangedObserver.h"
#include "IMouseButtonObserver.h"

#include "IViewMatrixChangedObserver.h"
#include "IProjectionMatrixChangedObserver.h"



// will be subject in Observer pattern, Observed by ?ShaderProgram?
class Camera : public ICursorCallbackObserver, public IKeyCallbackObserver, public IMouseButtonObserver, public IViewPortChangedObserver
{
private:
	std::vector<IViewMatrixChangedObserver*> viewMatrixChangedObservers;
	std::vector<IProjectionMatrixChangedObserver*> projectionMatrixChangedObservers;

	glm::vec3 target;
	glm::vec3 up;

	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;

	float alpha;	// Elevation (0° - up, 90° - level, 180° - down)
	float phi;		// Azimuth (0° - 360°, 0° - Towards +X, 90° - Towards +Z)

	float fov;			// fov of the camera, in degrees
	float viewRatio;
	float displayRangeMin;
	float displayRangeMax;

	bool mouseButtonHeld;
	bool firstCursorEvent;
	int lastCursorPoint[2];
	
	float mouseSensitivity[2];
	float movementSensitivity;

	void calculateTarget();
	void calculateTarget(float alpha, float phi);

	void calculateViewMatrix();
	void calculateProjectionMatrix();

	void addAlpha(float change);
	void addPhi(float change);


public:
	glm::vec3 eyePosition;

	Camera();
	Camera(glm::vec3 position);
	Camera(glm::vec3 position, float alpha, float phi);
	~Camera();

	glm::mat4 getViewMatrix();
	glm::mat4 getProjectionMatrix();

	bool registerViewMatrixChangedObserver(IViewMatrixChangedObserver* observer);
	bool registerProjectionMatrixChangedObserver(IProjectionMatrixChangedObserver* observer);

	bool unregisterViewMatrixChangedObserver(IViewMatrixChangedObserver* observer);
	bool unregisterProjectionMatrixChangedObserver(IProjectionMatrixChangedObserver* observer);

	virtual void cursorMovedHandler(GLFWwindow* window, double x, double y) override;
	virtual void keyHandler(GLFWwindow* window, int key, int scancode, int action, int mods) override;
	virtual void mouseButtonPressedHandler(GLFWwindow* window, int button, int action, int mode) override;
	virtual void viewPortChangedHandler(int width, int height) override;
};
