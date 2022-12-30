import warnings
import sys
import re
import setuptools


PYTHON_MAJOR = sys.version_info[0]
PYTHON_MINOR = sys.version_info[1]

# Python supported version checks.
if sys.version_info[:2] < (3, 8):
    raise RuntimeError("Python version >= 3.8 required.")


FULLVERSION = "2.0.0.dev0"

# Capture the version string:
# 1.22.0.dev0+ ... -> ISRELEASED == False, VERSION == 1.22.0
# 1.22.0rc1+ ... -> ISRELEASED == False, VERSION == 1.22.0
# 1.22.0 ... -> ISRELEASED == True, VERSION == 1.22.0
# 1.22.0rc1 ... -> ISRELEASED == True, VERSION == 1.22.0
ISRELEASED = re.search(r'(dev|\+)', FULLVERSION) is None
_V_MATCH = re.match(r'(\d+)\.(\d+)\.(\d+)', FULLVERSION)
if _V_MATCH is None:
    raise RuntimeError(f'Cannot parse version {FULLVERSION}')
MAJOR, MINOR, MICRO = _V_MATCH.groups()

VERSION = f"{MAJOR}.{MINOR}.{MICRO}"

if sys.version_info >= (3, 9):
    warnings.warn(f"goopylib {VERSION} may not yet support Python {PYTHON_MAJOR}.{PYTHON_MINOR}.", RuntimeWarning)


if __name__ == "__main__":
    setuptools.setup(packages=setuptools.find_packages())
    # subprocess.run(["twine", "check", "dist/*"])
    # subprocess.run(["twine", "upload", "-r", "testpypi", "dist/*"])
