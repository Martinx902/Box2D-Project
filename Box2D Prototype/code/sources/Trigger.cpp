/**
  * @author    Martin Pérez Villabrille
  * @copyright Copyright (c) 2023+ Martin Pérez Villabrille.
  *            All rights reserved
  */

#include "../headers/Trigger.hpp"
#include "../headers/Scene.hpp"

namespace Mgine2D
{
	void Trigger::initialize()
	{
		b2World* world = parent->get_physic_world();

		//------- BODIES --------

		b2BodyDef triggerBodyDef;
		triggerBodyDef.type = b2_staticBody;
		triggerBodyDef.position.Set(position.x, position.y);
		body = world->CreateBody(&triggerBodyDef);
		body->SetEnabled(true);

		//------- SHAPES --------

		b2PolygonShape triggerShape;
		triggerShape.SetAsBox(scale.x, scale.y);

		//------- FIXTURES --------

		b2FixtureDef triggerFixtureDef;
		triggerFixtureDef.shape = &triggerShape;
		triggerFixtureDef.density = 0.1f;
		triggerFixtureDef.friction = 0.3f;
		triggerFixtureDef.isSensor = true;
		triggerFixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(user_data);

		body->CreateFixture(&triggerFixtureDef);

		if (visualize)
			add_body(body);
	}
};