//
// Generated file, do not edit! Created by nedtool 4.6 from src/node/communication/routing/garRouting/GARRoutingPacket.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "GARRoutingPacket_m.h"

USING_NAMESPACE


// Another default rule (prevents compiler from choosing base class' doPacking())
template<typename T>
void doPacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doPacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}

template<typename T>
void doUnpacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doUnpacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}




// Template rule for outputting std::vector<T> types
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

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
inline std::ostream& operator<<(std::ostream& out,const T&) {return out;}

EXECUTE_ON_STARTUP(
    cEnum *e = cEnum::find("GARForwardingMode");
    if (!e) enums.getInstance()->add(e = new cEnum("GARForwardingMode"));
    e->insert(GAR_GREEDY_ROUTING, "GAR_GREEDY_ROUTING");
    e->insert(GAR_GAR_ROUTING, "GAR_GAR_ROUTING");
);

Register_Class(GARRoutingPacket);

GARRoutingPacket::GARRoutingPacket(const char *name, int kind) : ::GeoRoutingPacket(name,kind)
{
    this->routingMode_var = GAR_GREEDY_ROUTING;
    this->firstSenderAddress_var = 0;
    this->firstReceiverAddress_var = 0;
    this->senderAddress_var = 0;
}

GARRoutingPacket::GARRoutingPacket(const GARRoutingPacket& other) : ::GeoRoutingPacket(other)
{
    copy(other);
}

GARRoutingPacket::~GARRoutingPacket()
{
}

GARRoutingPacket& GARRoutingPacket::operator=(const GARRoutingPacket& other)
{
    if (this==&other) return *this;
    ::GeoRoutingPacket::operator=(other);
    copy(other);
    return *this;
}

void GARRoutingPacket::copy(const GARRoutingPacket& other)
{
    this->routingMode_var = other.routingMode_var;
    this->destinationLocation_var = other.destinationLocation_var;
    this->startPerimeterLocation_var = other.startPerimeterLocation_var;
    this->forwardPerimeterLocation_var = other.forwardPerimeterLocation_var;
    this->firstSenderAddress_var = other.firstSenderAddress_var;
    this->firstReceiverAddress_var = other.firstReceiverAddress_var;
    this->senderAddress_var = other.senderAddress_var;
}

void GARRoutingPacket::parsimPack(cCommBuffer *b)
{
    ::GeoRoutingPacket::parsimPack(b);
    doPacking(b,this->routingMode_var);
    doPacking(b,this->destinationLocation_var);
    doPacking(b,this->startPerimeterLocation_var);
    doPacking(b,this->forwardPerimeterLocation_var);
    doPacking(b,this->firstSenderAddress_var);
    doPacking(b,this->firstReceiverAddress_var);
    doPacking(b,this->senderAddress_var);
}

void GARRoutingPacket::parsimUnpack(cCommBuffer *b)
{
    ::GeoRoutingPacket::parsimUnpack(b);
    doUnpacking(b,this->routingMode_var);
    doUnpacking(b,this->destinationLocation_var);
    doUnpacking(b,this->startPerimeterLocation_var);
    doUnpacking(b,this->forwardPerimeterLocation_var);
    doUnpacking(b,this->firstSenderAddress_var);
    doUnpacking(b,this->firstReceiverAddress_var);
    doUnpacking(b,this->senderAddress_var);
}

int GARRoutingPacket::getRoutingMode() const
{
    return routingMode_var;
}

void GARRoutingPacket::setRoutingMode(int routingMode)
{
    this->routingMode_var = routingMode;
}

NodeLocation_type& GARRoutingPacket::getDestinationLocation()
{
    return destinationLocation_var;
}

void GARRoutingPacket::setDestinationLocation(const NodeLocation_type& destinationLocation)
{
    this->destinationLocation_var = destinationLocation;
}

NodeLocation_type& GARRoutingPacket::getStartPerimeterLocation()
{
    return startPerimeterLocation_var;
}

void GARRoutingPacket::setStartPerimeterLocation(const NodeLocation_type& startPerimeterLocation)
{
    this->startPerimeterLocation_var = startPerimeterLocation;
}

NodeLocation_type& GARRoutingPacket::getForwardPerimeterLocation()
{
    return forwardPerimeterLocation_var;
}

void GARRoutingPacket::setForwardPerimeterLocation(const NodeLocation_type& forwardPerimeterLocation)
{
    this->forwardPerimeterLocation_var = forwardPerimeterLocation;
}

const char * GARRoutingPacket::getFirstSenderAddress() const
{
    return firstSenderAddress_var.c_str();
}

void GARRoutingPacket::setFirstSenderAddress(const char * firstSenderAddress)
{
    this->firstSenderAddress_var = firstSenderAddress;
}

