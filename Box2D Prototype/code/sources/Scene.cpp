/**
  * @author    Martin Pérez Villabrille
  * @copyright Copyright (c) 2023+ Martin Pérez Villabrille.
  *            All rights reserved
  */

#include <tuple>

#include "../headers/Scene.hpp"

namespace Mgine2D
{

    void Scene::Contact_Listener::BeginContact(b2Contact* contact)
    {
        if (contact->GetFixtureA()->IsSensor())
        {
            sensorFixture = contact->GetFixtureA();
            otherFixture = contact->GetFixtureB();
        }
        else if (contact->GetFixtureB()->IsSensor())
        {
            sensorFixture = contact->GetFixtureB();
            otherFixture = contact->GetFixtureA();
        }

        if (sensorFixture)
        {
            if (otherFixture && otherFixture->GetUserData().pointer)
            {
                User_Data* userData = reinterpret_cast<User_Data*>(sensorFixture->GetUserData().pointer);

                //Activate Turret and Enable Elevator
                if (userData->id == "turret")
                {
                    Message* message = new Message;
                    message->id = "trigger";
                    message->trigger = "firstTrigger";

                    scene->get_message_dispatcher()->send(*message);
                }

                //Activate Elevator
                if (userData->id == "elevator")
                {
                    User_Data* otherUserData = reinterpret_cast<User_Data*>(otherFixture->GetUserData().pointer);

                    if (otherUserData->id == "vehicle")
                    {
                        Message* message = new Message;
                        message->id = "trigger";
                        message->trigger = "secondTrigger";

                        scene->get_message_dispatcher()->send(*message);
                    }
                }

                //Reset Scene
                if (userData->id == "reset")
                {
                    User_Data* otherUserData = reinterpret_cast<User_Data*>(otherFixture->GetUserData().pointer);

                    if (otherUserData->id == "vehicle")
                    {
                        scene->initialize_scene();
                    }
                }

                //End of game, play particles
                if (userData->id == "end")
                {
                    User_Data* otherUserData = reinterpret_cast<User_Data*>(otherFixture->GetUserData().pointer);

                    if (otherUserData->id == "ball")
                    {
                        Message* message = new Message;
                        message->id = "trigger";
                        message->trigger = "end";

                        scene->get_message_dispatcher()->send(*message);
                    }
                }
            }
        }
    }

	Scene::Scene(sf::RenderWindow* given_window, std::function<void(Scene&)> funcPtr) : window(given_window), configure_scene_ptr(funcPtr)
	{
		initialize_scene();

		window->setVerticalSyncEnabled(true);
	}

	void Scene::run()
	{
		running = true;

		const float target_fps = 60.f;
		const float target_time = 1.f / target_fps;

		float delta_time = target_time;

		sf::Clock timer;

		do
		{
			timer.restart();

			//Window events
			process_events();

			//Physics update
			update_world(delta_time);

			//Rendering SFML
			window->clear();

			update_entities();

			window->display();

			//Message System
			message_dispatcher->execute(delta_time);

			//Updating the timer and stopping for a few frames if we are execing the desired framerate
			float elapsed = timer.getElapsedTime().asSeconds();

			if (elapsed < target_time)
			{
				sf::sleep(sf::seconds(target_time - elapsed));
			}

			delta_time = timer.getElapsedTime().asSeconds();
		} while (running);
	}

	void Scene::process_events()
	{
		sf::Event event;

		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				running = false;
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
		{
			initialize_scene();
		}
	}

	void Scene::update_world(float t)
	{
		physics_world->Step(t, 8, 4);
	}

	void Scene::initialize_scene()
	{
		message_dispatcher = new Message_Dispatcher(this);

		contact_listener = new Contact_Listener(this);

		physics_world = new b2World(b2Vec2{ 0, -10.f });

		physics_world->SetContactListener(contact_listener);

		entities.clear();

		configure_scene_ptr(*this);

		//Initialize Entities
		for (auto& item : entities)
		{
			item.second->initialize();
		}
	}

	void Scene::update_entities()
	{
		for (auto& item : entities)
		{
			item.second->update();

			draw_entity(item.second->get_bodies(), *window, physics_to_graphics_scale);
		}
	}

	void Scene::draw_entity(std::vector<b2Body*>& bodies, sf::RenderWindow& renderer, float scale)
	{
		float window_height = get_window_height();

		for (size_t i = 0; i < bodies.size(); i++)
		{
			b2Body* body = bodies[i];

			const b2Transform& body_transform = body->GetTransform();

			for (b2Fixture* fixture = body->GetFixtureList(); fixture != nullptr; fixture = fixture->GetNext())
			{
				b2Shape::Type shape_type = fixture->GetShape()->GetType();

				switch (shape_type)
				{
				case b2Shape::e_circle:
				{
					b2CircleShape* circle = dynamic_cast<b2CircleShape*>(fixture->GetShape());

					sf::CircleShape shape;

					float radius = circle->m_radius * scale;

					shape.setPosition(box2d_position_to_sfml_position(b2Mul(body_transform, circle->m_p), window_height, scale) - sf::Vector2f(radius, radius));
					shape.setRadius(radius);
					shape.setFillColor(sf::Color::Yellow);

					renderer.draw(shape);

					break;
				}

				case b2Shape::e_edge:
				{
					b2EdgeShape* edge = dynamic_cast<b2EdgeShape*>(fixture->GetShape());

					const b2Vec2 start = b2Mul(body_transform, edge->m_vertex1);
					const b2Vec2 end = b2Mul(body_transform, edge->m_vertex2);

					sf::Color color = sf::Color::White;

					sf::Vertex line[] =
					{
						sf::Vertex(box2d_position_to_sfml_position(start, window_height, scale), color),
						sf::Vertex(box2d_position_to_sfml_position(end,   window_height, scale), color),
					};

					renderer.draw(line, 2, sf::Lines);

					break;
				}

				case b2Shape::e_polygon:
				{
					b2PolygonShape* box2d_polygon = dynamic_cast<b2PolygonShape*>(fixture->GetShape());

					sf::ConvexShape sfml_polygon;

					sfml_polygon.setPointCount(box2d_polygon->m_count);
					sfml_polygon.setFillColor(sf::Color::Blue);

					for (int index = 0; index < box2d_polygon->m_count; index++)
					{
						sfml_polygon.setPoint
						(
							index,
							box2d_position_to_sfml_position(b2Mul(body_transform, box2d_polygon->m_vertices[index]), window_height, scale)
						);
					}

					renderer.draw(sfml_polygon);

					break;
				}
				}
			}
		}
	}
}