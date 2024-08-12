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

namespace Mgine2D
{
	using vec2 = sf::Vector2f;

	/**
	 * @brief Stores the variables and characteristics of a particle.
	 */
	struct Particle
	{
		vec2 position;                          ///< Position of the particle.
		std::shared_ptr<sf::Shape> shape;       ///< SFML shape of the particle.
		vec2 speed;                             ///< Speed of the particle.
		float alpha;                            ///< Alpha value of the particle, not really transparency.
		bool active;                            ///< Whether the particle is active or not.

		/**
		 * @brief Constructs a particle with default properties and random color.
		 */
		Particle()
		{
			shape = std::make_shared<sf::CircleShape>(2.0f);

			// Generate random RGB values in the range [0, 255] for the color
			sf::Uint8 r = static_cast<sf::Uint8>(rand() % 256);
			sf::Uint8 g = static_cast<sf::Uint8>(rand() % 256);
			sf::Uint8 b = static_cast<sf::Uint8>(rand() % 256);

			alpha = float(rand());

			shape->setFillColor(sf::Color(r, g, b));
			active = true;
		}
	};
}