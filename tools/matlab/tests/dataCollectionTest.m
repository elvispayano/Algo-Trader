%% Data Collection Test Suite
%
% Description:
% Test suite for the Data Collection class
%
% Author:
% Elvis Payano
classdef dataCollectionTest < matlab.unittest.TestCase
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
        %% Test Inputs
        % Verify inputs are required in an expected data format
        function testInputs(tc)
            tc.verifyError(@()tc.obj.gatherHistory('1'), ...
                'dataCollection:gatherHistory:invalidInput')
            
            tc.verifyError(@()tc.obj.gatherHistory('T-2'), ...
                'dataCollection:gatherHistory:invalidInput')
        end
        
        %% Test Outputs
        % Verify outputs are provided in the expected data format
        function testOutputs(tc)
            dataObj = tc.obj.gatherHistory('MSFT');
            tc.verifyClass(dataObj.getRawData(),'py.pandas.core.frame.DataFrame')
            tc.verifyClass(dataObj.getFormattedData(),'py.list')
        end
    end
end