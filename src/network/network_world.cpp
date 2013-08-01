#include "network/network_world.hpp"

#include "network/protocol_manager.hpp"
#include "network/protocols/synchronization_protocol.hpp"
#include "network/protocols/controller_events_protocol.hpp"
#include "modes/world.hpp"

#include "karts/controller/controller.hpp"

NetworkWorld::NetworkWorld()
{
    m_running = false;
    m_has_run = false;
}

NetworkWorld::~NetworkWorld()
{
}

void NetworkWorld::update(float dt)
{
    if (!m_has_run)
        m_has_run = true;
    SynchronizationProtocol* protocol = static_cast<SynchronizationProtocol*>(
            ProtocolManager::getInstance()->getProtocol(PROTOCOL_SYNCHRONIZATION));
    if (protocol) // if this protocol exists, that's that we play online
    {
        Log::debug("NetworkWorld", "Coutdown value is %f", protocol->getCountdown());
        if (protocol->getCountdown() > 0.0)
        {
            return;
        }
    }
    World::getWorld()->updateWorld(dt);
    if (World::getWorld()->getPhase() >= WorldStatus::RESULT_DISPLAY_PHASE) // means it's the end
    {
        // consider the world finished.
        stop();
        Log::info("NetworkWorld", "The game is considered finish.");
    }
}

void NetworkWorld::controllerAction(Controller* controller, PlayerAction action, int value)
{
    ControllerEventsProtocol* protocol = static_cast<ControllerEventsProtocol*>(
        ProtocolManager::getInstance()->getProtocol(PROTOCOL_CONTROLLER_EVENTS));
    if (protocol)
        protocol->controllerAction(controller, action, value);
}

bool NetworkWorld::isRaceOver()
{
    if (!World::getWorld())
        return false;
    return (World::getWorld()->getPhase() >= WorldStatus::RESULT_DISPLAY_PHASE);
}