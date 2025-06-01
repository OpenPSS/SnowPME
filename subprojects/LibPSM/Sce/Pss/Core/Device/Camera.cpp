#include <Sce/Pss/Core/Device/Camera.hpp>
#include <Sce/Pss/Core/Error.hpp>

namespace Sce::Pss::Core::Device {
	int Camera::GetNumberOfCamerasNative(){
		Unimplemented();
	}
	int Camera::GetCameraFacingNative(int cameraId, CameraFacing* info) {
		Unimplemented();
	}
	int Camera::GetSupportedPreviewSizeCountNative(int cameraId){
		Unimplemented();
	}
	int Camera::GetSupportedPreviewSizeNative(int cameraId, int sizeId, CameraSize *size){
		Unimplemented();
	}
	int Camera::GetSupportedPictureSizeCountNative(int cameraId){
		Unimplemented();
	}
	int Camera::GetSupportedPictureSizeNative(int cameraId, int sizeId, CameraSize *size){
		Unimplemented();
	}
	int Camera::NewFromIndex(int cameraId, int *handle){
		Unimplemented();
	}
	int Camera::ReleaseNative(int handle){
		Unimplemented();
	}
	int Camera::GetCameraStateNative(int handle, CameraState *state){
		Unimplemented();
	}
	int Camera::HasTakenPictureNative(int handle, PictureState *taken){
		Unimplemented();
	}
	int Camera::OpenNative(int handle, CameraSize size){
		Unimplemented();
	}
	int Camera::CloseNative(int handle){
		Unimplemented();
	}
	int Camera::GetPreviewSizeNative(int handle, CameraSize *size){
		Unimplemented();
	}
	int Camera::GetPreviewImageFormatNative(int handle, CameraImageFormat *format){
		Unimplemented();
	}
	int Camera::StartNative(int handle){
		Unimplemented();
	}
	int Camera::StopNative(int handle){
		Unimplemented();
	}
	int Camera::ReadNative(int handle, uint8_t* frameBuffer, int bufferSize, long * frameCount){
		Unimplemented();
	}
	int Camera::TakePictureNative(int handle, CameraSize size){
		Unimplemented();
	}
	int Camera::GetPictureFilenameNative(int handle, std::string *filename){
		Unimplemented();
	}
}
