#pragma once
#include "GameObject.h"
class StaticEnvironmentObject : public GameObject
{
public:
	StaticEnvironmentObject();
	~StaticEnvironmentObject();
	void OnUpdate(float dt) override;
	void OnMessage(const std::string msg) override;
};