#include <qbpch.h>

#include "VulkanShader.h"


#include <shaderc/shaderc.hpp>
#include <spirv_cross/spirv_cross.hpp>
#include <spirv_cross/spirv_glsl.hpp>

#include "Qbit/Core/Timer.h"
#include "Qbit/Core/Application.h"
#include "Platform/Vulkan/VulkanContext.h"

namespace Qbit {

	namespace Utils {

		static VkShaderStageFlagBits ShaderTypeFromString(const std::string& type)
		{
			if (type == "vertex")
				return VK_SHADER_STAGE_VERTEX_BIT;
			if (type == "fragment" || type == "pixel")
				return VK_SHADER_STAGE_FRAGMENT_BIT;

			QB_CORE_ASSERT(false, "Unknown shader type!");
			return VK_SHADER_STAGE_FLAG_BITS_MAX_ENUM;
		}

		static shaderc_shader_kind ShaderStageToShaderC(VkShaderStageFlagBits stage) {
			switch (stage)
			{
			case VK_SHADER_STAGE_VERTEX_BIT: return shaderc_glsl_vertex_shader;
			case VK_SHADER_STAGE_FRAGMENT_BIT: return shaderc_glsl_fragment_shader;
			}
			QB_CORE_ASSERT(false, "Unknown shader stage!");
			return static_cast<shaderc_shader_kind>(0);
		}

		static const char* ShaderStageToString(VkShaderStageFlagBits stage) {
			switch (stage)
			{
			case VK_SHADER_STAGE_VERTEX_BIT: return "vertex";
			case VK_SHADER_STAGE_FRAGMENT_BIT: return "fragment";
			}
			QB_CORE_ASSERT(false);
			return nullptr;
		}

		static const char* GetCacheDirectory() {
			return "assets/cache/shader/vulkan";
		}

		static void CreateCacheDirectoryIfNeeded() {
			std::string cacheDirectory = GetCacheDirectory();
			if (!std::filesystem::exists(cacheDirectory))
				std::filesystem::create_directories(cacheDirectory);
		}

		static const char* ShaderStageCachedFileExtension(VkShaderStageFlagBits stage) {
			switch (stage) {
			case VK_SHADER_STAGE_VERTEX_BIT: return ".cached_vulkan.vert";
			case VK_SHADER_STAGE_FRAGMENT_BIT: return ".cached_vulkan.frag";
			}
			QB_CORE_ASSERT(false, "Unknown shader stage!");
			return "";
		}



	}

	VulkanShader::VulkanShader(const std::string& filepath)
		: m_FilePath(filepath)
	{
		QB_PROFILE_FUNCTION();

		{ /* Getting device from window. */
			Application& instance = Application::Get();

			Window& window = instance.GetWindow();

			VulkanContext& context = (VulkanContext&)window.GetGraphicsContext();

			m_Device = context.GetDevice();
			QB_CORE_ASSERT(m_Device != VK_NULL_HANDLE);
		} /* Device is needed for shader creation. */


		Utils::CreateCacheDirectoryIfNeeded();

		std::string source = ReadFile(filepath);
		auto shaderSources = PreProcess(source);

		{
			Timer timer;
			CompileOrGetVulkanBinaries(shaderSources);
			QB_CORE_WARN("Shader creation took {0} ms", timer.ElapsedMillis());
		}

		CreateProgram();

		auto lastSlash = filepath.find_last_of("/\\");
		lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
		auto lastDot = filepath.rfind('.');
		auto count = lastDot == std::string::npos ? filepath.size() - lastSlash : lastDot - lastSlash;
		m_Name = filepath.substr(lastSlash, count);
	}

	VulkanShader::VulkanShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		std::unordered_map<VkShaderStageFlagBits, std::string> sources;
		sources[VkShaderStageFlagBits::VK_SHADER_STAGE_VERTEX_BIT] = vertexSrc;
		sources[VkShaderStageFlagBits::VK_SHADER_STAGE_FRAGMENT_BIT] = fragmentSrc;

