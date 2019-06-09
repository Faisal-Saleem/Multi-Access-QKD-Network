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

class SwitchQuantumInterface : public cSimpleModule
{
protected:
    virtual void initialize(int stage) override;
    virtual int numInitStages() const override;
    virtual void handleMessage(cMessage *msg) override;
};

Define_Module(SwitchQuantumInterface);

void SwitchQuantumInterface::handleMessage(cMessage *msg)
{
    cGate *gate = msg->getArrivalGate();
    if(gate->isName("quantumChannelCommunication$i"))
    {
        std::string exitInterface=this->par("exitInterface").stringValue();
        exitInterface.append("$o");
        send(msg, exitInterface.c_str());
    }
    else
    {
       send(msg,"quantumChannelCommunication$o");
    }
}


void SwitchQuantumInterface::initialize(int stage)
{

}

int SwitchQuantumInterface::numInitStages() const
{
    return 3;
}






