//
// Generated file, do not edit! Created by nedtool 4.6 from src/node/communication/routing/gpsrRouting/GpsrRoutingControl.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "GpsrRoutingControl_m.h"

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
    cEnum *e = cEnum::find("GpsrRoutingCommandDef");
    if (!e) enums.getInstance()->add(e = new cEnum("GpsrRoutingCommandDef"));
    e->insert(SET_GPSR_NODE_POS, "SET_GPSR_NODE_POS");
    e->insert(SET_GPSR_SINK_POS, "SET_GPSR_SINK_POS");
    e->insert(SET_GPSR_BOOL, "SET_GPSR_BOOL");
);

Register_Class(GpsrRoutingControlCommand);

GpsrRoutingControlCommand::GpsrRoutingControlCommand(const char *name, int kind) : ::cMessage(name,kind)
{
    this->gpsrRoutingCommandKind_var = 0;
    this->double1_var = 0;
    this->double2_var = 0;
    this->int1_var = 0;
    this->int2_var = 0;
    this->bool1_var = false;
}

GpsrRoutingControlCommand::GpsrRoutingControlCommand(const GpsrRoutingControlCommand& other) : ::cMessage(other)
{
    copy(other);
}

GpsrRoutingControlCommand::~GpsrRoutingControlCommand()
{
}

GpsrRoutingControlCommand& GpsrRoutingControlCommand::operator=(const GpsrRoutingControlCommand& other)
{
    if (this==&other) return *this;
    ::cMessage::operator=(other);
    copy(other);
    return *this;
}

void GpsrRoutingControlCommand::copy(const GpsrRoutingControlCommand& other)
{
    this->gpsrRoutingCommandKind_var = other.gpsrRoutingCommandKind_var;
    this->double1_var = other.double1_var;
    this->double2_var = other.double2_var;
    this->int1_var = other.int1_var;
    this->int2_var = other.int2_var;
    this->bool1_var = other.bool1_var;
}

void GpsrRoutingControlCommand::parsimPack(cCommBuffer *b)
{
    ::cMessage::parsimPack(b);
    doPacking(b,this->gpsrRoutingCommandKind_var);
    doPacking(b,this->double1_var);
    doPacking(b,this->double2_var);
    doPacking(b,this->int1_var);
    doPacking(b,this->int2_var);
    doPacking(b,this->bool1_var);
}

void GpsrRoutingControlCommand::parsimUnpack(cCommBuffer *b)
{
    ::cMessage::parsimUnpack(b);
    doUnpacking(b,this->gpsrRoutingCommandKind_var);
    doUnpacking(b,this->double1_var);
    doUnpacking(b,this->double2_var);
    doUnpacking(b,this->int1_var);
    doUnpacking(b,this->int2_var);
    doUnpacking(b,this->bool1_var);
}

int GpsrRoutingControlCommand::getGpsrRoutingCommandKind() const
{
    return gpsrRoutingCommandKind_var;
}

void GpsrRoutingControlCommand::setGpsrRoutingCommandKind(int gpsrRoutingCommandKind)
{
    this->gpsrRoutingCommandKind_var = gpsrRoutingCommandKind;
}

double GpsrRoutingControlCommand::getDouble1() const
{
    return double1_var;
}

void GpsrRoutingControlCommand::setDouble1(double double1)
{
    this->double1_var = double1;
}

double GpsrRoutingControlCommand::getDouble2() const
{
    return double2_var;
}

void GpsrRoutingControlCommand::setDouble2(double double2)
{
    this->double2_var = double2;
}

int GpsrRoutingControlCommand::getInt1() const
{
    return int1_var;
}

void GpsrRoutingControlCommand::setInt1(int int1)
{
    this->int1_var = int1;
}

int GpsrRoutingControlCommand::getInt2() const
{
    return int2_var;
}

void GpsrRoutingControlCommand::setInt2(int int2)
{
    this->int2_var = int2;
}

