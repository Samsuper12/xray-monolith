module;
#include <vulkan_main.hpp>
#include <glm_main.hpp>

export module RV.Utils.Structs;
import xr.Core;


export struct AllocatedBuffer {
  VkBuffer buffer;
  VmaAllocation allocation;
  VmaAllocationInfo info;
};

export struct AllocatedImage {
  VkImage image;
  VkImageView imageView;
  VmaAllocation alloc;
  VkExtent3D imageExtent;
  VkFormat imageFormat;
  uint32_t layersCount;
};

export enum class PipelineBlend {
  None,
  AlphaBlend,
  Addictive
};

// TODO: sampler config
// TODO: multisampling
export struct PipelineConfig {
  PipelineBlend blend;
  bool zTest;
  bool zWrite;
};

export struct PipelineInput {
  VkDescriptorSetLayout globalDescriptorLayout;
  std::vector<VkDescriptorSetLayout> descriptorLayouts;
  std::vector<VkPushConstantRange> pcRanges;
};

export struct ShaderPass {
	VkPipeline pipeline;
	VkPipelineLayout pipelineLayout;

	PipelineInput inputs;
  PipelineConfig config;
};


export struct GPU_SceneData {
  glm::mat4 m_WVP;
  glm::mat4 m_WV;
  glm::mat4 m_W;
  glm::vec4 ambientColor;
  glm::vec4 sunlightDirection;
  glm::vec4 sunlightColor;

  glm::mat4 m_V;
  glm::mat4 m_inv_V;
  glm::mat4 m_P;
  glm::mat4 m_VP;

  uint32_t frameNumber;
  float deltaTime;
};

export struct GPU_Vertex {
  glm::vec3 position;
  float uv_x;
  glm::vec3 normal;
  float uv_y;
  glm::vec4 color;
};

export struct GPU_BasePushConstantData {
  VkDeviceAddress vertexBufferPtr;
  uint32_t vertexIndex;
};

export struct GPU_UIPC {
  GPU_BasePushConstantData base;
  uint8_t layerIndex;
};
