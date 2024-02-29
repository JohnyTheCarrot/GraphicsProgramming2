#include "BingusShader.h"
#include <vulkanbase/VulkanUtil.h>

VkPipelineShaderStageCreateInfo
BingusShader::CreateShaderInfo(const VkDevice &vkDevice, ShaderType shaderType, std::string_view shaderFilePath) {
	std::vector<char> fragShaderCode   = ReadFile(shaderFilePath);
	VkShaderModule    fragShaderModule = CreateShaderModule(vkDevice, fragShaderCode);

	VkPipelineShaderStageCreateInfo fragShaderStageInfo{};
	fragShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	fragShaderStageInfo.stage =
	        shaderType == ShaderType::Fragment ? VK_SHADER_STAGE_FRAGMENT_BIT : VK_SHADER_STAGE_VERTEX_BIT;
	fragShaderStageInfo.module = fragShaderModule;
	fragShaderStageInfo.pName  = "main";

	return fragShaderStageInfo;
}

VkShaderModule BingusShader::CreateShaderModule(const VkDevice &vkDevice, const std::vector<char> &code) {
	VkShaderModuleCreateInfo createInfo{};
	createInfo.sType    = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	createInfo.codeSize = code.size();
	createInfo.pCode    = reinterpret_cast<const uint32_t *>(code.data());

	VkShaderModule shaderModule;
	if (vkCreateShaderModule(vkDevice, &createInfo, nullptr, &shaderModule) != VK_SUCCESS) {
		throw std::runtime_error("failed to create shader module!");
	}

	return shaderModule;
}

void BingusShader::Initialize(const VkDevice &vkDevice) {
	m_ShaderStages.emplace_back(CreateShaderInfo(vkDevice, ShaderType::Vertex, m_VertexShaderFileName));
	m_ShaderStages.emplace_back(CreateShaderInfo(vkDevice, ShaderType::Fragment, m_FragmentShaderFileName));
}

void BingusShader::DestroyShaderModules(const VkDevice &vkDevice) {
	for (auto &stageInfo: m_ShaderStages) { vkDestroyShaderModule(vkDevice, stageInfo.module, nullptr); }

	m_ShaderStages.clear();
}

const BingusShader::ShaderStages &BingusShader::GetShaderStages() const {
	return m_ShaderStages;
}
