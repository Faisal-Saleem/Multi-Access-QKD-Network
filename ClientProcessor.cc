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
#include <random>
#include <vector>
#include <algorithm>
#include "ClientProcessor.h"
#include "ClientMemory.h"

using namespace omnetpp;



Define_Module(ClientProcessor);

void ClientProcessor::initialize(int stage)
{
    cModule *targetModule = this->getParentModule()->getSubmodule("clientMemory");
    ClientMemory *clientMemory = check_and_cast<ClientMemory *>(targetModule);
    if(stage == 0)
    {
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
    cModule *targetModule = this->getParentModule()->getSubmodule("clientMemory");
    ClientMemory *clientMemory = check_and_cast<ClientMemory *>(targetModule);
    cGate *gate = msg->getArrivalGate();
    if(gate->isName("publicInterfaceCommunication$i"))
    {
        if(strcmp(msg->par("type").stringValue(),"initQkdRespons") == 0)
        {

        }
        if(strcmp(msg->par("type").stringValue(),"qkdRequest") == 0)
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
            int randomKeyLength = this->getParentModule()->getParentModule()->par("initKeyLength").intValue();
            clientMemory->setInitialKeyBin(ClientProcessor::convertToBinary(randomKeyLength));

            cMessage *k1 = new cMessage("initialKey");
            k1->addPar("type").setStringValue("initialKey");
            k1->addPar("value").setStringValue(clientMemory->getInitialKeyBin().c_str());
            send(k1,"quantumInterfaceCommunication$o");
        }
        if(strcmp(msg->par("type").stringValue(),"qkdStates") == 0)
        {
            QuantumKeyEntry *receivedKey = new QuantumKeyEntry();
            receivedKey->setIdentity(1);
            receivedKey->setMacAddress(msg->par("srcMAC").stringValue());
            receivedKey->setKey(ClientProcessor::compareBasis(clientMemory->getPolarizationStates(), msg->par("filterUsage").stringValue(), clientMemory->getInitialKeyBin()).c_str());
            receivedKey->setStatus("Active");
            clientMemory->addQautumKey(receivedKey);
            ClientProcessor::printKeyTable();
        }
    }
    else
    {
        if(strcmp(msg->par("type").stringValue(), "quantumData") == 0)
        {
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
        if(strcmp(msg->par("type").stringValue(),"pfilter") == 0)
        {
            clientMemory->setPolarizationStates(msg->par("polarizationFilterUsed").stringValue());
        }
    }
    delete msg;
}

unsigned int ClientProcessor::countSetBits(unsigned int n)
{
    unsigned int count = 0;
    while (n)
    {
        count += n & 1;
        n >>= 1;
    }
    return count;
}

std::string ClientProcessor::convertToBinary(int initialKey)
{
    std::string binKey = "";
    for(int i=0; i<initialKey; i++)
    {
       binKey.append(std::to_string(rand()&1));
    }
    return binKey;
}

void ClientProcessor::printMacTable()
{
    cModule *targetModule = this->getParentModule()->getSubmodule("clientMemory");
    ClientMemory *clientMemory = check_and_cast<ClientMemory *>(targetModule);

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
    cModule *targetModule = this->getParentModule()->getSubmodule("clientMemory");
    ClientMemory *clientMemory = check_and_cast<ClientMemory *>(targetModule);

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

std::string ClientProcessor::compareBasis(std::string statesUsed, std::string receivedStates, std::string randomBits)
{
        std::string key;
        char statsU[statesUsed.length()];
        strcpy(statsU, statesUsed.c_str());

        char statsR[receivedStates.length()];
        strcpy(statsR, receivedStates.c_str());

        char bitsR[randomBits.length()];
        strcpy(bitsR, randomBits.c_str());

        for(int i=0; i<receivedStates.length(); i++)
        {
            if(statsU[i] == '|' && statsR[i] == '+')
            {
                key += bitsR[i];
            }
            else if(statsU[i] == '/' && statsR[i] == 'x')
            {
                key += bitsR[i];
            }
            else if (statsU[i] == '-' && statsR[i] == '+')
            {
                key += bitsR[i];
            }
            else if (statsU[i] == '\\' && statsR[i] == 'x')
            {
                key += bitsR[i];
            }
    }
    return key;
}
