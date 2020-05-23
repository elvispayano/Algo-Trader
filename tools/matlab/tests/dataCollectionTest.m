classdef dataCollectionTest < matlab.unittest.TestCase & matlab.mock.TestCase
    properties (Access = private)
        obj
    end
    
    methods (TestClassSetup)
        function setUp(tc)
            tc.obj = dataCollection;
            % Ensure creates with propery python engine
            tc.assertClass(tc.obj,'dataCollection')
        end
    end
    
    methods (Test)        
        function testInput(tc)
            tc.verifyError(@()tc.obj.gatherHistory('1'), ...
                'dataCollection:gatherHistory:invalidInput')
            
            tc.verifyError(@()tc.obj.gatherHistory('T-2'), ...
                'dataCollection:gatherHistory:invalidInput')
        end
        
        function testOutput(tc)
            dataObj = tc.obj.gatherHistory('MSFT');
            tc.verifyClass(dataObj.getRawData(),'py.pandas.core.frame.DataFrame')
            tc.verifyClass(dataObj.getFormattedData(),'py.list')
        end
    end
end