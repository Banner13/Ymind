编译选项 += \
        -DCMAKE_BUILD_TYPE=RelWithDebInfo \
        -Donnxruntime_BUILD_SHARED_LIB=ON \
        -Donnxruntime_BUILD_UNIT_TESTS=OFF \
        -Donnxruntime_CROSS_COMPILING=ON \
        -DONNX_CUSTOM_PROTOC_EXECUTABLE=/path/bin/protoc \
        -DPYTHON_EXECUTABLE=/usr/bin/python3 \
        -DCMAKE_TOOLCHAIN_FILE=/path/armxxx-toolchain.cmake \
        -S $(@D)/cmake
        
    注意protoc版本问题
