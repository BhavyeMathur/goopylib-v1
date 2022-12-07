# goopylib Version History

## v2.0.0

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
