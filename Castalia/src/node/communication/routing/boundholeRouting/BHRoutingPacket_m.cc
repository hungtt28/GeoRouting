//
// Generated file, do not edit! Created by nedtool 4.6 from src/node/communication/routing/boundholeRouting/BHRoutingPacket.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "BHRoutingPacket_m.h"

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

Register_Class(BHRoutingPacket);

BHRoutingPacket::BHRoutingPacket(const char *name, int kind) : ::GeoRoutingPacket(name,kind)
{
    this->routingMode_var = BOUNDHOLE_GREEDY_ROUTING;
    this->holeId_var = -1;
    this->originalId_var = -1;
    this->startIndex_var = -1;
    this->curIndex_var = -1;
    this->direction_var = true;
}

BHRoutingPacket::BHRoutingPacket(const BHRoutingPacket& other) : ::GeoRoutingPacket(other)
{
    copy(other);
}

BHRoutingPacket::~BHRoutingPacket()
{
}

BHRoutingPacket& BHRoutingPacket::operator=(const BHRoutingPacket& other)
{
    if (this==&other) return *this;
    ::GeoRoutingPacket::operator=(other);
    copy(other);
    return *this;
}

void BHRoutingPacket::copy(const BHRoutingPacket& other)
{
    this->routingMode_var = other.routingMode_var;
    this->destinationLocation_var = other.destinationLocation_var;
    this->startBoundHoleLocation_var = other.startBoundHoleLocation_var;
    this->holeId_var = other.holeId_var;
    this->originalId_var = other.originalId_var;
    this->startIndex_var = other.startIndex_var;
    this->curIndex_var = other.curIndex_var;
    this->direction_var = other.direction_var;
}

void BHRoutingPacket::parsimPack(cCommBuffer *b)
{
    ::GeoRoutingPacket::parsimPack(b);
    doPacking(b,this->routingMode_var);
    doPacking(b,this->destinationLocation_var);
    doPacking(b,this->startBoundHoleLocation_var);
    doPacking(b,this->holeId_var);
    doPacking(b,this->originalId_var);
    doPacking(b,this->startIndex_var);
    doPacking(b,this->curIndex_var);
    doPacking(b,this->direction_var);
}

void BHRoutingPacket::parsimUnpack(cCommBuffer *b)
{
    ::GeoRoutingPacket::parsimUnpack(b);
    doUnpacking(b,this->routingMode_var);
    doUnpacking(b,this->destinationLocation_var);
    doUnpacking(b,this->startBoundHoleLocation_var);
    doUnpacking(b,this->holeId_var);
    doUnpacking(b,this->originalId_var);
    doUnpacking(b,this->startIndex_var);
    doUnpacking(b,this->curIndex_var);
    doUnpacking(b,this->direction_var);
}

int BHRoutingPacket::getRoutingMode() const
{
    return routingMode_var;
}

void BHRoutingPacket::setRoutingMode(int routingMode)
{
    this->routingMode_var = routingMode;
}

NodeLocation_type& BHRoutingPacket::getDestinationLocation()
{
    return destinationLocation_var;
}

void BHRoutingPacket::setDestinationLocation(const NodeLocation_type& destinationLocation)
{
    this->destinationLocation_var = destinationLocation;
}

NodeLocation_type& BHRoutingPacket::getStartBoundHoleLocation()
{
    return startBoundHoleLocation_var;
}

void BHRoutingPacket::setStartBoundHoleLocation(const NodeLocation_type& startBoundHoleLocation)
{
    this->startBoundHoleLocation_var = startBoundHoleLocation;
}

int BHRoutingPacket::getHoleId() const
{
    return holeId_var;
}

void BHRoutingPacket::setHoleId(int holeId)
{
    this->holeId_var = holeId;
}

int BHRoutingPacket::getOriginalId() const
{
    return originalId_var;
}

void BHRoutingPacket::setOriginalId(int originalId)
{
    this->originalId_var = originalId;
}

int BHRoutingPacket::getStartIndex() const
{
    return startIndex_var;
}

void BHRoutingPacket::setStartIndex(int startIndex)
{
    this->startIndex_var = startIndex;
}

int BHRoutingPacket::getCurIndex() const
{
    return curIndex_var;
}

