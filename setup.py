from setuptools import setup, find_packages

with open("README.md", "r") as fh:
    long_description = fh.read()

setup(
    name='goopylib',
    package_dir={':math': 'goopylib/math', ":objects": 'goopylib/objects'},
    packages={"goopylib": "goopylib", "goopylib/math": "goopylib/math", "goopylib/objects": "goopylib/objects"},
    version='1.0.7a6',
    license='MIT License',

    description='A simple-yet-powerful 2D graphics framework built on top of Tkinter capable of creating good-looking, modern GUIs, games, and simple animations.',
    long_description=long_description,
    long_description_content_type="text/markdown",

    author='Bhavye Mathur',
    author_email='bhavyemathur@gmail.com',
    url='https://github.com/BhavyeMathur/goopylib',
    download_url='https://github.com/BhavyeMathur/goopylib/archive/v1.0.7-alpha0.tar.gz',
    keywords=['Tkinter', '2D Graphics', 'Python GUI', 'Game Creator', 'Graphics Library'],
    install_requires=[
        'keyboard',
        'pillow',
    ],
    classifiers=[
        'Development Status :: 3 - Alpha',
        'Intended Audience :: Developers',
        'Topic :: Software Development :: Build Tools',
        'License :: OSI Approved :: MIT License',
        'Programming Language :: Python :: 3',
        'Programming Language :: Python :: 3.4',
        'Programming Language :: Python :: 3.5',
        'Programming Language :: Python :: 3.6',
        'Programming Language :: Python :: 3.7',
        'Programming Language :: Python :: 3.8'
    ],
)
