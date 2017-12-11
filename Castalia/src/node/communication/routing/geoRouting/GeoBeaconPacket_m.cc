//
// Generated file, do not edit! Created by nedtool 4.6 from src/node/communication/routing/geoRouting/GeoBeaconPacket.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "GeoBeaconPacket_m.h"

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

Register_Class(GeoBeaconPacket);

GeoBeaconPacket::GeoBeaconPacket(const char *name, int kind) : ::GeoPacket(name,kind)
{
    this->geoPacketType_var = GEO_BEACON_PACKET;
}

GeoBeaconPacket::GeoBeaconPacket(const GeoBeaconPacket& other) : ::GeoPacket(other)
{
    copy(other);
}

GeoBeaconPacket::~GeoBeaconPacket()
{
}

GeoBeaconPacket& GeoBeaconPacket::operator=(const GeoBeaconPacket& other)
{
    if (this==&other) return *this;
    ::GeoPacket::operator=(other);
    copy(other);
    return *this;
}

void GeoBeaconPacket::copy(const GeoBeaconPacket& other)
{
    this->geoPacketType_var = other.geoPacketType_var;
    this->nodeLocation_var = other.nodeLocation_var;
}

void GeoBeaconPacket::parsimPack(cCommBuffer *b)
{
    ::GeoPacket::parsimPack(b);
    doPacking(b,this->geoPacketType_var);
    doPacking(b,this->nodeLocation_var);
}

void GeoBeaconPacket::parsimUnpack(cCommBuffer *b)
{
    ::GeoPacket::parsimUnpack(b);
    doUnpacking(b,this->geoPacketType_var);
    doUnpacking(b,this->nodeLocation_var);
}

int GeoBeaconPacket::getGeoPacketType() const
{
    return geoPacketType_var;
}

void GeoBeaconPacket::setGeoPacketType(int geoPacketType)
{
    this->geoPacketType_var = geoPacketType;
}

NodeLocation_type& GeoBeaconPacket::getNodeLocation()
{
    return nodeLocation_var;
}

void GeoBeaconPacket::setNodeLocation(const NodeLocation_type& nodeLocation)
{
    this->nodeLocation_var = nodeLocation;
}

class GeoBeaconPacketDescriptor : public cClassDescriptor
{
  public:
    GeoBeaconPacketDescriptor();
    virtual ~GeoBeaconPacketDescriptor();

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

Register_ClassDescriptor(GeoBeaconPacketDescriptor);

GeoBeaconPacketDescriptor::GeoBeaconPacketDescriptor() : cClassDescriptor("GeoBeaconPacket", "GeoPacket")
{
}

GeoBeaconPacketDescriptor::~GeoBeaconPacketDescriptor()
{
}

bool GeoBeaconPacketDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<GeoBeaconPacket *>(obj)!=NULL;
}

const char *GeoBeaconPacketDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int GeoBeaconPacketDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount(object) : 2;
}

unsigned int GeoBeaconPacketDescriptor::getFieldTypeFlags(void *object, int field) const
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

const char *GeoBeaconPacketDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "geoPacketType",
        "nodeLocation",
    };
    return (field>=0 && field<2) ? fieldNames[field] : NULL;
}

int GeoBeaconPacketDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='g' && strcmp(fieldName, "geoPacketType")==0) return base+0;
    if (fieldName[0]=='n' && strcmp(fieldName, "nodeLocation")==0) return base+1;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *GeoBeaconPacketDescriptor::getFieldTypeString(void *object, int field) const
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

const char *GeoBeaconPacketDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int GeoBeaconPacketDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    GeoBeaconPacket *pp = (GeoBeaconPacket *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string GeoBeaconPacketDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    GeoBeaconPacket *pp = (GeoBeaconPacket *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getGeoPacketType());
        case 1: {std::stringstream out; out << pp->getNodeLocation(); return out.str();}
        default: return "";
    }
}

bool GeoBeaconPacketDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    GeoBeaconPacket *pp = (GeoBeaconPacket *)object; (void)pp;
    switch (field) {
        case 0: pp->setGeoPacketType(string2long(value)); return true;
        default: return false;
    }
}

const char *GeoBeaconPacketDescriptor::getFieldStructName(void *object, int field) const
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

void *GeoBeaconPacketDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    GeoBeaconPacket *pp = (GeoBeaconPacket *)object; (void)pp;
    switch (field) {
        case 1: return (void *)(&pp->getNodeLocation()); break;
        default: return NULL;
    }
}


