# Run Tests
#
# Generate test and coverage reports in the desired format for all python
# modules used in the project.
#
# Author: Elvis Payano

# Import Libraries
import unittest

# Import Installed Libraries
import xmlrunner
import coverage

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

    # Start coverage analyzer
    cov = coverage.Coverage()

    # Run all tests within test suite
    cov.start()
    runner.run(testSuite)
    cov.stop()

    # Save coverage reports
    cov.save()
    cov.xml_report()