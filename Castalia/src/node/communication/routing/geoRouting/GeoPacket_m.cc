//
// Generated file, do not edit! Created by nedtool 4.6 from src/node/communication/routing/geoRouting/GeoPacket.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "GeoPacket_m.h"

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
    cEnum *e = cEnum::find("GeoPacketDef");
    if (!e) enums.getInstance()->add(e = new cEnum("GeoPacketDef"));
    e->insert(GEO_BEACON_PACKET, "GEO_BEACON_PACKET");
    e->insert(GEO_ROUTING_PACKET, "GEO_ROUTING_PACKET");
    e->insert(GEO_CONTROL_PACKET, "GEO_CONTROL_PACKET");
);

Register_Class(GeoPacket);

GeoPacket::GeoPacket(const char *name, int kind) : ::RoutingPacket(name,kind)
{
    this->geoPacketType_var = 0;
    this->sourceId_var = -1;
}

GeoPacket::GeoPacket(const GeoPacket& other) : ::RoutingPacket(other)
{
    copy(other);
}

GeoPacket::~GeoPacket()
{
}

GeoPacket& GeoPacket::operator=(const GeoPacket& other)
{
    if (this==&other) return *this;
    ::RoutingPacket::operator=(other);
    copy(other);
    return *this;
}

void GeoPacket::copy(const GeoPacket& other)
{
    this->geoPacketType_var = other.geoPacketType_var;
    this->sourceId_var = other.sourceId_var;
}

void GeoPacket::parsimPack(cCommBuffer *b)
{
    ::RoutingPacket::parsimPack(b);
    doPacking(b,this->geoPacketType_var);
    doPacking(b,this->sourceId_var);
}

void GeoPacket::parsimUnpack(cCommBuffer *b)
{
    ::RoutingPacket::parsimUnpack(b);
    doUnpacking(b,this->geoPacketType_var);
    doUnpacking(b,this->sourceId_var);
}

int GeoPacket::getGeoPacketType() const
{
    return geoPacketType_var;
}

void GeoPacket::setGeoPacketType(int geoPacketType)
{
    this->geoPacketType_var = geoPacketType;
}

int GeoPacket::getSourceId() const
{
    return sourceId_var;
}

void GeoPacket::setSourceId(int sourceId)
{
    this->sourceId_var = sourceId;
}

class GeoPacketDescriptor : public cClassDescriptor
{
  public:
    GeoPacketDescriptor();
    virtual ~GeoPacketDescriptor();

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

Register_ClassDescriptor(GeoPacketDescriptor);

GeoPacketDescriptor::GeoPacketDescriptor() : cClassDescriptor("GeoPacket", "RoutingPacket")
{
}

GeoPacketDescriptor::~GeoPacketDescriptor()
{
}

bool GeoPacketDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<GeoPacket *>(obj)!=NULL;
}

const char *GeoPacketDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int GeoPacketDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount(object) : 2;
}

unsigned int GeoPacketDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<2) ? fieldTypeFlags[field] : 0;
}

const char *GeoPacketDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "geoPacketType",
        "sourceId",
    };
    return (field>=0 && field<2) ? fieldNames[field] : NULL;
}

int GeoPacketDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='g' && strcmp(fieldName, "geoPacketType")==0) return base+0;
    if (fieldName[0]=='s' && strcmp(fieldName, "sourceId")==0) return base+1;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *GeoPacketDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "int",
    };
    return (field>=0 && field<2) ? fieldTypeStrings[field] : NULL;
}

const char *GeoPacketDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0:
            if (!strcmp(propertyname,"enum")) return "GeoPacketDef";
            return NULL;
        default: return NULL;
    }
}

int GeoPacketDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    GeoPacket *pp = (GeoPacket *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string GeoPacketDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    GeoPacket *pp = (GeoPacket *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getGeoPacketType());
        case 1: return long2string(pp->getSourceId());
        default: return "";
    }
}

bool GeoPacketDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    GeoPacket *pp = (GeoPacket *)object; (void)pp;
    switch (field) {
        case 0: pp->setGeoPacketType(string2long(value)); return true;
        case 1: pp->setSourceId(string2long(value)); return true;
        default: return false;
    }
}

const char *GeoPacketDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    };
}

void *GeoPacketDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    GeoPacket *pp = (GeoPacket *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}


