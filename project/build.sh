#!/bin/sh

# format for env.sh file:
# D='{path_to_project_root_directory}'
# WINE='env WINEPREFIX=/home/{your_user_acct_name}/.wine /usr/bin/wine'
# KEIL='C:\\Keil_v5\\UV4\\UV4.EXE' # wherever you installed Keil

source ./env.sh

cd $D
cat /dev/null > $D/out.log

$WINE $KEIL -b $D/mstar.uvproj -j0 -l $D/out.log

RES=$?

cat $D/out.log

if [ $RES -ge 2 ]; then
	exit 1
else

    echo "::::: COPYING HEX FILES :::::"
    cp $D/../build/mstar.H0* .

    echo "::::: CREATING BIN FILE :::::"
    $D/hex2bin.sh mstar

	exit 0
fi
