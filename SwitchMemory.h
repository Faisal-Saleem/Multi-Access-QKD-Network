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

/*! \class SwitchMemory
 *  \brief Class to hold the objects in memory
 */


#ifndef __QUANTUM_KEY_DISTRIBUTION_SWITCHMEMORY_H_
#define __QUANTUM_KEY_DISTRIBUTION_SWITCHMEMORY_H_

#include <omnetpp.h>
#include <ctime>
#include "MacTableEntry_m.h"
#include "QuantumSubInterfaceBinding_m.h"
#include "SessionStateEntry_m.h"
#include "ArpTableEntry_m.h"

using namespace omnetpp;

/*! \enum QueryType
 *  \brief Enumerator to query the MAC Address Table
 */
enum QueryType
{
    macAddress,
    qMacAddres,
    interface,
    qInterface
};

class SwitchMemory : public cSimpleModule
{
  private:
    cArray macAddressTable;
    cArray quantumSubInterfaceBinding;
    cArray arpTable;
    cArray sessionStateTable;
    std::string searchMacAddressTableByMacAddress(std::string macAddress, char query);
    std::string searchMacAddressTableByInterface(std::string interface, char query);
    std::string searchMacAddressTableByQuantumMacAddress(std::string interface, char query);
    std::string searchSessionStateTable(QueryType searchBy, std::string searchValue, char returnValue);

  public:
    // MAC Address Table Methods
    int macEntryIndex;
    MacTableEntry getMacTable(int index);
    void addMacTableEntry(MacTableEntry *macTableEntry);
    int getMacTableSize();
    std::string getQuantumInterfaceMacAddressFromMacTable(std::string publicInterfaceMacAddress);
    std::string getInterfaceIdFromMacTable(std::string macAddress);
    std::string getMacAddressOfInterfaceFromMacTable(std::string interface);
    std::string getQuantumMacAddressOfInterfaceFromMacTable(std::string interface);
    std::string getQuantumInterfaceFromMacTable(std::string qMacAddress);
    std::string getQuantumInterfaceFromMacTableByPublicMac(std::string macAddress);
    std::string getInterface(std::string macAddress);
    bool entryExist(std::string srcMac, std::string desMac);


    // Quantum Binding Table Methods
    int quantumBindingEntryIndex;
    QuantumSubInterfaceBinding getQuantumBindingTable(int index);
    void addQuantumBindingTableEntry(QuantumSubInterfaceBinding *quantumBindingEntry);
    int getQuantumBindingTableSize();
    std::string getExitInterfaceFromBindingTable(std::string src, std::string des);

    // ARP Table
    int arpEntryIndex;
    ArpTableEntry getArpTableEntry(int index);
    void addArpTableEntry(ArpTableEntry *arpTableEntry);
    int getArpTableSize();

    // Session State Table Methods;
    int sessionsStateEntryIndex;
    SessionStateEntry getsessionStateTableEntry(int index);
    void addSessionStateTableEntry(SessionStateEntry *sessionStateEntry);
    int getSessionStateTableSize();

  protected:
    virtual void initialize(int stage) override;
    virtual int numInitStages() const override;
};

#endif
