project('SnowPMEBenchmark', 'cpp',
    default_options : ['cpp_std=c++20', 'default_library=static']
)

benchmark = subproject('google-benchmark')
LibPSM = subproject('LibPSM')
LibShared = subproject('LibShared')

google_benchmark_dep = benchmark.get_variable('google_benchmark_dep')
LibPSM_dep = LibPSM.get_variable('LibPSM_dep')
LibShared_dep = LibPSM.get_variable('LibShared_dep')

executable('SnowPMEBenchmark',
    'main.cpp',
    dependencies: [google_benchmark_dep, LibPSM_dep, LibShared_dep]
)
