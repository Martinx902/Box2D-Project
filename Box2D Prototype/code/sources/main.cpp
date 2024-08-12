/**
  * @author    Martin Pérez Villabrille
  * @copyright Copyright (c) 2023+ Martin Pérez Villabrille.
  *            All rights reserved
  */

  /* ---------------------------------/
  |*        ---CONTROLS---            |
  |*                                  |
  |*         A - RIGHT                |
  |*         D - LEFT                 |
  |*         SPACE - BRAKE            |
  |*         V - ACTIVATE TRUNK       |
  |*         R - RESTART              |
  /----------------------------------*/

#include "../headers/Scene.hpp"
#include "../headers/Entity.hpp"
#include "../headers/Vehicle.hpp"
#include "../headers/Terrain.hpp"
#include "../headers/Turret.hpp"
#include "../headers/Elevator.hpp"
#include "../headers/Trigger.hpp"
#include "../headers/Particle_System.hpp"

#include <string>
#include <memory>
#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;
using namespace Mgine2D;

void create_vehicle(Scene& scene)
{
    auto vehicle = make_shared<Vehicle>(&scene, 30.f);

	scene.add_entity("vehicle", vehicle);
}

void create_terrain(Scene& scene)
{
    auto terrain = make_shared<Terrain>(&scene);

	scene.add_entity("terrain", terrain);
}

void create_elevator(Scene& scene)
{
    auto elevator = make_shared<Elevator>(&scene);

	scene.add_entity("elevator", elevator);
}

void create_turret(Scene& scene)
{
    auto turret = make_shared<Turret>(&scene);

	scene.add_entity("turret", turret);
}

void create_triggers(Scene& scene)
{
	//TURRET TRIGGER

    auto turret_trigger = make_shared<Trigger>(&scene, "turret", b2Vec2(28.f, 3.f), b2Vec2(1.f, 1.f));

	scene.add_entity("turret_trigger", turret_trigger);

	//RESET TRIGGER

    auto reset_trigger = make_shared<Trigger>(&scene, "reset", b2Vec2(13.9f, -3.f), b2Vec2(2.6f, 0.2f));

	scene.add_entity("reset_trigger", reset_trigger);

	//END TRIGGER

    auto end_trigger = make_shared<Trigger>(&scene, "end", b2Vec2(6.9f, 8.2f), b2Vec2(1.2f, 0.5f));

	scene.add_entity("end_trigger", end_trigger);
}

void create_particle_systems(Scene& scene)
{
	auto ps1 = make_shared<Particle_System>(&scene, vec2(550.f, 180.f), 300, 5.f, 12.f);
    auto ps2 = make_shared<Particle_System>(&scene, vec2(650.f, 180.f), 300, 5.f, 12.f);

	scene.add_entity("ps1", ps1);
	scene.add_entity("ps2", ps2);
}

void configure(Scene& scene)
{
	create_vehicle(scene);
	create_terrain(scene);
	create_turret(scene);
	create_elevator(scene);
	create_triggers(scene);
	create_particle_systems(scene);
}

int main()
{
	RenderWindow window(VideoMode(1710, 700), "Practica 1 - Animacion 3D", Style::Titlebar | Style::Close, ContextSettings(32));

	void (*configure_scene_ptr)(Scene&);

	configure_scene_ptr = &configure;

	Scene scene(&window, configure_scene_ptr);

	scene.run();

	return EXIT_SUCCESS;
}