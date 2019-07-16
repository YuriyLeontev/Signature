#!/bin/bash

make -j $(nproc --all)

# src dst size (Mb)
./Signature ./test.bin ./test.sig 50
