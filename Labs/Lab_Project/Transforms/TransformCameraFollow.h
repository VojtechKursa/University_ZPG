#pragma once

#include "TransformTranslate.h"

#include "../Camera.h"

#include "../Interfaces/IObserver.h"
#include "../Events/KeyEventData.h"



class TransformCameraFollow : public TransformTranslate, public IObserver
{
private:
    Camera* camera;
    bool following = true;

    void keyHandler(const KeyEventData* eventData);
    void updatePos();

public:
    TransformCameraFollow(Camera* camera);
    virtual ~TransformCameraFollow() override;

    virtual void notify(const Event* event) override;
};