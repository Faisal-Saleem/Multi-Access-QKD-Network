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

}


void SwitchQuantumInterface::initialize(int stage)
{
    /*
    if(stage == 2)
    {
        cModule *targetSwitch = getParentModule()->getSubmodule("switchMemory");
        SwitchMemory *switchModule = check_and_cast<SwitchMemory *>(targetSwitch);
        switchModule->printMacAddressTable();
    }
    */
}

int SwitchQuantumInterface::numInitStages() const
{
    return 3;
}






