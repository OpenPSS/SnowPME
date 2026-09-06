project('LibPssMono', 'c',
version: '0.1',
default_options: ['warning_level=0', 'cpp_std=c++20', 'default_library=static'])

mod = import('unstable-external_project')

c = meson.get_compiler('c')
bin_dir = meson.current_build_dir()
mono_include_dir = include_directories('include')

# generate configure script
pss_mono_autogen = join_paths(meson.current_source_dir(), 'pss-mono/autogen.sh')
pss_mono_autogen_dep = custom_target('pss-mono-autogen', command: [pss_mono_autogen], output: 'pss-mono/configure')

p = mod.add_project('pss-mono/configure',
    configure_options : [
        '--enable-pss',
    ],
	env: {
		'CFLAGS': '-O2'
	},
    depends: [ 
        pss_mono_autogen_dep 
    ],
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
