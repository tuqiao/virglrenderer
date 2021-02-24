/*
 * Copyright 2020 Google LLC
 * SPDX-License-Identifier: MIT
 */

#ifndef VN_PROTOCOL_RENDERER_DEFINES_H
#define VN_PROTOCOL_RENDERER_DEFINES_H

#include <stdlib.h>
#include <string.h>

#include "vulkan.h"

#include "vn_protocol_renderer_cs.h"

/* VkStructureType */
#define VK_STRUCTURE_TYPE_RING_CREATE_INFO_MESA ((VkStructureType)1000384000)

typedef enum VkCommandTypeEXT {
    VK_COMMAND_TYPE_vkCreateInstance_EXT = 0,
    VK_COMMAND_TYPE_vkDestroyInstance_EXT = 1,
    VK_COMMAND_TYPE_vkEnumeratePhysicalDevices_EXT = 2,
    VK_COMMAND_TYPE_vkGetPhysicalDeviceFeatures_EXT = 3,
    VK_COMMAND_TYPE_vkGetPhysicalDeviceFormatProperties_EXT = 4,
    VK_COMMAND_TYPE_vkGetPhysicalDeviceImageFormatProperties_EXT = 5,
    VK_COMMAND_TYPE_vkGetPhysicalDeviceProperties_EXT = 6,
    VK_COMMAND_TYPE_vkGetPhysicalDeviceQueueFamilyProperties_EXT = 7,
    VK_COMMAND_TYPE_vkGetPhysicalDeviceMemoryProperties_EXT = 8,
    VK_COMMAND_TYPE_vkGetInstanceProcAddr_EXT = 9,
    VK_COMMAND_TYPE_vkGetDeviceProcAddr_EXT = 10,
    VK_COMMAND_TYPE_vkCreateDevice_EXT = 11,
    VK_COMMAND_TYPE_vkDestroyDevice_EXT = 12,
    VK_COMMAND_TYPE_vkEnumerateInstanceExtensionProperties_EXT = 13,
    VK_COMMAND_TYPE_vkEnumerateDeviceExtensionProperties_EXT = 14,
    VK_COMMAND_TYPE_vkEnumerateInstanceLayerProperties_EXT = 15,
    VK_COMMAND_TYPE_vkEnumerateDeviceLayerProperties_EXT = 16,
    VK_COMMAND_TYPE_vkGetDeviceQueue_EXT = 17,
    VK_COMMAND_TYPE_vkQueueSubmit_EXT = 18,
    VK_COMMAND_TYPE_vkQueueWaitIdle_EXT = 19,
    VK_COMMAND_TYPE_vkDeviceWaitIdle_EXT = 20,
    VK_COMMAND_TYPE_vkAllocateMemory_EXT = 21,
    VK_COMMAND_TYPE_vkFreeMemory_EXT = 22,
    VK_COMMAND_TYPE_vkMapMemory_EXT = 23,
    VK_COMMAND_TYPE_vkUnmapMemory_EXT = 24,
    VK_COMMAND_TYPE_vkFlushMappedMemoryRanges_EXT = 25,
    VK_COMMAND_TYPE_vkInvalidateMappedMemoryRanges_EXT = 26,
    VK_COMMAND_TYPE_vkGetDeviceMemoryCommitment_EXT = 27,
    VK_COMMAND_TYPE_vkBindBufferMemory_EXT = 28,
    VK_COMMAND_TYPE_vkBindImageMemory_EXT = 29,
    VK_COMMAND_TYPE_vkGetBufferMemoryRequirements_EXT = 30,
    VK_COMMAND_TYPE_vkGetImageMemoryRequirements_EXT = 31,
    VK_COMMAND_TYPE_vkGetImageSparseMemoryRequirements_EXT = 32,
    VK_COMMAND_TYPE_vkGetPhysicalDeviceSparseImageFormatProperties_EXT = 33,
    VK_COMMAND_TYPE_vkQueueBindSparse_EXT = 34,
    VK_COMMAND_TYPE_vkCreateFence_EXT = 35,
    VK_COMMAND_TYPE_vkDestroyFence_EXT = 36,
    VK_COMMAND_TYPE_vkResetFences_EXT = 37,
    VK_COMMAND_TYPE_vkGetFenceStatus_EXT = 38,
    VK_COMMAND_TYPE_vkWaitForFences_EXT = 39,
    VK_COMMAND_TYPE_vkCreateSemaphore_EXT = 40,
    VK_COMMAND_TYPE_vkDestroySemaphore_EXT = 41,
    VK_COMMAND_TYPE_vkCreateEvent_EXT = 42,
    VK_COMMAND_TYPE_vkDestroyEvent_EXT = 43,
    VK_COMMAND_TYPE_vkGetEventStatus_EXT = 44,
    VK_COMMAND_TYPE_vkSetEvent_EXT = 45,
    VK_COMMAND_TYPE_vkResetEvent_EXT = 46,
    VK_COMMAND_TYPE_vkCreateQueryPool_EXT = 47,
    VK_COMMAND_TYPE_vkDestroyQueryPool_EXT = 48,
    VK_COMMAND_TYPE_vkGetQueryPoolResults_EXT = 49,
    VK_COMMAND_TYPE_vkCreateBuffer_EXT = 50,
    VK_COMMAND_TYPE_vkDestroyBuffer_EXT = 51,
    VK_COMMAND_TYPE_vkCreateBufferView_EXT = 52,
    VK_COMMAND_TYPE_vkDestroyBufferView_EXT = 53,
    VK_COMMAND_TYPE_vkCreateImage_EXT = 54,
    VK_COMMAND_TYPE_vkDestroyImage_EXT = 55,
    VK_COMMAND_TYPE_vkGetImageSubresourceLayout_EXT = 56,
    VK_COMMAND_TYPE_vkCreateImageView_EXT = 57,
    VK_COMMAND_TYPE_vkDestroyImageView_EXT = 58,
    VK_COMMAND_TYPE_vkCreateShaderModule_EXT = 59,
    VK_COMMAND_TYPE_vkDestroyShaderModule_EXT = 60,
    VK_COMMAND_TYPE_vkCreatePipelineCache_EXT = 61,
    VK_COMMAND_TYPE_vkDestroyPipelineCache_EXT = 62,
    VK_COMMAND_TYPE_vkGetPipelineCacheData_EXT = 63,
    VK_COMMAND_TYPE_vkMergePipelineCaches_EXT = 64,
    VK_COMMAND_TYPE_vkCreateGraphicsPipelines_EXT = 65,
    VK_COMMAND_TYPE_vkCreateComputePipelines_EXT = 66,
    VK_COMMAND_TYPE_vkDestroyPipeline_EXT = 67,
    VK_COMMAND_TYPE_vkCreatePipelineLayout_EXT = 68,
    VK_COMMAND_TYPE_vkDestroyPipelineLayout_EXT = 69,
    VK_COMMAND_TYPE_vkCreateSampler_EXT = 70,
    VK_COMMAND_TYPE_vkDestroySampler_EXT = 71,
    VK_COMMAND_TYPE_vkCreateDescriptorSetLayout_EXT = 72,
    VK_COMMAND_TYPE_vkDestroyDescriptorSetLayout_EXT = 73,
    VK_COMMAND_TYPE_vkCreateDescriptorPool_EXT = 74,
    VK_COMMAND_TYPE_vkDestroyDescriptorPool_EXT = 75,
    VK_COMMAND_TYPE_vkResetDescriptorPool_EXT = 76,
    VK_COMMAND_TYPE_vkAllocateDescriptorSets_EXT = 77,
    VK_COMMAND_TYPE_vkFreeDescriptorSets_EXT = 78,
    VK_COMMAND_TYPE_vkUpdateDescriptorSets_EXT = 79,
    VK_COMMAND_TYPE_vkCreateFramebuffer_EXT = 80,
    VK_COMMAND_TYPE_vkDestroyFramebuffer_EXT = 81,
    VK_COMMAND_TYPE_vkCreateRenderPass_EXT = 82,
    VK_COMMAND_TYPE_vkDestroyRenderPass_EXT = 83,
    VK_COMMAND_TYPE_vkGetRenderAreaGranularity_EXT = 84,
    VK_COMMAND_TYPE_vkCreateCommandPool_EXT = 85,
    VK_COMMAND_TYPE_vkDestroyCommandPool_EXT = 86,
    VK_COMMAND_TYPE_vkResetCommandPool_EXT = 87,
    VK_COMMAND_TYPE_vkAllocateCommandBuffers_EXT = 88,
    VK_COMMAND_TYPE_vkFreeCommandBuffers_EXT = 89,
    VK_COMMAND_TYPE_vkBeginCommandBuffer_EXT = 90,
    VK_COMMAND_TYPE_vkEndCommandBuffer_EXT = 91,
    VK_COMMAND_TYPE_vkResetCommandBuffer_EXT = 92,
    VK_COMMAND_TYPE_vkCmdBindPipeline_EXT = 93,
    VK_COMMAND_TYPE_vkCmdSetViewport_EXT = 94,
    VK_COMMAND_TYPE_vkCmdSetScissor_EXT = 95,
    VK_COMMAND_TYPE_vkCmdSetLineWidth_EXT = 96,
    VK_COMMAND_TYPE_vkCmdSetDepthBias_EXT = 97,
    VK_COMMAND_TYPE_vkCmdSetBlendConstants_EXT = 98,
    VK_COMMAND_TYPE_vkCmdSetDepthBounds_EXT = 99,
    VK_COMMAND_TYPE_vkCmdSetStencilCompareMask_EXT = 100,
    VK_COMMAND_TYPE_vkCmdSetStencilWriteMask_EXT = 101,
    VK_COMMAND_TYPE_vkCmdSetStencilReference_EXT = 102,
    VK_COMMAND_TYPE_vkCmdBindDescriptorSets_EXT = 103,
    VK_COMMAND_TYPE_vkCmdBindIndexBuffer_EXT = 104,
    VK_COMMAND_TYPE_vkCmdBindVertexBuffers_EXT = 105,
    VK_COMMAND_TYPE_vkCmdDraw_EXT = 106,
    VK_COMMAND_TYPE_vkCmdDrawIndexed_EXT = 107,
    VK_COMMAND_TYPE_vkCmdDrawIndirect_EXT = 108,
    VK_COMMAND_TYPE_vkCmdDrawIndexedIndirect_EXT = 109,
    VK_COMMAND_TYPE_vkCmdDispatch_EXT = 110,
    VK_COMMAND_TYPE_vkCmdDispatchIndirect_EXT = 111,
    VK_COMMAND_TYPE_vkCmdCopyBuffer_EXT = 112,
    VK_COMMAND_TYPE_vkCmdCopyImage_EXT = 113,
    VK_COMMAND_TYPE_vkCmdBlitImage_EXT = 114,
    VK_COMMAND_TYPE_vkCmdCopyBufferToImage_EXT = 115,
    VK_COMMAND_TYPE_vkCmdCopyImageToBuffer_EXT = 116,
    VK_COMMAND_TYPE_vkCmdUpdateBuffer_EXT = 117,
    VK_COMMAND_TYPE_vkCmdFillBuffer_EXT = 118,
    VK_COMMAND_TYPE_vkCmdClearColorImage_EXT = 119,
    VK_COMMAND_TYPE_vkCmdClearDepthStencilImage_EXT = 120,
    VK_COMMAND_TYPE_vkCmdClearAttachments_EXT = 121,
    VK_COMMAND_TYPE_vkCmdResolveImage_EXT = 122,
    VK_COMMAND_TYPE_vkCmdSetEvent_EXT = 123,
    VK_COMMAND_TYPE_vkCmdResetEvent_EXT = 124,
    VK_COMMAND_TYPE_vkCmdWaitEvents_EXT = 125,
    VK_COMMAND_TYPE_vkCmdPipelineBarrier_EXT = 126,
    VK_COMMAND_TYPE_vkCmdBeginQuery_EXT = 127,
    VK_COMMAND_TYPE_vkCmdEndQuery_EXT = 128,
    VK_COMMAND_TYPE_vkCmdResetQueryPool_EXT = 129,
    VK_COMMAND_TYPE_vkCmdWriteTimestamp_EXT = 130,
    VK_COMMAND_TYPE_vkCmdCopyQueryPoolResults_EXT = 131,
    VK_COMMAND_TYPE_vkCmdPushConstants_EXT = 132,
    VK_COMMAND_TYPE_vkCmdBeginRenderPass_EXT = 133,
    VK_COMMAND_TYPE_vkCmdNextSubpass_EXT = 134,
    VK_COMMAND_TYPE_vkCmdEndRenderPass_EXT = 135,
    VK_COMMAND_TYPE_vkCmdExecuteCommands_EXT = 136,
    VK_COMMAND_TYPE_vkEnumerateInstanceVersion_EXT = 137,
    VK_COMMAND_TYPE_vkBindBufferMemory2_EXT = 138,
    VK_COMMAND_TYPE_vkBindBufferMemory2KHR_EXT = 138,
    VK_COMMAND_TYPE_vkBindImageMemory2_EXT = 139,
    VK_COMMAND_TYPE_vkBindImageMemory2KHR_EXT = 139,
    VK_COMMAND_TYPE_vkGetDeviceGroupPeerMemoryFeatures_EXT = 140,
    VK_COMMAND_TYPE_vkGetDeviceGroupPeerMemoryFeaturesKHR_EXT = 140,
    VK_COMMAND_TYPE_vkCmdSetDeviceMask_EXT = 141,
    VK_COMMAND_TYPE_vkCmdSetDeviceMaskKHR_EXT = 141,
    VK_COMMAND_TYPE_vkCmdDispatchBase_EXT = 142,
    VK_COMMAND_TYPE_vkCmdDispatchBaseKHR_EXT = 142,
    VK_COMMAND_TYPE_vkEnumeratePhysicalDeviceGroups_EXT = 143,
    VK_COMMAND_TYPE_vkEnumeratePhysicalDeviceGroupsKHR_EXT = 143,
    VK_COMMAND_TYPE_vkGetImageMemoryRequirements2_EXT = 144,
    VK_COMMAND_TYPE_vkGetImageMemoryRequirements2KHR_EXT = 144,
    VK_COMMAND_TYPE_vkGetBufferMemoryRequirements2_EXT = 145,
    VK_COMMAND_TYPE_vkGetBufferMemoryRequirements2KHR_EXT = 145,
    VK_COMMAND_TYPE_vkGetImageSparseMemoryRequirements2_EXT = 146,
    VK_COMMAND_TYPE_vkGetImageSparseMemoryRequirements2KHR_EXT = 146,
    VK_COMMAND_TYPE_vkGetPhysicalDeviceFeatures2_EXT = 147,
    VK_COMMAND_TYPE_vkGetPhysicalDeviceFeatures2KHR_EXT = 147,
    VK_COMMAND_TYPE_vkGetPhysicalDeviceProperties2_EXT = 148,
    VK_COMMAND_TYPE_vkGetPhysicalDeviceProperties2KHR_EXT = 148,
    VK_COMMAND_TYPE_vkGetPhysicalDeviceFormatProperties2_EXT = 149,
    VK_COMMAND_TYPE_vkGetPhysicalDeviceFormatProperties2KHR_EXT = 149,
    VK_COMMAND_TYPE_vkGetPhysicalDeviceImageFormatProperties2_EXT = 150,
    VK_COMMAND_TYPE_vkGetPhysicalDeviceImageFormatProperties2KHR_EXT = 150,
    VK_COMMAND_TYPE_vkGetPhysicalDeviceQueueFamilyProperties2_EXT = 151,
    VK_COMMAND_TYPE_vkGetPhysicalDeviceQueueFamilyProperties2KHR_EXT = 151,
    VK_COMMAND_TYPE_vkGetPhysicalDeviceMemoryProperties2_EXT = 152,
    VK_COMMAND_TYPE_vkGetPhysicalDeviceMemoryProperties2KHR_EXT = 152,
    VK_COMMAND_TYPE_vkGetPhysicalDeviceSparseImageFormatProperties2_EXT = 153,
    VK_COMMAND_TYPE_vkGetPhysicalDeviceSparseImageFormatProperties2KHR_EXT = 153,
    VK_COMMAND_TYPE_vkTrimCommandPool_EXT = 154,
    VK_COMMAND_TYPE_vkTrimCommandPoolKHR_EXT = 154,
    VK_COMMAND_TYPE_vkGetDeviceQueue2_EXT = 155,
    VK_COMMAND_TYPE_vkCreateSamplerYcbcrConversion_EXT = 156,
    VK_COMMAND_TYPE_vkCreateSamplerYcbcrConversionKHR_EXT = 156,
    VK_COMMAND_TYPE_vkDestroySamplerYcbcrConversion_EXT = 157,
    VK_COMMAND_TYPE_vkDestroySamplerYcbcrConversionKHR_EXT = 157,
    VK_COMMAND_TYPE_vkCreateDescriptorUpdateTemplate_EXT = 158,
    VK_COMMAND_TYPE_vkCreateDescriptorUpdateTemplateKHR_EXT = 158,
    VK_COMMAND_TYPE_vkDestroyDescriptorUpdateTemplate_EXT = 159,
    VK_COMMAND_TYPE_vkDestroyDescriptorUpdateTemplateKHR_EXT = 159,
    VK_COMMAND_TYPE_vkUpdateDescriptorSetWithTemplate_EXT = 160,
    VK_COMMAND_TYPE_vkUpdateDescriptorSetWithTemplateKHR_EXT = 160,
    VK_COMMAND_TYPE_vkGetPhysicalDeviceExternalBufferProperties_EXT = 161,
    VK_COMMAND_TYPE_vkGetPhysicalDeviceExternalBufferPropertiesKHR_EXT = 161,
    VK_COMMAND_TYPE_vkGetPhysicalDeviceExternalFenceProperties_EXT = 162,
    VK_COMMAND_TYPE_vkGetPhysicalDeviceExternalFencePropertiesKHR_EXT = 162,
    VK_COMMAND_TYPE_vkGetPhysicalDeviceExternalSemaphoreProperties_EXT = 163,
    VK_COMMAND_TYPE_vkGetPhysicalDeviceExternalSemaphorePropertiesKHR_EXT = 163,
    VK_COMMAND_TYPE_vkGetDescriptorSetLayoutSupport_EXT = 164,
    VK_COMMAND_TYPE_vkGetDescriptorSetLayoutSupportKHR_EXT = 164,
    VK_COMMAND_TYPE_vkCmdDrawIndirectCount_EXT = 165,
    VK_COMMAND_TYPE_vkCmdDrawIndirectCountKHR_EXT = 165,
    VK_COMMAND_TYPE_vkCmdDrawIndirectCountAMD_EXT = 165,
    VK_COMMAND_TYPE_vkCmdDrawIndexedIndirectCount_EXT = 166,
    VK_COMMAND_TYPE_vkCmdDrawIndexedIndirectCountKHR_EXT = 166,
    VK_COMMAND_TYPE_vkCmdDrawIndexedIndirectCountAMD_EXT = 166,
    VK_COMMAND_TYPE_vkCreateRenderPass2_EXT = 167,
    VK_COMMAND_TYPE_vkCreateRenderPass2KHR_EXT = 167,
    VK_COMMAND_TYPE_vkCmdBeginRenderPass2_EXT = 168,
    VK_COMMAND_TYPE_vkCmdBeginRenderPass2KHR_EXT = 168,
    VK_COMMAND_TYPE_vkCmdNextSubpass2_EXT = 169,
    VK_COMMAND_TYPE_vkCmdNextSubpass2KHR_EXT = 169,
    VK_COMMAND_TYPE_vkCmdEndRenderPass2_EXT = 170,
    VK_COMMAND_TYPE_vkCmdEndRenderPass2KHR_EXT = 170,
    VK_COMMAND_TYPE_vkResetQueryPool_EXT = 171,
    VK_COMMAND_TYPE_vkResetQueryPoolEXT_EXT = 171,
    VK_COMMAND_TYPE_vkGetSemaphoreCounterValue_EXT = 172,
    VK_COMMAND_TYPE_vkGetSemaphoreCounterValueKHR_EXT = 172,
    VK_COMMAND_TYPE_vkWaitSemaphores_EXT = 173,
    VK_COMMAND_TYPE_vkWaitSemaphoresKHR_EXT = 173,
    VK_COMMAND_TYPE_vkSignalSemaphore_EXT = 174,
    VK_COMMAND_TYPE_vkSignalSemaphoreKHR_EXT = 174,
    VK_COMMAND_TYPE_vkGetBufferDeviceAddress_EXT = 175,
    VK_COMMAND_TYPE_vkGetBufferDeviceAddressKHR_EXT = 175,
    VK_COMMAND_TYPE_vkGetBufferDeviceAddressEXT_EXT = 175,
    VK_COMMAND_TYPE_vkGetBufferOpaqueCaptureAddress_EXT = 176,
    VK_COMMAND_TYPE_vkGetBufferOpaqueCaptureAddressKHR_EXT = 176,
    VK_COMMAND_TYPE_vkGetDeviceMemoryOpaqueCaptureAddress_EXT = 177,
    VK_COMMAND_TYPE_vkGetDeviceMemoryOpaqueCaptureAddressKHR_EXT = 177,
    VK_COMMAND_TYPE_vkCmdBindTransformFeedbackBuffersEXT_EXT = 181,
    VK_COMMAND_TYPE_vkCmdBeginTransformFeedbackEXT_EXT = 182,
    VK_COMMAND_TYPE_vkCmdEndTransformFeedbackEXT_EXT = 183,
    VK_COMMAND_TYPE_vkCmdBeginQueryIndexedEXT_EXT = 184,
    VK_COMMAND_TYPE_vkCmdEndQueryIndexedEXT_EXT = 185,
    VK_COMMAND_TYPE_vkCmdDrawIndirectByteCountEXT_EXT = 186,
    VK_COMMAND_TYPE_vkGetImageDrmFormatModifierPropertiesEXT_EXT = 187,
    VK_COMMAND_TYPE_vkSetReplyCommandStreamMESA_EXT = 178,
    VK_COMMAND_TYPE_vkSeekReplyCommandStreamMESA_EXT = 179,
    VK_COMMAND_TYPE_vkExecuteCommandStreamsMESA_EXT = 180,
    VK_COMMAND_TYPE_vkCreateRingMESA_EXT = 188,
    VK_COMMAND_TYPE_vkDestroyRingMESA_EXT = 189,
    VK_COMMAND_TYPE_vkNotifyRingMESA_EXT = 190,
    VK_COMMAND_TYPE_vkWriteRingExtraMESA_EXT = 191,
} VkCommandTypeEXT;

