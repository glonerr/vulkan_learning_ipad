cmake_minimum_required(VERSION 3.7.1)
# 设置一个合适的工程名
set(project_name vulkan_learning)

project(${project_name})

#AUTO_LOCATE_VULKAN - 可用的值是ON/OFF
#ON - 使用CMake自动查找Vulkan SDK的位置
#OFF - 手动设置Vulkan SDK的路径
#这样我们可以很方便的切换使用不同版本的Vulkan
option(AUTO_LOCATE_VULKAN "AUTO_LOCATE_VULKAN" ON)
if(AUTO_LOCATE_VULKAN)
    message(STATUS "Attempting auto locate vulkan using CMake......")
    # 通过CMake的vulkan模块查找Vulkan路径
    # 这里会自动返回一个布尔量Vulkan_FOUND，它表示Vulkan是否已经被自动找到（ON或者OFF）
    # 头文件路径 - 'Vulkan_INCLUDE_DIRS'
    # 必备库文件 - 'Vulkan_LIBRARY'
    find_package(Vulkan)
    # 尝试从${Vulkan_INCLUDE_DIRS}中抽取出VulkanSDK的路径
    if(NOT ${Vulkan_INCLUDE_DIRS} STREQUAL "")
        set(VULKAN_PATH ${Vulkan_INCLUDE_DIRS})
        string(REGEX REPLACE "/include" "" VULKAN_PATH ${VULKAN_PATH})
        message(STATUS VULKAN_PATH:${VULKAN_PATH}})
    endif()

    if(NOT Vulkan_FOUND)
    # CMake有可能无法自动定位库文件的位置，但是我们可以提供一些Vulkan_SDK
    # 的文件位置来确定'Vulkan_INCLUDE_DIRS'，进而从中抽取出正确的路径

    message(STATUS "Failed to locate Vulkan SDK, retrying again...")

    # 检查Vulkan路径是否是可用的，否则切换到手动模式
        if(EXISTS "${VULKAN_PATH}")
            message(STATUS "Successful locate the Vulkan SDK: ${VULKAN_PATH}")
        else()
            message("Error: Unable to locate Vulkan SDK, Please turn off auto locate option by specify 'AUTO_LOCATE_VULKAN' as 'OFF'")
            message("and specify manually path using 'VULKAN_SDK' and 'VULKAN_VERSION' variables in the CMakeLists.txt")
            return()
        endif()
        
    endif()
    
    message(STATUS vulkan_include_dirs:${Vulkan_INCLUDE_DIRS})
    message(STATUS vulkan_library:${Vulkan_LIBRARY})
else()
    message(STATUS "Attempting to locate Vulkan SDK using manual path......")
    set(VULKAN_SDK "path to vulkan sdk")
    set(VULKAN_VERSION "1.0.33.0")
    set(VULKAN_PATH "vulkan path")
    message(STATUS "Using manual specified path: ${VULKAN_PATH}")

    # 检查用户是否手动设置了路径
    if(NOT EXISTS ${VULKAN_PATH})
        message("Error: Unable to  lcoate the Vulkan SDK path: VULKAN_PATH: ${VULKAN_PATH}, Please specify correct path. For more infomation on correct installation process, Please refer to subsection 'Getting started with Lunar-G SDK' and 'Setting up first project with CMake' in Charpter 3, 'Shaking hands with the device' in this book 'Learning Vulkan', ISBN - 9781786469709")
        return()
    endif()
endif()


# 添加预编译宏
add_definitions(-DVK_USE_PLATFORM_XCB_KHR)

# 添加'vulkan'库文件来编译Vulkan应用程序
set(VULKAN_LIB_LIST 'vulkan')

message(STATUS ${CMAKE_SYSTEM_NAME})
if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    message(STATUS "build in windows system")

    # 包含Vulkan SDK的头文件目录
    include_directories(AFTER ${VULKAN_PATH}/Include)
    
    # 设置连接库 vulkan-1所在的目录
    link_directories(${VULKAN_PATH}/bin)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    message(STATUS "build in linux system")
endif()

source_group("include" REGULAR_EXPRESSION "include/*")
source_group("source"  REGULAR_EXPRESSION "source/*")

# 定义头文件路径
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# 收集所有需要编译的头文件和源代码文件
file(GLOB_RECURSE CPP_FILES ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp)
file(GLOB_RECURSE HPP_FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/*.*)

# 构建工程，需要设置一个名字，以及提供所需编译的文件列表
add_executable(${project_name} ${CPP_FILES} ${HPP_FILES})

# 将工程所需的debug和release依赖库连接进来
message(STATUS ${VULKAN_LIB_LIST})
target_link_libraries(${project_name} ${VULKAN_LIB_LIST})

# 定义工程属性
set_property(TARGET ${project_name} PROPERTY RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/binaries)
set_property(TARGET ${project_name} PROPERTY RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}/binaries)
set_property(TARGET ${project_name} PROPERTY RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR}/binaries)
set_property(TARGET ${project_name} PROPERTY RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${CMAKE_CURRENT_SOURCE_DIR}/binaries)
set_property(TARGET ${project_name} PROPERTY RUNTIME_OUTPUT_DIRECTORY_RELWITHDEGINFO ${CMAKE_CURRENT_SOURCE_DIR}/binaries)

# 定义工程中使用的C++版本
set_property(TARGET ${project_name} PROPERTY CXX_STANDARD 11)
set_property(TARGET ${project_name} PROPERTY CXX_STANDARD_REQUIRED ON)

# 定义工程中使用的C版本
set_property(TARGET ${project_name} PROPERTY C_STANDARD 99)
set_property(TARGET ${project_name} PROPERTY C_STANDARD_REQUIRED ON)

message(STATUS INCLUDE_DIRECTORIES:${INCLUDE_DIRECTORIES})
message(STATUS "${project_name}")
