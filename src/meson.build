subdir('bitStream')
subdir('encoder')

compress_exe = executable('compress.cpp.executable',
	sources: ['compress.cpp'],
	dependencies : [bitStream_input_dep, bitStream_output_dep, encoder_dep, cxxopts_dep],
	install : true)

uncompress_exe = executable('uncompress.cpp.executable',
	sources: ['uncompress.cpp'],
	dependencies : [bitStream_input_dep, bitStream_output_dep, encoder_dep, cxxopts_dep],
	install : true)
