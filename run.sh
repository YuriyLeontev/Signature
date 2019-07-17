#!/bin/bash

make -j $(nproc --all)

# src dst size (Mb)
time ./Signature sevastopol-6.1-20.06.2018.iso ./out.sig 100
