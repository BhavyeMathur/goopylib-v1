from distutils.core import setup, Extension
import subprocess
import sys
import os

path = os.path.abspath(os.getcwd())


def build_release():
    setup(package_dir={})
    subprocess.run(["twine", "check", "dist/*"])


def build_c_extensions():
    opengl_kwargs = {"extra_link_args": ["-framework", "OpenGL", "-framework", "Cocoa",
                                         "-framework", "IOKit", "-framework", "CoreVideo",
                                         "-framework", "CoreFoundation",
                                         f"{path}/goopylib/vendor/GLFW/libglfw.3.3.dylib"],}
    ext_kwargs = {"include_dirs": ["goopylib/src", "goopylib/vendor"],
                  "extra_objects": ["goopylib/goopylib.a"],
                  "extra_compile_args": ["-std=c++11"]}

    setup(ext_modules=[Extension(name="goopylib.core", sources=["goopylib/src/extension/core.cpp"], **ext_kwargs,
                                 **opengl_kwargs)], options={"build": {"build_lib": "."}})

    setup(ext_modules=[Extension(name="goopylib.window", sources=["goopylib/src/extension/window.cpp"], **ext_kwargs,
                                 **opengl_kwargs)], options={"build": {"build_lib": "."}})

    setup(ext_modules=[Extension(name="goopylib.easing", sources=["goopylib/src/extension/easing.cpp"], **ext_kwargs)],
          options={"build": {"build_lib": "."}})

    setup(ext_modules=[Extension(name="goopylib.color", sources=["goopylib/src/extension/color.cpp"], **ext_kwargs)],
          options={"build": {"build_lib": "."}})


def build_html_documentation():
    extensions = {}
    i = 0

    def move_extensions(parent):
        nonlocal extensions, i

        for root, dirs, files in os.walk(parent):
            for item in files:
                filespec = os.path.join(root, item)
                if filespec.endswith(".so"):
                    extensions[i] = filespec
                    os.rename(filespec, f"build/{i}.so")
                    i += 1
            for item in dirs:
                move_extensions(os.path.join(root, item))  # Recursively perform this operation for subdirectories

    move_extensions("goopylib")

    with open("goopylib/python/easing.py", "r") as fp:
        new = map(lambda line: line.replace(" -> EASING_TYPE", ""), fp.readlines())
    os.rename("goopylib/python/easing.py", f"build/_easing.py")

    with open("goopylib/python/easing.py", "w+") as fp:
        fp.writelines(new)

    # noinspection PyBroadException
    try:
        p = subprocess.Popen(["make", "clean", "html"], cwd="docs")
        p.wait()
    except BaseException:
        pass
    finally:
        for i in range(i):
            os.rename(f"build/{i}.so", extensions[i])
        os.rename("build/_easing.py", f"goopylib/python/easing.py")


def countlines(start, lines=0, _header=True, _begin_start=None):
    if _header:
        print('{:>10} |{:>10} | {:<20}'.format('ADDED', 'TOTAL', 'FILE'))
        print('{:->11}|{:->11}|{:->20}'.format('', '', ''))

    for file in os.listdir(start):
        file = os.path.join(start, file)
        if os.path.isfile(file):
            if any(file.endswith(end) for end in (".py", ".c", ".cpp", ".h", ".cfg", ".hpp")):
                if not any(folder in file for folder in {"vendor", "venv", "cmake-build-debug", "build", "docs"}):
                    with open(file, 'r') as f:
                        newlines = len(f.readlines())
                        lines += newlines

                        print('{:>10} |{:>10} | {}'.format(newlines, lines, file))

    for file in os.listdir(start):
        file = os.path.join(start, file)
        if os.path.isdir(file):
            lines = countlines(file, lines, _header=False, _begin_start=start)

    return lines


arg_text = """
Choose a task to perform:
    
    1. Create goopylib release
    2. Build C extensions
    3. Count Lines of Code
    4. Create Documentation

Enter option: """

if __name__ == "__main__":
    if ((len(sys.argv) == 1) and (arg := input(arg_text))) or (arg := sys.argv[-1]) in {"1", "2", "3", "4"}:
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
    else:
        if sys.argv[1] == "sdist" and sys.argv[2] == "bdist_wheel":
            build_release()
        elif sys.argv[1] == "build":
            build_c_extensions()
