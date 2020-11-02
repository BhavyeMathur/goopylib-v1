from setuptools import setup, Extension
from distutils.core import setup, Extension
from Cython.Build import cythonize
import os

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

        version='1.1.142a17',
        license='MIT License',

        description='A simple-yet-powerful 2D graphics framework built on top of Tkinter capable of creating good-looking, modern GUIs, games, and animations.',
        long_description=long_description,
        long_description_content_type="text/markdown",

        author='Bhavye Mathur',
        author_email='bhavyemathur@gmail.com',
        url='https://github.com/BhavyeMathur/goopylib',
        download_url='https://github.com/BhavyeMathur/goopylib/archive/v1.1.142-alpha.tar.gz',
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

def setup_bezier_curve():
    name = "CBezierCurve"
    setup(name=name,
          ext_modules=[Extension(name, sources=["goopylib/math/BezierCurve.c"])])

    try:
        os.remove(f"C:/Users/Bhavye Mathur/Documents/GitHub/goopylib/goopylib/math/{name}.pyd")
        os.remove(f"C:/Users/Bhavye Mathur/AppData/Local/Programs/Python/Python38/Lib/site-packages/{name}-0.0.0-py3.8.egg-info")
    except FileNotFoundError:
        print("File not Found")

    os.rename(
        f"C:/Users/Bhavye Mathur/AppData/Local/Programs/Python/Python38/Lib/site-packages/{name}.cp38-win_amd64.pyd",
        f"C:/Users/Bhavye Mathur/Documents/GitHub/goopylib/goopylib/math/{name}.pyd")

def setup_easing():
    name = "CEasing"
    setup(name=name,
          ext_modules=[Extension(name, sources=["goopylib/math/Easing.c"])])

    try:
        os.remove(f"C:/Users/Bhavye Mathur/Documents/GitHub/goopylib/goopylib/math/{name}.pyd")
        os.remove(f"C:/Users/Bhavye Mathur/AppData/Local/Programs/Python/Python38/Lib/site-packages/{name}-0.0.0-py3.8.egg-info")
    except FileNotFoundError:
        pass

    os.rename(f"C:/Users/Bhavye Mathur/AppData/Local/Programs/Python/Python38/Lib/site-packages/{name}.cp38-win_amd64.pyd",
              f"C:/Users/Bhavye Mathur/Documents/GitHub/goopylib/goopylib/math/{name}.pyd")

def setup_colours():
    name = "CColours"
    setup(name=name, ext_modules=[Extension(name, sources=["goopylib/colours.c"])])

    try:
        os.remove(f"C:/Users/Bhavye Mathur/Documents/GitHub/goopylib/goopylib/{name}.pyd")
    except:
        pass

    os.rename(
        f"C:/Users/Bhavye Mathur/AppData/Local/Programs/Python/Python38/Lib/site-packages/{name}-0.0.0-py3.8-win-amd64.egg/Ccolours.cp38-win_amd64.pyd",
        f"C:/Users/Bhavye Mathur/Documents/GitHub/goopylib/goopylib/{name}.pyd")


create_release()
