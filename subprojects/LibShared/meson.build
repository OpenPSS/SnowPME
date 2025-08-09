project('Shared', ['cpp', 'c'],
  version: '0.1',
  default_options:  {
    'warning_level': '0',
    'cpp_std': 'c++20',
    'c_std': 'c11',
    'default_library': 'static'
  }
)
cpp = meson.get_compiler('cpp')
c = meson.get_compiler('c')

dirbase = meson.current_source_dir()
include_libs = include_directories('.')

libShared = static_library('Shared',
	'Config.cpp',
	'Threading/ProgressTracker.cpp',
	'Debug/Logger.cpp',
	'Debug/Assert.cpp',
	'String/Path.cpp',
	'String/Format.cpp',
	'Windowing/CallbackBase.cpp',
	'Windowing/Event.cpp',
	'Windowing/EventQueue.cpp',
	'Windowing/WindowControl.cpp',
	'Package/PackageExtractor.cpp',
	'Crypto/aes.c',
	'Crypto/aes_x86.c',
	'Crypto/md5.c',
	'Crypto/sha1.c',
	'Crypto/sha256.c',
	'Crypto/hmac_sha256.c',
	include_directories: [ include_libs ],
	c_args: ['-maes', '-mssse3'])
	
LibShared_dep = declare_dependency(
	include_directories: include_libs,
	link_with: libShared
)
