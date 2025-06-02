project('SnowPME', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3', 'cpp_std=c++20'])

cpp = meson.get_compiler('cpp')

# External libraries ...
External = subproject('External')
external_dep = External.get_variable('external_dep')

# All static libraries
LibCXML = subproject('LibCXML')
LibGLAD = subproject('LibGLAD')
LibImGui = subproject('LibImGui')
LibMonoBridge = subproject('LibMonoBridge')
LibPSM = subproject('LibPSM')
LibShared = subproject('LibShared')
LibSnowPME = subproject('LibSnowPME')

libCXML_dep = LibCXML.get_variable('libCXML_dep')
libGLAD_dep = LibGLAD.get_variable('libGLAD_dep')
libImGui_dep = LibImGui.get_variable('libImGui_dep')
libMonoBridge_dep = LibMonoBridge.get_variable('libMonoBridge_dep')
libPSM_dep = LibPSM.get_variable('libPSM_dep')
libShared_dep = LibShared.get_variable('libShared_dep')
libSnowPME_dep = LibSnowPME.get_variable('libSnowPME_dep')


executable('SnowPME',
            'SnowPME/SnowPME.cpp',
            'SnowPME/Program.cpp',
            dependencies: [
				external_dep,
                libCXML_dep,
                libGLAD_dep,
                libImGui_dep,
                libMonoBridge_dep,
                libShared_dep,
                libPSM_dep,
                libSnowPME_dep
            ])

