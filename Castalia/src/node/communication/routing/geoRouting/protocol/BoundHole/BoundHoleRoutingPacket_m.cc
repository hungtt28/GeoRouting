//
// Generated file, do not edit! Created by nedtool 4.6 from src/node/communication/routing/geoRouting/protocol/BoundHole/BoundHoleRoutingPacket.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "BoundHoleRoutingPacket_m.h"

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
    cEnum *e = cEnum::find("BoundHoleForwardingMode");
    if (!e) enums.getInstance()->add(e = new cEnum("BoundHoleForwardingMode"));
    e->insert(BOUNDHOLE_GREEDY_ROUTING, "BOUNDHOLE_GREEDY_ROUTING");
    e->insert(BOUNDHOLE_BOUNDHOLE_ROUTING, "BOUNDHOLE_BOUNDHOLE_ROUTING");
);

Register_Class(BoundHoleRoutingPacket);

BoundHoleRoutingPacket::BoundHoleRoutingPacket(const char *name, int kind) : ::GeoRoutingPacket(name,kind)
{
    this->routingMode_var = BOUNDHOLE_GREEDY_ROUTING;
    this->startIngressId_var = -1;
    this->startBoundHoleId_var = -1;
    this->holeId_var = -1;
}

BoundHoleRoutingPacket::BoundHoleRoutingPacket(const BoundHoleRoutingPacket& other) : ::GeoRoutingPacket(other)
{
    copy(other);
}

BoundHoleRoutingPacket::~BoundHoleRoutingPacket()
{
}

BoundHoleRoutingPacket& BoundHoleRoutingPacket::operator=(const BoundHoleRoutingPacket& other)
{
    if (this==&other) return *this;
    ::GeoRoutingPacket::operator=(other);
    copy(other);
    return *this;
}

void BoundHoleRoutingPacket::copy(const BoundHoleRoutingPacket& other)
{
    this->routingMode_var = other.routingMode_var;
    this->destinationLocation_var = other.destinationLocation_var;
    this->startBoundHoleLocation_var = other.startBoundHoleLocation_var;
    this->startIngressId_var = other.startIngressId_var;
    this->startBoundHoleId_var = other.startBoundHoleId_var;
    this->holeId_var = other.holeId_var;
}

void BoundHoleRoutingPacket::parsimPack(cCommBuffer *b)
{
    ::GeoRoutingPacket::parsimPack(b);
    doPacking(b,this->routingMode_var);
    doPacking(b,this->destinationLocation_var);
    doPacking(b,this->startBoundHoleLocation_var);
    doPacking(b,this->startIngressId_var);
    doPacking(b,this->startBoundHoleId_var);
    doPacking(b,this->holeId_var);
}

void BoundHoleRoutingPacket::parsimUnpack(cCommBuffer *b)
{
    ::GeoRoutingPacket::parsimUnpack(b);
    doUnpacking(b,this->routingMode_var);
    doUnpacking(b,this->destinationLocation_var);
    doUnpacking(b,this->startBoundHoleLocation_var);
    doUnpacking(b,this->startIngressId_var);
    doUnpacking(b,this->startBoundHoleId_var);
    doUnpacking(b,this->holeId_var);
}

int BoundHoleRoutingPacket::getRoutingMode() const
{
    return routingMode_var;
}

void BoundHoleRoutingPacket::setRoutingMode(int routingMode)
{
    this->routingMode_var = routingMode;
}

NodeLocation_type& BoundHoleRoutingPacket::getDestinationLocation()
{
    return destinationLocation_var;
}

void BoundHoleRoutingPacket::setDestinationLocation(const NodeLocation_type& destinationLocation)
{
    this->destinationLocation_var = destinationLocation;
}

NodeLocation_type& BoundHoleRoutingPacket::getStartBoundHoleLocation()
{
    return startBoundHoleLocation_var;
}

void BoundHoleRoutingPacket::setStartBoundHoleLocation(const NodeLocation_type& startBoundHoleLocation)
{
    this->startBoundHoleLocation_var = startBoundHoleLocation;
}

int BoundHoleRoutingPacket::getStartIngressId() const
{
    return startIngressId_var;
}

void BoundHoleRoutingPacket::setStartIngressId(int startIngressId)
{
    this->startIngressId_var = startIngressId;
}

