#ifndef __QUANTUM_KEY_DISTRIBUTION_CLIENTMEMORY_H_
#define __QUANTUM_KEY_DISTRIBUTION_CLIENTMEMORY_H_

#include <omnetpp.h>
#include "MacTableEntry_m.h"
#include "QuantumKeyEntry_m.h"

using namespace omnetpp;

class ClientMemory : public cSimpleModule
{
private:
    cArray quantumTable;
    cArray quantumKey;
    std::string initialKey;
    std::string initialKeyBin;
    std::string polarizationStates;

public:
    MacTableEntry getMacTable(int index);
    void addMacTableEntry(MacTableEntry *macTableEntry);
    int getMacTableSize();

    QuantumKeyEntry getQuantumKey(int index);
    void addQautumKey(QuantumKeyEntry *key);
    int getNumberOfKey();
    int getPendingTransaction();
    std::string getPendingKeyMacAddress();
    void setPendingKey(std::string key);

    std::string getInitialKey();
    void setInitialKey(std::string key);

    std::string getPolarizationStates();
    void setPolarizationStates(std::string states);

    std::string getInitialKeyBin();
    void setInitialKeyBin(std::string bin);

protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
};

#endif
