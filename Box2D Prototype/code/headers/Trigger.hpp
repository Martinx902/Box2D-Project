/**
 * @author    Martin Pérez Villabrille
 * @copyright Copyright (c) 2023+ Martin Pérez Villabrille.
 *            All rights reserved
 */

#pragma once

#include <string>

#include "Entity.hpp"
#include "UserData.hpp"

namespace Mgine2D
{
	/**
	 * @brief Class representing a customizable trigger for the scene
	 */
	class Trigger : public Entity
	{
		User_Data* user_data; ///< Pointer to user data associated with the trigger. Is used to call methods on other entities based on the id.
		b2Vec2 position;      ///< Position of the trigger.
		b2Vec2 scale;		  ///< Scale of the trigger.
		b2Body* body;		  ///< Pointer to the Box2D body representing the trigger.
		bool visualize;		  ///< Flag indicating whether the trigger is going to be renderer or not

	public:
		/**
		 * @brief Constructor for the Trigger class.
		 * @param given_parent Pointer to the parent scene.
		 * @param id Id of the event this trigger calls when activated.
		 * @param given_position Position of the trigger.
		 * @param given_scale Scale of the trigger.
		 * @param _visualize Flag indicating whether the trigger is rendered (default is false).
		 */
		Trigger
		(
			Scene* given_parent,
			const std::string& id,
			b2Vec2 given_position,
			b2Vec2 given_scale,
			bool _visualize = false
		)
			:
			Entity(given_parent),
			position(given_position),
			scale(given_scale),
			visualize(_visualize)
		{
			user_data = new User_Data;
			user_data->id = id;
		}

		/**
		 * @brief Method to initialize the trigger.
		 */
		void initialize() override;

		/**
		 * @brief Method to disable the trigger.
		 */
		void disable()
		{
			body->SetEnabled(false);
		}
	};
}