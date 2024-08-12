/**
  * @author    Martin Pérez Villabrille
  * @copyright Copyright (c) 2023+ Martin Pérez Villabrille.
  *            All rights reserved
  */

#pragma once

#include "Entity.hpp"
#include "Message_Listener.hpp"
#include "Message.hpp"

#include "Particle.hpp"
#include "Particle_Emitter.hpp"
#include "Particle_Updater.hpp"
#include "Particle_Renderer.hpp"

namespace Mgine2D
{
	using vec2 = sf::Vector2f;
	/**
	* @brief Represents a system for managing particles within the scene.
	*/
	class Particle_System : public Entity, public Message_Listener
	{
		Particle_Pool* particle_pool;    ///< Pointer to the particle pool.
		Particle_Emitter emitter;        ///< Particle emitter associated with the system.
		Particle_Updater updater;        ///< Particle updater responsible for updating particle properties.
		Particle_Renderer renderer;      ///< Particle renderer for rendering particles.

		float frame_rate;                 ///< Frame rate of the particle system.
		int particle_count;               ///< Number of particles in the system.
		bool start;                       ///< Flag indicating whether the system has started.

	public:
		/**
		 * @brief Constructor for the Particle_System class.
		 *
		 * @param given_parent Pointer to the parent scene.
		 * @param emitterPos Initial position of the particle emitter.
		 * @param particle_count Number of particles in the system.
		 * @param minSpeed Minimum speed for emitted particles.
		 * @param maxSpeed Maximum speed for emitted particles.
		 */
		Particle_System
		(
			Scene* given_parent,
			const vec2& emitterPos,
			int given_particle_count,
			float minSpeed,
			float maxSpeed
		)
			:
			Entity(given_parent),
            frame_rate(1/60.f),
            particle_count(given_particle_count),
			emitter(emitterPos, minSpeed, maxSpeed),
            start(false),
            particle_pool(new Particle_Pool(particle_count))
		{
		}

		/**
		 * @brief Updates the particles and renders them.
		 */
		void update() override;

		/**
		 * @brief Sets up the particle pool instantiating all the particles on it.
		 */
		void initialize();

		/**
		 * @brief Updates the particle system with the given time step.
		 *
		 * @param dt The time step for the update.
		 */
		void update_system(float dt)
		{
			if (!particle_pool->queue_is_empty())
			{
				particle_pool->add_active_particle(emitter.emit_particle(vec2(0.1f, -2.f), *particle_pool));
			}
			updater.update(*particle_pool, dt);
		}

		/**
		 * @brief Renders the particle system.
		 *
		 * @param renderer Reference to the SFML render window.
		 */
		void render(sf::RenderWindow& renderer)
		{
			this->renderer.render(renderer, particle_pool->active_particles);
		}

		/**
		 * @brief Handles incoming messages.
		 *
		 * @param message The message to handle.
		 */
		void handle(const Message& message) override
		{
			if (message.trigger == "end")
				start = true;
		}
	};
}