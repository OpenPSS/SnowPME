project('SnowPME', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3', 'cpp_std=c++14'])

cpp = meson.get_compiler('cpp')

# include projects
LibCXML = subproject('LibCXML')
LibGLAD = subproject('LibGLAD')
LibImGui = subproject('LibImGui')
LibMonoBridge = subproject('LibMonoBridge')
LibPSM = subproject('LibPSM')
LibShared = subproject('LibShared')
LibSnowPME = subproject('LibSnowPME')

executable('SnowPME',
           'SnowPME/SnowPME.cpp',
		   'SnowPME/Program.cpp',
            dependencies : [
				declare_dependency(link_with: LibCXML),
				declare_dependency(link_with: LibGLAD),
				declare_dependency(link_with: LibImGui),
				declare_dependency(link_with: LibMonoBridge),
				declare_dependency(link_with: LibPSM),
				declare_dependency(link_with: LibShared),
				declare_dependency(link_with: LibSnowPME)
            ])