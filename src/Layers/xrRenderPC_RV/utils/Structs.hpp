#pragma once
#include "vulkan_main.hpp"

struct AllocatedBuffer {
  VkBuffer buffer;
  VmaAllocation allocation;
  VmaAllocationInfo info;
};

struct AllocatedImage {
  VkImage image;
  VkImageView imageView;
  VmaAllocation alloc;
  VkExtent3D imageExtent;
  VkFormat imageFormat;
  uint32_t layersCount;
};

enum class PipelineBlend {
  None,
  AlphaBlend,
  Addictive
};

// TODO: sampler config
// TODO: multisampling
struct PipelineConfig {
  PipelineBlend blend;
  bool zTest;
  bool zWrite;
};

struct PipelineInput {
  VkDescriptorSetLayout globalDescriptorLayout;
  std::vector<VkDescriptorSetLayout> descriptorLayouts;
  std::vector<VkPushConstantRange> pcRanges;
};

struct ShaderPass {
	VkPipeline pipeline;
	VkPipelineLayout pipelineLayout;

	PipelineInput inputs;
  PipelineConfig config;
};


struct GPU_SceneData {
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

struct GPU_Vertex {
  glm::vec3 position;
  float uv_x;
  glm::vec3 normal;
  float uv_y;
  glm::vec4 color;
};

struct GPU_BasePushConstantData {
  VkDeviceAddress vertexBufferPtr;
  uint32_t vertexIndex;
};

struct GPU_UIPC {
  GPU_BasePushConstantData base;
  uint8_t layerIndex;
};
