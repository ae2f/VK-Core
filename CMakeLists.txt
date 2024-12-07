cmake_minimum_required(VERSION 3.20)

project(CL-Core VERSION 0.01)
enable_testing()
if(NOT TARGET ${PROJECT_NAME})

add_subdirectory(mod/ae2f/Core)

# Namespace Package
include(GNUInstallDirs)

find_package(Core)
if(Core_FOUND)
    link_libraries(ae2f::Core)
else()
    link_libraries(Core)
endif()

find_package(OpenCL REQUIRED)
link_libraries(OpenCL::OpenCL)

add_library(
    ${PROJECT_NAME}
    INTERFACE
    "include/ae2fCL/Loc.h"
    "include/ae2fCL/Scenario.h"
)

include_directories(include)

target_include_directories(${PROJECT_NAME}
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

install(TARGETS ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}Targets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(DIRECTORY include/ae2f/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/ae2f
)

install(EXPORT ${PROJECT_NAME}Targets
    FILE ${PROJECT_NAME}Targets.cmake
    NAMESPACE ae2f::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/
)

include(CMakePackageConfigHelpers)
configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake
)

endif()