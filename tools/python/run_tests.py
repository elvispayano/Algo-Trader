# Import Libraries
import unittest

# Import Installed Libraries
import xmlrunner

# Main Function Handle
if __name__ == '__main__':
    # Initialize test suite object
    testSuite = unittest.TestSuite()

    # Discover all tests within the 'tests' directory
    testCase = unittest.defaultTestLoader.discover('./tests','test*.py')
    # Add each test case into the test suite
    for case in testCase:
        testSuite.addTests(case)

    # Initialize XML generating test runner
    runner = xmlrunner.XMLTestRunner(output='./reports')

    # Run all tests within test suite
    runner.run(testSuite)
