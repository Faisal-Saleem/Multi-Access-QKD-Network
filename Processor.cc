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
#include "ArpTableEntry_m.h"

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
    void printArpTable();
    void printSessionStateTable();
};

Define_Module(Processor);

void Processor::initialize(int stage)
{
    if(stage == 0)
    {
        tModule = this->getParentModule()->getSubmodule("switchMemory");
        switchMemory = check_and_cast<SwitchMemory *>(tModule);
        switchMemory->macEntryIndex = 1;
        switchMemory->arpEntryIndex = 1;
        switchMemory->sessionsStateEntryIndex = 1;

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
    if(strcmp("networkDiscovery",msg->par("type").stringValue()) == 0)
    {
        MacTableEntry *macTableEntry = new MacTableEntry();
        macTableEntry->setIdentity(switchMemory->macEntryIndex++);
        macTableEntry->setInterface(msg->par("interface").stringValue());
        macTableEntry->setMacAddress(msg->par("macAddress").stringValue());
        macTableEntry->setQuantumInterfaceId("   ");
        macTableEntry->setQuantumMacAddress("                 ");
        macTableEntry->setType(1);
        switchMemory->addMacTableEntry(macTableEntry);

        ArpTableEntry *arpTableEntry = new ArpTableEntry();
        arpTableEntry->setIdentity(switchMemory->arpEntryIndex++);
        arpTableEntry->setProtocol("Internet");
        arpTableEntry->setIpAddress(msg->par("ipAddress").stringValue());
        arpTableEntry->setAge("10");
        arpTableEntry->setMacAddress(msg->par("macAddress").stringValue());
        arpTableEntry->setType(0);
        arpTableEntry->setInterface(msg->par("interface").stringValue());
        switchMemory->addArpTableEntry(arpTableEntry);
        delete msg;
    }
    else if (strcmp("initQkd",msg->par("type").stringValue()) == 0)
    {
        SessionStateEntry *sessionStateEntry = new SessionStateEntry();
        sessionStateEntry->setSessionId(switchMemory->sessionsStateEntryIndex++);
        sessionStateEntry->setSrcMac(msg->par("srcInterfaceMacAddress").stringValue());
        sessionStateEntry->setSrcQMac(switchMemory->getQuantumInterfaceMacAddressFromMacTable(sessionStateEntry->getSrcMac()).c_str());
        sessionStateEntry->setSrcSubInterface(switchMemory->getQuantumInterfaceFromMacTable(sessionStateEntry->getSrcQMac()).c_str());
        sessionStateEntry->setDesMac(switchMemory->getMacAddressOfInterfaceFromMacTable(switchMemory->getInterfaceIdFromMacTable(msg->par("desMAC").stringValue()).c_str()).c_str());
        sessionStateEntry->setDesQMac(switchMemory->getQuantumMacAddressOfInterfaceFromMacTable(switchMemory->getInterfaceIdFromMacTable(msg->par("desMAC").stringValue()).c_str()).c_str());
        sessionStateEntry->setDesSubInterface(switchMemory->getQuantumInterfaceFromMacTable(sessionStateEntry->getDesQMac()).c_str());
        sessionStateEntry->setExpiry("0000");
        sessionStateEntry->setStatus("0");
        if(switchMemory->entryExist(sessionStateEntry->getSrcMac()) == false)
        {
            switchMemory->addSessionStateTableEntry(sessionStateEntry);
            cPacket *qkdSession = new cPacket("qkdRequest");
            qkdSession->addPar("type").setStringValue("qkdRequest");
            qkdSession->addPar("srcMAC").setStringValue(sessionStateEntry->getSrcMac());
            qkdSession->addPar("requestFrom").setStringValue(msg->par("srcMAC").stringValue());
            qkdSession->addPar("desMAC").setStringValue(sessionStateEntry->getDesMac());
            qkdSession->addPar("interface").setStringValue(switchMemory->getInterfaceIdFromMacTable(sessionStateEntry->getDesMac()).c_str());
            send(qkdSession,"publicInterfaceCommunication$o");
        }
        else
        {
            cPacket *qkdSession = new cPacket("clientBusy");
            qkdSession->addPar("type").setStringValue("initQkdRespons");
            qkdSession->addPar("desMAC").setStringValue(sessionStateEntry->getDesMac());
            qkdSession->addPar("interface").setStringValue(switchMemory->getInterfaceIdFromMacTable(sessionStateEntry->getSrcMac()).c_str());
            send(qkdSession,"publicInterfaceCommunication$o");
        }
        delete msg;
    }
    else if(strcmp("QKD-RESPONSE",msg->par("type").stringValue()) == 0)
    {
        cPacket *qkdAck = new cPacket("qkdAck");
        qkdAck->addPar("type").setStringValue("QKD-ACK");
        qkdAck->addPar("srcMAC").setStringValue(msg->par("srcMAC").stringValue());
        qkdAck->addPar("desMAC").setStringValue(msg->par("desMAC").stringValue());
        qkdAck->addPar("interface").setStringValue(switchMemory->getInterfaceIdFromMacTable(msg->par("desMAC").stringValue()).c_str());

        cModule *qSRCInterface = this->getParentModule()->getSubmodule(switchMemory->getQuantumInterfaceFromMacTableByPublicMac(msg->par("desMAC").stringValue()).c_str());
        cModule *qDESInterface = this->getParentModule()->getSubmodule(switchMemory->getQuantumInterfaceFromMacTableByPublicMac(msg->par("srcMAC").stringValue()).c_str());
        qSRCInterface->par("exitInterface").setStringValue(switchMemory->getExitInterfaceFromBindingTable(qSRCInterface->getName(), qDESInterface->getName()));

        send(qkdAck,"publicInterfaceCommunication$o");
        delete msg;

    }
    else if (strcmp("quantumData",msg->par("type").stringValue()) == 0)
    {
        cPacket *pkt = new cPacket("qkdStats");
        pkt->addPar("type").setStringValue("qkdStates");
        pkt->addPar("interface").setStringValue(switchMemory->getInterface(msg->par("desMAC").stringValue()).c_str());
        pkt->addPar("srcMAC").setStringValue(msg->par("srcMAC").stringValue());
        pkt->addPar("desMAC").setStringValue(msg->par("desMAC").stringValue());
        pkt->addPar("filterUsage").setStringValue(msg->par("filterUsage").stringValue());
        EV<<"INTERFACE : "<<switchMemory->getInterface(pkt->par("desMAC").stringValue());
        send(pkt,"publicInterfaceCommunication$o");
        delete msg;
    }
    else
    {
        delete msg;
    }
}

void Processor::finish()
{
    Processor::printMacAddressTable();
    Processor::printArpTable();
    Processor::printSessionStateTable();

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

void Processor::printArpTable()
{
    EV<<"[*] Arp Table\n";
        EV<<"=============================================================================================\n";
        EV<<"  Identity    Protocol        Address      Age(min)    Hardware Addr    Type   Interface    \n";
        EV<<"=============================================================================================\n";
        for(int i=0; i<switchMemory->getArpTableSize(); i++)
        {
            EV<<"      "
                    <<switchMemory->getArpTableEntry(i).getIdentity()
                    <<"       "
                    <<switchMemory->getArpTableEntry(i).getProtocol()
                    <<"     "
                    <<switchMemory->getArpTableEntry(i).getIpAddress()
                    <<"      "
                    <<switchMemory->getArpTableEntry(i).getAge()
                    <<"     "
                    <<switchMemory->getArpTableEntry(i).getMacAddress()
                    <<"    "
                    <<switchMemory->getArpTableEntry(i).getType()
                    <<"       "
                    <<switchMemory->getArpTableEntry(i).getInterface()
                    <<"\n";
        }
        EV<<"=============================================================================================\n";
}

void Processor::printSessionStateTable()
{
    EV<<"[*] Session State Table\n";
        EV<<"============================================================================================================\n";
        EV<<" ID         SRC               QSRC         INT          DES                QDES         INT  Expiry  Status \n";
        EV<<"============================================================================================================\n";
    for(int i=0; i<switchMemory->getSessionStateTableSize(); i++)
    {
        EV<<" "
                <<switchMemory->getsessionStateTableEntry(i).getSessionId()
                <<"   "
                <<switchMemory->getsessionStateTableEntry(i).getSrcMac()
                <<"  "
                <<switchMemory->getsessionStateTableEntry(i).getSrcQMac()
                <<"  "
                <<switchMemory->getsessionStateTableEntry(i).getSrcSubInterface()
                <<"   "
                <<switchMemory->getsessionStateTableEntry(i).getDesMac()
                <<" "
                <<switchMemory->getsessionStateTableEntry(i).getDesQMac()
                <<"    "
                <<switchMemory->getsessionStateTableEntry(i).getDesSubInterface()
                <<"   "
                <<switchMemory->getsessionStateTableEntry(i).getExpiry()
                <<"      "
                <<switchMemory->getsessionStateTableEntry(i).getStatus()
                <<"\n";
    }
    EV<<"============================================================================================================\n";
}


