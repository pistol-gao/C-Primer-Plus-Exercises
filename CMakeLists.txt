cmake_minimum_required(VERSION 3.8)
project(C_Primer_Plus_Exercises)

set(CMAKE_C_STANDARD 99)
#set(CMAKE_VERBOSE_MAKEFILE ON)

set(function_pointer practise/function/function_pointer.c practise/variable_param/variable_param_test.c)
set(function_pointer_in_struct practise/function/function_pointer_in_struct.c)
set(thread_test practise/thread/thread_test.c)
set(varible_test practise/variable_param/variable_param_test.c)


#set(SOURCE_FILES ./practise/function_pointer.c )
add_executable(thread_test ${thread_test})
add_executable(function_pointer ${function_pointer})
add_executable(function_pointer_in_struct ${function_pointer_in_struct})
add_executable(varible_test ${varible_test})