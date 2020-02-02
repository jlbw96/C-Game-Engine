#include "AwesomeGame.h"


AwesomeGame::AwesomeGame() {
	//sets pointer to null 
	m_engineInterfacePtr = nullptr;
	//loads level from text file
	LoadLevel("assets/levels/Levels.txt");
	//loads the json level from the loop
	loadLevelJSON(v_Levels.at(levelLoop));
	//increments the loop int
	levelLoop++;
	//adds the load component to the game object in the cuurent scene
	m_currentScene->gameObjects.at(0)->addComponent(new LoadComponent);
}

void AwesomeGame::LoadLevel(std::string filepath)
{
	std::ifstream myInputFile;
	myInputFile.open(filepath, std::ios_base::in);

	int numLevels;
	stringstream ss;
	string s;
	//std::vector<int> inVector;
	if (myInputFile.is_open())
	{
		// read the first line which has the number of elements
		getline(myInputFile, s);
		ss.str(s);
		ss.ignore(18); // ignore the first 18 chars
		ss >> numLevels;
		ss.clear();


		for (int i = 0; i < numLevels; i++) {
			
			getline(myInputFile, s);
			ss.clear();
			ss >> s;
			std::cout << s << std::endl;
			addLevel(s);

		}
	}
}

void AwesomeGame::addLevel(string level)
{
	//pushes back the level in the levels vector
	v_Levels.push_back(level);
}


void AwesomeGame::update(float dt) {


	string m;
	//while i < thane the gameobjects vector size then get load component for each gameobject
	for (int i = 0; i < m_currentScene->gameObjects.size(); i++) {
		if (m_currentScene->gameObjects.at(i)->getComponent<LoadComponent>()) {
			m = m_currentScene->gameObjects.at(i)->getComponent<LoadComponent>()->getMsg();
			if (m == "SwitchScene") {
				//set input to null
				m_inputHandler = nullptr;
				//points to the scene deconstructor
				m_currentScene->~Scene();
				// loads the json from the vector at the levelloop
				loadLevelJSON(v_Levels.at(levelLoop));
				//increments levelloop
				levelLoop++;

				//if loop = the size of vector
				if (levelLoop == v_Levels.size()) {
					//loop = 0;
					levelLoop = 0;
				}
				//adds the load component
				m_currentScene->gameObjects.at(0)->addComponent(new LoadComponent);
			}

		}

	}
	//updates current scene
	m_currentScene->update();

}
void AwesomeGame::render() {
	//renders background
	m_engineInterfacePtr->renderColouredBackground(0, 0, 0);

	// update the camera (probably don't need to do this each frame)
	m_engineInterfacePtr->setCamera(m_currentScene->m_camera);

	//draws the models form the gameobjects vector 
	for (int i = 0; i < m_currentScene->gameObjects.size(); i++)
	{
		m_engineInterfacePtr->drawModel(
			m_currentScene->gameObjects.at(i)->getComponent<ModelComponent>()->getModel(),
			m_currentScene->gameObjects.at(i)->getComponent<TransformComponent>()->getModelMatrix());
	}
}
bool AwesomeGame::loadLevelJSON(std::string levelJSONFile) {
	std::fstream jsonData;
	Json::Value root;
	Json::Reader reader;

	//if (m_currentScene)
	m_currentScene = new Scene;
	jsonData.open(levelJSONFile.c_str());
	// check for errors
	if (!reader.parse(jsonData, root)) {
		std::cout << "Failed to parse data from: " << levelJSONFile << reader.getFormattedErrorMessages();
		return false;
	}

	const Json::Value gameObjects = root["GameObjects"];
	// size() tells us how large the array is
	for (int i = 0; i < gameObjects.size(); i++) {
		GameObject* object;
		// Type
		string type = gameObjects[i]["type"].asString();
		if (type == "PlayerCharacter")
		{
			object = new PlayerCharacter;
			m_currentScene->m_camera = object->getComponent<CameraComponent>();
			m_inputHandler = new InputHandler(object);
			cout << "Player Character Set" << endl;
		}
		else if (type == "StaticEnvironmentObject")
		{
			object = new StaticEnvironmentObject;
			cout << "static set" << endl;
		}

		else if (type == "RotatingEnvironmentObject")
		{
			object = new RotatingEnvironmentObject;
			cout << "Rotating set" << endl;
		}

		else if (type == "MovingEnvironmentObject")
		{
			object = new MovingEnvironmentObject;
			cout << "Rotating set" << endl;
		}
		else
		{
			std::cout << type << ": unknown type\n";
			continue; // not an object we can create
		}
		std::cout << gameObjects[i]["name"].asString() << " -" << type << " loaded\n";
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
		// check if the node exists 
		if (orientNode.type() != Json::nullValue)
		{
		}
		else
		{
			orientation = glm::quat(1, 0, 0, 0);
			cout << "Error finding orientation: Default value given." << endl;
		}

		const Json::Value scaleNode = gameObjects[i]["scale"];
		scale.x = scaleNode[0].asFloat();
		scale.y = scaleNode[1].asFloat();
		scale.z = scaleNode[2].asFloat();
		// check if the scale node exists 
		if (scaleNode.type() != Json::nullValue)
		{
		}
		else
		{
			scale = glm::vec3(0.1, 0.1, 0.1);
			cout << "Error finding scale: Default value given." << endl;
		}



		cout << "Scale: [" << scale.x << ", " << scale.y << ", " << scale.z << "]" << endl;
		cout << "Orientation: [" << orientation.x << ", " << orientation.y << ", " << orientation.z << ", " << orientation.w << "]" << endl;
		cout << "Pos: " << posNode << endl;
		object->addComponent(new TransformComponent(pos, orientation, scale));

		const Json::Value pathNode = gameObjects[i]["path"];
		if (pathNode.type() != Json::nullValue)
		{
			object->addComponent(new ModelComponent(m_loadModels.addModel(pathNode.asString())));
		}
		else
		{
			std::cout << type << ": unknown Model\n";
			continue; // not an object we can create
			//object->addComponent(new ModelComponent(m_loadModels.addModel(pathNode.asString())));
			//cout << "Error finding object: This will throw exception." << endl;
		}
		m_currentScene->gameObjects.push_back(object);
	}
	cout << "Camera" << endl;
	cout << "Orientation: [" << m_currentScene->m_camera->m_orientation.w << ", " << m_currentScene->m_camera->m_orientation.x << ", " << m_currentScene->m_camera->m_orientation.y << ", " << m_currentScene->m_camera->m_orientation.z <<  "]" << endl;
	cout << "Pos: [" << m_currentScene->m_camera->m_position.x << ", " << m_currentScene->m_camera->m_position.y << ", " << m_currentScene->m_camera->m_position.z << "]" << endl;
	cout << "FOV: [" << m_currentScene->m_camera->m_fov << "]" << endl;
}

