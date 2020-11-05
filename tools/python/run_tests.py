'''
Run Tests

Description:
  Generate test and coverage reports in the desired format for all python
  modules used in the project.

Author:
  Elvis Payano
'''

# Import Libraries
from unittest import defaultTestLoader, TestSuite
from os import path, walk
import sys

# Import Installed Libraries
from xmlrunner import XMLTestRunner
from coverage import Coverage
from pylint import lint

# Main Function Handle
if __name__ == '__main__':
  # Initialize test suite object
  testSuite = TestSuite()

  # Discover all tests within the 'tests' directory
  testCase = defaultTestLoader.discover('./tests', 'test*.py')
  # Add each test case into the test suite
  for case in testCase:
    testSuite.addTests(case)

  # Initialize XML generating test runner
  xmlRunner = XMLTestRunner(output='./reports')

  # Start coverage analyzer
  coverageAnalyzer = Coverage()

  # Run all tests within test suite
  coverageAnalyzer.start()
  xmlRunner.run(testSuite)
  coverageAnalyzer.stop()

  # Save coverage reports
  coverageAnalyzer.save()
  coverageAnalyzer.xml_report()

  linterArgs = list()
  for relPath, dirContents, fileList in walk('.'):
    for file in fileList:
      if file.endswith('.py'):
        linterArgs.append(path.join(relPath, file))

  resultsLint = lint.Run(linterArgs)
  if resultsLint.linter.stats['global_note'] < 4.0:
    sys.exit(1)
