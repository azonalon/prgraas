zipfiles=
zip:
	rm -f assignment.zip
	zip -r assignment.zip . -x \*.aux \*.tex \*.log
pdf:
	pdflatex -shell-escape -file-line-error -interaction=nonstopmode \
		-output-directory="$(@D)" -halt-on-error $< *.tex
