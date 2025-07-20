#ifndef LIB_PSS_TEXTURE_2D_H
#define LIB_PSS_TEXTURE_2D_H 1

#include <Sce/Pss/Core/Graphics/Texture.hpp>
#include <Sce/Pss/Core/Imaging/Impl/ImageImpl.hpp>
#include <Sce/Pss/Core/PsmObject.hpp>
#include <Sce/Pss/Core/Graphics/InternalOption.hpp>
#include <glad/glad.h>

namespace Sce::Pss::Core::Graphics {
	class Texture2D : public Texture {
	private:
		std::shared_ptr<Sce::Pss::Core::Imaging::Impl::ImageImpl> imageImpl = nullptr;
	public:
		Texture2D(std::string& fileName, bool mipmap, Sce::Pss::Core::Graphics::PixelFormat format);
		Texture2D(int width, int height, bool mipmap, PixelFormat format, PixelBufferOption option, Sce::Pss::Core::Graphics::InternalOption option2);
		~Texture2D() = default;
		int InitImage(int width, int height, bool mipmap, PixelFormat format, PixelBufferOption option, Sce::Pss::Core::Graphics::InternalOption option2, int unk0);
		int LoadImage(uint8_t* data, uint32_t dataLen, bool mipmap, Sce::Pss::Core::Graphics::PixelFormat format);
		int ActiveStateChanged(bool state);
	};
}

#endif