#pragma once

#include <glm/ext.hpp>

#include <vector>

#include "IViewMatrixChangedObserver.h"
#include "IProjectionMatrixChangedObserver.h"
#include "ICursorCallbackObserver.h"
#include "IKeyCallbackObserver.h"



class ShaderProgram;

class Camera : public ICursorCallbackObserver, public IKeyCallbackObserver				// will be subject in Observer pattern, Observed by ?ShaderProgram?
{
private:
	std::vector<IViewMatrixChangedObserver*> viewMatrixChangedObservers;
	std::vector<IProjectionMatrixChangedObserver*> projectionMatrixChangedObservers;

	glm::vec3 target;
	glm::vec3 up;

	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;

	float alpha;
	float phi;

	float fov;			// fov of the camera, in degrees
	float viewRatio;
	float displayRangeMin;
	float displayRangeMax;

	void calculateTarget();
	void calculateTarget(float alpha, float phi);

	void calculateViewMatrix();
	void calculateProjectionMatrix();


public:
	glm::vec3 eyePosition;

	Camera();
	Camera(glm::vec3 position);
	Camera(glm::vec3 position, float alpha, float phi);

	bool setPhi(float phi);
	bool setAlpha(float alpha);
	bool setFov(float fov);
	bool setViewRatio(float viewRatio);
	bool setDisplayRange(float min, float max);

	float getPhi();
	float getAlpha();

	glm::mat4 getViewMatrix();
	glm::mat4 getProjectionMatrix();

	void registerViewMatrixChangedObserver(IViewMatrixChangedObserver* observer);
	void registerProjectionMatrixChangedObserver(IProjectionMatrixChangedObserver* observer);

	virtual void cursor_callback(GLFWwindow* window, double x, double y) override;
	virtual void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) override;
};
