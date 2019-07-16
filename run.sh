#!/bin/bash

make -j $(nproc --all)

./Signature ./file.bin ./out.sig 50
