cmake_minimum_required(VERSION 3.5.1)

function(set_target_cpp_standard target standard)
set_target_properties(
    ${target}
    PROPERTIES
        CXX_STANDARD ${standard}
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
)
endfunction()

set(DIR ${CMAKE_CURRENT_SOURCE_DIR})

project(cpplox LANGUAGES CXX)

add_executable(${PROJECT_NAME} 
	${DIR}/main.cpp
	${DIR}/src/Main.h
	${DIR}/src/Main.cpp)
	
set_target_cpp_standard(${PROJECT_NAME} 17)