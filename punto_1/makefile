
all: cuerda_rho.pdf 

cuerda_rho.pdf : string_rho.dat 
	python graficas.py string_rho.dat

string_rho.dat : string.x graficas.py
	./string.x 0.01

string.x : onda.c
	cc onda.c -o string.x -lm


clean:
	rm -f *.pdf
