import unittest
import xmlrunner

if __name__ == '__main__':
    # Create Test Suite
    test_suite = unittest.TestSuite()

    # Load All Tests
    test_cases = unittest.defaultTestLoader.discover('./tests','test*.py')
    for test in test_cases:
        test_suite.addTests(test)

    # Run tests
    test_runner = xmlrunner.XMLTestRunner(output='./reports')
    test_runner.run(test_suite)