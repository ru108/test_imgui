cmake_minimum_required(VERSION 3.20)

project(test_imgui VERSION 0.0.1 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 20)

set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT "${PROJECT_NAME}")

add_executable(${PROJECT_NAME}
  src/${PROJECT_NAME}.cpp
  src/MainMenuBar.h
  src/ExampleWindow.h
)

set(UI_DIR ${CMAKE_CURRENT_LIST_DIR}/src/UI)
file(GLOB UI
  ${UI_DIR}/WindowManager.h
  ${UI_DIR}/GLFWWindowManager.h
)
target_sources(${PROJECT_NAME} PRIVATE ${UI})
foreach(_source IN ITEMS ${UI})
  source_group("UI" FILES "${_source}")
endforeach()

set(COMMAND_DIR ${CMAKE_CURRENT_LIST_DIR}/src/Command)
file(GLOB COMMAND
  ${COMMAND_DIR}/ICommand.h
  ${COMMAND_DIR}/ApplicationCloseCommand.h
)
target_sources(${PROJECT_NAME} PRIVATE ${COMMAND})
foreach(_source IN ITEMS ${COMMAND})
  source_group("COMMAND" FILES "${_source}")
endforeach()

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR}/src)

set(IMGUI_DIR ${CMAKE_CURRENT_LIST_DIR}/imgui)
target_include_directories(${PROJECT_NAME} PRIVATE ${IMGUI_DIR})
file(GLOB IMGUI
  ${IMGUI_DIR}/imconfig.h
  ${IMGUI_DIR}/imgui.h
  ${IMGUI_DIR}/imgui.cpp
  ${IMGUI_DIR}/imgui_internal.h
  ${IMGUI_DIR}/imgui_demo.cpp
  ${IMGUI_DIR}/imgui_draw.cpp
  ${IMGUI_DIR}/imgui_tables.cpp
  ${IMGUI_DIR}/imgui_widgets.cpp
  ${IMGUI_DIR}/imgui_impl_glfw.h
  ${IMGUI_DIR}/imgui_impl_glfw.cpp
  ${IMGUI_DIR}/imgui_impl_opengl3.h
  ${IMGUI_DIR}/imgui_impl_opengl3.cpp
  ${IMGUI_DIR}/imgui_impl_opengl3_loader.h
)
target_sources(${PROJECT_NAME} PRIVATE ${IMGUI})
foreach(_source IN ITEMS ${IMGUI})
  get_filename_component(_source_path "${_source}" PATH)
  string(REPLACE "${CMAKE_SOURCE_DIR}" "" _group_path "${_source_path}")
  string(REPLACE "/" "\\" _group_path "${_group_path}")
  source_group("${_group_path}" FILES "${_source}")
endforeach()

include(FetchContent)
FetchContent_Declare(glfw
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  GIT_TAG        3.3.7
)
message(STATUS "Using glfw via FetchContent")
FetchContent_MakeAvailable(glfw)
target_include_directories(${PROJECT_NAME} PRIVATE ${glfw_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)

if(NOT MSVC)
  target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic -O3)
else()
  target_link_libraries(${PROJECT_NAME} PRIVATE opengl32.lib)
  target_compile_definitions(${PROJECT_NAME}
    PRIVATE $<$<COMPILE_LANG_AND_ID:CXX,MSVC>:UNICODE;_UNICODE>
    PRIVATE $<$<COMPILE_LANG_AND_ID:C,MSVC>:UNICODE;_UNICODE>)
  target_compile_options(${PROJECT_NAME} PRIVATE /permissive-)
endif()
