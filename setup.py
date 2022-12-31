import re
import shutil
import subprocess
import sys
import warnings

import setuptools
from setuptools.command.build_ext import build_ext as build_ext
from setuptools import setup, Extension

FULLVERSION = "2.0.0.dev1"
PYTHON_REQUIRES = (3, 8)


def run(cmd):
    print("GOOPYLIB:", cmd)
    subprocess.run(cmd.split())


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

    # Python supported version checks.
    if (python_major, python_minor) < PYTHON_REQUIRES:
        raise RuntimeError(f"Python version >= {PYTHON_REQUIRES[0]}.{PYTHON_REQUIRES[1]} required.")

    if (python_major, python_minor) > (3, 9):
        warnings.warn(f"goopylib {version} may not yet support Python {python_major}.{python_minor}.", RuntimeWarning)


def run_release():
    with open("pyproject.toml", "r") as f:
        content = f.read()

    content = re.sub("version = [\",'].*[\",']",
                     f"version = \"{FULLVERSION}\"", content)

    content = re.sub("requires-python = [\",'].*[\",']",
                     f"requires-python = \">={PYTHON_REQUIRES[0]}.{PYTHON_REQUIRES[1]}\"", content)

    with open("pyproject.toml", "w") as f:
        f.write(content)

    run("python -m build --sdist")

    run("twine check dist/*")
    # run("twine upload -r testpypi dist/*")


from distutils import sysconfig


class BuildSharedLibrary(build_ext):
    """Build the goopylib shared library"""

    def build_extension(self, ext):
        build_ext.build_extension(self, ext)

        extension = sysconfig.get_config_var('EXT_SUFFIX')
        print(f"GOOPYLIB: copying {self.build_lib}/goopylib/goopylib{extension} -> goopylib/")
        shutil.copy(f"{self.build_lib}/goopylib/goopylib{extension}", "goopylib")


check_version()

if len(sys.argv) == 1:
    run_release()

