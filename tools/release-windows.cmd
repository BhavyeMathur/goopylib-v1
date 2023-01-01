# create a source distribution
python -m build --sdist

# create Windows wheels using cibuildwheel
cibuildwheel --platform windows

# check and upload the wheels to a test site
twine check wheelhouse/*
twine upload -r testpypi wheelhouse/*
cd
