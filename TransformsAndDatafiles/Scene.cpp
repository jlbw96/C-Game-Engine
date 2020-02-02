#include "Scene.h"

void Scene::update()
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects.at(i)->OnUpdate(0.0f);
	}
}

Scene::Scene()
{

}