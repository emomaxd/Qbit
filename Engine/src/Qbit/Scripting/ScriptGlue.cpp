#include "qbpch.h"
#include "ScriptGlue.h"
#include "ScriptEngine.h"

#include "mono/jit/jit.h"
#include "mono/metadata/assembly.h"
#include "mono/metadata/object.h"
#include "mono/metadata/mono-debug.h"
#include "mono/metadata/threads.h"

#include "Qbit/Core/UUID.h"
#include "Qbit/Core/KeyCodes.h"
#include "Qbit/Core/Input.h"

#include "Qbit/Scene/Scene.h"
#include "Qbit/Scene/Entity.h"



namespace Qbit {

#define QB_ADD_INTERNAL_CALL(Name) mono_add_internal_call("Qbit.InternalCalls::" #Name, Name);

	static void NativeLog(MonoString* string, int parameter)
	{
		char* chr = mono_string_to_utf8(string);
		std::string str(chr);

		mono_free(chr);
		std::cout << str << ", " << parameter << std::endl;
	}

	static void Entity_GetTranslation(UUID uuid, glm::vec3* outTranslation)
	{
		Scene* scene = ScriptEngine::GetSceneContext();
		QB_CORE_ASSERT(scene);
		Entity entity = scene->GetEntityByUUID(uuid);
		QB_CORE_ASSERT(entity);

		*outTranslation = entity.GetComponent<TransformComponent>().Translation;
	}

	static void Entity_SetTranslation(UUID uuid, glm::vec3* translation)
	{
		Scene* scene = ScriptEngine::GetSceneContext();
		QB_CORE_ASSERT(scene);
		Entity entity = scene->GetEntityByUUID(uuid);
		QB_CORE_ASSERT(entity);

		entity.GetComponent<TransformComponent>().Translation = *translation;
	}

	static bool Input_IsKeyDown(KeyCode keycode)
	{
		return Input::IsKeyPressed(keycode);
	}

	void ScriptGlue::RegisterFunctions()
	{
		QB_ADD_INTERNAL_CALL(NativeLog);
		QB_ADD_INTERNAL_CALL(Entity_SetTranslation);
		QB_ADD_INTERNAL_CALL(Entity_GetTranslation);
		QB_ADD_INTERNAL_CALL(Input_IsKeyDown);
	}

}