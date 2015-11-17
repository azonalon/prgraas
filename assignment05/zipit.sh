#!/bin/sh
zip_name=$(basename "$PWD")

make clean

rm -f ${zip_name}.zip

zip -r ${zip_name}.zip . -x \*.aux \*.tex \*.log .\* makefile zipit.sh
