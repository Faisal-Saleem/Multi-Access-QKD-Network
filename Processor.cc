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
#include "MacTableEntry_m.h"

using namespace omnetpp;

cModule *tModule;
SwitchMemory *switchMemory;

class Processor : public cSimpleModule
{
protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    virtual void finish() override;
};

Define_Module(Processor);

void Processor::initialize()
{

}
void Processor::handleMessage(cMessage *msg)
{
    EV<<" MAC Address Received : "<<msg->par("macAddress").stringValue()<<" FROM Interface : "<<msg->par("interface").stringValue();
    tModule = this->getParentModule()->getSubmodule("switchMemory");
    switchMemory = check_and_cast<SwitchMemory *>(tModule);
    MacTableEntry *macTableEntry = new MacTableEntry();
    macTableEntry->setIdentity(switchMemory->macEntryIndex++);
    macTableEntry->setInterface(msg->par("interface").stringValue());
    macTableEntry->setMacAddress(msg->par("macAddress").stringValue());
    macTableEntry->setQuantumInterfaceId("   ");
    macTableEntry->setQuantumMacAddress("                 ");
    macTableEntry->setType(1);
    switchMemory->addMacTableEntry(macTableEntry);
}

void Processor::finish()
{
    switchMemory->printMacAddressTable();
}






