/*
                Copyright <SWGEmu>
        See file COPYING for copying conditions.*/

/**
 * @author      : Junie (AI Agent)
 * @file        : APIProxyVOIPManager.h
 */

#pragma once

#include "BaseAPIProxy.h"

namespace server {
 namespace web3 {
	class APIRequest;

	class APIProxyVOIPManager : public BaseAPIProxy {
	public:
		APIProxyVOIPManager() : BaseAPIProxy("VOIPManager")  {
		}

		void handle(APIRequest& apiRequest);
		void getNearbyPlayers(APIRequest& apiRequest);
	};
 }
}
