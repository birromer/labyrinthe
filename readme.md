[![Build Status](https://travis-ci.com/birromer/labyrinthe.svg?branch=master)](https://travis-ci.com/github/birromer/labyrinthe)

# TD5 of the C++ class at ENSTA Bretagne

## Folders:
`build/` is the temporary folder for building  
`include/` has the header files  
`src/` has the source files  
`data/` has the input files for the labyrinth  
`tests/` has the test source files  
`doc/` has the generated documentation  

## Building:
In order to build you must simply

    mkdir build
    cd build
    cmake ..
    make

The unit tests can be run with

    make test
