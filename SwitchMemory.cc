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
        EV<<"[*] Prepairing Quantum Sub Interface Binding Table\n";
        SwitchMemory::printQuantumSubinterfaceBindingTable();
    }
    if(stage == 1)
    {
        SwitchMemory::prepareMacAddressTable();
        EV<<"[*] Prepairing Quantum MAC Address Table\n";
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
    SwitchMemory::bindInterface(1,"f01","q01",0);
    SwitchMemory::bindInterface(1,"f02","q02",0);
    SwitchMemory::bindInterface(1,"f03","q03",0);
    SwitchMemory::bindInterface(1,"f04","q04",0);
    EV<<"[*] Done\n";
}

void SwitchMemory::bindInterface(int identity, std::string interface, std::string quantumInterface, int type)
{
    MacTableEntry *macTableEntry = new MacTableEntry();
    macTableEntry->setIdentity(identity);
    macTableEntry->setInterface(this->getParentModule()->getSubmodule(interface.c_str())->getName());
    macTableEntry->setMacAddress(this->getParentModule()->getSubmodule(interface.c_str())->par("macAddress").stringValue());
    macTableEntry->setQuantumInterfaceId(this->getParentModule()->getSubmodule(quantumInterface.c_str())->getName());
    macTableEntry->setQuantumMacAddress(this->getParentModule()->getSubmodule(quantumInterface.c_str())->par("macAddress").stringValue());
    macTableEntry->setType(type);
    macAddressTable.add(macTableEntry);
}

void SwitchMemory::printMacAddressTable()
{
    EV<<"[*] Quantum MAC Address Table\n";
    EV<<"=============================================================================================\n";
    EV<<"  Identity     Interface     MacAddress     Q_Interface          Q_MacAddress          Type   \n";
    EV<<"=============================================================================================\n";
    for(int i=0; i<macAddressTable.size(); i++)
    {
        MacTableEntry *macTableEntry = (MacTableEntry *) macAddressTable[i];
        EV<<"      "
                <<macTableEntry->getIdentity()
                <<"           "
                <<macTableEntry->getInterface()
                <<"     "
                <<macTableEntry->getMacAddress()
                <<"      "
                <<macTableEntry->getQuantumInterfaceId()
                <<"          "
                <<macTableEntry->getQuantumMacAddress()
                <<"          "
                <<macTableEntry->getType()
                <<"\n";
    }
    EV<<"=============================================================================================\n";
}

void SwitchMemory::prepareQuantumSubInterfaceBindingTable()
{
    EV<<"[*] Binding Quantum Sub Interface\n";
    SwitchMemory::bindSubInterface("01","q01","subInterface2$o","q02","subInterface1$i",0);
    SwitchMemory::bindSubInterface("02","q02","subInterface3$o","q03","subInterface2$i",0);
    SwitchMemory::bindSubInterface("03","q03","subInterface4$o","q04","subInterface3$i",0);
    SwitchMemory::bindSubInterface("04","q01","subInterface4$o","q04","subInterface1$i",0);
    SwitchMemory::bindSubInterface("05","q02","subInterface4$o","q04","subInterface2$i",0);
    SwitchMemory::bindSubInterface("06","q03","subInterface1$o","q01","subInterface3$i",0);
    SwitchMemory::bindSubInterface("07","q02","subInterface1$o","q01","subInterface2$i",0);
    SwitchMemory::bindSubInterface("08","q03","subInterface2$o","q02","subInterface3$i",0);
    SwitchMemory::bindSubInterface("09","q04","subInterface3$o","q03","subInterface4$i",0);
    SwitchMemory::bindSubInterface("10","q04","subInterface1$o","q01","subInterface4$i",0);
    SwitchMemory::bindSubInterface("11","q04","subInterface2$o","q02","subInterface4$i",0);
    SwitchMemory::bindSubInterface("12","q01","subInterface3$o","q03","subInterface1$i",0);
    EV<<"[*] Subinterface Binding Done\n";
}

void SwitchMemory::bindSubInterface(std::string identity, std::string sourceInterface,std::string sourceSubInterface,std::string destinationInterface, std::string destinationSubInterface, int status)
{
    QuantumSubInterfaceBinding *subInterfaceBindingEntry = new QuantumSubInterfaceBinding();
    subInterfaceBindingEntry->setIdentity(identity.c_str());
    subInterfaceBindingEntry->setConnectionId(this->getParentModule()->getSubmodule(sourceInterface.c_str())->gate(sourceSubInterface.c_str())->getConnectionId());
    subInterfaceBindingEntry->setSourceInterface(this->getParentModule()->getSubmodule(sourceInterface.c_str())->getName());
    subInterfaceBindingEntry->setSourceSubInterface(this->getParentModule()->getSubmodule(sourceInterface.c_str())->gate(sourceSubInterface.c_str())->getBaseName());
    subInterfaceBindingEntry->setDestinationInterface(this->getParentModule()->getSubmodule(destinationInterface.c_str())->getName());
    subInterfaceBindingEntry->setDestinationSubInterface(this->getParentModule()->getSubmodule(destinationInterface.c_str())->gate(destinationSubInterface.c_str())->getBaseName());
    subInterfaceBindingEntry->setStatus(status);
    quantumSubInterfaceBinding.add(subInterfaceBindingEntry);
}

void SwitchMemory::printQuantumSubinterfaceBindingTable()
{
    EV<<"[*] Quantum Sub Interface Binding Table\n";
    EV<<"===================================================================\n";
    EV<<"  Id   ConId     Src     Src-Sub      Dst     Dst-Sub      Type   \n";
    EV<<"===================================================================\n";
    for(int i=0; i<quantumSubInterfaceBinding.size(); i++)
    {
        QuantumSubInterfaceBinding *subInterfaceBindingEntry = (QuantumSubInterfaceBinding *) quantumSubInterfaceBinding[i];
        EV<<"  "<<subInterfaceBindingEntry->getIdentity()
                <<"     "<<subInterfaceBindingEntry->getConnectionId()
                <<"       "<<subInterfaceBindingEntry->getSourceInterface()
                <<"  "<<subInterfaceBindingEntry->getSourceSubInterface()
                <<"   "<<subInterfaceBindingEntry->getDestinationInterface()
                <<"   "<<subInterfaceBindingEntry->getDestinationSubInterface()
                <<"   "<<subInterfaceBindingEntry->getStatus()
                <<"\n";
    }
    EV<<"===================================================================\n";
}
