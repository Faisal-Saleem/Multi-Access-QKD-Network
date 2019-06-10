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
        discoveryPacket->addPar("type").setStringValue("networkDiscovery");
        discoveryPacket->addPar("macAddress").setStringValue(this->getParentModule()->getSubmodule("clientPublicInterface")->par("macAddress"));
        discoveryPacket->addPar("ipAddress").setStringValue(this->getParentModule()->getSubmodule("clientPublicInterface")->par("ipAddress"));
        sendDelayed(discoveryPacket, 1, "publicInterfaceCommunication$o");
    }
    else if(stage == 2)
    {
        if(strcmp(this->getParentModule()->getParentModule()->par("source"), this->getParentModule()->getName()) == 0 && this->getParentModule()->getParentModule()->par("multipoint").boolValue() == false)
        {
            cPacket *discoveryPacket = new cPacket("initQkd");
            discoveryPacket->addPar("type").setStringValue("initQkd");
            discoveryPacket->addPar("srcMAC").setStringValue(this->getParentModule()->getParentModule()->getSubmodule(this->getParentModule()->getParentModule()->par("source").stringValue())->getSubmodule("clientPublicInterface")->par("macAddress").stringValue());
            discoveryPacket->addPar("desMAC").setStringValue(this->getParentModule()->getParentModule()->getSubmodule(this->getParentModule()->getParentModule()->par("destination").stringValue())->getSubmodule("clientPublicInterface")->par("macAddress").stringValue());
            sendDelayed(discoveryPacket, 2, "publicInterfaceCommunication$o");
        }
        else if(this->getParentModule()->getParentModule()->par("multipoint").boolValue() == true)
        {
            if(strcmp(this->getParentModule()->getParentModule()->par("source"), this->getParentModule()->getName()) == 0)
            {
                cPacket *discoveryPacket = new cPacket("initQkd");
                discoveryPacket->addPar("type").setStringValue("initQkd");
                discoveryPacket->addPar("srcMAC").setStringValue(this->getParentModule()->getParentModule()->getSubmodule(this->getParentModule()->getParentModule()->par("source").stringValue())->getSubmodule("clientPublicInterface")->par("macAddress").stringValue());
                discoveryPacket->addPar("desMAC").setStringValue(this->getParentModule()->getParentModule()->getSubmodule(this->getParentModule()->getParentModule()->par("destination").stringValue())->getSubmodule("clientPublicInterface")->par("macAddress").stringValue());
                sendDelayed(discoveryPacket, 2, "publicInterfaceCommunication$o");
            }
            else if(strcmp(this->getParentModule()->getParentModule()->par("multiPointSource"), this->getParentModule()->getName()) == 0)
            {
                cPacket *discoveryPacket2 = new cPacket("initQkd");
                discoveryPacket2->addPar("type").setStringValue("initQkd");
                discoveryPacket2->addPar("srcMAC").setStringValue(this->getParentModule()->getParentModule()->getSubmodule(this->getParentModule()->getParentModule()->par("multiPointSource").stringValue())->getSubmodule("clientPublicInterface")->par("macAddress").stringValue());
                discoveryPacket2->addPar("desMAC").setStringValue(this->getParentModule()->getParentModule()->getSubmodule(this->getParentModule()->getParentModule()->par("multiPointDestination").stringValue())->getSubmodule("clientPublicInterface")->par("macAddress").stringValue());
                sendDelayed(discoveryPacket2, 2, "publicInterfaceCommunication$o");
            }

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
        if(strcmp(msg->par("type").stringValue(),"qkdRequest") == 0 && strcmp(this->getParentModule()->getSubmodule("clientPublicInterface")->par("macAddress").stringValue(), msg->par("requestTo")) == 0)
        {
            QuantumKeyEntry *key = new QuantumKeyEntry();
            key->setIdentity(1);
            key->setMacAddress(msg->par("requestFrom").stringValue());


            clientMemory->addQautumKey(key);
            ClientProcessor::printKeyTable();

            cPacket *qkdResponse = new cPacket("qkdResponse");
            qkdResponse->addPar("type").setStringValue("QKD-RESPONSE");
            qkdResponse->addPar("srcMAC").setStringValue(msg->par("desMAC").stringValue());
            qkdResponse->addPar("desMAC").setStringValue(msg->par("srcMAC").stringValue());
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
        if(strcmp(msg->par("type").stringValue(),"qkdStates") == 0)
        {
            if(strcmp(this->getParentModule()->getSubmodule("clientPublicInterface")->par("macAddress"), msg->par("desMAC").stringValue()) == 0)
            {
                EV<<"DES MAC :"<<msg->par("desMAC").stringValue()<<endl;
                QuantumKeyEntry *receivedKey = new QuantumKeyEntry();
                receivedKey->setIdentity(1);
                receivedKey->setMacAddress(msg->par("srcMAC").stringValue());
                receivedKey->setKey(ClientProcessor::compareBasis(clientMemory->getInitialKeyBin(), msg->par("filterUsage").stringValue()).c_str());
                receivedKey->setStatus("Active");
                clientMemory->addQautumKey(receivedKey);
                ClientProcessor::printKeyTable();
            }
        }
    }
    else
    {
        if(strcmp(msg->par("type").stringValue(), "quantumData") == 0)
        {

                EV<<"SRC MAC :"<<this->getParentModule()->getName()<<endl;
                clientMemory->setPendingKey(msg->par("siftedKey").stringValue());
                clientMemory->getQuantumKey(clientMemory->getPendingTransaction()).setKey(msg->par("siftedKey").stringValue());
                cPacket *polarizationStatus = new cPacket("quantumData");
                polarizationStatus->addPar("type").setStringValue("quantumData");
                polarizationStatus->addPar("filterUsage").setStringValue(msg->par("filterUsage").stringValue());
                polarizationStatus->addPar("srcMAC").setStringValue(this->getParentModule()->getSubmodule("clientPublicInterface")->par("macAddress").stringValue());
                polarizationStatus->addPar("desMAC").setStringValue(clientMemory->getPendingKeyMacAddress().c_str());
                send(polarizationStatus,"publicInterfaceCommunication$o");
                clientMemory->getQuantumKey(clientMemory->getPendingTransaction()).setStatus("Active");
                ClientProcessor::printKeyTable();

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
    for(int i=0; i<clientMemory->getNumberOfKey(); i++)
    {
        if(strcmp(clientMemory->getQuantumKey(i).getMacAddress(),this->getParentModule()->getSubmodule("clientPublicInterface")->par("macAddress").stringValue()) != 0)
        {
            EV<<"  "
                <<clientMemory->getQuantumKey(i).getIdentity()
                <<"     "
                <<clientMemory->getQuantumKey(i).getMacAddress()
                <<"     "
                <<clientMemory->getQuantumKey(i).getKey()
                <<"     "
                <<clientMemory->getQuantumKey(i).getStatus()
                <<"\n";

        }
    }
    EV<<"=======================================================\n";
}

std::string ClientProcessor::compareBasis(std::string initialKey, std::string receivedStats)
{
    std::string key = "";
    if(initialKey.length() == receivedStats.length())
    {
        char keyChar[initialKey.length()+1];
        strcpy(keyChar, initialKey.c_str());

        char statesChar[receivedStats.length()+1];
        strcpy(statesChar, receivedStats.c_str());

        for(int i=0; i<=initialKey.length(); i++)
        {
            if(receivedStats[i] == '1')
            {
                std::string s(1, keyChar[i]);
                key.append(s);
            }
        }
    }
    return key;
}
