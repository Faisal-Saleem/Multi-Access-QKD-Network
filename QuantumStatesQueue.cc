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

using namespace omnetpp;

class QuantumStatesQueue : public cSimpleModule
{
protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

Define_Module(QuantumStatesQueue);

void QuantumStatesQueue::initialize()
{

}
void QuantumStatesQueue::handleMessage(cMessage *msg)
{

}






