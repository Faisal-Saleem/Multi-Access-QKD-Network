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

cArray macAddressTable("macAddress");
cArray quantumSubInterfaceBinding("subInterfaceBinding");

void SwitchMemory::initialize(int stage)
{
    if(stage == 0)
    {
        SwitchMemory::prepareQuantumSubInterfaceBindingTable();
    }
    else if(stage == 1)
    {
        SwitchMemory::prepareMacAddressTable();
        EV<<"[*] Preparing Quantum MAC Address Table\n";
        SwitchMemory::printMacAddressTable();
    }
}

int SwitchMemory::numInitStages() const
{
    return 2;
}

void SwitchMemory::prepareMacAddressTable()
{
    EV<<"[*] Binding Public and Quantum Channels\n";
    SwitchMemory::bindInterface(1,this->getParentModule()->getSubmodule("f01")->getName() ,this->getParentModule()->getSubmodule("f01")->par("macAddress").stringValue(),this->getParentModule()->getSubmodule("q01")->getName() ,this->getParentModule()->getSubmodule("q01")->par("macAddress").stringValue(),0);
    SwitchMemory::bindInterface(2,this->getParentModule()->getSubmodule("f02")->getName() ,this->getParentModule()->getSubmodule("f02")->par("macAddress").stringValue(),this->getParentModule()->getSubmodule("q02")->getName() ,this->getParentModule()->getSubmodule("q02")->par("macAddress").stringValue(),0);
    SwitchMemory::bindInterface(3,this->getParentModule()->getSubmodule("f03")->getName() ,this->getParentModule()->getSubmodule("f03")->par("macAddress").stringValue(),this->getParentModule()->getSubmodule("q03")->getName() ,this->getParentModule()->getSubmodule("q03")->par("macAddress").stringValue(),0);
    SwitchMemory::bindInterface(4,this->getParentModule()->getSubmodule("f04")->getName() ,this->getParentModule()->getSubmodule("f04")->par("macAddress").stringValue(),this->getParentModule()->getSubmodule("q04")->getName() ,this->getParentModule()->getSubmodule("q04")->par("macAddress").stringValue(),0);
    EV<<"[*] Done\n";
}

void SwitchMemory::bindInterface(int identity, std::string interface, std::string macAddress, std::string quantumInterfaceId, std::string quantumMacAddress, int type)
{
    MacTableEntry *macTableEntry = new MacTableEntry();
    macTableEntry->setIdentity(identity);
    macTableEntry->setInterface(interface.c_str());
    macTableEntry->setMacAddress(macAddress.c_str());
    macTableEntry->setQuantumInterfaceId(quantumInterfaceId.c_str());
    macTableEntry->setQuantumMacAddress(quantumMacAddress.c_str());
    macTableEntry->setType(type);
    macAddressTable.add(macTableEntry);
}

void SwitchMemory::printMacAddressTable()
{
    EV<<"[*] Quantum MAC Address Table ready\n";
    EV<<"=============================================================================================\n";
    EV<<"  Identity     Interface     MacAddress     Q_Interface          Q_MacAddress          Type   \n";
    EV<<"=============================================================================================\n";
    for(int i=0; i<macAddressTable.size(); i++)
    {
        MacTableEntry *macTableEntry = (MacTableEntry *) macAddressTable[i];
        EV<<"      "<<macTableEntry->getIdentity()<<"           "<<macTableEntry->getInterface()<<"     "<<macTableEntry->getMacAddress()<<"      "<<macTableEntry->getQuantumInterfaceId()<<"          "<<macTableEntry->getQuantumMacAddress()<<"          "<<macTableEntry->getType()<<"\n";
    }
    EV<<"=============================================================================================\n";
}

void SwitchMemory::prepareQuantumSubInterfaceBindingTable()
{
    EV<<"[*] Bind Quantum Sub Interface\n";
    //EV<<"Gate Names "<<this->getParentModule()->getSubmodule("q01")->gate("sub$i[$0$]")->str();
    //SwitchMemory::bindSubInterface(1, this->getParentModule()->getSubmodule("q01")->gate("sub0")->getConnectionId(), destinationInterface, status)
}

void SwitchMemory::bindSubInterface(int identity, std::string sourceInterface, std::string destinationInterface, int status)
{
    QuantumSubInterfaceBinding *subInterfaceBindingEntry = new QuantumSubInterfaceBinding();
    subInterfaceBindingEntry->setIdentity(identity);
    subInterfaceBindingEntry->setSourceInterface(sourceInterface.c_str());
    subInterfaceBindingEntry->setDestinationInterface(destinationInterface.c_str());
    subInterfaceBindingEntry->setStatus(status);
    quantumSubInterfaceBinding.add(subInterfaceBindingEntry);
}

void SwitchMemory::printQuantumSubinterfaceBindingTable()
{

}
