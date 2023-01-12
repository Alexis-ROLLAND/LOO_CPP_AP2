#include <iostream>

//----------------------------------------------------------------------
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN	/*! Use if doctest with its own main function*/
#include "doctest.h"
//----------------------------------------------------------------------

#include "Sinus.hpp"

TEST_CASE("testing the Sinus class : Default non const object and getters") {
	Sinus mySinus{};
	
	CHECK(mySinus.getA0() == doctest::Approx(defaultA0));
	CHECK(mySinus.getAmplitude() == doctest::Approx(defaultAmplitude));
	CHECK(mySinus.getOmega() == doctest::Approx(defaultOmega));
	CHECK(mySinus.getPhi0() == doctest::Approx(defaultPhi0));
	CHECK(mySinus.gettStart() == doctest::Approx(defaulttStart));
	CHECK(mySinus.gettStop() == doctest::Approx(defaulttStop));
	CHECK(mySinus.getNbPoints() == defaultNbPoints);	
}


TEST_CASE("testing the Sinus class : Default non const object and setters") {
	Sinus mySinus{};
	
	// Setter for A0
	float	A0 = 2.5;
	mySinus.setA0(A0);
	CHECK(mySinus.getA0() == doctest::Approx(A0));
	
	// Setter for Amplitude
	float 	Amplitude = 3.3;
	mySinus.setAmplitude(Amplitude);
	CHECK(mySinus.getAmplitude() == doctest::Approx(Amplitude));
	
	// Setter fo Omega
	float 	Omega = 4*pi;
	mySinus.setOmega(Omega);
	CHECK(mySinus.getOmega() == doctest::Approx(Omega));
	
	Omega = -Omega;		// if Omega < 0...
	CHECK_THROWS_WITH_AS(mySinus.setOmega(Omega), "Omega can’t be negative.", std::domain_error);	// ...check exception
	
	// Setter for Phi0
	float 	Phi0 = pi / 2;
	mySinus.setPhi0(Phi0);
	CHECK(mySinus.getPhi0() == doctest::Approx(Phi0));
	
	mySinus.setPhi0(Phi0 + 2*pi);	// if Phi0 > 2*pi...
	CHECK(mySinus.getPhi0() == doctest::Approx(Phi0)); // Check Phi0 is now < 2*pi
	 
	Phi0 = -pi/2;
	mySinus.setPhi0(Phi0 - 2*pi);	// if Phi0 < -2*pi...
	CHECK(mySinus.getPhi0() == doctest::Approx(Phi0));	// check Phi0 is now > -2*pi
	
	// Setter for tStart
	REQUIRE(mySinus.gettStop() == doctest::Approx(defaulttStop));	// tStop must be at is default value (1)
	float tStart = 0.5;
	mySinus.settStart(tStart);
	CHECK(mySinus.gettStart() == doctest::Approx(tStart));
	tStart = -0.5;		// if tStart is < 0...
	CHECK_THROWS_WITH_AS(mySinus.settStart(tStart),"tStart can't be negative.",std::domain_error);	// ...check exception
	tStart = mySinus.gettStop() + 1;	// if tStart > tStop... 
	CHECK_THROWS_WITH_AS(mySinus.settStart(tStart),"tStart can’t be greater or equal than tStop.",std::overflow_error); // ...check exception
	tStart = mySinus.gettStop();	// if tStart == tStop
	CHECK_THROWS_WITH_AS(mySinus.settStart(tStart),"tStart can’t be greater or equal than tStop.",std::overflow_error); // ...check exception
	
	// Setter for tStop
	tStart = 0.5;
	mySinus.settStart(tStart);
	REQUIRE(mySinus.gettStart() == doctest::Approx(tStart));	// tStart must be set at 0.5 for the test
	float 	tStop = 2;
	mySinus.settStop(tStop);
	CHECK(mySinus.gettStop() == doctest::Approx(tStop));
	tStop = -1;		// if tStop is < 0...
	CHECK_THROWS_WITH_AS(mySinus.settStop(tStop),"tStop can’t be negative or null.",std::domain_error);	// ...check exception
	tStop = 0;		// if tStop == 0...
	CHECK_THROWS_WITH_AS(mySinus.settStop(tStop),"tStop can’t be negative or null.",std::domain_error);	// ...check exception
	tStop = 0.2;	// if tStop < tStart 
	CHECK_THROWS_WITH_AS(mySinus.settStop(tStop),"tStop can’t be lesser than tStart.",std::underflow_error);	// ...check exception
	tStop = mySinus.gettStart();	// if tStop == tStart
	CHECK_THROWS_WITH_AS(mySinus.settStop(tStop),"tStop can’t be lesser than tStart.",std::underflow_error);	// ...check exception
	
	// Setter for nbPoints
	unsigned int	nbPoints = 200;
	mySinus.setNbPoints(nbPoints);
	CHECK(mySinus.getNbPoints() == nbPoints);
	nbPoints = 0;	// if nbPoints == 0 	(can't be < 0, because is unsigned)
	CHECK_THROWS_WITH_AS(mySinus.setNbPoints(nbPoints),"nbPoints must be greater than 0.",std::invalid_argument);
}

TEST_CASE("testing the Sinus class : Default const object and getters") {
	const Sinus mySinus{};
	
	CHECK(mySinus.getA0() == doctest::Approx(defaultA0));
	CHECK(mySinus.getAmplitude() == doctest::Approx(defaultAmplitude));
	CHECK(mySinus.getOmega() == doctest::Approx(defaultOmega));
	CHECK(mySinus.getPhi0() == doctest::Approx(defaultPhi0));
	CHECK(mySinus.gettStart() == doctest::Approx(defaulttStart));
	CHECK(mySinus.gettStop() == doctest::Approx(defaulttStop));
	CHECK(mySinus.getNbPoints() == defaultNbPoints);	
}



