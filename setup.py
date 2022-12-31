import re
import os
import shutil
import subprocess
import sys
import warnings
from distutils import sysconfig
from distutils import log
from distutils.core import setup, Extension
from distutils.dep_util import newer_group
from distutils.errors import DistutilsSetupError
from distutils.command.build_ext import build_ext
from distutils.command.install import install

import setuptools

FULLVERSION = "2.0.0.dev1"
PYTHON_REQUIRES = (3, 8)

GOOPYLIB_LIBRARY = "goopylib" + sysconfig.get_config_var("EXT_SUFFIX")
if sys.platform == "darwin":
    GOOPYLIB_LIBRARY.replace(".so", ".dylib")


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


class Install(install):
    pass


class BuildExtension(build_ext):
    def build_extension(self, ext):
        if ext.name == "goopylib.goopylib":
            if ext.sources is None or not isinstance(ext.sources, (list, tuple)):
                raise DistutilsSetupError(f"in 'ext_modules' option (extension '{ext.name}'), 'sources' must be present"
                                          f" and must be a list of source filenames")

            # Sort to make the resulting .so file build reproducible
            sources = sorted(ext.sources)
            ext_path = self.get_ext_fullpath(ext.name)

            depends = sources + ext.depends
            if not (self.force or newer_group(depends, ext_path, 'newer')):
                log.debug("skipping '%s' shared library (up-to-date)", ext.name)
                return
            else:
                log.info("building '%s' shared library", ext.name)

            # First, compile the source code to object files.

            extra_args = ext.extra_compile_args or []

            macros = ext.define_macros[:]
            for undef in ext.undef_macros:
                macros.append((undef,))

            objects = self.compiler.compile(sources,
                                            output_dir=self.build_temp,
                                            macros=macros,
                                            include_dirs=ext.include_dirs,
                                            debug=self.debug,
                                            extra_postargs=extra_args,
                                            depends=ext.depends)

            # Now link the object files together into a "shared library"

            if ext.extra_objects:
                objects.extend(ext.extra_objects)
            extra_args = ext.extra_link_args or []

            linking_args = f"-L{' -L'.join(ext.library_dirs)} {' '.join(extra_args)} -l{' -l'.join(ext.libraries)}"
            run(f"g++ {' '.join(objects)} -shared {linking_args} -o goopylib/{GOOPYLIB_LIBRARY}")

            shutil.copy(f"goopylib/{GOOPYLIB_LIBRARY}", ".")
            os.rename(GOOPYLIB_LIBRARY, ext_path)

        else:
            build_ext.build_extension(self, ext)


check_version()

if len(sys.argv) == 1:
    run_release()

else:
    ext_kwargs = {"include_dirs":         ["goopylib", "goopylib/src", "goopylib/src/vendor"],
                  "runtime_library_dirs": ["goopylib"],
                  "extra_objects":        [f"goopylib/{GOOPYLIB_LIBRARY}"],
                  "extra_compile_args":   "-std=c++11 -w".split()}

    setup(packages=setuptools.find_packages(),
          include_package_data=False,
          cmdclass={"build_ext": BuildExtension},
          ext_modules=[
              Extension(name="goopylib.goopylib",
                        sources=[
                            "goopylib/src/goopylib/core/Core.cpp",
                            "goopylib/src/goopylib/core/BufferLayout.cpp",

                            "goopylib/src/goopylib/debug/Log.cpp",

                            "goopylib/src/goopylib/maths/Easing.cpp",
                            "goopylib/src/goopylib/maths/gpmath.cpp",

                            "goopylib/src/goopylib/color/Color.cpp",
                            "goopylib/src/goopylib/color/ColorConversions.cpp",
                            "goopylib/src/goopylib/color/Util.cpp",
                            "goopylib/src/goopylib/color/W3CX11.cpp",

                            "goopylib/src/goopylib/objects/Renderable.cpp",
                            "goopylib/src/goopylib/objects/Line.cpp",
                            "goopylib/src/goopylib/objects/Triangle.cpp",
                            "goopylib/src/goopylib/objects/Quad.cpp",
                            "goopylib/src/goopylib/objects/Ellipse.cpp",
                            "goopylib/src/goopylib/objects/Circle.cpp",
                            "goopylib/src/goopylib/objects/Image.cpp",

                            "goopylib/src/goopylib/scene/Renderer.cpp",
                            "goopylib/src/goopylib/scene/Camera.cpp",
                            "goopylib/src/goopylib/scene/CameraController.cpp",

                            "goopylib/src/platform/GLFW/Window.cpp",
                            "goopylib/src/platform/OpenGL/Buffer.cpp",
                            "goopylib/src/platform/OpenGL/VertexArray.cpp",
                            "goopylib/src/platform/OpenGL/Shader.cpp",
                            "goopylib/src/platform/OpenGL/Texture2D.cpp",

                            "goopylib/src/goopylib/core/Window.cpp",
                            "goopylib/src/goopylib/core/Buffer.cpp",
                            "goopylib/src/goopylib/core/VertexArray.cpp",
                            "goopylib/src/goopylib/shader/Shader.cpp",

                            "goopylib/src/vendor/stb/stb_image.cpp"
                        ],
                        include_dirs=["goopylib", "goopylib/src", "goopylib/src/vendor"],
                        library_dirs=["goopylib/src/vendor/GLFW"],
                        libraries=["glfw.3"],
                        extra_link_args=["-framework", "OpenGL"],
                        extra_compile_args=["-std=c++17", "-w", "-O0"]),

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
