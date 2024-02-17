import json
import os


def countlines(start,
               formats=(".py", ".c", ".cpp", ".h", ".hpp", ".glsl", ".frag", ".vert", ".geom", ".ipynb", ".bash",
                        ".dockerfile", ".bat", ".cmd", ".sh"),
               included_files=("CMakeLists.txt",),
               included_folders=("src", "tests", "examples"),
               excluded_folders=(),
               excluded_files=(),
               _header=True,
               _included=False):

    files = {}

    for file in os.listdir(start):
        filepath = os.path.join(start, file)
        if (any(file.endswith(fmt) for fmt in formats) and file not in excluded_files) or file in included_files:
            with open(filepath, "r") as f:
                if file.endswith(".ipynb"):
                    newlines = sum(len(c["source"]) for c in json.load(f)["cells"] if c["cell_type"] == "code")
                else:
                    newlines = len(f.readlines())

                files[filepath] = newlines

        elif os.path.isdir(filepath):
            if file in included_folders or _included:
                if file not in excluded_folders:
                    files.update(countlines(start=filepath,
                                            formats=formats,
                                            included_folders=included_folders,
                                            excluded_folders=excluded_folders,
                                            excluded_files=excluded_files,
                                            _header=False,
                                            _included=True))

    if _header:
        print("{:>10} |{:>10} | {:<20}".format("ADDED", "TOTAL", "FILE"))
        print("{:->11}|{:->11}|{:->20}".format("", "", ""))

        lines = 0
        for filepath, newlines in dict(sorted(files.items(), key=lambda x: x[1])).items():
            lines += newlines
            print("{:>10} |{:>10} | {}".format(newlines, lines, filepath))

    return files


countlines(start="..",
           included_folders=("src", "goopylib", "tests", "tools"))
