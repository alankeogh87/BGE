#include "Assignment1.h"
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

Assignment1::Assignment1(void)
{
}


Assignment1::~Assignment1(void)
{
}

bool Assignment1::Initialise()
{
	physicsFactory->CreateGroundPhysics();
	physicsFactory->CreateCameraPhysics();

	shared_ptr<GameComponent> ground = make_shared<Ground>();
	Attach(ground);

	setGravity(glm::vec3(0, -9, 0));
	elapsed = 0;

	Animat();

	if (!Game::Initialise())
	{
		return false;
	}

	return true;
}

void BGE::Assignment1::Update()
{
	Game::Update();
}

void BGE::Assignment1::Cleanup()
{
	Game::Cleanup();
}

void BGE::Assignment1::Animat()
{
	//Right Leg
	glm::quat quatLowerRightLeg = glm::angleAxis(30.0f, glm::vec3(1, 0, 0));
	glm::quat quatUpperRightLeg = glm::angleAxis(-45.0f, glm::vec3(1, 0, 0));

	shared_ptr<PhysicsController> lowerRightLeg = physicsFactory->CreateBox(2, 2, 15, glm::vec3(0, 8, 0), quatLowerRightLeg);
	shared_ptr<PhysicsController> upperRightLeg = physicsFactory->CreateBox(2, 2, 8, glm::vec3(0, 17, 0), quatUpperRightLeg);
	lowerRightLeg->transform->diffuse = glm::vec3(1, 0, 0);
	upperRightLeg->transform->diffuse = glm::vec3(0, 0, 0);

	btHingeConstraint * hingeRight = new btHingeConstraint(*lowerRightLeg->rigidBody, *upperRightLeg->rigidBody, btVector3(0, 0, 6), btVector3(0, 0, -6), btVector3(0, 1, 0), btVector3(0, 1, 0), true);
	dynamicsWorld->addConstraint(hingeRight);

	//Left Leg
	glm::quat quatLowerLeftLeg = glm::angleAxis(30.0f, glm::vec3(0, 1, 0));
	glm::quat quatUpperLeftLeg = glm::angleAxis(-45.0f, glm::vec3(0, 1, 0));

	shared_ptr<PhysicsController> lowerLeftLeg = physicsFactory->CreateBox(2, 2, 15, glm::vec3(8, 8, 0), quatLowerRightLeg);
	shared_ptr<PhysicsController> upperLeftLeg = physicsFactory->CreateBox(2, 2, 8, glm::vec3(8, 17, 0), quatUpperRightLeg);
	lowerLeftLeg->transform->diffuse = glm::vec3(1, 0, 0);
	upperLeftLeg->transform->diffuse = glm::vec3(0, 0, 0);

	btHingeConstraint * hingeLeft = new btHingeConstraint(*lowerLeftLeg->rigidBody, *upperLeftLeg->rigidBody, btVector3(0, 0, -6), btVector3(0, 0, 6), btVector3(0, 1, 0), btVector3(0, 1, 0), true);
	dynamicsWorld->addConstraint(hingeLeft);

	//Hip
	shared_ptr<PhysicsController> Hip = physicsFactory->CreateCylinder(1.5f, 5, glm::vec3(4, 19, 1), glm::angleAxis(90.0f, glm::vec3(0, 0, 1)));
	Hip->transform->diffuse = glm::vec3(1, 0, 0);
	btHingeConstraint * hingeRightHip = new btHingeConstraint(*upperRightLeg->rigidBody, *Hip->rigidBody, btVector3(0, -4, 0), btVector3(0, 0, 0), btVector3(0, 1, 0), btVector3(0, 1, 0), true);
	btHingeConstraint * hingeLeftHip = new btHingeConstraint(*upperLeftLeg->rigidBody, *Hip->rigidBody, btVector3(0, 4, 0), btVector3(0, 0, 0), btVector3(0, 1, 0), btVector3(0, 1, 0), true);
	
	dynamicsWorld->addConstraint(hingeRightHip);
	hingeLeftHip->setLimit(0.0f, 1.0f, 0.0f);
	dynamicsWorld->addConstraint(hingeLeftHip);
	
	// Enable a motor on the hinge joints
	hingeRightHip->enableAngularMotor(true, 100, 100);
	hingeLeftHip->enableAngularMotor(true, 100, -100);

	//Torso
	shared_ptr<PhysicsController> division = physicsFactory->CreateBox(1, 3, 10, glm::vec3(4, 22, -1), glm::angleAxis(90.0f, glm::vec3(0, 0, 1)));
	division->transform->diffuse = glm::vec3(0, 0, 0);

	btFixedConstraint * hipJoint1 = new btFixedConstraint(*Hip->rigidBody, *division->rigidBody, btTransform(GLToBtQuat(glm::angleAxis(90.0f, glm::vec3(0, 0, 1))), GLToBtVector(glm::vec3(4, 20, 1))), btTransform(GLToBtQuat(glm::angleAxis(90.0f, glm::vec3(0, 0, 1))), GLToBtVector(glm::vec3(4, 20, -1))));
	dynamicsWorld->addConstraint(hipJoint1);
	
	/*
	shared_ptr<PhysicsController> backTorso = physicsFactory->CreateBox(4, 10, 10, glm::vec3(4, 25, -4), glm::angleAxis(90.0f, glm::vec3(0, 0, 1)));
	backTorso->transform->diffuse = glm::vec3(0, 0, 0);
	shared_ptr<PhysicsController> frontTorso = physicsFactory->CreateCylinder(2, 8, glm::vec3(4, 25, 3), glm::angleAxis(90.0f, glm::vec3(0, 0, 1)));
	frontTorso->transform->diffuse = glm::vec3(1, 0, 0);
	btFixedConstraint * spine = new btFixedConstraint(*backTorso->rigidBody, *frontTorso->rigidBody, btTransform(GLToBtQuat(glm::angleAxis(90.0f, glm::vec3(0, 0, 1))), GLToBtVector(glm::vec3(4, 25, 0))), btTransform(GLToBtQuat(glm::angleAxis(90.0f, glm::vec3(0, 0, 1))), GLToBtVector(glm::vec3(4, 25, 0))));
	dynamicsWorld->addConstraint(spine);

	btFixedConstraint * hipJoint2 = new btFixedConstraint(*division->rigidBody, *backTorso->rigidBody, btTransform(GLToBtQuat(glm::angleAxis(90.0f, glm::vec3(0, 0, 1))), GLToBtVector(glm::vec3(4, 23, -2))), btTransform(GLToBtQuat(glm::angleAxis(90.0f, glm::vec3(0, 0, 1))), GLToBtVector(glm::vec3(4, 23, -2))));
	dynamicsWorld->addConstraint(hipJoint2);
	
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
	*/
}