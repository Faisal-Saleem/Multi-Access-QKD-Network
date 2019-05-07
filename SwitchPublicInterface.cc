/*
 * ProcessingQueue.cc
 *
 *  Created on: 3 Apr 2019
 *      Author: Faisal
 */

#include <string.h>
#include <omnetpp.h>
#include <bitset>
#include <iostream>

using namespace omnetpp;

class SwitchPublicInterface : public cSimpleModule
{
protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

Define_Module(SwitchPublicInterface);

void SwitchPublicInterface::initialize()
{

}
void SwitchPublicInterface::handleMessage(cMessage *msg)
{
    if(strcmp(msg->par("type").stringValue(),"initQKD") == 0)
    {
        msg->addPar("interface").setStringValue(this->getName());
        msg->addPar("srcInterfaceMacAddress").setStringValue(this->par("macAddress").stringValue());
        send(msg,"processorCommuniation$o");
    }
    else if(strcmp(msg->par("type").stringValue(),"initQkdRespons") == 0 || strcmp(msg->par("type").stringValue(),"qkdRequest") == 0)
    {
        send(msg,"publicChannelCommunication$o");
    }
    else if(strcmp(msg->par("type").stringValue(),"networkDiscovery") == 0)
    {
        msg->addPar("interface").setStringValue(this->getName());
        msg->addPar("srcInterfaceMacAddress").setStringValue(this->par("macAddress").stringValue());
        send(msg,"processorCommuniation$o");
    }
    else
    {
        msg->addPar("interface").setStringValue(this->getName());
        msg->addPar("srcInterfaceMacAddress").setStringValue(this->par("macAddress").stringValue());
        send(msg,"processorCommuniation$o");
    }
}






