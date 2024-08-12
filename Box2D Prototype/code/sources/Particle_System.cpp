/**
  * @author    Martin Pérez Villabrille
  * @copyright Copyright (c) 2023+ Martin Pérez Villabrille.
  *            All rights reserved
  */

#include "../headers/Particle_System.hpp"
#include "../headers/Scene.hpp"

namespace Mgine2D
{
	void Particle_System::update()
	{
		if (start)
		{
			update_system(frame_rate);
			render(*parent->get_window());
		}
	}

	void Particle_System::initialize()
	{
		//particle_pool = new Particle_Pool(particle_count);

		parent->add_message_listener(*this, "trigger");

		for (size_t i = 0; i < particle_count; i++)
		{
			particle_pool->create_particle(emitter.create_particle());
		}
	}
}