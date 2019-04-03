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
    cModule *cmod = this->getParentModule();
    cMessage *msg = new cMessage(cmod->getFullName());
    send(msg, "externalCommunication$o");
}
void ClientPublicInterface::handleMessage(cMessage *msg)
{
    send(msg, "externalCommunication$o");
}






