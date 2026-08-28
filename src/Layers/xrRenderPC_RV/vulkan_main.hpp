#pragma once 

#include <volk.h>
#define VMA_STATIC_VULKAN_FUNCTIONS 0
#define VMA_DYNAMIC_VULKAN_FUNCTIONS 0
#include "vk_mem_alloc.h"
#include <VkBootstrap.h>
#include <SDL3/SDL_vulkan.h>
#include "log.h"
#define TRACY_VK_USE_SYMBOL_TABLE
#include <profiler.h>
#include <tracy/TracyVulkan.hpp>

inline void VK_CHECK(VkResult x) {
  if (x != VK_SUCCESS) {
    Msg("Vulkan check error: %s", x);
    std::runtime_error(std::string(" Detected Vulkan error: ") +
                       std::to_string(x));
  }
}

inline auto TracyGPUMemNotify(const VmaAllocator& allocator) -> void {
  static const std::string nameAlloc = "VMA Alloc";
  VmaBudget budgets[VK_MAX_MEMORY_HEAPS];
  vmaGetHeapBudgets(allocator, budgets);
  const auto& budget = budgets[0];
  TracyPlot(nameAlloc.c_str(), static_cast<double>(budget.usage));
  TracyPlotConfig(nameAlloc.c_str(), tracy::PlotFormatType::Memory, false, true, tracy::Color::Red);
}

