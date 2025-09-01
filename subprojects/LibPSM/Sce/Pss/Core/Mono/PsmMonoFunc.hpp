#ifndef LIB_PSS_PSMMONOFUNC_H
#define LIB_PSS_PSMMONOFUNC_H 1

#include <Sce/Pss/Core/InitializeCsharp.hpp>
#include <Sce/Pss/Core/Features.hpp>

#include <Sce/Pss/Core/Environment/Log.hpp>
#include <Sce/Pss/Core/Environment/SystemEvents.hpp>
#include <Sce/Pss/Core/Environment/SystemParameters.hpp>
#include <Sce/Pss/Core/Environment/SystemMemory.hpp>
#include <Sce/Pss/Core/Environment/PersistentMemory.hpp>
#include <Sce/Pss/Core/Environment/Shell.hpp>
#include <Sce/Pss/Core/Environment/CommonDialog.hpp>
#include <Sce/Pss/Core/Environment/TextInputDialog.hpp>
#include <Sce/Pss/Core/Services/AccountInformation.hpp>
#include <Sce/Pss/Core/Services/InAppPurchaseDialog.hpp>
#include <Sce/Pss/Core/Environment/Clipboard.hpp>
#include <Sce/Pss/Core/Environment/NetworkInformation.hpp>
#include <Sce/Pss/Core/Device/CameraImportDialog.hpp>
#include <Sce/Pss/Core/Device/PhotoImportDialog.hpp>
#include <Sce/Pss/Core/Graphics/PsmGraphicsContext.hpp>
#include <Sce/Pss/Core/Graphics/PsmShaderProgram.hpp>
#include <Sce/Pss/Core/Graphics/PsmVertexBuffer.hpp>
#include <Sce/Pss/Core/Graphics/PsmPixelBuffer.hpp>
#include <Sce/Pss/Core/Graphics/PsmTexture.hpp>
#include <Sce/Pss/Core/Graphics/PsmFrameBuffer.hpp>
#include <Sce/Pss/Core/Audio/Sound.hpp>
#include <Sce/Pss/Core/Audio/SoundPlayer.hpp>
#include <Sce/Pss/Core/Audio/Bgm.hpp>
#include <Sce/Pss/Core/Audio/BgmPlayer.hpp>
#include <Sce/Pss/Core/Input/Touch.hpp>
#include <Sce/Pss/Core/Input/GamePad.hpp>
#include <Sce/Pss/Core/Input/Motion.hpp>
#include <Sce/Pss/Core/Imaging/Image.hpp>
#include <Sce/Pss/Core/Imaging/Font.hpp>
#include <Sce/Pss/Core/Device/Location.hpp>
#include <Sce/Pss/Core/Device/Camera.hpp>
#include <Sce/Pss/Core/Services/NetworkRequest.hpp>
#include <Sce/Pss/Core/Services/Network.hpp>
#include <LibShared.hpp>

#define PSM_MONO_FUNCTION_MIN_MAX_SDK(str, func, minsdk, maxsdk) { str, reinterpret_cast<void*>(func), minsdk, maxsdk }
#define PSM_MONO_FUNCTION_MIN_SDK(str, func, minsdk) { str, reinterpret_cast<void*>(func), minsdk, MAX_SDK }
#define PSM_MONO_FUNCTION(str, func) { str, reinterpret_cast<void*>(func), MIN_SDK, MAX_SDK }
#define PSM_MONO_FUNC_END() { nullptr, nullptr, 0x00 }

namespace Sce::Pss::Core::Mono {
	
	typedef struct PsmMonoFunc {
		const char* functionSignature;
		void* functionPointer;
		uint32_t minSdkVerison;
		uint32_t maxSdkVersion;
	} PsmMonoFunc;

	inline PsmMonoFunc ErrorFunctions[] {
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Error::GetExceptionInfoNative(string&,string&)", Sce::Pss::Core::Error::GetExceptionInfoNative ),
		PSM_MONO_FUNC_END()
	};

