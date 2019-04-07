/*
 * Switch.cc
 *
 *  Created on: 7 Apr 2019
 *      Author: Faisal
 */


#include <string.h>
#include <omnetpp.h>
#include <bitset>
#include <iostream>

using namespace omnetpp;

class Switch : public cSimpleModule
{
protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

Define_Module(Switch);

void Switch::initialize()
{
    EV<<"Test";
}
void Switch::handleMessage(cMessage *msg)
{
    //send(msg,"publicInterface$o");
}






