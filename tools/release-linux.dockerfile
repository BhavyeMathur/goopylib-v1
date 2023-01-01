FROM ubuntu:latest

RUN cd macos/

# install cmake
RUN apt-get update
RUN apt-get -y install cmake

# install OpenGL
RUN apt-get install libgl1-mesa-dev
RUN apt-get install mesa-common-dev
RUN apt-get install libglfw3
RUN apt-get install libglfw3-dev

# download the GNU compiler
RUN apt install build-essential

# set the path to the C and C++ compiler
RUN export CC=/usr/bin/gcc
RUN export CXX=/usr/bin/g++

# clear the cmake cache and build the project
RUN rm -rf cmake-build-linux
RUN cmake -S . -B cmake-build-linux/ -D CMAKE_BUILD_TYPE=Release
RUN cmake --build cmake-build-linux

# install Python and dependencies
RUN apt-get install python3
RUN apt-get install python-pip
RUN pip install cibuildwheel
RUN pip install twine

# create Linux wheels using cibuildwheel
RUN cibuildwheel --platform linux

# check and upload the wheels to a test site
RUN twine check wheelhouse/*
RUN twine upload -r testpypi wheelhouse/*
