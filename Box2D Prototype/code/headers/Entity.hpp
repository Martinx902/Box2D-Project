/**
 * @author    Martin Pérez Villabrille
 * @copyright Copyright (c) 2023+ Martin Pérez Villabrille.
 *            All rights reserved
 */

#pragma once

#include <list>
#include <memory>

#include <Box2D/Box2D.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

namespace Mgine2D
{
	class Scene;

	/**
	 * @brief Represents an Entity on the scene, an actor that can be rendered and have some behaviours
	 */
	class Entity
	{
	protected:
		Scene* parent;               ///< Pointer to the parent scene.
		std::vector<b2Body*> bodies; ///< Vector of Box2D bodies associated with the entity.

	public:
		/**
		 * @brief Constructor for the Entity class.
		 *
		 * @param given_parent Pointer to the parent scene.
		 */
		Entity(Scene* given_parent) : parent(given_parent) {}

		/**
		 * @brief Virtual destructor for the Entity class.
		 */
		virtual ~Entity() {}

		/**
		 * @brief Adds a Box2D body to the entity.
		 *
		 * @param body Pointer to the Box2D body to add.
		 */
		virtual void add_body(b2Body* body)
		{
			bodies.push_back(body);
		}

		/**
		 * @brief Retrieves the vector of Box2D bodies associated with the entity.
		 *
		 * @return Vector of Box2D bodies.
		 */
		std::vector<b2Body*>& get_bodies()
		{
			return bodies;
		}

		/**
		 * @brief Virtual function to update the entity.
		 */
		virtual void update() {}

		/**
		 * @brief Virtual function to initialize the entity. Most of the times Box2D configurations and visuals.
		 */
		virtual void initialize() {}
	};
}