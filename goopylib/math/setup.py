from distutils.core import setup, Extension
import os

module = Extension("BezierCurve", sources=["BezierCurve.c"])

setup(name="BezierCurve", ext_modules=[module])

print("Moving File")

file = 0
try:
    os.remove(r"C:\Users\Bhavye Mathur\Documents\GitHub\goopylib\goopylib\math\BezierCurve.pyd")
    file += 1
    os.remove(r"C:\Users\Bhavye Mathur\AppData\Local\Programs\Python\Python38\Lib\site-packages\BezierCurve-0.0.0-py3.8.egg-info")
    file += 1
    os.remove(r"C:\Users\Bhavye Mathur\Documents\GitHub\goopylib\goopylib\math\build")
except FileNotFoundError:
    print(f"File {file} not Found")
except PermissionError:
    print(f"Permission to remove file {file} denied")

os.rename(r"C:\Users\Bhavye Mathur\AppData\Local\Programs\Python\Python38\Lib\site-packages\BezierCurve.cp38-win_amd64.pyd",
          r"C:\Users\Bhavye Mathur\Documents\GitHub\goopylib\goopylib\math\BezierCurve.pyd")
