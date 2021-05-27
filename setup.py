from setuptools import setup

"""
pip install twine
pip install build

CREATING RELEASES-------------------------------------------------------------------------------------------------------
    - Update README.md version number
    - Update setup.cfg version number
    - Update goopylib/__init__.py __version__ variable
    - Run setup_extensions.py and build goopylib .pyd C extensions
    - Test all Example python files, run goopylib_tests.py and test functions on Windows
    - Run goopylib_tests.py countlines() function and update README.md with line count
    - Push to GitHub, pull from MacOS computer
    - Run setup_extensions.py and build goopylib .so C extensions
    - Test all Example python files, run goopylib_tests.py and test functions on MacOS
    - Push files to GitHub
    - Create GitHub Release
    - Update download_url in setup.cfg
    - Build goopylib Release
    - Upload goopylib Release on TestPyPi
    - Install and check from TestPyPi
    - Upload goopylib Release on PyPi
    - Test goopylib installation on Windows
    - Test goopylib installation on MacOS
    
    To create source distribution: 
        1. python -m build --sdist
        2. python setup.py sdist
        
    To create (platform) wheel: 
        1. python -m build --wheel
        2. python setup.py bdist_wheel
    
    To create release (wheel and source distribution):
        1. python -m build
        2. python setup.py sdist bdist_wheel

    To check release: twine check dist/*
    To upload test release: twine upload --repository testpypi dist/*
    To install test release: pip install -i https://test.pypi.org/simple/ goopylib==version
    
    To upload release: twine upload dist/*
    To install release: pip install goopylib==version
    
    Username: BhavyeMathur
"""

setup(package_dir={':maths': 'goopylib/maths', ":objects": 'goopylib/objects', ":applications": 'goopylib/applications',
                   ":sound": 'goopylib/sound', ":physics": 'goopylib/physics'})
