//
// Created by tangt on 12/10/2020.
//
// Class that represent the swapchain, use for send the render informations to the surface
//

#ifndef GAMEENGINE_SWAPCHAIN_H
#define GAMEENGINE_SWAPCHAIN_H

#include "vulkan/vulkan.hpp"

#include "RenderPass.h"

#define MAX_FRAMES_IN_FLIGHT 2

namespace graphics {

    class LogicalDevice;
    class Vertex;
    class Texture;

    class Swapchain {
    public:
        Swapchain(const LogicalDevice & logicalDevice);

        void initialize();
        void release();
        void recreate();

        const LogicalDevice & getParentLogicalDevice() const;
        const vk::SwapchainKHR & getVkSwapchain() const;
        const std::vector<vk::Image> & getVkSwapchainImage() const;
        const vk::Format & getVkSwapchainFormat() const;
        const vk::Extent2D & getVkSwapchainExtent() const;
        const RenderPass & getRenderPass() const;
        const std::vector<vk::Framebuffer> & getVkFrameBuffers() const;
        const vk::Buffer & getVkVertexBuffer() const;
        const vk::Buffer & getVkIndexBuffer() const;
        const vk::Semaphore & getVkImageAvaibleSemaphore(int iIndex) const;
        const vk::Semaphore & getVkRenderFinishSemaphore(int iIndex) const;
        const vk::Fence & getVkFence(int iIndex) const;
        const vk::Fence & getVkFenceInFlight(int iIndex) const;
        void setVkFenceInFlight(int iIndex, const vk::Fence & fence);
        const vk::DescriptorSet & getVkDescriptorSet(int iIndex) const;

    private:
        void initializeInternal();
        const vk::SurfaceFormatKHR & chooseSwapchainFormat(const std::vector<vk::SurfaceFormatKHR> & formats);
        const vk::PresentModeKHR & chooseSwapchainPrensentMode(const std::vector<vk::PresentModeKHR> & presentModes);
        vk::Extent2D chooseSwapchainExtent(const vk::SurfaceCapabilitiesKHR & capabilities);
        void initializeImageViews(); ///< Must be call after initializeInternal
        void initializeFrameBuffer(); ///< Must be call after renderPass initialization
        void createColorResources();
        void createDepthResources();
        void createVertexBuffer(const std::vector<Vertex> & vertices);
        void createIndexBuffer(const std::vector<uint32_t> & indices);
        void createUniformBuffers();
        void createDescriptorPool();
        void createDescriptorSet(const Texture & texture);
        void initializeSyncObj();

    private:
        const graphics::LogicalDevice & m_parentLogicalDevice;
        RenderPass m_renderPass;

        vk::SwapchainKHR m_swapchain;
        std::vector<vk::Image> m_vImages;
        vk::Format m_format;
        vk::Extent2D m_extent;
        std::vector<vk::ImageView> m_vImageViews;
        std::vector<vk::Framebuffer> m_vFrameBuffer;

        //
        // Color resources
        vk::Image m_colorImage;
        vk::DeviceMemory m_colorMemory;
        vk::ImageView m_colorView;

        //
        // Depth resources
        vk::Image m_depthImage;
        vk::DeviceMemory m_depthMemory;
        vk::ImageView m_depthView;

        //
        // Vertex buffer
        vk::Buffer m_vertexBuffer;
        vk::DeviceMemory m_verterBufferMemory;

        //
        // Index buffer
        vk::Buffer m_indexBuffer;
        vk::DeviceMemory m_indexBufferMemory;

        //
        // Unifom buffer
        std::vector<vk::Buffer> m_uniformBuffers;
        std::vector<vk::DeviceMemory> m_uniformBufferMemories;

        //
        // Descriptor
        vk::DescriptorPool m_descriptorPool;
        std::vector<vk::DescriptorSet> m_descriptorSets;

        //
        // Fence and semaphore
        std::vector<vk::Semaphore> m_imageAvaibleSemaphores;
        std::vector<vk::Semaphore> m_renderFinishSemaphores;
        std::vector<vk::Fence> m_fences;
        std::vector<vk::Fence> m_fencesInFlight;
    };
}

#endif //GAMEENGINE_SWAPCHAIN_H
