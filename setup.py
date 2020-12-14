from setuptools import setup, Extension
from distutils.core import setup, Extension

import os
import platform
import shutil


def create_release():
    with open("README.md", "r") as fh:
        long_description = fh.read()

    setup(
        name='goopylib',
        package_dir={':math': 'goopylib/math', ":objects": 'goopylib/objects', ":applications": 'goopylib/applications',
                     ":sound": 'goopylib/sound', ":physics": 'goopylib/physics'},

        packages={"goopylib": "goopylib",
                  "goopylib/math": "goopylib/math",
                  "goopylib/objects": "goopylib/objects",
                  "goopylib/applications": "goopylib/applications",
                  "goopylib/sound": "goopylib/sound",
                  "goopylib/physics": "goopylib/physics"},

        include_package_data=True,

        version='1.1.246a22',
        license='MIT License',

        description='A simple-yet-powerful 2D graphics framework built on top of Tkinter capable of creating '
                    'good-looking, modern GUIs, games, and animations.',
        long_description=long_description,
        long_description_content_type="text/markdown",

        author='Bhavye Mathur',
        author_email='bhavyemathur@gmail.com',
        url='https://github.com/BhavyeMathur/goopylib',
        download_url='https://github.com/BhavyeMathur/goopylib/archive/v1.1.246-alpha.tar.gz',
        keywords=['Tkinter', '2D Graphics', 'Python GUI', 'Game Creator', 'Graphics Library'],
        install_requires=['pillow'],
        project_urls={"Bug Tracker": "https://github.com/BhavyeMathur/goopylib/issues",
                      "Documentation": "https://github.com/BhavyeMathur/goopylib/wiki",
                      "Source Code": "https://github.com/BhavyeMathur/goopylib/tree/master/goopylib"},
        classifiers=[
            'Intended Audience :: Developers',
            'Topic :: Software Development :: Build Tools',
            'License :: OSI Approved :: MIT License',
        ],
        python_requires=">=3.6"
    )


def setup_extension(name, sources, output):
    name = "c_" + name
    setup(name=name, ext_modules=[Extension(name, sources=sources)])

    system = platform.system()

    try:
        if system == "Windows":
            try:
                os.remove(f"goopylib/{output}{name}.pyd")
            except FileNotFoundError:
                pass
            os.rename(f"build/lib.win-amd64-3.8/{name}.cp38-win_amd64.pyd", f"goopylib/{output}{name}.pyd")

        elif system == "Darwin":
            try:
                os.remove(f"goopylib/{output}{name}.o")
            except FileNotFoundError:
                pass
            os.rename(f"build/lib.macosx-10.9-x86_64-3.8/{name}.cpython-38-darwin.so", f"goopylib/{output}{name}.so")

            shutil.rmtree("dist")
            shutil.rmtree(f"{name}.egg-info")

    except FileNotFoundError as e:
        print(e)

    shutil.rmtree("build")


# setup_extension("colours", ["goopylib/colours.c"], "")
# setup_extension("easing", ["goopylib/math/Easing.c"], "math/")
# setup_extension("bezier_curve", ["goopylib/math/bezier_curve.c"], "math/")

create_release()

# To create release: python setup.py sdist bdist_wheel
# To build Extension: python setup.py build
