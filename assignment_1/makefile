# felix: 3053850
# eduard: 3053470
zip_prefix = $(shell basename "$$PWD")
zip_suffix = %gruppe%felix_schrader_3053850%eduard_sauter_3053470
zip_name = $(zip_prefix)$(zip_suffix)

zip: pdf
	rm -f $(zip_name).zip
	zip -r $(zip_name).zip . -x \*.aux \*.tex \*.log makefile

pdf:
	pdflatex -shell-escape -file-line-error -interaction=nonstopmode \
		-output-directory="$(@D)" -halt-on-error $< *.tex
