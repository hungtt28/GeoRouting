//
// Generated file, do not edit! Created by nedtool 4.6 from src/node/communication/routing/gearRouting/GEARRoutingPacket.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "GEARRoutingPacket_m.h"

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
    cEnum *e = cEnum::find("GEARForwardingMode");
    if (!e) enums.getInstance()->add(e = new cEnum("GEARForwardingMode"));
    e->insert(GEAR_GREEDY_ROUTING, "GEAR_GREEDY_ROUTING");
);

Register_Class(GEARRoutingPacket);

GEARRoutingPacket::GEARRoutingPacket(const char *name, int kind) : ::GeoRoutingPacket(name,kind)
{
    this->routingMode_var = GEAR_GREEDY_ROUTING;
}

GEARRoutingPacket::GEARRoutingPacket(const GEARRoutingPacket& other) : ::GeoRoutingPacket(other)
{
    copy(other);
}

GEARRoutingPacket::~GEARRoutingPacket()
{
}

GEARRoutingPacket& GEARRoutingPacket::operator=(const GEARRoutingPacket& other)
{
    if (this==&other) return *this;
    ::GeoRoutingPacket::operator=(other);
    copy(other);
    return *this;
}

void GEARRoutingPacket::copy(const GEARRoutingPacket& other)
{
    this->routingMode_var = other.routingMode_var;
    this->destinationLocation_var = other.destinationLocation_var;
}

void GEARRoutingPacket::parsimPack(cCommBuffer *b)
{
    ::GeoRoutingPacket::parsimPack(b);
    doPacking(b,this->routingMode_var);
    doPacking(b,this->destinationLocation_var);
}

void GEARRoutingPacket::parsimUnpack(cCommBuffer *b)
{
    ::GeoRoutingPacket::parsimUnpack(b);
    doUnpacking(b,this->routingMode_var);
    doUnpacking(b,this->destinationLocation_var);
}

int GEARRoutingPacket::getRoutingMode() const
{
    return routingMode_var;
}

void GEARRoutingPacket::setRoutingMode(int routingMode)
{
    this->routingMode_var = routingMode;
}

NodeLocation_type& GEARRoutingPacket::getDestinationLocation()
{
    return destinationLocation_var;
}

void GEARRoutingPacket::setDestinationLocation(const NodeLocation_type& destinationLocation)
{
    this->destinationLocation_var = destinationLocation;
}

class GEARRoutingPacketDescriptor : public cClassDescriptor
{
  public:
    GEARRoutingPacketDescriptor();
    virtual ~GEARRoutingPacketDescriptor();

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

Register_ClassDescriptor(GEARRoutingPacketDescriptor);

GEARRoutingPacketDescriptor::GEARRoutingPacketDescriptor() : cClassDescriptor("GEARRoutingPacket", "GeoRoutingPacket")
{
}

GEARRoutingPacketDescriptor::~GEARRoutingPacketDescriptor()
{
}

bool GEARRoutingPacketDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<GEARRoutingPacket *>(obj)!=NULL;
}

const char *GEARRoutingPacketDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int GEARRoutingPacketDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount(object) : 2;
}

unsigned int GEARRoutingPacketDescriptor::getFieldTypeFlags(void *object, int field) const
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
    };
    return (field>=0 && field<2) ? fieldTypeFlags[field] : 0;
}

const char *GEARRoutingPacketDescriptor::getFieldName(void *object, int field) const
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
    };
    return (field>=0 && field<2) ? fieldNames[field] : NULL;
}

int GEARRoutingPacketDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='r' && strcmp(fieldName, "routingMode")==0) return base+0;
    if (fieldName[0]=='d' && strcmp(fieldName, "destinationLocation")==0) return base+1;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *GEARRoutingPacketDescriptor::getFieldTypeString(void *object, int field) const
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
    };
    return (field>=0 && field<2) ? fieldTypeStrings[field] : NULL;
}

const char *GEARRoutingPacketDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int GEARRoutingPacketDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    GEARRoutingPacket *pp = (GEARRoutingPacket *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string GEARRoutingPacketDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    GEARRoutingPacket *pp = (GEARRoutingPacket *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getRoutingMode());
        case 1: {std::stringstream out; out << pp->getDestinationLocation(); return out.str();}
        default: return "";
    }
}

bool GEARRoutingPacketDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    GEARRoutingPacket *pp = (GEARRoutingPacket *)object; (void)pp;
    switch (field) {
        case 0: pp->setRoutingMode(string2long(value)); return true;
        default: return false;
    }
}

const char *GEARRoutingPacketDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 1: return opp_typename(typeid(NodeLocation_type));
        default: return NULL;
    };
}

void *GEARRoutingPacketDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    GEARRoutingPacket *pp = (GEARRoutingPacket *)object; (void)pp;
    switch (field) {
        case 1: return (void *)(&pp->getDestinationLocation()); break;
        default: return NULL;
    }
}