typedef enum VkCommandFlagBitsEXT {
    VK_COMMAND_GENERATE_REPLY_BIT_EXT = 0x00000001,
} VkCommandFlagBitsEXT;

typedef VkFlags VkCommandFlagsEXT;

typedef VkFlags VkCommandStreamExecutionFlagsMESA;

typedef VkFlags VkRingCreateFlagsMESA;

typedef VkFlags VkRingNotifyFlagsMESA;

typedef struct VkCommandStreamDescriptionMESA {
    uint32_t resourceId;
    size_t offset;
    size_t size;
} VkCommandStreamDescriptionMESA;

typedef struct VkCommandStreamDependencyMESA {
    uint32_t srcCommandStream;
    uint32_t dstCommandStream;
} VkCommandStreamDependencyMESA;

typedef struct VkRingCreateInfoMESA {
    VkStructureType sType;
    const void* pNext;
    VkRingCreateFlagsMESA flags;
    uint32_t resourceId;
    size_t offset;
    size_t size;
    uint64_t idleTimeout;
    size_t headOffset;
    size_t tailOffset;
    size_t statusOffset;
    size_t bufferOffset;
    size_t bufferSize;
    size_t extraOffset;
    size_t extraSize;
} VkRingCreateInfoMESA;

struct vn_command_vkCreateInstance {
    const VkInstanceCreateInfo* pCreateInfo;
    const VkAllocationCallbacks* pAllocator;
    VkInstance* pInstance;

