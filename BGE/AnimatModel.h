#pragma once
#include "Game.h"
#include "PhysicsController.h"
#include "PhysicsFactory.h"
#include <btBulletDynamicsCommon.h>

namespace BGE
{
	class AnimatModel :
		public Game
	{
	private:

	public:
		AnimatModel(void);
		~AnimatModel(void);
		bool Initialise();
		void Update();
		void Cleanup();
		void Model();
	};
}
