Executable: Accountant Insert Calculate

Accountant: Accountant.c
	gcc -o Accountant Accountant.c ./lib/kutuphanem.c

Insert: Inserter.c
	gcc Inserter.c -o Inserter

Calculate: Calc.c
	gcc Calc.c -o Calc

clean:
	rm Calc Inserter Accountant