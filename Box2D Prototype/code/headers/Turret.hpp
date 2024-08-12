/**
 * @author    Martin Pérez Villabrille
 * @copyright Copyright (c) 2023+ Martin Pérez Villabrille.
 *            All rights reserved
 */

#pragma once

#include "Entity.hpp"
#include "Message_Listener.hpp"
#include "Message.hpp"

namespace Mgine2D
{
	/**
	 * @brief Class representing the turret entity of the scene.
	 */
	class Turret : public Entity, public Message_Listener
	{
		b2RevoluteJoint* joint; ///< Pointer to the turret's revolute joint.

	public:
		/**
		 * @brief Constructor for the Turret class.
		 * @param given_parent Pointer to the parent scene.
		 */
		Turret(Scene* given_parent) : joint(nullptr), Entity(given_parent)
		{}

	private:
		/**
		 * @brief Creates the visuals and sets up the configuration for the turret
		 */
		void initialize() override;

		/**
		 * @brief Spawns the balls that are used as triggers of the scene and placed on top of the turret
		 * @param world Pointer to the Box2D world.
		 * @param ballFixtureDef Definition of the ball's fixture.
		 */
		void spawn_balls(b2World* world, b2FixtureDef& ballFixtureDef);

		/**
		 * @brief Method to activate the turret and drop the balls.
		 */
		void turn_turret();

	public:
		/**
		 * @brief Method to handle incoming messages.
		 * @param message Reference to the incoming message.
		 */
		void handle(const Message& message) override;
	};
}