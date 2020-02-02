#pragma once

#include "Component.h"
#include "Model.h"
#include <string>
#include <glm/glm.hpp>

class ModelComponent : public Component
{
private:
	Model* model;
public:
	ModelComponent() {};
	ModelComponent(Model* modelIn) { model = modelIn; };

	void OnUpdate(float dt)  override {};
	void OnMessage(const std::string m) override{};

	Model* getModel() { return model; };

};