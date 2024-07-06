#pragma once

#include "Qbit/Core/Base.h"
#include "Qbit/Scene/Scene.h"
#include "Qbit/Scene/Entity.h"

namespace Qbit {

	class SceneHierarchyPanel
	{
	public:
		SceneHierarchyPanel() = default;
		SceneHierarchyPanel(const Ref<Scene>& scene);

		void SetContext(const Ref<Scene>& scene);

		void OnImGuiRender();

		Entity GetSelectedEntity() const { return m_SelectionContext; }
		void SetSelectedEntity(Entity entity);
		static Ref<Texture> m_CheckerBoardTexture;
		//static Ref<Texture> GetCheckerBoardTexture() { return m_CheckerBoardTexture; }
	private:
		template<typename T>
		void DisplayAddComponentEntry(const std::string& entryName);

		void DrawEntityNode(Entity entity);
		void DrawComponents(Entity entity);
	private:
		Ref<Scene> m_Context;
		Entity m_SelectionContext;
		
	};

}