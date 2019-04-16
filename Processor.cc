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
#include "QuantumSubInterfaceBinding_m.h"

using namespace omnetpp;

cModule *tModule;
SwitchMemory *switchMemory;

class Processor : public cSimpleModule
{
protected:
    virtual void initialize(int stage) override;
    virtual void handleMessage(cMessage *msg) override;
    virtual int numInitStages() const override;
    virtual void finish() override;

    void prepareMacAddressTable();
    void bindInterface(int identity, std::string interface, std::string quantumInterface, int type);
    void prepareQuantumSubInterfaceBindingTable();
    void bindSubInterface(std::string identity, std::string sourceInterface, std::string sourceSubInterface, std::string destinationInterface, std::string destinationSubInterface, int status);

public:
    void printMacAddressTable();
    void printQuantumSubinterfaceBindingTable();
};

Define_Module(Processor);

void Processor::initialize(int stage)
{
    if(stage == 0)
    {
        tModule = this->getParentModule()->getSubmodule("switchMemory");
        switchMemory = check_and_cast<SwitchMemory *>(tModule);
        switchMemory->macEntryIndex = 1;

        Processor::prepareQuantumSubInterfaceBindingTable();
        EV<<"[*] Prepairing Quantum Sub Interface Binding Table\n";
        Processor::printQuantumSubinterfaceBindingTable();
    }
    if(stage == 1)
    {
        Processor::prepareMacAddressTable();
        EV<<"[*] Prepairing Quantum MAC Address Table\n";
        Processor::printMacAddressTable();
    }
}

int Processor::numInitStages() const
{
    return 2;
}

void Processor::handleMessage(cMessage *msg)
{
    MacTableEntry *macTableEntry = new MacTableEntry();
    macTableEntry->setIdentity(switchMemory->macEntryIndex++);
    macTableEntry->setInterface(msg->par("interface").stringValue());
    macTableEntry->setMacAddress(msg->par("macAddress").stringValue());
    macTableEntry->setQuantumInterfaceId("   ");
    macTableEntry->setQuantumMacAddress("                 ");
    macTableEntry->setType(1);
    switchMemory->addMacTableEntry(macTableEntry);
    delete msg;
}

void Processor::finish()
{
    Processor::printMacAddressTable();
}

void Processor::prepareMacAddressTable()
{
    EV<<"[*] Binding Public and Quantum Channels\n";
    Processor::bindInterface(switchMemory->macEntryIndex++,"f01","q01",0);
    Processor::bindInterface(switchMemory->macEntryIndex++,"f02","q02",0);
    Processor::bindInterface(switchMemory->macEntryIndex++,"f03","q03",0);
    Processor::bindInterface(switchMemory->macEntryIndex++,"f04","q04",0);
    EV<<"[*] Done\n";
}

void Processor::bindInterface(int identity, std::string interface, std::string quantumInterface, int type)
{
    MacTableEntry *macTableEntry = new MacTableEntry();
    macTableEntry->setIdentity(identity);
    macTableEntry->setInterface(this->getParentModule()->getSubmodule(interface.c_str())->getName());
    macTableEntry->setMacAddress(this->getParentModule()->getSubmodule(interface.c_str())->par("macAddress").stringValue());
    macTableEntry->setQuantumInterfaceId(this->getParentModule()->getSubmodule(quantumInterface.c_str())->getName());
    macTableEntry->setQuantumMacAddress(this->getParentModule()->getSubmodule(quantumInterface.c_str())->par("macAddress").stringValue());
    macTableEntry->setType(type);
    switchMemory->addMacTableEntry(macTableEntry);
}

void Processor::printMacAddressTable()
{
    EV<<"[*] Quantum MAC Address Table\n";
    EV<<"=============================================================================================\n";
    EV<<"  Identity     Interface     MacAddress     Q_Interface          Q_MacAddress          Type   \n";
    EV<<"=============================================================================================\n";
    for(int i=0; i<switchMemory->getMacTableSize(); i++)
    {
        EV<<"      "
                <<switchMemory->getMacTable(i).getIdentity()
                <<"           "
                <<switchMemory->getMacTable(i).getInterface()
                <<"     "
                <<switchMemory->getMacTable(i).getMacAddress()
                <<"      "
                <<switchMemory->getMacTable(i).getQuantumInterfaceId()
                <<"          "
                <<switchMemory->getMacTable(i).getQuantumMacAddress()
                <<"          "
                <<switchMemory->getMacTable(i).getType()
                <<"\n";
    }
    EV<<"=============================================================================================\n";
}

