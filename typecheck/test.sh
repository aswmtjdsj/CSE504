#/bin/sh
./demo finaltest/in01 > ../in01.i
cd ..
./input_gen.py
./easm in01.i
./in01 < in01.in