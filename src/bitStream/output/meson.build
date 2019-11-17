inc = include_directories('.')

bitStream_output = library('bitStream_output', sources: ['BitOutputStream.cpp', 'BitOutputStream.hpp'])

bitStream_output_dep = declare_dependency(include_directories: inc,
   link_with: bitStream_output)
