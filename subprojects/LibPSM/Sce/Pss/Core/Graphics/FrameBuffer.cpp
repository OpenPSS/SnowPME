#include <Sce/Pss/Core/Graphics/FrameBuffer.hpp>
#include <LibShared.hpp>


namespace Sce::Pss::Core::Graphics {
	using namespace Shared::Debug;

	int FrameBuffer::ActiveStateChanged(bool state) {
		Logger::Debug(__FUNCTION__);
		return PSM_ERROR_NO_ERROR;
	}

	FrameBuffer::FrameBuffer() {

	}

	FrameBuffer::~FrameBuffer() {

	}

}