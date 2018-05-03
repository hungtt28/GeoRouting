//
// Generated file, do not edit! Created by nedtool 4.6 from src/node/communication/routing/gearRouting/GEARHelloPacket.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "GEARHelloPacket_m.h"

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

Register_Class(GEARHelloPacket);

GEARHelloPacket::GEARHelloPacket(const char *name, int kind) : ::GeoPacket(name,kind)
{
    this->geoPacketType_var = GEO_BEACON_PACKET;
    this->learnedCost_var = 0;
}

GEARHelloPacket::GEARHelloPacket(const GEARHelloPacket& other) : ::GeoPacket(other)
{
    copy(other);
}

GEARHelloPacket::~GEARHelloPacket()
{
}

GEARHelloPacket& GEARHelloPacket::operator=(const GEARHelloPacket& other)
{
    if (this==&other) return *this;
    ::GeoPacket::operator=(other);
    copy(other);
    return *this;
}

void GEARHelloPacket::copy(const GEARHelloPacket& other)
{
    this->geoPacketType_var = other.geoPacketType_var;
    this->nodeLocation_var = other.nodeLocation_var;
    this->learnedCost_var = other.learnedCost_var;
}

void GEARHelloPacket::parsimPack(cCommBuffer *b)
{
    ::GeoPacket::parsimPack(b);
    doPacking(b,this->geoPacketType_var);
    doPacking(b,this->nodeLocation_var);
    doPacking(b,this->learnedCost_var);
}

void GEARHelloPacket::parsimUnpack(cCommBuffer *b)
{
    ::GeoPacket::parsimUnpack(b);
    doUnpacking(b,this->geoPacketType_var);
    doUnpacking(b,this->nodeLocation_var);
    doUnpacking(b,this->learnedCost_var);
}

int GEARHelloPacket::getGeoPacketType() const
{
    return geoPacketType_var;
}

void GEARHelloPacket::setGeoPacketType(int geoPacketType)
{
    this->geoPacketType_var = geoPacketType;
}

NodeLocation_type& GEARHelloPacket::getNodeLocation()
{
    return nodeLocation_var;
}

void GEARHelloPacket::setNodeLocation(const NodeLocation_type& nodeLocation)
{
    this->nodeLocation_var = nodeLocation;
}

double GEARHelloPacket::getLearnedCost() const
{
    return learnedCost_var;
}

void GEARHelloPacket::setLearnedCost(double learnedCost)
{
    this->learnedCost_var = learnedCost;
}

class GEARHelloPacketDescriptor : public cClassDescriptor
{
  public:
    GEARHelloPacketDescriptor();
    virtual ~GEARHelloPacketDescriptor();

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

Register_ClassDescriptor(GEARHelloPacketDescriptor);

GEARHelloPacketDescriptor::GEARHelloPacketDescriptor() : cClassDescriptor("GEARHelloPacket", "GeoPacket")
{
}

GEARHelloPacketDescriptor::~GEARHelloPacketDescriptor()
{
}

bool GEARHelloPacketDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<GEARHelloPacket *>(obj)!=NULL;
}

const char *GEARHelloPacketDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int GEARHelloPacketDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 3+basedesc->getFieldCount(object) : 3;
}

unsigned int GEARHelloPacketDescriptor::getFieldTypeFlags(void *object, int field) const
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
        FD_ISEDITABLE,
    };
    return (field>=0 && field<3) ? fieldTypeFlags[field] : 0;
}

const char *GEARHelloPacketDescriptor::getFieldName(void *object, int field) const
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
        "learnedCost",
    };
    return (field>=0 && field<3) ? fieldNames[field] : NULL;
}

int GEARHelloPacketDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='g' && strcmp(fieldName, "geoPacketType")==0) return base+0;
    if (fieldName[0]=='n' && strcmp(fieldName, "nodeLocation")==0) return base+1;
    if (fieldName[0]=='l' && strcmp(fieldName, "learnedCost")==0) return base+2;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *GEARHelloPacketDescriptor::getFieldTypeString(void *object, int field) const
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
        "double",
    };
    return (field>=0 && field<3) ? fieldTypeStrings[field] : NULL;
}

const char *GEARHelloPacketDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int GEARHelloPacketDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    GEARHelloPacket *pp = (GEARHelloPacket *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string GEARHelloPacketDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    GEARHelloPacket *pp = (GEARHelloPacket *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getGeoPacketType());
        case 1: {std::stringstream out; out << pp->getNodeLocation(); return out.str();}
        case 2: return double2string(pp->getLearnedCost());
        default: return "";
    }
}

bool GEARHelloPacketDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    GEARHelloPacket *pp = (GEARHelloPacket *)object; (void)pp;
    switch (field) {
        case 0: pp->setGeoPacketType(string2long(value)); return true;
        case 2: pp->setLearnedCost(string2double(value)); return true;
        default: return false;
    }
}

const char *GEARHelloPacketDescriptor::getFieldStructName(void *object, int field) const
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

void *GEARHelloPacketDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    GEARHelloPacket *pp = (GEARHelloPacket *)object; (void)pp;
    switch (field) {
        case 1: return (void *)(&pp->getNodeLocation()); break;
        default: return NULL;
    }
}


