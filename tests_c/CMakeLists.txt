cmake_minimum_required(VERSION 3.20)
set (CMAKE_CXX_STANDARD 17)
include(GNUInstallDirs)

enable_testing()

add_executable (test_trace test_trace.cpp)
target_link_libraries(test_trace fcl_static ${CMAKE_THREAD_LIBS_INIT})
target_include_directories(test_trace PRIVATE .. ../fcl)
add_test(TestTrace test_trace)

add_executable (test_fcl test_fcl.cpp)
target_link_libraries(test_fcl fcl_static ${CMAKE_THREAD_LIBS_INIT})
target_include_directories(test_fcl PRIVATE .. ../fcl)
add_test(TestFCL test_fcl)

add_executable (test_layer test_layer.cpp)
target_link_libraries(test_layer fcl_static ${CMAKE_THREAD_LIBS_INIT})
target_include_directories(test_layer PRIVATE .. ../fcl)
add_test(TestLayer test_layer)

add_executable (test_neuron test_neuron.cpp)
target_link_libraries(test_neuron fcl_static ${CMAKE_THREAD_LIBS_INIT})
target_include_directories(test_neuron PRIVATE .. ../fcl)
add_test(TestNeuron test_neuron)

add_executable (test_fcl_filters test_fcl_filters.cpp)
target_link_libraries(test_fcl_filters fcl_static ${CMAKE_THREAD_LIBS_INIT})
target_include_directories(test_fcl_filters PRIVATE .. ../fcl)
add_test(TestNeuron test_neuron)
