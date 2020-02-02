#pragma once
#include "IEngineCore.h"
#include "InputHandler.h"
#include "GameObject.h"
#include "CameraComponent.h"
#include "PlayerCharacter.h"
#include "LoadComponent.h"
#include "Scene.h"
#include "json/json.h"
#include "LoadModels.h"
class Game
{
public:
	Game() {};
	virtual ~Game() {}
	IEngineCore* m_engineInterfacePtr;
	InputHandler* m_inputHandler;
	Scene* m_currentScene;
	LoadModels m_loadModels;
	int levelLoop = 0;

	virtual void update(float dt) = 0;
	virtual void render() = 0;

	std::vector<string> v_Levels;

	//void loadLevel(std::string levelFile);
	bool loadLevelJSON(std::string levelJSONFile);
private:
};
