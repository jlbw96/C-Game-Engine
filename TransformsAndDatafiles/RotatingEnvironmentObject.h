#pragma once
#include "GameObject.h"
class RotatingEnvironmentObject : public GameObject
{
public:
	RotatingEnvironmentObject();
	~RotatingEnvironmentObject();
	void OnUpdate(float dt) override;
	void OnMessage(const std::string msg) override;

	float rotation = 0.8f;
};
