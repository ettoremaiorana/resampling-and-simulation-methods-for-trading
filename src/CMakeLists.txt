#
# Find all executables
#
file(GLOB project_SRCS *.cpp *.h)

#
# Add executables to project
#
#
# create a library for unit tests
#
message(${project_SRCS})
add_executable(${project_BIN} ${project_SRCS})
target_link_libraries(${project_BIN})
add_library(${project_LIB} OBJECT bootstrap.cpp financial.cpp stats.cpp)
target_link_libraries(${project_LIB} ${CONAN_LIBS})

INSTALL(TARGETS ${project_LIB}
        DESTINATION ../lib)

if( ${CMAKE_SYSTEM_NAME} MATCHES "Linux" )
    target_link_libraries(${project_BIN} PUBLIC pthread)
endif()

if(MSVC)
    target_compile_options(${project_BIN} PUBLIC /D_SILENCE_CXX17_ALLOCATOR_VOID_DEPRECATION_WARNING /wd4459)
endif()
