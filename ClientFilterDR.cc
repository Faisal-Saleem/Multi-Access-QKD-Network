/*
 * ClientFilterDR.cc
 *
 *  Created on: 7 Apr 2019
 *      Author: Faisal
 */


#include <string.h>
#include <omnetpp.h>
#include <bitset>
#include <iostream>

using namespace omnetpp;

class ClientFilterDR : public cSimpleModule
{
protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

Define_Module(ClientFilterDR);

void ClientFilterDR::initialize()
{

}
void ClientFilterDR::handleMessage(cMessage *msg)
{
    msg->setName("/");
    send(msg,"polarizedLight");
}






