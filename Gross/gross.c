
double getGross(double rate, double hours){
	if (hours > 40.0) {
		double overtime = hours - 40.0;
		return (rate * 40.0) + (overtime * (rate * 1.5));
	}
	else
		return hours * rate;
}