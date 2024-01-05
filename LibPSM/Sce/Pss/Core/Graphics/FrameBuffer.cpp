#include <Sce/Pss/Core/Graphics/FrameBuffer.hpp>
#include <LibShared.hpp>
using namespace Shared::Debug;

namespace Sce::Pss::Core::Graphics {

	int FrameBuffer::ActiveStateChanged(bool state) {
		Logger::Debug(__FUNCTION__);
		return PSM_ERROR_NO_ERROR;
	}

	FrameBuffer::FrameBuffer() {

	}

	FrameBuffer::~FrameBuffer() {

	}

}