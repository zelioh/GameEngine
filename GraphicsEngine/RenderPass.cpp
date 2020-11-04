//
// Created by tangt on 12/10/2020.
//
// Class use for the render pass instancing
//

#include "RenderPass.h"
#include "Swapchain.h"
#include "LogicalDevice.h"
#include "PhysicalDevice.h"

void graphics::RenderPass::initialize(const Swapchain &swapchain)
{
    //
    // Set color attachment
    vk::AttachmentDescription colorAttachement{};
    PhysicalDevice * physicalDevice = PhysicalDevice::getInstance();

    colorAttachement.format = swapchain.getVkSwapchainFormat();
    colorAttachement.samples = physicalDevice->getVkMSSASample();
    colorAttachement.loadOp = vk::AttachmentLoadOp::eClear;
    colorAttachement.storeOp = vk::AttachmentStoreOp::eStore;
    colorAttachement.stencilLoadOp = vk::AttachmentLoadOp::eDontCare;
    colorAttachement.stencilStoreOp = vk::AttachmentStoreOp::eDontCare;
    colorAttachement.initialLayout = vk::ImageLayout::eUndefined;
    colorAttachement.finalLayout = vk::ImageLayout::eColorAttachmentOptimal;

    vk::AttachmentReference colorRef{};

    colorRef.attachment = 0;
    colorRef.layout = vk::ImageLayout::eColorAttachmentOptimal;

    //
    // Set depth attachment
    vk::AttachmentDescription depthAttachment{};

    depthAttachment.format = physicalDevice->findVkSupportedFormat(
                                    {vk::Format::eD32Sfloat, vk::Format::eD32SfloatS8Uint, vk::Format::eD24UnormS8Uint},
                                    vk::ImageTiling::eOptimal,
                                    vk::FormatFeatureFlagBits::eDepthStencilAttachment);

    depthAttachment.samples = physicalDevice->getVkMSSASample();
    depthAttachment.loadOp = vk::AttachmentLoadOp::eClear;
    depthAttachment.storeOp = vk::AttachmentStoreOp::eDontCare;
    depthAttachment.stencilLoadOp = vk::AttachmentLoadOp::eDontCare;
    depthAttachment.stencilStoreOp = vk::AttachmentStoreOp::eDontCare;
    depthAttachment.initialLayout = vk::ImageLayout::eUndefined;
    depthAttachment.finalLayout = vk::ImageLayout::eDepthStencilAttachmentOptimal;

    vk::AttachmentReference depthRef{};

    depthRef.attachment = 1;
    depthRef.layout = vk::ImageLayout::eDepthStencilAttachmentOptimal;

    //
    // Set color resolver
    vk::AttachmentDescription colorAttachmentResolver{};

    colorAttachmentResolver.format = swapchain.getVkSwapchainFormat();
    colorAttachmentResolver.samples = vk::SampleCountFlagBits::e1;
    colorAttachmentResolver.loadOp = vk::AttachmentLoadOp::eDontCare;
    colorAttachmentResolver.storeOp = vk::AttachmentStoreOp::eStore;
    colorAttachmentResolver.stencilStoreOp = vk::AttachmentStoreOp::eDontCare;
    colorAttachmentResolver.stencilLoadOp = vk::AttachmentLoadOp::eDontCare;
    colorAttachmentResolver.initialLayout = vk::ImageLayout::eUndefined;
    colorAttachmentResolver.finalLayout = vk::ImageLayout::ePresentSrcKHR;

    vk::AttachmentReference colorAttachmentResolverRef{};

    colorAttachmentResolverRef.attachment = 2;
    colorAttachmentResolverRef.layout = vk::ImageLayout::eColorAttachmentOptimal;

    //
    // Set subpass
    vk::SubpassDescription subpass{};
    subpass.pipelineBindPoint = vk::PipelineBindPoint::eGraphics;
    subpass.colorAttachmentCount = 1;
    subpass.pColorAttachments = &colorRef;
    subpass.pDepthStencilAttachment = &depthRef;
    subpass.pResolveAttachments = &colorAttachmentResolverRef;

    vk::SubpassDependency dependency{};
    dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
    dependency.dstSubpass = 0;
    dependency.srcStageMask = vk::PipelineStageFlagBits::eColorAttachmentOutput;
    dependency.srcAccessMask = static_cast<vk::AccessFlagBits>(0);
    dependency.dstStageMask = vk::PipelineStageFlagBits::eColorAttachmentOutput;
    dependency.dstAccessMask = vk::AccessFlagBits::eColorAttachmentWrite;

    // Create render pass
    std::array<vk::AttachmentDescription, 3> attachments = {colorAttachement, depthAttachment, colorAttachmentResolver};
    vk::RenderPassCreateInfo renderPassInfo{};

    renderPassInfo.attachmentCount = static_cast<uint32_t>(attachments.size());
    renderPassInfo.pAttachments = attachments.data();
    renderPassInfo.subpassCount = 1;
    renderPassInfo.pSubpasses = &subpass;
    renderPassInfo.dependencyCount = 1;
    renderPassInfo.pDependencies = &dependency;

    m_renderPass = swapchain.getParentLogicalDevice().getVkLogicalDevice().createRenderPass(renderPassInfo);
}

void graphics::RenderPass::release(const Swapchain &swapchain)
{
    swapchain.getParentLogicalDevice().getVkLogicalDevice().destroyRenderPass(m_renderPass);
}

const vk::RenderPass & graphics::RenderPass::getVkRenderPass() const
{
    return m_renderPass;
}