void BHRoutingPacket::setCurIndex(int curIndex)
{
    this->curIndex_var = curIndex;
}

bool BHRoutingPacket::getDirection() const
{
    return direction_var;
}

void BHRoutingPacket::setDirection(bool direction)
{
    this->direction_var = direction;
}

class BHRoutingPacketDescriptor : public cClassDescriptor
{
  public:
    BHRoutingPacketDescriptor();
    virtual ~BHRoutingPacketDescriptor();

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

Register_ClassDescriptor(BHRoutingPacketDescriptor);

BHRoutingPacketDescriptor::BHRoutingPacketDescriptor() : cClassDescriptor("BHRoutingPacket", "GeoRoutingPacket")
{
}

BHRoutingPacketDescriptor::~BHRoutingPacketDescriptor()
{
}

bool BHRoutingPacketDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<BHRoutingPacket *>(obj)!=NULL;
}

const char *BHRoutingPacketDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int BHRoutingPacketDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 8+basedesc->getFieldCount(object) : 8;
}

unsigned int BHRoutingPacketDescriptor::getFieldTypeFlags(void *object, int field) const
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
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<8) ? fieldTypeFlags[field] : 0;
}

const char *BHRoutingPacketDescriptor::getFieldName(void *object, int field) const
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
        "holeId",
        "originalId",
        "startIndex",
        "curIndex",
        "direction",
    };
    return (field>=0 && field<8) ? fieldNames[field] : NULL;
}

int BHRoutingPacketDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='r' && strcmp(fieldName, "routingMode")==0) return base+0;
    if (fieldName[0]=='d' && strcmp(fieldName, "destinationLocation")==0) return base+1;
    if (fieldName[0]=='s' && strcmp(fieldName, "startBoundHoleLocation")==0) return base+2;
    if (fieldName[0]=='h' && strcmp(fieldName, "holeId")==0) return base+3;
    if (fieldName[0]=='o' && strcmp(fieldName, "originalId")==0) return base+4;
    if (fieldName[0]=='s' && strcmp(fieldName, "startIndex")==0) return base+5;
    if (fieldName[0]=='c' && strcmp(fieldName, "curIndex")==0) return base+6;
    if (fieldName[0]=='d' && strcmp(fieldName, "direction")==0) return base+7;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *BHRoutingPacketDescriptor::getFieldTypeString(void *object, int field) const
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
        "int",
        "bool",
    };
    return (field>=0 && field<8) ? fieldTypeStrings[field] : NULL;
}

const char *BHRoutingPacketDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int BHRoutingPacketDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    BHRoutingPacket *pp = (BHRoutingPacket *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string BHRoutingPacketDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    BHRoutingPacket *pp = (BHRoutingPacket *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getRoutingMode());
        case 1: {std::stringstream out; out << pp->getDestinationLocation(); return out.str();}
        case 2: {std::stringstream out; out << pp->getStartBoundHoleLocation(); return out.str();}
        case 3: return long2string(pp->getHoleId());
        case 4: return long2string(pp->getOriginalId());
        case 5: return long2string(pp->getStartIndex());
        case 6: return long2string(pp->getCurIndex());
        case 7: return bool2string(pp->getDirection());
        default: return "";
    }
}

bool BHRoutingPacketDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    BHRoutingPacket *pp = (BHRoutingPacket *)object; (void)pp;
    switch (field) {
        case 0: pp->setRoutingMode(string2long(value)); return true;
        case 3: pp->setHoleId(string2long(value)); return true;
        case 4: pp->setOriginalId(string2long(value)); return true;
        case 5: pp->setStartIndex(string2long(value)); return true;
        case 6: pp->setCurIndex(string2long(value)); return true;
        case 7: pp->setDirection(string2bool(value)); return true;
        default: return false;
    }
}

const char *BHRoutingPacketDescriptor::getFieldStructName(void *object, int field) const
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

void *BHRoutingPacketDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    BHRoutingPacket *pp = (BHRoutingPacket *)object; (void)pp;
    switch (field) {
        case 1: return (void *)(&pp->getDestinationLocation()); break;
        case 2: return (void *)(&pp->getStartBoundHoleLocation()); break;
        default: return NULL;
    }
}


