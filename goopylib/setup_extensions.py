from setuptools import setup, Extension

import os
import shutil

"""
Install Visual C++ Build Tools 2015 (v14.0) for Windows
Install MinGW C Compiler for Windows

Tested on Python 3.7.9 (Windows) and Python 3.8.6 (MacOSX)

pip install --upgrade setuptools
pip install build

BUILDING EXTENSIONS-----------------------------------------------------------------------------------------------------
    To build Extension: python setup_extensions.py build -c mingw32
    build -c mingw32
"""


"""
Use setup.cfg instead

def create_release():
    with open("README.md", "r") as fh:
        long_description = fh.read()

    setup(
        name='goopylib',
        version='1.1.282a24',
        download_url='https://github.com/BhavyeMathur/goopylib/archive/v1.1.282-alpha.tar.gz',

        package_dir={':maths': 'goopylib/maths', ":objects": 'goopylib/objects', ":applications": 'goopylib/applications',
                     ":sound": 'goopylib/sound', ":physics": 'goopylib/physics'},

        packages={"goopylib": "goopylib",
                  "goopylib/maths": "goopylib/maths",
                  "goopylib/objects": "goopylib/objects",
                  "goopylib/applications": "goopylib/applications",
                  "goopylib/sound": "goopylib/sound",
                  "goopylib/physics": "goopylib/physics"},

        include_package_data=True,

        license='MIT License',

        description='A simple-yet-powerful 2D graphics framework built on top of Tkinter capable of creating '
                    'good-looking, modern GUIs, games, and animations.',
        long_description=long_description,
        long_description_content_type="text/markdown",

        author='Bhavye Mathur',
        author_email='bhavyemathur@gmail.com',
        url='https://github.com/BhavyeMathur/goopylib',
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
        python_requires=">=3.6",
    )
"""


def setup_extension(source):
    name = f"c_{os.path.splitext(os.path.basename(source))[0]}"
    folder_path = os.path.dirname(source)
    if folder_path == "":
        folder_path = "."

    setup(name=name,
          ext_modules=[Extension(name, sources=[source])],
          options={'build': {'build_lib': folder_path}})

    for file in os.listdir(folder_path):
        if file.startswith(name) and file.endswith('.pyd') and file != f"{name}.pyd":
            shutil.move(f"{folder_path}/{file}", f"{folder_path}/{name}.pyd")
            break
        if file.startswith(name) and file.endswith('.so') and file != f"{name}.so":
            shutil.move(f"{folder_path}/{file}", f"{folder_path}/{name}.so")
            break


def setup_extensions(extensions):
    for extension in extensions:
        setup_extension(extension)

    try:
        shutil.rmtree("build")
    except FileNotFoundError:
        pass


setup_extensions(["colours.c", "maths/bezier_curve.c"])
