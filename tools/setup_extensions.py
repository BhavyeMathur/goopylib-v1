import sys
import os

import setuptools

from setup import find_extensions, check_version, RUNTIME_LIBRARY_DIRS

if os.getcwd().endswith("tools"):
    os.chdir("..")

check_version()

if sys.platform == "darwin":
    RUNTIME_LIBRARY_DIRS.append(f"{os.getcwd()}/binaries/lib-macos")

if len(sys.argv) == 1:
    option = int(input("""Choose what to do:
    1. Build automatically
    2. Build all extensions\n
    """))

    if option == 2:
        for item in os.listdir("goopylib/ext"):
            if item.endswith(".so"):
                os.remove(f"goopylib/ext/{item}")

    elif option != 1:
        raise ValueError("Unknown option")

    os.system("python tools/setup_extensions.py build")
else:
    setuptools.setup(ext_modules=find_extensions(),
                     include_dirs=["vendor"],
                     options={"build": {"build_lib": "."}})
