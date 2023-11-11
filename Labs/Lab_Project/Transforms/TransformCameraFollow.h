#pragma once

#include "TransformTranslate.h"

#include "../Camera.h"

#include "../Interfaces/IObserver.h"



class TransformCameraFollow : public TransformTranslate, public IObserver
{
private:
    Camera* camera;

public:
    TransformCameraFollow(Camera* camera);
    virtual ~TransformCameraFollow() override;

    virtual void notify(const Event* event) override;
};