void Processor::prepareQuantumSubInterfaceBindingTable()
{
    EV<<"[*] Binding Quantum Sub Interface\n";
    Processor::bindSubInterface("01","q01","subInterface2$o","q02","subInterface1$i",0);
    Processor::bindSubInterface("02","q02","subInterface3$o","q03","subInterface2$i",0);
    Processor::bindSubInterface("03","q03","subInterface4$o","q04","subInterface3$i",0);
    Processor::bindSubInterface("04","q01","subInterface4$o","q04","subInterface1$i",0);
    Processor::bindSubInterface("05","q02","subInterface4$o","q04","subInterface2$i",0);
    Processor::bindSubInterface("06","q03","subInterface1$o","q01","subInterface3$i",0);
    Processor::bindSubInterface("07","q02","subInterface1$o","q01","subInterface2$i",0);
    Processor::bindSubInterface("08","q03","subInterface2$o","q02","subInterface3$i",0);
    Processor::bindSubInterface("09","q04","subInterface3$o","q03","subInterface4$i",0);
    Processor::bindSubInterface("10","q04","subInterface1$o","q01","subInterface4$i",0);
    Processor::bindSubInterface("11","q04","subInterface2$o","q02","subInterface4$i",0);
    Processor::bindSubInterface("12","q01","subInterface3$o","q03","subInterface1$i",0);
    EV<<"[*] Subinterface Binding Done\n";
}

void Processor::bindSubInterface(std::string identity, std::string sourceInterface,std::string sourceSubInterface,std::string destinationInterface, std::string destinationSubInterface, int status)
{
    QuantumSubInterfaceBinding *subInterfaceBindingEntry = new QuantumSubInterfaceBinding();
    subInterfaceBindingEntry->setIdentity(identity.c_str());
    subInterfaceBindingEntry->setConnectionId(this->getParentModule()->getSubmodule(sourceInterface.c_str())->gate(sourceSubInterface.c_str())->getConnectionId());
    subInterfaceBindingEntry->setSourceInterface(this->getParentModule()->getSubmodule(sourceInterface.c_str())->getName());
    subInterfaceBindingEntry->setSourceSubInterface(this->getParentModule()->getSubmodule(sourceInterface.c_str())->gate(sourceSubInterface.c_str())->getBaseName());
    subInterfaceBindingEntry->setDestinationInterface(this->getParentModule()->getSubmodule(destinationInterface.c_str())->getName());
    subInterfaceBindingEntry->setDestinationSubInterface(this->getParentModule()->getSubmodule(destinationInterface.c_str())->gate(destinationSubInterface.c_str())->getBaseName());
    subInterfaceBindingEntry->setStatus(status);
    switchMemory->addQuantumBindingTableEntry(subInterfaceBindingEntry);
}

void Processor::printQuantumSubinterfaceBindingTable()
{
    EV<<"[*] Quantum Sub Interface Binding Table\n";
    EV<<"===================================================================\n";
    EV<<"  Id   ConId     Src     Src-Sub      Dst     Dst-Sub      Type   \n";
    EV<<"===================================================================\n";
    for(int i=0; i<switchMemory->getQuantumBindingTableSize(); i++)
    {
        //QuantumSubInterfaceBinding *subInterfaceBindingEntry = (QuantumSubInterfaceBinding *) switchMemory->getQuantumBindingTable(i);
        EV<<"  "<<switchMemory->getQuantumBindingTable(i).getIdentity()
                <<"     "<<switchMemory->getQuantumBindingTable(i).getConnectionId()
                <<"       "<<switchMemory->getQuantumBindingTable(i).getSourceInterface()
                <<"  "<<switchMemory->getQuantumBindingTable(i).getSourceSubInterface()
                <<"   "<<switchMemory->getQuantumBindingTable(i).getDestinationInterface()
                <<"   "<<switchMemory->getQuantumBindingTable(i).getDestinationSubInterface()
                <<"   "<<switchMemory->getQuantumBindingTable(i).getStatus()
                <<"\n";
    }
    EV<<"===================================================================\n";
}




