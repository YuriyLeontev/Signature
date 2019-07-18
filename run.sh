#!/bin/bash

make -j $(nproc --all)

# src dst size (Mb)
time ./Signature ./file.bin ./out.sig 100

# strace -c ./Signature ./file.bin ./out.sig 100
# ltrace -c ./Signature ./file.bin ./out.sig 100