		CompileOrGetVulkanBinaries(sources);
		CreateProgram();
	}

	VulkanShader::~VulkanShader()
	{
		vkDestroyShaderModule(m_Device, m_VertexModule, nullptr);
		vkDestroyShaderModule(m_Device, m_FragmentModule, nullptr);
	}

	void VulkanShader::Bind() const
	{
	}

	void VulkanShader::Unbind() const
	{
	}

	void VulkanShader::SetInt(const std::string& name, int value)
	{
	}

	void VulkanShader::SetIntArray(const std::string& name, int* values, uint32_t count)
	{
	}

	void VulkanShader::SetFloat(const std::string& name, float value)
	{
	}

	void VulkanShader::SetFloat2(const std::string& name, const glm::vec2& value)
	{
	}

	void VulkanShader::SetFloat3(const std::string& name, const glm::vec3& value)
	{
	}

	void VulkanShader::SetFloat4(const std::string& name, const glm::vec4& value)
	{
	}

	void VulkanShader::SetMat4(const std::string& name, const glm::mat4& value)
	{
	}

	void VulkanShader::CreateProgram()
	{
		for (auto& shader : m_VulkanSPIRV)
		{
			VkShaderModuleCreateInfo createInfo{};
			createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
			createInfo.codeSize = shader.second.size() * sizeof(uint32_t);
			createInfo.pCode = reinterpret_cast<const uint32_t*>(shader.second.data());

			VkShaderModule shaderModule;
			if (vkCreateShaderModule(m_Device, &createInfo, nullptr, &shaderModule) != VK_SUCCESS)
			{
				QB_CORE_ERROR("Failed to create shader module!");
				QB_CORE_ASSERT(false);
			}
			
			if (shader.first == VkShaderStageFlagBits::VK_SHADER_STAGE_VERTEX_BIT)
			{
				m_VertexModule = shaderModule;
				continue;
			}
			m_FragmentModule = shaderModule;
		}

		CreateShaderStage();

	}

	void VulkanShader::CreateShaderStage()
	{
		{
			VkPipelineShaderStageCreateInfo vertShaderStageInfo{};
			vertShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
			vertShaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;

			vertShaderStageInfo.module = m_VertexModule;
			vertShaderStageInfo.pName = "main";

			m_VertexStageInfo = vertShaderStageInfo;
		}

		{
			VkPipelineShaderStageCreateInfo fragShaderStageInfo{};
			fragShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
			fragShaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
			fragShaderStageInfo.module = m_FragmentModule;
			fragShaderStageInfo.pName = "main";

			m_FragmentStageInfo = fragShaderStageInfo;
		}
	}

	void VulkanShader::Reflect(VkShaderStageFlagBits stage, const std::vector<uint32_t>& shaderData)
	{
		spirv_cross::Compiler compiler(shaderData);
		spirv_cross::ShaderResources resources = compiler.get_shader_resources();

		QB_CORE_TRACE("OpenGLShader::Reflect - {0} {1}", Utils::ShaderStageToString(stage), m_FilePath);
		QB_CORE_TRACE("    {0} uniform buffers", resources.uniform_buffers.size());
		QB_CORE_TRACE("    {0} resources", resources.sampled_images.size());

		QB_CORE_TRACE("Uniform buffers:");
		for (const auto& resource : resources.uniform_buffers)
		{
			const auto& bufferType = compiler.get_type(resource.base_type_id);
			uint32_t bufferSize = compiler.get_declared_struct_size(bufferType);
			uint32_t binding = compiler.get_decoration(resource.id, spv::DecorationBinding);
			int memberCount = bufferType.member_types.size();

			QB_CORE_TRACE("  {0}", resource.name);
			QB_CORE_TRACE("    Size = {0}", bufferSize);
			QB_CORE_TRACE("    Binding = {0}", binding);
			QB_CORE_TRACE("    Members = {0}", memberCount);
		}
	}

	std::string VulkanShader::ReadFile(const std::string& filepath)
	{
		std::string result;
		std::ifstream in(filepath, std::ios::in | std::ios::binary); // ifstream closes itself due to RAII
		if (in)
		{
			in.seekg(0, std::ios::end);
			size_t size = in.tellg();
			if (size != -1)
			{
				result.resize(size);
				in.seekg(0, std::ios::beg);
				in.read(&result[0], size);
			}
			else
			{
				QB_CORE_ERROR("Could not read from file '{0}'", filepath);
			}
		}
		else
		{
			QB_CORE_ERROR("Could not open file '{0}'", filepath);
		}

		return result;
	}
	std::unordered_map<VkShaderStageFlagBits, std::string> VulkanShader::PreProcess(const std::string& source)
	{
		std::unordered_map<VkShaderStageFlagBits, std::string> shaderSources;

		const char* typeToken = "#type";
		size_t typeTokenLength = strlen(typeToken);
		size_t pos = source.find(typeToken, 0); //Start of shader type declaration line
		while (pos != std::string::npos)
		{
			size_t eol = source.find_first_of("\r\n", pos); //End of shader type declaration line
			QB_CORE_ASSERT(eol != std::string::npos, "Syntax error");
			size_t begin = pos + typeTokenLength + 1; //Start of shader type name (after "#type " keyword)
			std::string type = source.substr(begin, eol - begin);
			QB_CORE_ASSERT(Utils::ShaderTypeFromString(type), "Invalid shader type specified");

			size_t nextLinePos = source.find_first_not_of("\r\n", eol); //Start of shader code after shader type declaration line
			QB_CORE_ASSERT(nextLinePos != std::string::npos, "Syntax error");
			pos = source.find(typeToken, nextLinePos); //Start of next shader type declaration line

			shaderSources[Utils::ShaderTypeFromString(type)] = (pos == std::string::npos) ? source.substr(nextLinePos) : source.substr(nextLinePos, pos - nextLinePos);
		}

		return shaderSources;
	}
	void VulkanShader::CompileOrGetVulkanBinaries(const std::unordered_map<VkShaderStageFlagBits, std::string>& shaderSources)
	{
		shaderc::Compiler compiler;
		shaderc::CompileOptions options;
		options.SetTargetEnvironment(shaderc_target_env_vulkan, shaderc_env_version_vulkan_1_2);
		options.SetTargetSpirv(shaderc_spirv_version_1_3);
		options.SetOptimizationLevel(shaderc_optimization_level_performance);

		std::filesystem::path cacheDirectory = Utils::GetCacheDirectory();

		for (auto&& [stage, source] : shaderSources) {
			std::filesystem::path shaderFilePath = m_FilePath;
			std::filesystem::path cachedPath = cacheDirectory / (shaderFilePath.filename().string() + Utils::ShaderStageCachedFileExtension(stage));

			std::ifstream in(cachedPath, std::ios::in | std::ios::binary);
			if (in.is_open()) {
				in.seekg(0, std::ios::end);
				auto size = in.tellg();
				in.seekg(0, std::ios::beg);

				auto& data = m_VulkanSPIRV[stage];
				data.resize(size / sizeof(uint32_t));
				in.read((char*)data.data(), size);

				if (size % 4 != 0) {
					QB_CORE_ERROR("Invalid SPIR-V file size: {}. Must be a multiple of 4.", (uint32_t)size);
				}
				
			}
			else {
				shaderc::SpvCompilationResult module = compiler.CompileGlslToSpv(source, Utils::ShaderStageToShaderC(stage), m_FilePath.c_str(), options);
				if (module.GetCompilationStatus() != shaderc_compilation_status_success)
				{
					QB_CORE_ERROR(module.GetErrorMessage());
					QB_CORE_ASSERT(false);
				}

				m_VulkanSPIRV[stage] = std::vector<uint32_t>(module.cbegin(), module.cend());

				std::ofstream out(cachedPath, std::ios::out | std::ios::binary);
				if (out.is_open()) {
					auto& data = m_VulkanSPIRV[stage];
					out.write((char*)data.data(), data.size() * sizeof(uint32_t));
					out.flush();
					out.close();
				}
			}
		}
	}
	


}