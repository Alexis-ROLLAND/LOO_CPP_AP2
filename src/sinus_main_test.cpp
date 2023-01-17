#include <iostream>

//----------------------------------------------------------------------
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN	/*! Use if doctest with its own main function*/
#include "doctest.h"
//----------------------------------------------------------------------

#define	TEST0_PRJ_ARCHITECTURE							/**< Project architecture only - may be disabled once passed	*/

#define	TEST1_ACCESSORS_NON_CONST_OBJECT

#define	TEST2_GLOBAL
#define	TEST21_SETTER_A0_AND_AMPLITUDE
#define	TEST22_SETTER_OMEGA
#define	TEST23_SETTER_PHI0
#define	TEST24_SETTER_TSTART
#define	TEST25_SETTER_TSTOP
#define	TEST26_SETTER_NBPOINTS

#define	TEST3_DEFAULT_CONST_OBJECT

#define	TEST4_GLOBAL
#define	TEST41_HELPER_COMPUTE_NON_CONST
#define	TEST42_HELPER_COMPUTE_CONST

#define	TEST5_GLOBAL
#define	TEST51_GENERATE_NON_CONST_DEFAULT_FILENAME
#define	TEST52_GENERATE_NON_CONST_STD_FILENAME

#define	TEST6_GLOBAL
#define	TEST61_PARAM_CTOR_GOOD_VALUES_NON_CONST_OBJECT
#define	TEST62_PARAM_CTOR_GOOD_VALUES_CONST_OBJECT
#define	TEST63_PARAM_CTOR_BAD_OMEGA
#define	TEST64_PARAM_CTOR_BAD_PHI0
#define	TEST65_PARAM_CTOR_BAD_TSTART
#define	TEST66_PARAM_CTOR_BAD_TSTOP
#define	TEST67_PARAM_CTOR_BAD_NBPOINTS


#include "Sinus.hpp"

#ifdef	TEST0_PRJ_ARCHITECTURE
TEST_CASE("0 - Project architecture"){
	std::cout << "Project Architecture is OK\n";
}
#endif	/*	TEST0_PRJ_ARCHITECTURE */

#ifdef	TEST1_ACCESSORS_NON_CONST_OBJECT
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
#endif	/* EST1_ACCESSORS_NON_CONST_OBJECT	*/

#ifdef	TEST2_GLOBAL
TEST_CASE("2 - Testing the Sinus class : Default non const object and setters") {
	Sinus mySinus{};
	
	#ifdef	TEST21_SETTER_A0_AND_AMPLITUDE
	// Setter for A0
	float	A0 = 2.5;
	mySinus.setA0(A0);
	CHECK(mySinus.getA0() == doctest::Approx(A0));
	
	// Setter for Amplitude
	float 	Amplitude = 3.3;
	mySinus.setAmplitude(Amplitude);
	CHECK(mySinus.getAmplitude() == doctest::Approx(Amplitude));
	#endif	/* TEST21_SETTER_A0_AND_AMPLITUDE	*/
	
	#ifdef	TEST22_SETTER_OMEGA
	// Setter fo Omega
	float 	Omega = 4*pi;
	mySinus.setOmega(Omega);
	CHECK(mySinus.getOmega() == doctest::Approx(Omega));
	
	Omega = -Omega;		// if Omega < 0...
	CHECK_THROWS_WITH_AS(mySinus.setOmega(Omega), "Omega can’t be negative.", std::domain_error);	// ...check exception
	#endif	/* TEST22_SETTER_OMEGA */
	
	#ifdef	TEST23_SETTER_PHI0
	// Setter for Phi0
	float 	Phi0 = pi / 2;
	mySinus.setPhi0(Phi0);
	CHECK(mySinus.getPhi0() == doctest::Approx(Phi0));
	
	mySinus.setPhi0(Phi0 + 2*pi);	// if Phi0 > 2*pi...
	CHECK(mySinus.getPhi0() == doctest::Approx(Phi0)); // Check Phi0 is now < 2*pi
	 
	Phi0 = -pi/2;
	mySinus.setPhi0(Phi0 - 2*pi);	// if Phi0 < -2*pi...
	CHECK(mySinus.getPhi0() == doctest::Approx(Phi0));	// check Phi0 is now > -2*pi
	#endif	/* TEST23_SETTER_PHI0 */
	
	#ifdef	TEST24_SETTER_TSTART
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
	#endif	/* TEST24_SETTER_TSTART */
	
	#ifdef	TEST25_SETTER_TSTOP
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
	#endif	/* TEST25_SETTER_TSTOP */
	
	#ifdef	TEST26_SETTER_NBPOINTS
	// Setter for nbPoints
	unsigned int	nbPoints = 200;
	mySinus.setNbPoints(nbPoints);
	CHECK(mySinus.getNbPoints() == nbPoints);
	nbPoints = 0;	// if nbPoints == 0 	(can't be < 0, because is unsigned)
	CHECK_THROWS_WITH_AS(mySinus.setNbPoints(nbPoints),"nbPoints must be greater than 0.",std::invalid_argument);
	#endif	/* TEST26_SETTER_NBPOINTS */
}
#endif	/* TEST2_GLOBAL	*/

