from distutils.core import setup
setup(
  name = 'goopylib', 
  packages = ['goopylib'],
  version = '1.0.0',
  license='Unlicense',
  description = 'A simple-yet-powerful 2D graphics framework built on top of Tkinter capable of creating good-looking, modern GUIs, games, and simple animations.',
  author = 'Bhavye Mathur',
  author_email = 'bhavyemathur@gmail.com',
  url = 'https://github.com/BhavyeMathur/goopylib',
  download_url = 'https://github.com/BhavyeMathur/goopylib/archive/v1.0-alpha.tar.gz',
  keywords = ['Tkinter', '2D Graphics', 'Python GUI', 'Game Creator', 'Graphics Library'],
  install_requires=[       
          'keyboard',
          'pillow',
      ],
  classifiers=[
    'Development Status :: 3 - Alpha',
    'Intended Audience :: Developers',      # Define that your audience are developers
    'Topic :: Software Development :: Build Tools',
    'License :: OSI Approved :: Unlicense',   # Again, pick a license
    'Programming Language :: Python :: 3',
    'Programming Language :: Python :: 3.4',
    'Programming Language :: Python :: 3.5',
    'Programming Language :: Python :: 3.6',
    'Programming Language :: Python :: 3.7',
    'Programming Language :: Python :: 3.8'
  ],
)
