#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

void printTitle(FILE *output);
void printHeader(FILE *output);
void calculate(FILE *input, FILE *output);
void printSummary(FILE *output, double gross, double fica, double net, int pageCounter, int records);
void printDepSummary(FILE *output, double gross, double fica, double net);

int main() {
	FILE *input;
	FILE *output;

	char fileIn[25];
	char fileOut[25];
	char response;

	printf("Enter the input filepath: ");
	scanf("%s", fileIn);
	input = fopen(fileIn, "r");
	if (input == NULL){
		perror("Error opening input file: ");
		exit(1);
	}

	printf("Enter the output filepath: ");
	scanf("%s", fileOut);
	if((output = fopen(fileOut, "r")) != NULL){
		printf("A file by the name of '%s' already exists.\n", fileOut);
		printf("Do you wish to overwrite this file? (Y or N) ");
		scanf("%*c%c", &response);
		if (response == 'n' || response == 'N') {
			fclose(input);
			fclose(output);
			exit(1);
		}
	}
	output = fopen(fileOut, "w");
		if (output == NULL) {
			perror("Could not create output file: ");
			fclose(input);
			fclose(output);
			exit(1);
		}

	printTitle(output);
	printHeader(output);
	calculate(input, output);
	fclose(input);
	fclose(output);
	return 0;
}

void printTitle(FILE *output){
	printf("\n\t\t\t\tKhanplex Designs inc.\n\n");
	fprintf(output, "\n\t\t\t\tKhanplex Designs inc.\n\n");
}

void printHeader(FILE *output){
	char emplNum[] = "Empl.#", lastName[] = "Last-Name", firstName[] = "First-Name",
	 dep[] = "Dept.", ytd[] = "YTD", gross[] = "Gross", fica[] = "FICA", net[] = "Net";

	printf("%-8s%-12s%-12s%-8s%12s%12s%12s%12s\n",
			emplNum, lastName, firstName, dep, ytd, gross, fica, net);
	fprintf(output, "%-8s%-12s%-12s%-8s%12s%12s%12s%12s\n",
			emplNum, lastName, firstName, dep, ytd, gross, fica, net);
}

void calculate(FILE *input, FILE *output){
	int emplNum, lineCounter = 0, pageCounter = 1, records = 0;
	char lastName[20], firstName[20], dep[5];
	double rate= 0.0, hours = 0.0, fica = 0.0, ytd = 0.0, gross = 0.0, net = 0.0,
	 pGross = 0.0, pFica = 0.0, pNet = 0.0, tGross = 0.0, tFica = 0.0, tNet = 0.0;
	double depGross = 0.0, depFica = 0.0, depNet = 0.0;
	char tempDpt[8] = "";

	while((fscanf(input, "%i%s%s%s%lf%lf%lf",
		&emplNum, lastName, firstName, dep, &ytd, &rate, &hours)) != EOF) {
		records++;
		if (lineCounter == 4) {
			newPage(output, pGross, pFica, pNet, pageCounter);
			pageCounter++;
			lineCounter = 0;
			pGross = 0.0;
			pFica = 0.0;
			pNet = 0.0;
			printHeader(output);
		}

		if ((strcmp(tempDpt, "") != 0) && (strcmp(dep, tempDpt)) != 0) {
			printDepSummary(output, depGross, depFica, depNet);
			depGross = 0;
			depFica = 0;
			depNet = 0;
		}

		strcpy(tempDpt, dep);
		gross = getGross(rate, hours);
		pGross += gross;
		tGross += gross;
		depGross += gross;
		fica = getTax(ytd, gross);
		pFica += fica;
		tFica += fica;
		depFica += fica;
		net = getNet(gross, fica);
		pNet += net;
		tNet += net;
		depNet += net;

		printf("%-8i%-12s%-12s%-8s%12.2f%12.2f%12.2f%12.2f\n",
		emplNum, lastName, firstName, dep, ytd, gross, fica, net);

		fprintf(output, "%-8i%-12s%-12s%-8s%12.2f%12.2f%12.2f%12.2f\n",
		emplNum, lastName, firstName, dep, ytd, gross, fica, net);

		 lineCounter++;
	}
	printDepSummary(output, depGross, depFica, depNet);
	newPage(output, pGross, pFica, pNet, pageCounter);
	pageCounter++;
	printSummary(output, tGross, tFica, tNet, pageCounter, records);
}

void printSummary(FILE *output, double gross, double fica, double net, int pageCounter, int records){
	char pageText[] = "PAGE";
	printf("\t\t\t\t\t\tReport Summary\n\n");
	printf("\t\t\t\tRecords Processed: %10i\n", records);
	printf("\t\t\t\t      Total Gross: %10.2lf%c\n", gross, ',');
	printf("\t\t\t\t       Total FICA: %10.2lf%c\n", fica, ',');
	printf("\t\t\t\t        Total Net: %10.2lf%c\n", net, ',');
	printf("%s %i\n", pageText, pageCounter);

	fprintf(output, "\t\t\t\t\t\tReport Summary\n\n");
	fprintf(output, "\t\t\t\tRecords Processed: %i\n", records);
	fprintf(output, "\t\t\t\t      Total Gross: %10.2lf%c\n", gross, ',');
	fprintf(output, "\t\t\t\t       Total FICA: %10.2lf%c\n", fica, ',');
	fprintf(output, "\t\t\t\t        Total Net: %10.2lf%c\n", net, ',');
	fprintf(output, "%86s %i\n", pageText, pageCounter);
}

void printDepSummary(FILE *output, double gross, double fica, double net){
	char depHeader[] = "Dpt. Summary:";

	printf("%52s%12.2lf%12.2lf%12.2lf\n\n",
	 depHeader, gross, fica, net);

	fprintf(output, "%52s%12.2lf%12.2lf%12.2lf\n\n",
	 depHeader, gross, fica, net);
}



























	
