#include "StaticEnvironmentObject.h"
#include "TransformComponent.h"
#include "ModelComponent.h"

using namespace std;

StaticEnvironmentObject::StaticEnvironmentObject()
{
	addComponent(new TransformComponent);
	addComponent(new ModelComponent);
}



void StaticEnvironmentObject::OnUpdate(float dt)
{

}

void StaticEnvironmentObject::OnMessage(const std::string msg)
{

}