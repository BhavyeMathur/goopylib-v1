import sys
import re
import warnings

from setuptools import setup, Extension
import setuptools

FULLVERSION = "2.0.0.dev5"
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


if sys.platform == "darwin":
    compile_args = ["-std=c++17", "-Wno-macro-redefined", "-Wno-unused-function", "-Wno-unknown-pragmas"]
    compile_args += ["-Wno-deprecated-volatile"]  # suppress warnings caused by glm

    library_dirs = ["binaries/lib-macos"]
    data_files = []

elif sys.platform == "win32":
    compile_args = ["/wd4005"]  # suppress macro-redefinition warning
    library_dirs = ["binaries/lib-vc2022"]
    data_files = [("goopylib", ["binaries/lib-vc2022/goopylib.dll"])]

else:
    compile_args = []
    library_dirs = []
    data_files = []


def find_extensions():
    ext_kwargs = {"include_dirs":         [".", "goopylib", "src", "vendor", "vendor/glad", "vendor/glm",
                                           "vendor/spdlog/include", "vendor/GLFW/include"],
                  "library_dirs":         library_dirs,
                  "runtime_library_dirs": RUNTIME_LIBRARY_DIRS,
                  "libraries":            ["goopylib"],
                  "extra_compile_args":   compile_args}

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

        Extension(name="goopylib.ext.renderable",
                  sources=["goopylib/objects/renderable.cpp"],
                  **ext_kwargs),

        Extension(name="goopylib.ext.triangle",
                  sources=["goopylib/objects/triangle.cpp"],
                  **ext_kwargs),

        Extension(name="goopylib.ext.quad",
                  sources=["goopylib/objects/quad.cpp",
                           "goopylib/objects/quad_object.cpp"],
                  **ext_kwargs),

        Extension(name="goopylib.ext.rectangle",
                  sources=["goopylib/objects/rectangle.cpp",
                           "goopylib/objects/quad_object.cpp"],
                  **ext_kwargs),

        Extension(name="goopylib.ext.line",
                  sources=["goopylib/objects/line.cpp",
                           "goopylib/objects/quad_object.cpp"],
                  **ext_kwargs),

        Extension(name="goopylib.ext.ellipse",
                  sources=["goopylib/objects/ellipse.cpp"],
                  **ext_kwargs),

        Extension(name="goopylib.ext.circle",
                  sources=["goopylib/objects/circle.cpp"],
                  **ext_kwargs),

        Extension(name="goopylib.ext.image",
                  sources=["goopylib/objects/image.cpp",
                           "goopylib/objects/quad_object.cpp"],
                  **ext_kwargs),

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
