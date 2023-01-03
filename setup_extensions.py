from distutils.core import setup, Extension


setup(name="fputs",
      version="2.0.0",
      description="Python interface for the fputs C library function",
      author="<your name>",
      author_email="your_email@gmail.com",
      ext_modules=[Extension("fputs", ["fputsmodule.c"])])
