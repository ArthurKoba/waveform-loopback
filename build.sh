cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=wsl_compile.cmake --no-warn-unused-cli
cmake --build build --config Release