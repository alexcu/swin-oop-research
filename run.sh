#!/bin/sh
# Runner for CatMouse

echo "CatMouse Runner"
echo "==============="
echo "1) CatMouse v1 - Decoupled C++"
echo "2) CatMouse v2 - Decoupled Objective-C"
echo "3) CatMouse v3 - Coupled C++"
echo "4) CatMouse v4 - Coupled Objective-C"
echo
read -p "Enter version number: " OPT

./bin/CatMouse_v#$OPT.app/Contents/MacOS/CatMouse

