
#include "Sinus.hpp"

void	Sinus::settStart(float _tStart){
	if (_tStart < 0) throw std::domain_error("tStart can't be negative.");
	if (_tStart >= this->gettStop() ) throw std::overflow_error("tStart can’t be greater or equal than tStop.");
	
	this->tStart = _tStart;
}

void	Sinus::settStop(float _tStop){
	if (_tStop <= 0) throw std::domain_error("tStop can’t be negative or null.");
	if (_tStop <= this->gettStart()) throw std::underflow_error("tStop can’t be lesser than tStart.");
	this->tStop = _tStop;
}
//----------------------------------------------------------------------
/*
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
*/
//----------------------------------------------------------------------
/*
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
*/
