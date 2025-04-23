#include "classesInclude.h";

//test if cloud platforms move as time passes
void TEST_CLOUD_MOVEMENT(void) {
	CloudMedium testCloud(sf::Vector2f(735.f, 670.f), sf::Vector2f(-105.f, 670.f), MEDIUM, HORIZONTAL);

	sf::Vector2f cloudPosition = testCloud.getPosition();

	// use 1 second as delta time (realistic for pixels/second velocity)
	float dt = 1.0f;
	testCloud.update(dt);

	// save updated position for comparison
	sf::Vector2f cloudPositionAfterDT = testCloud.getPosition();

	// check for movement, position after 1 sec time should not equal initial position
	if (cloudPosition != cloudPositionAfterDT) {
		std::cout << "TEST CLOUD MOVEMENT TEST PASSED, CLOUD POSITION MODIFIED AS TIME PASSES";
	}
	else {
		std::cout << "TEST CLOUD MOVEMENT TEST FAILED";
	}

	std::cout << std::endl;
}

//test if meteor obstacles move as time passes
void TEST_METEOR_MOVEMENT(void) {
	float dt = 1.0f;  // 1 second for clear movement
	sf::Vector2f startPosition = { 0.f, 0.f };
	meteorHazard testHazard(startPosition);

	sf::Vector2f initialPosition = testHazard.getPosition();

	testHazard.update(dt);

	sf::Vector2f meteorPositionAfterDT = testHazard.getPosition();
	
	//compare initial position to the position after time has passed
	if (initialPosition != meteorPositionAfterDT) {
		std::cout << "TEST METEOR MOVEMENT TEST PASSED, METEOR POSITION MODIFIED AS TIME PASSES";
	}
	else {
		std::cout << "TEST METEOR MOVEMENT TEST FAILED";
	}
	std::cout << std::endl;
}

//Test if reset function works, (reset used to insure clouds don't populate infintely and there is a constant stream of platforms)
void TEST_CLOUD_RESET_POSITION(void) {
	//create test cloud
	CloudMedium testCloud(sf::Vector2f(735.f, 670.f), sf::Vector2f(-105.f, 670.f), MEDIUM, HORIZONTAL);
	sf::Vector2f initialPosition = testCloud.getPosition();
	
	testCloud.update(1.0f);  // simulate 1 second elapsing
	sf::Vector2f movedPosition = testCloud.getPosition();
	
	testCloud.resetPos();
	sf::Vector2f resetPosition = testCloud.getPosition();
	

//compare reset location to moved location (as time has passed)
//compare reset location to initial location
	if (resetPosition != movedPosition && (resetPosition == initialPosition)) {
		std::cout << "CLOUD RESET POSITION FUNCTION TEST PASSED, RESET FUNCTION SETS CLOUD TO INITIAL POSITION";
	}
	else {
		std::cout << "CLOUD RESET POSITION FUNCTION TEST FAILED";
	}
	std::cout << std::endl;
}

//test random of planet generation
void TEST_PLANET_RANDOMIZATION(void) {
	goal g1, g2; //two test planets, should not be spawned in the same location (if rand works as intended)

	if (g1.getCollisionShape().getPosition() != g2.getCollisionShape().getPosition()) {
		std::cout << "PLANET/GOAL RANDOMIZATION SUCCESSFUL";
	}
	else { //if planets not spawned in same region/spawned in random region 
		std::cout << "PLANET/GOAL RANDOMIZATION FAILED";
	}

	std::cout << std::endl;

}


//test if star direction settings work (stars can move in right or left diagonal)
void TEST_STAR_HAZARD_DIRECTIONALITY(void) {
	sf::Vector2f starPosition{ 0,0 }; //star position doesn't matter in test
	starHazard testStar1(starPosition, LEFT), testStar2(starPosition, RIGHT);

	//if directionality settings work as intended, velocities should be not equal (or negatives of eachother)
	if (testStar1.getVelocityX() != testStar2.getVelocityX()) { //left direction star has negative x velocity, positive in right
		std::cout << "TEST_STAR_HAZARD_DIRECTIONALITY TEST PASSED";
	}
	if (testStar1.getVelocityX() == testStar2.getVelocityY()) {
		std::cout << "TEST_STAR_HAZARD_DIRECTIONALITY TEST PASSED";
	}
	std::cout << std::endl;
}
