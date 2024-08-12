/**
  * @author    Martin Pérez Villabrille
  * @copyright Copyright (c) 2023+ Martin Pérez Villabrille.
  *            All rights reserved
  */

#include "../headers/Physic_Entity.hpp"
#include "../headers/Scene.hpp"

#include <vector>
#include <Box2D/Box2D.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

namespace Mgine2D
{
	void Physic_Entity::render(sf::RenderWindow& renderer, float scale)
	{
		//Si utilizo este renderer entonces no estoy usando para nada mi lista de shapes, lo que hace que pueda mudar este método a la escena
		//pero eso significaría que otro tipo de entities que deriven de Entity no tengan la posibilidad de renderizarse como ellas quieran

		//También si lo quito que diferencia tengo de una physic entity a una entity normal?

		//Primer renderer usando las shapes de SFML, no funcionaba correctamente.

		/*
		float window_height = parent->get_window_height();

		for (const auto& drawable : shapes) {
			auto body_position = body->GetPosition();
			auto body_rotation = body->GetAngle();

			// Apply new position and rotation to the shapes based on their type
			if (auto circleShape = std::dynamic_pointer_cast<sf::CircleShape>(drawable)) {
				// Apply position and rotation to the circle shape
				circleShape->setPosition(box2d_position_to_sfml_position(body_position, window_height, scale));
				circleShape->setRotation(body_rotation); // Convert radians to degrees
			}
			else if (auto convexShape = std::dynamic_pointer_cast<sf::ConvexShape>(drawable)) {
				// Apply position and rotation to the convex shape
				convexShape->setPosition(box2d_position_to_sfml_position(body_position, window_height, scale));
				convexShape->setRotation(body_rotation); // Convert radians to degrees
			}
			else if (auto vertexArray = std::dynamic_pointer_cast<sf::VertexArray>(drawable)) {
				// Apply position and rotation to the vertex array
				// You would need to implement this based on your specific vertex array usage
			}

			// Draw the shape
			renderer.draw(*drawable);
		}
        */

		/*
		float window_height = parent->get_window_height();
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
				shape.setFillColor(sf::Color::Blue);

				renderer.draw(shape);

				break;
			}

			case b2Shape::e_edge:
			{
				b2EdgeShape* edge = dynamic_cast<b2EdgeShape*>(fixture->GetShape());

				const b2Vec2 start = b2Mul(body_transform, edge->m_vertex1);
				const b2Vec2 end = b2Mul(body_transform, edge->m_vertex2);

				sf::Color color = sf::Color::Green;

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
				sfml_polygon.setFillColor(sf::Color::Yellow);

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
		*/
	}

	void Physic_Entity::set_shape()
	{
		/*
		float window_height = parent->get_window_height();

		const b2Transform& body_transform = body->GetTransform();

		for (b2Fixture* fixture = body->GetFixtureList(); fixture != nullptr; fixture = fixture->GetNext())
		{
			b2Shape::Type shape_type = fixture->GetShape()->GetType();

			//CIRCLES
			if (shape_type == b2Shape::e_circle)
			{
				b2CircleShape* circle = dynamic_cast<b2CircleShape*>(fixture->GetShape());

				float  radius = circle->m_radius * parent->get_physics_to_graphics_scale();
				b2Vec2 center = circle->m_p;

				std::shared_ptr<sf::CircleShape> circle_shape = std::make_shared<sf::CircleShape>();

				circle_shape->setPosition
				(box2d_position_to_sfml_position(b2Mul(body_transform, center), window_height, parent->get_physics_to_graphics_scale()) - sf::Vector2f(radius, radius));
				circle_shape->setFillColor(sf::Color::Blue);
				circle_shape->setRadius(radius);

				shapes.push_back(circle_shape);
			}

			//EDGES
			else if (shape_type == b2Shape::e_edge)
			{
				b2EdgeShape* edge = dynamic_cast<b2EdgeShape*>(fixture->GetShape());
				b2Vec2 start = b2Mul(body_transform, edge->m_vertex1);
				b2Vec2 end = b2Mul(body_transform, edge->m_vertex2);

				auto line = std::make_shared<sf::VertexArray>(sf::Lines, 2);

				(*line)[0].position = box2d_position_to_sfml_position(start, window_height, parent->get_physics_to_graphics_scale());
				(*line)[1].position = box2d_position_to_sfml_position(end, window_height, parent->get_physics_to_graphics_scale());
				(*line)[0].color = sf::Color::Green;
				(*line)[1].color = sf::Color::Green;

				shapes.push_back(line);
			}

			//POLYGONS
			else if (shape_type == b2Shape::e_polygon)
			{
				b2PolygonShape* box2d_polygon = dynamic_cast<b2PolygonShape*>(fixture->GetShape());

				std::shared_ptr<sf::ConvexShape> polygon_shape = std::make_shared<sf::ConvexShape>();

				int number_of_vertices = box2d_polygon->m_count;

				polygon_shape->setPointCount(number_of_vertices);
				polygon_shape->setFillColor(sf::Color::Yellow);

				for (int index = 0; index < number_of_vertices; index++)
				{
					polygon_shape->setPoint
					(
						index,
						box2d_position_to_sfml_position(b2Mul(body_transform, box2d_polygon->m_vertices[index]), window_height, parent->get_physics_to_graphics_scale())
					);
				}

				shapes.push_back(polygon_shape);
			}
		}
		*/
	}
}