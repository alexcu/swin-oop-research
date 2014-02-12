rm results.txt

echo STATS FOR \#1 >> ./results.txt
echo ============ >> ./results.txt
perl ./cloc.pl ../../#1_CatMouse_C++_DECoupled/src/ >> ./results.txt


echo STATS FOR \#2 >> ./results.txt
echo ============ >> ./results.txt
perl ./cloc.pl ../../#2_CatMouse_ObjC_DECoupled/src/ >> ./results.txt


echo STATS FOR \#3 >> ./results.txt
echo ============ >> ./results.txt
perl ./cloc.pl ../../#3_CatMouse_C++_Coupled/src/ >> ./results.txt


echo STATS FOR \#4 >> ./results.txt
echo ============ >> ./results.txt
perl ./cloc.pl ../../#4_CatMouse_ObjC_Coupled/src/ >> ./results.txt


