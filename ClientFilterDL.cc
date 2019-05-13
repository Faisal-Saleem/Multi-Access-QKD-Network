/*
 * ClientFilterDL.cc
 *
 *  Created on: 7 Apr 2019
 *      Author: Faisal
 *
 */


#include <string.h>
#include <omnetpp.h>
#include <bitset>
#include <iostream>

using namespace omnetpp;

class ClientFilterDL : public cSimpleModule
{
protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

Define_Module(ClientFilterDL);

void ClientFilterDL::initialize()
{

}
void ClientFilterDL::handleMessage(cMessage *msg)
{
    msg->setName("\\");
    send(msg,"polarizedLight");
}