	inline PsmMonoFunc ServiceFunctions[] {
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Services.NetworkRequest::CreateRequestNative(int,string,string,int&)", Sce::Pss::Core::Services::NetworkRequest::CreateRequestNative ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Services.NetworkRequest::QueueRequestNative(int,string,string,int&)", Sce::Pss::Core::Services::NetworkRequest::QueueRequestNative ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Services.NetworkRequest::DestroyRequestNative(int)", Sce::Pss::Core::Services::NetworkRequest::DestroyRequestNative ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Services.NetworkRequest::GetResponseNative(int,string&)", Sce::Pss::Core::Services::NetworkRequest::GetResponseNative ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Services.NetworkRequest::RegisterThreadNative()", Sce::Pss::Core::Services::NetworkRequest::RegisterThreadNative ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Services.NetworkRequest::UnregisterThreadNative()", Sce::Pss::Core::Services::NetworkRequest::UnregisterThreadNative ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Services.Network::CheckStateNative(uint&)", Sce::Pss::Core::Services::Network::CheckStateNative ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Services.Network::GetOnlineIdNative(string&)", Sce::Pss::Core::Services::Network::GetOnlineIdNative ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Services.Network::GetAccountIdNative(ulong&)", Sce::Pss::Core::Services::Network::GetAccountIdNative ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Services.Network::SetWebRequestDelegate(intptr)", Sce::Pss::Core::Services::Network::SetWebRequestDelegate ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Services.Network::SetAuthServer(bool)", Sce::Pss::Core::Services::Network::SetAuthServer ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Services.Network::GetAuthTicketDataNative(string&)", Sce::Pss::Core::Services::Network::GetAuthTicketDataNative ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Services.Network::ResetAuthTicketNative()", Sce::Pss::Core::Services::Network::ResetAuthTicketNative ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Services.Network::SetAppIdNative(string)", Sce::Pss::Core::Services::Network::SetAppIdNative ),
		PSM_MONO_FUNC_END()
	};

	inline PsmMonoFunc CameraFunctions[] {
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Device.Camera::GetNumberOfCamerasNative()", Sce::Pss::Core::Device::Camera::GetNumberOfCamerasNative ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Device.Camera::GetCameraFacingNative(int,Sce.PlayStation.Core.Device.CameraFacing&)", Sce::Pss::Core::Device::Camera::GetCameraFacingNative ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Device.Camera::GetSupportedPreviewSizeCountNative(int)", Sce::Pss::Core::Device::Camera::GetSupportedPreviewSizeCountNative ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Device.Camera::GetSupportedPreviewSizeNative(int,int,Sce.PlayStation.Core.Device.CameraSize&)", Sce::Pss::Core::Device::Camera::GetSupportedPreviewSizeNative ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Device.Camera::GetSupportedPictureSizeCountNative(int)", Sce::Pss::Core::Device::Camera::GetSupportedPictureSizeCountNative ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Device.Camera::GetSupportedPictureSizeNative(int,int,Sce.PlayStation.Core.Device.CameraSize&)", Sce::Pss::Core::Device::Camera::GetSupportedPictureSizeNative ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Device.Camera::NewFromIndex(int,int&)", Sce::Pss::Core::Device::Camera::NewFromIndex ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Device.Camera::ReleaseNative(int)", Sce::Pss::Core::Device::Camera::ReleaseNative ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Device.Camera::GetCameraStateNative(int,Sce.PlayStation.Core.Device.CameraState&)", Sce::Pss::Core::Device::Camera::GetCameraStateNative ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Device.Camera::HasTakenPictureNative(int,Sce.PlayStation.Core.Device.PictureState&)", Sce::Pss::Core::Device::Camera::HasTakenPictureNative ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Device.Camera::OpenNative(int,Sce.PlayStation.Core.Device.CameraSize)", Sce::Pss::Core::Device::Camera::OpenNative ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Device.Camera::CloseNative(int)", Sce::Pss::Core::Device::Camera::CloseNative ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Device.Camera::GetPreviewSizeNative(int,Sce.PlayStation.Core.Device.CameraSize&)", Sce::Pss::Core::Device::Camera::GetPreviewSizeNative ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Device.Camera::GetPreviewImageFormatNative(int,Sce.PlayStation.Core.Device.CameraImageFormat&)", Sce::Pss::Core::Device::Camera::GetPreviewImageFormatNative ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Device.Camera::StartNative(int)", Sce::Pss::Core::Device::Camera::StartNative ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Device.Camera::StopNative(int)", Sce::Pss::Core::Device::Camera::StopNative ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Device.Camera::ReadNative(int,byte[],int,long&)", Sce::Pss::Core::Device::Camera::ReadNative ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Device.Camera::TakePictureNative(int,Sce.PlayStation.Core.Device.CameraSize)", Sce::Pss::Core::Device::Camera::TakePictureNative ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Device.Camera::GetPictureFilenameNative(int,string&)", Sce::Pss::Core::Device::Camera::GetPictureFilenameNative ),
		PSM_MONO_FUNC_END()

	};

	inline PsmMonoFunc LocationFunctions[] {
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Device.Location::StartNative()", Sce::Pss::Core::Device::Location::StartNative ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Device.Location::StopNative()", Sce::Pss::Core::Device::Location::StopNative ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Device.Location::GetDataNative(Sce.PlayStation.Core.Device.LocationData&)", Sce::Pss::Core::Device::Location::GetDataNative ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Device.Location::GetEnableDevicesNative()", Sce::Pss::Core::Device::Location::GetEnableDevicesNative ),
		PSM_MONO_FUNC_END()
	};

	inline PsmMonoFunc ImagingFunctions[] {
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Imaging.Image::NewFromFilename(string,int&)", Sce::Pss::Core::Imaging::Image::NewFromFilename ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Imaging.Image::NewFromFileImage(byte[],int&)", Sce::Pss::Core::Imaging::Image::NewFromFileImage ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Imaging.Image::NewFromModeSizeColor(Sce.PlayStation.Core.Imaging.ImageMode,Sce.PlayStation.Core.Imaging.ImageSize&,Sce.PlayStation.Core.Imaging.ImageColor&,int&)", Sce::Pss::Core::Imaging::Image::NewFromModeSizeColor ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Imaging.Image::NewFromModeSizeBuffer(Sce.PlayStation.Core.Imaging.ImageMode,Sce.PlayStation.Core.Imaging.ImageSize&,byte[],int&)", Sce::Pss::Core::Imaging::Image::NewFromModeSizeBuffer ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Imaging.Image::AddRefNative(int)", Sce::Pss::Core::Imaging::Image::AddRefNative ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Imaging.Image::ReleaseNative(int)", Sce::Pss::Core::Imaging::Image::ReleaseNative ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Imaging.Image::GetSize(int,Sce.PlayStation.Core.Imaging.ImageSize&)", Sce::Pss::Core::Imaging::Image::GetSize ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Imaging.Image::SetDecodeSize(int,Sce.PlayStation.Core.Imaging.ImageSize&)", Sce::Pss::Core::Imaging::Image::SetDecodeSize ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Imaging.Image::DecodeNative(int)", Sce::Pss::Core::Imaging::Image::DecodeNative ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Imaging.Image::GetPixelData(int,byte[],uint)", Sce::Pss::Core::Imaging::Image::GetPixelData ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Imaging.Image::GetPixelDataSize(int,uint&)", Sce::Pss::Core::Imaging::Image::GetPixelDataSize ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Imaging.Image::ResizeNative(int,Sce.PlayStation.Core.Imaging.ImageSize&,int&)", Sce::Pss::Core::Imaging::Image::ResizeNative ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Imaging.Image::CropNative(int,Sce.PlayStation.Core.Imaging.ImageRect&,int&)", Sce::Pss::Core::Imaging::Image::CropNative ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Imaging.Image::DrawImageNative(int,int,Sce.PlayStation.Core.Imaging.ImagePosition&)", Sce::Pss::Core::Imaging::Image::DrawImageNative ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Imaging.Image::DrawRectangleNative(int,Sce.PlayStation.Core.Imaging.ImageColor&,Sce.PlayStation.Core.Imaging.ImageRect&)", Sce::Pss::Core::Imaging::Image::DrawRectangleNative ),
		
		/*
		* Exclusive to PSVita PSM Runtime for some reason,
		* 'private static extern int DrawTextNative(int handle, string text, uint offset, uint len, ref ImageColor color, int font_handle, ref ImagePosition position);'
		* basically specifically on VITA's Sce.PlayStation.Core.dll, this is now uints instead of int; *why did they do this?*
		*/
		PSM_MONO_FUNCTION_MIN_MAX_SDK("Sce.PlayStation.Core.Imaging.Image::DrawTextNative(int,string,int,int,Sce.PlayStation.Core.Imaging.ImageColor&,int,Sce.PlayStation.Core.Imaging.ImagePosition&)", Sce::Pss::Core::Imaging::Image::DrawTextNative, MIN_SDK, SDK_2_00_00),
		PSM_MONO_FUNCTION_MIN_SDK( "Sce.PlayStation.Core.Imaging.Image::DrawTextNative(int,string,uint,uint,Sce.PlayStation.Core.Imaging.ImageColor&,int,Sce.PlayStation.Core.Imaging.ImagePosition&)", Sce::Pss::Core::Imaging::Image::DrawTextNative, SDK_2_01_00),

		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Imaging.Image::ExportNative(int,string,string)", Sce::Pss::Core::Imaging::Image::ExportNative ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Imaging.Image::SaveAsNative(int,string)", Sce::Pss::Core::Imaging::Image::SaveAsNative ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Imaging.Font::NewFromFilenameSizeStyle(string,int,Sce.PlayStation.Core.Imaging.FontStyle,int&)", Sce::Pss::Core::Imaging::Font::NewFromFilenameSizeStyle ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Imaging.Font::NewFromAliasSizeStyle(Sce.PlayStation.Core.Imaging.FontAlias,int,Sce.PlayStation.Core.Imaging.FontStyle,int&)", Sce::Pss::Core::Imaging::Font::NewFromAliasSizeStyle ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Imaging.Font::AddRefNative(int)", Sce::Pss::Core::Imaging::Font::AddRefNative ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Imaging.Font::ReleaseNative(int)", Sce::Pss::Core::Imaging::Font::ReleaseNative ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Imaging.Font::GetName(int,string&)", Sce::Pss::Core::Imaging::Font::GetName ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Imaging.Font::GetSize(int,int&)", Sce::Pss::Core::Imaging::Font::GetSize ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Imaging.Font::GetStyle(int,Sce.PlayStation.Core.Imaging.FontStyle&)", Sce::Pss::Core::Imaging::Font::GetStyle ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Imaging.Font::GetMetrics(int,Sce.PlayStation.Core.Imaging.FontMetrics&)", Sce::Pss::Core::Imaging::Font::GetMetrics ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Imaging.Font::GetTextWidthNative(int,string,int,int,int&)", Sce::Pss::Core::Imaging::Font::GetTextWidthNative ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Imaging.Font::GetTextMetricsNative(int,string,int,int,Sce.PlayStation.Core.Imaging.CharMetrics[])", Sce::Pss::Core::Imaging::Font::GetTextMetricsNative ),
		PSM_MONO_FUNC_END()
	};

	inline PsmMonoFunc InputFunctions[] {
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Input.Touch::GetDataNative(int,Sce.PlayStation.Core.Input.TouchData[],int,int&)", Sce::Pss::Core::Input::Touch::GetDataNative ),
		PSM_MONO_FUNCTION_MIN_SDK( "Sce.PlayStation.Core.Input.Touch::GetRearTouchDataNative(int,Sce.PlayStation.Core.Input.TouchData[],int,int&)", Sce::Pss::Core::Input::Touch::GetRearTouchDataNative, SDK_2_00_00 ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Input.GamePad::GetDataNative(int,Sce.PlayStation.Core.Input.GamePadData&)", Sce::Pss::Core::Input::GamePad::GetDataNative ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Input.Motion::GetDataNative(int,Sce.PlayStation.Core.Input.MotionData&)", Sce::Pss::Core::Input::Motion::GetDataNative ),
		PSM_MONO_FUNC_END()
	};

	inline PsmMonoFunc AudioFunctions[] {
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Audio.Sound::NewFromFilename(string,int&)", Sce::Pss::Core::Audio::Sound::NewFromFilename ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Audio.Sound::NewFromFileImage(byte[],int&)", Sce::Pss::Core::Audio::Sound::NewFromFileImage ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Audio.Sound::ReleaseNative(int)", Sce::Pss::Core::Audio::Sound::ReleaseNative ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Audio.Sound::CreatePlayerNative(int,int&)", Sce::Pss::Core::Audio::Sound::CreatePlayerNative ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Audio.SoundPlayer::ReleaseNative(int)", Sce::Pss::Core::Audio::SoundPlayer::ReleaseNative ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Audio.SoundPlayer::PlayNative(int)", Sce::Pss::Core::Audio::SoundPlayer::PlayNative ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Audio.SoundPlayer::StopNative(int)", Sce::Pss::Core::Audio::SoundPlayer::StopNative ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Audio.SoundPlayer::GetStatusNative(int,Sce.PlayStation.Core.Audio.SoundStatus&)", Sce::Pss::Core::Audio::SoundPlayer::GetStatusNative ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Audio.SoundPlayer::GetVolumeNative(int,single&)", Sce::Pss::Core::Audio::SoundPlayer::GetVolumeNative ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Audio.SoundPlayer::SetVolumeNative(int,single)", Sce::Pss::Core::Audio::SoundPlayer::SetVolumeNative ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Audio.SoundPlayer::GetPanNative(int,single&)", Sce::Pss::Core::Audio::SoundPlayer::GetPanNative ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Audio.SoundPlayer::SetPanNative(int,single)", Sce::Pss::Core::Audio::SoundPlayer::SetPanNative ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Audio.SoundPlayer::GetLoopNative(int,bool&)", Sce::Pss::Core::Audio::SoundPlayer::GetLoopNative ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Audio.SoundPlayer::SetLoopNative(int,bool)", Sce::Pss::Core::Audio::SoundPlayer::SetLoopNative ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Audio.SoundPlayer::GetPlaybackRateNative(int,single&)", Sce::Pss::Core::Audio::SoundPlayer::GetPlaybackRateNative ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Audio.SoundPlayer::SetPlaybackRateNative(int,single)", Sce::Pss::Core::Audio::SoundPlayer::SetPlaybackRateNative ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Audio.SoundPlayer::GetPosition(int,ulong&)", Sce::Pss::Core::Audio::SoundPlayer::GetPosition ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Audio.SoundPlayer::SetPosition(int,ulong)", Sce::Pss::Core::Audio::SoundPlayer::SetPosition ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Audio.SoundPlayer::GetLength(int,ulong&)", Sce::Pss::Core::Audio::SoundPlayer::GetLength ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Audio.Bgm::NewFromFilename(string,int&)", Sce::Pss::Core::Audio::Bgm::NewFromFilename ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Audio.Bgm::NewFromFileImage(byte[],int&)", Sce::Pss::Core::Audio::Bgm::NewFromFileImage ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Audio.Bgm::ReleaseNative(int)", Sce::Pss::Core::Audio::Bgm::ReleaseNative ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Audio.Bgm::CreatePlayerNative(int,int&)", Sce::Pss::Core::Audio::Bgm::CreatePlayerNative ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Audio.BgmPlayer::ReleaseNative(int)", Sce::Pss::Core::Audio::BgmPlayer::ReleaseNative ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Audio.BgmPlayer::PlayNative(int)", Sce::Pss::Core::Audio::BgmPlayer::PlayNative ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Audio.BgmPlayer::StopNative(int)", Sce::Pss::Core::Audio::BgmPlayer::StopNative ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Audio.BgmPlayer::GetStatusNative(int,Sce.PlayStation.Core.Audio.BgmStatus&)", Sce::Pss::Core::Audio::BgmPlayer::GetStatusNative ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Audio.BgmPlayer::PauseNative(int)", Sce::Pss::Core::Audio::BgmPlayer::PauseNative ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Audio.BgmPlayer::ResumeNative(int)", Sce::Pss::Core::Audio::BgmPlayer::ResumeNative ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Audio.BgmPlayer::SetVolumeNative(int,single)", Sce::Pss::Core::Audio::BgmPlayer::SetVolumeNative ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Audio.BgmPlayer::GetVolumeNative(int,single&)", Sce::Pss::Core::Audio::BgmPlayer::GetVolumeNative ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Audio.BgmPlayer::GetLoopNative(int,bool&)", Sce::Pss::Core::Audio::BgmPlayer::GetLoopNative ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Audio.BgmPlayer::SetLoopNative(int,bool)", Sce::Pss::Core::Audio::BgmPlayer::SetLoopNative ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Audio.BgmPlayer::GetPlaybackRateNative(int,single&)", Sce::Pss::Core::Audio::BgmPlayer::GetPlaybackRateNative ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Audio.BgmPlayer::SetPlaybackRateNative(int,single)", Sce::Pss::Core::Audio::BgmPlayer::SetPlaybackRateNative ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Audio.BgmPlayer::GetPosition(int,ulong&)", Sce::Pss::Core::Audio::BgmPlayer::GetPosition ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Audio.BgmPlayer::SetPosition(int,ulong)", Sce::Pss::Core::Audio::BgmPlayer::SetPosition ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Audio.BgmPlayer::GetLength(int,ulong&)", Sce::Pss::Core::Audio::BgmPlayer::GetLength ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Audio.BgmPlayer::GetLoopPosition(int,ulong&,ulong&)", Sce::Pss::Core::Audio::BgmPlayer::GetLoopPosition ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Audio.BgmPlayer::SetLoopPosition(int,ulong,ulong)", Sce::Pss::Core::Audio::BgmPlayer::SetLoopPosition ),
		PSM_MONO_FUNC_END()
	};

	inline PsmMonoFunc GraphicsFunctions[] {
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Graphics.PsmGraphicsContext::Create(int,int,Sce.PlayStation.Core.Graphics.PixelFormat,Sce.PlayStation.Core.Graphics.PixelFormat,Sce.PlayStation.Core.Graphics.MultiSampleMode,int&)", Sce::Pss::Core::Graphics::PsmGraphicsContext::Create ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Graphics.PsmGraphicsContext::Delete(int)", Sce::Pss::Core::Graphics::PsmGraphicsContext::Delete ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Graphics.PsmGraphicsContext::Update(int,Sce.PlayStation.Core.Graphics.GraphicsUpdate,Sce.PlayStation.Core.Graphics.GraphicsState&,int[])", Sce::Pss::Core::Graphics::PsmGraphicsContext::Update ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Graphics.PsmGraphicsContext::SwapBuffers(int)", Sce::Pss::Core::Graphics::PsmGraphicsContext::SwapBuffers ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Graphics.PsmGraphicsContext::Clear(int,Sce.PlayStation.Core.Graphics.ClearMask)", Sce::Pss::Core::Graphics::PsmGraphicsContext::Clear ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Graphics.PsmGraphicsContext::DrawArrays(int,Sce.PlayStation.Core.Graphics.DrawMode,int,int,int)", Sce::Pss::Core::Graphics::PsmGraphicsContext::DrawArrays ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Graphics.PsmGraphicsContext::DrawArrays2(int,Sce.PlayStation.Core.Graphics.Primitive[],int,int)", Sce::Pss::Core::Graphics::PsmGraphicsContext::DrawArrays2 ),
		PSM_MONO_FUNCTION_MIN_SDK( "Sce.PlayStation.Core.Graphics.PsmGraphicsContext::DrawArraysInstanced(int,Sce.PlayStation.Core.Graphics.DrawMode,int,int,int,int)", Sce::Pss::Core::Graphics::PsmGraphicsContext::DrawArraysInstanced, SDK_2_00_00 ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Graphics.PsmGraphicsContext::ReadPixels(int,byte[],Sce.PlayStation.Core.Graphics.PixelFormat,int,int,int,int)", Sce::Pss::Core::Graphics::PsmGraphicsContext::ReadPixels ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Graphics.PsmGraphicsContext::ReadPixels2(int,int,int,Sce.PlayStation.Core.Graphics.TextureCubeFace,int,int,int,int,int,int)", Sce::Pss::Core::Graphics::PsmGraphicsContext::ReadPixels2 ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Graphics.PsmGraphicsContext::GetMaxScreenSize(int&,int&)", Sce::Pss::Core::Graphics::PsmGraphicsContext::GetMaxScreenSize ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Graphics.PsmGraphicsContext::GetScreenSizes(Sce.PlayStation.Core.Imaging.ImageSize[],int&)", Sce::Pss::Core::Graphics::PsmGraphicsContext::GetScreenSizes ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Graphics.PsmGraphicsContext::GetScreenInfo(int,int&,int&,Sce.PlayStation.Core.Graphics.PixelFormat&,Sce.PlayStation.Core.Graphics.PixelFormat&,Sce.PlayStation.Core.Graphics.MultiSampleMode&)", Sce::Pss::Core::Graphics::PsmGraphicsContext::GetScreenInfo ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Graphics.PsmGraphicsContext::GetCaps(int,Sce.PlayStation.Core.Graphics.GraphicsCapsState&)", Sce::Pss::Core::Graphics::PsmGraphicsContext::GetCaps ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Graphics.PsmGraphicsContext::SetActiveScreen(int,int,int,int,int)", Sce::Pss::Core::Graphics::PsmGraphicsContext::SetActiveScreen ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Graphics.PsmGraphicsContext::SetVirtualScreen(int,int,int,int,int)", Sce::Pss::Core::Graphics::PsmGraphicsContext::SetVirtualScreen ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Graphics.PsmShaderProgram::FromFile(string,string,string[],int[],int&)", Sce::Pss::Core::Graphics::PsmShaderProgram::FromFile ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Graphics.PsmShaderProgram::FromImage(byte[],byte[],string[],int[],int&)", Sce::Pss::Core::Graphics::PsmShaderProgram::FromImage ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Graphics.PsmShaderProgram::Delete(int)", Sce::Pss::Core::Graphics::PsmShaderProgram::Delete ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Graphics.PsmShaderProgram::AddRef(int)", Sce::Pss::Core::Graphics::PsmShaderProgram::AddRef ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Graphics.PsmShaderProgram::GetUniformCount(int,int&)", Sce::Pss::Core::Graphics::PsmShaderProgram::GetUniformCount ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Graphics.PsmShaderProgram::GetAttributeCount(int,int&)", Sce::Pss::Core::Graphics::PsmShaderProgram::GetAttributeCount ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Graphics.PsmShaderProgram::FindUniform(int,string,int&)", Sce::Pss::Core::Graphics::PsmShaderProgram::FindUniform ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Graphics.PsmShaderProgram::FindAttribute(int,string,int&)", Sce::Pss::Core::Graphics::PsmShaderProgram::FindAttribute ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Graphics.PsmShaderProgram::GetUniformBinding(int,int,string&)", Sce::Pss::Core::Graphics::PsmShaderProgram::GetUniformBinding ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Graphics.PsmShaderProgram::SetUniformBinding(int,int,string)", Sce::Pss::Core::Graphics::PsmShaderProgram::SetUniformBinding ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Graphics.PsmShaderProgram::GetAttributeBinding(int,int,string&)", Sce::Pss::Core::Graphics::PsmShaderProgram::GetAttributeBinding ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Graphics.PsmShaderProgram::SetAttributeBinding(int,int,string)", Sce::Pss::Core::Graphics::PsmShaderProgram::SetAttributeBinding ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Graphics.PsmShaderProgram::GetUniformType(int,int,Sce.PlayStation.Core.Graphics.ShaderUniformType&)", Sce::Pss::Core::Graphics::PsmShaderProgram::GetUniformType ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Graphics.PsmShaderProgram::GetAttributeType(int,int,Sce.PlayStation.Core.Graphics.ShaderAttributeType&)", Sce::Pss::Core::Graphics::PsmShaderProgram::GetAttributeType ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Graphics.PsmShaderProgram::GetUniformName(int,int,string&)", Sce::Pss::Core::Graphics::PsmShaderProgram::GetUniformName ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Graphics.PsmShaderProgram::GetAttributeName(int,int,string&)", Sce::Pss::Core::Graphics::PsmShaderProgram::GetAttributeName ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Graphics.PsmShaderProgram::GetUniformSize(int,int,int&)", Sce::Pss::Core::Graphics::PsmShaderProgram::GetUniformSize ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Graphics.PsmShaderProgram::GetAttributeSize(int,int,int&)", Sce::Pss::Core::Graphics::PsmShaderProgram::GetAttributeSize ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Graphics.PsmShaderProgram::SetUniformValue(int,int,int,Sce.PlayStation.Core.Matrix4&,Sce.PlayStation.Core.Graphics.ShaderUniformType)", Sce::Pss::Core::Graphics::PsmShaderProgram::SetUniformValue ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Graphics.PsmShaderProgram::SetUniformValue(int,int,int,Sce.PlayStation.Core.Vector4&,Sce.PlayStation.Core.Graphics.ShaderUniformType)", Sce::Pss::Core::Graphics::PsmShaderProgram::SetUniformValue ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Graphics.PsmShaderProgram::SetUniformValue(int,int,int,Sce.PlayStation.Core.Vector3&,Sce.PlayStation.Core.Graphics.ShaderUniformType)", Sce::Pss::Core::Graphics::PsmShaderProgram::SetUniformValue ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Graphics.PsmShaderProgram::SetUniformValue(int,int,int,Sce.PlayStation.Core.Vector2&,Sce.PlayStation.Core.Graphics.ShaderUniformType)", Sce::Pss::Core::Graphics::PsmShaderProgram::SetUniformValue ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Graphics.PsmShaderProgram::SetUniformValue(int,int,int,single&,Sce.PlayStation.Core.Graphics.ShaderUniformType)", Sce::Pss::Core::Graphics::PsmShaderProgram::SetUniformValue ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Graphics.PsmShaderProgram::SetUniformValue(int,int,int,int&,Sce.PlayStation.Core.Graphics.ShaderUniformType)", Sce::Pss::Core::Graphics::PsmShaderProgram::SetUniformValue ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Graphics.PsmShaderProgram::SetUniformValue2(int,int,Sce.PlayStation.Core.Matrix4[],Sce.PlayStation.Core.Graphics.ShaderUniformType,int,int,int)", Sce::Pss::Core::Graphics::PsmShaderProgram::SetUniformValue2 ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Graphics.PsmShaderProgram::SetUniformValue2(int,int,Sce.PlayStation.Core.Vector4[],Sce.PlayStation.Core.Graphics.ShaderUniformType,int,int,int)", Sce::Pss::Core::Graphics::PsmShaderProgram::SetUniformValue2 ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Graphics.PsmShaderProgram::SetUniformValue2(int,int,Sce.PlayStation.Core.Vector3[],Sce.PlayStation.Core.Graphics.ShaderUniformType,int,int,int)", Sce::Pss::Core::Graphics::PsmShaderProgram::SetUniformValue2 ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Graphics.PsmShaderProgram::SetUniformValue2(int,int,Sce.PlayStation.Core.Vector2[],Sce.PlayStation.Core.Graphics.ShaderUniformType,int,int,int)", Sce::Pss::Core::Graphics::PsmShaderProgram::SetUniformValue2 ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Graphics.PsmShaderProgram::SetUniformValue2(int,int,single[],Sce.PlayStation.Core.Graphics.ShaderUniformType,int,int,int)", Sce::Pss::Core::Graphics::PsmShaderProgram::SetUniformValue2 ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Graphics.PsmShaderProgram::SetUniformValue2(int,int,int[],Sce.PlayStation.Core.Graphics.ShaderUniformType,int,int,int)", Sce::Pss::Core::Graphics::PsmShaderProgram::SetUniformValue2 ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Graphics.PsmShaderProgram::SetAttributeValue2(int,int,single[])", Sce::Pss::Core::Graphics::PsmShaderProgram::SetAttributeValue2 ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Graphics.PsmShaderProgram::GetUniformTexture(int,int,int&)", Sce::Pss::Core::Graphics::PsmShaderProgram::GetUniformTexture ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Graphics.PsmShaderProgram::GetAttributeStream(int,int,int&)", Sce::Pss::Core::Graphics::PsmShaderProgram::GetAttributeStream ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Graphics.PsmShaderProgram::SetAttributeStream(int,int,int)", Sce::Pss::Core::Graphics::PsmShaderProgram::SetAttributeStream ),
		
		/*
		* changelogs says something about adding VertexBuffer.VertexBuffer(int,int,int,VertexFormat[]) in SDK2.00
		* as well as VertexBuffer.InstanceDivisor;
		* not sure exactly what that is about however;
		*/
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Graphics.PsmVertexBuffer::Create(int,int,int,int,Sce.PlayStation.Core.Graphics.VertexFormat[],int&)", Sce::Pss::Core::Graphics::PsmVertexBuffer::Create),

		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Graphics.PsmVertexBuffer::Delete(int)", Sce::Pss::Core::Graphics::PsmVertexBuffer::Delete ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Graphics.PsmVertexBuffer::AddRef(int)", Sce::Pss::Core::Graphics::PsmVertexBuffer::AddRef ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Graphics.PsmVertexBuffer::SetVertices(int,System.Array,int,int,int)", Sce::Pss::Core::Graphics::PsmVertexBuffer::SetVertices ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Graphics.PsmVertexBuffer::SetVertices2(int,int,System.Array,Sce.PlayStation.Core.Graphics.VertexFormat,Sce.PlayStation.Core.Vector4&,Sce.PlayStation.Core.Vector4&,int,int,int,int,int)", Sce::Pss::Core::Graphics::PsmVertexBuffer::SetVertices2 ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Graphics.PsmVertexBuffer::SetIndices(int,uint16[],int,int,int)", Sce::Pss::Core::Graphics::PsmVertexBuffer::SetIndices ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Graphics.PsmPixelBuffer::Create(Sce.PlayStation.Core.Graphics.PixelBufferType,int,int,bool,Sce.PlayStation.Core.Graphics.PixelFormat,Sce.PlayStation.Core.Graphics.PixelBufferOption,Sce.PlayStation.Core.Graphics.InternalOption,int&)", Sce::Pss::Core::Graphics::PsmPixelBuffer::Create ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Graphics.PsmPixelBuffer::Delete(int)", Sce::Pss::Core::Graphics::PsmPixelBuffer::Delete ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Graphics.PsmPixelBuffer::AddRef(int)", Sce::Pss::Core::Graphics::PsmPixelBuffer::AddRef ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Graphics.PsmPixelBuffer::GetInfo(int,Sce.PlayStation.Core.Graphics.PixelBufferType&,int&,int&,int&,Sce.PlayStation.Core.Graphics.PixelFormat&,Sce.PlayStation.Core.Graphics.PixelBufferOption&)", Sce::Pss::Core::Graphics::PsmPixelBuffer::GetInfo ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Graphics.PsmTexture::FromFile(Sce.PlayStation.Core.Graphics.PixelBufferType,string,bool,Sce.PlayStation.Core.Graphics.PixelFormat,int&)", Sce::Pss::Core::Graphics::PsmTexture::FromFile ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Graphics.PsmTexture::FromImage(Sce.PlayStation.Core.Graphics.PixelBufferType,byte[],bool,Sce.PlayStation.Core.Graphics.PixelFormat,int&)", Sce::Pss::Core::Graphics::PsmTexture::FromImage ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Graphics.PsmTexture::SetFilter(int,Sce.PlayStation.Core.Graphics.TextureFilter&)", Sce::Pss::Core::Graphics::PsmTexture::SetFilter ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Graphics.PsmTexture::SetWrap(int,Sce.PlayStation.Core.Graphics.TextureWrap&)", Sce::Pss::Core::Graphics::PsmTexture::SetWrap ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Graphics.PsmTexture::SetMaxAnisotropy(int,single)", Sce::Pss::Core::Graphics::PsmTexture::SetMaxAnisotropy ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Graphics.PsmTexture::SetPixels(int,int,Sce.PlayStation.Core.Graphics.TextureCubeFace,System.Array,Sce.PlayStation.Core.Graphics.PixelFormat,int,int,int,int,int,int)", Sce::Pss::Core::Graphics::PsmTexture::SetPixels ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Graphics.PsmTexture::GenerateMipmap(int)", Sce::Pss::Core::Graphics::PsmTexture::GenerateMipmap ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Graphics.PsmFrameBuffer::Create(int&)", Sce::Pss::Core::Graphics::PsmFrameBuffer::Create ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Graphics.PsmFrameBuffer::Delete(int)", Sce::Pss::Core::Graphics::PsmFrameBuffer::Delete ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Graphics.PsmFrameBuffer::AddRef(int)", Sce::Pss::Core::Graphics::PsmFrameBuffer::AddRef ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Graphics.PsmFrameBuffer::SetColorTarget(int,int,int,Sce.PlayStation.Core.Graphics.TextureCubeFace,int&)", Sce::Pss::Core::Graphics::PsmFrameBuffer::SetColorTarget ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Graphics.PsmFrameBuffer::SetDepthTarget(int,int,int,Sce.PlayStation.Core.Graphics.TextureCubeFace,int&)", Sce::Pss::Core::Graphics::PsmFrameBuffer::SetDepthTarget ),
		PSM_MONO_FUNC_END()
	};

	inline PsmMonoFunc EnvironmentFunctions[] {
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Environment.Log::WriteNative(string)", Sce::Pss::Core::Environment::Log::WriteNative ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Environment.Log::GetNeedsRedirection()", Sce::Pss::Core::Environment::Log::GetNeedsRedirection ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Environment.SystemEvents::CheckEventsNative(Sce.PlayStation.Core.Environment.SystemEvents/InternalData&)", Sce::Pss::Core::Environment::SystemEvents::CheckEventsNative ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Environment.SystemParameters::GetInt(Sce.PlayStation.Core.Environment.SystemParameters/ParameterKey,int&)", Sce::Pss::Core::Environment::SystemParameters::GetInt ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Environment.SystemParameters::GetFloat(Sce.PlayStation.Core.Environment.SystemParameters/ParameterKey,single&)", Sce::Pss::Core::Environment::SystemParameters::GetFloat ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Environment.SystemParameters::GetString(Sce.PlayStation.Core.Environment.SystemParameters/ParameterKey,string&)", Sce::Pss::Core::Environment::SystemParameters::GetString ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Environment.SystemMemory::GetMemoryUsage(bool)", Sce::Pss::Core::Environment::SystemMemory::GetMemoryUsage ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Environment.PersistentMemory::WriteNative(byte[])", Sce::Pss::Core::Environment::PersistentMemory::WriteNative ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Environment.PersistentMemory::ReadNative(byte[])", Sce::Pss::Core::Environment::PersistentMemory::ReadNative ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Environment.Shell::ExecuteNative(Sce.PlayStation.Core.Environment.Shell/Action&)", Sce::Pss::Core::Environment::Shell::ExecuteNative ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Environment.TextInputDialog::NewNative(Sce.PlayStation.Core.Environment.CommonDialogType,int&)", Sce::Pss::Core::Environment::CommonDialog::NewNative ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Environment.TextInputDialog::ReleaseNative(Sce.PlayStation.Core.Environment.CommonDialogType,int)", Sce::Pss::Core::Environment::CommonDialog::ReleaseNative ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Environment.TextInputDialog::OpenNative(Sce.PlayStation.Core.Environment.CommonDialogType,int,Sce.PlayStation.Core.Environment.TextInputDialog/Arguments&)", Sce::Pss::Core::Environment::CommonDialog::OpenNative ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Environment.TextInputDialog::AbortNative(Sce.PlayStation.Core.Environment.CommonDialogType,int)", Sce::Pss::Core::Environment::CommonDialog::AbortNative ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Environment.TextInputDialog::GetState(Sce.PlayStation.Core.Environment.CommonDialogType,int,Sce.PlayStation.Core.Environment.CommonDialogState&)", Sce::Pss::Core::Environment::CommonDialog::GetState ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Environment.TextInputDialog::GetResult(Sce.PlayStation.Core.Environment.CommonDialogType,int,Sce.PlayStation.Core.Environment.CommonDialogResult&,Sce.PlayStation.Core.Environment.TextInputDialog/Results&)", Sce::Pss::Core::Environment::CommonDialog::GetResult ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Services.AccountInformation::GetUniqueID(byte[])", Sce::Pss::Core::Services::AccountInformation::GetUniqueID ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Services.InAppPurchaseDialog::NewNative(int,int&)", Sce::Pss::Core::Environment::CommonDialog::NewNative ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Services.InAppPurchaseDialog::ReleaseNative(int,int)", Sce::Pss::Core::Environment::CommonDialog::ReleaseNative ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Services.InAppPurchaseDialog::OpenNative(int,int,Sce.PlayStation.Core.Services.InAppPurchaseDialog/CommandArguments&)", Sce::Pss::Core::Environment::CommonDialog::OpenNative ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Services.InAppPurchaseDialog::AbortNative(int,int)", Sce::Pss::Core::Environment::CommonDialog::AbortNative ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Services.InAppPurchaseDialog::GetState(int,int,Sce.PlayStation.Core.Environment.CommonDialogState&)", Sce::Pss::Core::Environment::CommonDialog::GetState ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Services.InAppPurchaseDialog::GetResult(int,int,Sce.PlayStation.Core.Environment.CommonDialogResult&,Sce.PlayStation.Core.Services.InAppPurchaseDialog/CommandResults&)", Sce::Pss::Core::Environment::CommonDialog::GetResult ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Environment.Clipboard::SetTextNative(string)", Sce::Pss::Core::Environment::Clipboard::SetTextNative ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Environment.Clipboard::GetTextNative(string&)", Sce::Pss::Core::Environment::Clipboard::GetTextNative ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Environment.NetworkInformation::GetNetworkInterfaceTypeNative()", Sce::Pss::Core::Environment::NetworkInformation::GetNetworkInterfaceTypeNative ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Device.CameraImportDialog::NewNative(int,int&)", Sce::Pss::Core::Environment::CommonDialog::NewNative ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Device.CameraImportDialog::ReleaseNative(int,int)", Sce::Pss::Core::Environment::CommonDialog::ReleaseNative ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Device.CameraImportDialog::OpenNative(int,int,Sce.PlayStation.Core.Device.CameraImportDialog/DialogArguments&)", Sce::Pss::Core::Environment::CommonDialog::OpenNative ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Device.CameraImportDialog::AbortNative(int,int)", Sce::Pss::Core::Environment::CommonDialog::AbortNative ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Device.CameraImportDialog::GetState(int,int,Sce.PlayStation.Core.Environment.CommonDialogState&)", Sce::Pss::Core::Environment::CommonDialog::GetState ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Device.CameraImportDialog::GetResult(int,int,Sce.PlayStation.Core.Environment.CommonDialogResult&,Sce.PlayStation.Core.Device.CameraImportDialog/DialogResults&)", Sce::Pss::Core::Environment::CommonDialog::GetResult ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Device.PhotoImportDialog::NewNative(int,int&)", Sce::Pss::Core::Environment::CommonDialog::NewNative ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Device.PhotoImportDialog::ReleaseNative(int,int)", Sce::Pss::Core::Environment::CommonDialog::ReleaseNative ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Device.PhotoImportDialog::OpenNative(int,int,Sce.PlayStation.Core.Device.PhotoImportDialog/DialogArguments&)", Sce::Pss::Core::Environment::CommonDialog::OpenNative ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Device.PhotoImportDialog::AbortNative(int,int)", Sce::Pss::Core::Environment::CommonDialog::AbortNative ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Device.PhotoImportDialog::GetState(int,int,Sce.PlayStation.Core.Environment.CommonDialogState&)", Sce::Pss::Core::Environment::CommonDialog::GetState ),
		PSM_MONO_FUNCTION( "Sce.PlayStation.Core.Device.PhotoImportDialog::GetResult(int,int,Sce.PlayStation.Core.Environment.CommonDialogResult&,Sce.PlayStation.Core.Device.PhotoImportDialog/DialogResults&)", Sce::Pss::Core::Environment::CommonDialog::GetResult ),
		PSM_MONO_FUNC_END()
	};
}

#endif