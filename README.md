[![Build Status](https://travis-ci.org/plexoos/travex.svg?branch=master)](https://travis-ci.org/plexoos/travex)

This package provides a library of C++ classes which can be used to evaluate and
validate reconstruction of charged particle tracks measured by tracking
detectors. One of the objective of this library is to design and implement such
functionality in a detector-independent way that can be applied to most common
detector configurations and reconstruction algorithms and frameworks used in
particle physics experiments.

We use `doxygen` to document the code: <http://plexoos.github.io/travex/>


How to build and install the library
====================================


Prerequisites
-------------

- C++ compiler with C++11 support (e.g. g++ >= 4.8.2)
- ROOT (>= 5.34.30), http://root.cern.ch
- boost libraries (>= 1.54): `program_options`, `regex`, and `filesystem`


Build with cmake
----------------

Checkout the code using one of the following commands:

    git clone https://github.com/plexoos/travex.git   # If you do not have an account on github.com
    git clone git@github.com:plexoos/travex.git       # otherwise.

Compile and build the tools:

    cd travex/
    mkdir build && cd build
    cmake ../
    make install
