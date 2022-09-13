#ifndef LIB_PSM_CAMERA_H
#define LIB_PSM_CAMERA_H 1
#include <stdint.h>
#include <stdlib.h>
#include <string>
#include <iostream>

#include "CameraFacing.hpp"
#include "CameraImageFormat.hpp"
#include "CameraState.hpp"
#include "CameraSize.hpp"
#include "CameraInfo.hpp"
#include "PictureState.hpp"

using namespace std;

namespace Sce::PlayStation::Core::Device {
	class Camera {
	public:
		static int GetNumberOfCamerasNative();
		static int GetCameraFacingNative(int cameraId, CameraFacing *info);
		static int GetSupportedPreviewSizeCountNative(int cameraId);
		static int GetSupportedPreviewSizeNative(int cameraId, int sizeId, CameraSize *size);
		static int GetSupportedPictureSizeCountNative(int cameraId);
		static int GetSupportedPictureSizeNative(int cameraId, int sizeId, CameraSize *size);
		static int NewFromIndex(int cameraId, int *handle);
		static int ReleaseNative(int handle);
		static int GetCameraStateNative(int handle, CameraState *state);
		static int HasTakenPictureNative(int handle, PictureState *taken);
		static int OpenNative(int handle, CameraSize size);
		static int CloseNative(int handle);
		static int GetPreviewSizeNative(int handle, CameraSize *size);
		static int GetPreviewImageFormatNative(int handle, CameraImageFormat *format);
		static int StartNative(int handle);
		static int StopNative(int handle);
		static int ReadNative(int handle, byte* frameBuffer, int bufferSize, long *frameCount);
		static int TakePictureNative(int handle, CameraSize size);
		static int GetPictureFilenameNative(int handle, string *filename);
	};
}
#endif
