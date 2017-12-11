//
// Generated file, do not edit! Created by nedtool 4.6 from src/node/communication/routing/gpsrRouting/GpsrRoutingPacket.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "GpsrRoutingPacket_m.h"

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
    cEnum *e = cEnum::find("GpsrPacketDef");
    if (!e) enums.getInstance()->add(e = new cEnum("GpsrPacketDef"));
    e->insert(GPSR_DATA_PACKET, "GPSR_DATA_PACKET");
    e->insert(GPSR_HELLO_MSG_PACKET, "GPSR_HELLO_MSG_PACKET");
    e->insert(GPSR_REP_HELLO_MSG_PACKET, "GPSR_REP_HELLO_MSG_PACKET");
    e->insert(GPSR_SINK_ADDRESS_PACKET, "GPSR_SINK_ADDRESS_PACKET");
);

Register_Class(GpsrPacket);

GpsrPacket::GpsrPacket(const char *name, int kind) : ::RoutingPacket(name,kind)
{
    this->GpsrPacketKind_var = 0;
    this->x_src_var = 0;
    this->y_src_var = 0;
    this->x_dst_var = 0;
    this->y_dst_var = 0;
}

GpsrPacket::GpsrPacket(const GpsrPacket& other) : ::RoutingPacket(other)
{
    copy(other);
}

GpsrPacket::~GpsrPacket()
{
}

GpsrPacket& GpsrPacket::operator=(const GpsrPacket& other)
{
    if (this==&other) return *this;
    ::RoutingPacket::operator=(other);
    copy(other);
    return *this;
}

void GpsrPacket::copy(const GpsrPacket& other)
{
    this->GpsrPacketKind_var = other.GpsrPacketKind_var;
    this->x_src_var = other.x_src_var;
    this->y_src_var = other.y_src_var;
    this->x_dst_var = other.x_dst_var;
    this->y_dst_var = other.y_dst_var;
}

void GpsrPacket::parsimPack(cCommBuffer *b)
{
    ::RoutingPacket::parsimPack(b);
    doPacking(b,this->GpsrPacketKind_var);
    doPacking(b,this->x_src_var);
    doPacking(b,this->y_src_var);
    doPacking(b,this->x_dst_var);
    doPacking(b,this->y_dst_var);
}

void GpsrPacket::parsimUnpack(cCommBuffer *b)
{
    ::RoutingPacket::parsimUnpack(b);
    doUnpacking(b,this->GpsrPacketKind_var);
    doUnpacking(b,this->x_src_var);
    doUnpacking(b,this->y_src_var);
    doUnpacking(b,this->x_dst_var);
    doUnpacking(b,this->y_dst_var);
}

int GpsrPacket::getGpsrPacketKind() const
{
    return GpsrPacketKind_var;
}

void GpsrPacket::setGpsrPacketKind(int GpsrPacketKind)
{
    this->GpsrPacketKind_var = GpsrPacketKind;
}

int GpsrPacket::getX_src() const
{
    return x_src_var;
}

void GpsrPacket::setX_src(int x_src)
{
    this->x_src_var = x_src;
}

int GpsrPacket::getY_src() const
{
    return y_src_var;
}

void GpsrPacket::setY_src(int y_src)
{
    this->y_src_var = y_src;
}

int GpsrPacket::getX_dst() const
{
    return x_dst_var;
}

void GpsrPacket::setX_dst(int x_dst)
{
    this->x_dst_var = x_dst;
}

int GpsrPacket::getY_dst() const
{
    return y_dst_var;
}

void GpsrPacket::setY_dst(int y_dst)
{
    this->y_dst_var = y_dst;
}

class GpsrPacketDescriptor : public cClassDescriptor
{
  public:
    GpsrPacketDescriptor();
    virtual ~GpsrPacketDescriptor();

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

Register_ClassDescriptor(GpsrPacketDescriptor);

GpsrPacketDescriptor::GpsrPacketDescriptor() : cClassDescriptor("GpsrPacket", "RoutingPacket")
{
}

GpsrPacketDescriptor::~GpsrPacketDescriptor()
{
}

bool GpsrPacketDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<GpsrPacket *>(obj)!=NULL;
}

const char *GpsrPacketDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int GpsrPacketDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 5+basedesc->getFieldCount(object) : 5;
}

unsigned int GpsrPacketDescriptor::getFieldTypeFlags(void *object, int field) const
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
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<5) ? fieldTypeFlags[field] : 0;
}

const char *GpsrPacketDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "GpsrPacketKind",
        "x_src",
        "y_src",
        "x_dst",
        "y_dst",
    };
    return (field>=0 && field<5) ? fieldNames[field] : NULL;
}

int GpsrPacketDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='G' && strcmp(fieldName, "GpsrPacketKind")==0) return base+0;
    if (fieldName[0]=='x' && strcmp(fieldName, "x_src")==0) return base+1;
    if (fieldName[0]=='y' && strcmp(fieldName, "y_src")==0) return base+2;
    if (fieldName[0]=='x' && strcmp(fieldName, "x_dst")==0) return base+3;
    if (fieldName[0]=='y' && strcmp(fieldName, "y_dst")==0) return base+4;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *GpsrPacketDescriptor::getFieldTypeString(void *object, int field) const
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
        "int",
        "int",
        "int",
    };
    return (field>=0 && field<5) ? fieldTypeStrings[field] : NULL;
}

const char *GpsrPacketDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0:
            if (!strcmp(propertyname,"enum")) return "GpsrPacketDef";
            return NULL;
        default: return NULL;
    }
}

int GpsrPacketDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    GpsrPacket *pp = (GpsrPacket *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string GpsrPacketDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    GpsrPacket *pp = (GpsrPacket *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getGpsrPacketKind());
        case 1: return long2string(pp->getX_src());
        case 2: return long2string(pp->getY_src());
        case 3: return long2string(pp->getX_dst());
        case 4: return long2string(pp->getY_dst());
        default: return "";
    }
}

bool GpsrPacketDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    GpsrPacket *pp = (GpsrPacket *)object; (void)pp;
    switch (field) {
        case 0: pp->setGpsrPacketKind(string2long(value)); return true;
        case 1: pp->setX_src(string2long(value)); return true;
        case 2: pp->setY_src(string2long(value)); return true;
        case 3: pp->setX_dst(string2long(value)); return true;
        case 4: pp->setY_dst(string2long(value)); return true;
        default: return false;
    }
}

const char *GpsrPacketDescriptor::getFieldStructName(void *object, int field) const
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

void *GpsrPacketDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    GpsrPacket *pp = (GpsrPacket *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}


