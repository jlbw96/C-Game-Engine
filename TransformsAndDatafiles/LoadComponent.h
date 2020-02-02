#pragma once
#include "Component.h"


class LoadComponent : public Component
{
public:
	LoadComponent() {};

	void OnUpdate(float dt) override
	{

	}
	void OnMessage(const std::string m) override
	{
		if (m == "SwitchScene")
		{
			msg = m;
		}
	}

	std::string getMsg() { return msg; }
private:
	std::string msg;

};