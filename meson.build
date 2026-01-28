project(
  'vernye',
  'c',
  meson_version : '>= 1.3.0',
  version : '0.1.0',
  default_options : ['warning_level=3'],
)

dependencies = [
]

exe = executable(
  'vernye',
  'vernye.c',
  dependencies : dependencies,
  install : true,
)

test('basic', exe)
