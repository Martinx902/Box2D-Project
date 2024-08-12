/**
 * @author    Martin Pérez Villabrille
 * @copyright Copyright (c) 2023+ Martin Pérez Villabrille.
 *            All rights reserved
 */

#pragma once

#include <vector>

#include <Box2D/Box2D.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "Entity.hpp"
#include "UserData.hpp"

namespace Mgine2D
{
    /**
     * @brief Vehicle entity of the scene
     */
    class Vehicle : public Entity
    {
        float movement_speed;               ///< Speed of movement for the vehicle.
        bool trunk_is_open;                 ///< Flag indicating if the trunk is open.

        b2RevoluteJoint* right_wheel_joint; ///< Joint for the right wheel.
        b2RevoluteJoint* left_wheel_joint;  ///< Joint for the left wheel.
        b2RevoluteJoint* trunk_joint;       ///< Joint for the trunk.

        /**
         * @brief Enum defining movement directions for the vehicle.
         */
        enum Movement
        {
            RIGHT = -1,
            BRAKE = 0,
            LEFT = 1
        };

    public:
        /**
         * @brief Constructor for the Vehicle class.
         * @param given_parent Pointer to the parent Scene.
         * @param given_speed Initial movement speed of the vehicle.
         */
        Vehicle
        (
            Scene* given_parent,
            float given_speed
        )
            :
            Entity(given_parent),
            movement_speed(given_speed),
            right_wheel_joint(nullptr),
            left_wheel_joint(nullptr),
            trunk_joint(nullptr),
            trunk_is_open(false)
        {
        }

        /**
         * @brief Register the input of the user for the player, movement and managing the trunk
         */
        void update() override;

        /**
         * @brief Creates the visuals and sets up the configuration for the car
         */
        void initialize() override;

    private:

        /**
         * @brief Move the vehicle in the specified direction.
         * @param movement_direction Direction of movement.
         */
        void move(Movement movement_direction);

        /**
         * @brief Opens and closes the trunk of the vehicle based on its actual state
         */
        void activate_trunk();
    };
}