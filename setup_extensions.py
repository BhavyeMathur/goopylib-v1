from setuptools import setup, Extension

import os
import shutil

"""
Install Visual C++ Build Tools 2015 (v14.0)
Tested on Python 3.7.9
Install MinGW C Compiler

pip install twine
pip install --upgrade setuptools

pip install build

CREATING RELEASES-------------------------------------------------------------------------------------------------------
    To create release: python setup_extensions.py sdist bdist_wheel
    sdist bdist_wheel

    To check release: twine check dist/*
    To upload release: twine upload dist/*

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

        package_dir={':math': 'goopylib/math', ":objects": 'goopylib/objects', ":applications": 'goopylib/applications',
                     ":sound": 'goopylib/sound', ":physics": 'goopylib/physics'},

        packages={"goopylib": "goopylib",
                  "goopylib/math": "goopylib/math",
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


def setup_extension(name, sources):
    name = "c_" + name
    folder_path = os.path.dirname(sources[0])
    setup(name=name,
          ext_modules=[Extension(name, sources=sources)],
          options={'build': {'build_lib': folder_path}})

    files = os.listdir(folder_path)
    for file in files:
        if '.pyd' in file and file[:len(name)] == name:
            os.rename(f"{folder_path}/{file}", f"{folder_path}/{name}.pyd")
            break


def setup_extensions(extensions):
    for extension in extensions:
        setup_extension(extension[0], [extension[1]])

    try:
        shutil.rmtree("build")
    except FileNotFoundError:
        pass


setup_extensions([("colours", "goopylib/colours.c"),
                  ("bezier_curve", "goopylib/math/bezier_curve.c")])
