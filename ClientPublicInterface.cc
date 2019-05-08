/*
 * ClientPublicInterface.cc
 *
 *  Created on: 3 Apr 2019
 *      Author: Faisal
 */

#include <string.h>
#include <omnetpp.h>
#include <bitset>
#include <iostream>

using namespace omnetpp;

class ClientPublicInterface : public cSimpleModule
{
protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

Define_Module(ClientPublicInterface);

void ClientPublicInterface::initialize()
{

}
void ClientPublicInterface::handleMessage(cMessage *msg)
{
    if(strcmp(msg->par("type").stringValue(),"initQkdRespons") == 0 || strcmp(msg->par("type").stringValue(),"qkdRequest") == 0 || strcmp(msg->par("type").stringValue(),"QKD-ACK") == 0)
    {
        send(msg,"processorCommunication$o");
    }
    else
    {
        send(msg,"externalCommunication$o");
    }
}






