# install dependencies
pip install build
pip install cibuildwheel

# move into goopylib folder
cd ..

# create a source distribution
python -m build --sdist

# create MacOS wheels using cibuildwheel
cibuildwheel --platform macos

# check and upload the wheels to a test site
twine check wheelhouse/*
twine upload -r testpypi wheelhouse/*