    VkResult ret;
};

struct vn_command_vkDestroyInstance {
    VkInstance instance;
    const VkAllocationCallbacks* pAllocator;
};

struct vn_command_vkEnumeratePhysicalDevices {
    VkInstance instance;
    uint32_t* pPhysicalDeviceCount;
    VkPhysicalDevice* pPhysicalDevices;

    VkResult ret;
};

struct vn_command_vkGetDeviceProcAddr {
    VkDevice device;
    const char* pName;

    PFN_vkVoidFunction ret;
};

struct vn_command_vkGetInstanceProcAddr {
    VkInstance instance;
    const char* pName;

    PFN_vkVoidFunction ret;
};

struct vn_command_vkGetPhysicalDeviceProperties {
    VkPhysicalDevice physicalDevice;
    VkPhysicalDeviceProperties* pProperties;
};

struct vn_command_vkGetPhysicalDeviceQueueFamilyProperties {
    VkPhysicalDevice physicalDevice;
    uint32_t* pQueueFamilyPropertyCount;
    VkQueueFamilyProperties* pQueueFamilyProperties;
};

struct vn_command_vkGetPhysicalDeviceMemoryProperties {
    VkPhysicalDevice physicalDevice;
    VkPhysicalDeviceMemoryProperties* pMemoryProperties;
};

struct vn_command_vkGetPhysicalDeviceFeatures {
    VkPhysicalDevice physicalDevice;
    VkPhysicalDeviceFeatures* pFeatures;
};

struct vn_command_vkGetPhysicalDeviceFormatProperties {
    VkPhysicalDevice physicalDevice;
    VkFormat format;
    VkFormatProperties* pFormatProperties;
};

struct vn_command_vkGetPhysicalDeviceImageFormatProperties {
    VkPhysicalDevice physicalDevice;
    VkFormat format;
    VkImageType type;
    VkImageTiling tiling;
    VkImageUsageFlags usage;
    VkImageCreateFlags flags;
    VkImageFormatProperties* pImageFormatProperties;

    VkResult ret;
};

struct vn_command_vkCreateDevice {
    VkPhysicalDevice physicalDevice;
    const VkDeviceCreateInfo* pCreateInfo;
    const VkAllocationCallbacks* pAllocator;
    VkDevice* pDevice;

    VkResult ret;
};

struct vn_command_vkDestroyDevice {
    VkDevice device;
    const VkAllocationCallbacks* pAllocator;
};

struct vn_command_vkEnumerateInstanceVersion {
    uint32_t* pApiVersion;

    VkResult ret;
};

struct vn_command_vkEnumerateInstanceLayerProperties {
    uint32_t* pPropertyCount;
    VkLayerProperties* pProperties;

    VkResult ret;
};

struct vn_command_vkEnumerateInstanceExtensionProperties {
    const char* pLayerName;
    uint32_t* pPropertyCount;
    VkExtensionProperties* pProperties;

    VkResult ret;
};

struct vn_command_vkEnumerateDeviceLayerProperties {
    VkPhysicalDevice physicalDevice;
    uint32_t* pPropertyCount;
    VkLayerProperties* pProperties;

    VkResult ret;
};

struct vn_command_vkEnumerateDeviceExtensionProperties {
    VkPhysicalDevice physicalDevice;
    const char* pLayerName;
    uint32_t* pPropertyCount;
    VkExtensionProperties* pProperties;

    VkResult ret;
};

struct vn_command_vkGetDeviceQueue {
    VkDevice device;
    uint32_t queueFamilyIndex;
    uint32_t queueIndex;
    VkQueue* pQueue;
};

struct vn_command_vkQueueSubmit {
    VkQueue queue;
    uint32_t submitCount;
    const VkSubmitInfo* pSubmits;
    VkFence fence;

    VkResult ret;
};

struct vn_command_vkQueueWaitIdle {
    VkQueue queue;

    VkResult ret;
};

struct vn_command_vkDeviceWaitIdle {
    VkDevice device;

    VkResult ret;
};

struct vn_command_vkAllocateMemory {
    VkDevice device;
    const VkMemoryAllocateInfo* pAllocateInfo;
    const VkAllocationCallbacks* pAllocator;
    VkDeviceMemory* pMemory;

    VkResult ret;
};

struct vn_command_vkFreeMemory {
    VkDevice device;
    VkDeviceMemory memory;
    const VkAllocationCallbacks* pAllocator;
};

struct vn_command_vkMapMemory {
    VkDevice device;
    VkDeviceMemory memory;
    VkDeviceSize offset;
    VkDeviceSize size;
    VkMemoryMapFlags flags;
    void** ppData;

    VkResult ret;
};

struct vn_command_vkUnmapMemory {
    VkDevice device;
    VkDeviceMemory memory;
};

struct vn_command_vkFlushMappedMemoryRanges {
    VkDevice device;
    uint32_t memoryRangeCount;
    const VkMappedMemoryRange* pMemoryRanges;

    VkResult ret;
};

struct vn_command_vkInvalidateMappedMemoryRanges {
    VkDevice device;
    uint32_t memoryRangeCount;
    const VkMappedMemoryRange* pMemoryRanges;

    VkResult ret;
};

struct vn_command_vkGetDeviceMemoryCommitment {
    VkDevice device;
    VkDeviceMemory memory;
    VkDeviceSize* pCommittedMemoryInBytes;
};

struct vn_command_vkGetBufferMemoryRequirements {
    VkDevice device;
    VkBuffer buffer;
    VkMemoryRequirements* pMemoryRequirements;
};

struct vn_command_vkBindBufferMemory {
    VkDevice device;
    VkBuffer buffer;
    VkDeviceMemory memory;
    VkDeviceSize memoryOffset;

    VkResult ret;
};

struct vn_command_vkGetImageMemoryRequirements {
    VkDevice device;
    VkImage image;
    VkMemoryRequirements* pMemoryRequirements;
};

struct vn_command_vkBindImageMemory {
    VkDevice device;
    VkImage image;
    VkDeviceMemory memory;
    VkDeviceSize memoryOffset;

    VkResult ret;
};

struct vn_command_vkGetImageSparseMemoryRequirements {
    VkDevice device;
    VkImage image;
    uint32_t* pSparseMemoryRequirementCount;
    VkSparseImageMemoryRequirements* pSparseMemoryRequirements;
};

struct vn_command_vkGetPhysicalDeviceSparseImageFormatProperties {
    VkPhysicalDevice physicalDevice;
    VkFormat format;
    VkImageType type;
    VkSampleCountFlagBits samples;
    VkImageUsageFlags usage;
    VkImageTiling tiling;
    uint32_t* pPropertyCount;
    VkSparseImageFormatProperties* pProperties;
};

struct vn_command_vkQueueBindSparse {
    VkQueue queue;
    uint32_t bindInfoCount;
    const VkBindSparseInfo* pBindInfo;
    VkFence fence;

    VkResult ret;
};

struct vn_command_vkCreateFence {
    VkDevice device;
    const VkFenceCreateInfo* pCreateInfo;
    const VkAllocationCallbacks* pAllocator;
    VkFence* pFence;

    VkResult ret;
};

struct vn_command_vkDestroyFence {
    VkDevice device;
    VkFence fence;
    const VkAllocationCallbacks* pAllocator;
};

struct vn_command_vkResetFences {
    VkDevice device;
    uint32_t fenceCount;
    const VkFence* pFences;

    VkResult ret;
};

struct vn_command_vkGetFenceStatus {
    VkDevice device;
    VkFence fence;

    VkResult ret;
};

struct vn_command_vkWaitForFences {
    VkDevice device;
    uint32_t fenceCount;
    const VkFence* pFences;
    VkBool32 waitAll;
    uint64_t timeout;

    VkResult ret;
};

struct vn_command_vkCreateSemaphore {
    VkDevice device;
    const VkSemaphoreCreateInfo* pCreateInfo;
    const VkAllocationCallbacks* pAllocator;
    VkSemaphore* pSemaphore;

    VkResult ret;
};

struct vn_command_vkDestroySemaphore {
    VkDevice device;
    VkSemaphore semaphore;
    const VkAllocationCallbacks* pAllocator;
};

struct vn_command_vkCreateEvent {
    VkDevice device;
    const VkEventCreateInfo* pCreateInfo;
    const VkAllocationCallbacks* pAllocator;
    VkEvent* pEvent;

    VkResult ret;
};

struct vn_command_vkDestroyEvent {
    VkDevice device;
    VkEvent event;
    const VkAllocationCallbacks* pAllocator;
};

struct vn_command_vkGetEventStatus {
    VkDevice device;
    VkEvent event;

    VkResult ret;
};

struct vn_command_vkSetEvent {
    VkDevice device;
    VkEvent event;

    VkResult ret;
};

struct vn_command_vkResetEvent {
    VkDevice device;
    VkEvent event;

    VkResult ret;
};

struct vn_command_vkCreateQueryPool {
    VkDevice device;
    const VkQueryPoolCreateInfo* pCreateInfo;
    const VkAllocationCallbacks* pAllocator;
    VkQueryPool* pQueryPool;

    VkResult ret;
};

struct vn_command_vkDestroyQueryPool {
    VkDevice device;
    VkQueryPool queryPool;
    const VkAllocationCallbacks* pAllocator;
};

struct vn_command_vkGetQueryPoolResults {
    VkDevice device;
    VkQueryPool queryPool;
    uint32_t firstQuery;
    uint32_t queryCount;
    size_t dataSize;
    void* pData;
    VkDeviceSize stride;
    VkQueryResultFlags flags;

    VkResult ret;
};

struct vn_command_vkResetQueryPool {
    VkDevice device;
    VkQueryPool queryPool;
    uint32_t firstQuery;
    uint32_t queryCount;
};

struct vn_command_vkCreateBuffer {
    VkDevice device;
    const VkBufferCreateInfo* pCreateInfo;
    const VkAllocationCallbacks* pAllocator;
    VkBuffer* pBuffer;

    VkResult ret;
};

struct vn_command_vkDestroyBuffer {
    VkDevice device;
    VkBuffer buffer;
    const VkAllocationCallbacks* pAllocator;
};

struct vn_command_vkCreateBufferView {
    VkDevice device;
    const VkBufferViewCreateInfo* pCreateInfo;
    const VkAllocationCallbacks* pAllocator;
    VkBufferView* pView;

    VkResult ret;
};

struct vn_command_vkDestroyBufferView {
    VkDevice device;
    VkBufferView bufferView;
    const VkAllocationCallbacks* pAllocator;
};

struct vn_command_vkCreateImage {
    VkDevice device;
    const VkImageCreateInfo* pCreateInfo;
    const VkAllocationCallbacks* pAllocator;
    VkImage* pImage;

    VkResult ret;
};

struct vn_command_vkDestroyImage {
    VkDevice device;
    VkImage image;
    const VkAllocationCallbacks* pAllocator;
};

struct vn_command_vkGetImageSubresourceLayout {
    VkDevice device;
    VkImage image;
    const VkImageSubresource* pSubresource;
    VkSubresourceLayout* pLayout;
};

struct vn_command_vkCreateImageView {
    VkDevice device;
    const VkImageViewCreateInfo* pCreateInfo;
    const VkAllocationCallbacks* pAllocator;
    VkImageView* pView;

    VkResult ret;
};

struct vn_command_vkDestroyImageView {
    VkDevice device;
    VkImageView imageView;
    const VkAllocationCallbacks* pAllocator;
};

struct vn_command_vkCreateShaderModule {
    VkDevice device;
    const VkShaderModuleCreateInfo* pCreateInfo;
    const VkAllocationCallbacks* pAllocator;
    VkShaderModule* pShaderModule;

    VkResult ret;
};

struct vn_command_vkDestroyShaderModule {
    VkDevice device;
    VkShaderModule shaderModule;
    const VkAllocationCallbacks* pAllocator;
};

