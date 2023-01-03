from setuptools import setup
import setuptools

from tools.packaging.extensions import extensions, data_files
from tools.packaging.version import check_version


check_version()

setup(packages=setuptools.find_packages(),
      data_files=data_files,
      ext_modules=extensions.extensions)
