function runTest()

%% Prepare Report Generation Area
report = './reports';
if isfolder(report)
    rmdir(report,'s');
end
mkdir(report)

%% Generate Test Suite
import matlab.unittest.TestSuite

suite = TestSuite.fromFolder('./tests');

%% Generate Test Runner
import matlab.unittest.TestRunner
import matlab.unittest.plugins.XMLPlugin

xmlFile = [report '/TestResults.xml'];
pXML    = XMLPlugin.producingJUnitFormat(xmlFile);

runner  = TestRunner.withNoPlugins;
runner.addPlugin(pXML);

%% Run Tests
results = runner.run(suite);
table(results)

end