struct vn_command_vkCreatePipelineCache {
    VkDevice device;
    const VkPipelineCacheCreateInfo* pCreateInfo;
    const VkAllocationCallbacks* pAllocator;
    VkPipelineCache* pPipelineCache;

    VkResult ret;
};

struct vn_command_vkDestroyPipelineCache {
    VkDevice device;
    VkPipelineCache pipelineCache;
    const VkAllocationCallbacks* pAllocator;
};

struct vn_command_vkGetPipelineCacheData {
    VkDevice device;
    VkPipelineCache pipelineCache;
    size_t* pDataSize;
    void* pData;

    VkResult ret;
};

struct vn_command_vkMergePipelineCaches {
    VkDevice device;
    VkPipelineCache dstCache;
    uint32_t srcCacheCount;
    const VkPipelineCache* pSrcCaches;

    VkResult ret;
};

struct vn_command_vkCreateGraphicsPipelines {
    VkDevice device;
    VkPipelineCache pipelineCache;
    uint32_t createInfoCount;
    const VkGraphicsPipelineCreateInfo* pCreateInfos;
    const VkAllocationCallbacks* pAllocator;
    VkPipeline* pPipelines;

    VkResult ret;
};

struct vn_command_vkCreateComputePipelines {
    VkDevice device;
    VkPipelineCache pipelineCache;
    uint32_t createInfoCount;
    const VkComputePipelineCreateInfo* pCreateInfos;
    const VkAllocationCallbacks* pAllocator;
    VkPipeline* pPipelines;

    VkResult ret;
};

struct vn_command_vkDestroyPipeline {
    VkDevice device;
    VkPipeline pipeline;
    const VkAllocationCallbacks* pAllocator;
};

struct vn_command_vkCreatePipelineLayout {
    VkDevice device;
    const VkPipelineLayoutCreateInfo* pCreateInfo;
    const VkAllocationCallbacks* pAllocator;
    VkPipelineLayout* pPipelineLayout;

    VkResult ret;
};

struct vn_command_vkDestroyPipelineLayout {
    VkDevice device;
    VkPipelineLayout pipelineLayout;
    const VkAllocationCallbacks* pAllocator;
};

struct vn_command_vkCreateSampler {
    VkDevice device;
    const VkSamplerCreateInfo* pCreateInfo;
    const VkAllocationCallbacks* pAllocator;
    VkSampler* pSampler;

    VkResult ret;
};

struct vn_command_vkDestroySampler {
    VkDevice device;
    VkSampler sampler;
    const VkAllocationCallbacks* pAllocator;
};

struct vn_command_vkCreateDescriptorSetLayout {
    VkDevice device;
    const VkDescriptorSetLayoutCreateInfo* pCreateInfo;
    const VkAllocationCallbacks* pAllocator;
    VkDescriptorSetLayout* pSetLayout;

    VkResult ret;
};

struct vn_command_vkDestroyDescriptorSetLayout {
    VkDevice device;
    VkDescriptorSetLayout descriptorSetLayout;
    const VkAllocationCallbacks* pAllocator;
};

struct vn_command_vkCreateDescriptorPool {
    VkDevice device;
    const VkDescriptorPoolCreateInfo* pCreateInfo;
    const VkAllocationCallbacks* pAllocator;
    VkDescriptorPool* pDescriptorPool;

    VkResult ret;
};

struct vn_command_vkDestroyDescriptorPool {
    VkDevice device;
    VkDescriptorPool descriptorPool;
    const VkAllocationCallbacks* pAllocator;
};

struct vn_command_vkResetDescriptorPool {
    VkDevice device;
    VkDescriptorPool descriptorPool;
    VkDescriptorPoolResetFlags flags;

    VkResult ret;
};

struct vn_command_vkAllocateDescriptorSets {
    VkDevice device;
    const VkDescriptorSetAllocateInfo* pAllocateInfo;
    VkDescriptorSet* pDescriptorSets;

    VkResult ret;
};

struct vn_command_vkFreeDescriptorSets {
    VkDevice device;
    VkDescriptorPool descriptorPool;
    uint32_t descriptorSetCount;
    const VkDescriptorSet* pDescriptorSets;

    VkResult ret;
};

struct vn_command_vkUpdateDescriptorSets {
    VkDevice device;
    uint32_t descriptorWriteCount;
    const VkWriteDescriptorSet* pDescriptorWrites;
    uint32_t descriptorCopyCount;
    const VkCopyDescriptorSet* pDescriptorCopies;
};

struct vn_command_vkCreateFramebuffer {
    VkDevice device;
    const VkFramebufferCreateInfo* pCreateInfo;
    const VkAllocationCallbacks* pAllocator;
    VkFramebuffer* pFramebuffer;

    VkResult ret;
};

struct vn_command_vkDestroyFramebuffer {
    VkDevice device;
    VkFramebuffer framebuffer;
    const VkAllocationCallbacks* pAllocator;
};

struct vn_command_vkCreateRenderPass {
    VkDevice device;
    const VkRenderPassCreateInfo* pCreateInfo;
    const VkAllocationCallbacks* pAllocator;
    VkRenderPass* pRenderPass;

    VkResult ret;
};

struct vn_command_vkDestroyRenderPass {
    VkDevice device;
    VkRenderPass renderPass;
    const VkAllocationCallbacks* pAllocator;
};

struct vn_command_vkGetRenderAreaGranularity {
    VkDevice device;
    VkRenderPass renderPass;
    VkExtent2D* pGranularity;
};

struct vn_command_vkCreateCommandPool {
    VkDevice device;
    const VkCommandPoolCreateInfo* pCreateInfo;
    const VkAllocationCallbacks* pAllocator;
    VkCommandPool* pCommandPool;

    VkResult ret;
};

struct vn_command_vkDestroyCommandPool {
    VkDevice device;
    VkCommandPool commandPool;
    const VkAllocationCallbacks* pAllocator;
};

struct vn_command_vkResetCommandPool {
    VkDevice device;
    VkCommandPool commandPool;
    VkCommandPoolResetFlags flags;

    VkResult ret;
};

struct vn_command_vkAllocateCommandBuffers {
    VkDevice device;
    const VkCommandBufferAllocateInfo* pAllocateInfo;
    VkCommandBuffer* pCommandBuffers;

    VkResult ret;
};

struct vn_command_vkFreeCommandBuffers {
    VkDevice device;
    VkCommandPool commandPool;
    uint32_t commandBufferCount;
    const VkCommandBuffer* pCommandBuffers;
};

struct vn_command_vkBeginCommandBuffer {
    VkCommandBuffer commandBuffer;
    const VkCommandBufferBeginInfo* pBeginInfo;

    VkResult ret;
};

struct vn_command_vkEndCommandBuffer {
    VkCommandBuffer commandBuffer;

    VkResult ret;
};

struct vn_command_vkResetCommandBuffer {
    VkCommandBuffer commandBuffer;
    VkCommandBufferResetFlags flags;

    VkResult ret;
};

struct vn_command_vkCmdBindPipeline {
    VkCommandBuffer commandBuffer;
    VkPipelineBindPoint pipelineBindPoint;
    VkPipeline pipeline;
};

struct vn_command_vkCmdSetViewport {
    VkCommandBuffer commandBuffer;
    uint32_t firstViewport;
    uint32_t viewportCount;
    const VkViewport* pViewports;
};

struct vn_command_vkCmdSetScissor {
    VkCommandBuffer commandBuffer;
    uint32_t firstScissor;
    uint32_t scissorCount;
    const VkRect2D* pScissors;
};

struct vn_command_vkCmdSetLineWidth {
    VkCommandBuffer commandBuffer;
    float lineWidth;
};

struct vn_command_vkCmdSetDepthBias {
    VkCommandBuffer commandBuffer;
    float depthBiasConstantFactor;
    float depthBiasClamp;
    float depthBiasSlopeFactor;
};

struct vn_command_vkCmdSetBlendConstants {
    VkCommandBuffer commandBuffer;
    const float blendConstants[4];
};

struct vn_command_vkCmdSetDepthBounds {
    VkCommandBuffer commandBuffer;
    float minDepthBounds;
    float maxDepthBounds;
};

struct vn_command_vkCmdSetStencilCompareMask {
    VkCommandBuffer commandBuffer;
    VkStencilFaceFlags faceMask;
    uint32_t compareMask;
};

struct vn_command_vkCmdSetStencilWriteMask {
    VkCommandBuffer commandBuffer;
    VkStencilFaceFlags faceMask;
    uint32_t writeMask;
};

struct vn_command_vkCmdSetStencilReference {
    VkCommandBuffer commandBuffer;
    VkStencilFaceFlags faceMask;
    uint32_t reference;
};

struct vn_command_vkCmdBindDescriptorSets {
    VkCommandBuffer commandBuffer;
    VkPipelineBindPoint pipelineBindPoint;
    VkPipelineLayout layout;
    uint32_t firstSet;
    uint32_t descriptorSetCount;
    const VkDescriptorSet* pDescriptorSets;
    uint32_t dynamicOffsetCount;
    const uint32_t* pDynamicOffsets;
};

struct vn_command_vkCmdBindIndexBuffer {
    VkCommandBuffer commandBuffer;
    VkBuffer buffer;
    VkDeviceSize offset;
    VkIndexType indexType;
};

struct vn_command_vkCmdBindVertexBuffers {
    VkCommandBuffer commandBuffer;
    uint32_t firstBinding;
    uint32_t bindingCount;
    const VkBuffer* pBuffers;
    const VkDeviceSize* pOffsets;
};

struct vn_command_vkCmdDraw {
    VkCommandBuffer commandBuffer;
    uint32_t vertexCount;
    uint32_t instanceCount;
    uint32_t firstVertex;
    uint32_t firstInstance;
};

struct vn_command_vkCmdDrawIndexed {
    VkCommandBuffer commandBuffer;
    uint32_t indexCount;
    uint32_t instanceCount;
    uint32_t firstIndex;
    int32_t vertexOffset;
    uint32_t firstInstance;
};

struct vn_command_vkCmdDrawIndirect {
    VkCommandBuffer commandBuffer;
    VkBuffer buffer;
    VkDeviceSize offset;
    uint32_t drawCount;
    uint32_t stride;
};

struct vn_command_vkCmdDrawIndexedIndirect {
    VkCommandBuffer commandBuffer;
    VkBuffer buffer;
    VkDeviceSize offset;
    uint32_t drawCount;
    uint32_t stride;
};

struct vn_command_vkCmdDispatch {
    VkCommandBuffer commandBuffer;
    uint32_t groupCountX;
    uint32_t groupCountY;
    uint32_t groupCountZ;
};

struct vn_command_vkCmdDispatchIndirect {
    VkCommandBuffer commandBuffer;
    VkBuffer buffer;
    VkDeviceSize offset;
};

struct vn_command_vkCmdCopyBuffer {
    VkCommandBuffer commandBuffer;
    VkBuffer srcBuffer;
    VkBuffer dstBuffer;
    uint32_t regionCount;
    const VkBufferCopy* pRegions;
};

struct vn_command_vkCmdCopyImage {
    VkCommandBuffer commandBuffer;
    VkImage srcImage;
    VkImageLayout srcImageLayout;
    VkImage dstImage;
    VkImageLayout dstImageLayout;
    uint32_t regionCount;
    const VkImageCopy* pRegions;
};

struct vn_command_vkCmdBlitImage {
    VkCommandBuffer commandBuffer;
    VkImage srcImage;
    VkImageLayout srcImageLayout;
    VkImage dstImage;
    VkImageLayout dstImageLayout;
    uint32_t regionCount;
    const VkImageBlit* pRegions;
    VkFilter filter;
};

struct vn_command_vkCmdCopyBufferToImage {
    VkCommandBuffer commandBuffer;
    VkBuffer srcBuffer;
    VkImage dstImage;
    VkImageLayout dstImageLayout;
    uint32_t regionCount;
    const VkBufferImageCopy* pRegions;
};

