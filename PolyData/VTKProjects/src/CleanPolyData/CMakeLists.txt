cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(CleanPolyData)

find_package(VTK COMPONENTS 
  CommonCore
  CommonDataModel
  FiltersCore
  FiltersSources
)

if (NOT VTK_FOUND)
  message(FATAL_ERROR "CleanPolyData: Unable to find the VTK build folder.")
endif()

# Prevent a "command line is too long" failure in Windows.
set(CMAKE_NINJA_FORCE_RESPONSE_FILE "ON" CACHE BOOL "Force Ninja to use response files.")
add_executable(CleanPolyData MACOSX_BUNDLE CleanPolyData.cxx )
  target_link_libraries(CleanPolyData PRIVATE ${VTK_LIBRARIES}
)
# vtk_module_autoinit is needed
vtk_module_autoinit(
  TARGETS CleanPolyData
  MODULES ${VTK_LIBRARIES}
)