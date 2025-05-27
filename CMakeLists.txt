cmake_minimum_required(VERSION 3.5) 
project(crypt_dir)

set(CMAKE_CXX_STANDARD 17) 
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenSSL REQUIRED)

include_directories(${OPENSSL_INCLUDE_DIR}) 
add_executable(cryptor main.cpp Crypt.cpp Aes256.cpp Scanner.cpp )
target_compile_options(cryptor PRIVATE -Wno-deprecated-declarations)
target_link_libraries(cryptor ${OPENSSL_LIBRARIES})