struct vn_command_vkCmdCopyImageToBuffer {
    VkCommandBuffer commandBuffer;
    VkImage srcImage;
    VkImageLayout srcImageLayout;
    VkBuffer dstBuffer;
    uint32_t regionCount;
    const VkBufferImageCopy* pRegions;
};

struct vn_command_vkCmdUpdateBuffer {
    VkCommandBuffer commandBuffer;
    VkBuffer dstBuffer;
    VkDeviceSize dstOffset;
    VkDeviceSize dataSize;
    const void* pData;
};

struct vn_command_vkCmdFillBuffer {
    VkCommandBuffer commandBuffer;
    VkBuffer dstBuffer;
    VkDeviceSize dstOffset;
    VkDeviceSize size;
    uint32_t data;
};

struct vn_command_vkCmdClearColorImage {
    VkCommandBuffer commandBuffer;
    VkImage image;
    VkImageLayout imageLayout;
    const VkClearColorValue* pColor;
    uint32_t rangeCount;
    const VkImageSubresourceRange* pRanges;
};

struct vn_command_vkCmdClearDepthStencilImage {
    VkCommandBuffer commandBuffer;
    VkImage image;
    VkImageLayout imageLayout;
    const VkClearDepthStencilValue* pDepthStencil;
    uint32_t rangeCount;
    const VkImageSubresourceRange* pRanges;
};

struct vn_command_vkCmdClearAttachments {
    VkCommandBuffer commandBuffer;
    uint32_t attachmentCount;
    const VkClearAttachment* pAttachments;
    uint32_t rectCount;
    const VkClearRect* pRects;
};

struct vn_command_vkCmdResolveImage {
    VkCommandBuffer commandBuffer;
    VkImage srcImage;
    VkImageLayout srcImageLayout;
    VkImage dstImage;
    VkImageLayout dstImageLayout;
    uint32_t regionCount;
    const VkImageResolve* pRegions;
};

struct vn_command_vkCmdSetEvent {
    VkCommandBuffer commandBuffer;
    VkEvent event;
    VkPipelineStageFlags stageMask;
};

struct vn_command_vkCmdResetEvent {
    VkCommandBuffer commandBuffer;
    VkEvent event;
    VkPipelineStageFlags stageMask;
};

struct vn_command_vkCmdWaitEvents {
    VkCommandBuffer commandBuffer;
    uint32_t eventCount;
    const VkEvent* pEvents;
    VkPipelineStageFlags srcStageMask;
    VkPipelineStageFlags dstStageMask;
    uint32_t memoryBarrierCount;
    const VkMemoryBarrier* pMemoryBarriers;
    uint32_t bufferMemoryBarrierCount;
    const VkBufferMemoryBarrier* pBufferMemoryBarriers;
    uint32_t imageMemoryBarrierCount;
    const VkImageMemoryBarrier* pImageMemoryBarriers;
};

struct vn_command_vkCmdPipelineBarrier {
    VkCommandBuffer commandBuffer;
    VkPipelineStageFlags srcStageMask;
    VkPipelineStageFlags dstStageMask;
    VkDependencyFlags dependencyFlags;
    uint32_t memoryBarrierCount;
    const VkMemoryBarrier* pMemoryBarriers;
    uint32_t bufferMemoryBarrierCount;
    const VkBufferMemoryBarrier* pBufferMemoryBarriers;
    uint32_t imageMemoryBarrierCount;
    const VkImageMemoryBarrier* pImageMemoryBarriers;
};

struct vn_command_vkCmdBeginQuery {
    VkCommandBuffer commandBuffer;
    VkQueryPool queryPool;
    uint32_t query;
    VkQueryControlFlags flags;
};

struct vn_command_vkCmdEndQuery {
    VkCommandBuffer commandBuffer;
    VkQueryPool queryPool;
    uint32_t query;
};

struct vn_command_vkCmdResetQueryPool {
    VkCommandBuffer commandBuffer;
    VkQueryPool queryPool;
    uint32_t firstQuery;
    uint32_t queryCount;
};

struct vn_command_vkCmdWriteTimestamp {
    VkCommandBuffer commandBuffer;
    VkPipelineStageFlagBits pipelineStage;
    VkQueryPool queryPool;
    uint32_t query;
};

struct vn_command_vkCmdCopyQueryPoolResults {
    VkCommandBuffer commandBuffer;
    VkQueryPool queryPool;
    uint32_t firstQuery;
    uint32_t queryCount;
    VkBuffer dstBuffer;
    VkDeviceSize dstOffset;
    VkDeviceSize stride;
    VkQueryResultFlags flags;
};

struct vn_command_vkCmdPushConstants {
    VkCommandBuffer commandBuffer;
    VkPipelineLayout layout;
    VkShaderStageFlags stageFlags;
    uint32_t offset;
    uint32_t size;
    const void* pValues;
};

struct vn_command_vkCmdBeginRenderPass {
    VkCommandBuffer commandBuffer;
    const VkRenderPassBeginInfo* pRenderPassBegin;
    VkSubpassContents contents;
};

struct vn_command_vkCmdNextSubpass {
    VkCommandBuffer commandBuffer;
    VkSubpassContents contents;
};

struct vn_command_vkCmdEndRenderPass {
    VkCommandBuffer commandBuffer;
};

struct vn_command_vkCmdExecuteCommands {
    VkCommandBuffer commandBuffer;
    uint32_t commandBufferCount;
    const VkCommandBuffer* pCommandBuffers;
};

struct vn_command_vkGetPhysicalDeviceFeatures2 {
    VkPhysicalDevice physicalDevice;
    VkPhysicalDeviceFeatures2* pFeatures;
};

struct vn_command_vkGetPhysicalDeviceProperties2 {
    VkPhysicalDevice physicalDevice;
    VkPhysicalDeviceProperties2* pProperties;
};

struct vn_command_vkGetPhysicalDeviceFormatProperties2 {
    VkPhysicalDevice physicalDevice;
    VkFormat format;
    VkFormatProperties2* pFormatProperties;
};

struct vn_command_vkGetPhysicalDeviceImageFormatProperties2 {
    VkPhysicalDevice physicalDevice;
    const VkPhysicalDeviceImageFormatInfo2* pImageFormatInfo;
    VkImageFormatProperties2* pImageFormatProperties;

    VkResult ret;
};

struct vn_command_vkGetPhysicalDeviceQueueFamilyProperties2 {
    VkPhysicalDevice physicalDevice;
    uint32_t* pQueueFamilyPropertyCount;
    VkQueueFamilyProperties2* pQueueFamilyProperties;
};

struct vn_command_vkGetPhysicalDeviceMemoryProperties2 {
    VkPhysicalDevice physicalDevice;
    VkPhysicalDeviceMemoryProperties2* pMemoryProperties;
};

struct vn_command_vkGetPhysicalDeviceSparseImageFormatProperties2 {
    VkPhysicalDevice physicalDevice;
    const VkPhysicalDeviceSparseImageFormatInfo2* pFormatInfo;
    uint32_t* pPropertyCount;
    VkSparseImageFormatProperties2* pProperties;
};

struct vn_command_vkTrimCommandPool {
    VkDevice device;
    VkCommandPool commandPool;
    VkCommandPoolTrimFlags flags;
};

struct vn_command_vkGetPhysicalDeviceExternalBufferProperties {
    VkPhysicalDevice physicalDevice;
    const VkPhysicalDeviceExternalBufferInfo* pExternalBufferInfo;
    VkExternalBufferProperties* pExternalBufferProperties;
};

struct vn_command_vkGetPhysicalDeviceExternalSemaphoreProperties {
    VkPhysicalDevice physicalDevice;
    const VkPhysicalDeviceExternalSemaphoreInfo* pExternalSemaphoreInfo;
    VkExternalSemaphoreProperties* pExternalSemaphoreProperties;
};

struct vn_command_vkGetPhysicalDeviceExternalFenceProperties {
    VkPhysicalDevice physicalDevice;
    const VkPhysicalDeviceExternalFenceInfo* pExternalFenceInfo;
    VkExternalFenceProperties* pExternalFenceProperties;
};

struct vn_command_vkEnumeratePhysicalDeviceGroups {
    VkInstance instance;
    uint32_t* pPhysicalDeviceGroupCount;
    VkPhysicalDeviceGroupProperties* pPhysicalDeviceGroupProperties;

    VkResult ret;
};

struct vn_command_vkGetDeviceGroupPeerMemoryFeatures {
    VkDevice device;
    uint32_t heapIndex;
    uint32_t localDeviceIndex;
    uint32_t remoteDeviceIndex;
    VkPeerMemoryFeatureFlags* pPeerMemoryFeatures;
};

struct vn_command_vkBindBufferMemory2 {
    VkDevice device;
    uint32_t bindInfoCount;
    const VkBindBufferMemoryInfo* pBindInfos;

    VkResult ret;
};

struct vn_command_vkBindImageMemory2 {
    VkDevice device;
    uint32_t bindInfoCount;
    const VkBindImageMemoryInfo* pBindInfos;

    VkResult ret;
};

struct vn_command_vkCmdSetDeviceMask {
    VkCommandBuffer commandBuffer;
    uint32_t deviceMask;
};

struct vn_command_vkCmdDispatchBase {
    VkCommandBuffer commandBuffer;
    uint32_t baseGroupX;
    uint32_t baseGroupY;
    uint32_t baseGroupZ;
    uint32_t groupCountX;
    uint32_t groupCountY;
    uint32_t groupCountZ;
};

struct vn_command_vkCreateDescriptorUpdateTemplate {
    VkDevice device;
    const VkDescriptorUpdateTemplateCreateInfo* pCreateInfo;
    const VkAllocationCallbacks* pAllocator;
    VkDescriptorUpdateTemplate* pDescriptorUpdateTemplate;

    VkResult ret;
};

struct vn_command_vkDestroyDescriptorUpdateTemplate {
    VkDevice device;
    VkDescriptorUpdateTemplate descriptorUpdateTemplate;
    const VkAllocationCallbacks* pAllocator;
};

struct vn_command_vkUpdateDescriptorSetWithTemplate {
    VkDevice device;
    VkDescriptorSet descriptorSet;
    VkDescriptorUpdateTemplate descriptorUpdateTemplate;
    const void* pData;
};

struct vn_command_vkGetBufferMemoryRequirements2 {
    VkDevice device;
    const VkBufferMemoryRequirementsInfo2* pInfo;
    VkMemoryRequirements2* pMemoryRequirements;
};

struct vn_command_vkGetImageMemoryRequirements2 {
    VkDevice device;
    const VkImageMemoryRequirementsInfo2* pInfo;
    VkMemoryRequirements2* pMemoryRequirements;
};

struct vn_command_vkGetImageSparseMemoryRequirements2 {
    VkDevice device;
    const VkImageSparseMemoryRequirementsInfo2* pInfo;
    uint32_t* pSparseMemoryRequirementCount;
    VkSparseImageMemoryRequirements2* pSparseMemoryRequirements;
};

struct vn_command_vkCreateSamplerYcbcrConversion {
    VkDevice device;
    const VkSamplerYcbcrConversionCreateInfo* pCreateInfo;
    const VkAllocationCallbacks* pAllocator;
    VkSamplerYcbcrConversion* pYcbcrConversion;

    VkResult ret;
};

struct vn_command_vkDestroySamplerYcbcrConversion {
    VkDevice device;
    VkSamplerYcbcrConversion ycbcrConversion;
    const VkAllocationCallbacks* pAllocator;
};

struct vn_command_vkGetDeviceQueue2 {
    VkDevice device;
    const VkDeviceQueueInfo2* pQueueInfo;
    VkQueue* pQueue;
};

struct vn_command_vkGetDescriptorSetLayoutSupport {
    VkDevice device;
    const VkDescriptorSetLayoutCreateInfo* pCreateInfo;
    VkDescriptorSetLayoutSupport* pSupport;
};

struct vn_command_vkCreateRenderPass2 {
    VkDevice device;
    const VkRenderPassCreateInfo2* pCreateInfo;
    const VkAllocationCallbacks* pAllocator;
    VkRenderPass* pRenderPass;

    VkResult ret;
};

