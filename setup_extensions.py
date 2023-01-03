import sys
import os

from setuptools import setup

from tools.packaging.version import check_version
from tools.packaging.config import RUNTIME_LIBRARY_DIRS
from tools.packaging import extensions

check_version()

if sys.platform == "darwin":
    RUNTIME_LIBRARY_DIRS.append(f"{os.getcwd()}/binaries/lib-macos")

if len(sys.argv) == 1:
    os.system("python setup_extensions.py build")
else:
    setup(ext_modules=extensions.find_extensions(),
          options={"build": {"build_lib": "."}})
