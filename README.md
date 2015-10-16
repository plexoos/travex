[![Build Status](https://travis-ci.org/plexoos/travex.svg?branch=master)](https://travis-ci.org/plexoos/travex)

This package provides a library of C++ classes which can be used to evaluate and
validate reconstruction of charged particle tracks as measured by a tracking
detector. One of the objectives of this library is to design and implement such
functionality in a detector-independent way that can be applied to most common
detector configurations and reconstruction algorithms and frameworks used in
particle physics experiments.

Currently, the code is available at <https://github.com/plexoos/travex> and the
`doxygen` generated documentation can be found at
<http://plexoos.github.io/travex>


The Concept
===========

This tools is designed to answer the following questions:

- Given a hit produced and reconstructed in the detector (i.e. the hit is
  available for reconstruction), what is the probability to assign this hit to
  a reconstructed track?

- Given a hit assigned to the reconstructed track, what is the probability for
  this hit to be the actual (i.e. true) hit produced by the track?


The following entities must be provided by the user:

- A reconstructed track
- A set of hit candidates for the track node in question
- A condition to select the best candidate
- Info what hit was accepted by the reconstruction algorithm (in case of not skipped layer)



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
