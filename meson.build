project('SnowPME', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3', 'cpp_std=c++20', 'default_library=static'])

cpp = meson.get_compiler('cpp')

include_libs = include_directories('SnowPME')

GlobalInclude = subproject('GlobalInclude')
GlobalInclude_dep = GlobalInclude.get_variable('GlobalInclude_dep')

libC_dep = cpp.find_library('libc', required: true, static: true)
libCPP_dep = cpp.find_library('libc++', required: true, static: true)


LibPSM = subproject('LibPSM')
LibCXML = subproject('LibCXML')
LibShared = subproject('LibShared')
LibSnowPME = subproject('LibSnowPME')
LibPssMono = subproject('LibPssMono')

LibPSM_dep = LibPSM.get_variable('LibPSM_dep')
LibCXML_dep = LibCXML.get_variable('libCXML_dep')
LibShared_dep = LibShared.get_variable('LibShared_dep')
LibSnowPME_dep = LibSnowPME.get_variable('LibSnowPME_dep')
LibPssMono_dep = LibPssMono.get_variable('LibPssMono_dep')

executable('SnowPME',
	'SnowPME/SnowPME.cpp',
	'SnowPME/Program.cpp',
	include_directories: include_libs,
	dependencies : [
		GlobalInclude_dep,
		LibPSM_dep,
		LibCXML_dep,
		LibShared_dep,
		LibSnowPME_dep,
		LibPssMono_dep,

		libC_dep,
		libCPP_dep
	]
)

subproject('SnowPMEBenchmark')
