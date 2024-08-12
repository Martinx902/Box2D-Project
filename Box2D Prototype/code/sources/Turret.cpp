/**
  * @author    Martin Pérez Villabrille
  * @copyright Copyright (c) 2023+ Martin Pérez Villabrille.
  *            All rights reserved
  */

#include "../headers/Turret.hpp"
#include "../headers/Scene.hpp"
#include "../headers/Layers.h"
#include <box2d/b2_settings.h>
#include "../headers/UserData.hpp"

namespace Mgine2D
{
	void Turret::turn_turret()
	{
		joint->SetMotorSpeed(5.f);

		joint->SetMaxMotorTorque(15);

		joint->SetLimits(0, 1.57f);
	}

	void Turret::handle(const Message& message)
	{
		if (message.trigger == "firstTrigger")
			turn_turret();
	}

	void Turret::initialize()
	{
		parent->add_message_listener(*this, "trigger");

		b2World* world = parent->get_physic_world();

		User_Data* user_data = new User_Data;
		user_data->id = "turret";

		//------- BODIES --------

		//UPPER BODY

		b2BodyDef bodyDef1;
		bodyDef1.type = b2_dynamicBody;
		b2Body* upperBody = world->CreateBody(&bodyDef1);

		//LOWER BODY

		b2BodyDef bodyDef2;
		bodyDef2.type = b2_staticBody;
		bodyDef2.position.Set(24.4f, 4.2f);
		bodyDef2.angle = 1.5708f;
		bodyDef2.enabled = true;
		b2Body* lowerBody = world->CreateBody(&bodyDef2);

		//JOINT

		b2BodyDef jointBodyDef;
		jointBodyDef.type = b2_staticBody;
		jointBodyDef.position.Set(24.4f, 6.4f);
		b2Body* joint_body = world->CreateBody(&jointBodyDef);

		//------- SHAPES --------

		//UPPER BODY

		b2PolygonShape polygonShape1;
		polygonShape1.SetAsBox(1.5f, 0.1f, b2Vec2(23.5, 7.5f), -48.f);

		b2PolygonShape polygonShape2;
		polygonShape2.SetAsBox(1.5f, 0.1f, b2Vec2(25.3f, 7.5f), 48.f);

		//LOWER BODY

		b2PolygonShape polygonShape3;
		polygonShape3.SetAsBox(2.2f, 0.1f);

		//JOINT

		b2CircleShape wheelShape;
		wheelShape.m_radius = 0.3f;

		//TRIGGER

		b2PolygonShape triggerShape;
		triggerShape.SetAsBox(1, 1);

		//------- FIXTURES --------

		//UPPER BODY

		b2FixtureDef polygonfixture1;
		polygonfixture1.shape = &polygonShape1;
		polygonfixture1.density = 0.01f;

		b2FixtureDef polygonfixture2;
		polygonfixture2.shape = &polygonShape2;
		polygonfixture2.density = 0.01f;

		//LOWER BODY

		b2FixtureDef polygonfixture3;
		polygonfixture3.shape = &polygonShape3;
		polygonfixture3.density = 1.0f;
		polygonfixture3.filter.categoryBits = Layers::NotCollisionable;

		//JOINT

		b2FixtureDef ballFixtureDef;
		ballFixtureDef.shape = &wheelShape;
		ballFixtureDef.density = 0.45f;
		ballFixtureDef.friction = 0.3f;

		//TRIGGER

		b2FixtureDef triggerFixtureDef;
		triggerFixtureDef.shape = &triggerShape;
		triggerFixtureDef.density = 0.45f;
		triggerFixtureDef.friction = 0.3f;
		triggerFixtureDef.isSensor = true;
		triggerFixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(user_data);

		//------- ADD FIXTURES --------

		upperBody->CreateFixture(&polygonfixture1);
		upperBody->CreateFixture(&polygonfixture2);

		lowerBody->CreateFixture(&polygonfixture3);

		joint_body->CreateFixture(&ballFixtureDef);

		//------- JOINTS --------

		b2RevoluteJointDef jointDef1;
		jointDef1.Initialize(upperBody, lowerBody, joint_body->GetWorldCenter());
		jointDef1.enableMotor = true;
		joint = (b2RevoluteJoint*)world->CreateJoint(&jointDef1);
		joint->EnableLimit(true);

		add_body(upperBody);
		add_body(lowerBody);
		add_body(joint_body);

		spawn_balls(world, ballFixtureDef);
	}

	void Turret::spawn_balls(b2World* world, b2FixtureDef& ballFixtureDef)
	{
		User_Data* user_data = new User_Data;
		user_data->id = "ball";

		ballFixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(user_data);

		for (size_t i = 0; i < 5; i++)
		{
			b2BodyDef ballDef;
			ballDef.type = b2_dynamicBody;
			ballDef.position.Set(24.4f, 9.f + i);
			b2Body* ballBody = world->CreateBody(&ballDef);
			ballBody->IsBullet();

			ballBody->CreateFixture(&ballFixtureDef);

			add_body(ballBody);
		}
	}
}