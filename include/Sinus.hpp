/**
 *	@file	Sinus.hpp
 * 	@brief 	Sinus class (standalone version) header file
 * 	@author	Alexis ROLLAND
 * 	@date	2023-01
 * 
 */
#ifndef __SINUS_H__
#define	__SINUS_H__

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

constexpr	unsigned int	defaultNbPoints = 100;	/**< Default number of points : 100	*/
constexpr	float 			defaulttStart = 0;		/**< Default start time : 0 (sec)	*/
constexpr	float 			defaulttStop = 1;		/**< Default stop time : 1 (sec)	*/

constexpr	float 			pi=3.14159265;			/**< What to say ?... */	
constexpr	float 			defaultA0 = 0;			/**< Default offset */
constexpr	float 			defaultAmplitude = 1;	/**< Default amplitude */
constexpr	float 			defaultOmega = (2*pi);	/**< Default angular frequency - makes a 1Hz Sine */
constexpr	float 			defaultPhi0 = 0;		/**< Default phase at t=0 */

/**
 *	Type SinusParam : Signal caractéristics
 * 
 *    	sin_tn(tn) = A0 + amplitude * sin(omega*tn + phi0)
 */
struct	SinusParam{
		// 
		float 	A0;							/**<  Offset			*/
		float 	Amplitude;					/**<  Amplitude		*/
		float 	Omega;						/**<  Angular frequency  (rad.s-1) */
		float 	Phi0;						/**<  Phase at t=0		*/
	};

/**
 *	Type SignalPoint 
 */
struct	SignalPoint{
		float	tn;				/**< t (X) coordinates of the point		*/
		float 	sig_tn;			/**< s(t) (Y) coordinates of the point 	*/
	};
	
class Sinus{
	private:
	// Internal stuff
	mutable std::vector<SignalPoint>	tabSignal{};	/**< Vector containing the signal data (points)	*/
	mutable float 	dt{0};								/**< "simulation" step							*/
	
	// Simulation parameters
	float 			tStart{defaulttStart};	 	/**< Start time. In "time units", 0 by default.	*/
	float 			tStop{defaulttStop};		/**< Stop time. In "time units", 1 by default. */
	unsigned int	nbPoints{defaultNbPoints};	/**< Simulation step. Defined by (tStop - tStart) / nbPoints. */
			
	SinusParam Parameters{defaultA0,defaultAmplitude,defaultOmega,defaultPhi0};	/**< Sinus parameters */
	
	//void	Compute()const;
	
	public:
	Sinus() = default ;
	virtual ~Sinus() = default;
	
	// Accessors
	float 	getA0()const  noexcept {return this->Parameters.A0;};
	void	setA0(float A0) noexcept {this->Parameters.A0 = A0;};
	
	float 	getAmplitude()const  noexcept {return(this->Parameters.Amplitude);};
	void	setAmplitude(float Amplitude)  noexcept {this->Parameters.Amplitude = Amplitude;};
		
	float 	getOmega()const noexcept{return(this->Parameters.Omega);};
	void	setOmega(float _Omega){if (_Omega < 0) throw std::domain_error("Omega can’t be negative.") ;this->Parameters.Omega = _Omega;};
		
	float	getPhi0() const noexcept {return this->Parameters.Phi0;};
	void	setPhi0(float _Phi0) noexcept {this->Parameters.Phi0 = std::fmod(_Phi0 , (2*pi) );};
	
	float	gettStart() const noexcept {return this->tStart;};
	void	settStart(float _tStart); 
	
	float 	gettStop()const  noexcept {return this->tStop;};
	void	settStop(float _tStop);
		
	unsigned int	getNbPoints()const  noexcept  {return this->nbPoints;};
	void	setNbPoints(unsigned int _nbPoints) {if (_nbPoints == 0) throw std::invalid_argument("nbPoints must be greater than 0.");this->nbPoints = _nbPoints;};
	
	/*
	void	setNbPoints(int NbPoints)  noexcept {this->NbPoints = NbPoints;};
		
	*/
	
	/*
	void	settStop(float tStop)  noexcept  {this->tStop = tStop;};
	
	*/
	
	/*
	// Generate function
	int		Generate(std::string FileName="sinus.data")const;
	*/
};
#endif

