import sys
import os

from setuptools import setup

from setup import find_extensions, check_version, RUNTIME_LIBRARY_DIRS

check_version()

if sys.platform == "darwin":
    RUNTIME_LIBRARY_DIRS.append(f"{os.getcwd()}/binaries/lib-macos")

if len(sys.argv) == 1:
    os.system("python setup_extensions.py build")
else:
    setup(ext_modules=find_extensions(),
          options={"build": {"build_lib": "."}})
