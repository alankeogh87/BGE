#include "AnimatModel.h"
#include "PhysicsController.h"
#include "Sphere.h"
#include "PhysicsCamera.h"
#include "Box.h"
#include "Cylinder.h"
#include "Steerable3DController.h"
#include "Ground.h"
#include "Content.h"
#include <btBulletDynamicsCommon.h>
#include <gtc/quaternion.hpp>
#include <gtx/quaternion.hpp>
#include <gtx/euler_angles.hpp>
#include <gtx/norm.hpp>
#include "VectorDrawer.h"
#include "Utils.h"

using namespace BGE;

AnimatModel::AnimatModel(void)
{
}


AnimatModel::~AnimatModel(void)
{
}

bool AnimatModel::Initialise()
{
	physicsFactory->CreateGroundPhysics();
	physicsFactory->CreateCameraPhysics();

	shared_ptr<GameComponent> ground = make_shared<Ground>();
	Attach(ground);

	//setGravity(glm::vec3(0, -9, 0));
	elapsed = 0;

	Model();

	if (!Game::Initialise())
	{
		return false;
	}

	return true;
}

void BGE::AnimatModel::Update()
{
	Game::Update();
}

void BGE::AnimatModel::Cleanup()
{
	Game::Cleanup();
}

void BGE::AnimatModel::Model()
{
	//Right Leg
	glm::quat quatLowerRightLeg = glm::angleAxis(30.0f, glm::vec3(1, 0, 0));
	glm::quat quatUpperRightLeg = glm::angleAxis(-60.0f, glm::vec3(1, 0, 0));

	shared_ptr<PhysicsController> lowerRightLeg = physicsFactory->CreateBox(2, 2, 15, glm::vec3(0, 11, 0), quatLowerRightLeg);
	shared_ptr<PhysicsController> upperRightLeg = physicsFactory->CreateBox(2, 2, 8, glm::vec3(0, 17, 0), quatUpperRightLeg);
	lowerRightLeg->transform->diffuse = glm::vec3(1, 0, 0);
	upperRightLeg->transform->diffuse = glm::vec3(0, 0, 0);

	//Left Leg
	glm::quat quatLowerLeftLeg = glm::angleAxis(30.0f, glm::vec3(0, 1, 0));
	glm::quat quatUpperLeftLeg = glm::angleAxis(-60.0f, glm::vec3(0, 1, 0));

	shared_ptr<PhysicsController> lowerLeftLeg = physicsFactory->CreateBox(2, 2, 15, glm::vec3(8, 11, 0), quatLowerRightLeg);
	shared_ptr<PhysicsController> upperLeftLeg = physicsFactory->CreateBox(2, 2, 8, glm::vec3(8, 17, 0), quatUpperRightLeg);
	lowerLeftLeg->transform->diffuse = glm::vec3(1, 0, 0);
	upperLeftLeg->transform->diffuse = glm::vec3(0, 0, 0);

	//Hip
	shared_ptr<PhysicsController> Hip = physicsFactory->CreateCylinder(1.5f, 5, glm::vec3(4, 19, 1), glm::angleAxis(90.0f, glm::vec3(0, 0, 1)));
	Hip->transform->diffuse = glm::vec3(1, 0, 0);

	//Torso
	shared_ptr<PhysicsController> division = physicsFactory->CreateBox(1, 3, 10, glm::vec3(4, 22, -1), glm::angleAxis(90.0f, glm::vec3(0, 0, 1)));
	division->transform->diffuse = glm::vec3(0, 0, 0);

	shared_ptr<PhysicsController> backTorso = physicsFactory->CreateBox(4, 10, 10, glm::vec3(4, 25, -4), glm::angleAxis(90.0f, glm::vec3(0, 0, 1)));
	backTorso->transform->diffuse = glm::vec3(0, 0, 0);
	shared_ptr<PhysicsController> frontTorso = physicsFactory->CreateCylinder(2, 8, glm::vec3(4, 25, 3), glm::angleAxis(90.0f, glm::vec3(0, 0, 1)));
	frontTorso->transform->diffuse = glm::vec3(1, 0, 0);

	//Right Arm
	shared_ptr<PhysicsController> upperRightArm = physicsFactory->CreateBox(1, 3, 1, glm::vec3(-3, 25, -4), glm::angleAxis(90.0f, glm::vec3(0, 0, 1)));
	shared_ptr<PhysicsController> lowerRightArm = physicsFactory->CreateCylinder(1, 5, glm::vec3(-4, 25, 0), glm::angleAxis(90.0f, glm::vec3(1, 0, 0)));
	upperRightArm->transform->diffuse = glm::vec3(1, 0, 0);
	lowerRightArm->transform->diffuse = glm::vec3(0, 0, 0);

	//Left Arm
	shared_ptr<PhysicsController> upperLeftArm = physicsFactory->CreateBox(1, 3, 1, glm::vec3(11, 25, -4), glm::angleAxis(90.0f, glm::vec3(0, 0, 1)));
	shared_ptr<PhysicsController> lowerLeftArm = physicsFactory->CreateCylinder(1, 5, glm::vec3(12, 25, 0), glm::angleAxis(90.0f, glm::vec3(1, 0, 0)));
	upperLeftArm->transform->diffuse = glm::vec3(1, 0, 0);
	lowerLeftArm->transform->diffuse = glm::vec3(0, 0, 0);
}