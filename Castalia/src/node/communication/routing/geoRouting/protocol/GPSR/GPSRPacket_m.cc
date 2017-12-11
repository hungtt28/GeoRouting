//
// Generated file, do not edit! Created by nedtool 4.6 from src/node/communication/routing/geoRouting/protocol/GPSR/GPSRPacket.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "GPSRPacket_m.h"

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
    cEnum *e = cEnum::find("GPSRForwardingMode");
    if (!e) enums.getInstance()->add(e = new cEnum("GPSRForwardingMode"));
    e->insert(GPSR_GREEDY_ROUTING, "GPSR_GREEDY_ROUTING");
    e->insert(GPSR_PERIMETER_ROUTING, "GPSR_PERIMETER_ROUTING");
);

Register_Class(GPSRPacket);

GPSRPacket::GPSRPacket(const char *name, int kind) : ::GeoRoutingPacket(name,kind)
{
    this->routingMode_var = GPSR_GREEDY_ROUTING;
    this->firstSenderAddress_var = 0;
    this->firstReceiverAddress_var = 0;
    this->senderAddress_var = 0;
}

GPSRPacket::GPSRPacket(const GPSRPacket& other) : ::GeoRoutingPacket(other)
{
    copy(other);
}

GPSRPacket::~GPSRPacket()
{
}

GPSRPacket& GPSRPacket::operator=(const GPSRPacket& other)
{
    if (this==&other) return *this;
    ::GeoRoutingPacket::operator=(other);
    copy(other);
    return *this;
}

void GPSRPacket::copy(const GPSRPacket& other)
{
    this->routingMode_var = other.routingMode_var;
    this->destinationLocation_var = other.destinationLocation_var;
    this->startPerimeterLocation_var = other.startPerimeterLocation_var;
    this->forwardPerimeterLocation_var = other.forwardPerimeterLocation_var;
    this->firstSenderAddress_var = other.firstSenderAddress_var;
    this->firstReceiverAddress_var = other.firstReceiverAddress_var;
    this->senderAddress_var = other.senderAddress_var;
}

void GPSRPacket::parsimPack(cCommBuffer *b)
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

void GPSRPacket::parsimUnpack(cCommBuffer *b)
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

int GPSRPacket::getRoutingMode() const
{
    return routingMode_var;
}

void GPSRPacket::setRoutingMode(int routingMode)
{
    this->routingMode_var = routingMode;
}

NodeLocation_type& GPSRPacket::getDestinationLocation()
{
    return destinationLocation_var;
}

void GPSRPacket::setDestinationLocation(const NodeLocation_type& destinationLocation)
{
    this->destinationLocation_var = destinationLocation;
}

NodeLocation_type& GPSRPacket::getStartPerimeterLocation()
{
    return startPerimeterLocation_var;
}

void GPSRPacket::setStartPerimeterLocation(const NodeLocation_type& startPerimeterLocation)
{
    this->startPerimeterLocation_var = startPerimeterLocation;
}

NodeLocation_type& GPSRPacket::getForwardPerimeterLocation()
{
    return forwardPerimeterLocation_var;
}

void GPSRPacket::setForwardPerimeterLocation(const NodeLocation_type& forwardPerimeterLocation)
{
    this->forwardPerimeterLocation_var = forwardPerimeterLocation;
}

const char * GPSRPacket::getFirstSenderAddress() const
{
    return firstSenderAddress_var.c_str();
}

void GPSRPacket::setFirstSenderAddress(const char * firstSenderAddress)
{
    this->firstSenderAddress_var = firstSenderAddress;
}

const char * GPSRPacket::getFirstReceiverAddress() const
{
    return firstReceiverAddress_var.c_str();
}

void GPSRPacket::setFirstReceiverAddress(const char * firstReceiverAddress)
{
    this->firstReceiverAddress_var = firstReceiverAddress;
}

const char * GPSRPacket::getSenderAddress() const
{
    return senderAddress_var.c_str();
}

void GPSRPacket::setSenderAddress(const char * senderAddress)
{
    this->senderAddress_var = senderAddress;
}

class GPSRPacketDescriptor : public cClassDescriptor
{
  public:
    GPSRPacketDescriptor();
    virtual ~GPSRPacketDescriptor();

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

Register_ClassDescriptor(GPSRPacketDescriptor);

GPSRPacketDescriptor::GPSRPacketDescriptor() : cClassDescriptor("GPSRPacket", "GeoRoutingPacket")
{
}

GPSRPacketDescriptor::~GPSRPacketDescriptor()
{
}

bool GPSRPacketDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<GPSRPacket *>(obj)!=NULL;
}

const char *GPSRPacketDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int GPSRPacketDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 7+basedesc->getFieldCount(object) : 7;
}

unsigned int GPSRPacketDescriptor::getFieldTypeFlags(void *object, int field) const
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

const char *GPSRPacketDescriptor::getFieldName(void *object, int field) const
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

int GPSRPacketDescriptor::findField(void *object, const char *fieldName) const
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

const char *GPSRPacketDescriptor::getFieldTypeString(void *object, int field) const
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

const char *GPSRPacketDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int GPSRPacketDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    GPSRPacket *pp = (GPSRPacket *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string GPSRPacketDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    GPSRPacket *pp = (GPSRPacket *)object; (void)pp;
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

bool GPSRPacketDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    GPSRPacket *pp = (GPSRPacket *)object; (void)pp;
    switch (field) {
        case 0: pp->setRoutingMode(string2long(value)); return true;
        case 4: pp->setFirstSenderAddress((value)); return true;
        case 5: pp->setFirstReceiverAddress((value)); return true;
        case 6: pp->setSenderAddress((value)); return true;
        default: return false;
    }
}

const char *GPSRPacketDescriptor::getFieldStructName(void *object, int field) const
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

void *GPSRPacketDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    GPSRPacket *pp = (GPSRPacket *)object; (void)pp;
    switch (field) {
        case 1: return (void *)(&pp->getDestinationLocation()); break;
        case 2: return (void *)(&pp->getStartPerimeterLocation()); break;
        case 3: return (void *)(&pp->getForwardPerimeterLocation()); break;
        default: return NULL;
    }
}


