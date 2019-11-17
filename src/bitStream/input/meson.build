inc = include_directories('.',)

bitStream_input = library('bitStream_input', sources: ['BitInputStream.cpp', 'BitInputStream.hpp'])

bitStream_input_dep = declare_dependency(include_directories: inc,
   link_with: bitStream_input)
