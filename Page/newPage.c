#include <stdio.h>

// void printLineBreak(FILE *output);

void newPage(FILE *output, double gross, double fica, double net, int pageCounter){
	char totalHeader[] = "Page Totals:";
	printf("\n%52s%12.2lf%12.2lf%12.2lf\n%87s%i\n\f",
	 totalHeader, gross, fica, net, "PAGE ", pageCounter);

	fprintf(output, "\n%52s%12.2lf%12.2lf%12.2lf\n%87s%i\n\f",
	 totalHeader, gross, fica, net, "PAGE ", pageCounter);

	 // printLineBreak(output);
}

// void printLineBreak(FILE *output){
// 	for (int i = 0; i < 88; ++i) {
// 		printf("-");
// 		fprintf(output, "-");
// 	}
// 	printf("\n");
// 	fprintf(output, "\n");
// }
