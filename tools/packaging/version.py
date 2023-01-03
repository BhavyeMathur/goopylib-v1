import sys
import re
import warnings

FULLVERSION = "2.0.0.dev5"
PYTHON_REQUIRES = (3, 8)


def check_version():
    python_major = sys.version_info[0]
    python_minor = sys.version_info[1]

    # Capture the version string:
    # 1.22.0.dev0+ ... -> ISRELEASED == False, VERSION == 1.22.0
    # 1.22.0rc1+ ... -> ISRELEASED == False, VERSION == 1.22.0
    # 1.22.0 ... -> ISRELEASED == True, VERSION == 1.22.0
    # 1.22.0rc1 ... -> ISRELEASED == True, VERSION == 1.22.0
    is_released = re.search(r'(dev|\+)', FULLVERSION) is None
    _V_MATCH = re.match(r'(\d+)\.(\d+)\.(\d+)', FULLVERSION)
    if _V_MATCH is None:
        raise RuntimeError(f'Cannot parse version {FULLVERSION}')
    major, minor, micro = _V_MATCH.groups()

    version = f"{major}.{minor}.{micro}"

    # Python supported version checks

    if (python_major, python_minor) < PYTHON_REQUIRES:
        raise RuntimeError(f"Python version >= {PYTHON_REQUIRES[0]}.{PYTHON_REQUIRES[1]} required.")

    if (python_major, python_minor) > (3, 11):
        warnings.warn(f"goopylib {version} may not yet support Python {python_major}.{python_minor}.", RuntimeWarning)

    # Update the pyproject.toml file with these version details

    with open("pyproject.toml", "r") as f:
        content = f.read()

    content = re.sub("version = [\",'].*[\",']",
                     f"version = \"{FULLVERSION}\"", content)

    content = re.sub("requires-python = [\",'].*[\",']",
                     f"requires-python = \">={PYTHON_REQUIRES[0]}.{PYTHON_REQUIRES[1]}\"", content)

    with open("pyproject.toml", "w") as f:
        f.write(content)

    # Update the setup.cfg file with these version details

    with open("setup.cfg", "r") as f:
        content = f.read()

    content = re.sub("version = .*",
                     f"version = {FULLVERSION}", content)

    content = re.sub("python_requires = .*",
                     f"python_requires = >={PYTHON_REQUIRES[0]}.{PYTHON_REQUIRES[1]}", content)

    with open("pyproject.toml", "w") as f:
        f.write(content)
