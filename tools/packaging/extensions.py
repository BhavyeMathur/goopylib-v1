import sys

from setuptools import Extension

if sys.platform == "darwin":
    compile_args = ["-std=c++11", "-Wno-macro-redefined"]
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

ext_kwargs = {"include_dirs":       [".", "goopylib", "src", "src/vendor"],
              "library_dirs":       library_dirs,
              "libraries":          ["goopylib"],
              "extra_compile_args": compile_args}

extensions = [
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
]