bool GpsrRoutingControlCommand::getBool1() const
{
    return bool1_var;
}

void GpsrRoutingControlCommand::setBool1(bool bool1)
{
    this->bool1_var = bool1;
}

class GpsrRoutingControlCommandDescriptor : public cClassDescriptor
{
  public:
    GpsrRoutingControlCommandDescriptor();
    virtual ~GpsrRoutingControlCommandDescriptor();

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

Register_ClassDescriptor(GpsrRoutingControlCommandDescriptor);

GpsrRoutingControlCommandDescriptor::GpsrRoutingControlCommandDescriptor() : cClassDescriptor("GpsrRoutingControlCommand", "cMessage")
{
}

GpsrRoutingControlCommandDescriptor::~GpsrRoutingControlCommandDescriptor()
{
}

bool GpsrRoutingControlCommandDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<GpsrRoutingControlCommand *>(obj)!=NULL;
}

const char *GpsrRoutingControlCommandDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int GpsrRoutingControlCommandDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 6+basedesc->getFieldCount(object) : 6;
}

unsigned int GpsrRoutingControlCommandDescriptor::getFieldTypeFlags(void *object, int field) const
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
        FD_ISEDITABLE,
    };
    return (field>=0 && field<6) ? fieldTypeFlags[field] : 0;
}

const char *GpsrRoutingControlCommandDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "gpsrRoutingCommandKind",
        "double1",
        "double2",
        "int1",
        "int2",
        "bool1",
    };
    return (field>=0 && field<6) ? fieldNames[field] : NULL;
}

int GpsrRoutingControlCommandDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='g' && strcmp(fieldName, "gpsrRoutingCommandKind")==0) return base+0;
    if (fieldName[0]=='d' && strcmp(fieldName, "double1")==0) return base+1;
    if (fieldName[0]=='d' && strcmp(fieldName, "double2")==0) return base+2;
    if (fieldName[0]=='i' && strcmp(fieldName, "int1")==0) return base+3;
    if (fieldName[0]=='i' && strcmp(fieldName, "int2")==0) return base+4;
    if (fieldName[0]=='b' && strcmp(fieldName, "bool1")==0) return base+5;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *GpsrRoutingControlCommandDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "double",
        "double",
        "int",
        "int",
        "bool",
    };
    return (field>=0 && field<6) ? fieldTypeStrings[field] : NULL;
}

const char *GpsrRoutingControlCommandDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0:
            if (!strcmp(propertyname,"enum")) return "GpsrRoutingCommandDef";
            return NULL;
        default: return NULL;
    }
}

int GpsrRoutingControlCommandDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    GpsrRoutingControlCommand *pp = (GpsrRoutingControlCommand *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string GpsrRoutingControlCommandDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    GpsrRoutingControlCommand *pp = (GpsrRoutingControlCommand *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getGpsrRoutingCommandKind());
        case 1: return double2string(pp->getDouble1());
        case 2: return double2string(pp->getDouble2());
        case 3: return long2string(pp->getInt1());
        case 4: return long2string(pp->getInt2());
        case 5: return bool2string(pp->getBool1());
        default: return "";
    }
}

bool GpsrRoutingControlCommandDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    GpsrRoutingControlCommand *pp = (GpsrRoutingControlCommand *)object; (void)pp;
    switch (field) {
        case 0: pp->setGpsrRoutingCommandKind(string2long(value)); return true;
        case 1: pp->setDouble1(string2double(value)); return true;
        case 2: pp->setDouble2(string2double(value)); return true;
        case 3: pp->setInt1(string2long(value)); return true;
        case 4: pp->setInt2(string2long(value)); return true;
        case 5: pp->setBool1(string2bool(value)); return true;
        default: return false;
    }
}

const char *GpsrRoutingControlCommandDescriptor::getFieldStructName(void *object, int field) const
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

void *GpsrRoutingControlCommandDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    GpsrRoutingControlCommand *pp = (GpsrRoutingControlCommand *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}


