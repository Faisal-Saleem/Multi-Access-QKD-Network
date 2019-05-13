/*
 * ClientQSGenerator.cc
 *
 *  Created on: 7 Apr 2019
 *      Author: Faisal
 */


#include <string.h>
#include <omnetpp.h>
#include <bitset>
#include <iostream>

using namespace omnetpp;

class QuantumStatesGenerator : public cSimpleModule
{
protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

Define_Module(QuantumStatesGenerator);

void QuantumStatesGenerator::initialize()
{

}

void QuantumStatesGenerator::handleMessage(cMessage *msg)
{
    /*
     * Gate DL,  Bit Value 0,    Polarisation State \
     * Gate V,   Bit Value 0,    Polarisation State |
     * Gate DR,  Bit Value 1,    Polarisation State /
     * Gate H,   Bit Value 1,    Polarisation State -
     */

    int randomGate;
    std::string polarizationFilterUsed;

    cGate *gate = msg->getArrivalGate();
    if(gate->isName("processorCommunication$i"))
    {
        cQueue queue("quantumStatesQueue");
        std::string key = msg->par("value").stringValue();
        delete msg;
        char *stat = new char[key.length()+1];

        strcpy(stat, key.c_str());
        for(int i=0; i<key.length(); i++)
        {
            std::string j = std::string(1, stat[i]);
            std::string polarization;
            if (j == "0") {
                randomGate = (rand() % 2) + 0;
            }
            else {
                randomGate = (rand() % 2) + 0;
                randomGate = randomGate + 2;
            }
            cMessage *quantumState = new cMessage(j.c_str());

            queue.insert(quantumState);
            while (!queue.isEmpty()) {

                msg = (cMessage *) queue.pop();
                std::string exitGate = "";
                if(randomGate == 0)
                {
                    exitGate = "DL";
                }
                else if(randomGate == 1)
                {
                    exitGate = "V";
                }
                else if(randomGate == 2)
                {
                    exitGate = "DR";
                }
                else
                {
                    exitGate = "H";
                }
                sendDelayed(msg,0,exitGate.c_str());
            }

            if (randomGate == 0) {
                polarizationFilterUsed.append("\\");
            }
            else if (randomGate == 1) {
                polarizationFilterUsed.append("|");
            }
            else if (randomGate == 2) {
                polarizationFilterUsed.append("/");
            }
            else {
                polarizationFilterUsed.append("-");
            }
        }
        cMessage *polarizationFilters = new cMessage("polarizationFilterUsed");
        polarizationFilters->addPar("type").setStringValue("pfilter");
        polarizationFilters->addPar("polarizationFilterUsed").setStringValue(polarizationFilterUsed.c_str());
        send(polarizationFilters,"processorCommunication$o");
    }
}






