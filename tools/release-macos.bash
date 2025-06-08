# install dependencies
python -m pip install build
python -m pip install twine
python -m pip install cibuildwheel

# move into goopylib folder
cd ..

# remove directories
rm -rf dist
rm -rf wheelhouse

# create a source distribution
python -m build --sdist

# create MacOS wheels using cibuildwheel
cibuildwheel --platform macos

# check and upload the wheels to a test site
twine check wheelhouse/*
twine upload -r testpypi wheelhouse/*

twine upload wheelhouse/*
