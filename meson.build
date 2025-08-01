project('gr4-block-tutorial', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3',
                     'cpp_std=c++23'])


cmake = import('cmake')


gr4_dep = dependency('gnuradio4')
gr4_blocklib_dep = declare_dependency(
  link_args: ['/usr/local/lib/libgnuradio-blocklib-core.so'],
  dependencies: [],
  include_directories: include_directories('/usr/local/include')
)


# ut_dep = dependency('boost-ut')
boost_ut_proj = subproject('boost-ut')
ut_dep = boost_ut_proj.get_variable('boostut_dep')

subdir('blocks')
