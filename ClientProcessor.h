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

    std::string convertToBinary(int initialKey);
    std::string compareBasis(std::string statesUsed, std::string receivedStates, std::string randomBits);

public:
    void initializeNetwork();
    void initiateQKDRequest(std::string source, std::string destination);
    void printMacTable();
    void printKeyTable();
};



#endif /* CLIENTPROCESSOR_H_ */
