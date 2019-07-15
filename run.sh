#!/bin/bash

make -j $(nproc --all)

./Signature ./test.bin ./out.sig 10


