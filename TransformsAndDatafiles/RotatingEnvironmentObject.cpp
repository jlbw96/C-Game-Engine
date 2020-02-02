#include "RotatingEnvironmentObject.h"
#include "TransformComponent.h"
#include "ModelComponent.h"

using namespace std;

RotatingEnvironmentObject::RotatingEnvironmentObject()
{
	addComponent(new TransformComponent);
	addComponent(new ModelComponent);
}

void RotatingEnvironmentObject::OnUpdate(float dt)
{
	TransformComponent* transform = getComponent<TransformComponent>();
	transform->yaw(rotation);
}

void RotatingEnvironmentObject::OnMessage(const std::string msg)
{

}