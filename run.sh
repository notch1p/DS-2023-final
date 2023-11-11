RED="\033[31m"
GREEN="\033[32m"
ENDCOLOR="\033[0m"
BIGreen='\033[1;92m'
UWhite='\033[4;37m'
On_IYellow='\033[1;103m'
IGreen='\033[0;92m'
for i in OG{doc.docx,main,pic.bmp,text.txt}; do
    ./main -c -i $i -o enc$i
    ./main -x -i enc$i -o dec$i -q
done
echo "${On_IYellow}Results${ENDCOLOR}\t${BIGreen}Original(MD5Hash)\t\t\tDecrypted(MD5Hash)${ENDCOLOR}"
for i in OG{doc.docx,main,pic.bmp,text.txt}; do
    echo "\033[3mcompare md5 of OG$i dec$i\033[0m"
    md51="$(md5 -q $i)"
    md52="$(md5 -q dec$i)"
    [ "$md51" = "$md52" ] && echo "${RED}true${ENDCOLOR}\t${IGreen}${md51}\t${md52}${ENDCOLOR}"
done
