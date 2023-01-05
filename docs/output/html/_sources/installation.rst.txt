Installation Guide
==================

**To install goopylib on Windows or MacOS**, use the `Python Package Index (PyPI) <https://pypi.org/project/goopylib>`_:

.. code:: bash

    pip install goopylib

Wheels for Linux are not currently supported but coming as soon as I can build them!

.. warning::

    The minimum required Python version is Python 3.8.

-----------

|

Building goopylib using CMake
-----------------------------

To build goopylib from source, you will first need to download or compile the GLFW library. Pre-built binaries are
available for Windows 64-bit or 32-bit systems and Apple Intel/Apple Silicon
`here <https://www.glfw.org/download.html>`_. Follow `this <https://www.glfw.org/docs/3.3/compile.html>`_ guide
to compile GLFW yourself.

Next, download goopylib's source distribution from `GitHub <https://github.com/BhavyeMathur/goopylib>`_
or clone it using git:

.. code:: bash

    git clone https://github.com/BhavyeMathur/goopylib.git goopylib


Then, build the library using CMake:

.. code:: bash

    mkdir build
    cd build
    cmake ..
    cmake --build

Finally, you can build the Python/C++ extensions by running the following commands in the goopylib directory:

.. code:: bash

    python setup_extensions.py build
