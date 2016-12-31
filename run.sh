#!/bin/sh

echo Fuzzy Rename and Cover Fetcher

echo "*Mission Started*"
ls roms/*.nes -1  | sort   | while read -r i ; do    

   echo "--------------------------------------"
   echo "Current directory: "
   pwd 

   echo "--------------------------------------"
   echo "Prepare the directory" 
   [ ! -d "roms" ] && mkdir roms 
   mv *.nes roms/ 

   echo "--------------------------------------"
   echo "Processing file: ($i)" 
   mv -v "$i" . 
   ls -ltra database.txt
   nes2bmp database.txt
   mv *.nes roms/ 

done 
echo "*Mission Completed*"

