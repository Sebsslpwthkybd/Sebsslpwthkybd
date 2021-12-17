# coding:utf-8
import unittest
import main


class Test_GUI(unittest.TestCase):
    test1 = main.proper_fraction(4, 2, 3)
    test2 = main.proper_fraction(1, 6, 8)

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

    def test_calculating(self):
        test_result = main.calculating([self.test1, '+', self.test2])
        self.assertEqual(test_result.integer, 6)
        self.assertEqual(test_result.numerator, 5)
        self.assertEqual(test_result.denominator, 12)

        test_result = main.calculating([self.test1, '-', self.test2])
        self.assertEqual(test_result.integer, 2)
        self.assertEqual(test_result.numerator, 11)
        self.assertEqual(test_result.denominator, 12)

        test_result = main.calculating([self.test1, '*', self.test2])
        self.assertEqual(test_result.integer, 8)
        self.assertEqual(test_result.numerator, 1)
        self.assertEqual(test_result.denominator, 6)

        test_result = main.calculating([self.test1, '/', self.test2])
        self.assertEqual(test_result.integer, 2)
        self.assertEqual(test_result.numerator, 2)
        self.assertEqual(test_result.denominator, 3)

    def test_calculating_number(self):
        test_result = main.calculating_number(self.test1)
        self.assertEqual(test_result, 4)

    def test_print_number(self):
        test_result = main.print_number(main.proper_fraction(8, 6, 12))
        self.assertEqual(test_result, "8'1/2")

        test_result = main.print_number(main.proper_fraction(8, 0, 12))
        self.assertEqual(test_result, "8")

        test_result = main.print_number(main.proper_fraction(8, 6, 6))
        self.assertEqual(test_result, "9")


if __name__ == '__main__':
    unittest.main()
