/**
  * @author    Martin Pérez Villabrille
  * @copyright Copyright (c) 2023+ Martin Pérez Villabrille.
  *            All rights reserved
  */

#include <algorithm>

#include "../headers/Vehicle.hpp"
#include "../headers/Scene.hpp"

namespace Mgine2D
{
	void Vehicle::move(Movement movement_direction)
	{
		right_wheel_joint->SetMaxMotorTorque(75.f);
		right_wheel_joint->SetMotorSpeed(movement_speed * int(movement_direction));

		left_wheel_joint->SetMaxMotorTorque(75.f);
		left_wheel_joint->SetMotorSpeed(movement_speed * int(movement_direction));
	}

	void Vehicle::activate_trunk()
	{
		int direction = trunk_is_open ? -1 : 1;

		trunk_joint->SetMaxMotorTorque(10.f);

		trunk_joint->SetMotorSpeed(15.f * direction);

		trunk_is_open = direction == 1 ? true : false;
	}

	void Vehicle::update()
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			move(Movement::LEFT);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			move(Movement::RIGHT);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			move(Movement::BRAKE);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::V))
		{
			activate_trunk();
		}
	}

	void Vehicle::initialize()
	{
		b2World* world = parent->get_physic_world();

		User_Data* user_data = new User_Data;
		user_data->id = "vehicle";

		//------- BODIES --------

		//CHASIS
		b2BodyDef chassisBodyDef;
		chassisBodyDef.type = b2_dynamicBody;
		chassisBodyDef.position.Set(1, 5.8f);
		b2Body* chasssis_body = world->CreateBody(&chassisBodyDef);

		//WHEEL 1
		b2BodyDef wheel1BodyDef;
		wheel1BodyDef.type = b2_dynamicBody;
		wheel1BodyDef.position.Set(0.2f, 5.5f);
		b2Body* right_wheel_body = world->CreateBody(&wheel1BodyDef);

		//WHEEL 2
		b2BodyDef wheel2BodyDef;
		wheel2BodyDef.type = b2_dynamicBody;
		wheel2BodyDef.position.Set(1.8f, 5.5f);
		b2Body* left_wheel_body = world->CreateBody(&wheel2BodyDef);

		//TRUNK
		b2BodyDef trunkBodyDef;
		trunkBodyDef.type = b2_dynamicBody;
		trunkBodyDef.position.Set(1, 6.2f);
		b2Body* trunk_body = world->CreateBody(&trunkBodyDef);

		//TRUNK JOINT
		b2BodyDef trunkJointBodyDef;
		trunkJointBodyDef.type = b2_dynamicBody;
		trunkJointBodyDef.position.Set(-0.1f, 6.3f);
		b2Body* trunk_joint_body = world->CreateBody(&trunkJointBodyDef);

		//------- SHAPES --------

		b2PolygonShape chassisShape;
		chassisShape.SetAsBox(1.3f, 0.2f);

		b2CircleShape wheelShape;
		wheelShape.m_radius = 0.3f;

		b2PolygonShape trunkBaseShape;
		trunkBaseShape.SetAsBox(1.3f, 0.1f);

		b2PolygonShape trunkLateralShape1;
		trunkLateralShape1.SetAsBox(0.1f, 0.25f, b2Vec2(-1.2f, 0.25f), 0);

		b2PolygonShape trunkLateralShape2;
		trunkLateralShape2.SetAsBox(0.1f, 0.4f, b2Vec2(1.2f, 0.4f), 0);

		b2CircleShape jointTrunkShape;
		jointTrunkShape.m_radius = 0.2f;
		jointTrunkShape.m_p = b2Vec2(-1.05f, 0.2f);

		//------- FIXTURES --------

		//CHASIS
		b2FixtureDef chassisFixtureDef;
		chassisFixtureDef.shape = &chassisShape;
		chassisFixtureDef.density = 0.5f;
		chassisFixtureDef.friction = 0.3f;

		//WHEELS
		b2FixtureDef wheelFixtureDef;
		wheelFixtureDef.shape = &wheelShape;
		wheelFixtureDef.density = 1.0f;
		wheelFixtureDef.friction = 0.3f;

		//TRUNK

		//BASE
		b2FixtureDef baseTrunkDef;
		baseTrunkDef.shape = &trunkBaseShape;
		baseTrunkDef.density = 0.1f;
		baseTrunkDef.friction = 0.3f;

		//LATERALS
		b2FixtureDef lateralTrunkDef1;
		lateralTrunkDef1.shape = &trunkLateralShape1;
		lateralTrunkDef1.density = 0.1f;

		b2FixtureDef lateralTrunkDef2;
		lateralTrunkDef2.shape = &trunkLateralShape2;
		lateralTrunkDef2.density = 0.1f;

		b2FixtureDef trunkJoinFixtureDef;
		trunkJoinFixtureDef.shape = &jointTrunkShape;
		trunkJoinFixtureDef.density = 0.1f;

		//------- USER DATA --------

		chassisFixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(user_data);
		wheelFixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(user_data);
		baseTrunkDef.userData.pointer = reinterpret_cast<uintptr_t>(user_data);
		lateralTrunkDef1.userData.pointer = reinterpret_cast<uintptr_t>(user_data);
		lateralTrunkDef2.userData.pointer = reinterpret_cast<uintptr_t>(user_data);

		//------- ADD FIXTURES --------

		chasssis_body->CreateFixture(&chassisFixtureDef);
		chasssis_body->CreateFixture(&trunkJoinFixtureDef);

		right_wheel_body->CreateFixture(&wheelFixtureDef);
		left_wheel_body->CreateFixture(&wheelFixtureDef);

		trunk_body->CreateFixture(&lateralTrunkDef1);
		trunk_body->CreateFixture(&lateralTrunkDef2);
		trunk_body->CreateFixture(&baseTrunkDef);

		//------- JOINTS --------

		b2RevoluteJointDef jointDef1;
		jointDef1.Initialize(chasssis_body, right_wheel_body, right_wheel_body->GetWorldCenter());
		jointDef1.enableMotor = true;
		right_wheel_joint = (b2RevoluteJoint*)world->CreateJoint(&jointDef1);

		b2RevoluteJointDef jointDef2;
		jointDef2.Initialize(chasssis_body, left_wheel_body, left_wheel_body->GetWorldCenter());
		jointDef2.enableMotor = true;
		left_wheel_joint = (b2RevoluteJoint*)world->CreateJoint(&jointDef2);

		b2RevoluteJointDef trunkJointDef;
		trunkJointDef.Initialize(chasssis_body, trunk_body, trunk_joint_body->GetWorldCenter());
		trunkJointDef.enableMotor = true;
		trunk_joint = (b2RevoluteJoint*)world->CreateJoint(&trunkJointDef);
		trunk_joint->EnableLimit(true);
        trunk_joint->SetLimits(0, 2);

		add_body(right_wheel_body);
		add_body(left_wheel_body);
		add_body(trunk_body);
		add_body(trunk_joint_body);
		add_body(chasssis_body);
	}
}