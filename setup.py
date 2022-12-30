import os
import re
import subprocess
import sys
import warnings
from distutils.core import Extension, setup

import setuptools

FULLVERSION = "2.0.0.dev1"
PYTHON_REQUIRES = (3, 8)

PYTHON_MAJOR = sys.version_info[0]
PYTHON_MINOR = sys.version_info[1]

# Python supported version checks.
if (PYTHON_MAJOR, PYTHON_MINOR) < PYTHON_REQUIRES:
    raise RuntimeError(f"Python version >= {PYTHON_REQUIRES[0]}.{PYTHON_REQUIRES[1]} required.")

# Capture the version string:
# 1.22.0.dev0+ ... -> ISRELEASED == False, VERSION == 1.22.0
# 1.22.0rc1+ ... -> ISRELEASED == False, VERSION == 1.22.0
# 1.22.0 ... -> ISRELEASED == True, VERSION == 1.22.0
# 1.22.0rc1 ... -> ISRELEASED == True, VERSION == 1.22.0
ISRELEASED = re.search(r'(dev|\+)', FULLVERSION) is None
_V_MATCH = re.match(r'(\d+)\.(\d+)\.(\d+)', FULLVERSION)
if _V_MATCH is None:
    raise RuntimeError(f'Cannot parse version {FULLVERSION}')
MAJOR, MINOR, MICRO = _V_MATCH.groups()

VERSION = f"{MAJOR}.{MINOR}.{MICRO}"

if (PYTHON_MAJOR, PYTHON_MINOR) > (3, 9):
    warnings.warn(f"goopylib {VERSION} may not yet support Python {PYTHON_MAJOR}.{PYTHON_MINOR}.", RuntimeWarning)

if len(sys.argv) == 1:
    with open("pyproject.toml", "r") as f:
        content = f.read()
        content = re.sub("version = [\",'].*[\",']",
                         f"version = \"{FULLVERSION}\"", content)

        content = re.sub("requires-python = [\",'].*[\",']",
                         f"requires-python = \">={PYTHON_REQUIRES[0]}.{PYTHON_REQUIRES[1]}\"", content)

    with open("pyproject.toml", "w") as f:
        f.write(content)

    subprocess.run("python -m build".split())

    subprocess.run(["twine", "check", "dist/*"])
    subprocess.run(["twine", "upload", "-r", "testpypi", "dist/*"])

else:
    print("CWD", os.getcwd())
    ext_kwargs = {"include_dirs":         ["goopylib", "goopylib/src", "goopylib/src/vendor"],
                  "runtime_library_dirs": ["."],
                  "extra_objects":        [f"goopylib/goopylib.dylib"],
                  "extra_compile_args":   "-std=c++11 -v".split()}

    if sys.argv[1] == "setup.py" and sys.argv[2] == "build":
        setup_kwargs = {"options": {"build": {"build_lib": "."}}}
    else:
        setup_kwargs = {}

    setup(packages=setuptools.find_packages(),
          version=FULLVERSION,
          ext_modules=[Extension(name="goopylib.ext.easing",
                                 sources=["goopylib/maths/easing.cpp"],
                                 **ext_kwargs),

                       Extension(name="goopylib.ext.color_conversions",
                                 sources=["goopylib/color/conversions.cpp"],
                                 **ext_kwargs),

                       Extension(name="goopylib.ext.color",
                                 sources=["goopylib/color/color.cpp"],
                                 **ext_kwargs),

                       Extension(name="goopylib.ext.core",
                                 sources=["goopylib/core/core.cpp"],
                                 **ext_kwargs),

                       Extension(name="goopylib.ext.window",
                                 sources=["goopylib/core/window.cpp"],
                                 **ext_kwargs),

                       Extension(name="goopylib.ext.renderable",
                                 sources=["goopylib/objects/renderable.cpp"],
                                 **ext_kwargs),

                       Extension(name="goopylib.ext.line",
                                 sources=["goopylib/objects/line.cpp"],
                                 **ext_kwargs),

                       Extension(name="goopylib.ext.triangle",
                                 sources=["goopylib/objects/triangle.cpp"],
                                 **ext_kwargs),

                       Extension(name="goopylib.ext.quad",
                                 sources=["goopylib/objects/quad.cpp"],
                                 **ext_kwargs),

                       Extension(name="goopylib.ext.rectangle",
                                 sources=["goopylib/objects/rectangle.cpp"],
                                 **ext_kwargs),

                       Extension(name="goopylib.ext.ellipse",
                                 sources=["goopylib/objects/ellipse.cpp"],
                                 **ext_kwargs),

                       Extension(name="goopylib.ext.circle",
                                 sources=["goopylib/objects/circle.cpp"],
                                 **ext_kwargs),

                       Extension(name="goopylib.ext.image",
                                 sources=["goopylib/objects/image.cpp"],
                                 **ext_kwargs),

                       Extension(name="goopylib.ext.camera",
                                 sources=["goopylib/scene/camera.cpp"],
                                 **ext_kwargs),

                       Extension(name="goopylib.ext.camera_controller",
                                 sources=["goopylib/scene/camera_controller.cpp"],
                                 **ext_kwargs)],
          **setup_kwargs)
