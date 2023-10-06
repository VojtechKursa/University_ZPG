#pragma once

#include "Transform.h"
#include "TransformRotate.h"
#include "IKeyCallbackListener.h"



class TransformRotateContinuous : public Transform, public IKeyCallbackListener
{
private:
    char pauseKey;
    bool pausable;

    bool paused;
    float lastTick;

    TransformRotate* rotateTransform;

    void setCurrentRotation();

public:
    Rotation rates;

    TransformRotateContinuous();
    TransformRotateContinuous(Rotation rotationRates, char* pauseKey = nullptr);

    virtual glm::mat4 getMatrix() override;

    //! \param pauseKey The pointer to a char representing the new pause key or nullptr to unset the pause key.
    void setPauseKey(char* pauseKey = nullptr);

    virtual void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) override;
};

