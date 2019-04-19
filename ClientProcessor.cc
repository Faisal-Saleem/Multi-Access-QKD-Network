/*
 * ClientProcessor.cc
 *
 *  Created on: 7 Apr 2019
 *      Author: Faisal
 */

#include <string.h>
#include <omnetpp.h>
#include <bitset>
#include <iostream>

using namespace omnetpp;

class ClientProcessor : public cSimpleModule
{
protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

Define_Module(ClientProcessor);

void ClientProcessor::initialize()
{
    cPacket *discoveryPacket = new cPacket("data");
    discoveryPacket->setByteLength(1024);
    discoveryPacket->addPar("type").setStringValue("networkDiscovery");
    discoveryPacket->addPar("macAddress").setStringValue(this->getParentModule()->getSubmodule("clientPublicInterface")->par("macAddress"));
    discoveryPacket->addPar("ipAddress").setStringValue(this->getParentModule()->getSubmodule("clientPublicInterface")->par("ipAddress"));
    send(discoveryPacket, "publicInterfaceCommunication$o");
}
void ClientProcessor::handleMessage(cMessage *msg)
{
    EV<<" Client MAC Address : "<<msg->par("macAddress").stringValue();
    //send(msg,"quantumInterfaceCommunication$o");
}







