from setuptools import setup

with open("README.md", "r") as fh:
    long_description = fh.read()

setup(
    name='goopylib',
    package_dir={'': 'goopylib', 'math': 'goopylib/math', "objects": 'goopylib/objects'},
    py_modules=['imports', 'colours', 'constants', 'GraphWin', 'Point', 'styles', 'util',
                'math/BezierCurve', 'math/BSpline', 'math/Interpolations',
                'objects/_BBox', 'objects/Arc', 'objects/Button', 'objects/Checkbox', 'objects/Circle',
                'objects/CycleButton', 'objects/Entry', 'objects/GraphicsObject', 'objects/Image',
                'objects/Line', 'objects/Oval', 'objects/Polygon', 'objects/RadioButton',
                'objects/Rectangle', 'objects/Slider', 'objects/Text'],
    version='1.0.7a0',
    license='MIT License',

    description='A simple-yet-powerful 2D graphics framework built on top of Tkinter capable of creating good-looking, modern GUIs, games, and simple animations.',
    long_description=long_description,
    long_description_content_type="text/markdown",

    author='Bhavye Mathur',
    author_email='bhavyemathur@gmail.com',
    url='https://github.com/BhavyeMathur/goopylib',
    download_url='https://github.com/BhavyeMathur/goopylib/archive/v1.0.6-alpha.tar.gz',
    keywords=['Tkinter', '2D Graphics', 'Python GUI', 'Game Creator', 'Graphics Library'],
    install_requires=[
        'keyboard',
        'pillow',
    ],
    classifiers=[
        'Development Status :: 3 - Alpha',
        'Intended Audience :: Developers',  # Define that your audience are developers
        'Topic :: Software Development :: Build Tools',
        'License :: OSI Approved :: MIT License',  # Again, pick a license
        'Programming Language :: Python :: 3',
        'Programming Language :: Python :: 3.4',
        'Programming Language :: Python :: 3.5',
        'Programming Language :: Python :: 3.6',
        'Programming Language :: Python :: 3.7',
        'Programming Language :: Python :: 3.8'
    ],
)
