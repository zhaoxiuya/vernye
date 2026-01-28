project(
  'vernye',
  'c',
  meson_version : '>= 1.3.0',
  version : '0.1.0',
  default_options : ['warning_level=3', 'c_std=c99'],
)

inc = include_directories('include')

libzxl = static_library('zxl', 'src/zxl.c', include_directories: inc)

test_exe = executable(
  'test_zxl',
  'test/test.c',
  link_with: libzxl,
  include_directories: inc
)

test('zxl_test', test_exe)
