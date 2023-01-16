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
#include <filesystem>

constexpr	unsigned int	defaultNbPoints = 100;	/**< Default number of points : 100	*/
constexpr	float 			defaulttStart = 0;		/**< Default start time : 0 (sec)	*/
constexpr	float 			defaulttStop = 1;		/**< Default stop time : 1 (sec)	*/

constexpr	float 			pi=3.14159265;			/**< What to say ?... */	
constexpr	float 			defaultA0 = 0;			/**< Default offset */
constexpr	float 			defaultAmplitude = 1;	/**< Default amplitude */
constexpr	float 			defaultOmega = (2*pi);	/**< Default angular frequency - makes a 1Hz Sine */
constexpr	float 			defaultPhi0 = 0;		/**< Default phase at t=0 */

constexpr	std::string_view	defaultFileName{"sinus.data"};	/**< Default File name	 */
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

/**
 *	Type ComputeParameters
 * 		(Simulation params)
 */
struct 	ComputeParameters{
		float 			tStart;	 	/**< Start time. In "time units", 0 by default.	*/
		float 			tStop;		/**< Stop time. In "time units", 1 by default. */
		unsigned int	nbPoints;	/**< Simulation step. Defined by (tStop - tStart) / nbPoints. */
}	;

/**
 *	helper Class for computing the signal
 * 
 * 	Could be unnecessary... really ?
 * 	What about :
 * 		- Single Responsability Service (SRP) ? Is the Sinus class is a "container" or an "algorithm" ? Should not be both... With this helper, the Sinus is clearly a container, the helper an algorithm.
 * 		- Open Close Principle (OCP) : is the Sinus more or less extensible with or without this class (parallel calculus...)
 * 		- Dont Repeat Yourself (DRY) : The computing class (function) could be easily reused
 *  	- Testability : How the compute function (private) could have been tested without this helper class ?  
 * 
 */
class SinusComputeHelper{
	public:
		SinusComputeHelper() = default;
		std::vector<SignalPoint> Compute(const SinusParam &SinusParameters, const ComputeParameters &SimulParameters) const noexcept;	
		~SinusComputeHelper() = default;
};

	
class Sinus{
	private:
	// Internal stuff
	mutable std::vector<SignalPoint>	tabSignal{};	/**< Vector containing the signal data (points)	*/
		
	ComputeParameters	SimulParams{defaulttStart, defaulttStop, defaultNbPoints};	/**< Simulation parameters */		
	SinusParam Parameters{defaultA0, defaultAmplitude, defaultOmega, defaultPhi0};	/**< Sinus parameters */
	
	mutable	bool	needToRecompute{true};
		
	SinusComputeHelper	helper{};
	void	compute() const noexcept {this->tabSignal = this->helper.Compute(this->Parameters, this->SimulParams);};
	
	// private accessors
	bool	getNeedToRecompute() const noexcept {return this->needToRecompute;};
	void	setNeedToRecompute(bool value) const noexcept {this->needToRecompute = value;};
	
	public:
	// SMF
	Sinus() = default ;
	Sinus(const SinusParam &SinusParameters, const ComputeParameters &SimulParameters);	// Ctor with params - has to check the params, throws exception in case of bad parameter
	virtual ~Sinus() = default;
	
	
	// Accessors
	float 	getA0()const  noexcept {return this->Parameters.A0;};
	void	setA0(float A0) noexcept {this->Parameters.A0 = A0;setNeedToRecompute(true);};
	
	float 	getAmplitude()const  noexcept {return(this->Parameters.Amplitude);};
	void	setAmplitude(float Amplitude)  noexcept {this->Parameters.Amplitude = Amplitude;setNeedToRecompute(true);};
		
	float 	getOmega()const noexcept{return(this->Parameters.Omega);};
	void	setOmega(float _Omega){if (_Omega < 0) throw std::domain_error("Omega can’t be negative.") ;this->Parameters.Omega = _Omega;setNeedToRecompute(true);};
		
	float	getPhi0() const noexcept {return this->Parameters.Phi0;};
	void	setPhi0(float _Phi0) noexcept {this->Parameters.Phi0 = std::fmod(_Phi0 , (2*pi) );setNeedToRecompute(true);};
	
	float	gettStart() const noexcept {return this->SimulParams.tStart;};
	void	settStart(float _tStart); 
	
	float 	gettStop()const  noexcept {return this->SimulParams.tStop;};
	void	settStop(float _tStop);
		
	unsigned int	getNbPoints()const  noexcept  {return this->SimulParams.nbPoints;};
	void	setNbPoints(unsigned int _nbPoints) {if (_nbPoints == 0) throw std::invalid_argument("nbPoints must be greater than 0.");this->SimulParams.nbPoints = _nbPoints;setNeedToRecompute(true);};
	
	unsigned int	generate(const std::filesystem::path FileName=defaultFileName)const;
	
};



#endif

