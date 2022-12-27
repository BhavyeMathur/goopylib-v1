import unittest
import math.easing as gp


class EasingFunctions(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.ease_linear = gp.ease_linear()
        
        cls.ease_poly_in = gp.ease_poly_in()
        cls.ease_poly_out = gp.ease_poly_out()
        cls.ease_poly = gp.ease_poly()

        cls.ease_quad_in = gp.ease_quad_in()
        cls.ease_quad_out = gp.ease_quad_out()
        cls.ease_quad = gp.ease_quad()

        cls.ease_cubic_in = gp.ease_cubic_in()
        cls.ease_cubic_out = gp.ease_cubic_out()
        cls.ease_cubic = gp.ease_cubic()

        cls.ease_quart_in = gp.ease_quart_in()
        cls.ease_quart_out = gp.ease_quart_out()
        cls.ease_quart = gp.ease_quart()

        cls.ease_quint_in = gp.ease_quint_in()
        cls.ease_quint_out = gp.ease_quint_out()
        cls.ease_quint = gp.ease_quint()

        cls.ease_sin_in = gp.ease_sin_in()
        cls.ease_sin_out = gp.ease_sin_out()
        cls.ease_sin = gp.ease_sin()

        cls.ease_exp_in = gp.ease_exp_in()
        cls.ease_exp_out = gp.ease_exp_out()
        cls.ease_exp = gp.ease_exp()

        cls.ease_circle_in = gp.ease_circle_in()
        cls.ease_circle_out = gp.ease_circle_out()
        cls.ease_circle = gp.ease_circle()

        cls.ease_back_in = gp.ease_back_in()
        cls.ease_back_out = gp.ease_back_out()
        cls.ease_back = gp.ease_back()

        cls.ease_elastic_in = gp.ease_elastic_in()
        cls.ease_elastic_out = gp.ease_elastic_out()
        cls.ease_elastic = gp.ease_elastic()

        cls.ease_bounce_in = gp.ease_bounce_in()
        cls.ease_bounce_out = gp.ease_bounce_out()
        cls.ease_bounce = gp.ease_bounce()

    # Linear Easing
    def test_linear_type_error(self):
        with self.assertRaises(TypeError):
            self.ease_linear("test")
        
    def test_linear_repr(self):
        self.assertEqual("ease_linear()", str(self.ease_linear))

    # Polynomial Easing
    def test_poly_in_type_error(self):
        with self.assertRaises(TypeError):
            self.ease_poly_in("test")
    
    def test_poly_out_type_error(self):
        with self.assertRaises(TypeError):
            self.ease_poly_out("test")
            
    def test_poly_type_error(self):
        with self.assertRaises(TypeError):
            self.ease_poly("test")

    def test_poly_repr(self):
        self.assertEqual("ease_poly(power=6.0)", str(self.ease_poly))
        self.assertEqual("ease_poly_in(power=6.0)", str(self.ease_poly_in))
        self.assertEqual("ease_poly_out(power=6.0)", str(self.ease_poly_out))

    # Quadratic Easing
    def test_quad_in_type_error(self):
        with self.assertRaises(TypeError):
            self.ease_quad_in("test")

    def test_quad_out_type_error(self):
        with self.assertRaises(TypeError):
            self.ease_quad_out("test")

    def test_quad_type_error(self):
        with self.assertRaises(TypeError):
            self.ease_quad("test")

    def test_quad_repr(self):
        self.assertEqual("ease_quad()", str(self.ease_quad))
        self.assertEqual("ease_quad_in()", str(self.ease_quad_in))
        self.assertEqual("ease_quad_out()", str(self.ease_quad_out))

    # Cubic Easing
    def test_cubic_in_type_error(self):
        with self.assertRaises(TypeError):
            self.ease_cubic_in("test")

    def test_cubic_out_type_error(self):
        with self.assertRaises(TypeError):
            self.ease_cubic_out("test")

    def test_cubic_type_error(self):
        with self.assertRaises(TypeError):
            self.ease_cubic("test")

    def test_cubic_repr(self):
        self.assertEqual("ease_cubic()", str(self.ease_cubic))
        self.assertEqual("ease_cubic_in()", str(self.ease_cubic_in))
        self.assertEqual("ease_cubic_out()", str(self.ease_cubic_out))
        
    # Quartic Easing
    def test_quart_in_type_error(self):
        with self.assertRaises(TypeError):
            self.ease_quart_in("test")

    def test_quart_out_type_error(self):
        with self.assertRaises(TypeError):
            self.ease_quart_out("test")

    def test_quart_type_error(self):
        with self.assertRaises(TypeError):
            self.ease_quart("test")

    def test_quart_repr(self):
        self.assertEqual("ease_quart()", str(self.ease_quart))
        self.assertEqual("ease_quart_in()", str(self.ease_quart_in))
        self.assertEqual("ease_quart_out()", str(self.ease_quart_out))
        
    # Quintic Easing
    def test_quint_in_type_error(self):
        with self.assertRaises(TypeError):
            self.ease_quint_in("test")

    def test_quint_out_type_error(self):
        with self.assertRaises(TypeError):
            self.ease_quint_out("test")

    def test_quint_type_error(self):
        with self.assertRaises(TypeError):
            self.ease_quint("test")

    def test_quint_repr(self):
        self.assertEqual("ease_quint()", str(self.ease_quint))
        self.assertEqual("ease_quint_in()", str(self.ease_quint_in))
        self.assertEqual("ease_quint_out()", str(self.ease_quint_out))
        
    # Quintic Easing
    def test_sin_in_type_error(self):
        with self.assertRaises(TypeError):
            self.ease_sin_in("test")

    def test_sin_out_type_error(self):
        with self.assertRaises(TypeError):
            self.ease_sin_out("test")

    def test_sin_type_error(self):
        with self.assertRaises(TypeError):
            self.ease_sin("test")

    def test_sin_repr(self):
        self.assertEqual("ease_sin()", str(self.ease_sin))
        self.assertEqual("ease_sin_in()", str(self.ease_sin_in))
        self.assertEqual("ease_sin_out()", str(self.ease_sin_out))
        
    # Exponential Easing
    def test_exp_in_type_error(self):
        with self.assertRaises(TypeError):
            self.ease_exp_in("test")

    def test_exp_out_type_error(self):
        with self.assertRaises(TypeError):
            self.ease_exp_out("test")

    def test_exp_type_error(self):
        with self.assertRaises(TypeError):
            self.ease_exp("test")

    def test_exp_repr(self):
        self.assertEqual("ease_exp(base=2.7182817459106445)", str(self.ease_exp))
        self.assertEqual("ease_exp_in(base=2.7182817459106445)", str(self.ease_exp_in))
        self.assertEqual("ease_exp_out(base=2.7182817459106445)", str(self.ease_exp_out))
        
    # Circle Easing
    def test_circle_in_type_error(self):
        with self.assertRaises(TypeError):
            self.ease_circle_in("test")

    def test_circle_out_type_error(self):
        with self.assertRaises(TypeError):
            self.ease_circle_out("test")

    def test_circle_type_error(self):
        with self.assertRaises(TypeError):
            self.ease_circle("test")

    def test_circle_repr(self):
        self.assertEqual("ease_circle()", str(self.ease_circle))
        self.assertEqual("ease_circle_in()", str(self.ease_circle_in))
        self.assertEqual("ease_circle_out()", str(self.ease_circle_out))
        
    # Back Easing
    def test_back_in_type_error(self):
        with self.assertRaises(TypeError):
            self.ease_back_in("test")

    def test_back_out_type_error(self):
        with self.assertRaises(TypeError):
            self.ease_back_out("test")

    def test_back_type_error(self):
        with self.assertRaises(TypeError):
            self.ease_back("test")

    def test_back_repr(self):
        self.assertEqual("ease_back(factor=1.7015800476074219)", str(self.ease_back))
        self.assertEqual("ease_back_in(factor=1.7015800476074219)", str(self.ease_back_in))
        self.assertEqual("ease_back_out(factor=1.7015800476074219)", str(self.ease_back_out))
        
    # Elastic Easing
    def test_elastic_in_type_error(self):
        with self.assertRaises(TypeError):
            self.ease_elastic_in("test")

    def test_elastic_out_type_error(self):
        with self.assertRaises(TypeError):
            self.ease_elastic_out("test")

    def test_elastic_type_error(self):
        with self.assertRaises(TypeError):
            self.ease_elastic("test")

    def test_elastic_repr(self):
        self.assertEqual("ease_elastic(factor=3)", str(self.ease_elastic))
        self.assertEqual("ease_elastic_in(factor=3)", str(self.ease_elastic_in))
        self.assertEqual("ease_elastic_out(factor=3)", str(self.ease_elastic_out))
        
    # Bounce Easing
    def test_bounce_in_type_error(self):
        with self.assertRaises(TypeError):
            self.ease_bounce_in("test")

    def test_bounce_out_type_error(self):
        with self.assertRaises(TypeError):
            self.ease_bounce_out("test")

    def test_bounce_type_error(self):
        with self.assertRaises(TypeError):
            self.ease_bounce("test")

    def test_bounce_repr(self):
        self.assertEqual("ease_bounce(bounces=4, damping=0.4000000059604645)", str(self.ease_bounce))
        self.assertEqual("ease_bounce_in(bounces=4, damping=0.4000000059604645)", str(self.ease_bounce_in))
        self.assertEqual("ease_bounce_out(bounces=4, damping=0.4000000059604645)", str(self.ease_bounce_out))
