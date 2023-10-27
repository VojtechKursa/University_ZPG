#pragma once

#include "../Interfaces/IKeyCallbackObserver.h"
#include "../Interfaces/IFrameObserver.h"
#include "../Interfaces/ITransformContinuousable.h"
#include "Transform.h"



class TransformContinuous : public Transform, public IKeyCallbackObserver, public IFrameObserver
{
private:
    char pauseKey;
    bool pausable;

    bool paused;

    ITransformContinuousable* transform;
    glm::vec3 rate;

    void setCurrentTransform(float timeSinceLastFrameSec);

public:
    TransformContinuous(ITransformContinuousable* transform, glm::vec3 rate, char pauseKey = 0);
    virtual ~TransformContinuous() override;

    virtual glm::mat4 getMatrix() override;

    //! \param pauseKey The char representing the new pause key
    void setPauseKey(char pauseKey);
    void unsetPauseKey();

    virtual void keyHandler(GLFWwindow* window, int key, int scancode, int action, int mods) override;
    virtual void frameHandler(double timeSinceLastFrameSec) override;
};

