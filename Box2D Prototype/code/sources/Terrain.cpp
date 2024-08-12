/**
  * @author    Martin Pérez Villabrille
  * @copyright Copyright (c) 2023+ Martin Pérez Villabrille.
  *            All rights reserved
  */

#include "../headers/Terrain.hpp"
#include "../headers/Scene.hpp"

namespace Mgine2D
{
	void Terrain::initialize()
	{
		b2World* world = parent->get_physic_world();

		//------- BODIES --------

		b2BodyDef bodyDef;
		bodyDef.type = b2_staticBody;
		b2Body* terrain_body = world->CreateBody(&bodyDef);

		//------- SHAPES --------

		//LEFT RAMP

		b2EdgeShape edge0;
		edge0.SetTwoSided(b2Vec2(-0.1f, 0.1f), b2Vec2(11.3f, 0.1f));

		b2EdgeShape edge1;
		edge1.SetTwoSided(b2Vec2(-0.1f, 4), b2Vec2(3, 4));

		b2EdgeShape edge2;
		edge2.SetTwoSided(b2Vec2(3, 4), b2Vec2(4.5f, 3.f));

		b2EdgeShape edge3;
		edge3.SetTwoSided(b2Vec2(4.5f, 3), b2Vec2(5.8f, 2.2f));

		b2EdgeShape edge4;
		edge4.SetTwoSided(b2Vec2(5.8f, 2.2f), b2Vec2(7.5f, 1.8f));

		b2EdgeShape edge5;
		edge5.SetTwoSided(b2Vec2(7.5f, 1.8f), b2Vec2(9.5f, 2));

		b2EdgeShape edge6;
		edge6.SetTwoSided(b2Vec2(9.5f, 2), b2Vec2(11.3f, 2.5f));

		b2EdgeShape edge7;
		edge7.SetTwoSided(b2Vec2(11.3f, 2.5f), b2Vec2(11.3f, 0.1f));

		//RIGHT RAMP

		b2EdgeShape edge8;
		edge8.SetTwoSided(b2Vec2(16.5f, 1.5f), b2Vec2(30, 2.3f));

		b2EdgeShape edge9;
		edge9.SetTwoSided(b2Vec2(16.5f, 1.5f), b2Vec2(16.5f, 0.1f));

		b2EdgeShape edge10;
		edge10.SetTwoSided(b2Vec2(16.5f, 0.1f), b2Vec2(30, 0.1f));

		//PLATFORM

		b2PolygonShape polygonShape1;
		polygonShape1.SetAsBox(1.5f, 0.1f, b2Vec2(6, 7.5f), -48.f);

		b2PolygonShape polygonShape2;
		polygonShape2.SetAsBox(1.5f, 0.1f, b2Vec2(7.8f, 7.5f), 48.f);

		b2PolygonShape polygonShape3;
		polygonShape3.SetAsBox(1.3f, 0.1f, b2Vec2(10.f, 8.6f), 0);

		//BORDERS

		b2EdgeShape leftBorderShape;
		leftBorderShape.SetTwoSided(b2Vec2(-0.2f, 0), b2Vec2(-0.2f, 40));

		b2EdgeShape rightBorderShape;
		rightBorderShape.SetTwoSided(b2Vec2(28.5f, 0), b2Vec2(28.5f, 40));

		//------- FIXTURES --------

		//LEFT RAMP

		b2FixtureDef fixtureDef0;
		fixtureDef0.shape = &edge0;
		fixtureDef0.density = 1.0f;

		b2FixtureDef fixtureDef1;
		fixtureDef1.shape = &edge1;
		fixtureDef1.density = 1.0f;

		b2FixtureDef fixtureDef2;
		fixtureDef2.shape = &edge2;
		fixtureDef2.density = 1.0f;

		b2FixtureDef fixtureDef3;
		fixtureDef3.shape = &edge3;
		fixtureDef3.density = 1.0f;

		b2FixtureDef fixtureDef4;
		fixtureDef4.shape = &edge4;
		fixtureDef4.density = 1.0f;

		b2FixtureDef fixtureDef5;
		fixtureDef5.shape = &edge5;
		fixtureDef5.density = 1.0f;

		b2FixtureDef fixtureDef6;
		fixtureDef6.shape = &edge6;
		fixtureDef6.density = 1.0f;

		b2FixtureDef fixtureDef7;
		fixtureDef7.shape = &edge7;
		fixtureDef7.density = 1.0f;

		//RIGHT RAMP

		b2FixtureDef fixtureDef8;
		fixtureDef8.shape = &edge8;
		fixtureDef8.density = 1.0f;

		b2FixtureDef fixtureDef9;
		fixtureDef9.shape = &edge9;
		fixtureDef9.density = 1.0f;

		b2FixtureDef fixtureDef10;
		fixtureDef10.shape = &edge10;
		fixtureDef10.density = 1.0f;

		//PLATFORM

		b2FixtureDef polygonfixture1;
		polygonfixture1.shape = &polygonShape1;
		polygonfixture1.density = 1.0f;

		b2FixtureDef polygonfixture2;
		polygonfixture2.shape = &polygonShape2;
		polygonfixture2.density = 1.0f;

		b2FixtureDef polygonfixture3;
		polygonfixture3.shape = &polygonShape3;
		polygonfixture3.density = 1.0f;

		//BORDERS

		b2FixtureDef borderFixture1;
		borderFixture1.shape = &leftBorderShape;
		borderFixture1.density = 1.0f;

		b2FixtureDef borderFixture2;
		borderFixture2.shape = &rightBorderShape;
		borderFixture2.density = 1.0f;

		//------- ADD FIXTURES --------

		//LEFT RAMP

		terrain_body->CreateFixture(&fixtureDef0);
		terrain_body->CreateFixture(&fixtureDef1);
		terrain_body->CreateFixture(&fixtureDef2);
		terrain_body->CreateFixture(&fixtureDef3);
		terrain_body->CreateFixture(&fixtureDef4);
		terrain_body->CreateFixture(&fixtureDef5);
		terrain_body->CreateFixture(&fixtureDef6);
		terrain_body->CreateFixture(&fixtureDef7);

		//RIGHT RAMP

		terrain_body->CreateFixture(&fixtureDef8);
		terrain_body->CreateFixture(&fixtureDef9);
		terrain_body->CreateFixture(&fixtureDef10);

		//PLATFORM

		terrain_body->CreateFixture(&polygonfixture1);
		terrain_body->CreateFixture(&polygonfixture2);
		terrain_body->CreateFixture(&polygonfixture3);

		//BORDERS

		terrain_body->CreateFixture(&borderFixture1);
		terrain_body->CreateFixture(&borderFixture2);

		add_body(terrain_body);
	}
}