#ifdef	TEST3_DEFAULT_CONST_OBJECT
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
#endif	/* TEST3_DEFAULT_CONST_OBJECT 	*/

#ifdef	TEST4_GLOBAL
TEST_CASE("4 - Testing the compute function global bahaviour (not the real algorithm) , within a compute helper class"){
	
	SinusParam	testSinusParam{defaultA0, defaultAmplitude, defaultOmega, defaultPhi0};
	ComputeParameters	testSimulParams{defaulttStart, defaulttStop, defaultNbPoints};
	std::vector<SignalPoint>	resSinus{};
	
	#ifdef	TEST41_HELPER_COMPUTE_NON_CONST
	SinusComputeHelper	helper{};
	
	resSinus = helper.Compute(testSinusParam, testSimulParams);
		
	// Minimal tests here... Fell free to add some :) 
	CHECK(resSinus.size() == defaultNbPoints);	// is the result vector the correct size ?
	SignalPoint Point = resSinus.front();	// get first element of result vector
	CHECK( Point.tn == doctest::Approx(testSimulParams.tStart));	// is the tn matching start time ?
	#endif	/* TEST41_HELPER_COMPUTE_NON_CONST */
	
	#ifdef	TEST42_HELPER_COMPUTE_CONST
	const SinusComputeHelper	chelper{};
	resSinus = chelper.Compute(testSinusParam, testSimulParams);
		
	// Minimal tests here... Fell free to add some :) 
	CHECK(resSinus.size() == defaultNbPoints);	// is the result vector the correct size ?
	Point = resSinus.front();	// get first element of result vector
	CHECK( Point.tn == doctest::Approx(testSimulParams.tStart));	// is the tn matching start time ?
	#endif	/* TEST42_HELPER_COMPUTE_CONST	*/
}
#endif	/* TEST4_GLOBAL	*/

#ifdef	TEST5_GLOBAL
TEST_CASE("5 - Testing the generate method - non const objects"){
	Sinus mySinus{};
	
	std::string_view	FileName{defaultFileName};
	std::filesystem::remove(FileName);
	REQUIRE(std::filesystem::exists(FileName) == false);
	unsigned int 		expectedSize{1850};
	
	#ifdef	TEST51_GENERATE_NON_CONST_DEFAULT_FILENAME
	mySinus.generate();
	
	std::filesystem::file_status fs =  std::filesystem::status(FileName);
	CHECK(std::filesystem::exists(FileName));
	CHECK(fs.type() == std::filesystem::file_type::regular );	// Possible use of td::filesystem::is_regular_file instead
	CHECK(std::filesystem::file_size(FileName) == expectedSize);
	#endif	/* TEST51_GENERATE_NON_CONST_DEFAULT_FILENAME	*/
	
	#ifdef	TEST52_GENERATE_NON_CONST_STD_FILENAME
	mySinus.setOmega(4*pi);
	mySinus.setAmplitude(2);
	FileName = "sinus2.data";
	
	mySinus.generate(FileName);
	
	fs =  std::filesystem::status(FileName);
	CHECK(std::filesystem::exists(FileName));
	CHECK(fs.type() == std::filesystem::file_type::regular );	// Possible use of td::filesystem::is_regular_file instead
	CHECK(std::filesystem::file_size(FileName) == expectedSize);
	#endif	/* TEST52_GENERATE_NON_CONST_STD_FILENAME */
}
#endif	/* TEST5_GLOBAL	*/

