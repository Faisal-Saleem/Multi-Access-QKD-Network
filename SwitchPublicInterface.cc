/*
 * ProcessingQueue.cc
 *
 *  Created on: 3 Apr 2019
 *      Author: Faisal
 */

#include <string.h>
#include <omnetpp.h>
#include <bitset>
#include <iostream>
#include "SwitchMemory.h"

using namespace omnetpp;

class SwitchPublicInterface : public cSimpleModule
{
protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

Define_Module(SwitchPublicInterface);

void SwitchPublicInterface::initialize()
{

}

void SwitchPublicInterface::handleMessage(cMessage *msg)
{
    cGate *gate = msg->getArrivalGate();
    if(gate->isName("publicChannelCommunication$i"))
    {
        msg->addPar("interface").setStringValue(this->getName());
        msg->addPar("srcInterfaceMacAddress").setStringValue(this->par("macAddress").stringValue());
        send(msg,"processorCommuniation$o");
    }
    else
    {
        send(msg,"publicChannelCommunication$o");
    }
}






