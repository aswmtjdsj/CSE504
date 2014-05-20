#! /bin/sh
./demo finaltest/typecheckin01 > result
echo "for finaltest/typecheckin01"
diff -w result finaltest/typecheckout01
./demo finaltest/typecheckin02 > result
echo "for finaltest/typecheckin02"
diff -w result finaltest/typecheckout02
./demo finaltest/typecheckin03 > result
echo "for finaltest/typecheckin03"
diff -w result finaltest/typecheckout03
./demo finaltest/typecheckin04 > result
echo "for finaltest/typecheckin04"
diff -w result finaltest/typecheckout04
./demo finaltest/typecheckin05 > result
echo "for finaltest/typecheckin05"
diff -w result finaltest/typecheckout05
./demo finaltest/typecheckin06 > result
echo "for finaltest/typecheckin06"
diff -w result finaltest/typecheckout06
./demo finaltest/typecheckin07 > result
echo "for finaltest/typecheckin07"
diff -w result finaltest/typecheckout07
./demo finaltest/typecheckin08 > result
echo "for finaltest/typecheckin08"
diff -w result finaltest/typecheckout08
./demo finaltest/typecheckin09 > result
echo "for finaltest/typecheckin09"
diff -w result finaltest/typecheckout09
./demo finaltest/typecheckin10 > result
echo "for finaltest/typecheckin10"
diff -w result finaltest/typecheckout10

