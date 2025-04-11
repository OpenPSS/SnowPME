#include "Camera.hpp"

namespace Sce::Pss::Core::Device {
	int Camera::GetNumberOfCamerasNative(){
		std::cout << "Sce::Pss::Core::Device::GetNumberOfCamerasNative() Unimplemented.";
		return 0;
	}
	int Camera::GetCameraFacingNative(int cameraId, CameraFacing* info) {
		std::cout << "Sce::Pss::Core::Device::GetCameraFacingNative(int, Sce::Pss::Core::Device::CameraFacing *) Unimplemented.";
		return 0;
	}
	int Camera::GetSupportedPreviewSizeCountNative(int cameraId){
		std::cout << "Sce::Pss::Core::Device::GetSupportedPreviewSizeCountNative(int) Unimplemented.";
		return 0;
	}
	int Camera::GetSupportedPreviewSizeNative(int cameraId, int sizeId, CameraSize *size){
		std::cout << "Sce::Pss::Core::Device::GetSupportedPreviewSizeNative(int, int, Sce::Pss::Core::Device::CameraSize *) Unimplemented.";
		return 0;
	}
	int Camera::GetSupportedPictureSizeCountNative(int cameraId){
		std::cout << "Sce::Pss::Core::Device::GetSupportedPictureSizeCountNative(int) Unimplemented.";
		return 0;
	}
	int Camera::GetSupportedPictureSizeNative(int cameraId, int sizeId, CameraSize *size){
		std::cout << "Sce::Pss::Core::Device::GetSupportedPictureSizeNative(int, int, Sce::Pss::Core::Device::CameraSize *) Unimplemented.";
		return 0;
	}
	int Camera::NewFromIndex(int cameraId, int *handle){
		std::cout << "Sce::Pss::Core::Device::NewFromIndex(int, int *) Unimplemented.";
		return 0;
	}
	int Camera::ReleaseNative(int handle){
		std::cout << "Sce::Pss::Core::Device::ReleaseNative(int) Unimplemented.";
		return 0;
	}
	int Camera::GetCameraStateNative(int handle, CameraState *state){
		std::cout << "Sce::Pss::Core::Device::GetCameraStateNative(int, Sce::Pss::Core::Device::CameraState *) Unimplemented.";
		return 0;
	}
	int Camera::HasTakenPictureNative(int handle, PictureState *taken){
		std::cout << "Sce::Pss::Core::Device::HasTakenPictureNative(int, Sce::Pss::Core::Device::PictureState *) Unimplemented.";
		return 0;
	}
	int Camera::OpenNative(int handle, CameraSize size){
		std::cout << "Sce::Pss::Core::Device::OpenNative(int, Sce::Pss::Core::Device::CameraSize) Unimplemented.";
		return 0;
	}
	int Camera::CloseNative(int handle){
		std::cout << "Sce::Pss::Core::Device::CloseNative(int) Unimplemented.";
		return 0;
	}
	int Camera::GetPreviewSizeNative(int handle, CameraSize *size){
		std::cout << "Sce::Pss::Core::Device::GetPreviewSizeNative(int, Sce::Pss::Core::Device::CameraSize *) Unimplemented.";
		return 0;
	}
	int Camera::GetPreviewImageFormatNative(int handle, CameraImageFormat *format){
		std::cout << "Sce::Pss::Core::Device::GetPreviewImageFormatNative(int, Sce::Pss::Core::Device::CameraImageFormat *) Unimplemented.";
		return 0;
	}
	int Camera::StartNative(int handle){
		std::cout << "Sce::Pss::Core::Device::StartNative(int) Unimplemented.";
		return 0;
	}
	int Camera::StopNative(int handle){
		std::cout << "Sce::Pss::Core::Device::StopNative(int) Unimplemented.";
		return 0;
	}
	int Camera::ReadNative(int handle, uint8_t* frameBuffer, int bufferSize, long * frameCount){
		std::cout << "Sce::Pss::Core::Device::ReadNative(int, byte*, int, long *) Unimplemented.";
		return 0;
	}
	int Camera::TakePictureNative(int handle, CameraSize size){
		std::cout << "Sce::Pss::Core::Device::TakePictureNative(int, Sce::Pss::Core::Device::CameraSize) Unimplemented.";
		return 0;
	}
	int Camera::GetPictureFilenameNative(int handle, std::string *filename){
		std::cout << "Sce::Pss::Core::Device::GetPictureFilenameNative(int, string *) Unimplemented.";
		return 0;
	}
}
