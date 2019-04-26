/*
 * Client.cc
 *
 *  Created on: 15 Apr 2019
 *      Author: Faisal
 */
#include <string.h>
#include <omnetpp.h>
#include <bitset>
#include <iostream>
#include "ClientMemory.h"
#include "ClientProcessor.h"

using namespace omnetpp;

cModule *targetModule;
ClientMemory *clientMemory;

class Client : public cModule
{
    protected:
        virtual void initialize(int stage) override;
        virtual int numInitStages() const override;
        void printMacTable();
};

Define_Module(Client);

void Client::initialize(int stage)
{
    if(stage == 0)
    {
        targetModule = this->getSubmodule("clientMemory");
        clientMemory = check_and_cast<ClientMemory *>(targetModule);
        MacTableEntry *macTableEntry = new MacTableEntry();
        macTableEntry->setIdentity(1);
        macTableEntry->setInterface(this->getSubmodule("clientPublicInterface")->getName());
        macTableEntry->setMacAddress(this->getSubmodule("clientPublicInterface")->par("macAddress").stringValue());
        macTableEntry->setQuantumInterfaceId(this->getSubmodule("clientQuantumInterface")->getName());
        macTableEntry->setType(0);
        clientMemory->addMacTableEntry(macTableEntry);
        Client::printMacTable();
    }
}

int Client::numInitStages() const
{
    return 3;
}

void Client::printMacTable()
{
    EV<<"[*] "<<this->getName()<<" MAC Address Table\n";
        EV<<"=============================================================================================\n";
        EV<<"  Identity     Interface                 MacAddress             Q_Interface         Type   \n";
        EV<<"=============================================================================================\n";
        EV<<"     "
                <<clientMemory->getMacTable(0).getIdentity()
                <<"     "
                <<clientMemory->getMacTable(0).getInterface()
                <<"     "
                <<clientMemory->getMacTable(0).getMacAddress()
                <<"     "
                <<clientMemory->getMacTable(0).getQuantumInterfaceId()
                <<"     "
                <<clientMemory->getMacTable(0).getType()
                <<"\n";
        EV<<"=============================================================================================\n";
}






