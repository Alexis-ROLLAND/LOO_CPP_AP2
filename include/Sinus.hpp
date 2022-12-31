#ifndef __SINUS_H__
#define	__SINUS_H__

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

constexpr	float 			pi=3.14159265;			
constexpr	unsigned int	defaultNbPoints = 100;
constexpr	float 			defaulttStart = 0;
constexpr	float 			defaulttStop = 1;

class Sinus{
	private:
	// Internal stuff
	mutable std::vector<float> tn;
	mutable std::vector<float> sin_tn;
	mutable float 	dt;
	
	// Simulation parameters
	mutable float 			tStart{defaulttStart};	 
	mutable	float 			tStop{defaulttStop};
	mutable unsigned int	NbPoints{defaultNbPoints};
			
	// Signal caractéristics
	// sin_tn(tn) = A0 + amplitude * sin(omega*tn + phi0)
	float 	A0;			// Composante continue
	float 	Amplitude;	// Amplitude
	float 	Omega;		// pulsation en rad.s-1
	float 	Phi0;		// Phase à l'origine
	
	void	Refresh_dt() const  noexcept ;
	int		Compute()const;
	
	public:
	Sinus():Sinus(defaulttStart,1,(2*pi),0,defaulttStop,defaultNbPoints){};	// Default Ctor 1Hz sinus - A=1 - No CC - then, call  the delegated Ctor
	Sinus(float A0, float Amplitude, float Omega, float Phi0, float tStop=defaulttStop, unsigned int NbPoints=defaultNbPoints); // Delegated Ctor
	virtual ~Sinus() = default;
	
	// Accessors
	void	setA0(float A0) noexcept {this->A0 = A0;};
	float 	getA0()const  noexcept {return this->A0;};
	
	void	setAmplitude(float Amplitude)  noexcept {this->Amplitude = Amplitude;};
	float 	getAmplitude()const  noexcept {return(this->Amplitude);};
	
	void 	setOmega(float Omega)  noexcept {this->Omega = Omega;};
	float 	getOmega()const  noexcept {return this->Omega;};
	
	void	setPhi0(float Phi0) noexcept ;	// Need to constraint between 0 and 2PI
	float	getPhi0()const  noexcept {return Phi0;};
		
	void	setNbPoints(int NbPoints)  noexcept {this->NbPoints = NbPoints;};
	unsigned int	getNbPoints()const  noexcept  {return this->NbPoints;};	
	
	void	settStop(float tStop)  noexcept  {this->tStop = tStop;};
	float 	gettStop()const  noexcept {return this->tStop;};
	
	float 	getdt()const  noexcept {this->Refresh_dt();return this->dt;};		// Refresh dt before return the value
	
	// Generate function
	int		Generate(std::string FileName="sinus.data")const;
		
};
#endif

