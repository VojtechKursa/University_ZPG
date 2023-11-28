#include "TransformTranslateBezier.h"

#include "../Events/FrameEventData.h"



TransformTranslateBezier::TransformTranslateBezier()
	: bezier(BezierCurve()), tSpeed(0.5f), overflow(OVERFLOW_REVERSE)
{ }

TransformTranslateBezier::TransformTranslateBezier(BezierCurve bezier, float tSpeed, BezierOverflowBehaviour overflowBehaviour)
	: bezier(bezier), tSpeed(tSpeed == -1 ? (1 / static_cast<double>(bezier.getCubicsCount())) / 2.0 : tSpeed), overflow(overflowBehaviour)
{

	Application::getInstance()->registerObserver(this);
}

TransformTranslateBezier::~TransformTranslateBezier()
{
	Application::getInstance()->unregisterObserver(this);
}



void TransformTranslateBezier::notify(const Event* event)
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

			this->translationVector = this->bezier.getPoint(t);

			break;
	}
}
