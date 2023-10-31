#pragma once

#include "../Interfaces/ITransformContinuousable.h"
#include "Transform.h"

#include "../Interfaces/IObserver.h"



class TransformContinuous : public Transform, public IObserver
{
private:
    char pauseKey;
    bool pausable;

    bool paused;

    ITransformContinuousable* transform;
    glm::vec3 rate;

    void setCurrentTransform(float timeSinceLastFrameSec);

    void keyHandler(int key, int scancode, int action, int mods);
    void frameHandler(double timeSinceLastFrameSec);

public:
    TransformContinuous(ITransformContinuousable* transform, glm::vec3 rate, char pauseKey = 0);
    virtual ~TransformContinuous() override;

    virtual glm::mat4 getMatrix() override;

    //! \param pauseKey The char representing the new pause key
    void setPauseKey(char pauseKey);
    void unsetPauseKey();

    virtual void notify(const Event* event) override;
};

