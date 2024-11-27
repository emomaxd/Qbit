#include "qbpch.h"
#include "Project.h"

#include "ProjectSerializer.h"

#include "filewatch/FileWatch.h"

#include "Qbit/Core/Application.h"


namespace Qbit {

	static void CreateDirectoryIfNeeded(const std::filesystem::path& path)
	{
		if (!std::filesystem::exists(path))
			std::filesystem::create_directories(path);
	}

	static void ReCreateSolution()
	{
		std::filesystem::path path = std::filesystem::current_path() / Project::GetActive()->GetConfig().Name;

		const std::string command = "cd " + path.string() + " && cmake .";
		system(command.c_str());
	}

	static void BuildSolution()
	{
		std::filesystem::path path = std::filesystem::current_path() / Project::GetActive()->GetConfig().Name;

		const std::string command = "cd " + path.string() + " && cmake --build .";
		system(command.c_str());
	}

	struct fws
	{
		Scope<filewatch::FileWatch<std::string>> m_FileWatch;
	};
	static fws* s_Fws;

	static void SetupFilewatch()
	{

		std::filesystem::path watchPath = std::filesystem::current_path() / Project::GetActive()->GetConfig().Name;
		s_Fws->m_FileWatch = CreateScope<filewatch::FileWatch<std::string>>(
			(watchPath / "Assets" / "Scripts").string(),    // Ensure this returns std::string
			std::regex(".*\\.cs"),                     // Use std::regex for std::string
			[&](const std::string& path, const filewatch::Event change_type)  // Callback
			{
				if (change_type == filewatch::Event::added)
				{
					QB_TRACE("ADDED!");
					Application::Get().SubmitToMainThread([&]()
					{
						s_Fws->m_FileWatch.reset();    // Safely reset the watcher
						ReCreateSolution();            // Recreate solution logic
						SetupFilewatch();
					});
				}
				else if (change_type == filewatch::Event::modified)
				{
					QB_TRACE("MODIFIED!");
					Application::Get().SubmitToMainThread([&]()
					{
							s_Fws->m_FileWatch.reset();    // Safely reset the watcher
							BuildSolution();               // Build solution logic
							SetupFilewatch();
					});
				}
			}
		);

	}

	Ref<Project> Project::New(const ProjectConfig& config)
	{
		s_Fws = new fws;
		s_ActiveProject = CreateRef<Project>();

		s_ActiveProject->m_Config = config;

		SetupFilewatch();
	
		return s_ActiveProject;
	}

	Ref<Project> Project::Load(const std::filesystem::path& path)
	{
		s_Fws = new fws;
		Ref<Project> project = CreateRef<Project>();

		ProjectSerializer serializer(project);
		if (serializer.Deserialize(path))
		{
			project->m_ProjectDirectory = path.parent_path();
			s_ActiveProject = project;
			SetupFilewatch();
			return s_ActiveProject;
		}
		return nullptr;
	}

	bool Project::SaveActive(const std::filesystem::path& path)
	{
		ProjectSerializer serializer(s_ActiveProject);
		if (serializer.Serialize(path))
		{
			s_ActiveProject->m_ProjectDirectory = path.parent_path();
			return true;
		}

		return false;
	}

	void Project::SetProjectDirectory(const std::filesystem::path& path)
	{
		m_ProjectDirectory = path;
	}

}