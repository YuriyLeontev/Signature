#!/bin/bash

make -j $(nproc --all)

# src dst size (Mb)
time ./Signature ./file4.bin ./out.sig 100
