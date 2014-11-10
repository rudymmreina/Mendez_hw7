all: estado_t.pdf 

estado_t.pdf: estado_t.dat
	python graficas.py estado_t.dat

estado_t.dat:sod_test.x graficas.py
	./sod_test.x

sod_test.x: euler.c
	cc euler.c -o sod_test.x -lm


clean:
	rm -f *.pdf
