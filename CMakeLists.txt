cmake_minimum_required(VERSION 3.8)
project(C_Primer_Plus_Exercises)

set(CMAKE_C_STANDARD 99)
#set(CMAKE_VERBOSE_MAKEFILE ON)

set(ch03_e1 ch03/exercise1.c practise/attribute/attribute_test.c)
set(ch03_e2 ch03/exercise2.c)
set(function_pointer practise/function/function_pointer.c practise/variable_param/variable_param_test.c)
set(function_pointer_in_struct practise/function/function_pointer_in_struct.c)
set(thread_test practise/thread/thread_test.c)
set(varible_test practise/variable_param/variable_param_test.c)
set(kernel_test_time_after_test practise/kernel_function/time_after_test.c)

set(attibute_test practise/attribute/attribute_test.c)
set(dynamic_array_test practise/array/dynamic_array_test.c)



#set(SOURCE_FILES ./practise/function_pointer.c )
add_executable(ch03_e1 ${ch03_e1})
add_executable(ch03_e2 ${ch03_e2})
add_executable(thread_test ${thread_test})
add_executable(function_pointer ${function_pointer})
add_executable(function_pointer_in_struct ${function_pointer_in_struct})
add_executable(varible_test ${varible_test} )
add_executable(kernel_test_time_after_test ${kernel_test_time_after_test} practise/kernel_function/time_after_test.c)
add_executable(attribute_test ${attibute_test} practise/attribute/attribute_test.c)
add_executable(dynamic_array_test ${dynamic_array_test})
