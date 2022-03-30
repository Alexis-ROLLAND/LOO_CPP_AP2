#ifndef __SINUS_H__
#define	__SINUS_H__

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

constexpr	float 	pi=3.14159265;
constexpr	unsigned int	defaultNbPoints = 100;
constexpr	float 	defaulttStop = 1;

class Sinus{
	private:
	// Internal stuff
	mutable std::vector<float> tn;
	mutable std::vector<float> sin_tn;
	mutable float 	dt;
	
	// Simulation parameters
	const float 	tStart = 0;	 
	mutable	float 			tStop;
	mutable unsigned int	NbPoints;
	
		
	// Signal caractéristics
	// sin_tn(tn) = A0 + amplitude * sin(omega*tn + phi0)
	float 	A0;		// Composante continue
	float 	Amplitude;	// Amplitude
	float 	Omega;	// pulsation en rad.s-1
	float 	Phi0;	// Phase à l'origine
	
	void	Refresh_dt()const;
	int		Compute()const;
	
	public:
	Sinus():Sinus(0,1,(2*pi),0,defaulttStop,defaultNbPoints){};	// Default Ctor 1Hz sinus - A=1 - No CC using the delegated Ctor
	Sinus(float A0, float Amplitude, float Omega, float Phi0, float tStop=defaulttStop, unsigned int NbPoints=defaultNbPoints); // Delegated Ctor
	virtual ~Sinus(){};
	
	// Accessors
	void	setA0(float A0){this->A0 = A0;};
	float 	getA0()const{return this->A0;};
	
	void	setAmplitude(float Amplitude){this->Amplitude = Amplitude;};
	float 	getAmplitude()const{return(this->Amplitude);};
	
	void 	setOmega(float Omega){this->Omega = Omega;};
	float 	getOmega()const{return this->Omega;};
	
	void	setPhi0(float Phi0);	// Need to constraint between 0 and 2PI
	float	getPhi0()const{return Phi0;};
		
	void	setNbPoints(int NbPoints){this->NbPoints = NbPoints;};
	unsigned int	getNbPoints()const{return this->NbPoints;};	
	
	void	settStop(float tStop){this->tStop = tStop;};
	float 	gettStop()const{return this->tStop;};
	
	float 	getdt()const{this->Refresh_dt();return this->dt;};		// Refresh dt before return the value
	
	// Generate function
	int		Generate(std::string FileName="sinus.data")const;
		
		
		
		
};
#endif

