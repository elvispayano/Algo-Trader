'''
Setup Module

Description:
  Setup and configure the Algo Trainer Module

Author:
  Elvis Payano
'''
from setuptools import setup

if __name__ == '__main__':
  setup(name='algo_trainer',
        version='0.0.1',
        author = "Elvis Payano",
        description='Algorithm Trader Training Module',
        packages=['algo_trainer', 'algo_trainer/environments'],
        zip_safe=False)
