/*
 * ClientPublicInterface.cc
 *
 *  Created on: 3 Apr 2019
 *      Author: Faisal
 */

#include <string.h>
#include <omnetpp.h>
#include <bitset>
#include <iostream>

using namespace omnetpp;

class ClientPublicInterface : public cSimpleModule
{
protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

Define_Module(ClientPublicInterface);

void ClientPublicInterface::initialize()
{

}

void ClientPublicInterface::handleMessage(cMessage *msg)
{
    cGate *gate = msg->getArrivalGate();
    if(gate->isName("processorCommunication$i"))
    {
        send(msg,"externalCommunication$o");
    }
    else
    {
        send(msg,"processorCommunication$o");
    }
}






