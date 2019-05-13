//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include <string.h>
#include <bitset>
#include <iostream>
#include "SwitchMemory.h"
#include "MacTableEntry_m.h"
#include "QuantumSubInterfaceBinding_m.h"
#include "SessionStateEntry_m.h"

Define_Module(SwitchMemory);

void SwitchMemory::initialize(int stage)
{

}

int SwitchMemory::numInitStages() const
{
    return 2;
}

MacTableEntry SwitchMemory::getMacTable(int index)
{
    MacTableEntry *macTableEntry = (MacTableEntry *) this->macAddressTable[index];
    return *macTableEntry;
}

void SwitchMemory::addMacTableEntry(MacTableEntry *macTableEntry)
{
    this->macAddressTable.add(macTableEntry);
}

int SwitchMemory::getMacTableSize()
{
    return this->macAddressTable.size();
}

std::string SwitchMemory::getQuantumInterfaceMacAddressFromMacTable(std::string publicInterfaceMacAddress)
{
    return SwitchMemory::searchMacAddressTableByMacAddress(publicInterfaceMacAddress, 'Q');
}

std::string SwitchMemory::getInterfaceIdFromMacTable(std::string macAddress)
{
    return SwitchMemory::searchMacAddressTableByMacAddress(macAddress, 'I');
}

std::string SwitchMemory::getMacAddressOfInterfaceFromMacTable(std::string interface)
{
    return SwitchMemory::searchMacAddressTableByInterface(interface, 'M');
}

std::string SwitchMemory::getQuantumMacAddressOfInterfaceFromMacTable(std::string interface)
{
    return SwitchMemory::searchMacAddressTableByInterface(interface, 'Q');
}

std::string SwitchMemory::getQuantumInterfaceFromMacTable(std::string qMacAddress)
{
    return SwitchMemory::searchMacAddressTableByQuantumMacAddress(qMacAddress, 'I');
}

std::string SwitchMemory::getQuantumInterfaceFromMacTableByPublicMac(std::string macAddress)
{
    return SwitchMemory::searchMacAddressTableByMacAddress(macAddress, 'X');
}

bool SwitchMemory::entryExist(std::string srcMac)
{
    bool result = false;
    for(int i=0; i<sessionStateTable.size(); i++)
    {
        SessionStateEntry *session = (SessionStateEntry *) this->sessionStateTable[i];
        if(strcmp(session->getSrcMac(),srcMac.c_str()) == 0)
        {
            result = true;
        }
        else
        {
            result = false;
        }
    }
    return result;
}

std::string SwitchMemory::searchMacAddressTableByMacAddress(std::string macAddress, char query)
{
    std::string queryResult = "";
    for(int i=0; i<macAddressTable.size(); i++)
    {
        MacTableEntry *macTableEntry = (MacTableEntry *) this->macAddressTable[i];
        if(strcmp(macTableEntry->getMacAddress(), macAddress.c_str()) == 0)
        {
            switch(query)
            {
                case 'Q':
                    queryResult = macTableEntry->getQuantumMacAddress();
                    break;
                case 'I':
                    queryResult = macTableEntry->getInterface();
                    break;
                case 'X':
                    queryResult = macTableEntry->getQuantumInterfaceId();
                    break;
            }
        }
    }
    return queryResult;
}

std::string SwitchMemory::searchMacAddressTableByInterface(std::string interface, char query)
{
    std::string queryResult = "";
    for(int i=0; i<macAddressTable.size(); i++)
    {
        MacTableEntry *macTableEntry = (MacTableEntry *) this->macAddressTable[i];
        if(strcmp(macTableEntry->getInterface(), interface.c_str()) == 0 && macTableEntry->getType() == 0)
        {
            switch(query)
            {
                case 'Q':
                    queryResult = macTableEntry->getQuantumMacAddress();
                    break;
                case 'M':
                    queryResult = macTableEntry->getMacAddress();
                    break;
                case 'I':
                    queryResult = macTableEntry->getQuantumInterfaceId();
                    break;
            }
        }
    }
    return queryResult;
}

std::string SwitchMemory::searchMacAddressTableByQuantumMacAddress(std::string qMacAddress, char query)
{
    std::string queryResult = "";
    for(int i=0; i<macAddressTable.size(); i++)
    {
        MacTableEntry *macTableEntry = (MacTableEntry *) this->macAddressTable[i];
        if(strcmp(macTableEntry->getQuantumMacAddress(), qMacAddress.c_str()) == 0)
        {
            switch(query)
            {
                case 'M':
                    queryResult = macTableEntry->getMacAddress();
                    break;
                case 'I':
                    queryResult = macTableEntry->getQuantumInterfaceId();
                    break;
            }
        }
    }
    return queryResult;
}

QuantumSubInterfaceBinding SwitchMemory::getQuantumBindingTable(int index)
{
    QuantumSubInterfaceBinding *quantumBindingEntry = (QuantumSubInterfaceBinding *) this->quantumSubInterfaceBinding[index];
    return *quantumBindingEntry;
}

void SwitchMemory::addQuantumBindingTableEntry(QuantumSubInterfaceBinding *quantumBindingEntry)
{
    this->quantumSubInterfaceBinding.add(quantumBindingEntry);
}

int SwitchMemory::getQuantumBindingTableSize()
{
    return this->quantumSubInterfaceBinding.size();
}

std::string SwitchMemory::getExitInterfaceFromBindingTable(std::string src, std::string des)
{
    std::string exitInterface = "";
    for(int i=0; i<quantumSubInterfaceBinding.size(); i++)
    {
        QuantumSubInterfaceBinding *binding = (QuantumSubInterfaceBinding *)this->quantumSubInterfaceBinding[i];
        if(strcmp(binding->getSourceInterface(), src.c_str()) == 0 && strcmp(binding->getDestinationInterface(), des.c_str()) == 0)
        {
            exitInterface = binding->getSourceSubInterface();
            break;
        }
    }
    return exitInterface;
}

SessionStateEntry SwitchMemory::getsessionStateTableEntry(int index)
{
    SessionStateEntry *sessionStateEntry = (SessionStateEntry *) this->sessionStateTable[index];
    return *sessionStateEntry;
}

void SwitchMemory::addSessionStateTableEntry(SessionStateEntry *sessionStateEntry)
{
    this->sessionStateTable.add(sessionStateEntry);
}

int SwitchMemory::getSessionStateTableSize()
{
    return this->sessionStateTable.size();
}

ArpTableEntry SwitchMemory::getArpTableEntry(int index)
{
    ArpTableEntry *arpTableEntry = (ArpTableEntry *) this->arpTable[index];
    return *arpTableEntry;
}

void SwitchMemory::addArpTableEntry(ArpTableEntry *arpTableEntry)
{
    this->arpTable.add(arpTableEntry);
}

int SwitchMemory::getArpTableSize()
{
    return this->arpTable.size();
}