int BoundHoleRoutingPacket::getStartBoundHoleId() const
{
    return startBoundHoleId_var;
}

void BoundHoleRoutingPacket::setStartBoundHoleId(int startBoundHoleId)
{
    this->startBoundHoleId_var = startBoundHoleId;
}

int BoundHoleRoutingPacket::getHoleId() const
{
    return holeId_var;
}

void BoundHoleRoutingPacket::setHoleId(int holeId)
{
    this->holeId_var = holeId;
}

class BoundHoleRoutingPacketDescriptor : public cClassDescriptor
{
  public:
    BoundHoleRoutingPacketDescriptor();
    virtual ~BoundHoleRoutingPacketDescriptor();

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

Register_ClassDescriptor(BoundHoleRoutingPacketDescriptor);

BoundHoleRoutingPacketDescriptor::BoundHoleRoutingPacketDescriptor() : cClassDescriptor("BoundHoleRoutingPacket", "GeoRoutingPacket")
{
}

BoundHoleRoutingPacketDescriptor::~BoundHoleRoutingPacketDescriptor()
{
}

bool BoundHoleRoutingPacketDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<BoundHoleRoutingPacket *>(obj)!=NULL;
}

const char *BoundHoleRoutingPacketDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int BoundHoleRoutingPacketDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 6+basedesc->getFieldCount(object) : 6;
}

unsigned int BoundHoleRoutingPacketDescriptor::getFieldTypeFlags(void *object, int field) const
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
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<6) ? fieldTypeFlags[field] : 0;
}

const char *BoundHoleRoutingPacketDescriptor::getFieldName(void *object, int field) const
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
        "startBoundHoleLocation",
        "startIngressId",
        "startBoundHoleId",
        "holeId",
    };
    return (field>=0 && field<6) ? fieldNames[field] : NULL;
}

int BoundHoleRoutingPacketDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='r' && strcmp(fieldName, "routingMode")==0) return base+0;
    if (fieldName[0]=='d' && strcmp(fieldName, "destinationLocation")==0) return base+1;
    if (fieldName[0]=='s' && strcmp(fieldName, "startBoundHoleLocation")==0) return base+2;
    if (fieldName[0]=='s' && strcmp(fieldName, "startIngressId")==0) return base+3;
    if (fieldName[0]=='s' && strcmp(fieldName, "startBoundHoleId")==0) return base+4;
    if (fieldName[0]=='h' && strcmp(fieldName, "holeId")==0) return base+5;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *BoundHoleRoutingPacketDescriptor::getFieldTypeString(void *object, int field) const
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
        "int",
        "int",
        "int",
    };
    return (field>=0 && field<6) ? fieldTypeStrings[field] : NULL;
}

const char *BoundHoleRoutingPacketDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int BoundHoleRoutingPacketDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    BoundHoleRoutingPacket *pp = (BoundHoleRoutingPacket *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string BoundHoleRoutingPacketDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    BoundHoleRoutingPacket *pp = (BoundHoleRoutingPacket *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getRoutingMode());
        case 1: {std::stringstream out; out << pp->getDestinationLocation(); return out.str();}
        case 2: {std::stringstream out; out << pp->getStartBoundHoleLocation(); return out.str();}
        case 3: return long2string(pp->getStartIngressId());
        case 4: return long2string(pp->getStartBoundHoleId());
        case 5: return long2string(pp->getHoleId());
        default: return "";
    }
}

bool BoundHoleRoutingPacketDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    BoundHoleRoutingPacket *pp = (BoundHoleRoutingPacket *)object; (void)pp;
    switch (field) {
        case 0: pp->setRoutingMode(string2long(value)); return true;
        case 3: pp->setStartIngressId(string2long(value)); return true;
        case 4: pp->setStartBoundHoleId(string2long(value)); return true;
        case 5: pp->setHoleId(string2long(value)); return true;
        default: return false;
    }
}

const char *BoundHoleRoutingPacketDescriptor::getFieldStructName(void *object, int field) const
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
        default: return NULL;
    };
}

void *BoundHoleRoutingPacketDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    BoundHoleRoutingPacket *pp = (BoundHoleRoutingPacket *)object; (void)pp;
    switch (field) {
        case 1: return (void *)(&pp->getDestinationLocation()); break;
        case 2: return (void *)(&pp->getStartBoundHoleLocation()); break;
        default: return NULL;
    }
}


