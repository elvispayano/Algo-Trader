'''
Setup Module

Description:
  Setup and configure the Ticker Module

Author:
  Elvis Payano
'''
from setuptools import setup

if __name__ == '__main__':
  setup(name='ticker',
        version='1.0',
        description='Yahoo Finance Interface',
        packages=['ticker'],
        zip_safe=False)
