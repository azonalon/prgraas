#!/bin/sh
zip_name=$(basename "$PWD")

make clean

[[ -f text_aufgaben.tex ]] &&  \
    pdflatex -shell-escape -file-line-error -interaction=nonstopmode \
    -output-directory="./" -halt-on-error text_aufgaben.tex

rm -f ${zip_name}.zip

zip -r ${zip_name}.zip . -x \*.aux \*.tex \*.log .\* makefile zipit.sh
