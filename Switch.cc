/*
 * Switch.cc
 *
 *  Created on: 7 Apr 2019
 *      Author: Faisal
 */


#include <string.h>
#include <omnetpp.h>
#include <bitset>
#include <iostream>
#include "MacTableEntry_m.h"

using namespace omnetpp;
cArray macAddressTable("macAddress");
class Switch : public cModule
{
/*public:
    cArray *macAddressTable;*/
protected:
    //virtual void initialize() override;
    //virtual void handleMessage(cMessage *msg) override;
    virtual void initialize(int stage) override;
    virtual int numInitStages() const override;
    void bindInterface(int identity, std::string interface, std::string macAddress, std::string quantumInterfaceId, std::string quantumMacAddress, int type);
};

Define_Module(Switch);

/*
void Switch::initialize()
{
    EV<<"\n\rSRC MAC : "<<getParentModule()->par("macAddressTable").stringValue()<<"\n\r";
    EV<<"\n\rExit Interface :"<<getParentModule()->gate("quantumInterface$o")->str()<<"\n\r";
}


void Switch::handleMessage(cMessage *msg)
{
    //send(msg,"publicInterface$o");
}
*/
void Switch::initialize(int stage)
{
    if(stage == 0)
    {
        //macAddressTable= new cArray();
    } else if(stage == 1)
    {
        Switch::bindInterface(1,this->getSubmodule("f01")->getName() ,this->getSubmodule("f01")->par("macAddress").stringValue(),this->getSubmodule("q01")->getName() ,this->getSubmodule("q01")->par("macAddress").stringValue(),0);
        Switch::bindInterface(2,this->getSubmodule("f02")->getName() ,this->getSubmodule("f02")->par("macAddress").stringValue(),this->getSubmodule("q02")->getName() ,this->getSubmodule("q02")->par("macAddress").stringValue(),0);
        Switch::bindInterface(3,this->getSubmodule("f03")->getName() ,this->getSubmodule("f03")->par("macAddress").stringValue(),this->getSubmodule("q03")->getName() ,this->getSubmodule("q03")->par("macAddress").stringValue(),0);
        Switch::bindInterface(4,this->getSubmodule("f04")->getName() ,this->getSubmodule("f04")->par("macAddress").stringValue(),this->getSubmodule("q04")->getName() ,this->getSubmodule("q04")->par("macAddress").stringValue(),0);

        EV<<"===========================================================================================================\n";
        EV<<"|\tIdentity\tInterface\tMacAddress\tQ Interface\tQ MacAddress\tType\t|\n";
        EV<<"===========================================================================================================\n";
        for(int i=0; i<macAddressTable.size(); i++)
        {
            MacTableEntry *macTableEntry = (MacTableEntry *) macAddressTable[i];
            EV<<"\t"<<macTableEntry->getIdentity()<<"\t"<<macTableEntry->getInterface()<<"\t"<<macTableEntry->getMacAddress()<<"\t"<<macTableEntry->getQuantumInterfaceId()<<"\t"<<macTableEntry->getQuantumMacAddress()<<"\t"<<macTableEntry->getType()<<"\n";
        }


        //MacTableEntry *macTableEntry = new MacTableEntry();
        //macTableEntry->setIdentity(1);
        //macTableEntry->setMacAddress(this->getSubmodule("f01")->par("macAddress").stringValue());
        //macTableEntry->setQuantumMacAddress(this->getSubmodule("q01")->par("macAddress").stringValue());
        //EV<<macAddressTable[0];
        /*EV<<this->getSubmodule("f02")->par("macAddress").str();
        EV<<this->getSubmodule("f03")->par("macAddress").str();
        EV<<this->getSubmodule("f04")->par("macAddress").str();
        EV<<this->getSubmodule("q01")->par("macAddress").str();
        EV<<this->getSubmodule("q02")->par("macAddress").str();
        EV<<this->getSubmodule("q03")->par("macAddress").str();
        EV<<this->getSubmodule("q04")->par("macAddress").str();*/
        //this->getSubmodule("macAddressTable")->par("macAddress").setStringValue(this->getSubmodule("q04")->par("macAddress").str());
    }
}

int Switch::numInitStages() const
{
    return 2;
}

void Switch::bindInterface(int identity, std::string interface, std::string macAddress, std::string quantumInterfaceId, std::string quantumMacAddress, int type)
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




