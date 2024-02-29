#ifndef VULKANLAB01_BINGUSSHADER_H
#define VULKANLAB01_BINGUSSHADER_H

#include <string_view>
#include <vector>
#include <vulkan/vulkan_core.h>

class BingusShader final {
public:
	static constexpr VkPipelineInputAssemblyStateCreateInfo INPUT_ASSEMBLY_STATE_INFO{
	        .sType                  = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO,
	        .topology               = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,
	        .primitiveRestartEnable = VK_FALSE,
	};

	static constexpr VkPipelineVertexInputStateCreateInfo VERTEX_INPUT_STATE_INFO{
	        .sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO
	};

	using ShaderStages = std::vector<VkPipelineShaderStageCreateInfo>;

	BingusShader(std::string_view vertexShaderFileName, std::string_view fragmentShaderFile)
	    : m_VertexShaderFileName{vertexShaderFileName}
	    , m_FragmentShaderFileName{fragmentShaderFile} {};

	BingusShader(const BingusShader &)            = delete;
	BingusShader(BingusShader &&)                 = delete;
	BingusShader &operator=(const BingusShader &) = delete;
	BingusShader &operator=(BingusShader &&)      = delete;

	void Initialize(const VkDevice &vkDevice);

	[[nodiscard]]
	const ShaderStages &GetShaderStages() const;

private:
	enum class ShaderType {
		Fragment,
		Vertex,
	};
	static VkPipelineShaderStageCreateInfo
	CreateShaderInfo(const VkDevice &vkDevice, ShaderType shaderType, std::string_view shaderFilePath);

	void DestroyShaderModules(const VkDevice &vkDevice);

	static VkShaderModule CreateShaderModule(const VkDevice &device, const std::vector<char> &code);

	ShaderStages m_ShaderStages;
	std::string  m_VertexShaderFileName;

	std::string m_FragmentShaderFileName;
};


#endif//VULKANLAB01_BINGUSSHADER_H
