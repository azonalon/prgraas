# felix: 3053850
# eduard: 3053470
zip:
	rm -f ../$${basename "$$PWD"}.zip
	zip -r $${basename "$$PWD"}.zip . -x \*.aux \*.tex \*.log

pdf:
	pdflatex -shell-escape -file-line-error -interaction=nonstopmode \
		-output-directory="$(@D)" -halt-on-error $< *.tex
