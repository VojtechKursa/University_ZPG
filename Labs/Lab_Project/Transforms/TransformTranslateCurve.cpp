#include "TransformTranslateCurve.h"

#include "../Events/FrameEventData.h"

#include "../Curves/BezierCurve.h"



TransformTranslateCurve::TransformTranslateCurve()
	: curve(new BezierCurve()), tSpeed(0.5f), overflow(OVERFLOW_REVERSE)
{ }

TransformTranslateCurve::TransformTranslateCurve(ICurve* curve, float tSpeed, CurveOverflowBehaviour overflowBehaviour)
	: curve(curve), tSpeed(tSpeed == -1 ? (1 / static_cast<double>(curve->getSegmentCount())) / 2.0 : tSpeed), overflow(overflowBehaviour)
{
	Application::getInstance()->registerObserver(this);
}

TransformTranslateCurve::~TransformTranslateCurve()
{
	if(curve != nullptr)
	{
		delete curve;
		curve = nullptr;
	}

	Application::getInstance()->unregisterObserver(this);
}



void TransformTranslateCurve::notify(const Event* event)
{
	switch (event->eventType)
	{
		case EVENT_FRAME:
			t += static_cast<float>(static_cast<const FrameEventData*>(event->data)->timeSinceLastFrameSec * tSpeed * directionModifier);
			if (t < 0 || t > 1)
			{
				switch (overflow)
				{
					case OVERFLOW_RESET:
						t = 0;
						break;
					case OVERFLOW_REVERSE:
						directionModifier = -(directionModifier);
						if (t > 1)
							t -= t - 1;
						else
							t = abs(t);
						break;
				}
			}

			this->translationVector = this->curve->getPoint(t);

			break;
	}
}
