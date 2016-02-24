from binsearch import binary_search
import unittest

class MyTest(unittest.TestCase):

    def test_search(self):
        self.assertEqual(binary_search([2,3,4],3), 1)

    def test_notin(self):
        self.assertEqual(binary_search([2,3,4],1),-1)

    def test_type(self):
        with self.assertRaises(TypeError):
            binary_search(['a',3],1)

    def test_type2(self):
        with self.assertRaises(TypeError):
            binary_search(['a','b'],1)

    def test_zerol(self):
        with self.assertRaises(ValueError):
            binary_search([],1)


if __name__ == '__main__':
    unittest.main()
