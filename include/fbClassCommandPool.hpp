/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fbClassCommandPool.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Rustam <super.rustamm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/29 16:33:41 by Rustam            #+#    #+#             */
/*   Updated: 2019/12/29 16:37:29 by Rustam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FB_CLASS_COMMAND_POOL_HPP
# define FB_CLASS_COMMAND_POOL_HPP

# include "firebreak.hpp"

class CommandPool
{
	public:
		CommandPool(VkCommandPoolCreateInfo info = {}, VkAllocationCallbacks allocation = {});
		CommandPool(VkAllocationCallbacks allocation) : CommandPool({}, allocation) { }

		VkCommandPool					&getSelf						();
		VkCommandPoolCreateInfo			&getCreateInfo					();
		VkAllocationCallbacks			&getAllocation					();
		VkCommandBufferAllocateInfo		&getCommandBufferAllocateInfo	();
		VkCommandBuffer					&getCommandBuffer				(uint32_t index = 0, uint32_t group = 0);
		std::vector<VkCommandBuffer>	&getCommandBufferGroup			(uint32_t group = 0);
		int32_t 						getErrorCode					();

		void create(Device &device);
		void allocateCommandBuffers(Device &device);
		void freeCommandBuffers(Device &device);

		void beginCommandBuffer(uint32_t index = 0, uint32_t group = 0);
		void beginCommandBufferGroup(uint32_t group = 0);
		void endCommandBuffer(uint32_t index = 0, uint32_t group = 0);
		void endCommandBufferGroup(uint32_t group = 0);
		void resetCommandBuffer(VkCommandBufferResetFlags flags = 0, uint32_t index = 0, uint32_t group = 0);
		void resetCommandBufferGroup(VkCommandBufferResetFlags flags = 0, uint32_t group = 0);
		void cmdCopy(Buffer &srcBuffer, Buffer &dstBuffer, uint32_t regionCount, VkBufferCopy *pRegions, uint32_t index = 0, uint32_t group = 0);
		void cmdPipelineBarrier(VkPipelineStageFlags srcStage, VkPipelineStageFlags dstStage, VkDependencyFlags dependencyFlags,
								uint32_t memoryBarrierCount, VkMemoryBarrier *pMemoryBarriers,
								int32_t bufferMemoryBarrierCount, VkBufferMemoryBarrier *pBufferMemoryBarriers,
								uint32_t imageMemoryBarrierCount, VkImageMemoryBarrier *pImageMemoryBarriers,
								uint32_t index = 0, uint32_t group = 0);
		void cmdFillBuffer(Buffer dstBuffer, VkDeviceSize dstOffset, VkDeviceSize dstSize, uint32_t data, uint32_t index = 0, uint32_t group = 0);
		void cmdUpdateBuffer(Buffer dstBuffer, VkDeviceSize dstOffset, VkDeviceSize dataSize, uint32_t pData, uint32_t index = 0, uint32_t group = 0);
		void cmdClearColorImage(Image dstImage, VkImageLayout imageLayout, VkClearColorValue *pColor,
										uint32_t rangeCount, VkImageSubresourceRange *pRanges, uint32_t index = 0, uint32_t group = 0);
		void cmdClearDepthStencilImage(Image dstImage, VkImageLayout imageLayout, VkClearDepthStencilValue *pDepthStencil, uint32_t rangeCount,
										VkImageSubresourceRange *pRanges, uint32_t index = 0, uint32_t group = 0);
		void cmdCopyBufferToImage(Buffer srcBuffer, Image dstImage, VkImageLayout dstImageLayout, uint32_t regionCount,
									VkBufferImageCopy *pRegions, uint32_t index = 0, uint32_t group = 0);
		void cmdCopyImageToBuffer(Image srcImage, VkImageLayout imageLayout, Buffer dstBuffer, uint32_t regionCount,
								VkBufferImageCopy *pRegions, uint32_t index = 0, uint32_t group = 0);
		void cmdCopyImage(Image srcImage, VkImageLayout srcImageLayout, Image dstImage, VkImageLayout dstImageLayout,
							uint32_t regionCount, VkImageCopy *pRegions, uint32_t index = 0, uint32_t group = 0);

		void reset					(Device &device, VkCommandPoolResetFlags flags = 0);
		void destroy				(Device &device);

		~CommandPool();

	private:
		VkCommandPool				self;
		VkCommandPoolCreateInfo		sCreateInfo;
		VkAllocationCallbacks		sAllocation;
		VkCommandBufferAllocateInfo	sCommandBufferAllocateInfo;
		VkCommandBufferBeginInfo	sCommandBufferBeginInfo;

		std::vector<std::vector<VkCommandBuffer>>	ppCommandBuffers;

		int32_t	codeOfError	= false;
};

#endif