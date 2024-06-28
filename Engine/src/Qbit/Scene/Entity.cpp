#include "qbpch.h"
#include "Entity.h"

namespace Qbit {

	Entity::Entity(entt::entity handle, Scene* scene)
		: m_EntityHandle(handle), m_Scene(scene)
	{
	}

}