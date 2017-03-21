#!/bin/bash

# CPU make
(
  cd ../ORIG
  make
)

# DFE make
DF=DFE
(
  cd ../APP/RunRules/$DF
  make
)

# gen tests
./gen.sh

./bench.sh ../ORIG/sollp
./bench.sh ../APP/RunRules/$DF/binaries/Simplex

