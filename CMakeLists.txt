cmake_minimum_required (VERSION 3.10)

project (FinalPractice VERSION 1.0)

#Skibidi project

list(APPEND Engine "engine/src/engine/Window.cpp")
list(APPEND Engine "engine/src/engine/BaseScene.cpp")
list(APPEND Engine "engine/src/engine/SceneManager.cpp")
list(APPEND Engine "engine/src/engine/TimeManager.cpp")
list(APPEND Engine "engine/src/engine/Input.cpp")
list(APPEND Engine "engine/src/engine/Camera.cpp")
list(APPEND Engine "engine/src/engine/Controller.cpp")
list(APPEND Engine "engine/src/engine/AssetManager.cpp")

list(APPEND Engine "engine/src/engine/D3DObjects/Mesh.cpp")
list(APPEND Engine "engine/src/engine/D3DObjects/GameObject.cpp")
list(APPEND Engine "engine/src/engine/D3DObjects/D3DPipeline.cpp")
list(APPEND Engine "engine/src/engine/D3DObjects/VertexLayout.cpp")
list(APPEND Engine "engine/src/engine/D3DObjects/CBufferObject.cpp")
list(APPEND Engine "engine/src/engine/D3DObjects/RasterizerState.cpp")
list(APPEND Engine "engine/src/engine/D3DObjects/TextureSampler.cpp")
list(APPEND Engine "engine/src/engine/D3DObjects/ImageTexture.cpp")
list(APPEND Engine "engine/src/engine/D3DObjects/PipelineBinding.cpp")

list(APPEND Game "engine/src/game/gameScene.cpp")

# Add source to this project's executable.
add_executable (FinalPractice "engine/src/main.cpp" ${Engine} ${Game})

#Add GLFW for window
add_library(GLFW STATIC IMPORTED GLOBAL)
set_property(TARGET GLFW PROPERTY IMPORTED_LOCATION "${CMAKE_CURRENT_LIST_DIR}/libraries/GLFW/glfw3.lib")
target_link_libraries(FinalPractice GLFW)

#Add Direct3D11
find_library("d3d11.lib" PATH "C:/Program Files (x86)/Windows Kits/10/Lib/10.0.22000.0/")
find_library("dxgi.lib" PATH "C:/Program Files( x86)/Windows Kits/10/Lib/10.0.22000.0/")
find_library("d3dcompiler.lib" PATH "C:/Program Files( x86)/Windows Kits/10/Lib/10.0.22000.0/")
find_library("winmm.lib" PATH "C:/Program Files( x86)/Windows Kits/10/Lib/10.0.22000.0/")
find_library("dxguid.lib" PATH "C:/Program Files( x86)/Windows Kits/10/Lib/10.0.22000.0/")

target_link_libraries(FinalPractice d3d11)
target_link_libraries(FinalPractice dxgi)
target_link_libraries(FinalPractice d3dcompiler)
target_link_libraries(FinalPractice winmm)
target_link_libraries(FinalPractice dxguid)

#Include all additional header files
target_include_directories(FinalPractice PUBLIC "${CMAKE_CURRENT_LIST_DIR}/libraries/includes")

target_include_directories(FinalPractice PUBLIC "${CMAKE_CURRENT_LIST_DIR}/engine/src")

#Copy shaders into the output directory, to prevent them being copied manually
add_custom_target(copyShaders ALL
COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_LIST_DIR}/engine/shaders" "${CMAKE_BINARY_DIR}/shaders"
COMMENT "Copied shaders to output directory" VERBATIM
)

#Copy assets into the output directory, to prevent them being copied manually
add_custom_target(copyAssets ALL
COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_LIST_DIR}/engine/assets" "${CMAKE_BINARY_DIR}/assets"
COMMENT "Copied assets to output directory" VERBATIM
)

add_dependencies(FinalPractice copyShaders)
add_dependencies(FinalPractice copyAssets)