/**
 * @author    Martin Pérez Villabrille
 * @copyright Copyright (c) 2023+ Martin Pérez Villabrille.
 *            All rights reserved
 */

#pragma once

#include <vector>
#include <queue>

#include "Particle.hpp"

namespace Mgine2D
{
	using vec2 = sf::Vector2f;

	/**
	 * @brief Manages a pool of particles for reuse.
	 */
	class Particle_Pool
	{
	public:
		std::queue<Particle> particles;			///< Queue of particles available for reuse.
		std::vector<Particle> active_particles; ///< Vector of active particles.

	public:
		/**
		 * @brief Constructor for the Particle_Pool class.
		 *
		 * @param initialSize The initial size of the particle pool.
		 */
		Particle_Pool(size_t initialSize)
		{ }

		/**
		 * @brief Retrieves a particle by index from the active particles.
		 *
		 * @param index The index of the particle to retrieve.
		 * @return Reference to the particle.
		 */
		Particle& getParticle(size_t index)
		{
			return active_particles[index];
		}

		/**
		 * @brief Gets the size of the active particles vector.
		 *
		 * @return The size of the active particles vector.
		 */
		size_t size() const
		{
			return active_particles.size();
		}

		/**
		 * @brief Creates a new particle in the particle pool.
		 *
		 * @param particle The particle to create.
		 */
		void create_particle(const Particle& particle)
		{
			particles.push(particle);
		}

		/**
		 * @brief Checks if the particle queue is empty.
		 *
		 * @return True if the particle queue is empty, false otherwise.
		 */
		bool queue_is_empty()
		{
			return particles.empty();
		}

		/**
		 * @brief Takes a particle for the particle list to be activated
		 *
		 * @return The spawned particle.
		 */
		Particle spawn_particle()
		{
			Particle particle = particles.front();
			particles.pop();

			return particle;
		}

		/**
		 * @brief Adds a particle to the active particles list.
		 *
		 * @param particle The particle to add.
		 */
		void add_active_particle(Particle& particle)
		{
			active_particles.push_back(particle);
		}

		/**
		 * @brief Despawns a particle from the active particles list and sends it to the particle list to be used again
		 *
		 * @param particle The particle to despawn.
		 * @param index The index of the particle in the active particles list.
		 */
		void despawn_particle(Particle& particle, size_t index)
		{
			particles.push(particle);
			active_particles.erase(active_particles.begin() + index);
		}
	};
}