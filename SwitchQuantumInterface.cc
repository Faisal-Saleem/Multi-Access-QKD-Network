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

class SwitchQuantumInterface : public cSimpleModule
{
protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

Define_Module(SwitchQuantumInterface);

void SwitchQuantumInterface::initialize()
{

}
void SwitchQuantumInterface::handleMessage(cMessage *msg)
{

}






