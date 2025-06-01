#include <Sce/Pss/Core/Device/Camera.hpp>
#include <Sce/Pss/Core/Error.hpp>

namespace Sce::Pss::Core::Device {
	int Camera::GetNumberOfCamerasNative(){
		UNIMPLEMENTED();
	}
	int Camera::GetCameraFacingNative(int cameraId, CameraFacing* info) {
		UNIMPLEMENTED();
	}
	int Camera::GetSupportedPreviewSizeCountNative(int cameraId){
		UNIMPLEMENTED();
	}
	int Camera::GetSupportedPreviewSizeNative(int cameraId, int sizeId, CameraSize *size){
		UNIMPLEMENTED();
	}
	int Camera::GetSupportedPictureSizeCountNative(int cameraId){
		UNIMPLEMENTED();
	}
	int Camera::GetSupportedPictureSizeNative(int cameraId, int sizeId, CameraSize *size){
		UNIMPLEMENTED();
	}
	int Camera::NewFromIndex(int cameraId, int *handle){
		UNIMPLEMENTED();
	}
	int Camera::ReleaseNative(int handle){
		UNIMPLEMENTED();
	}
	int Camera::GetCameraStateNative(int handle, CameraState *state){
		UNIMPLEMENTED();
	}
	int Camera::HasTakenPictureNative(int handle, PictureState *taken){
		UNIMPLEMENTED();
	}
	int Camera::OpenNative(int handle, CameraSize size){
		UNIMPLEMENTED();
	}
	int Camera::CloseNative(int handle){
		UNIMPLEMENTED();
	}
	int Camera::GetPreviewSizeNative(int handle, CameraSize *size){
		UNIMPLEMENTED();
	}
	int Camera::GetPreviewImageFormatNative(int handle, CameraImageFormat *format){
		UNIMPLEMENTED();
	}
	int Camera::StartNative(int handle){
		UNIMPLEMENTED();
	}
	int Camera::StopNative(int handle){
		UNIMPLEMENTED();
	}
	int Camera::ReadNative(int handle, uint8_t* frameBuffer, int bufferSize, long * frameCount){
		UNIMPLEMENTED();
	}
	int Camera::TakePictureNative(int handle, CameraSize size){
		UNIMPLEMENTED();
	}
	int Camera::GetPictureFilenameNative(int handle, std::string *filename){
		UNIMPLEMENTED();
	}
}
