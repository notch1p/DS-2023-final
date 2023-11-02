./main -c -i test -o test.huff -l test.log
cat test.log
./main -x -i test.huff -o test.dec
cat test.ahed.log
md5sum test
md5sum test.dec
