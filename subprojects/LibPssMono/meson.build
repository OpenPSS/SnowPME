project('LibPssMono', 'c',
version: '0.1',
default_options: ['warning_level=0', 'cpp_std=c++20', 'default_library=static'])

mod = import('unstable-external_project')

c = meson.get_compiler('c')
bin_dir = meson.current_build_dir()
mono_include_dir = include_directories('include')

# generate configure script
pss_mono_subdir = join_paths(meson.current_source_dir(), 'pss-mono')
pss_mono_configure = join_paths(pss_mono_subdir, 'configure')
pss_mono_autogen = join_paths(pss_mono_subdir, 'autogen.sh')

#pss_mono_autogen_dep = custom_target(
#            'pss_autogen', 
#            command: pss_mono_autogen,
#           # build_subdir: pss_mono_subdir,
#            build_always_stale: true,
#            output: ['configure']
#)

r = run_command(['cd', 'pss-mono'])
r = run_command(['./autogen.sh'])


p = mod.add_project(pss_mono_configure,
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
