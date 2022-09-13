#include "Camera.hpp"

namespace Sce::PlayStation::Core::Device {
	int Camera::GetNumberOfCamerasNative(){
		cout << "Sce::PlayStation::Core::Device::GetNumberOfCamerasNative() Unimplemented.";
		return 0;
	}
	int Camera::GetCameraFacingNative(int cameraId, CameraFacing* info) {
		cout << "Sce::PlayStation::Core::Device::GetCameraFacingNative(int, Sce::PlayStation::Core::Device::CameraFacing *) Unimplemented.";
		return 0;
	}
	int Camera::GetSupportedPreviewSizeCountNative(int cameraId){
		cout << "Sce::PlayStation::Core::Device::GetSupportedPreviewSizeCountNative(int) Unimplemented.";
		return 0;
	}
	int Camera::GetSupportedPreviewSizeNative(int cameraId, int sizeId, CameraSize *size){
		cout << "Sce::PlayStation::Core::Device::GetSupportedPreviewSizeNative(int, int, Sce::PlayStation::Core::Device::CameraSize *) Unimplemented.";
		return 0;
	}
	int Camera::GetSupportedPictureSizeCountNative(int cameraId){
		cout << "Sce::PlayStation::Core::Device::GetSupportedPictureSizeCountNative(int) Unimplemented.";
		return 0;
	}
	int Camera::GetSupportedPictureSizeNative(int cameraId, int sizeId, CameraSize *size){
		cout << "Sce::PlayStation::Core::Device::GetSupportedPictureSizeNative(int, int, Sce::PlayStation::Core::Device::CameraSize *) Unimplemented.";
		return 0;
	}
	int Camera::NewFromIndex(int cameraId, int *handle){
		cout << "Sce::PlayStation::Core::Device::NewFromIndex(int, int *) Unimplemented.";
		return 0;
	}
	int Camera::ReleaseNative(int handle){
		cout << "Sce::PlayStation::Core::Device::ReleaseNative(int) Unimplemented.";
		return 0;
	}
	int Camera::GetCameraStateNative(int handle, CameraState *state){
		cout << "Sce::PlayStation::Core::Device::GetCameraStateNative(int, Sce::PlayStation::Core::Device::CameraState *) Unimplemented.";
		return 0;
	}
	int Camera::HasTakenPictureNative(int handle, PictureState *taken){
		cout << "Sce::PlayStation::Core::Device::HasTakenPictureNative(int, Sce::PlayStation::Core::Device::PictureState *) Unimplemented.";
		return 0;
	}
	int Camera::OpenNative(int handle, CameraSize size){
		cout << "Sce::PlayStation::Core::Device::OpenNative(int, Sce::PlayStation::Core::Device::CameraSize) Unimplemented.";
		return 0;
	}
	int Camera::CloseNative(int handle){
		cout << "Sce::PlayStation::Core::Device::CloseNative(int) Unimplemented.";
		return 0;
	}
	int Camera::GetPreviewSizeNative(int handle, CameraSize *size){
		cout << "Sce::PlayStation::Core::Device::GetPreviewSizeNative(int, Sce::PlayStation::Core::Device::CameraSize *) Unimplemented.";
		return 0;
	}
	int Camera::GetPreviewImageFormatNative(int handle, CameraImageFormat *format){
		cout << "Sce::PlayStation::Core::Device::GetPreviewImageFormatNative(int, Sce::PlayStation::Core::Device::CameraImageFormat *) Unimplemented.";
		return 0;
	}
	int Camera::StartNative(int handle){
		cout << "Sce::PlayStation::Core::Device::StartNative(int) Unimplemented.";
		return 0;
	}
	int Camera::StopNative(int handle){
		cout << "Sce::PlayStation::Core::Device::StopNative(int) Unimplemented.";
		return 0;
	}
	int Camera::ReadNative(int handle, byte* frameBuffer, int bufferSize, long * frameCount){
		cout << "Sce::PlayStation::Core::Device::ReadNative(int, byte*, int, long *) Unimplemented.";
		return 0;
	}
	int Camera::TakePictureNative(int handle, CameraSize size){
		cout << "Sce::PlayStation::Core::Device::TakePictureNative(int, Sce::PlayStation::Core::Device::CameraSize) Unimplemented.";
		return 0;
	}
	int Camera::GetPictureFilenameNative(int handle, string *filename){
		cout << "Sce::PlayStation::Core::Device::GetPictureFilenameNative(int, string *) Unimplemented.";
		return 0;
	}
}
