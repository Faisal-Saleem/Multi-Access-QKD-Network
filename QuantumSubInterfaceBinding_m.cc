//
// Generated file, do not edit! Created by nedtool 5.4 from QuantumSubInterfaceBinding.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wshadow"
#  pragma clang diagnostic ignored "-Wconversion"
#  pragma clang diagnostic ignored "-Wunused-parameter"
#  pragma clang diagnostic ignored "-Wc++98-compat"
#  pragma clang diagnostic ignored "-Wunreachable-code-break"
#  pragma clang diagnostic ignored "-Wold-style-cast"
#elif defined(__GNUC__)
#  pragma GCC diagnostic ignored "-Wshadow"
#  pragma GCC diagnostic ignored "-Wconversion"
#  pragma GCC diagnostic ignored "-Wunused-parameter"
#  pragma GCC diagnostic ignored "-Wold-style-cast"
#  pragma GCC diagnostic ignored "-Wsuggest-attribute=noreturn"
#  pragma GCC diagnostic ignored "-Wfloat-conversion"
#endif

#include <iostream>
#include <sstream>
#include "QuantumSubInterfaceBinding_m.h"

namespace omnetpp {

// Template pack/unpack rules. They are declared *after* a1l type-specific pack functions for multiple reasons.
// They are in the omnetpp namespace, to allow them to be found by argument-dependent lookup via the cCommBuffer argument

// Packing/unpacking an std::vector
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<T,A>& v)
{
    int n = v.size();
    doParsimPacking(buffer, n);
    for (int i = 0; i < n; i++)
        doParsimPacking(buffer, v[i]);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<T,A>& v)
{
    int n;
    doParsimUnpacking(buffer, n);
    v.resize(n);
    for (int i = 0; i < n; i++)
        doParsimUnpacking(buffer, v[i]);
}

// Packing/unpacking an std::list
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::list<T,A>& l)
{
    doParsimPacking(buffer, (int)l.size());
    for (typename std::list<T,A>::const_iterator it = l.begin(); it != l.end(); ++it)
        doParsimPacking(buffer, (T&)*it);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::list<T,A>& l)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        l.push_back(T());
        doParsimUnpacking(buffer, l.back());
    }
}

// Packing/unpacking an std::set
template<typename T, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::set<T,Tr,A>& s)
{
    doParsimPacking(buffer, (int)s.size());
    for (typename std::set<T,Tr,A>::const_iterator it = s.begin(); it != s.end(); ++it)
        doParsimPacking(buffer, *it);
}

template<typename T, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::set<T,Tr,A>& s)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        T x;
        doParsimUnpacking(buffer, x);
        s.insert(x);
    }
}

// Packing/unpacking an std::map
template<typename K, typename V, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::map<K,V,Tr,A>& m)
{
    doParsimPacking(buffer, (int)m.size());
    for (typename std::map<K,V,Tr,A>::const_iterator it = m.begin(); it != m.end(); ++it) {
        doParsimPacking(buffer, it->first);
        doParsimPacking(buffer, it->second);
    }
}

template<typename K, typename V, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::map<K,V,Tr,A>& m)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        K k; V v;
        doParsimUnpacking(buffer, k);
        doParsimUnpacking(buffer, v);
        m[k] = v;
    }
}

// Default pack/unpack function for arrays
template<typename T>
void doParsimArrayPacking(omnetpp::cCommBuffer *b, const T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimPacking(b, t[i]);
}

template<typename T>
void doParsimArrayUnpacking(omnetpp::cCommBuffer *b, T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimUnpacking(b, t[i]);
}

// Default rule to prevent compiler from choosing base class' doParsimPacking() function
template<typename T>
void doParsimPacking(omnetpp::cCommBuffer *, const T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

template<typename T>
void doParsimUnpacking(omnetpp::cCommBuffer *, T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

}  // namespace omnetpp


// forward
template<typename T, typename A>
std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec);

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
inline std::ostream& operator<<(std::ostream& out,const T&) {return out;}

