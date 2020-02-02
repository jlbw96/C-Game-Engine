#pragma once
#include "IEngineCore.h"
#include "InputHandler.h"
#include "Scene.h"
#include "CameraComponent.h"

class Game
{
public:

	Game();
	virtual ~Game() {}
	IEngineCore* m_engineInterfacePtr;
	InputHandler* m_inputHandler;
	Scene* m_currentScene;	CameraComponent* m_camera;
	virtual void update(float dt) = 0;
	virtual void render() = 0;

	bool loadLevelJSON(std::string levelJSONFile);
	std::vector<GameObject> v_gameObjects;
};