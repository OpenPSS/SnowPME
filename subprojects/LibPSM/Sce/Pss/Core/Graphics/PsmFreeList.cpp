#include <Sce/Pss/Core/Graphics/PsmFreeList.hpp>
#include <Sce/Pss/Core/System/Handles.hpp>
#include <Sce/Pss/Core/PsmObject.hpp>
#include <Sce/Pss/Core/Graphics/GraphicsObject.hpp>
#include <Sce/Pss/Core/Graphics/VertexBuffer.hpp>
#include <Sce/Pss/Core/Graphics/FrameBuffer.hpp>
#include <Sce/Pss/Core/Graphics/ShaderProgram.hpp>
#include <Sce/Pss/Core/Graphics/GraphicsContext.hpp>
#include <Sce/Pss/Core/Threading/Thread.hpp>

using namespace Sce::Pss::Core::System;
using namespace Sce::Pss::Core::Threading;

namespace Sce::Pss::Core::Graphics {
	std::vector<PsmFree> PsmFreeList::freeList;

	void PsmFreeList::AddEntry(PsmFree freeEntry)
	{
		LOG_FUNCTION();
		LOCK_GUARD_STATIC();
		freeList.push_back(freeEntry);
	}

	void PsmFreeList::FreeHeldObjects()
	{
		ASSERT(Thread::IsMainThread());
		
		LOG_FUNCTION();
		LOCK_GUARD_STATIC();
		for (PsmFree free : freeList) {
			switch (free.Type()) {
			case PsmObjectType::GraphicsContext:
				Logger::Debug("Freeing GraphicsContext: "+Format::Hex(free.Handle()));
				GraphicsContext::DeleteGraphicsCtx();
				break;
			case PsmObjectType::FrameBuffer:
				Logger::Debug("Freeing FrameBuffer: " + Format::Hex(free.Handle()));
				FrameBuffer::Delete(free.Handle());
				break;
			case PsmObjectType::VertexBuffer:
				Logger::Debug("Freeing VertexBuffer: " + Format::Hex(free.Handle()));
				VertexBuffer::Delete(free.Handle());
				break;
			case PsmObjectType::PixelBuffer:
				Logger::Debug("Freeing PixelBuffer: " + Format::Hex(free.Handle()));
				PixelBuffer::Delete(free.Handle());
				break;
			case PsmObjectType::ShaderProgram:
				Logger::Debug("Freeing ShaderProgram: " + Format::Hex(free.Handle()));
				ShaderProgram::Delete(free.Handle());
				break;
			}
		}

		freeList.clear();
	}

}