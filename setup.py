import os
import shutil
import subprocess
import sys
from distutils.core import Extension, setup
import json

path = os.path.abspath(os.getcwd())


# regex to replace function body: \) \{[^}]*\} with );


def build_release():
    try:
        shutil.rmtree("dist")
    except FileNotFoundError:
        pass

    setup(package_dir={":color": "goopylib/color", ":objects": "goopylib/objects", ":core": "goopylib/core",
                       ":events": "goopylib/events", ":ext": "goopylib/ext", ":maths": "goopylib/maths", 
                       ":scene": "goopylib/scene"},
          include_package_data=True)
    subprocess.run(["twine", "check", "dist/*"])
    subprocess.run(["twine", "upload", "-r", "testpypi", "dist/*"])


def build_c_exts():
    ext_kwargs = {"include_dirs":         ["src", "src/vendor"],
                  "extra_compile_args":   ["-std=c++11", "-v"],
                  "runtime_library_dirs": [f"{path}/goopylib"],
                  "extra_objects":        ["goopylib/goopylib.dylib"]}
    setup_kwargs = {"options": {"build": {"build_lib": "."}}}

    setup(ext_modules=[Extension(name="goopylib.ext.easing",
                                 sources=["src/ext/maths/easing.cpp"],
                                 **ext_kwargs)], **setup_kwargs)

    setup(ext_modules=[Extension(name="goopylib.ext.color_conversions",
                                 sources=["src/ext/color/conversions.cpp"],
                                 **ext_kwargs)], **setup_kwargs)

    setup(ext_modules=[Extension(name="goopylib.ext.color",
                                 sources=["src/ext/color/color.cpp"],
                                 **ext_kwargs)], **setup_kwargs)

    setup(ext_modules=[Extension(name="goopylib.ext.core",
                                 sources=["src/ext/core/core.cpp"],
                                 **ext_kwargs)], **setup_kwargs)

    setup(ext_modules=[Extension(name="goopylib.ext.window",
                                 sources=["src/ext/core/window.cpp"],
                                 **ext_kwargs)], **setup_kwargs)

    setup(ext_modules=[Extension(name="goopylib.ext.renderable",
                                 sources=["src/ext/objects/renderable.cpp"],
                                 **ext_kwargs)], **setup_kwargs)

    setup(ext_modules=[Extension(name="goopylib.ext.line",
                                 sources=["src/ext/objects/line.cpp"],
                                 **ext_kwargs)], **setup_kwargs)

    setup(ext_modules=[Extension(name="goopylib.ext.triangle",
                                 sources=["src/ext/objects/triangle.cpp"],
                                 **ext_kwargs)], **setup_kwargs)

    setup(ext_modules=[Extension(name="goopylib.ext.quad",
                                 sources=["src/ext/objects/quad.cpp"],
                                 **ext_kwargs)], **setup_kwargs)

    setup(ext_modules=[Extension(name="goopylib.ext.rectangle",
                                 sources=["src/ext/objects/rectangle.cpp"],
                                 **ext_kwargs)], **setup_kwargs)

    setup(ext_modules=[Extension(name="goopylib.ext.ellipse",
                                 sources=["src/ext/objects/ellipse.cpp"],
                                 **ext_kwargs)], **setup_kwargs)

    setup(ext_modules=[Extension(name="goopylib.ext.circle",
                                 sources=["src/ext/objects/circle.cpp"],
                                 **ext_kwargs)], **setup_kwargs)

    setup(ext_modules=[Extension(name="goopylib.ext.image",
                                 sources=["src/ext/objects/image.cpp"],
                                 **ext_kwargs)], **setup_kwargs)

    setup(ext_modules=[Extension(name="goopylib.ext.camera",
                                 sources=["src/ext/scene/camera.cpp"],
                                 **ext_kwargs)], **setup_kwargs)

    setup(ext_modules=[Extension(name="goopylib.ext.camera_controller",
                                 sources=["src/ext/scene/camera_controller.cpp"],
                                 **ext_kwargs)], **setup_kwargs)


def build_html_documentation():
    exts = {}
    i = 0

    def move_exts(parent):
        nonlocal exts, i

        for root, dirs, files in os.walk(parent):
            for item in files:
                filespec = os.path.join(root, item)
                if filespec.endswith(".so"):
                    exts[i] = filespec
                    os.rename(filespec, f"build/{i}.so")
                    i += 1
            for item in dirs:
                move_exts(os.path.join(root, item))  # Recursively perform this operation for subdirectories

    move_exts("goopylib")

    with open("goopylib/maths/easing.py", "r") as fp:
        new = map(lambda line: line.replace(" -> EASING_TYPE", ""), fp.readlines())
    os.rename("goopylib/maths/easing.py", f"build/_easing.py")

    with open("goopylib/maths/easing.py", "w+") as fp:
        fp.writelines(new)

    try:
        p = subprocess.Popen(["make", "clean", "html"], cwd="docs")
        p.wait()
    except BaseException:
        pass
    finally:
        for i in range(i):
            os.rename(f"build/{i}.so", exts[i])
        os.rename("build/_easing.py", f"goopylib/maths/easing.py")


def countlines(start, lines=0, _header=True, _begin_start=None,
               formats=(".py", ".c", ".cpp", ".h", ".hpp", ".glsl", ".frag", ".vert", ".geom", ".ipynb"),
               excluded_folders=("vendor", "venv", "build", "docs", "cmake-build-debug", "cmake-build-release"),
               excluded_files=("main.py", "main.cpp", "empty.cpp")):

    if _header:
        print("{:>10} |{:>10} | {:<20}".format("ADDED", "TOTAL", "FILE"))
        print("{:->11}|{:->11}|{:->20}".format("", "", ""))

    for file in os.listdir(start):
        filepath = os.path.join(start, file)
        if any(file.endswith(fmt) for fmt in formats) and file not in excluded_files:
            with open(filepath, "r") as f:
                if file.endswith(".ipynb"):
                    newlines = sum(len(c["source"]) for c in json.load(f)["cells"] if c["cell_type"] == "code")
                else:
                    newlines = len(f.readlines())

                lines += newlines

                print("{:>10} |{:>10} | {}".format(newlines, lines, filepath))

        elif os.path.isdir(filepath) and file not in excluded_folders:
            lines = countlines(filepath, lines, False, start, formats, excluded_folders, excluded_files)

    return lines


arg_text = """
Choose a task to perform:
    
    1. Create goopylib release
    2. Build C exts
    3. Count Lines of Code
    4. Create Documentation

Enter option: """


def run_subprocess(arg):
    if arg == "1":
        subprocess.run(["python3", "setup.py", "sdist", "bdist_wheel"])
    elif arg == "2":
        subprocess.run(["python3", "setup.py", "build"])
    elif arg == "3":
        countlines(".")
    elif arg == "4":
        build_html_documentation()
    else:
        raise ValueError(f"Unknown configuration '{arg}'")


if __name__ == "__main__":
    if len(sys.argv) == 1:
        run_subprocess(input(arg_text))
    elif sys.argv[-1] in {"1", "2", "3", "4"}:
        run_subprocess(sys.argv[-1])
    else:
        if sys.argv[1] == "sdist":
            print("Building Release")
            build_release()
        elif sys.argv[1] == "build":
            build_c_exts()
