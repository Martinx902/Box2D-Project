/**
  * @author    Martin Pérez Villabrille
  * @copyright Copyright (c) 2023+ Martin Pérez Villabrille.
  *            All rights reserved
  */

#include "../headers/Elevator.hpp"
#include "../headers/Scene.hpp"

namespace Mgine2D
{
	void Elevator::spawn_elevator()
	{
		if (!elevator_instanciated)
		{
			platform_body->SetEnabled(true);
			trigger_body->SetEnabled(true);

			add_body(platform_body);

			elevator_instanciated = true;
		}
	}

	void Elevator::activate_elevator()
	{
		trigger_body->SetEnabled(false);

		elevator_moving = true;
	}

	void Elevator::update()
	{
		if (elevator_moving)
		{
			platform_body->SetLinearVelocity({ 0, 1 });

			b2Vec2 desiredPosition(13.9f, 8.5f);
			b2Vec2 currentPosition = platform_body->GetPosition();

			if (currentPosition.y > desiredPosition.y)
			{
				platform_body->SetLinearVelocity({ 0, 0 });

				elevator_moving = false;
			}
		}
	}

	void Elevator::handle(const Message& message)
	{
		if (message.trigger == "firstTrigger")
			spawn_elevator();

		if (message.trigger == "secondTrigger" && trigger_body->IsEnabled())
			activate_elevator();
	}

	void Elevator::initialize()
	{
		parent->add_message_listener(*this, "trigger");

		b2World* world = parent->get_physic_world();

		User_Data* user_data = new User_Data;
		user_data->id = "elevator";

		//------- BODIES --------

		//PLATFORM

		b2BodyDef platformBodyDef;
		platformBodyDef.type = b2_kinematicBody;
		platformBodyDef.position.Set(13.9f, 1.3f);
		platform_body = world->CreateBody(&platformBodyDef);
		platform_body->SetEnabled(false);

		//TRIGGER

		b2BodyDef triggerBodyDef;
		triggerBodyDef.type = b2_staticBody;
		triggerBodyDef.position.Set(13.2f, 2.7f);
		trigger_body = world->CreateBody(&triggerBodyDef);
		trigger_body->SetEnabled(false);

		//------- SHAPES --------

		b2PolygonShape platformShape;
		platformShape.SetAsBox(2.6f, 0.2f);

		b2PolygonShape poleShape;
		poleShape.SetAsBox(0.2f, 10.f, b2Vec2(0, -10.f), 0);

		b2PolygonShape triggerShape;
		triggerShape.SetAsBox(2, 1);

		//------- FIXTURES --------

		b2FixtureDef platformFixtureDef;
		platformFixtureDef.shape = &platformShape;
		platformFixtureDef.density = 0.1f;
		platformFixtureDef.friction = 0.3f;

		b2FixtureDef poleFixtureDef;
		poleFixtureDef.shape = &poleShape;
		poleFixtureDef.density = 0.1f;
		poleFixtureDef.friction = 0.3f;

		//TRIGGER

		b2FixtureDef triggerFixtureDef;
		triggerFixtureDef.shape = &triggerShape;
		triggerFixtureDef.density = 0.1f;
		triggerFixtureDef.friction = 0.3f;
		triggerFixtureDef.isSensor = true;
		triggerFixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(user_data);

		//------- ADD FIXTURES --------

		platform_body->CreateFixture(&platformFixtureDef);
		platform_body->CreateFixture(&poleFixtureDef);

		trigger_body->CreateFixture(&triggerFixtureDef);
	}
}