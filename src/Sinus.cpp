
#include "Sinus.hpp"

//----------------------------------------------------------------------
Sinus::Sinus(float A0, float Amplitude, float Omega, float Phi0, float tStop, unsigned int NbPoints):A0{A0},Amplitude{Amplitude},Omega{Omega},Phi0{Phi0},tStop{tStop},NbPoints{NbPoints}{
	
	Refresh_dt();
	while(this->Phi0 > (2*pi)) this->Phi0 -= (2*pi); 	// Phi0 ramenée, si nécessaire dans [0;2PI] 
}
//----------------------------------------------------------------------
void	Sinus::setPhi0(float Phi0){
	
	this->Phi0 = Phi0;
	while(this->Phi0 > (2*pi)) this->Phi0 -= (2*pi); 	// Phi0 ramenée, si nécessaire dans [0;2PI] 
}
//----------------------------------------------------------------------
void	Sinus::Refresh_dt()const{
	
	if (tStop <= 0) tStop = defaulttStop;	// Reset tStop to 1 in case of wrong/bad value
	if (NbPoints == 0) NbPoints = defaultNbPoints;	// Reset NbPoints to 100 in case of wrong/bad value
	
	dt = (tStop - tStart)/NbPoints;
}
//----------------------------------------------------------------------
int		Sinus::Compute()const{
	float real_t;
	float tmp;
	
	Refresh_dt();
	
	tn.clear();
	sin_tn.clear();
	
	for (int t=0;t<NbPoints;t++){
		real_t = t*dt;
		tn.push_back(real_t);
		
		tmp = (Omega * real_t) + Phi0;
		tmp = sin(tmp);
		tmp *= Amplitude;
		tmp += A0;
		
		sin_tn.push_back(tmp);
	}
	
	return 0;
}
//----------------------------------------------------------------------
int	Sinus::Generate(std::string FileName)const{
	if (Compute() != 0) return -1;	// Compute problem...
	
	std::ofstream outputfile(FileName,std::ofstream::out);
	
	if (outputfile.fail()) return -2;	// File problem...
	
	if ( (tn.size() != NbPoints) || (sin_tn.size() != NbPoints) ) {		// Size incoherency
		outputfile.close();	
		return -3;	
	}
	for (unsigned int i=0 ; i<NbPoints ; i++){
		float x=tn.at(i);
		float y=sin_tn.at(i);
		std::string data_line = std::to_string(x)+"\t"+std::to_string(y)+"\n";
		//std::cout << data_line;
		outputfile << data_line;
	} 
	outputfile.close();
	
	
	return 0;
}

