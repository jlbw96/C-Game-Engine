#include "Scene.h"
#include "BaseGame.h"
#include "StaticEnvironmentObject.h"
#include <fstream>
#include <sstream>
#include <vector>
#include "json/json.h"
#include "ModelComponent.h"
#include "TransformComponent.h"
#include "cameraComponent.h"
#include "StaticEnvironmentObject.h"
#include "PlayerCharacter.h"

using namespace std;
vector <int> g_inVector;
int numElementsToRead;
stringstream ss;
string s;

Game::Game()
{
	m_engineInterfacePtr = nullptr;
	m_inputHandler = new InputHandler(&m_playerCube);
	loadLevelJSON("assets/levels/myCubeLevel.json");
}


bool Game::loadLevelJSON(std::string levelJSONFile) {
	std::fstream jsonData;
	Json::Value root;
	Json::Reader reader;

	jsonData.open(levelJSONFile.c_str());
	Model* myTestModel = new Model("assets/models/Cube1.3ds");
	// check for errors
	if (!reader.parse(jsonData, root)) {
		std::cout << "Failed to parse data from: " << levelJSONFile << reader.getFormattedErrorMessages();
		return false;
	}

	const Json::Value gameObjects = root["GameObjects"];
	// size() tells us how large the array is
	for (int i = 0; i < gameObjects.size(); i++) {
		// get string 
		GameObject object = GameObject();
		std::cout << gameObjects[i]["name"].asString() << " loaded\n";
		string type = gameObjects[i]["type"].asString();
		if (type == "PlayerCharacter")
		{
			m_currentScene->v_gameObjects.push_back(new PlayerCharacter());
			m_currentScene->m_camera = m_currentScene->v_gameObjects[i]->getComponent<CameraComponent>();
			m_inputHandler.v_objectsRequiringInput.push_back(m_currentScene->v_gameObjects[i]);
		}
		else if (type == "StaticEnvironmentObject")
		{
			m_currentScene->v_gameObjects.push_back(new StaticEnvironmentObject());
		}
		else
		{
			std::cout << type << ": unknown type\n";
			continue; // not an object we can create
		}
		std::cout << gameObjects[i]["name"].asString() << "-" << type << " loaded\n";
		glm::vec3 scale;
		glm::quat orientation;
		glm::vec3 pos;
		const Json::Value posNode = gameObjects[i]["position"];
		pos.x = posNode[0].asFloat();
		pos.y = posNode[1].asFloat();
		pos.z = posNode[2].asFloat();
		const Json::Value orientNode = gameObjects[i]["orientation"];
		orientation.x = orientNode[0].asFloat();
		orientation.y = orientNode[1].asFloat();
		orientation.z = orientNode[2].asFloat();
		orientation.w = orientNode[3].asFloat();

		const Json::Value scaleNode = gameObjects[i]["scale"];
		scale.x = scaleNode[0].asFloat();
		scale.y = scaleNode[1].asFloat();
		scale.z = scaleNode[2].asFloat();

		// check if the node exists 
		if (orientNode.type() != Json::nullValue)
		{
		}
		else
		{
			orientation = glm::quat(1, 0, 0, 0);
		}

		// check if the node exists 
		if (scaleNode.type() != Json::nullValue)
		{
		}
		else
		{
			scale = glm::vec3(1, 1, 1);
		}
		cout << "Scale: [" << scale.x << ", " << scale.y << ", " << scale.z << "]" << endl;
		cout << "Orientation: [" << orientation.x << ", " << orientation.y << ", " << orientation.z << ", " << orientation.w << "]" << endl;
		cout << "Pos: " << posNode << endl;
		object.addComponent(new TransformComponent(pos, orientation, scale));
		object.addComponent(new ModelComponent(myTestModel));
		m_currentScene->gameObjects.push_back(object);
	}
	cout << "Camera (Position): [" << m_camera.m_position.x << ", " << m_camera.m_position.y << ", " << m_camera.m_position.z << "]" << endl;
	cout << "Camera (Orientation): [" << m_camera.m_orientation.x << ", " << m_camera.m_orientation.y << ", " << m_camera.m_orientation.z << ", " << m_camera.m_orientation.w << "]" << endl;
	cout << "Camera (Fov): [" << m_camera.m_fov << "]" << endl;
}


void Game::render()
{

	m_engineInterfacePtr->renderColouredBackground(0, 0, 0);

	// update the camera (probably don't need to do this each frame)
	m_engineInterfacePtr->setCamera(&m_camera);

	for (int i = 0; i < m_currentScene->gameObjects.size(); i++)
	{
		m_engineInterfacePtr->drawModel(
			m_currentScene->gameObjects.at(i).getComponent<ModelComponent>()->getModel(),
			m_currentScene->gameObjects.at(i).getComponent<TransformComponent>()->getModelMatrix());
	}
}
