#include <iostream>

#include "Sinus.hpp"





int main(){

	const Sinus MySinus(0,1,(2*pi),0,defaulttStop,defaultNbPoints);
	
	
	std::cout << "A0 = " << MySinus.getA0() << std::endl;
	std::cout << "Amplitude = " << MySinus.getAmplitude() << std::endl;
	std::cout << "Omega = " << MySinus.getOmega() << " rad/s" << std::endl;
	std::cout << "Phase à l'origine = " << MySinus.getPhi0() << " rad" << std::endl;
	std::cout << "Nb points = " << MySinus.getNbPoints() << std::endl;
	std::cout << "tStop = " << MySinus.gettStop() << std::endl;
	std::cout << "dt = " << MySinus.getdt() << std::endl; 
	
	
	MySinus.Generate();
	
	
	return 0;
}


