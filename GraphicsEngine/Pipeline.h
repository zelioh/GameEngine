//
// Created by tangt on 13/10/2020.
//
// Graphics pipeline implementation, use to bind a shader, viewport, scissor, rasterizer, ... with the command buffer
// TODO: Add more flexibility for creation
//

#ifndef GAMEENGINE_PIPELINE_H
#define GAMEENGINE_PIPELINE_H

#include "vulkan/vulkan.hpp"
#include "Shader.h"

namespace graphics {
    class LogicalDevice;
    class Shader;
    class Swapchain;

    class Pipeline
    {
    public:
        Pipeline() = default; ///< Default constructor
        Pipeline(const Shader & shader); ///< Call initalize

        void initialize(const Shader & shader); ///< Initalize the pipeline
        void initialize();
        void release();

        const vk::Pipeline & getVkPipeline() const;
        const vk::PipelineLayout & getVkPipelineLayout() const;

    private:
        vk::ShaderModule createShaderModule(const std::vector<char> & data);

    private:
        vk::Pipeline m_pipeline;
        vk::PipelineLayout m_pipelineLayout;
        Shader m_shader;
    };

}

#endif //GAMEENGINE_PIPELINE_H
