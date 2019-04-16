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

#include "SwitchMemory.h"
#include <string.h>
#include <bitset>
#include <iostream>
#include "MacTableEntry_m.h"
#include "QuantumSubInterfaceBinding_m.h"

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
