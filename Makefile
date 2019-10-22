payroll: main.o gross.o tax.o net.o newPage.o
	gcc main.o gross.o tax.o net.o newPage.o -o payroll

main.o: Main/main.c Main/functions.h 
	gcc -c Main/main.c -Wextra -Wall -pedantic

gross.o: Gross/gross.c
	gcc -c Gross/gross.c

tax.o: FICA/tax.c
	gcc -c FICA/tax.c

net.o: Net/net.c
	gcc -c Net/net.c

newPage.o: Page/newPage.c
	gcc -c Page/newPage.c

clean:
	rm *.o payroll