/*
 * ClientProcessor.h
 *
 *  Created on: 23 Apr 2019
 *      Author: Faisal
 */

#ifndef CLIENTPROCESSOR_H_
#define CLIENTPROCESSOR_H_

#include <string.h>
#include <omnetpp.h>
#include <bitset>
#include <iostream>

using namespace omnetpp;

class ClientProcessor : public cSimpleModule
{
protected:
    virtual void initialize(int stage) override;
    virtual void handleMessage(cMessage *msg) override;
    virtual int numInitStages() const override;

public:
    void initializeNetwork();
    void initiateQKDRequest(std::string source, std::string destination);
};



#endif /* CLIENTPROCESSOR_H_ */