#pragma once
#include "GameObject.h"
class MovingEnvironmentObject : public GameObject
{
public:
	MovingEnvironmentObject();
	~MovingEnvironmentObject();
	void OnUpdate(float dt) override;
	void OnMessage(const std::string msg) override;

	float movementX = 0.5f, movementY, movementZ = 0.5f;
	bool forward = true;
};
