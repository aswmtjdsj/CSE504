#/bin/sh
./demo test1 > ../test1.i
cd ..
./input_gen.py
./easm test1.i
./test1 < test1.in
