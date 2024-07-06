#pragma once

#include "Qbit/Renderer/Texture.h"

#include <filesystem>

namespace Qbit {

	class ContentBrowserPanel
	{
	public:
		ContentBrowserPanel();

		void OnImGuiRender();

	private:

		std::unordered_map<std::string, Ref<Texture2D>> m_TextureCache;

		Ref<Texture2D> GetTextureForFile(const std::string& filepath);
		bool IsTextureFile(const std::string& filepath);
		Ref<Texture2D> LoadTexture(const std::string& filepath);

	private:
		std::filesystem::path m_BaseDirectory;
		std::filesystem::path m_CurrentDirectory;

		Ref<Texture2D> m_DirectoryIcon;
		Ref<Texture2D> m_FileIcon;
	};

}