from distutils.core import setup, Extension
import os

def setup_bezier_curve():
    name = "CBezierCurve"
    setup(name=name, ext_modules=[Extension(name, sources=["BezierCurve.c"])])

    try:
        os.remove(f"C:/Users/Bhavye Mathur/Documents/GitHub/goopylib/goopylib/math/{name}.pyd")
        os.remove(f"C:/Users/Bhavye Mathur/AppData/Local/Programs/Python/Python38/Lib/site-packages/{name}-0.0.0-py3.8.egg-info")
    except FileNotFoundError:
        print("File not Found")

    os.rename(
        f"C:/Users/Bhavye Mathur/AppData/Local/Programs/Python/Python38/Lib/site-packages/{name}.cp38-win_amd64.pyd",
        f"C:/Users/Bhavye Mathur/Documents/GitHub/goopylib/goopylib/math/{name}.pyd")

def setup_easing():
    setup(name="Easing", ext_modules=[Extension("Easing", sources=["Easing.c"])])

    try:
        os.remove(r"C:/Users/Bhavye Mathur/Documents/GitHub/goopylib/goopylib/math/Easing.pyd")
        os.remove(r"C:/Users/Bhavye Mathur/AppData/Local/Programs/Python/Python38/Lib/site-packages/Easing-0.0.0-py3.8.egg-info")
    except FileNotFoundError:
        pass

    os.rename(r"C:/Users/Bhavye Mathur/AppData/Local/Programs/Python/Python38/Lib/site-packages/Easing.cp38-win_amd64.pyd",
              r"C:/Users/Bhavye Mathur/Documents/GitHub/goopylib/goopylib/math/CEasing.pyd")


setup_bezier_curve()
