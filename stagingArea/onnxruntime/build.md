### 基于buildroot交叉编译Onnxruntime
构建环境：
主机-Ubuntu20.04(WSL2)，目标设备-瑞芯微RK11xx(ARM)。

目标：生成libonnxruntime.so，尽量少依赖其他库。

编译过程中遇到的主要问题：
1. toolchain.cmake文件
2. protobuf问题
3. 生成的动态库依赖许多其他库

#### 1. 需要使用toolchain.cmake来设置sysroot路径，确保能找到依赖的头文件以及库文件。
尽量使用buildroot或者yocto编译cmake-host来生成toolchain.cmake。
``` make
# set(SDK_INSTALL_DIR "${CMAKE_CURRENT_LIST_DIR}/../../../../..")

set(HOST_SYSROOT    "/home/jack/work/BSP/buildroot/output/rockchip_rv1126_rv1109/host")

set(TARGET_SYSROOT  "/home/jack/work/BSP/buildroot/output/rockchip_rv1126_rv1109/host/arm-buildroot-linux-gnueabihf/sysroot")

set(HOST_BIN        "${HOST_SYSROOT}/bin")
set(TOOLCHAIN_NAME  "arm-linux-gnueabihf")
set(GCC_DIR         "${HOST_BIN}")

set(CMAKE_SYSTEM_NAME       Linux)
set(CMAKE_SYSTEM_PROCESSOR armv7)

set(CMAKE_C_COMPILER    "${GCC_DIR}/${TOOLCHAIN_NAME}-gcc")
set(CMAKE_CXX_COMPILER  "${GCC_DIR}/${TOOLCHAIN_NAME}-g++")
set(ARCH_FLAGS          " -mthumb -mfpu=neon -mfloat-abi=hard -mcpu=cortex-a7")

set(CMAKE_C_FLAGS       "${ARCH_FLAGS}" CACHE STRING "" FORCE )
set(CMAKE_CXX_FLAGS     "${ARCH_FLAGS}" CACHE STRING "" FORCE )
set(CMAKE_ASM_FLAGS     ${CMAKE_C_FLAGS} CACHE STRING "" FORCE )
set(CMAKE_LDFLAGS_FLAGS ${CMAKE_C_FLAGS} CACHE STRING "" FORCE )

set(CMAKE_SYSROOT "${TARGET_SYSROOT}")

set(CMAKE_FIND_ROOT_PATH "${TARGET_SYSROOT}" )
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER )
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY )
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY )
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY )

set(CMAKE_FIND_LIBRARY_CUSTOM_LIB_SUFFIX "")

set(CMAKE_PROGRAM_PATH "${HOST_SYSROOT}/bin" CACHE STRING "" FORCE)
```

#### 2. protobuf一直出现语法问题
onnxruntime对protobuf有版本要求，同上在注意版本的基础上，尽量使用buildroot或者yocto编译protobuf-host，然后在cmake选项中添加
``` cmake-opt
-DONNX_CUSTOM_PROTOC_EXECUTABLE=$(HOST_DIR)/bin/protoc
```

#### 3. 尽量减少目标文件的依赖
``` cmake-opt
-DBUILD_SHARED_LIBS=OFF    #其他依赖以静态库的方式链接到目标文件
-Donnxruntime_BUILD_SHARED_LIB=ON   #目标文件生成动态库
```

#### 4. 其他
``` cmake-opt
-Donnxruntime_CROSS_COMPILING=ON   #交叉编译选项，会增加一些检查
-Donnxruntime_MINIMAL_BUILD=ON    #最小化
```

``` buildroot-package.mk
ONNXRUNTIME_VERSION = v1.11.1
ONNXRUNTIME_SITE = https://github.com/microsoft/onnxruntime
ONNXRUNTIME_SITE_METHOD = git
ONNXRUNTIME_GIT_SUBMODULES = YES
ONNXRUNTIME_GIT_LFS = YES
ONNXRUNTIME_INSTALL_STAGING = YES
#ONNXRUNTIME_GIT_CLONE_OPTS = --recursive   # submodule
ONNXRUNTIME_DEPENDENCIES += libglib2
ONNXRUNTIME_DEPENDENCIES += protobuf

ONNXRUNTIME_CONF_OPTS += \
        -DBUILD_SHARED_LIBS=OFF \
        -Donnxruntime_BUILD_SHARED_LIB=ON \
        -Donnxruntime_BUILD_UNIT_TESTS=OFF \
        -Donnxruntime_CROSS_COMPILING=ON \
        -DONNX_CUSTOM_PROTOC_EXECUTABLE=$(HOST_DIR)/bin/protoc \
        -DPYTHON_EXECUTABLE=/usr/bin/python3 \
        -S $(@D)/cmake


define ONNXRUNTIME_INSTALL_STAGING_CMDS
    # 安装主库文件
    $(INSTALL) -D -m 0755 $(@D)/libonnxruntime.so.1.11.1 $(STAGING_DIR)/usr/lib/libonnxruntime.so
        $(INSTALL) -D -m 0755 $(@D)/libonnxruntime_providers_shared.so $(STAGING_DIR)/usr/lib/libonnxruntime_providers_shared.so
endef

$(eval $(cmake-package))
```
吐槽，这个库真的给我干吐了
