#include <string.h>
#include <omnetpp.h>
#include <bitset>
#include <iostream>
#include "ClientMemory.h"
#include "MacTableEntry_m.h"
#include "QuantumKeyEntry_m.h"

Define_Module(ClientMemory);

void ClientMemory::initialize()
{

}

void ClientMemory::handleMessage(cMessage *msg)
{

}

MacTableEntry ClientMemory::getMacTable(int index)
{
    MacTableEntry *macTableEntry = (MacTableEntry *) this->quantumTable[index];
    return *macTableEntry;
}

void ClientMemory::addMacTableEntry(MacTableEntry *macTableEntry)
{
    this->quantumTable.add(macTableEntry);
}

int ClientMemory::getMacTableSize()
{
    return this->quantumTable.size();
}

QuantumKeyEntry ClientMemory::getQuantumKey(int index)
{
    QuantumKeyEntry *quantumKeyEntry = (QuantumKeyEntry *) this->quantumKey[index];
    return *quantumKeyEntry;
}

void ClientMemory::addQautumKey(QuantumKeyEntry *key)
{
    this->quantumKey.add(key);
}

int ClientMemory::getNumberOfKey()
{
    return this->quantumKey.size();
}

int ClientMemory::getPendingTransaction()
{
    int index = 0;
    for(int i=0; i<this->quantumKey.size(); i++)
    {
        QuantumKeyEntry *qKey = (QuantumKeyEntry *) this->quantumKey[i];
        if(strcmp(qKey->getKey(),"") == 0)
        {
            index = i;
            break;
        }
    }
    return index;
}

std::string ClientMemory::getPendingKeyMacAddress()
{
    std::string desMac = "";
    for(int i=0; i<this->quantumKey.size(); i++)
    {
        QuantumKeyEntry *qKey = (QuantumKeyEntry *) this->quantumKey[i];

        if(strcmp(qKey->getStatus(),"") == 0)
        {
            desMac = qKey->getMacAddress();
            qKey->setStatus("Active");
            break;
        }
    }
    return desMac;
}

void ClientMemory::setPendingKey(std::string key)
{
    for(int i=0; i<this->quantumKey.size(); i++)
    {
        QuantumKeyEntry *qKey = (QuantumKeyEntry *) this->quantumKey[i];
        if(strcmp(qKey->getKey(),"") == 0)
        {
            qKey->setKey(key.c_str());
            break;
        }
    }
}

std::string ClientMemory::getInitialKey()
{
    return this->initialKey;
}
void ClientMemory::setInitialKey(std::string key)
{
       this->initialKey=key;
}

std::string ClientMemory::getPolarizationStates()
{
    return this->polarizationStates;
}

void ClientMemory::setPolarizationStates(std::string states)
{
    this->polarizationStates = states;
}

std::string ClientMemory::getInitialKeyBin()
{
    return this->initialKeyBin;
}

void ClientMemory::setInitialKeyBin(std::string bin)
{
    this->initialKeyBin = bin;
}