struct vn_command_vkCmdBeginRenderPass2 {
    VkCommandBuffer commandBuffer;
    const VkRenderPassBeginInfo* pRenderPassBegin;
    const VkSubpassBeginInfo* pSubpassBeginInfo;
};

struct vn_command_vkCmdNextSubpass2 {
    VkCommandBuffer commandBuffer;
    const VkSubpassBeginInfo* pSubpassBeginInfo;
    const VkSubpassEndInfo* pSubpassEndInfo;
};

struct vn_command_vkCmdEndRenderPass2 {
    VkCommandBuffer commandBuffer;
    const VkSubpassEndInfo* pSubpassEndInfo;
};

struct vn_command_vkGetSemaphoreCounterValue {
    VkDevice device;
    VkSemaphore semaphore;
    uint64_t* pValue;

    VkResult ret;
};

struct vn_command_vkWaitSemaphores {
    VkDevice device;
    const VkSemaphoreWaitInfo* pWaitInfo;
    uint64_t timeout;

    VkResult ret;
};

struct vn_command_vkSignalSemaphore {
    VkDevice device;
    const VkSemaphoreSignalInfo* pSignalInfo;

    VkResult ret;
};

struct vn_command_vkCmdDrawIndirectCount {
    VkCommandBuffer commandBuffer;
    VkBuffer buffer;
    VkDeviceSize offset;
    VkBuffer countBuffer;
    VkDeviceSize countBufferOffset;
    uint32_t maxDrawCount;
    uint32_t stride;
};

struct vn_command_vkCmdDrawIndexedIndirectCount {
    VkCommandBuffer commandBuffer;
    VkBuffer buffer;
    VkDeviceSize offset;
    VkBuffer countBuffer;
    VkDeviceSize countBufferOffset;
    uint32_t maxDrawCount;
    uint32_t stride;
};

struct vn_command_vkCmdBindTransformFeedbackBuffersEXT {
    VkCommandBuffer commandBuffer;
    uint32_t firstBinding;
    uint32_t bindingCount;
    const VkBuffer* pBuffers;
    const VkDeviceSize* pOffsets;
    const VkDeviceSize* pSizes;
};

struct vn_command_vkCmdBeginTransformFeedbackEXT {
    VkCommandBuffer commandBuffer;
    uint32_t firstCounterBuffer;
    uint32_t counterBufferCount;
    const VkBuffer* pCounterBuffers;
    const VkDeviceSize* pCounterBufferOffsets;
};

struct vn_command_vkCmdEndTransformFeedbackEXT {
    VkCommandBuffer commandBuffer;
    uint32_t firstCounterBuffer;
    uint32_t counterBufferCount;
    const VkBuffer* pCounterBuffers;
    const VkDeviceSize* pCounterBufferOffsets;
};

struct vn_command_vkCmdBeginQueryIndexedEXT {
    VkCommandBuffer commandBuffer;
    VkQueryPool queryPool;
    uint32_t query;
    VkQueryControlFlags flags;
    uint32_t index;
};

struct vn_command_vkCmdEndQueryIndexedEXT {
    VkCommandBuffer commandBuffer;
    VkQueryPool queryPool;
    uint32_t query;
    uint32_t index;
};

struct vn_command_vkCmdDrawIndirectByteCountEXT {
    VkCommandBuffer commandBuffer;
    uint32_t instanceCount;
    uint32_t firstInstance;
    VkBuffer counterBuffer;
    VkDeviceSize counterBufferOffset;
    uint32_t counterOffset;
    uint32_t vertexStride;
};

struct vn_command_vkGetImageDrmFormatModifierPropertiesEXT {
    VkDevice device;
    VkImage image;
    VkImageDrmFormatModifierPropertiesEXT* pProperties;

    VkResult ret;
};

struct vn_command_vkGetBufferOpaqueCaptureAddress {
    VkDevice device;
    const VkBufferDeviceAddressInfo* pInfo;

    uint64_t ret;
};

struct vn_command_vkGetBufferDeviceAddress {
    VkDevice device;
    const VkBufferDeviceAddressInfo* pInfo;

    VkDeviceAddress ret;
};

struct vn_command_vkGetDeviceMemoryOpaqueCaptureAddress {
    VkDevice device;
    const VkDeviceMemoryOpaqueCaptureAddressInfo* pInfo;

    uint64_t ret;
};

struct vn_command_vkSetReplyCommandStreamMESA {
    const VkCommandStreamDescriptionMESA* pStream;
};

struct vn_command_vkSeekReplyCommandStreamMESA {
    size_t position;
};

struct vn_command_vkExecuteCommandStreamsMESA {
    uint32_t streamCount;
    const VkCommandStreamDescriptionMESA* pStreams;
    const size_t* pReplyPositions;
    uint32_t dependencyCount;
    const VkCommandStreamDependencyMESA* pDependencies;
    VkCommandStreamExecutionFlagsMESA flags;
};

struct vn_command_vkCreateRingMESA {
    uint64_t ring;
    const VkRingCreateInfoMESA* pCreateInfo;
};

struct vn_command_vkDestroyRingMESA {
    uint64_t ring;
};

struct vn_command_vkNotifyRingMESA {
    uint64_t ring;
    uint32_t seqno;
    VkRingNotifyFlagsMESA flags;
};

struct vn_command_vkWriteRingExtraMESA {
    uint64_t ring;
    size_t offset;
    uint32_t value;
};

struct vn_dispatch_context {
    void *data;
    void (*debug_log)(struct vn_dispatch_context *ctx, const char *msg);

    struct vn_cs_encoder *encoder;
    struct vn_cs_decoder *decoder;

