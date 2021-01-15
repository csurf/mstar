#!/bin/sh
# script to merge two hex files 
# into single128k binary file
# requires srec package

f=$1
srec_cat \
--disable-sequence-warning \
--contradictory-bytes=ignore \
--redundant-bytes=ignore \
$f.H00 -Intel -fill 0XFF 0x0 0x20000 \
$f.H01 -Intel -offset 0x10000 \
-o $f.bin -Binary
