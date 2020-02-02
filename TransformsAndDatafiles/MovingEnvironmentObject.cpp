#include "MovingEnvironmentObject.h"
#include "TransformComponent.h"
#include "ModelComponent.h"

using namespace std;

MovingEnvironmentObject::MovingEnvironmentObject()
{
	addComponent(new TransformComponent);
	addComponent(new ModelComponent);
}

void MovingEnvironmentObject::OnUpdate(float dt)
{
	TransformComponent* transform = getComponent<TransformComponent>();
	if (transform->m_position.x <= 0)
	{
		
		forward = true;
	}
	else if (transform->m_position.x >= 20)
	{
		forward = false;
	}
	if (forward == true) {
		transform->translate(movementX, 0, 0);
	}
	if (forward == false) {
		transform->translate(-movementX, 0, 0);
	}
}

void MovingEnvironmentObject::OnMessage(const std::string msg)
{

}