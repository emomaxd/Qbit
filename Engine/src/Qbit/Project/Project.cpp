#include "qbpch.h"
#include "Project.h"

#include "ProjectSerializer.h"

namespace Qbit {

	static void CreateDirectoryIfNeeded(const std::filesystem::path& path)
	{
		if (!std::filesystem::exists(path))
			std::filesystem::create_directories(path);
	}

	Ref<Project> Project::New(const ProjectConfig& config)
	{
		s_ActiveProject = CreateRef<Project>();

		s_ActiveProject->m_Config = config;
	
		return s_ActiveProject;
	}

	Ref<Project> Project::Load(const std::filesystem::path& path)
	{
		Ref<Project> project = CreateRef<Project>();

		ProjectSerializer serializer(project);
		if (serializer.Deserialize(path))
		{
			project->m_ProjectDirectory = path.parent_path();
			s_ActiveProject = project;
			return s_ActiveProject;
		}

		return nullptr;
	}

	bool Project::SaveActive(const std::filesystem::path& path)
	{
		ProjectSerializer serializer(s_ActiveProject);
		if (serializer.Serialize(path))
		{
			//s_ActiveProject->m_ProjectDirectory = path.parent_path();
			return true;
		}

		return false;
	}

	void Project::SetProjectDirectory(const std::filesystem::path& path)
	{
		m_ProjectDirectory = path;
	}

}