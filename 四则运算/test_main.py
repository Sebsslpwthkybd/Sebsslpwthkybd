# utf-8
import unittest
import main
from main import proper_fraction


class Test_GUI(unittest.TestCase):
    test1 = proper_fraction(4, 2, 3)
    test2 = proper_fraction(1, 6, 8)

    def test_add(self):
        test_result = main.add_proper_fraction(self.test1, self.test2)
        self.assertEqual(test_result.integer, 6)
        self.assertEqual(test_result.numerator, 5)
        self.assertEqual(test_result.denominator, 12)

    def test_subtract(self):
        test_result = main.subtract_proper_fraction(self.test1, self.test2)
        self.assertEqual(test_result.integer, 2)
        self.assertEqual(test_result.numerator, 11)
        self.assertEqual(test_result.denominator, 12)

    def test_reduce_fraction(self):
        numerator, denominator = main.reduce_fraction(self.test2.numerator, self.test2.denominator)
        self.assertEqual(numerator, 3)
        self.assertEqual(denominator, 4)

    def test_multiply(self):
        test_result = main.multiply_proper_fraction(self.test1, self.test2)
        self.assertEqual(test_result.integer, 8)
        self.assertEqual(test_result.numerator, 1)
        self.assertEqual(test_result.denominator, 6)

    def test_divide(self):
        test_result = main.divide_proper_fraction(self.test1, self.test2)
        self.assertEqual(test_result.integer, 2)
        self.assertEqual(test_result.numerator, 2)
        self.assertEqual(test_result.denominator, 3)


if __name__ == '__main__':
    unittest.main()
