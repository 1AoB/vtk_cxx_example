cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(AlignFrames)

find_package(VTK COMPONENTS 
  CommonCore
  CommonDataModel
  CommonTransforms
  FiltersGeneral
  IOXML
)

if (NOT VTK_FOUND)
  message(FATAL_ERROR "AlignFrames: Unable to find the VTK build folder.")
endif()

# Prevent a "command line is too long" failure in Windows.
set(CMAKE_NINJA_FORCE_RESPONSE_FILE "ON" CACHE BOOL "Force Ninja to use response files.")
add_executable(AlignFrames MACOSX_BUNDLE AlignFrames.cxx )
  target_link_libraries(AlignFrames PRIVATE ${VTK_LIBRARIES}
)
# vtk_module_autoinit is needed
vtk_module_autoinit(
  TARGETS AlignFrames
  MODULES ${VTK_LIBRARIES}
)