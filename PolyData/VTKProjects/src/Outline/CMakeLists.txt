cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(Outline)

find_package(VTK COMPONENTS 
  CommonColor
  CommonCore
  CommonDataModel
  FiltersModeling
  FiltersSources
  InteractionStyle
  RenderingContextOpenGL2
  RenderingCore
  RenderingFreeType
  RenderingGL2PSOpenGL2
  RenderingOpenGL2
)
# 寻找VTK库
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

if (NOT VTK_FOUND)
  message(FATAL_ERROR "Outline: Unable to find the VTK build folder.")
endif()

# Prevent a "command line is too long" failure in Windows.
set(CMAKE_NINJA_FORCE_RESPONSE_FILE "ON" CACHE BOOL "Force Ninja to use response files.")
add_executable(Outline MACOSX_BUNDLE Outline.cxx )
  target_link_libraries(Outline PRIVATE ${VTK_LIBRARIES}
)
# vtk_module_autoinit is needed
vtk_module_autoinit(
  TARGETS Outline
  MODULES ${VTK_LIBRARIES}
)