const char * GARRoutingPacket::getFirstReceiverAddress() const
{
    return firstReceiverAddress_var.c_str();
}

void GARRoutingPacket::setFirstReceiverAddress(const char * firstReceiverAddress)
{
    this->firstReceiverAddress_var = firstReceiverAddress;
}

const char * GARRoutingPacket::getSenderAddress() const
{
    return senderAddress_var.c_str();
}

void GARRoutingPacket::setSenderAddress(const char * senderAddress)
{
    this->senderAddress_var = senderAddress;
}

class GARRoutingPacketDescriptor : public cClassDescriptor
{
  public:
    GARRoutingPacketDescriptor();
    virtual ~GARRoutingPacketDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(GARRoutingPacketDescriptor);

GARRoutingPacketDescriptor::GARRoutingPacketDescriptor() : cClassDescriptor("GARRoutingPacket", "GeoRoutingPacket")
{
}

GARRoutingPacketDescriptor::~GARRoutingPacketDescriptor()
{
}

bool GARRoutingPacketDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<GARRoutingPacket *>(obj)!=NULL;
}

const char *GARRoutingPacketDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int GARRoutingPacketDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 7+basedesc->getFieldCount(object) : 7;
}

unsigned int GARRoutingPacketDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISCOMPOUND,
        FD_ISCOMPOUND,
        FD_ISCOMPOUND,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<7) ? fieldTypeFlags[field] : 0;
}

const char *GARRoutingPacketDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "routingMode",
        "destinationLocation",
        "startPerimeterLocation",
        "forwardPerimeterLocation",
        "firstSenderAddress",
        "firstReceiverAddress",
        "senderAddress",
    };
    return (field>=0 && field<7) ? fieldNames[field] : NULL;
}

int GARRoutingPacketDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='r' && strcmp(fieldName, "routingMode")==0) return base+0;
    if (fieldName[0]=='d' && strcmp(fieldName, "destinationLocation")==0) return base+1;
    if (fieldName[0]=='s' && strcmp(fieldName, "startPerimeterLocation")==0) return base+2;
    if (fieldName[0]=='f' && strcmp(fieldName, "forwardPerimeterLocation")==0) return base+3;
    if (fieldName[0]=='f' && strcmp(fieldName, "firstSenderAddress")==0) return base+4;
    if (fieldName[0]=='f' && strcmp(fieldName, "firstReceiverAddress")==0) return base+5;
    if (fieldName[0]=='s' && strcmp(fieldName, "senderAddress")==0) return base+6;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *GARRoutingPacketDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "NodeLocation_type",
        "NodeLocation_type",
        "NodeLocation_type",
        "string",
        "string",
        "string",
    };
    return (field>=0 && field<7) ? fieldTypeStrings[field] : NULL;
}

const char *GARRoutingPacketDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int GARRoutingPacketDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    GARRoutingPacket *pp = (GARRoutingPacket *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string GARRoutingPacketDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    GARRoutingPacket *pp = (GARRoutingPacket *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getRoutingMode());
        case 1: {std::stringstream out; out << pp->getDestinationLocation(); return out.str();}
        case 2: {std::stringstream out; out << pp->getStartPerimeterLocation(); return out.str();}
        case 3: {std::stringstream out; out << pp->getForwardPerimeterLocation(); return out.str();}
        case 4: return oppstring2string(pp->getFirstSenderAddress());
        case 5: return oppstring2string(pp->getFirstReceiverAddress());
        case 6: return oppstring2string(pp->getSenderAddress());
        default: return "";
    }
}

bool GARRoutingPacketDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    GARRoutingPacket *pp = (GARRoutingPacket *)object; (void)pp;
    switch (field) {
        case 0: pp->setRoutingMode(string2long(value)); return true;
        case 4: pp->setFirstSenderAddress((value)); return true;
        case 5: pp->setFirstReceiverAddress((value)); return true;
        case 6: pp->setSenderAddress((value)); return true;
        default: return false;
    }
}

const char *GARRoutingPacketDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 1: return opp_typename(typeid(NodeLocation_type));
        case 2: return opp_typename(typeid(NodeLocation_type));
        case 3: return opp_typename(typeid(NodeLocation_type));
        default: return NULL;
    };
}

void *GARRoutingPacketDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    GARRoutingPacket *pp = (GARRoutingPacket *)object; (void)pp;
    switch (field) {
        case 1: return (void *)(&pp->getDestinationLocation()); break;
        case 2: return (void *)(&pp->getStartPerimeterLocation()); break;
        case 3: return (void *)(&pp->getForwardPerimeterLocation()); break;
        default: return NULL;
    }
}


