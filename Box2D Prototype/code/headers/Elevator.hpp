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
	 * @brief Represents an elevator entity in the game scene.
	 */
	class Elevator : public Entity, public Message_Listener
	{
		b2Body* platform_body;              ///< Pointer to the Box2D body representing the elevator platform.
		b2Body* trigger_body;               ///< Pointer to the Box2D body representing the elevator trigger.
		bool elevator_instanciated; ///< Flag indicating whether the elevator has been instantiated.
		bool elevator_moving;       ///< Flag indicating whether the elevator is moving.

	public:
		/**
		 * @brief Constructor for the Elevator class.
		 *
		 * @param given_parent Pointer to the parent scene.
		 */
		Elevator(Scene* given_parent) 
            : 
            platform_body(nullptr), 
            trigger_body(nullptr), 
            elevator_instanciated(false),
            elevator_moving(false), 
            Entity(given_parent) 
        {}

	private:
		/**
		 * @brief Sets up the visuals and configuration of Box2D
		 */
		void initialize() override;

		/**
		 * @brief Enables the visuals of the elevator and activates the trigger so it can be used
		 */
		void spawn_elevator();

		/**
		 * @brief Makes the elevator go up when triggered its use.
		 */
		void activate_elevator();

	public:
		/**
		 * @brief When activated moves the elevator to a desired position
		 */
		void update() override;

		/**
		 * @brief Handles incoming messages.
		 *
		 * @param message The incoming message.
		 */
		void handle(const Message& message) override;
	};
}