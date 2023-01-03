from setuptools import setup
import setuptools

from tools.packaging import extensions
from tools.packaging.version import check_version


check_version()

setup(packages=setuptools.find_packages(),
      ext_modules=extensions.find_extensions(),
      data_files=extensions.data_files)
