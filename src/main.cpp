#include <iostream>
#include <string>
#include <math.h>
#include <functional>
#include "Eseries.h"

typedef struct Resistors {
	double R1;
	double R2;
	Resistors(double r1, double r2) : R1(r1), R2(r2) {}
	Resistors() : R1(0), R2(0) {}
	Resistors(double r) : R1(r), R2(r) {}
} Resistors;

void calc_R_ratio(unsigned int series, std::function<bool(Resistors,Resistors)> compare,Resistors& R){
	auto Eseries = E192_E24_Series(series);
	for(auto i : Eseries)
		for(auto j : Eseries)
			if (compare(R, Resistors(i,j)))
				R = Resistors(i,j);
}

double normalise(double ratio){
	if (ratio > 1){
		int div = std::log10(ratio);
		return ratio / std::pow(10,div+1);
	}
	return ratio;
}

double denormalise(double ratio){
	double ret = 1;
	if (ratio > 1){
		int div = std::log10(ratio);
		ret *= std::pow(10,div+1);
	}
	return ret;
}

void parse_args(int argc, char** argv, unsigned int& series, double& ratio){
	if (argc < 2 || argc > 3){
		std::cout << "Usage: " << argv[0] << " <ratio> <series>" << std::endl;
		std::cout << "Or: " << argv[0] << " <ratio>" << std::endl;
		std::cout << "With <ratio> being A/B or a decimal fraction." << std::endl;
		std::cout << "And with <series> being one of [3,6,12,24,48,96,192]." << std::endl;
		exit(1);
	}
	if (argc == 3){
		double pows = std::strtoul(argv[2],NULL,10);
		if(pows <= 0){
			std::cout << "Series must be a positive integer." << std::endl;
			exit(1);
		}
		pows /= 3;
		double tmp = std::log2(pows);
		if(tmp != (int)tmp || tmp > 6 || pows < 1){
			std::cout << "Series must be one of [3,6,12,24,48,96,192]." << std::endl;
			exit(1);
		}
		series = (int)tmp;
	}
	ratio = std::strtod(argv[1],NULL);
	if(ratio <= 0){
		if(std::string(argv[1]).find("/") != std::string::npos){
			std::string tmp = std::string(argv[1]);
			int pos = tmp.find("/");
			double num = std::strtol(tmp.substr(0,pos).c_str(),NULL,10);
			double den = std::strtol(tmp.substr(pos+1).c_str(),NULL,10);
			if(num <= 0 || den <= 0){
				std::cout << "Ratio must conatain 2 positive whole integers." << std::endl;
				exit(1);
			}
			ratio = num/den;
		} else{
			std::cout << "Ratio must be A/B or a decimal fraction." << std::endl;
			exit(1);
		}
	}
}

int main(int argc, char* argv[]) {
	Resistors R(1);
	unsigned int series = 3; // E24
	double ratio = 1;
	parse_args(argc, argv, series, ratio);
	double NormRatio = normalise(ratio);
	auto compare = [NormRatio](Resistors RO, Resistors RN) -> bool {
		double O = (RO.R1/RO.R2)-NormRatio;
		double N = (RN.R1/RN.R2)-NormRatio;
		if(N < 0) return false;
		return O > N;
	};
	calc_R_ratio(series,compare, R);
	std::cout << R.R1*denormalise(ratio) << "/" << R.R2 << "="<< (R.R1/R.R2)*denormalise(ratio) << std::endl;
	return 0;
}
