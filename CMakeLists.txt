cmake_minimum_required(VERSION 3.1)
project("xrandom")

add_executable(xrandom xrandom.c)
add_executable(php-xrandom php-xrandom.c)

enable_testing()
add_executable(test-xrandom test-xrandom.c)
add_executable(test-php-xrandom test-php-xrandom.c)
add_test(test-xrandom test-xrandom)
add_test(test-php-xrandom test-php-xrandom)

add_library(freebsd-random freebsd-rand.c freebsd-random.c)
add_library(linux-random glibc-rand.c glibc-rand_r.c glibc-random.c glibc-random_r.c)
add_library(ixrandom INTERFACE)
target_link_libraries(ixrandom INTERFACE freebsd-random linux-random)

add_library(php-random php-random.c)
target_link_libraries(php-random ixrandom)

target_link_libraries(xrandom ixrandom)
target_link_libraries(php-xrandom php-random)
target_link_libraries(test-xrandom ixrandom)
target_link_libraries(test-php-xrandom php-random)
