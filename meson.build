project('SnowPME', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3', 'cpp_std=c++20'])

cpp = meson.get_compiler('cpp')

LibPSM = subproject('LibPSM')
LibCXML = subproject('LibCXML')
LibShared = subproject('LibShared')
LibSnowPME = subproject('LibSnowPME')
LibPSSMono = subproject('LibPSSMono')
External = subproject('External')

LibPSM_dep = LibPSM.get_variable('LibPSM_dep')
LibCXML_dep = LibCXML.get_variable('libCXML_dep')
LibShared_dep = LibShared.get_variable('LibShared_dep')
LibSnowPME_dep = LibSnowPME.get_variable('LibSnowPME_dep')
LibPSSMono_dep = LibPSSMono.get_variable('LibPSSMono_dep')
External_dep = External.get_variable('External_dep')

executable('SnowPME',
	'SnowPME/SnowPME.cpp',
	'SnowPME/Program.cpp',
	dependencies : [
		LibPSM_dep,
		LibCXML_dep,
		LibShared_dep,
		LibSnowPME_dep,
		LibPSSMono_dep,
		External_dep
	]
)
