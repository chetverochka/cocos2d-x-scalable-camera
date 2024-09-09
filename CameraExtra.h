#pragma once

#include "cocos2d.h"

using namespace cocos2d;

class CameraExtra : public Camera {
protected:

	float FOV;
	float ratio;
	float nearP;
	float farP;

	float farP_K; // factor

	bool init() {
		FOV = 60.f;
		ratio = Director::getInstance()->getVisibleSize().width / Director::getInstance()->getVisibleSize().height;
		nearP = 0.f;
		farP = 1000.f;
		farP_K = 1.f;

		if (!initPerspective(FOV, ratio, nearP, farP * farP_K))	return false;
		return true;
	}
public:
	static CameraExtra* create() {
		CameraExtra* camera = new (std::nothrow) CameraExtra();
		if (camera && camera->init()) {
			camera->autorelease();
			return camera;
		}

		CC_SAFE_DELETE(camera);
		return nullptr;
	}

	void reset() {
		initPerspective(FOV, ratio, nearP, farP * farP_K);
	}

	void setFarPlaneK(int k) {
		farP_K = k;
		reset();
	}
	void setFOV(float fieldOfView) {
		FOV = fieldOfView;
		reset();
	}
	void setScale(float k) override {
		Camera::setPositionZ((farP * farP_K / 2) * k);
	}
};
