/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef ROLLCOMMAND_H_
#define ROLLCOMMAND_H_

#include "QueueCommand.h"
#include "server/chat/ChatManager.h"

class RollCommand : public QueueCommand {
public:

	RollCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (!creature->isPlayerCreature())
			return GENERALERROR;

		int maxRoll = 100;
		String args = arguments.toString();

		if (!args.isEmpty()) {
			try {
				maxRoll = Integer::valueOf(args);
			} catch (const Exception& e) {
				maxRoll = 100;
			}
		}

		if (maxRoll <= 0) {
			creature->sendSystemMessage("Invalid roll range. Please use a number greater than 0.");
			return INVALIDPARAMETERS;
		}

		int roll = System::random(maxRoll - 1) + 1;

		StringBuffer message;
		message << "rolls " << roll << " (1-" << maxRoll << ").";

		ChatManager* chatManager = server->getZoneServer()->getChatManager();

		if (chatManager != nullptr) {
			UnicodeString rollMsg(message.toString());
			chatManager->broadcastChatMessage(creature, rollMsg, 0, 0, 0);
		}

		return SUCCESS;
	}

};

#endif //ROLLCOMMAND_H_
