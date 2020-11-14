//
// Created by tangt on 12/10/2020.
//
// Class that represente the logical device, use for queue and pipeline instancing
//

#ifndef GAMEENGINE_LOGICALDEVICE_H
#define GAMEENGINE_LOGICALDEVICE_H

#include "Queue.h"
#include "CommandPool.h"
#include "public/GraphicsEngine/GraphicsEngine.h"

namespace graphics {

    class PhysicalDevice;
    struct Vertex;

    class GRAPHICS_ENGINE_EXPORT LogicalDevice
    {
    public:
        static LogicalDevice * getInstance();

        void initializeCommandPool();

        void releaseCommandPool();
        void release();

        const vk::Device & getVkLogicalDevice() const;
        const Queue & getGraphicQueue() const;
        const Queue & getPresentQueue() const;

        vk::ImageView createVkImageView(const vk::Image & image,
                                        vk::Format format,
                                        vk::ImageAspectFlags aspect,
                                        uint32_t mipLevel = 1) const;

        void createVkImage(uint32_t width, uint32_t height, uint32_t mipLevel,
                           vk::SampleCountFlagBits numSample,
                           vk::Format format, vk::ImageTiling tiling,
                           vk::ImageUsageFlags usages, vk::MemoryPropertyFlagBits properties,
                           vk::Image & image, vk::DeviceMemory & memory) const;

        void createVkBuffer(vk::DeviceSize size,
                            vk::BufferUsageFlags usages,
                            vk::MemoryPropertyFlags properties,
                            vk::Buffer & buffer,
                            vk::DeviceMemory & memory) const;

        void copyVkBuffer(const vk::Buffer & srcBuffer, const vk::Buffer & dstBuffer, vk::DeviceSize size) const;
        vk::CommandBuffer beginVkSingleTimeBuffer() const;
        void endVkSingleTimeBuffer(const vk::CommandBuffer & commandBuffer) const;

        const vk::DescriptorSetLayout & getDescriptorSetLayout() const;
        const CommandPool & getCommandPool() const;

        void createImage(uint32_t width, uint32_t height, uint32_t mipLevel,
                              vk::SampleCountFlagBits numSample,
                              vk::Format format, vk::ImageTiling tiling,
                              vk::ImageUsageFlags usages, vk::MemoryPropertyFlags properties,
                              vk::Image &image, vk::DeviceMemory &memory) const;
        void transitionImageLayout(vk::Image image, vk::Format format, vk::ImageLayout oldLayout,
                                   vk::ImageLayout newLayout, uint32_t mipLevel) const;
        bool formatHasStencil(vk::Format format) const;
        void copyVkBufferToImage(const vk::Buffer & buffer, const vk::Image & image, uint32_t width, uint32_t height) const;

        void generateMipmap(const vk::Image & image,
                            vk::Format format,
                            uint32_t texWidth, uint32_t texHeight, uint32_t mipLevel) const;

        void createVertexBuffer(vk::Buffer & vertexBuffer, vk::DeviceMemory & memory, const std::vector<graphics::Vertex> & m_vertices) const;
        void createIndexBuffer(vk::Buffer & indexBuffer, vk::DeviceMemory & memory, const std::vector<uint32_t> & m_indices) const;

    private:
        LogicalDevice();

        void initializeInternal();
        void initializeDescriptorLayout();

    private:
        vk::Device m_logicalDevice;
        Queue m_graphicQueue;
        Queue m_presentQueue;
        vk::DescriptorSetLayout m_descriptorLayout;
        CommandPool m_commandPool;
    };

}

#endif //GAMEENGINE_LOGICAL1DEVICE_H
