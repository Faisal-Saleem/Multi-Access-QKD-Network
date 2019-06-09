/*
 * ClientProcessor.cc
 *
 *  Created on: 7 Apr 2019
 *      Author: Faisal
 *
 */

#include <string.h>
#include <omnetpp.h>
#include <bitset>
#include <iostream>
#include <cstdlib>
#include "ClientProcessor.h"
#include "ClientMemory.h"

using namespace omnetpp;

cModule *targetModule;
ClientMemory *clientMemory;

Define_Module(ClientProcessor);

void ClientProcessor::initialize(int stage)
{
    if(stage == 0)
    {
        targetModule = this->getParentModule()->getSubmodule("clientMemory");
        clientMemory = check_and_cast<ClientMemory *>(targetModule);
        MacTableEntry *macTableEntry = new MacTableEntry();
        macTableEntry->setIdentity(1);
        macTableEntry->setInterface(this->getParentModule()->getSubmodule("clientPublicInterface")->getName());
        macTableEntry->setMacAddress(this->getParentModule()->getSubmodule("clientPublicInterface")->par("macAddress").stringValue());
        macTableEntry->setQuantumInterfaceId(this->getParentModule()->getSubmodule("clientQuantumInterface")->getName());
        macTableEntry->setType(0);
        clientMemory->addMacTableEntry(macTableEntry);
        ClientProcessor::printMacTable();
    }
    else if(stage == 1)
    {
        cPacket *discoveryPacket = new cPacket("networkDiscovery");
        discoveryPacket->setByteLength(1024);
        discoveryPacket->addPar("type").setStringValue("networkDiscovery");
        discoveryPacket->addPar("macAddress").setStringValue(this->getParentModule()->getSubmodule("clientPublicInterface")->par("macAddress"));
        discoveryPacket->addPar("ipAddress").setStringValue(this->getParentModule()->getSubmodule("clientPublicInterface")->par("ipAddress"));
        sendDelayed(discoveryPacket, 1, "publicInterfaceCommunication$o");
    }
    else if(stage == 2)
    {
        if(strcmp(this->getParentModule()->getParentModule()->par("source"), this->getParentModule()->getName()) == 0)
        {
            cPacket *discoveryPacket = new cPacket("initQkd");
            discoveryPacket->setByteLength(1024);
            discoveryPacket->addPar("type").setStringValue("initQkd");
            discoveryPacket->addPar("srcMAC").setStringValue(this->getParentModule()->getParentModule()->getSubmodule(this->getParentModule()->getParentModule()->par("source").stringValue())->getSubmodule("clientPublicInterface")->par("macAddress").stringValue());
            discoveryPacket->addPar("desMAC").setStringValue(this->getParentModule()->getParentModule()->getSubmodule(this->getParentModule()->getParentModule()->par("destination").stringValue())->getSubmodule("clientPublicInterface")->par("macAddress").stringValue());
            sendDelayed(discoveryPacket, 2, "publicInterfaceCommunication$o");
        }
    }
}

int ClientProcessor::numInitStages() const
{
    return 3;
}

void ClientProcessor::handleMessage(cMessage *msg)
{
    cGate *gate = msg->getArrivalGate();
    if(gate->isName("publicInterfaceCommunication$i"))
    {
        if(strcmp(msg->par("type").stringValue(),"initQkdRespons") == 0)
        {

        }
        if(strcmp(msg->par("type").stringValue(),"qkdRequest") == 0)
        {
            QuantumKeyEntry *key = new QuantumKeyEntry();
            cPacket *qkdResponse = new cPacket("qkdResponse");
            qkdResponse->addPar("type").setStringValue("QKD-RESPONSE");
            qkdResponse->addPar("srcMAC").setStringValue(msg->par("desMAC").stringValue());
            qkdResponse->addPar("desMAC").setStringValue(msg->par("srcMAC").stringValue());

            key->setIdentity(1);
            key->setMacAddress(msg->par("srcMAC").stringValue());

            clientMemory->addQautumKey(key);

            send(qkdResponse,"publicInterfaceCommunication$o");
        }
        if(strcmp(msg->par("type").stringValue(),"QKD-ACK") == 0)
        {
            int randomKey = rand()% 100 + 899;
            clientMemory->setInitialKey(std::to_string(randomKey));
            clientMemory->setInitialKeyBin(ClientProcessor::convertToBinary(randomKey));
            cMessage *k1 = new cMessage("initialKey");
            k1->addPar("type").setStringValue("initialKey");
            k1->addPar("value").setStringValue(clientMemory->getInitialKeyBin().c_str());
            send(k1,"quantumInterfaceCommunication$o");
        }
    }
    else
    {
        /*
        if(strcmp(msg->par("type").stringValue(),"pfilter") == 0)
        {
            clientMemory->setPolarizationStates(msg->par("polarizationFilterUsed").stringValue());
        }
        */

        if(strcmp(msg->par("type").stringValue(), "quantumData") == 0)
        {
            clientMemory->setPendingKey(msg->par("siftedKey").stringValue());
            clientMemory->getQuantumKey(clientMemory->getPendingTransaction()).setKey(msg->par("siftedKey").stringValue());
            clientMemory->getQuantumKey(clientMemory->getPendingTransaction()).setStatus("Active");
            ClientProcessor::printKeyTable();

            cPacket *polarizationStatus = new cPacket("quantumData");
            polarizationStatus->addPar("type").setStringValue("quantumData");
            polarizationStatus->addPar("filterUsage").setStringValue(msg->par("filterUsage").stringValue());
            send(polarizationStatus,"publicInterfaceCommunication$o");
        }
    }
    delete msg;
}

std::string ClientProcessor::convertToBinary(int initialKey)
{
    std::string key = std::to_string(initialKey);
    std::string binKey = "";
    for(std::size_t i=0; i< key.size(); ++i)
    {
        binKey.append(std::bitset<8>(key.c_str()[i]).to_string());
    }
    return binKey;
}

void ClientProcessor::printMacTable()
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

void ClientProcessor::printKeyTable()
{
    EV<<"[*] "<<this->getParentModule()->getName()<<" Quantum Key Table\n";
            EV<<"=======================================================\n";
            EV<<"  ID       MacAddress           Key        Status   \n";
            EV<<"=======================================================\n";
            EV<<"  "
                    <<clientMemory->getQuantumKey(0).getIdentity()
                    <<"     "
                    <<clientMemory->getQuantumKey(0).getMacAddress()
                    <<"     "
                    <<clientMemory->getQuantumKey(0).getKey()
                    <<"     "
                    <<clientMemory->getQuantumKey(0).getStatus()
                    <<"\n";
            EV<<"=======================================================\n";
}