else:
    if sys.platform == "darwin":
        config = sysconfig.get_config_vars()
        ldshared = config["LDSHARED"]
        suffix = config["EXT_SUFFIX"]

        config["LDSHARED"] = config["LDSHARED"].replace("-bundle", "-dynamiclib")
        config["EXT_SUFFIX"] = ".dylib"

    ext_kwargs = {"include_dirs":         ["goopylib", "goopylib/src", "goopylib/src/vendor"],
                  "runtime_library_dirs": ["goopylib"],
                  "extra_objects":        [f"goopylib/goopylib{sysconfig.get_config_var('EXT_SUFFIX')}"],
                  "extra_compile_args":   "-std=c++11 -w -O0".split()}

    setup(cmdclass={"build_ext": BuildSharedLibrary},

          ext_modules=[Extension(name="goopylib.goopylib",
                                 sources=[
                                     "goopylib/src/goopylib/core/Core.cpp",
                                     # "goopylib/src/goopylib/core/BufferLayout.cpp",
                                     #
                                     # "goopylib/src/goopylib/debug/Log.cpp",
                                     #
                                     # "goopylib/src/goopylib/maths/Easing.cpp",
                                     # "goopylib/src/goopylib/maths/gpmath.cpp",
                                     #
                                     # "goopylib/src/goopylib/color/Color.cpp",
                                     # "goopylib/src/goopylib/color/ColorConversions.cpp",
                                     # "goopylib/src/goopylib/color/Util.cpp",
                                     # "goopylib/src/goopylib/color/W3CX11.cpp",
                                     #
                                     # "goopylib/src/goopylib/objects/Renderable.cpp",
                                     # "goopylib/src/goopylib/objects/Line.cpp",
                                     # "goopylib/src/goopylib/objects/Triangle.cpp",
                                     # "goopylib/src/goopylib/objects/Quad.cpp",
                                     # "goopylib/src/goopylib/objects/Ellipse.cpp",
                                     # "goopylib/src/goopylib/objects/Circle.cpp",
                                     # "goopylib/src/goopylib/objects/Image.cpp",
                                     #
                                     # "goopylib/src/goopylib/scene/Renderer.cpp",
                                     # "goopylib/src/goopylib/scene/Camera.cpp",
                                     # "goopylib/src/goopylib/scene/CameraController.cpp",
                                     #
                                     # "goopylib/src/platform/GLFW/Window.cpp",
                                     # "goopylib/src/platform/OpenGL/Buffer.cpp",
                                     # "goopylib/src/platform/OpenGL/VertexArray.cpp",
                                     # "goopylib/src/platform/OpenGL/Shader.cpp",
                                     # "goopylib/src/platform/OpenGL/Texture2D.cpp",
                                     #
                                     # "goopylib/src/goopylib/core/Window.cpp",
                                     # "goopylib/src/goopylib/core/Buffer.cpp",
                                     # "goopylib/src/goopylib/core/VertexArray.cpp",
                                     # "goopylib/src/goopylib/shader/Shader.cpp",

                                     # "goopylib/src/vendor/stb/stb_image.cpp"
                                 ],
                                 include_dirs=["goopylib", "goopylib/src", "goopylib/src/vendor"],
                                 library_dirs=["goopylib/src/vendor/GLFW"],
                                 extra_link_args=["-framework", "OpenGL"],
                                 extra_compile_args=["-std=c++20", "-w", "-O0"])])

    if sys.platform == 'darwin':
        config = sysconfig.get_config_vars()
        config["LDSHARED"] = ldshared
        config["EXT_SUFFIX"] = suffix

    setup(ext_modules=[
              # Extension(name="goopylib.ext.easing",
              #           sources=["goopylib/maths/easing.cpp"],
              #           **ext_kwargs),
              #
              # Extension(name="goopylib.ext.color_conversions",
              #           sources=["goopylib/color/conversions.cpp"],
              #           **ext_kwargs),
              #
              # Extension(name="goopylib.ext.color",
              #           sources=["goopylib/color/color.cpp"],
              #           **ext_kwargs),

              Extension(name="goopylib.ext.core",
                        sources=["goopylib/core/core.cpp"],
                        **ext_kwargs),

              # Extension(name="goopylib.ext.window",
              #           sources=["goopylib/core/window.cpp"],
              #           **ext_kwargs),
              #
              # Extension(name="goopylib.ext.renderable",
              #           sources=["goopylib/objects/renderable.cpp"],
              #           **ext_kwargs),
              #
              # Extension(name="goopylib.ext.line",
              #           sources=["goopylib/objects/line.cpp"],
              #           **ext_kwargs),
              #
              # Extension(name="goopylib.ext.triangle",
              #           sources=["goopylib/objects/triangle.cpp"],
              #           **ext_kwargs),
              #
              # Extension(name="goopylib.ext.quad",
              #           sources=["goopylib/objects/quad.cpp"],
              #           **ext_kwargs),
              #
              # Extension(name="goopylib.ext.rectangle",
              #           sources=["goopylib/objects/rectangle.cpp"],
              #           **ext_kwargs),
              #
              # Extension(name="goopylib.ext.ellipse",
              #           sources=["goopylib/objects/ellipse.cpp"],
              #           **ext_kwargs),
              #
              # Extension(name="goopylib.ext.circle",
              #           sources=["goopylib/objects/circle.cpp"],
              #           **ext_kwargs),
              #
              # Extension(name="goopylib.ext.image",
              #           sources=["goopylib/objects/image.cpp"],
              #           **ext_kwargs),
              #
              # Extension(name="goopylib.ext.camera",
              #           sources=["goopylib/scene/camera.cpp"],
              #           **ext_kwargs),
              #
              # Extension(name="goopylib.ext.camera_controller",
              #           sources=["goopylib/scene/camera_controller.cpp"],
              #           **ext_kwargs)
          ])
