# Proximity VOIP Implementation Options

There are two main ways to implement proximity VOIP in SWGEmu:

## 1. Server-Backed (REST API)
This approach uses the built-in Core3 REST API to retrieve proximity data.
- **How it works:** Your client (or a bridge app) queries the Core3 REST API (`/v1/voip/nearby`) to get the positions of nearby players.
- **Pros:** Does not require memory reading; compatible with any client.
- **Cons:** Requires a server-side API call, which can have some latency compared to raw memory reading.

## 2. Client-Local Only (Memory Reading / Bridge)
This approach reads the game's memory directly to find player coordinates.
- **How it works:** A separate bridge application (running locally) attaches to the SWG client process, reads the `X, Y, Z` memory addresses for the player and nearby entities, and pushes them to a VOIP client (e.g., Mumble/TeamSpeak).
- **Pros:** Zero network latency for position updates; works entirely offline from the server API.
- **Cons:** Requires reverse-engineering (finding memory offsets); can be flagged as "cheating" if not implemented carefully (as memory reading is often used for bots/hacks).

### Implementing the Client-Local Bridge
If you choose the Client-Local Only path, you will need to build an external tool. We have provided a skeleton Python script in `tools/` that demonstrates the architecture.

**Warning:** You will need to use tools like `Cheat Engine` or `ReClass.NET` to find the current memory addresses for `Player` coordinates in your specific version of the SWG client.

**Architecture:**
1.  **Memory Scanner:** Reads client memory to get `Player` X/Y/Z.
2.  **Entity Iterator:** Scans nearby memory blocks for other players.
3.  **VOIP Link:** Uses a Mumble Link API or similar to feed coordinates to the VOIP audio engine.

Refer to `tools/bridge-skeleton.py` for a template.
