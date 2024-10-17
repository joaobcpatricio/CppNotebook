# CMake Course

The content here will follow a CMake course from Udemy.

Please refer to CMakeGuide.md for more documentation.

## Manual build steps

### Steps

### 1.

    0.) Create Source and CMakeFile
    1.) $mkdir build
    2.) $cd build
    3.) $cmake ..    // For Generating the Build files / configure the project
        3.1.) $cmake [<options>] -S <path-to-source> -B <path-to-build>
            3.1.1.) $cmake -S .. -B -
    4.) $cmake --build .
    3.1.) $cmake .
    5.) $./Executable

### 2.

    0.) To build specific target:
        0.1.) $cmake --build . --target Library
        0.2.) $cmake --build . --target Executable

### 3. Adding variables

Should be created on a top directory.

To use place them inside `${}`.

### 4. Makefile

    We can use makefile to perform some actions, as to clean the build directory.
    $make prepare

### 5. Build passing values

    $cmake .. -DCOMPILE_EXECUTABLE=ON #The name shall be righ after the "D". Once set it stays "ON" until a proper clean of the build folder.
    $cmake --build .

### 6.

#### Generator

For GCC and Clang:

    $cmake -S .. -B . -G "Unix Makefiles" #Option 1
    $cmake .. -G "Uniex Makefiles"  # Option 2

For MSVC, for example:

    $cmake -S .. -B . -G "Visual Studio 16 2019"

#### Build Type

    $cmake -DCMAKE_BUILD_TYPE=Release ..

### 8.

See a dependency graph under unix, use the cmake file to
run: `cd build && cmake .. --graphviz=graph.dot && dot -Tpng graph.dot -o graphImage.png`

### 9. PUBLIC vs PRIVATE

#### PUBLIC

```cmake
target_link_libraries(A PUBLIC B)
target_link_libraries(C PUBLIC A)
```

When A links in B as *PUBLIC*, it says that A uses B in its implementation, and B is also used in A's public API. Hence,
C can use B since it is part of the public API of A.

#### PRIVATE

```cmake
target_link_libraries(A PRIVATE B)
target_link_libraries(C PRIVATE A)
```

When A links in B as *PRIVATE*, it is saying that A uses B in its
implementation, but B is not used in any part of A's public API. Any code
that makes calls into A would not need to refer directly to anything from
B.