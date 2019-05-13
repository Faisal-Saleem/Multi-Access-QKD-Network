#include <string.h>
#include <omnetpp.h>
#include <bitset>
#include <iostream>
#include "ClientMemory.h"
#include "MacTableEntry_m.h"

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
