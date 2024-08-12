/**
 * @author    Martin Pérez Villabrille
 * @copyright Copyright (c) 2023+ Martin Pérez Villabrille.
 *            All rights reserved
 */

#pragma once

#include <string>
#include <map>
#include <memory>
#include <functional>

#include <Box2D/Box2D.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "Entity.hpp"
#include "Message_Dispatcher.hpp"
#include "Message_Listener.hpp"
#include "UserData.hpp"

namespace Mgine2D
{
	/**
	 * @brief Collection of all entities on the game, manages contacts and updates the render and physics.
	 */
	class Scene
	{
	private:

		/**
		 * @brief Internal class to handle contact listening for the scene's physics using Box2D collision system.
		 */
		class Contact_Listener : public b2ContactListener
		{
			Scene* scene;                       ///< Pointer to the parent scene.

			b2Fixture* sensorFixture = nullptr; ///< Pointer to the first sensor fixture involved in the contact.

			b2Fixture* otherFixture = nullptr;  ///< Pointer to the other fixture involved in the contact.

		public:

			/**
			 * @brief Constructor for the Contact_Listener class.
			 *
			 * @param given_scene Pointer to the parent scene.
			 */
			Contact_Listener(Scene* given_scene) : scene(given_scene) { }

			/**
			 * @brief Called when two fixtures begin to touch.
			 *
			 * @param contact Pointer to the contact information.
			 */
            void BeginContact(b2Contact* contact) override;
		};

	private:

		Message_Dispatcher* message_dispatcher;					 ///< Manages message dispatching between listeners.

		Contact_Listener* contact_listener;						 ///< Listener for physics contact events.

		b2World* physics_world;									 ///< Pointer to the Box2D world for physics simulation.

		std::map<std::string, std::shared_ptr<Entity>> entities; ///< Map of entities in the scene.

		sf::RenderWindow* window;								 ///< Pointer to the SFML render window.

		bool running;											 ///< Flag indicating if the scene is running.

		const float physics_to_graphics_scale = 60.f;			 ///< Scale factor for converting Box2D coordinates to SFML coordinates.

		std::function<void(Scene&)> configure_scene_ptr;		 ///< Function pointer for configuring the scene.

	public:

		/**
		 * @brief Constructor for the Scene class.
		 *
		 * @param given_window Pointer to the SFML render window.
		 * @param funcPtr Function pointer for configuring the scene.
		 */
		Scene(sf::RenderWindow* given_window, std::function<void(Scene&)> funcPtr);

		/**
		 * @brief Runs the main loop of the scene, updating, rendering and simulating physics.
		 */
		void run();

		/**
		 * @brief Adds an entity to the scene.
		 *
		 * @param id ID of the entity.
		 * @param entity Pointer to the entity object.
		 */
		void add_entity(const std::string& id, std::shared_ptr<Entity> entity)
		{
			if (!entities[id])
				entities[id] = entity;
		}

		/**
		 * @brief Retrieves an entity from the scene by its ID.
		 *
		 * @param id ID of the entity to retrieve.
		 * @return Pointer to the entity if found, nullptr otherwise.
		 */
		std::shared_ptr<Entity> get_entity_by_id(const std::string& id)
		{
			return entities[id];
		}

		/**
		 * @brief Adds a message listener to the message dispatcher.
		 *
		 * @param listener Reference to the listener object.
		 * @param id ID of the message to listen for.
		 */
		void add_message_listener(Message_Listener& listener, const std::string& id)
		{
			message_dispatcher->add(listener, id);
		}

		/**
		 * @brief Retrieves the Box2D physics world.
		 *
		 * @return Pointer to the Box2D world.
		 */
		b2World* get_physic_world()
		{
			return physics_world;
		}

		/**
		 * @brief Retrieves the scale factor from Box2D to SFML.
		 *
		 * @return The physics-to-graphics scale factor.
		 */
		float get_physics_to_graphics_scale()
		{
			return physics_to_graphics_scale;
		}

		/**
		 * @brief Retrieves the height of the window in graphics coordinates.
		 *
		 * @return The height of the window.
		 */
		const float get_window_height() const
		{
			return float(window->getSize().y);
		}

		/**
		 * @brief Retrieves a pointer to the SFML render window.
		 *
		 * @return Pointer to the render window.
		 */
		const sf::RenderWindow* get_window() const
		{
			return window;
		}

		/**
		 * @brief Retrieves a non-const pointer to the SFML render window.
		 *
		 * @return Non-const pointer to the render window.
		 */
		sf::RenderWindow* get_window()
		{
			return window;
		}

		/**
		 * @brief Retrieves the message dispatcher.
		 *
		 * @return Pointer to the message dispatcher.
		 */
		Message_Dispatcher* get_message_dispatcher()
		{
			return message_dispatcher;
		}

	private:

		/**
		 * @brief Processes input events in the scene.
		 */
		void process_events();

		/**
		 * @brief Calls all of the update methods of the entities on scene.
		 */
		void update_entities();

		/**
		 * @brief Initializes the scene. Reseting the entities and parameters needed to work.
		 */
		void initialize_scene();

		/**
		 * @brief Updates the Box2D world simulating a frame of physics.
		 *
		 * @param t Time elapsed since the last update.
		 */
		void update_world(float t);

		/**
		 * @brief Draws the specified bodies on the render window.
		 *
		 * @param bodies Vector of Box2D bodies to draw.
		 * @param renderer Reference to the SFML render window.
		 * @param scale Scale factor for converting physics coordinates to graphics coordinates.
		 */
		void draw_entity(std::vector<b2Body*>& bodies, sf::RenderWindow& renderer, float scale);

		/**
		 * @brief Converts a Box2D position to an SFML position.
		 *
		 * @param box2d_position The position in Box2D coordinates.
		 * @param window_height The height of the SFML window.
		 * @param scale Scale factor for converting physics coordinates to graphics coordinates.
		 * @return The position in SFML coordinates.
		 */
		inline sf::Vector2f box2d_position_to_sfml_position(const b2Vec2& box2d_position, float window_height, float scale)
		{
			return sf::Vector2f(box2d_position.x * scale, window_height - box2d_position.y * scale);
		}
	};
}