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
    //SwitchInterfaceInit *switchInterface = new SwitchInterfaceInit();
    //switchInterface->setMacAddress(this->par("macAddress").stringValue());
    //EV<<"aslfkjdalsjkdf lkjasdf ljkasdf "<<switchInterface->getMacAddress();

    //cModule *macAddressTable = getParentModule()->getSubmodule("macAddressTable");
    //macAddressTable->par("interface").setStringValue(this->par(parname));
    //macAddressTable->par("macAddress").setStringValue(this->par("macAddress").stringValue());
    //EV<<"Hardware Address"<<par("macAddress").stringValue();

}
void SwitchQuantumInterface::handleMessage(cMessage *msg)
{

}






