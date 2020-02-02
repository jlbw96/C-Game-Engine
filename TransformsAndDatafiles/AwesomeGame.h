#pragma once
#include <string>
#include <sstream>
#include <iostream>
#include "Game.h"
#include "MovingEnvironmentObject.h"
#include "RotatingEnvironmentObject.h"
#include "StaticEnvironmentObject.h"
#include "PlayerCharacter.h"
#include "LoadModels.h"

class AwesomeGame : public Game
{
public:
	AwesomeGame();
	void update(float dt) override;
	void render() override;
	bool loadLevelJSON(std::string levelJSONFile);
	int rotateValue = 90;
	void LoadLevel(string filepath);
	void addLevel(string level);
};
