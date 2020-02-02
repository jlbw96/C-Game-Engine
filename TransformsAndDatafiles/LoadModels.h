#pragma once
#include "Model.h"
#include "vector"

using namespace std;

class LoadModels
{
public:
	Model* addModel(string modelFilePath) {
		for (int i = 0; i < modelLoaded.size(); i++) {
			if (modelFilePath == modelLoaded.at(i)->getPath()) {
				return modelLoaded.at(i);
			}
		}


		Model* newModel = new Model(modelFilePath);
		modelLoaded.push_back(newModel);
		return modelLoaded.at(modelLoaded.size() - 1);
	}

private:
	vector<Model*> modelLoaded;

};