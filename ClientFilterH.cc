/*
 * ClientFilterH.cc
 *
 *  Created on: 7 Apr 2019
 *      Author: Faisal
 */


#include <string.h>
#include <omnetpp.h>
#include <bitset>
#include <iostream>

using namespace omnetpp;

class ClientFilterH : public cSimpleModule
{
protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

Define_Module(ClientFilterH);

void ClientFilterH::initialize()
{

}
void ClientFilterH::handleMessage(cMessage *msg)
{
    //send(msg,"publicInterface$o");
}





