inc_dirs = '../include'

pmt_conv_dep = dependency('pmt_converter', required: true)
zmq_dep = dependency('cppzmq', required: true)
gr4_zeromq_headers = dependency('gnuradio4-zeromq-headers',required: true)

exe = executable('zmq_loopback', 'zmq_loopback.cpp',
  install : true,
  include_directories: inc_dirs,
  dependencies: [gr4_dep, gr4_blocklib_dep, pmt_conv_dep, zmq_dep, gr4_zeromq_headers])

exe = executable('zmq_loopback_square', 'zmq_loopback_square.cpp',
  install : true,
  include_directories: inc_dirs,
  dependencies: [gr4_dep, gr4_blocklib_dep, pmt_conv_dep, zmq_dep, gr4_zeromq_headers])


#exe2 = executable('gr4-dynamic-flowgraph', 'gr4-dynamic-example.cpp',
#  install : true,
#  include_directories: inc_dirs,
#  dependencies: [gr4_dep, gr4_blocklib_dep])

