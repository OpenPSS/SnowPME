project('LibPssMono', 'c',
version: '0.1',
default_options: ['warning_level=0', 'cpp_std=c++20', 'default_library=static'])
mod = import('unstable-external_project')

c = meson.get_compiler('c')
mono_include_dir = include_directories('include')

# generate configure script
pss_mono_subdir = join_paths(meson.current_source_dir(), 'pss-mono')
pss_mono_configure = join_paths(pss_mono_subdir, 'configure')

r = run_command(['autoreconf', '-ivf', pss_mono_subdir], check: true)

p = mod.add_project(pss_mono_configure,
    configure_options : [
        '--enable-pss',
        '--prefix=@PREFIX@',
    ],
    env: {
        'CFLAGS': '-O2'
    },
    verbose: true
)

monosgen_dep = p.dependency('monosgen-static')

LibPssMono_dep = declare_dependency(
include_directories: mono_include_dir,
dependencies: [
    monosgen_dep
])
