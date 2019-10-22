double getGross(double, double);
double getTax(double ytd, double gross);
double getNet(double gross, double taxes);
void newPage(FILE *output, double gross, double fica, double net, int pageCounter);
void printLineBreak(FILE *output);
