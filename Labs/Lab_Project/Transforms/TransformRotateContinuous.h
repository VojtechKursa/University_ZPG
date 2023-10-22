#pragma once

#include "TransformComposite.h"
#include "TransformRotate.h"

#include "../Interfaces/IKeyCallbackObserver.h"



class TransformRotateContinuous : public TransformComposite, public IKeyCallbackObserver
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
    TransformRotateContinuous(Rotation rotationRates, char pauseKey = 0);

    virtual glm::mat4 getMatrix() override;

    //! \param pauseKey The char representing the new pause key
    void setPauseKey(char pauseKey);
    void unsetPauseKey();

    virtual void keyHandler(GLFWwindow* window, int key, int scancode, int action, int mods) override;
};

