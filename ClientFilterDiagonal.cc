/*
 * ClientFilterDaigonal.cc
 *
 *  Created on: 7 Apr 2019
 *      Author: Faisal
 */

#include <string.h>
#include <omnetpp.h>
#include <bitset>
#include <iostream>

using namespace omnetpp;

class ClientFilterDiagonal : public cSimpleModule
{
protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

Define_Module(ClientFilterDiagonal);

void ClientFilterDiagonal::initialize()
{

}
void ClientFilterDiagonal::handleMessage(cMessage *msg)
{
    //send(msg,"publicInterface$o");
}







