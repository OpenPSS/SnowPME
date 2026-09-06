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
				GraphicsContext::Delete(free.Handle());
				GraphicsContext::MakeLocalObject();
			case PsmObjectType::FrameBuffer:
				FrameBuffer::Delete(free.Handle());
			case PsmObjectType::VertexBuffer:
				VertexBuffer::Delete(free.Handle());
			case PsmObjectType::Texture:
				Texture::Delete(free.Handle());
			case PsmObjectType::Shader:
				ShaderProgram::Delete(free.Handle());
			}
		}

		freeList.clear();
	}

}