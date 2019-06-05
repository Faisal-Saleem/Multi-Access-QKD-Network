/*
 * Client.cc
 *
 *  Created on: 3 Apr 2019
 *      Author: Faisal
 */

#include <string.h>
#include <omnetpp.h>
#include <bitset>
#include <iostream>

using namespace omnetpp;

class ClientQuantumInterface : public cSimpleModule
{
protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

Define_Module(ClientQuantumInterface);

void ClientQuantumInterface::initialize()
{

}
void ClientQuantumInterface::handleMessage(cMessage *msg)
{
    cGate *gate = msg->getArrivalGate();
    if(gate->isName("quantumChannelCommunication$i"))
    {
        int randomGate;
        double x = rand()/static_cast<double>(RAND_MAX+1);
        randomGate = 0 + static_cast<int>( x * (2 - 0) );
        if(randomGate == 1)
        {
            send(msg,"diagonal");
        }
        else
        {
            send(msg,"flat");
        }
    }
    else
    {
        send(msg,"quantumChannelCommunication$o");
    }
}




