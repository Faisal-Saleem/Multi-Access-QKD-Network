#ifndef __QUANTUM_KEY_DISTRIBUTION_CLIENTMEMORY_H_
#define __QUANTUM_KEY_DISTRIBUTION_CLIENTMEMORY_H_

#include <omnetpp.h>
#include "MacTableEntry_m.h"

using namespace omnetpp;

class ClientMemory : public cSimpleModule
{
private:
    cArray quantumTable;
public:
    MacTableEntry getMacTable(int index);
    void addMacTableEntry(MacTableEntry *macTableEntry);
    int getMacTableSize();
protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
};

#endif
