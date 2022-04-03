# CMake generated Testfile for 
# Source directory: /home/ivan/Documents/SLAE4SEM/tests
# Build directory: /home/ivan/Documents/SLAE4SEM/cmake-build-debug/tests
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(test_csr_matrix "/home/ivan/Documents/SLAE4SEM/cmake-build-debug/tests/test_csr_matrix")
set_tests_properties(test_csr_matrix PROPERTIES  _BACKTRACE_TRIPLES "/home/ivan/Documents/SLAE4SEM/tests/CMakeLists.txt;24;add_test;/home/ivan/Documents/SLAE4SEM/tests/CMakeLists.txt;0;")
add_test(test_power_method_csr "/home/ivan/Documents/SLAE4SEM/cmake-build-debug/tests/test_power_method_csr")
set_tests_properties(test_power_method_csr PROPERTIES  _BACKTRACE_TRIPLES "/home/ivan/Documents/SLAE4SEM/tests/CMakeLists.txt;24;add_test;/home/ivan/Documents/SLAE4SEM/tests/CMakeLists.txt;0;")
add_test(test_power_method_dense "/home/ivan/Documents/SLAE4SEM/cmake-build-debug/tests/test_power_method_dense")
set_tests_properties(test_power_method_dense PROPERTIES  _BACKTRACE_TRIPLES "/home/ivan/Documents/SLAE4SEM/tests/CMakeLists.txt;24;add_test;/home/ivan/Documents/SLAE4SEM/tests/CMakeLists.txt;0;")
add_test(test_qr "/home/ivan/Documents/SLAE4SEM/cmake-build-debug/tests/test_qr")
set_tests_properties(test_qr PROPERTIES  _BACKTRACE_TRIPLES "/home/ivan/Documents/SLAE4SEM/tests/CMakeLists.txt;24;add_test;/home/ivan/Documents/SLAE4SEM/tests/CMakeLists.txt;0;")
subdirs("googletest-master")
