clear

# install dependencies
python -m pip install matplotlib
python -m pip install seaborn

python -m pip install sphinx
python -m pip install sphinxcontrib-katex
python -m pip install sphinx-rtd-theme

cd ../docs || exit

# create graphs
python api_reference/easing_graphs/easing_graphs.py

# create docs
make html
