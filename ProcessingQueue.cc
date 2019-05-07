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

class ProcessingQueue : public cSimpleModule
{
protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

Define_Module(ProcessingQueue);

void ProcessingQueue::initialize()
{

}
void ProcessingQueue::handleMessage(cMessage *msg)
{
    if(strcmp(msg->par("type").stringValue(),"initQKD") == 0)
    {
        send(msg,"processorCommunication$o");
    }
    else if(strcmp(msg->par("type").stringValue(),"initQkdRespons") == 0 || strcmp(msg->par("type").stringValue(),"qkdRequest") == 0)
    {
        std::string interface = msg->par("interface").stringValue();
        interface.append("$o");
        send(msg,interface.c_str());
    }
    else if(strcmp(msg->par("type").stringValue(),"networkDiscovery") == 0)
    {
        send(msg,"processorCommunication$o");
    }
    else
    {
        send(msg,"processorCommunication$o");
    }
}






