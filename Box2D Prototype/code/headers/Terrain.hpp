/**
 * @author    Martin Pérez Villabrille
 * @copyright Copyright (c) 2023+ Martin Pérez Villabrille.
 *            All rights reserved
 */

#pragma once

#include "Entity.hpp"
#include "Particle_System.hpp"

namespace Mgine2D
{
	/**
	 * @brief Class representing the static entites of background of the scene.
	 */
	class Terrain : public Entity
	{
	public:
		/**
		 * @brief Constructor for the Terrain class.
		 * @param given_parent Pointer to the parent scene.
		 */
		Terrain(Scene* given_parent) : Entity(given_parent)
		{}

	private:
		/**
		 * @brief Method to configure the parameters of the trigger
		 */
		void initialize() override;
	};
}