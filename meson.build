project('DSCpp', 'cpp')

add_global_arguments('-std=c++17', language : 'cpp')
add_global_arguments('-Wall', language : 'cpp')
add_global_arguments('-Wextra', language : 'cpp')
add_global_arguments('-Wnon-virtual-dtor', language : 'cpp')
add_global_arguments('-pedantic', language : 'cpp')
add_global_arguments('-Wa,-mbig-obj', language : 'cpp')

executable('t', 'test_bench.cpp')
