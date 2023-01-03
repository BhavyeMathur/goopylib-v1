from setuptools import setup

from tools.packaging.extensions import extensions
from tools.packaging.version import check_version

check_version()

setup(ext_modules=extensions,
      options={"build": {"build_lib": "."}})
