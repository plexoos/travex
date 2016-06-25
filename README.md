[![Build Status](https://travis-ci.org/plexoos/travex.svg?branch=master)](https://travis-ci.org/plexoos/travex)
[![Coverity Scan Build Status](https://scan.coverity.com/projects/9254/badge.svg)](https://scan.coverity.com/projects/plexoos-travex)


This package provides a library of C++ classes which can be used to evaluate and
validate reconstruction of charged particle tracks measured by a tracking
detector. One of the objectives of this library is to design and implement such
functionality in a detector-independent way that can be applied to most common
detector configurations, reconstruction algorithms, and frameworks used in
particle physics experiments.

The code and coding style in this project are heavily based on and influenced by
the [ROOT](http://root.cern.ch) framework. The source is available at
<https://github.com/plexoos/travex> and the `doxygen` generated documentation
can be found at <http://plexoos.github.io/travex>


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

Checkout the code using the following command:

    git clone https://github.com/plexoos/travex.git

Compile and build the library and the tools:

    cd travex/
    mkdir build && cd build
    cmake ../
    make install
