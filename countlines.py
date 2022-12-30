import json
import os


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


countlines(".")