    void (*dispatch_vkCreateInstance)(struct vn_dispatch_context *ctx, struct vn_command_vkCreateInstance *args);
    void (*dispatch_vkDestroyInstance)(struct vn_dispatch_context *ctx, struct vn_command_vkDestroyInstance *args);
    void (*dispatch_vkEnumeratePhysicalDevices)(struct vn_dispatch_context *ctx, struct vn_command_vkEnumeratePhysicalDevices *args);
    void (*dispatch_vkGetDeviceProcAddr)(struct vn_dispatch_context *ctx, struct vn_command_vkGetDeviceProcAddr *args);
    void (*dispatch_vkGetInstanceProcAddr)(struct vn_dispatch_context *ctx, struct vn_command_vkGetInstanceProcAddr *args);
    void (*dispatch_vkGetPhysicalDeviceProperties)(struct vn_dispatch_context *ctx, struct vn_command_vkGetPhysicalDeviceProperties *args);
    void (*dispatch_vkGetPhysicalDeviceQueueFamilyProperties)(struct vn_dispatch_context *ctx, struct vn_command_vkGetPhysicalDeviceQueueFamilyProperties *args);
    void (*dispatch_vkGetPhysicalDeviceMemoryProperties)(struct vn_dispatch_context *ctx, struct vn_command_vkGetPhysicalDeviceMemoryProperties *args);
    void (*dispatch_vkGetPhysicalDeviceFeatures)(struct vn_dispatch_context *ctx, struct vn_command_vkGetPhysicalDeviceFeatures *args);
    void (*dispatch_vkGetPhysicalDeviceFormatProperties)(struct vn_dispatch_context *ctx, struct vn_command_vkGetPhysicalDeviceFormatProperties *args);
    void (*dispatch_vkGetPhysicalDeviceImageFormatProperties)(struct vn_dispatch_context *ctx, struct vn_command_vkGetPhysicalDeviceImageFormatProperties *args);
    void (*dispatch_vkCreateDevice)(struct vn_dispatch_context *ctx, struct vn_command_vkCreateDevice *args);
    void (*dispatch_vkDestroyDevice)(struct vn_dispatch_context *ctx, struct vn_command_vkDestroyDevice *args);
    void (*dispatch_vkEnumerateInstanceVersion)(struct vn_dispatch_context *ctx, struct vn_command_vkEnumerateInstanceVersion *args);
    void (*dispatch_vkEnumerateInstanceLayerProperties)(struct vn_dispatch_context *ctx, struct vn_command_vkEnumerateInstanceLayerProperties *args);
    void (*dispatch_vkEnumerateInstanceExtensionProperties)(struct vn_dispatch_context *ctx, struct vn_command_vkEnumerateInstanceExtensionProperties *args);
    void (*dispatch_vkEnumerateDeviceLayerProperties)(struct vn_dispatch_context *ctx, struct vn_command_vkEnumerateDeviceLayerProperties *args);
    void (*dispatch_vkEnumerateDeviceExtensionProperties)(struct vn_dispatch_context *ctx, struct vn_command_vkEnumerateDeviceExtensionProperties *args);
    void (*dispatch_vkGetDeviceQueue)(struct vn_dispatch_context *ctx, struct vn_command_vkGetDeviceQueue *args);
    void (*dispatch_vkQueueSubmit)(struct vn_dispatch_context *ctx, struct vn_command_vkQueueSubmit *args);
    void (*dispatch_vkQueueWaitIdle)(struct vn_dispatch_context *ctx, struct vn_command_vkQueueWaitIdle *args);
    void (*dispatch_vkDeviceWaitIdle)(struct vn_dispatch_context *ctx, struct vn_command_vkDeviceWaitIdle *args);
    void (*dispatch_vkAllocateMemory)(struct vn_dispatch_context *ctx, struct vn_command_vkAllocateMemory *args);
    void (*dispatch_vkFreeMemory)(struct vn_dispatch_context *ctx, struct vn_command_vkFreeMemory *args);
    void (*dispatch_vkMapMemory)(struct vn_dispatch_context *ctx, struct vn_command_vkMapMemory *args);
    void (*dispatch_vkUnmapMemory)(struct vn_dispatch_context *ctx, struct vn_command_vkUnmapMemory *args);
    void (*dispatch_vkFlushMappedMemoryRanges)(struct vn_dispatch_context *ctx, struct vn_command_vkFlushMappedMemoryRanges *args);
    void (*dispatch_vkInvalidateMappedMemoryRanges)(struct vn_dispatch_context *ctx, struct vn_command_vkInvalidateMappedMemoryRanges *args);
    void (*dispatch_vkGetDeviceMemoryCommitment)(struct vn_dispatch_context *ctx, struct vn_command_vkGetDeviceMemoryCommitment *args);
    void (*dispatch_vkGetBufferMemoryRequirements)(struct vn_dispatch_context *ctx, struct vn_command_vkGetBufferMemoryRequirements *args);
    void (*dispatch_vkBindBufferMemory)(struct vn_dispatch_context *ctx, struct vn_command_vkBindBufferMemory *args);
    void (*dispatch_vkGetImageMemoryRequirements)(struct vn_dispatch_context *ctx, struct vn_command_vkGetImageMemoryRequirements *args);
    void (*dispatch_vkBindImageMemory)(struct vn_dispatch_context *ctx, struct vn_command_vkBindImageMemory *args);
    void (*dispatch_vkGetImageSparseMemoryRequirements)(struct vn_dispatch_context *ctx, struct vn_command_vkGetImageSparseMemoryRequirements *args);
    void (*dispatch_vkGetPhysicalDeviceSparseImageFormatProperties)(struct vn_dispatch_context *ctx, struct vn_command_vkGetPhysicalDeviceSparseImageFormatProperties *args);
    void (*dispatch_vkQueueBindSparse)(struct vn_dispatch_context *ctx, struct vn_command_vkQueueBindSparse *args);
    void (*dispatch_vkCreateFence)(struct vn_dispatch_context *ctx, struct vn_command_vkCreateFence *args);
    void (*dispatch_vkDestroyFence)(struct vn_dispatch_context *ctx, struct vn_command_vkDestroyFence *args);
    void (*dispatch_vkResetFences)(struct vn_dispatch_context *ctx, struct vn_command_vkResetFences *args);
    void (*dispatch_vkGetFenceStatus)(struct vn_dispatch_context *ctx, struct vn_command_vkGetFenceStatus *args);
    void (*dispatch_vkWaitForFences)(struct vn_dispatch_context *ctx, struct vn_command_vkWaitForFences *args);
    void (*dispatch_vkCreateSemaphore)(struct vn_dispatch_context *ctx, struct vn_command_vkCreateSemaphore *args);
    void (*dispatch_vkDestroySemaphore)(struct vn_dispatch_context *ctx, struct vn_command_vkDestroySemaphore *args);
    void (*dispatch_vkCreateEvent)(struct vn_dispatch_context *ctx, struct vn_command_vkCreateEvent *args);
    void (*dispatch_vkDestroyEvent)(struct vn_dispatch_context *ctx, struct vn_command_vkDestroyEvent *args);
    void (*dispatch_vkGetEventStatus)(struct vn_dispatch_context *ctx, struct vn_command_vkGetEventStatus *args);
    void (*dispatch_vkSetEvent)(struct vn_dispatch_context *ctx, struct vn_command_vkSetEvent *args);
    void (*dispatch_vkResetEvent)(struct vn_dispatch_context *ctx, struct vn_command_vkResetEvent *args);
    void (*dispatch_vkCreateQueryPool)(struct vn_dispatch_context *ctx, struct vn_command_vkCreateQueryPool *args);
    void (*dispatch_vkDestroyQueryPool)(struct vn_dispatch_context *ctx, struct vn_command_vkDestroyQueryPool *args);
    void (*dispatch_vkGetQueryPoolResults)(struct vn_dispatch_context *ctx, struct vn_command_vkGetQueryPoolResults *args);
    void (*dispatch_vkResetQueryPool)(struct vn_dispatch_context *ctx, struct vn_command_vkResetQueryPool *args);
    void (*dispatch_vkCreateBuffer)(struct vn_dispatch_context *ctx, struct vn_command_vkCreateBuffer *args);
    void (*dispatch_vkDestroyBuffer)(struct vn_dispatch_context *ctx, struct vn_command_vkDestroyBuffer *args);
    void (*dispatch_vkCreateBufferView)(struct vn_dispatch_context *ctx, struct vn_command_vkCreateBufferView *args);
    void (*dispatch_vkDestroyBufferView)(struct vn_dispatch_context *ctx, struct vn_command_vkDestroyBufferView *args);
    void (*dispatch_vkCreateImage)(struct vn_dispatch_context *ctx, struct vn_command_vkCreateImage *args);
    void (*dispatch_vkDestroyImage)(struct vn_dispatch_context *ctx, struct vn_command_vkDestroyImage *args);
    void (*dispatch_vkGetImageSubresourceLayout)(struct vn_dispatch_context *ctx, struct vn_command_vkGetImageSubresourceLayout *args);
    void (*dispatch_vkCreateImageView)(struct vn_dispatch_context *ctx, struct vn_command_vkCreateImageView *args);
    void (*dispatch_vkDestroyImageView)(struct vn_dispatch_context *ctx, struct vn_command_vkDestroyImageView *args);
    void (*dispatch_vkCreateShaderModule)(struct vn_dispatch_context *ctx, struct vn_command_vkCreateShaderModule *args);
    void (*dispatch_vkDestroyShaderModule)(struct vn_dispatch_context *ctx, struct vn_command_vkDestroyShaderModule *args);
    void (*dispatch_vkCreatePipelineCache)(struct vn_dispatch_context *ctx, struct vn_command_vkCreatePipelineCache *args);
    void (*dispatch_vkDestroyPipelineCache)(struct vn_dispatch_context *ctx, struct vn_command_vkDestroyPipelineCache *args);
    void (*dispatch_vkGetPipelineCacheData)(struct vn_dispatch_context *ctx, struct vn_command_vkGetPipelineCacheData *args);
    void (*dispatch_vkMergePipelineCaches)(struct vn_dispatch_context *ctx, struct vn_command_vkMergePipelineCaches *args);
    void (*dispatch_vkCreateGraphicsPipelines)(struct vn_dispatch_context *ctx, struct vn_command_vkCreateGraphicsPipelines *args);
    void (*dispatch_vkCreateComputePipelines)(struct vn_dispatch_context *ctx, struct vn_command_vkCreateComputePipelines *args);
    void (*dispatch_vkDestroyPipeline)(struct vn_dispatch_context *ctx, struct vn_command_vkDestroyPipeline *args);
    void (*dispatch_vkCreatePipelineLayout)(struct vn_dispatch_context *ctx, struct vn_command_vkCreatePipelineLayout *args);
    void (*dispatch_vkDestroyPipelineLayout)(struct vn_dispatch_context *ctx, struct vn_command_vkDestroyPipelineLayout *args);
    void (*dispatch_vkCreateSampler)(struct vn_dispatch_context *ctx, struct vn_command_vkCreateSampler *args);
    void (*dispatch_vkDestroySampler)(struct vn_dispatch_context *ctx, struct vn_command_vkDestroySampler *args);
    void (*dispatch_vkCreateDescriptorSetLayout)(struct vn_dispatch_context *ctx, struct vn_command_vkCreateDescriptorSetLayout *args);
    void (*dispatch_vkDestroyDescriptorSetLayout)(struct vn_dispatch_context *ctx, struct vn_command_vkDestroyDescriptorSetLayout *args);
    void (*dispatch_vkCreateDescriptorPool)(struct vn_dispatch_context *ctx, struct vn_command_vkCreateDescriptorPool *args);
    void (*dispatch_vkDestroyDescriptorPool)(struct vn_dispatch_context *ctx, struct vn_command_vkDestroyDescriptorPool *args);
    void (*dispatch_vkResetDescriptorPool)(struct vn_dispatch_context *ctx, struct vn_command_vkResetDescriptorPool *args);
    void (*dispatch_vkAllocateDescriptorSets)(struct vn_dispatch_context *ctx, struct vn_command_vkAllocateDescriptorSets *args);
    void (*dispatch_vkFreeDescriptorSets)(struct vn_dispatch_context *ctx, struct vn_command_vkFreeDescriptorSets *args);
    void (*dispatch_vkUpdateDescriptorSets)(struct vn_dispatch_context *ctx, struct vn_command_vkUpdateDescriptorSets *args);
    void (*dispatch_vkCreateFramebuffer)(struct vn_dispatch_context *ctx, struct vn_command_vkCreateFramebuffer *args);
    void (*dispatch_vkDestroyFramebuffer)(struct vn_dispatch_context *ctx, struct vn_command_vkDestroyFramebuffer *args);
    void (*dispatch_vkCreateRenderPass)(struct vn_dispatch_context *ctx, struct vn_command_vkCreateRenderPass *args);
    void (*dispatch_vkDestroyRenderPass)(struct vn_dispatch_context *ctx, struct vn_command_vkDestroyRenderPass *args);
    void (*dispatch_vkGetRenderAreaGranularity)(struct vn_dispatch_context *ctx, struct vn_command_vkGetRenderAreaGranularity *args);
    void (*dispatch_vkCreateCommandPool)(struct vn_dispatch_context *ctx, struct vn_command_vkCreateCommandPool *args);
    void (*dispatch_vkDestroyCommandPool)(struct vn_dispatch_context *ctx, struct vn_command_vkDestroyCommandPool *args);
    void (*dispatch_vkResetCommandPool)(struct vn_dispatch_context *ctx, struct vn_command_vkResetCommandPool *args);
    void (*dispatch_vkAllocateCommandBuffers)(struct vn_dispatch_context *ctx, struct vn_command_vkAllocateCommandBuffers *args);
    void (*dispatch_vkFreeCommandBuffers)(struct vn_dispatch_context *ctx, struct vn_command_vkFreeCommandBuffers *args);
    void (*dispatch_vkBeginCommandBuffer)(struct vn_dispatch_context *ctx, struct vn_command_vkBeginCommandBuffer *args);
    void (*dispatch_vkEndCommandBuffer)(struct vn_dispatch_context *ctx, struct vn_command_vkEndCommandBuffer *args);
    void (*dispatch_vkResetCommandBuffer)(struct vn_dispatch_context *ctx, struct vn_command_vkResetCommandBuffer *args);
    void (*dispatch_vkCmdBindPipeline)(struct vn_dispatch_context *ctx, struct vn_command_vkCmdBindPipeline *args);
    void (*dispatch_vkCmdSetViewport)(struct vn_dispatch_context *ctx, struct vn_command_vkCmdSetViewport *args);
    void (*dispatch_vkCmdSetScissor)(struct vn_dispatch_context *ctx, struct vn_command_vkCmdSetScissor *args);
    void (*dispatch_vkCmdSetLineWidth)(struct vn_dispatch_context *ctx, struct vn_command_vkCmdSetLineWidth *args);
    void (*dispatch_vkCmdSetDepthBias)(struct vn_dispatch_context *ctx, struct vn_command_vkCmdSetDepthBias *args);
    void (*dispatch_vkCmdSetBlendConstants)(struct vn_dispatch_context *ctx, struct vn_command_vkCmdSetBlendConstants *args);
    void (*dispatch_vkCmdSetDepthBounds)(struct vn_dispatch_context *ctx, struct vn_command_vkCmdSetDepthBounds *args);
    void (*dispatch_vkCmdSetStencilCompareMask)(struct vn_dispatch_context *ctx, struct vn_command_vkCmdSetStencilCompareMask *args);
    void (*dispatch_vkCmdSetStencilWriteMask)(struct vn_dispatch_context *ctx, struct vn_command_vkCmdSetStencilWriteMask *args);
    void (*dispatch_vkCmdSetStencilReference)(struct vn_dispatch_context *ctx, struct vn_command_vkCmdSetStencilReference *args);
    void (*dispatch_vkCmdBindDescriptorSets)(struct vn_dispatch_context *ctx, struct vn_command_vkCmdBindDescriptorSets *args);
    void (*dispatch_vkCmdBindIndexBuffer)(struct vn_dispatch_context *ctx, struct vn_command_vkCmdBindIndexBuffer *args);
    void (*dispatch_vkCmdBindVertexBuffers)(struct vn_dispatch_context *ctx, struct vn_command_vkCmdBindVertexBuffers *args);
    void (*dispatch_vkCmdDraw)(struct vn_dispatch_context *ctx, struct vn_command_vkCmdDraw *args);
    void (*dispatch_vkCmdDrawIndexed)(struct vn_dispatch_context *ctx, struct vn_command_vkCmdDrawIndexed *args);
    void (*dispatch_vkCmdDrawIndirect)(struct vn_dispatch_context *ctx, struct vn_command_vkCmdDrawIndirect *args);
    void (*dispatch_vkCmdDrawIndexedIndirect)(struct vn_dispatch_context *ctx, struct vn_command_vkCmdDrawIndexedIndirect *args);
    void (*dispatch_vkCmdDispatch)(struct vn_dispatch_context *ctx, struct vn_command_vkCmdDispatch *args);
    void (*dispatch_vkCmdDispatchIndirect)(struct vn_dispatch_context *ctx, struct vn_command_vkCmdDispatchIndirect *args);
    void (*dispatch_vkCmdCopyBuffer)(struct vn_dispatch_context *ctx, struct vn_command_vkCmdCopyBuffer *args);
    void (*dispatch_vkCmdCopyImage)(struct vn_dispatch_context *ctx, struct vn_command_vkCmdCopyImage *args);
    void (*dispatch_vkCmdBlitImage)(struct vn_dispatch_context *ctx, struct vn_command_vkCmdBlitImage *args);
    void (*dispatch_vkCmdCopyBufferToImage)(struct vn_dispatch_context *ctx, struct vn_command_vkCmdCopyBufferToImage *args);
    void (*dispatch_vkCmdCopyImageToBuffer)(struct vn_dispatch_context *ctx, struct vn_command_vkCmdCopyImageToBuffer *args);
    void (*dispatch_vkCmdUpdateBuffer)(struct vn_dispatch_context *ctx, struct vn_command_vkCmdUpdateBuffer *args);
    void (*dispatch_vkCmdFillBuffer)(struct vn_dispatch_context *ctx, struct vn_command_vkCmdFillBuffer *args);
    void (*dispatch_vkCmdClearColorImage)(struct vn_dispatch_context *ctx, struct vn_command_vkCmdClearColorImage *args);
    void (*dispatch_vkCmdClearDepthStencilImage)(struct vn_dispatch_context *ctx, struct vn_command_vkCmdClearDepthStencilImage *args);
    void (*dispatch_vkCmdClearAttachments)(struct vn_dispatch_context *ctx, struct vn_command_vkCmdClearAttachments *args);
    void (*dispatch_vkCmdResolveImage)(struct vn_dispatch_context *ctx, struct vn_command_vkCmdResolveImage *args);
    void (*dispatch_vkCmdSetEvent)(struct vn_dispatch_context *ctx, struct vn_command_vkCmdSetEvent *args);
    void (*dispatch_vkCmdResetEvent)(struct vn_dispatch_context *ctx, struct vn_command_vkCmdResetEvent *args);
    void (*dispatch_vkCmdWaitEvents)(struct vn_dispatch_context *ctx, struct vn_command_vkCmdWaitEvents *args);
    void (*dispatch_vkCmdPipelineBarrier)(struct vn_dispatch_context *ctx, struct vn_command_vkCmdPipelineBarrier *args);
    void (*dispatch_vkCmdBeginQuery)(struct vn_dispatch_context *ctx, struct vn_command_vkCmdBeginQuery *args);
    void (*dispatch_vkCmdEndQuery)(struct vn_dispatch_context *ctx, struct vn_command_vkCmdEndQuery *args);
    void (*dispatch_vkCmdResetQueryPool)(struct vn_dispatch_context *ctx, struct vn_command_vkCmdResetQueryPool *args);
    void (*dispatch_vkCmdWriteTimestamp)(struct vn_dispatch_context *ctx, struct vn_command_vkCmdWriteTimestamp *args);
    void (*dispatch_vkCmdCopyQueryPoolResults)(struct vn_dispatch_context *ctx, struct vn_command_vkCmdCopyQueryPoolResults *args);
    void (*dispatch_vkCmdPushConstants)(struct vn_dispatch_context *ctx, struct vn_command_vkCmdPushConstants *args);
    void (*dispatch_vkCmdBeginRenderPass)(struct vn_dispatch_context *ctx, struct vn_command_vkCmdBeginRenderPass *args);
    void (*dispatch_vkCmdNextSubpass)(struct vn_dispatch_context *ctx, struct vn_command_vkCmdNextSubpass *args);
    void (*dispatch_vkCmdEndRenderPass)(struct vn_dispatch_context *ctx, struct vn_command_vkCmdEndRenderPass *args);
    void (*dispatch_vkCmdExecuteCommands)(struct vn_dispatch_context *ctx, struct vn_command_vkCmdExecuteCommands *args);
    void (*dispatch_vkGetPhysicalDeviceFeatures2)(struct vn_dispatch_context *ctx, struct vn_command_vkGetPhysicalDeviceFeatures2 *args);
    void (*dispatch_vkGetPhysicalDeviceProperties2)(struct vn_dispatch_context *ctx, struct vn_command_vkGetPhysicalDeviceProperties2 *args);
    void (*dispatch_vkGetPhysicalDeviceFormatProperties2)(struct vn_dispatch_context *ctx, struct vn_command_vkGetPhysicalDeviceFormatProperties2 *args);
    void (*dispatch_vkGetPhysicalDeviceImageFormatProperties2)(struct vn_dispatch_context *ctx, struct vn_command_vkGetPhysicalDeviceImageFormatProperties2 *args);
    void (*dispatch_vkGetPhysicalDeviceQueueFamilyProperties2)(struct vn_dispatch_context *ctx, struct vn_command_vkGetPhysicalDeviceQueueFamilyProperties2 *args);
    void (*dispatch_vkGetPhysicalDeviceMemoryProperties2)(struct vn_dispatch_context *ctx, struct vn_command_vkGetPhysicalDeviceMemoryProperties2 *args);
    void (*dispatch_vkGetPhysicalDeviceSparseImageFormatProperties2)(struct vn_dispatch_context *ctx, struct vn_command_vkGetPhysicalDeviceSparseImageFormatProperties2 *args);
    void (*dispatch_vkTrimCommandPool)(struct vn_dispatch_context *ctx, struct vn_command_vkTrimCommandPool *args);
    void (*dispatch_vkGetPhysicalDeviceExternalBufferProperties)(struct vn_dispatch_context *ctx, struct vn_command_vkGetPhysicalDeviceExternalBufferProperties *args);
    void (*dispatch_vkGetPhysicalDeviceExternalSemaphoreProperties)(struct vn_dispatch_context *ctx, struct vn_command_vkGetPhysicalDeviceExternalSemaphoreProperties *args);
    void (*dispatch_vkGetPhysicalDeviceExternalFenceProperties)(struct vn_dispatch_context *ctx, struct vn_command_vkGetPhysicalDeviceExternalFenceProperties *args);
    void (*dispatch_vkEnumeratePhysicalDeviceGroups)(struct vn_dispatch_context *ctx, struct vn_command_vkEnumeratePhysicalDeviceGroups *args);
    void (*dispatch_vkGetDeviceGroupPeerMemoryFeatures)(struct vn_dispatch_context *ctx, struct vn_command_vkGetDeviceGroupPeerMemoryFeatures *args);
    void (*dispatch_vkBindBufferMemory2)(struct vn_dispatch_context *ctx, struct vn_command_vkBindBufferMemory2 *args);
    void (*dispatch_vkBindImageMemory2)(struct vn_dispatch_context *ctx, struct vn_command_vkBindImageMemory2 *args);
    void (*dispatch_vkCmdSetDeviceMask)(struct vn_dispatch_context *ctx, struct vn_command_vkCmdSetDeviceMask *args);
    void (*dispatch_vkCmdDispatchBase)(struct vn_dispatch_context *ctx, struct vn_command_vkCmdDispatchBase *args);
    void (*dispatch_vkCreateDescriptorUpdateTemplate)(struct vn_dispatch_context *ctx, struct vn_command_vkCreateDescriptorUpdateTemplate *args);
    void (*dispatch_vkDestroyDescriptorUpdateTemplate)(struct vn_dispatch_context *ctx, struct vn_command_vkDestroyDescriptorUpdateTemplate *args);
    void (*dispatch_vkUpdateDescriptorSetWithTemplate)(struct vn_dispatch_context *ctx, struct vn_command_vkUpdateDescriptorSetWithTemplate *args);
    void (*dispatch_vkGetBufferMemoryRequirements2)(struct vn_dispatch_context *ctx, struct vn_command_vkGetBufferMemoryRequirements2 *args);
    void (*dispatch_vkGetImageMemoryRequirements2)(struct vn_dispatch_context *ctx, struct vn_command_vkGetImageMemoryRequirements2 *args);
    void (*dispatch_vkGetImageSparseMemoryRequirements2)(struct vn_dispatch_context *ctx, struct vn_command_vkGetImageSparseMemoryRequirements2 *args);
    void (*dispatch_vkCreateSamplerYcbcrConversion)(struct vn_dispatch_context *ctx, struct vn_command_vkCreateSamplerYcbcrConversion *args);
    void (*dispatch_vkDestroySamplerYcbcrConversion)(struct vn_dispatch_context *ctx, struct vn_command_vkDestroySamplerYcbcrConversion *args);
    void (*dispatch_vkGetDeviceQueue2)(struct vn_dispatch_context *ctx, struct vn_command_vkGetDeviceQueue2 *args);
    void (*dispatch_vkGetDescriptorSetLayoutSupport)(struct vn_dispatch_context *ctx, struct vn_command_vkGetDescriptorSetLayoutSupport *args);
    void (*dispatch_vkCreateRenderPass2)(struct vn_dispatch_context *ctx, struct vn_command_vkCreateRenderPass2 *args);
    void (*dispatch_vkCmdBeginRenderPass2)(struct vn_dispatch_context *ctx, struct vn_command_vkCmdBeginRenderPass2 *args);
    void (*dispatch_vkCmdNextSubpass2)(struct vn_dispatch_context *ctx, struct vn_command_vkCmdNextSubpass2 *args);
    void (*dispatch_vkCmdEndRenderPass2)(struct vn_dispatch_context *ctx, struct vn_command_vkCmdEndRenderPass2 *args);
    void (*dispatch_vkGetSemaphoreCounterValue)(struct vn_dispatch_context *ctx, struct vn_command_vkGetSemaphoreCounterValue *args);
    void (*dispatch_vkWaitSemaphores)(struct vn_dispatch_context *ctx, struct vn_command_vkWaitSemaphores *args);
    void (*dispatch_vkSignalSemaphore)(struct vn_dispatch_context *ctx, struct vn_command_vkSignalSemaphore *args);
    void (*dispatch_vkCmdDrawIndirectCount)(struct vn_dispatch_context *ctx, struct vn_command_vkCmdDrawIndirectCount *args);
    void (*dispatch_vkCmdDrawIndexedIndirectCount)(struct vn_dispatch_context *ctx, struct vn_command_vkCmdDrawIndexedIndirectCount *args);
    void (*dispatch_vkCmdBindTransformFeedbackBuffersEXT)(struct vn_dispatch_context *ctx, struct vn_command_vkCmdBindTransformFeedbackBuffersEXT *args);
    void (*dispatch_vkCmdBeginTransformFeedbackEXT)(struct vn_dispatch_context *ctx, struct vn_command_vkCmdBeginTransformFeedbackEXT *args);
    void (*dispatch_vkCmdEndTransformFeedbackEXT)(struct vn_dispatch_context *ctx, struct vn_command_vkCmdEndTransformFeedbackEXT *args);
    void (*dispatch_vkCmdBeginQueryIndexedEXT)(struct vn_dispatch_context *ctx, struct vn_command_vkCmdBeginQueryIndexedEXT *args);
    void (*dispatch_vkCmdEndQueryIndexedEXT)(struct vn_dispatch_context *ctx, struct vn_command_vkCmdEndQueryIndexedEXT *args);
    void (*dispatch_vkCmdDrawIndirectByteCountEXT)(struct vn_dispatch_context *ctx, struct vn_command_vkCmdDrawIndirectByteCountEXT *args);
    void (*dispatch_vkGetImageDrmFormatModifierPropertiesEXT)(struct vn_dispatch_context *ctx, struct vn_command_vkGetImageDrmFormatModifierPropertiesEXT *args);
    void (*dispatch_vkGetBufferOpaqueCaptureAddress)(struct vn_dispatch_context *ctx, struct vn_command_vkGetBufferOpaqueCaptureAddress *args);
    void (*dispatch_vkGetBufferDeviceAddress)(struct vn_dispatch_context *ctx, struct vn_command_vkGetBufferDeviceAddress *args);
    void (*dispatch_vkGetDeviceMemoryOpaqueCaptureAddress)(struct vn_dispatch_context *ctx, struct vn_command_vkGetDeviceMemoryOpaqueCaptureAddress *args);
    void (*dispatch_vkSetReplyCommandStreamMESA)(struct vn_dispatch_context *ctx, struct vn_command_vkSetReplyCommandStreamMESA *args);
    void (*dispatch_vkSeekReplyCommandStreamMESA)(struct vn_dispatch_context *ctx, struct vn_command_vkSeekReplyCommandStreamMESA *args);
    void (*dispatch_vkExecuteCommandStreamsMESA)(struct vn_dispatch_context *ctx, struct vn_command_vkExecuteCommandStreamsMESA *args);
    void (*dispatch_vkCreateRingMESA)(struct vn_dispatch_context *ctx, struct vn_command_vkCreateRingMESA *args);
    void (*dispatch_vkDestroyRingMESA)(struct vn_dispatch_context *ctx, struct vn_command_vkDestroyRingMESA *args);
    void (*dispatch_vkNotifyRingMESA)(struct vn_dispatch_context *ctx, struct vn_command_vkNotifyRingMESA *args);
    void (*dispatch_vkWriteRingExtraMESA)(struct vn_dispatch_context *ctx, struct vn_command_vkWriteRingExtraMESA *args);
};

#endif /* VN_PROTOCOL_RENDERER_DEFINES_H */
