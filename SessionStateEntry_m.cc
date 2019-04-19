//
// Generated file, do not edit! Created by nedtool 5.4 from SessionStateEntry.msg.
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
#include "SessionStateEntry_m.h"

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

Register_Class(SessionStateEntry)

SessionStateEntry::SessionStateEntry(const char *name, short kind) : ::omnetpp::cPacket(name,kind)
{
    this->sessionId = 0;
}

SessionStateEntry::SessionStateEntry(const SessionStateEntry& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

SessionStateEntry::~SessionStateEntry()
{
}

SessionStateEntry& SessionStateEntry::operator=(const SessionStateEntry& other)
{
    if (this==&other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void SessionStateEntry::copy(const SessionStateEntry& other)
{
    this->sessionId = other.sessionId;
    this->srcQMac = other.srcQMac;
    this->desQMac = other.desQMac;
    this->SubInterface = other.SubInterface;
    this->expiry = other.expiry;
    this->status = other.status;
}

void SessionStateEntry::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->sessionId);
    doParsimPacking(b,this->srcQMac);
    doParsimPacking(b,this->desQMac);
    doParsimPacking(b,this->SubInterface);
    doParsimPacking(b,this->expiry);
    doParsimPacking(b,this->status);
}

void SessionStateEntry::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->sessionId);
    doParsimUnpacking(b,this->srcQMac);
    doParsimUnpacking(b,this->desQMac);
    doParsimUnpacking(b,this->SubInterface);
    doParsimUnpacking(b,this->expiry);
    doParsimUnpacking(b,this->status);
}

int SessionStateEntry::getSessionId() const
{
    return this->sessionId;
}

void SessionStateEntry::setSessionId(int sessionId)
{
    this->sessionId = sessionId;
}

const char * SessionStateEntry::getSrcQMac() const
{
    return this->srcQMac.c_str();
}

void SessionStateEntry::setSrcQMac(const char * srcQMac)
{
    this->srcQMac = srcQMac;
}

const char * SessionStateEntry::getDesQMac() const
{
    return this->desQMac.c_str();
}

void SessionStateEntry::setDesQMac(const char * desQMac)
{
    this->desQMac = desQMac;
}

const char * SessionStateEntry::getSubInterface() const
{
    return this->SubInterface.c_str();
}

void SessionStateEntry::setSubInterface(const char * SubInterface)
{
    this->SubInterface = SubInterface;
}

const char * SessionStateEntry::getExpiry() const
{
    return this->expiry.c_str();
}

void SessionStateEntry::setExpiry(const char * expiry)
{
    this->expiry = expiry;
}

const char * SessionStateEntry::getStatus() const
{
    return this->status.c_str();
}

void SessionStateEntry::setStatus(const char * status)
{
    this->status = status;
}

class SessionStateEntryDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    SessionStateEntryDescriptor();
    virtual ~SessionStateEntryDescriptor();

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

Register_ClassDescriptor(SessionStateEntryDescriptor)

SessionStateEntryDescriptor::SessionStateEntryDescriptor() : omnetpp::cClassDescriptor("SessionStateEntry", "omnetpp::cPacket")
{
    propertynames = nullptr;
}

SessionStateEntryDescriptor::~SessionStateEntryDescriptor()
{
    delete[] propertynames;
}

bool SessionStateEntryDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<SessionStateEntry *>(obj)!=nullptr;
}

const char **SessionStateEntryDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *SessionStateEntryDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int SessionStateEntryDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 6+basedesc->getFieldCount() : 6;
}

unsigned int SessionStateEntryDescriptor::getFieldTypeFlags(int field) const
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
    };
    return (field>=0 && field<6) ? fieldTypeFlags[field] : 0;
}

const char *SessionStateEntryDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "sessionId",
        "srcQMac",
        "desQMac",
        "SubInterface",
        "expiry",
        "status",
    };
    return (field>=0 && field<6) ? fieldNames[field] : nullptr;
}

int SessionStateEntryDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='s' && strcmp(fieldName, "sessionId")==0) return base+0;
    if (fieldName[0]=='s' && strcmp(fieldName, "srcQMac")==0) return base+1;
    if (fieldName[0]=='d' && strcmp(fieldName, "desQMac")==0) return base+2;
    if (fieldName[0]=='S' && strcmp(fieldName, "SubInterface")==0) return base+3;
    if (fieldName[0]=='e' && strcmp(fieldName, "expiry")==0) return base+4;
    if (fieldName[0]=='s' && strcmp(fieldName, "status")==0) return base+5;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *SessionStateEntryDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "string",
        "string",
        "string",
        "string",
        "string",
    };
    return (field>=0 && field<6) ? fieldTypeStrings[field] : nullptr;
}

const char **SessionStateEntryDescriptor::getFieldPropertyNames(int field) const
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

const char *SessionStateEntryDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int SessionStateEntryDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    SessionStateEntry *pp = (SessionStateEntry *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *SessionStateEntryDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    SessionStateEntry *pp = (SessionStateEntry *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string SessionStateEntryDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    SessionStateEntry *pp = (SessionStateEntry *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getSessionId());
        case 1: return oppstring2string(pp->getSrcQMac());
        case 2: return oppstring2string(pp->getDesQMac());
        case 3: return oppstring2string(pp->getSubInterface());
        case 4: return oppstring2string(pp->getExpiry());
        case 5: return oppstring2string(pp->getStatus());
        default: return "";
    }
}

bool SessionStateEntryDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    SessionStateEntry *pp = (SessionStateEntry *)object; (void)pp;
    switch (field) {
        case 0: pp->setSessionId(string2long(value)); return true;
        case 1: pp->setSrcQMac((value)); return true;
        case 2: pp->setDesQMac((value)); return true;
        case 3: pp->setSubInterface((value)); return true;
        case 4: pp->setExpiry((value)); return true;
        case 5: pp->setStatus((value)); return true;
        default: return false;
    }
}

const char *SessionStateEntryDescriptor::getFieldStructName(int field) const
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

void *SessionStateEntryDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    SessionStateEntry *pp = (SessionStateEntry *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}


