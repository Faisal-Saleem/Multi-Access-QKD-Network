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

class Switch : public cModule
{
    protected:
        virtual void initialize(int stage) override;
        virtual int numInitStages() const override;
};

Define_Module(Switch);

void Switch::initialize(int stage)
{

}

int Switch::numInitStages() const
{
    return 2;
}


