#pragma once
#include "IEngineCore.h"
#include "InputHandler.h"
#include "GameObject.h"
#include "CameraComponent.h"
#include "RotatingEnvironmentObject.h"

class Scene
{
public:
	Scene();
	void render(IEngineCore* engineInterfacePtr);
	std::vector<GameObject> v_playerCubes;
	std::vector<GameObject*> gameObjects;
	//GameObject m_playerBackground;
	CameraComponent* m_camera;
	
	void update();
private:
};