
double taxRate = 0.071;
double tax;
int grossMargin = 110100.0;

double getTax(double ytd, double gross){
	if (ytd >= grossMargin) {
		 return 0.0;
	}
	else {
		if ((ytd + gross) <= grossMargin) {
			tax = gross * taxRate;
			 return tax;
		}
		else {
			tax = (grossMargin - ytd) * taxRate;
			 return tax;
		}
	}
}