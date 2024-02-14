import sys
import re
import warnings

from setuptools import setup, Extension
import setuptools

FULLVERSION = "2.0.0"
PYTHON_REQUIRES = (3, 8)

RUNTIME_LIBRARY_DIRS = []


def check_version():
    python_major = sys.version_info[0]
    python_minor = sys.version_info[1]

    # Capture the version string:
    # 1.22.0.dev0+ ... -> ISRELEASED == False, VERSION == 1.22.0
    # 1.22.0rc1+ ... -> ISRELEASED == False, VERSION == 1.22.0
    # 1.22.0 ... -> ISRELEASED == True, VERSION == 1.22.0
    # 1.22.0rc1 ... -> ISRELEASED == True, VERSION == 1.22.0
    is_released = re.search(r'(dev|\+)', FULLVERSION) is None
    _V_MATCH = re.match(r'(\d+)\.(\d+)\.(\d+)', FULLVERSION)
    if _V_MATCH is None:
        raise RuntimeError(f'Cannot parse version {FULLVERSION}')
    major, minor, micro = _V_MATCH.groups()

    version = f"{major}.{minor}.{micro}"

    # Python supported version checks

    if (python_major, python_minor) < PYTHON_REQUIRES:
        raise RuntimeError(f"Python version >= {PYTHON_REQUIRES[0]}.{PYTHON_REQUIRES[1]} required.")

    if (python_major, python_minor) > (3, 11):
        warnings.warn(f"goopylib {version} may not yet support Python {python_major}.{python_minor}.", RuntimeWarning)

    # Update the pyproject.toml file with these version details

    with open("pyproject.toml", "r") as f:
        content = f.read()

    content = re.sub("version = [\",'].*[\",']",
                     f"version = \"{FULLVERSION}\"", content)

    content = re.sub("requires-python = [\",'].*[\",']",
                     f"requires-python = \">={PYTHON_REQUIRES[0]}.{PYTHON_REQUIRES[1]}\"", content)

    with open("pyproject.toml", "w") as f:
        f.write(content)

    # Update the setup.cfg file with these version details

    with open("setup.cfg", "r") as f:
        content = f.read()

    content = re.sub("version = .*",
                     f"version = {FULLVERSION}", content)

    content = re.sub("python_requires = .*",
                     f"python_requires = >={PYTHON_REQUIRES[0]}.{PYTHON_REQUIRES[1]}", content)

    with open("setup.cfg", "w") as f:
        f.write(content)

    # Update the __init__.py file with these version details

    with open("goopylib/__init__.py", "r") as f:
        content = f.read()

    content = re.sub("__version__ = \".*\"",
                     f"__version__ = \"{FULLVERSION}\"", content)

    with open("goopylib/__init__.py", "w") as f:
        f.write(content)


if sys.platform == "darwin":
    compile_args = ["-std=c++17", "-Wno-macro-redefined", "-Wno-unused-function", "-Wno-unknown-pragmas"]
    compile_args += ["-Wno-deprecated-volatile"]  # suppress warnings caused by glm

    library_dirs = ["binaries/lib-macos"]
    data_files = []

elif sys.platform == "win32":
    compile_args = ["/std:c++17", "/wd4005", "/wd4068"]  # suppress macro-redefinition & unknown pragma warnings
    library_dirs = ["binaries/lib-vc2022/Release/"]  # TODO figure out how to remove Release folder
    data_files = [("goopylib", ["binaries/lib-vc2022/Release/goopylib.dll"])]

else:
    compile_args = []
    library_dirs = []
    data_files = []

ext_kwargs = {"include_dirs":         [".", "goopylib", "src", "vendor", "vendor/glad", "vendor/glm",
                                       "vendor/spdlog/include", "vendor/GLFW/include"],
              "library_dirs":         library_dirs,
              "runtime_library_dirs": RUNTIME_LIBRARY_DIRS,
              "libraries":            ["goopylib"],
              "extra_compile_args":   compile_args}


def get_object_extension(obj: str):
    return Extension(name=f"goopylib.ext.{obj}",
                     sources=[f"goopylib/objects/{obj}/module.cpp",
                              f"goopylib/objects/{obj}/{obj}.cpp",
                              f"goopylib/objects/{obj}/type.cpp"],
                     **ext_kwargs)


def find_extensions():
    return [
        Extension(name="goopylib.ext.easing",
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

        get_object_extension("renderable"),

        get_object_extension("triangle"),

        get_object_extension("quad"),
        get_object_extension("rectangle"),
        get_object_extension("line"),

        get_object_extension("ellipse"),
        get_object_extension("circle"),

        get_object_extension("image"),

        Extension(name="goopylib.ext.camera",
                  sources=["goopylib/scene/camera.cpp"],
                  **ext_kwargs),

        Extension(name="goopylib.ext.camera_controller",
                  sources=["goopylib/scene/camera_controller.cpp"],
                  **ext_kwargs)
    ]


if __name__ == "__main__":
    check_version()

    setup(packages=setuptools.find_packages(),
          ext_modules=find_extensions(),
          data_files=data_files)
