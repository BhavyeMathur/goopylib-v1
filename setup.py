import os
import subprocess
import sys
from distutils.core import Extension, setup

path = os.path.abspath(os.getcwd())


# regex to replace function body: \) \{[^}]*\} with );


def build_release():
    setup(package_dir={})
    subprocess.run(["twine", "check", "dist/*"])


def build_c_extensions():
    ext_kwargs = {"include_dirs":         ["goopylib", "goopylib/src", "goopylib/vendor"],
                  "extra_compile_args":   ["-std=c++11", "-v"],
                  "runtime_library_dirs": [f"{path}/goopylib"],
                  "extra_objects":        ["goopylib/goopylib.dylib"]}
    setup_kwargs = {"options": {"build": {"build_lib": "."}}}

    setup(ext_modules=[Extension(name="goopylib.ext.easing",
                                 sources=["goopylib/src/extension/math/easing.cpp"],
                                 **ext_kwargs)], **setup_kwargs)

    ext_kwargs["extra_link_args"] += ["-framework", "OpenGL", "-framework", "Cocoa",
                                      "-framework", "IOKit", "-framework", "CoreVideo",
                                      "-framework", "CoreFoundation"]

    ext_kwargs["extra_link_args"] += [f"{path}/goopylib/vendor/GLFW/libglfw.3.3.dylib"]

    setup(ext_modules=[Extension(name="goopylib.ext.core",
                                 sources=["goopylib/src/extension/core/core.cpp"],
                                 **ext_kwargs)], **setup_kwargs)


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

    with open("goopylib/easing.py", "r") as fp:
        new = map(lambda line: line.replace(" -> EASING_TYPE", ""), fp.readlines())
    os.rename("goopylib/easing.py", f"build/_easing.py")

    with open("goopylib/easing.py", "w+") as fp:
        fp.writelines(new)

    try:
        p = subprocess.Popen(["make", "clean", "html"], cwd="docs")
        p.wait()
    except BaseException:
        pass
    finally:
        for i in range(i):
            os.rename(f"build/{i}.so", extensions[i])
        os.rename("build/_easing.py", f"goopylib/easing.py")


def countlines(start, lines=0, _header=True, _begin_start=None,
               formats=(".py", ".c", ".cpp", ".h", ".hpp", ".glsl", ".frag", ".vert", ".geom"),
               excluded_folders=("vendor", "venv", "build", "docs", "examples"),
               excluded_files=("main.py", "main.cpp", "empty.cpp")):

    if _header:
        print('{:>10} |{:>10} | {:<20}'.format('ADDED', 'TOTAL', 'FILE'))
        print('{:->11}|{:->11}|{:->20}'.format('', '', ''))

    for file in os.listdir(start):
        filepath = os.path.join(start, file)
        if any(file.endswith(fmt) for fmt in formats) and file not in excluded_files:
            with open(filepath, 'r') as f:
                newlines = len(f.readlines())
                lines += newlines

                print('{:>10} |{:>10} | {}'.format(newlines, lines, filepath))

        elif os.path.isdir(filepath) and file not in excluded_folders:
            lines = countlines(filepath, lines, False, start, formats, excluded_folders, excluded_files)

    return lines


arg_text = """
Choose a task to perform:
    
    1. Create goopylib release
    2. Build C extensions
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
        if sys.argv[1] == "sdist" and sys.argv[2] == "bdist_wheel":
            build_release()
        elif sys.argv[1] == "build":
            build_c_extensions()
