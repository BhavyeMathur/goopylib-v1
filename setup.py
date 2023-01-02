import re
import sys
import warnings
from distutils.core import setup, Extension

import setuptools

FULLVERSION = "2.0.0.dev4"
PYTHON_REQUIRES = (3, 8)


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


check_version()

ext_kwargs = {"include_dirs":       [".", "goopylib", "src", "src/vendor"],
              "library_dirs":       [f"binaries/lib-{'macos' if sys.platform == 'darwin' else 'vc2022'}"],
              "libraries":          ["goopylib"],
              "extra_compile_args": "-std=c++11 -Wno-deprecated-volatile".split() if sys.platform == "darwin" else []}

setup(packages=setuptools.find_packages(),
      package_data={"goopylib.ext": ["binaries/lib-vc2022/goopylib.dll"]} if sys.platform == "win32" else {},
      include_package_data=False,
      ext_modules=[
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
                    **ext_kwargs)
      ])
