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
#include "ClientProcessor.h"

using namespace omnetpp;

Define_Module(ClientProcessor);

void ClientProcessor::initialize(int stage)
{
    if(stage == 1)
    {
        cPacket *discoveryPacket = new cPacket("networkDiscovery");
        discoveryPacket->setByteLength(1024);
        discoveryPacket->addPar("type").setStringValue("networkDiscovery");
        discoveryPacket->addPar("macAddress").setStringValue(this->getParentModule()->getSubmodule("clientPublicInterface")->par("macAddress"));
        discoveryPacket->addPar("ipAddress").setStringValue(this->getParentModule()->getSubmodule("clientPublicInterface")->par("ipAddress"));
        send(discoveryPacket, "publicInterfaceCommunication$o");
    } else if(stage == 2)
    {
        if(strcmp(this->getParentModule()->getParentModule()->par("source"), this->getParentModule()->getName()) == 0)
        {
            cPacket *discoveryPacket = new cPacket("initQkd");
            discoveryPacket->setByteLength(1024);
            discoveryPacket->addPar("type").setStringValue("initQkd");
            discoveryPacket->addPar("srcMAC").setStringValue(this->getParentModule()->getParentModule()->getSubmodule(this->getParentModule()->getParentModule()->par("source").stringValue())->getSubmodule("clientPublicInterface")->par("macAddress").stringValue());
            discoveryPacket->addPar("desMAC").setStringValue(this->getParentModule()->getParentModule()->getSubmodule(this->getParentModule()->getParentModule()->par("destination").stringValue())->getSubmodule("clientPublicInterface")->par("macAddress").stringValue());
            sendDelayed(discoveryPacket, 1000, "publicInterfaceCommunication$o");
        }
    }
}

int ClientProcessor::numInitStages() const
{
    return 3;
}

void ClientProcessor::handleMessage(cMessage *msg)
{
    if(strcmp(msg->par("type").stringValue(),"initQkdRespons") == 0)
    {
        delete msg;
    }
}
