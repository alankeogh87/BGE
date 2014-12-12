#pragma once
#include "Game.h"
#include "PhysicsController.h"
#include "PhysicsFactory.h"
#include <btBulletDynamicsCommon.h>

namespace BGE
{
	class Assignment1 :
		public Game
	{
	private:

	public:
		Assignment1(void);
		~Assignment1(void);
		bool Initialise();
		void Update();
		void Cleanup();
		void CreateWall();
		void Animat();
	};
}
