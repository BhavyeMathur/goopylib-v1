import sys
import re
import warnings

from setuptools import setup, Extension
import setuptools

FULLVERSION = "2.1.0"
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
    compile_args = ["-std=c++20", "-Wno-macro-redefined", "-Wno-unused-function", "-Wno-unknown-pragmas"]
    compile_args += ["-Wno-deprecated-volatile"]  # suppress warnings caused by glm

    library_dirs = ["binaries/lib-macos"]
    data_files = []

elif sys.platform == "win32":
    compile_args = ["/std:c++20", "/wd4005", "/wd4068"]  # suppress macro-redefinition & unknown pragma warnings
    library_dirs = ["binaries/lib-vc2022/Release/"]  # TODO figure out how to remove Release folder
    data_files = [("goopylib", ["binaries/lib-vc2022/Release/goopylib.dll"])]

else:
    compile_args = []
    library_dirs = []
    data_files = []

ext_kwargs = {"include_dirs":         [".", "src", "vendor", "vendor/glad", "vendor/glm",
                                       "vendor/spdlog/include", "vendor/GLFW/include", "vendor/pybind11/include"],
              "library_dirs":         library_dirs,
              "runtime_library_dirs": RUNTIME_LIBRARY_DIRS,
              "libraries":            ["goopylib"],
              "extra_compile_args":   compile_args}


def get_extension(path: str):
    return Extension(name=f"goopylib.{path}",
                     sources=[f"goopylib/{path.replace('.', '/')}.cpp"],
                     **ext_kwargs)


def find_extensions():
    return [
        get_extension("color.color"),

        get_extension("core.core"),
        get_extension("core.window"),

        get_extension("maths.easing"),

        get_extension("objects.renderable"),
        get_extension("objects.triangle"),
        get_extension("objects.quad"),
        get_extension("objects.rectangle"),
        get_extension("objects.line"),
        get_extension("objects.ellipse"),
        get_extension("objects.circle"),
        get_extension("objects.image"),

        get_extension("scene.camera"),
        get_extension("scene.camera_controller"),
    ]


if __name__ == "__main__":
    check_version()

    setup(packages=setuptools.find_packages(),
          ext_modules=find_extensions(),
          data_files=data_files)
