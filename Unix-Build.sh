# Set the default build target to "Debug"
BUILT_TARGET="Debug"

# First parameter, if any, is used as the build target.
# If no parameter is given, then default to "Debug".
if [ "$#" == 0 ]; then
    BUILD_TARGET="Debug"
else
    # Use the first parameter as the build target
    BUILD_TARGET="$1"
fi

# All remaining parameters are used as parameters to CMake

# Change directory to the build directory
cd build

# Run CMake with the specified build type and any additional parameters
cmake -DCMAKE_BUILD_TYPE="$BUILD_TARGET" "${@:1}" ../

# Compile the project using make with 4 parallel jobs
make -j 4

# Move the 'res' directory to the parent directory
mv ../res/ ./

