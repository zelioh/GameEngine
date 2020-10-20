//
// Created by tangt on 13/10/2020.
//
// Graphics pipeline implementation, use to bind a shader, viewport, scissor, rasterizer, ... with the command buffer
// TODO: Add more flexibility for creation
//

#ifndef GAMEENGINE_PIPELINE_H
#define GAMEENGINE_PIPELINE_H

#include "vulkan/vulkan.hpp"

namespace graphics {
    class LogicalDevice;
    class Shader;
    class Swapchain;

    class Pipeline
    {
    public:
        Pipeline() = default; ///< Default constructor
        Pipeline(const LogicalDevice & logicalDevice, const Swapchain & swapchain, const Shader & shader); ///< Call initalize

        void initialize(const LogicalDevice & logicalDevice, const Swapchain & swapchain, const Shader & shader); ///< Initalize the pipeline
        void release(const LogicalDevice & logicalDevice);

        const vk::Pipeline & getVkPipeline() const;
        const vk::PipelineLayout & getVkPipelineLayout() const;

    private:
        vk::ShaderModule createShaderModule(const LogicalDevice &logicalDevice, const std::vector<char> & data);

    private:
        vk::Pipeline m_pipeline;
        vk::PipelineLayout m_pipelineLayout;
    };

}

#endif //GAMEENGINE_PIPELINE_H
