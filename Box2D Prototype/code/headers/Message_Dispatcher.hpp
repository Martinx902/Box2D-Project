/**
 * @author    Martin Pérez Villabrille
 * @copyright Copyright (c) 2023 + UDIT
 * @details   Mgine -- All rights reserved
 */

#pragma once

#include <map>
#include <list>
#include <string>

#include "Message.hpp"
#include "Message_Listener.hpp"

namespace Mgine2D
{
	class Scene;

	/**
	 * @brief Dispatches messages to listeners.
	 */
	class Message_Dispatcher
	{
		Scene* parent;

		std::list< Message > messages;													///< Queue of messages to be dispatched

		std::map <std::string, std::list < Message_Listener* > > messageListeners;		///< Map of message IDs to their listeners

	public:

		/**
		 * @brief Constructs a Message Dispatcher object with a given priority and scene.
		 *
		 * @param given_priority The priority of the task.
		 * @param given_scene    Pointer to the scene.
		 */
		Message_Dispatcher(Scene* given_scene) : parent(given_scene) {}

		/**
		 * @brief Adds a message listener for a specific message ID.
		 *
		 * @param listener   The listener object.
		 * @param message_id The ID of the message to listen for.
		 */
		void add(Message_Listener& listener, const std::string& message_id)
		{
			messageListeners[message_id].push_back(&listener);
		}

		/**
		 * @brief Sends a message to be dispatched.
		 *
		 * @param message The message to be dispatched.
		 */
		void send(const Message& message)
		{
			messages.push_back(message);
		}

		/**
		 * @brief Executes the message dispatcher, dispatching messages to listeners.
		 *
		 * @param t The time elapsed since the last execution.
		 */
		void execute(float t);
	};
}