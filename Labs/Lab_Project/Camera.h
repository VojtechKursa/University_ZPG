#pragma once

#include <glm/ext.hpp>

#include <vector>

#include "Rotation.h"

#include "Interfaces/ICursorCallbackObserver.h"
#include "Interfaces/IKeyCallbackObserver.h"
#include "Interfaces/IViewPortChangedObserver.h"
#include "Interfaces/IMouseButtonObserver.h"
#include "Interfaces/IFrameObserver.h"

#include "Interfaces/IViewMatrixChangedObserver.h"
#include "Interfaces/IProjectionMatrixChangedObserver.h"



class Camera : public ICursorCallbackObserver, public IKeyCallbackObserver, public IMouseButtonObserver, public IViewPortChangedObserver, public IFrameObserver
{
private:
	std::vector<IViewMatrixChangedObserver*> viewMatrixChangedObservers;
	std::vector<IProjectionMatrixChangedObserver*> projectionMatrixChangedObservers;

	glm::vec3 eyePosition;

	glm::vec3 target;
	glm::vec3 up;

	glm::vec3 motionVector;

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
	float movementSpeed;

	void calculateTarget();
	void calculateTarget(float alpha, float phi);

	void calculateViewMatrix();
	void calculateProjectionMatrix();

	void addAlpha(float change);
	void addPhi(float change);

	glm::vec3 getActualMotionVector();


public:
	Camera();
	Camera(glm::vec3 position);
	Camera(glm::vec3 position, float alpha, float phi);
	~Camera();

	glm::mat4 getViewMatrix();
	glm::mat4 getProjectionMatrix();

	bool setPosition(glm::vec3 position);
	bool setRotation(Rotation rotation);

	bool registerViewMatrixChangedObserver(IViewMatrixChangedObserver* observer);
	bool registerProjectionMatrixChangedObserver(IProjectionMatrixChangedObserver* observer);

	bool unregisterViewMatrixChangedObserver(IViewMatrixChangedObserver* observer);
	bool unregisterProjectionMatrixChangedObserver(IProjectionMatrixChangedObserver* observer);

	virtual void cursorMovedHandler(GLFWwindow* window, double x, double y) override;
	virtual void keyHandler(GLFWwindow* window, int key, int scancode, int action, int mods) override;
	virtual void mouseButtonPressedHandler(GLFWwindow* window, int button, int action, int mode) override;
	virtual void viewPortChangedHandler(int width, int height) override;
	virtual void frameHandler(double timeSinceLastFrameSec) override;
};
