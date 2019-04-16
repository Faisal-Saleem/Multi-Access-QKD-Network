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

#ifndef __QUANTUM_KEY_DISTRIBUTION_SWITCHMEMORY_H_
#define __QUANTUM_KEY_DISTRIBUTION_SWITCHMEMORY_H_

#include <omnetpp.h>
#include "MacTableEntry_m.h"

using namespace omnetpp;

class SwitchMemory : public cSimpleModule
{
  private:
    cArray macAddressTable;
    cArray quantumSubInterfaceBinding;
  public:
    void printMacAddressTable();
    void printQuantumSubinterfaceBindingTable();
    MacTableEntry getMacTable(int index);
    void addMacTableEntry(MacTableEntry *macTableEntry);
    int getMacTableSize();

    int macEntryIndex;
  protected:
    virtual void initialize(int stage) override;
    virtual int numInitStages() const override;
    void prepareMacAddressTable();
    void bindInterface(int identity, std::string interface, std::string quantumInterface, int type);
    void prepareQuantumSubInterfaceBindingTable();
    void bindSubInterface(std::string identity, std::string sourceInterface, std::string sourceSubInterface, std::string destinationInterface, std::string destinationSubInterface, int status);
};

#endif