// operator<< for std::vector<T>
template<typename T, typename A>
inline std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec)
{
    out.put('{');
    for(typename std::vector<T,A>::const_iterator it = vec.begin(); it != vec.end(); ++it)
    {
        if (it != vec.begin()) {
            out.put(','); out.put(' ');
        }
        out << *it;
    }
    out.put('}');
    
    char buf[32];
    sprintf(buf, " (size=%u)", (unsigned int)vec.size());
    out.write(buf, strlen(buf));
    return out;
}

Register_Class(QuantumSubInterfaceBinding)

QuantumSubInterfaceBinding::QuantumSubInterfaceBinding(const char *name, short kind) : ::omnetpp::cPacket(name,kind)
{
    this->connectionId = 0;
    this->status = 0;
}

QuantumSubInterfaceBinding::QuantumSubInterfaceBinding(const QuantumSubInterfaceBinding& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

QuantumSubInterfaceBinding::~QuantumSubInterfaceBinding()
{
}

QuantumSubInterfaceBinding& QuantumSubInterfaceBinding::operator=(const QuantumSubInterfaceBinding& other)
{
    if (this==&other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void QuantumSubInterfaceBinding::copy(const QuantumSubInterfaceBinding& other)
{
    this->identity = other.identity;
    this->connectionId = other.connectionId;
    this->sourceInterface = other.sourceInterface;
    this->sourceSubInterface = other.sourceSubInterface;
    this->destinationInterface = other.destinationInterface;
    this->destinationSubInterface = other.destinationSubInterface;
    this->status = other.status;
}

void QuantumSubInterfaceBinding::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->identity);
    doParsimPacking(b,this->connectionId);
    doParsimPacking(b,this->sourceInterface);
    doParsimPacking(b,this->sourceSubInterface);
    doParsimPacking(b,this->destinationInterface);
    doParsimPacking(b,this->destinationSubInterface);
    doParsimPacking(b,this->status);
}

void QuantumSubInterfaceBinding::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->identity);
    doParsimUnpacking(b,this->connectionId);
    doParsimUnpacking(b,this->sourceInterface);
    doParsimUnpacking(b,this->sourceSubInterface);
    doParsimUnpacking(b,this->destinationInterface);
    doParsimUnpacking(b,this->destinationSubInterface);
    doParsimUnpacking(b,this->status);
}

const char * QuantumSubInterfaceBinding::getIdentity() const
{
    return this->identity.c_str();
}

void QuantumSubInterfaceBinding::setIdentity(const char * identity)
{
    this->identity = identity;
}

int QuantumSubInterfaceBinding::getConnectionId() const
{
    return this->connectionId;
}

void QuantumSubInterfaceBinding::setConnectionId(int connectionId)
{
    this->connectionId = connectionId;
}

const char * QuantumSubInterfaceBinding::getSourceInterface() const
{
    return this->sourceInterface.c_str();
}

void QuantumSubInterfaceBinding::setSourceInterface(const char * sourceInterface)
{
    this->sourceInterface = sourceInterface;
}

const char * QuantumSubInterfaceBinding::getSourceSubInterface() const
{
    return this->sourceSubInterface.c_str();
}

void QuantumSubInterfaceBinding::setSourceSubInterface(const char * sourceSubInterface)
{
    this->sourceSubInterface = sourceSubInterface;
}

const char * QuantumSubInterfaceBinding::getDestinationInterface() const
{
    return this->destinationInterface.c_str();
}

void QuantumSubInterfaceBinding::setDestinationInterface(const char * destinationInterface)
{
    this->destinationInterface = destinationInterface;
}

const char * QuantumSubInterfaceBinding::getDestinationSubInterface() const
{
    return this->destinationSubInterface.c_str();
}

void QuantumSubInterfaceBinding::setDestinationSubInterface(const char * destinationSubInterface)
{
    this->destinationSubInterface = destinationSubInterface;
}

int QuantumSubInterfaceBinding::getStatus() const
{
    return this->status;
}

void QuantumSubInterfaceBinding::setStatus(int status)
{
    this->status = status;
}

class QuantumSubInterfaceBindingDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    QuantumSubInterfaceBindingDescriptor();
    virtual ~QuantumSubInterfaceBindingDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(QuantumSubInterfaceBindingDescriptor)

QuantumSubInterfaceBindingDescriptor::QuantumSubInterfaceBindingDescriptor() : omnetpp::cClassDescriptor("QuantumSubInterfaceBinding", "omnetpp::cPacket")
{
    propertynames = nullptr;
}

QuantumSubInterfaceBindingDescriptor::~QuantumSubInterfaceBindingDescriptor()
{
    delete[] propertynames;
}

bool QuantumSubInterfaceBindingDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<QuantumSubInterfaceBinding *>(obj)!=nullptr;
}

const char **QuantumSubInterfaceBindingDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *QuantumSubInterfaceBindingDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int QuantumSubInterfaceBindingDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 7+basedesc->getFieldCount() : 7;
}

unsigned int QuantumSubInterfaceBindingDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<7) ? fieldTypeFlags[field] : 0;
}

const char *QuantumSubInterfaceBindingDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "identity",
        "connectionId",
        "sourceInterface",
        "sourceSubInterface",
        "destinationInterface",
        "destinationSubInterface",
        "status",
    };
    return (field>=0 && field<7) ? fieldNames[field] : nullptr;
}

int QuantumSubInterfaceBindingDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='i' && strcmp(fieldName, "identity")==0) return base+0;
    if (fieldName[0]=='c' && strcmp(fieldName, "connectionId")==0) return base+1;
    if (fieldName[0]=='s' && strcmp(fieldName, "sourceInterface")==0) return base+2;
    if (fieldName[0]=='s' && strcmp(fieldName, "sourceSubInterface")==0) return base+3;
    if (fieldName[0]=='d' && strcmp(fieldName, "destinationInterface")==0) return base+4;
    if (fieldName[0]=='d' && strcmp(fieldName, "destinationSubInterface")==0) return base+5;
    if (fieldName[0]=='s' && strcmp(fieldName, "status")==0) return base+6;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *QuantumSubInterfaceBindingDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "string",
        "int",
        "string",
        "string",
        "string",
        "string",
        "int",
    };
    return (field>=0 && field<7) ? fieldTypeStrings[field] : nullptr;
}

const char **QuantumSubInterfaceBindingDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *QuantumSubInterfaceBindingDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int QuantumSubInterfaceBindingDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    QuantumSubInterfaceBinding *pp = (QuantumSubInterfaceBinding *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *QuantumSubInterfaceBindingDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    QuantumSubInterfaceBinding *pp = (QuantumSubInterfaceBinding *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string QuantumSubInterfaceBindingDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    QuantumSubInterfaceBinding *pp = (QuantumSubInterfaceBinding *)object; (void)pp;
    switch (field) {
        case 0: return oppstring2string(pp->getIdentity());
        case 1: return long2string(pp->getConnectionId());
        case 2: return oppstring2string(pp->getSourceInterface());
        case 3: return oppstring2string(pp->getSourceSubInterface());
        case 4: return oppstring2string(pp->getDestinationInterface());
        case 5: return oppstring2string(pp->getDestinationSubInterface());
        case 6: return long2string(pp->getStatus());
        default: return "";
    }
}

bool QuantumSubInterfaceBindingDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    QuantumSubInterfaceBinding *pp = (QuantumSubInterfaceBinding *)object; (void)pp;
    switch (field) {
        case 0: pp->setIdentity((value)); return true;
        case 1: pp->setConnectionId(string2long(value)); return true;
        case 2: pp->setSourceInterface((value)); return true;
        case 3: pp->setSourceSubInterface((value)); return true;
        case 4: pp->setDestinationInterface((value)); return true;
        case 5: pp->setDestinationSubInterface((value)); return true;
        case 6: pp->setStatus(string2long(value)); return true;
        default: return false;
    }
}

const char *QuantumSubInterfaceBindingDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *QuantumSubInterfaceBindingDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    QuantumSubInterfaceBinding *pp = (QuantumSubInterfaceBinding *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}


