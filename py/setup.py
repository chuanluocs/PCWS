import numpy as np
from os import path
from setuptools import setup, Extension

module_pcws = Extension(
    'pcws', 
    sources = [
        '../mersenne_rng.cpp', 
        '../ResultTuple.cpp', 
        '../WeightedMinHash.cpp',  
        'entry.cpp'
    ], 
    extra_compile_args='-O3',
    include_dirs=[
        path.join(path.dirname(__file__), '..'),
        np.get_include()
    ],
    language='c++'
)

setup (name = 'pcws',
       version = '1.0',
       ext_modules = [module_pcws])