#ifdef 	TEST6_GLOBAL
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
	
	
	#ifdef 	TEST61_PARAM_CTOR_GOOD_VALUES_NON_CONST_OBJECT
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
	#endif	/* TEST61_PARAM_CTOR_GOOD_VALUES_NON_CONST_OBJECT */
	
	#ifdef	TEST62_PARAM_CTOR_GOOD_VALUES_CONST_OBJECT
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
	#endif	/* TEST62_PARAM_CTOR_GOOD_VALUES_CONST_OBJECT */
	
	#ifdef	TEST63_PARAM_CTOR_BAD_OMEGA
	SUBCASE("Bad value for Omega - const and non const object"){
		testSinusParam.Omega = -testOmega;
		CHECK_THROWS_WITH_AS(Sinus mySinus(testSinusParam, testSimulParams), "Omega can’t be negative.", std::domain_error);	// ...check exception
		CHECK_THROWS_WITH_AS(const Sinus mySinus(testSinusParam, testSimulParams), "Omega can’t be negative.", std::domain_error);	// ...check exception
	}
	#endif	/* TEST63_PARAM_CTOR_BAD_OMEGA */
	
	#ifdef	TEST64_PARAM_CTOR_BAD_PHI0
	SUBCASE("Out of bounds value for Phi0 - const and non const object"){
		testSinusParam.Phi0 = testPhi0 + 3*pi;
		CHECK_THROWS_WITH_AS(Sinus mySinus(testSinusParam, testSimulParams), "Initial phi0 can’t be outside bounds.", std::domain_error);	// ...check exception
		CHECK_THROWS_WITH_AS(const Sinus mySinus(testSinusParam, testSimulParams), "Initial phi0 can’t be outside bounds.", std::domain_error);	// ...check exception
	}
	#endif	/* TEST64_PARAM_CTOR_BAD_PHI0 */
	
	#ifdef	TEST65_PARAM_CTOR_BAD_TSTART
	SUBCASE("Bad values for tStart - const and non const object"){
		testSimulParams.tStart = -testtStart;
		CHECK_THROWS_WITH_AS(Sinus mySinus(testSinusParam, testSimulParams), "tStart can't be negative.", std::domain_error);	// ...check exception
		CHECK_THROWS_WITH_AS(const Sinus mySinus(testSinusParam, testSimulParams), "tStart can't be negative.", std::domain_error);	// ...check exception
		
		testSimulParams.tStart = testtStop + testtStart;
		CHECK_THROWS_WITH_AS(Sinus mySinus(testSinusParam, testSimulParams), "tStart can’t be greater or equal than tStop.",std::overflow_error);	// ...check exception
		CHECK_THROWS_WITH_AS(const Sinus mySinus(testSinusParam, testSimulParams), "tStart can’t be greater or equal than tStop.",std::overflow_error);	// ...check exception
	}
	#endif	/* TEST65_PARAM_CTOR_BAD_TSTART */
	
	#ifdef	TEST66_PARAM_CTOR_BAD_TSTOP
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
	#endif	/* TEST66_PARAM_CTOR_BAD_TSTOP */
	
	#ifdef	TEST67_PARAM_CTOR_BAD_NBPOINTS
	SUBCASE("Bad value nbPoints - const and non const object"){
		testSimulParams.nbPoints = 0;
		CHECK_THROWS_WITH_AS(Sinus mySinus(testSinusParam, testSimulParams), "nbPoints must be greater than 0.",std::invalid_argument);	// ...check exception
		CHECK_THROWS_WITH_AS(const Sinus mySinus(testSinusParam, testSimulParams), "nbPoints must be greater than 0.",std::invalid_argument);	// ...check exception
	}
	#endif	/* TEST67_PARAM_CTOR_BAD_NBPOINTS */
	
}
#endif	/* TEST6_GLOBAL	*/


