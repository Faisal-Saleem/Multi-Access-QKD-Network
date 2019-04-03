/*
 * Client.cc
 *
 *  Created on: 3 Apr 2019
 *      Author: Faisal
 */

#include <string.h>
#include <omnetpp.h>
#include <bitset>
#include <iostream>

using namespace omnetpp;

class Client : public cSimpleModule
{
protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

Define_Module(Client);

void Client::initialize()
{

}
void Client::handleMessage(cMessage *msg)
{
    send(msg,"publicInterface$o");
}




