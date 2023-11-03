./main -c -i OGtest.txt -o test.txt.huff -l test.log
./main -x -i test.txt.huff -o dectest.txt
./main -c -i OGtest.docx -o test.docx.huff -l test.log
./main -x -i test.docx.huff -o dectest.docx
./main -c -i OGtest.png -o test.png.huff -l test.log
./main -x -i test.png.huff -o dectest.png

RED="\033[31m"
GREEN="\033[32m"
ENDCOLOR="\033[0m"
BIGreen='\033[1;92m'
UWhite='\033[4;37m'
On_IYellow='\033[1;103m'
IGreen='\033[0;92m'
echo "${On_IYellow}Results${ENDCOLOR}\t${BIGreen}Original(MD5Hash)\t\t\tDecrypted(MD5Hash)${ENDCOLOR}"
for i in test.{txt,docx,png}; do
    echo "\033[3mcompare md5 of OG$i dec$i\033[0m"
    md51="$(md5 -q OG$i)"
    md52="$(md5 -q dec$i)"
    [ "$md51" = "$md52" ] && echo "${RED}true${ENDCOLOR}\t${IGreen}${md51}\t${md52}${ENDCOLOR}"
done
