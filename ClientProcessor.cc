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
    cModule *cmod = this->getParentModule();
    cMessage *msg = new cMessage(cmod->getFullName());
    EV<<cmod->getFullName();
    send(msg, "quantumInterfaceCommunication$o");
}
void ClientProcessor::handleMessage(cMessage *msg)
{
    send(msg,"quantumInterfaceCommunication$o");
}







