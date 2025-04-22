#include "classesInclude.h";

//test random of planet generation
void TEST_PLANET_RANDOMIZATION(void) {
	goal g1, g2;

	if (g1.getCollisionShape().getPosition() != g2.getCollisionShape().getPosition()) {
		std::cout << "PLANET/GOAL RANDOMIZATION SUCCESSFUL";
	}
	else { //if planets not spawned in same region/spawned in random region 
		std::cout << "PLANET/GOAL RANDOMIZATION FAILED";
	}

	std::cout << std::endl;

}

void TEST_STAR_HAZARD_DIRECTIONALITY(void) {
	sf::Vector2f starPosition{ 0,0 }; //star position doesn't matter in test
	starHazard testStar1(starPosition, LEFT), testStar2(starPosition, RIGHT);

	if (testStar1.getVelocityX() != testStar2.getVelocityX()) { //left direction star has negative x velocity, positive in right
		std::cout << "TEST_STAR_HAZARD_DIRECTIONALITY TEST PASSED";
	}
	if (testStar1.getVelocityX() == testStar2.getVelocityY()) {
		std::cout << "TEST_STAR_HAZARD_DIRECTIONALITY TEST PASSED";
	}
	std::cout << std::endl;
}

void TEST_CLOUD_MOVEMENT(void) {
	CloudMedium testCloud(sf::Vector2f(735.f, 670.f), sf::Vector2f(-105.f, 670.f), MEDIUM, HORIZONTAL);
	sf::Vector2f cloudPosition = testCloud.getPosition();
	
	
	testCloud.update(10); //10 is dt (or movement of cloud as time elapses)
	sf::Vector2f cloudPositionAfterDT = testCloud.getPosition();

	if (cloudPosition != cloudPositionAfterDT) {
		std::cout << "TEST CLOUD MOVEMENT TEST PASSED, CLOUD POSITION MODIFIED AS TIME PASSES";
	}
	else {
		std::cout << "TEST CLOUD MOVEMENT TEST FAILED";
	}
	std::cout << std::endl;
}

void TEST_METEOR_MOVEMENT(void) {
	float dT;
	dT = 50;
	sf::Vector2f startPosition = { 0,0 };
	meteorHazard testHazard(startPosition);
	
	sf::Vector2f initialPosition = testHazard.getPosition();

	testHazard.update(50);
	sf::Vector2f meteorPositionAfterDT = testHazard.getPosition();

	if (initialPosition != meteorPositionAfterDT) {
		std::cout << "TEST METEOR MOVEMENT TEST PASSED, METEOR POSITION MODIFIED AS TIME PASSES";
	}
	else {
		std::cout << "TEST METEOR MOVEMENT TEST FAILED";
	}
	std::cout << std::endl;
}

void TEST_CLOUD_RESET_POSITION(void) {
	sf::Vector2f initialPosition, updatedPosition;
	CloudMedium testCloud(sf::Vector2f(735.f, 670.f), sf::Vector2f(-105.f, 670.f), MEDIUM, HORIZONTAL);
	initialPosition = testCloud.getPosition();

	testCloud.update(50);
	updatedPosition = testCloud.getPosition();

	testCloud.resetPos();

	if (testCloud.getPosition() != updatedPosition) {
		std::cout << "CLOUD RESET POSITION FUNCTION TEST PASSED, RESET FUNCTION SETS CLOUD TO INITIAL POSITION";
	}
	else{
		std::cout << "CLOUD RESET POSITION FUNCTION TEST FAILED";
	}
	std::cout << std::endl;
}