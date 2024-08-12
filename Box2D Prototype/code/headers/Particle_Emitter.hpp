/**
 * @author    Martin Pérez Villabrille
 * @copyright Copyright (c) 2023+ Martin Pérez Villabrille.
 *            All rights reserved
 */

#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <random>

#include "Particle.hpp"
#include "Particle_Pool.hpp"

namespace Mgine2D
{
	using vec2 = sf::Vector2f;

	/**
	 * @brief Represents an emitter of particles that assigns random values to particles when emmitted.
	 */
	class Particle_Emitter
	{
		vec2 position;                  ///< Position of the emitter.
		float minSpeed;                 ///< Minimum speed of emitted particles.
		float maxSpeed;                 ///< Maximum speed of emitted particles.

		std::random_device rd;								///< Random device for generating random numbers.
		std::mt19937 gen;									///< Mersenne Twister random number generator.
		std::uniform_real_distribution<float> distribution; ///< Uniform distribution for speed.

	public:
		/**
		 * @brief Constructor for the Particle_Emitter class.
		 *
		 * @param position The position of the emitter.
		 * @param minSpeed The minimum speed of emitted particles.
		 * @param maxSpeed The maximum speed of emitted particles.
		 */
		Particle_Emitter
		(
			const vec2& position,
			float given_min_speed,
			float given_max_speed
		)
			:
			position(position),
			rd(),
			gen(rd()),
            minSpeed(given_min_speed),
            maxSpeed(given_max_speed),
			distribution(minSpeed, maxSpeed)
		{}

		/**
		 * @brief Creates a new particle at the emitter's position.
		 *
		 * @return The created particle.
		 */
		Particle create_particle()
		{
			Particle* particle = new Particle();

			particle->position = position;

			particle->shape->setPosition(position);

			return *particle;
		}

		/**
		 * @brief Emits a particle with random velocity from the particle pool.
		 *
		 * @param direction The direction of emission.
		 * @param pool The particle pool from which to spawn the particle.
		 * @return The emitted particle.
		 */
		Particle emit_particle(const vec2& direction, Particle_Pool& pool)
		{
			Particle particle = pool.spawn_particle();

			particle.position = position;

			particle.shape->setPosition(particle.position);

			particle.speed = vec2((rand() % 20) * direction.x, (rand() % 20) * direction.y);

			particle.active = true;

			particle.alpha = 255;

			return particle;
		}
	};
}