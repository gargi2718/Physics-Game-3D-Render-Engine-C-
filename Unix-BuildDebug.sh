# Change directory to the 'build' directory
cd build

# Run CMake to generate build files for the project in the parent directory -DCMAKE_BUILD_TYPE="Debug" sets the build type to Debug
cmake -DCMAKE_BUILD_TYPE="Debug" ../

# Compile the project using make with 4 parallel jobs
make -j 4

# Move the 'res' directory from the parent directory to the current directory
mv ../res/ ./
