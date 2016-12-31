# fuzzyrename-nes-covers



  ########################################################
  ########################################################
  ########################################################
  ############ Fuzzy Rename and Cover Fetcher ############
  ########################################################
  ########################################################
  ########################################################


========================================================================
 Requirements
========================================================================

  1. gcc and linux (can be easily ported to Windows)
           gcc nes2bmp.c  -o nes2bmp
           then move the nes2bmp to your /usr/bin directory
           afterwards you can run run.sh 

  2. here the first argument must and shall be the database.txt
  3. roms into dir roms/ (with .nes)
  4. covers into snaps/ (with .png) 
  5. target dir 

  "target" dir will be the folder with all bmp files (resized 300%)




========================================================================
 Use
========================================================================

           wget the database "database.txt"
           gcc nes2bmp.c  -o nes2bmp
           mv nes2bmp /usr/bin
           sh run.sh 
           and you will find the covers into the directory "target" 



