project('pa3_compression', 'cpp',
	version : '0.0.1',
	default_options : ['warning_level=3',
			   'b_coverage=true',
			   'cpp_std=c++14'])

# === src dependencies ===
cxxopts_proj = subproject('cxxopts')
cxxopts_dep = cxxopts_proj.get_variable('cxxopts_dep')
# === end src dependencies ===
subdir('src')

# === test dependencies ===
gtest_proj = subproject('gtest')
gtest_dep = gtest_proj.get_variable('gtest_main_dep')
if not gtest_dep.found()
    error('MESON_SKIP_TEST: gtest not installed.')
endif
# === end test dependencies ===
subdir('test')

# === custom commands ===
run_target('cov',
    command : ['./build_scripts/generate_coverage_report'])

run_target('clang-tidy',
    command : ['./build_scripts/tidy.sh'])

run_target('cppcheck', command : ['cppcheck',
    '--enable=all', '--std=c++14', '--error-exitcode=1', '--suppres=missingInclude',
    'src', 'test'])
# === end custom commands ===
