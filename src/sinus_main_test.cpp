#include <iostream>

//----------------------------------------------------------------------
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN	/*! Use if doctest with its own main function*/
#include "doctest.h"
//----------------------------------------------------------------------

#include "Sinus.hpp"

TEST_CASE("1 - Testing the Sinus class : Default non const object and getters") {
	Sinus mySinus{};
	
	CHECK(mySinus.getA0() == doctest::Approx(defaultA0));
	CHECK(mySinus.getAmplitude() == doctest::Approx(defaultAmplitude));
	CHECK(mySinus.getOmega() == doctest::Approx(defaultOmega));
	CHECK(mySinus.getPhi0() == doctest::Approx(defaultPhi0));
	CHECK(mySinus.gettStart() == doctest::Approx(defaulttStart));
	CHECK(mySinus.gettStop() == doctest::Approx(defaulttStop));
	CHECK(mySinus.getNbPoints() == defaultNbPoints);	
}


TEST_CASE("2 - Testing the Sinus class : Default non const object and setters") {
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

TEST_CASE("3 - Testing the Sinus class : Default const object and getters") {
	const Sinus mySinus{};
	
	CHECK(mySinus.getA0() == doctest::Approx(defaultA0));
	CHECK(mySinus.getAmplitude() == doctest::Approx(defaultAmplitude));
	CHECK(mySinus.getOmega() == doctest::Approx(defaultOmega));
	CHECK(mySinus.getPhi0() == doctest::Approx(defaultPhi0));
	CHECK(mySinus.gettStart() == doctest::Approx(defaulttStart));
	CHECK(mySinus.gettStop() == doctest::Approx(defaulttStop));
	CHECK(mySinus.getNbPoints() == defaultNbPoints);	
}

TEST_CASE("4 - Testing the compute function global bahaviour (not the real algorithm) , within a compute helper class"){
	
	SinusParam	testSinusParam{defaultA0, defaultAmplitude, defaultOmega, defaultPhi0};
	ComputeParameters	testSimulParams{defaulttStart, defaulttStop, defaultNbPoints};
	std::vector<SignalPoint>	resSinus{};
	
	SinusComputeHelper	helper{};
	
	resSinus = helper.Compute(testSinusParam, testSimulParams);
		
	// Minimal tests here... Fell free to add some :) 
	CHECK(resSinus.size() == defaultNbPoints);	// is the result vector the correct size ?
	SignalPoint Point = resSinus.front();	// get first element of result vector
	CHECK( Point.tn == doctest::Approx(testSimulParams.tStart));	// is the tn matching start time ?
	
	
	const SinusComputeHelper	chelper{};
	resSinus = chelper.Compute(testSinusParam, testSimulParams);
		
	// Minimal tests here... Fell free to add some :) 
	CHECK(resSinus.size() == defaultNbPoints);	// is the result vector the correct size ?
	Point = resSinus.front();	// get first element of result vector
	CHECK( Point.tn == doctest::Approx(testSimulParams.tStart));	// is the tn matching start time ?
	
}

TEST_CASE("5 - Testing the generate method - non const objects"){
	Sinus mySinus{};
	
	std::string_view	FileName{defaultFileName};
	std::filesystem::remove(FileName);
	REQUIRE(std::filesystem::exists(FileName) == false);
	unsigned int 		expectedSize{1850};
	
	mySinus.generate();
	
	std::filesystem::file_status fs =  std::filesystem::status(FileName);
	CHECK(std::filesystem::exists(FileName));
	CHECK(fs.type() == std::filesystem::file_type::regular );	// Possible use of td::filesystem::is_regular_file instead
	CHECK(std::filesystem::file_size(FileName) == expectedSize);
	
	mySinus.setOmega(4*pi);
	mySinus.setAmplitude(2);
	FileName = "sinus2.data";
	
	mySinus.generate(FileName);
	
	fs =  std::filesystem::status(FileName);
	CHECK(std::filesystem::exists(FileName));
	CHECK(fs.type() == std::filesystem::file_type::regular );	// Possible use of td::filesystem::is_regular_file instead
	CHECK(std::filesystem::file_size(FileName) == expectedSize);
	
}

TEST_CASE("6 - Testing the parametrized Ctor"){
	float	testA0{-0.5};
	float 	testAmplitude{3.3};
	float 	testOmega{6*pi};
	float 	testPhi0{pi};
	
	float 	testtStart{0.5};
	float 	testtStop{1.5};
	unsigned  int	testNbPoints{200};
	
	SinusParam	testSinusParam{testA0, testAmplitude, testOmega, testPhi0};
	ComputeParameters	testSimulParams{testtStart, testtStop, testNbPoints};
	
	SUBCASE("Good values - non const object"){
		Sinus mySinus(testSinusParam, testSimulParams);
		
		CHECK(mySinus.getA0() == doctest::Approx(testA0));
		CHECK(mySinus.getAmplitude() == doctest::Approx(testAmplitude));
		CHECK(mySinus.getOmega() == doctest::Approx(testOmega));
		CHECK(mySinus.getPhi0() == doctest::Approx(testPhi0));
		CHECK(mySinus.gettStart() == doctest::Approx(testtStart));
		CHECK(mySinus.gettStop() == doctest::Approx(testtStop));
		CHECK(mySinus.getNbPoints() == testNbPoints);	
	}
	
	SUBCASE("Good values - const object"){
		const Sinus mySinus(testSinusParam, testSimulParams);
		
		CHECK(mySinus.getA0() == doctest::Approx(testA0));
		CHECK(mySinus.getAmplitude() == doctest::Approx(testAmplitude));
		CHECK(mySinus.getOmega() == doctest::Approx(testOmega));
		CHECK(mySinus.getPhi0() == doctest::Approx(testPhi0));
		CHECK(mySinus.gettStart() == doctest::Approx(testtStart));
		CHECK(mySinus.gettStop() == doctest::Approx(testtStop));
		CHECK(mySinus.getNbPoints() == testNbPoints);	
	}
	
	SUBCASE("Bad value for Omega - const and non const object"){
		testSinusParam.Omega = -testOmega;
		CHECK_THROWS_WITH_AS(Sinus mySinus(testSinusParam, testSimulParams), "Omega can’t be negative.", std::domain_error);	// ...check exception
		CHECK_THROWS_WITH_AS(const Sinus mySinus(testSinusParam, testSimulParams), "Omega can’t be negative.", std::domain_error);	// ...check exception
	}
	
	SUBCASE("Out of bounds value for Phi0 - const and non const object"){
		testSinusParam.Phi0 = testPhi0 + 3*pi;
		CHECK_THROWS_WITH_AS(Sinus mySinus(testSinusParam, testSimulParams), "Initial phi0 can’t be outside bounds.", std::domain_error);	// ...check exception
		CHECK_THROWS_WITH_AS(const Sinus mySinus(testSinusParam, testSimulParams), "Initial phi0 can’t be outside bounds.", std::domain_error);	// ...check exception
	}
	
	SUBCASE("Bad values for tStart - const and non const object"){
		testSimulParams.tStart = -testtStart;
		CHECK_THROWS_WITH_AS(Sinus mySinus(testSinusParam, testSimulParams), "tStart can't be negative.", std::domain_error);	// ...check exception
		CHECK_THROWS_WITH_AS(const Sinus mySinus(testSinusParam, testSimulParams), "tStart can't be negative.", std::domain_error);	// ...check exception
		
		testSimulParams.tStart = testtStop + testtStart;
		CHECK_THROWS_WITH_AS(Sinus mySinus(testSinusParam, testSimulParams), "tStart can’t be greater or equal than tStop.",std::overflow_error);	// ...check exception
		CHECK_THROWS_WITH_AS(const Sinus mySinus(testSinusParam, testSimulParams), "tStart can’t be greater or equal than tStop.",std::overflow_error);	// ...check exception
		
	}
	
	SUBCASE("Bad values for tStop - const and non const object"){
		testSimulParams.tStop = -testtStop;
		CHECK_THROWS_WITH_AS(Sinus mySinus(testSinusParam, testSimulParams), "tStop can’t be negative or null.", std::domain_error);	// ...check exception
		CHECK_THROWS_WITH_AS(const Sinus mySinus(testSinusParam, testSimulParams), "tStop can’t be negative or null.", std::domain_error);	// ...check exception
		
		testSimulParams.tStop = 0;
		CHECK_THROWS_WITH_AS(Sinus mySinus(testSinusParam, testSimulParams), "tStop can’t be negative or null.", std::domain_error);	// ...check exception
		CHECK_THROWS_WITH_AS(const Sinus mySinus(testSinusParam, testSimulParams), "tStop can’t be negative or null.", std::domain_error);	// ...check exception
		
		testSimulParams.tStart = testtStop;	 
		testSimulParams.tStop = testtStart;
		CHECK_THROWS_WITH_AS(Sinus mySinus(testSinusParam, testSimulParams), "tStart can’t be greater or equal than tStop.",std::overflow_error);	// ...check exception
		CHECK_THROWS_WITH_AS(const Sinus mySinus(testSinusParam, testSimulParams), "tStart can’t be greater or equal than tStop.",std::overflow_error);	// ...check exception
	}
	
	SUBCASE("Bad value nbPoints - const and non const object"){
		testSimulParams.nbPoints = 0;
		CHECK_THROWS_WITH_AS(Sinus mySinus(testSinusParam, testSimulParams), "nbPoints must be greater than 0.",std::invalid_argument);	// ...check exception
		CHECK_THROWS_WITH_AS(const Sinus mySinus(testSinusParam, testSimulParams), "nbPoints must be greater than 0.",std::invalid_argument);	// ...check exception
	}
	
	
}



