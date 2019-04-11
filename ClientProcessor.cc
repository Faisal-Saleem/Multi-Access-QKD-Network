/*
 * ClientProcessor.cc
 *
 *  Created on: 7 Apr 2019
 *      Author: Faisal
 */

#include <string.h>
#include <omnetpp.h>
#include <bitset>
#include <iostream>

using namespace omnetpp;

class ClientProcessor : public cSimpleModule
{
protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

Define_Module(ClientProcessor);

void ClientProcessor::initialize()
{
    cPacket *initialDataPacket = new cPacket("data");
    initialDataPacket->setByteLength(1024);
    initialDataPacket->addPar(getParentModule()->par("macAddress"));

    //cModule *cmod = this->getParentModule();
    //cMessage *msg = new cMessage(initialDataPacket);
    //EV<<"\n\rSRC MAC : "<<getParentModule()->par("macAddress").stringValue()<<"\n\r";
    //EV<<"\n\rExit Interface :"<<getParentModule()->gate("quantumInterface$o")->str()<<"\n\r";
    send(initialDataPacket, "quantumInterfaceCommunication$o");
}
void ClientProcessor::handleMessage(cMessage *msg)
{
    send(msg,"quantumInterfaceCommunication$o");
}







