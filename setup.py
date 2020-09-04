from setuptools import setup

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

    version='1.1.43a6',
    license='MIT License',

    description='A simple-yet-powerful 2D graphics framework built on top of Tkinter capable of creating good-looking, modern GUIs, games, and animations.',
    long_description=long_description,
    long_description_content_type="text/markdown",

    author='Bhavye Mathur',
    author_email='bhavyemathur@gmail.com',
    url='https://github.com/BhavyeMathur/goopylib',
    download_url='https://github.com/BhavyeMathur/goopylib/archive/v1.1.43-alpha.tar.gz',
    keywords=['Tkinter', '2D Graphics', 'Python GUI', 'Game Creator', 'Graphics Library'],
    install_requires=['pillow', 'numpy'],
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
