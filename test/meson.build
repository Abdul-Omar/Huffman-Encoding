inc = include_directories('.')

test_HCTree_exe = executable('test_HCTree.cpp.executable',
    sources: ['test_HCTree.cpp'],
    dependencies : [bitStream_input_dep, bitStream_output_dep, encoder_dep, gtest_dep],
    include_directories : inc)
test('my HCTree test', test_HCTree_exe)

test_bitInputStream_exe = executable('test_BitInputStream.cpp.executable',
    sources: ['test_BitInputStream.cpp'],
    dependencies : [bitStream_input_dep, bitStream_output_dep, encoder_dep, gtest_dep],
    include_directories : inc)
test('my BitInputStream test', test_bitInputStream_exe)

test_bitOutputStream_exe = executable('test_BitOutputStream.cpp.executable',
    sources: ['test_BitOutputStream.cpp'],
    dependencies : [bitStream_output_dep, bitStream_input_dep, encoder_dep, gtest_dep],
    include_directories : inc)
test('my BitOutputStream test', test_bitOutputStream_exe)

