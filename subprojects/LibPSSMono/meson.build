project('LibPSSMono', 'c')

bin_dir = meson.current_build_dir()

mod = import('unstable-external_project')
p = mod.add_project('configure', verbose: true)
eglib_dep = p.dependency('eglib-static')
monosgen_dep = p.dependency('monosgen-static')
monoruntimesgen_dep = p.dependency('monoruntimesgen')

LibPSSMono_dep = declare_dependency(dependencies: [
	eglib_dep, monosgen_dep, monoruntimesgen_dep
])
