#pragma once
#include <map>
#include "GameObject.h"
#include <vector>
#include "TransformComponent.h"
#include "LoadComponent.h"

class InputCommand
{
public:
	virtual ~InputCommand() {}
	virtual void execute(GameObject& playerBackground) = 0;
};

//e.g. class RotateLeftCommand : public InputCommand
class RotateCameraLeftCommand : public InputCommand
{
public:
	void execute(GameObject& gameObject) override
	{
		gameObject.OnMessage("rotateCameraLeft");
	}
};

class RotateCameraRightCommand : public InputCommand
{
public:
	void execute(GameObject& gameObject) override
	{
		gameObject.OnMessage("rotateCameraRight");
	}
};

class TranslateCameraForwardCommand : public InputCommand
{
public:
	void execute(GameObject& gameObject) override
	{
		gameObject.OnMessage("movePlayerForward");

	}
};

class TranslateCameraBackwardCommand : public InputCommand
{
public:
	void execute(GameObject& gameObject) override
	{
		gameObject.OnMessage("movePlayerBackward");
	}
};

class FirstViewCommand : public InputCommand
{
public:
	void execute(GameObject& gameObject) override
	{
			gameObject.OnMessage("SetCameraFirstPerson");
	}
};

class ThirdViewCommand : public InputCommand
{
public:
	void execute(GameObject& gameObject) override
	{
		gameObject.OnMessage("SetCameraThirdPerson");
	}
};

class SwitchSceneCommand : public InputCommand
{
public:
	void execute(GameObject& gameObject) override
	{
	if (gameObject.getComponent<LoadComponent>())
		gameObject.getComponent<LoadComponent>()->OnMessage("SwitchScene");
}
};

struct InputHandler
{	
	GameObject* objectPlayer;

	std::map<int, InputCommand*> m_controlMapping;

	InputHandler(GameObject* playerCube) : objectPlayer(playerCube)
	{
		// the idea will be to map the keys directly from a config file that can be loaded in
		// and changed on the fly
		m_controlMapping[65] =  new RotateCameraLeftCommand;
		m_controlMapping[68] = new RotateCameraRightCommand;
		m_controlMapping[87] = new TranslateCameraForwardCommand;
		m_controlMapping[83] = new TranslateCameraBackwardCommand;
		m_controlMapping[89] = new FirstViewCommand;
		m_controlMapping[84] = new ThirdViewCommand;
		m_controlMapping[85] = new SwitchSceneCommand;
	}

	void handleInputs(const std::vector<bool>& keyBuffer)
	{
		for(const auto& mapEntry : m_controlMapping)
		{
			if(keyBuffer[mapEntry.first])
			{
				mapEntry.second->execute(*objectPlayer);
			}
		}

	}
};
