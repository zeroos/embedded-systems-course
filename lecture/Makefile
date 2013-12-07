all: slides.pdf

%.pdf: %.tex
	pdflatex $^

clean:
	-latexmk -C slides.pdf
	-rm -rf *.{nav,snm,vrb} *~
