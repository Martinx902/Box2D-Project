/**
 * @author    Martin Pérez Villabrille
 * @copyright Copyright (c) 2023 + UDIT
 * @details   Mgine -- All rights reserved
 */

#pragma once

#include <string>
#include <tuple>
#include <map>

namespace Mgine2D
{
	/**
	 * @brief Structure representing a message and its data.
	 */
	struct Message
	{
		std::string id;			///< Identifier of the message
		std::string trigger;	///< Parameter of the message
	};
}