/**
  * @author    Martin Pérez Villabrille
  * @copyright Copyright (c) 2023+ Martin Pérez Villabrille.
  *            All rights reserved
  */

#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

namespace Mgine2D
{
	/**
	 * @brief Handles rendering particles on the screen.
	 */
	class Particle_Renderer
	{
	public:
		/**
		 * @brief Renders active particles on the screen.
		 *
		 * @param renderer Reference to the SFML render window.
		 * @param active_particles Vector containing active particles to render.
		 */
		void render(sf::RenderWindow& renderer, std::vector<Particle>& active_particles)
		{
			for (const auto& particle : active_particles)
			{
				renderer.draw(*particle.shape);
			}
		}
	};
}