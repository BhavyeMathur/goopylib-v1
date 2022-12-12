# goopylib Version History

## v2.0.0

#### 12 December, 2022 - ? lines of code

* Added a C++ API to set Shader Uniforms

#### 10 December, 2022 - ~15400 lines of code

* Added a Shader class
* Added log mesages to the Buffer classes
* Added a Vertex Array draw method
* Vertex Arrays can now create their own Index Buffers
* Added Python wrappers for VertexArray, VertexBuffer, IndexBuffer, and Shader

#### 9 December, 2022 - 14290 lines of code

* Added Color operator overloading to the Python API
* Fixed bug where the color logger couldn't be used from C++ due to the static initialisation of W3CX11 colors
* Added Index Buffer, Vertex Buffer, and Vertex Array classes (mostly copied from The Cherno's Hazel)

#### 8 December, 2022 - ~13400 lines of code

* Split goopylib C++ extensions into more submodules
* goopylib now uses dynamic library linking
* goopylib ints instead of unsigned ints to prevent odd overflow behaviour
* Added simple operator overloading for Colors
* Added background colors to Windows

#### 7 December, 2022 - 13012 lines of code

* Fixed bug with Window callbacks being deallocated just before being called
* Split Python extension sources into .cpp and .h files
* Implemented a submodule to work with colors
* Added functions to get random colors

#### 6 December, 2022 - 10798 lines of code

* Added key press callbacks to the Window
* Added RGB, CMYK, HSV, and HSL color conversions to the C++ API
* Split the code module into core, color, and easing

#### 5 December, 2022 - 9486 lines of code

* Added logging support (taken from The Cherno's Hazel)
* Window callbacks are now O(1) functions, not O(n)
