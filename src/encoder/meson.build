inc = include_directories('.')

encoder = library('encoder', dependencies : [bitStream_input_dep, bitStream_output_dep], sources: ['HCTree.cpp'])

encoder_dep = declare_dependency(include_directories: inc,
   link_with: encoder)
