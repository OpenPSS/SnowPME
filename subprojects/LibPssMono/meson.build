project('LibPssMono', 'c')

c = meson.get_compiler('c')
bin_dir = meson.current_build_dir()
mono_include_dir = include_directories('include')

mod = import('unstable-external_project')
p = mod.add_project('configure',
	env: {
		'CFLAGS': '-O2'
	},
	verbose: true
)
eglib_dep = p.dependency('eglib-static')
monosgen_dep = p.dependency('monosgen-static')
monoruntimesgen_dep = p.dependency('monoruntimesgen')

LibPssMono_dep = declare_dependency(
include_directories: mono_include_dir,
dependencies: [
	eglib_dep, monosgen_dep, monoruntimesgen_dep
])
