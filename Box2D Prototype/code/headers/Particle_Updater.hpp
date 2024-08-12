/**
 * @author    Martin Pérez Villabrille
 * @copyright Copyright (c) 2023+ Martin Pérez Villabrille.
 *            All rights reserved
 */

#pragma once

#include "Particle_Pool.hpp"
#include "Particle.hpp"

namespace Mgine2D
{
	using vec2 = sf::Vector2f;

	/**
	 * @brief Handles updating particles in the particle pool.
	 */
	class Particle_Updater
	{
	public:
		/**
		 * @brief Updates the position and de-activation of the particles in active particle pool.
		 *
		 * @param pool The particle pool to update.
		 * @param dt The time step for the update.
		 */
		void update(Particle_Pool& pool, float dt)
		{
			for (size_t i = 0; i < pool.size(); ++i)
			{
				Particle& particle = pool.getParticle(i);

				if (particle.active)
				{
					particle.position += particle.speed * dt;

					particle.shape->setPosition(particle.position);

					particle.alpha -= 45 * dt;

					if (particle.alpha <= 0)
					{
						particle.active = false;
						pool.despawn_particle(particle, i);
					}
				}
			}
		}
	};
}