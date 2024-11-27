#pragma once

#include "Qbit/Renderer/Texture.h"

#include <filesystem>

namespace Qbit {

	class ContentBrowserPanel
	{
	public:
		ContentBrowserPanel();

		void OnImGuiRender();

		inline bool GetIsHovered() { return m_IsHovered; }
		inline std::filesystem::path GetCurrentDirectory() { return m_CurrentDirectory; }
	private:

		std::unordered_map<std::string, Ref<Texture2D>> m_TextureCache;

		Ref<Texture2D> GetTextureForFile(const std::string& filepath);
		bool IsTextureFile(const std::string& filepath);
		Ref<Texture2D> LoadTexture(const std::string& filepath);

		void CreateCustomFile(const std::filesystem::path & path);
		void CreateCSharpFile(std::ofstream& file, const std::string& namespaceName, const std::string& className);

		void DisplayFileCreationPopup();
		void ShowContextMenu();
	private:
		std::filesystem::path m_BaseDirectory;
		std::filesystem::path m_CurrentDirectory;

		bool m_IsHovered = false;

		Ref<Texture2D> m_DirectoryIcon;
		Ref<Texture2D> m_FileIcon;
	};

}