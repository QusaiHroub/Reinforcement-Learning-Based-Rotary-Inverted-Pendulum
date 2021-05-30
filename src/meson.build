RIP_RLB_sources = [
  'main.cc',
  'main_window.cc',
  'pendulum.cc',
  'manager.cc',
]

subdir('utils')

cpp = meson.get_compiler('cpp')

RIP_RLB_deps = [
  dependency('gtkmm-3.0', version: '>= 3.18'),
  dependency('threads'),
  cpp.find_library('wiringPi'),
]

RIP_RLB_cpp_args = [
  '-fconcepts',
  '-lwiringPi',
]

executable('RIP_RLB', RIP_RLB_sources,
  dependencies: RIP_RLB_deps,
  install: true,
  cpp_args : RIP_RLB_cpp_args,
)