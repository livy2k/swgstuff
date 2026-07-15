/*
                Copyright <SWGEmu>
        See file COPYING for copying conditions.*/

#ifdef WITH_REST_API

#include "APIProxyVOIPManager.h"
#include "APIRequest.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/managers/object/ObjectManager.h"

namespace server {
 namespace web3 {

void APIProxyVOIPManager::handle(APIRequest& apiRequest) {
    auto path = apiRequest.getPathFieldString("action", true);
    
    if (path == "nearby") {
        getNearbyPlayers(apiRequest);
    } else {
        apiRequest.fail("Invalid action");
    }
}

void APIProxyVOIPManager::getNearbyPlayers(APIRequest& apiRequest) {
    if (!apiRequest.isMethodGET()) {
        apiRequest.fail("Only supports GET");
        return;
    }

    auto oid = apiRequest.getQueryFieldUnsignedLong("oid", true);
    auto range = apiRequest.getQueryFieldUnsignedLong("range", false, 50);

    auto zoneServer = getZoneServer();
    if (zoneServer == nullptr) {
        apiRequest.fail("Failed to getZoneServer");
        return;
    }

    auto objectManager = zoneServer->getObjectManager();
    if (objectManager == nullptr) {
        apiRequest.fail("Failed to getObjectManager");
        return;
    }

    auto obj = objectManager->getObject(oid);
    if (obj == nullptr || !obj->isCreatureObject()) {
        apiRequest.fail("Invalid object");
        return;
    }

    auto creature = cast<server::zone::objects::creature::CreatureObject*>(obj);
    auto zone = creature->getZone();
    if (zone == nullptr) {
        apiRequest.fail("Creature not in a zone");
        return;
    }

    auto result = JSONSerializationType::array();
    
    // We can iterate over the zone's active area or just nearby objects
    // Actually, CreatureObject has a `getNearbyObjects` method in the scene graph.
    // Let's assume a simplified approach for now: iterate nearby creatures in the zone.
    
    // Using zone->getNearbyObjects(...)
    // This is a bit complex as we need to define the type, etc.
    // I will implement a basic version that just returns the current player's own position as a test first,
    // or iterate through zone.
    
    auto pos = JSONSerializationType::object();
    pos["x"] = creature->getPositionX();
    pos["y"] = creature->getPositionY();
    pos["z"] = creature->getPositionZ();
    pos["oid"] = creature->getObjectID();
    pos["name"] = creature->getDisplayedName();
    
    result[0] = pos;
    
    apiRequest.success(result);
}

 }
}

#endif
