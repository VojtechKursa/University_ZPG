#pragma once

#include <glm/ext.hpp>

#include <vector>

#include "Subject.h"
#include "Rotation.h"



class LightSpot;



class Camera : public Subject, public IObserver
{
private:
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

	bool cameraRotationEnabled;
	bool firstCursorEvent;
	int lastCursorPoint[2];
	
	float mouseSensitivity[2];
	float movementSpeed;

	bool flying;

	LightSpot* flashlight;

	void calculateTarget();
	void calculateTarget(float alpha, float phi);

	void calculateViewMatrix();
	void calculateProjectionMatrix();

	void addAlpha(float change);
	void addPhi(float change);

	glm::vec3 getActualMotionVector();

	void cursorMovedHandler(double x, double y);
	void keyHandler(int key, int scancode, int action, int mods);
	void mouseButtonHandler(int button, int action, int mode);
	void viewPortChangedHandler(int width, int height);
	void frameHandler(double timeSinceLastFrameSec);

	// Call only after recalculating target (which is also part of calculateViewMatrix())
	void updateFlashlightRotation();
	// Call only after recalculating target (which is also part of calculateViewMatrix())
	void updateFlashlightPosition();


public:
	Camera();
	Camera(glm::vec3 position);
	Camera(glm::vec3 position, float alpha, float phi);
	~Camera();

	glm::mat4 getViewMatrix();
	glm::mat4 getProjectionMatrix();

	glm::vec3 getPosition();
	bool setPosition(glm::vec3 position);
	Rotation getRotation();
	bool setRotation(Rotation rotation);

	LightSpot* getFlashlight();
	bool addFlashlight(float foi = -1, glm::vec3 lightColor = glm::vec3(1,1,1));

	bool setFlying(bool flying);
	bool getFlying();

	virtual void notify(const Event* event) override;
};
