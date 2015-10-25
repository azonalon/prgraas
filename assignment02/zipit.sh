zip_prefix=$(basename "$PWD")
zip_name='assignment02'

make clean

pdflatex -shell-escape -file-line-error -interaction=nonstopmode \
    -output-directory="./" -halt-on-error text_aufgaben.tex

rm -f ${zip_name}.zip

zip -r ${zip_name}.zip . -x \*.aux \*.tex \*.log makefile
