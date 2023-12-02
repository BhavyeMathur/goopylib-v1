import sys
import os

import setuptools

from setup import find_extensions, check_version, RUNTIME_LIBRARY_DIRS

os.chdir("..")
check_version()

if sys.platform == "darwin":
    RUNTIME_LIBRARY_DIRS.append(f"{os.getcwd()}/binaries/lib-macos")

if len(sys.argv) == 1:
    os.chdir("tools")
    os.system("python setup_extensions.py build")
else:
    setuptools.setup(ext_modules=find_extensions(),
                     include_dirs=["vendor"],
                     options={"build": {"build_lib": "."}})
