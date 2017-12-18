//
// Generated file, do not edit! Created by nedtool 4.6 from src/node/communication/routing/boundholeRouting/BHPacket.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "BHPacket_m.h"

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
    cEnum *e = cEnum::find("BoundHoleMode");
    if (!e) enums.getInstance()->add(e = new cEnum("BoundHoleMode"));
    e->insert(BOUNDHOLE_SUPPRESSED_START_MODE, "BOUNDHOLE_SUPPRESSED_START_MODE");
    e->insert(BOUNDHOLE_REFRESH_MODE, "BOUNDHOLE_REFRESH_MODE");
);

Register_Class(BHPacket);

BHPacket::BHPacket(const char *name, int kind) : ::GeoControlPacket(name,kind)
{
    this->boundHoleMode_var = BOUNDHOLE_SUPPRESSED_START_MODE;
    this->originalId_var = -1;
    this->holeId_var = -1;
    this->bForce_var = false;
    this->iNode_var = -1;
}

BHPacket::BHPacket(const BHPacket& other) : ::GeoControlPacket(other)
{
    copy(other);
}

BHPacket::~BHPacket()
{
}

BHPacket& BHPacket::operator=(const BHPacket& other)
{
    if (this==&other) return *this;
    ::GeoControlPacket::operator=(other);
    copy(other);
    return *this;
}

void BHPacket::copy(const BHPacket& other)
{
    this->boundHoleMode_var = other.boundHoleMode_var;
    this->originalId_var = other.originalId_var;
    this->holeId_var = other.holeId_var;
    this->bForce_var = other.bForce_var;
    this->iNode_var = other.iNode_var;
    this->boundHoleNodes_var = other.boundHoleNodes_var;
}

void BHPacket::parsimPack(cCommBuffer *b)
{
    ::GeoControlPacket::parsimPack(b);
    doPacking(b,this->boundHoleMode_var);
    doPacking(b,this->originalId_var);
    doPacking(b,this->holeId_var);
    doPacking(b,this->bForce_var);
    doPacking(b,this->iNode_var);
    doPacking(b,this->boundHoleNodes_var);
}

void BHPacket::parsimUnpack(cCommBuffer *b)
{
    ::GeoControlPacket::parsimUnpack(b);
    doUnpacking(b,this->boundHoleMode_var);
    doUnpacking(b,this->originalId_var);
    doUnpacking(b,this->holeId_var);
    doUnpacking(b,this->bForce_var);
    doUnpacking(b,this->iNode_var);
    doUnpacking(b,this->boundHoleNodes_var);
}

int BHPacket::getBoundHoleMode() const
{
    return boundHoleMode_var;
}

void BHPacket::setBoundHoleMode(int boundHoleMode)
{
    this->boundHoleMode_var = boundHoleMode;
}

int BHPacket::getOriginalId() const
{
    return originalId_var;
}

void BHPacket::setOriginalId(int originalId)
{
    this->originalId_var = originalId;
}

int BHPacket::getHoleId() const
{
    return holeId_var;
}

void BHPacket::setHoleId(int holeId)
{
    this->holeId_var = holeId;
}

bool BHPacket::getBForce() const
{
    return bForce_var;
}

void BHPacket::setBForce(bool bForce)
{
    this->bForce_var = bForce;
}

int BHPacket::getINode() const
{
    return iNode_var;
}

void BHPacket::setINode(int iNode)
{
    this->iNode_var = iNode;
}

Nodes& BHPacket::getBoundHoleNodes()
{
    return boundHoleNodes_var;
}

void BHPacket::setBoundHoleNodes(const Nodes& boundHoleNodes)
{
    this->boundHoleNodes_var = boundHoleNodes;
}

class BHPacketDescriptor : public cClassDescriptor
{
  public:
    BHPacketDescriptor();
    virtual ~BHPacketDescriptor();

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

Register_ClassDescriptor(BHPacketDescriptor);

BHPacketDescriptor::BHPacketDescriptor() : cClassDescriptor("BHPacket", "GeoControlPacket")
{
}

BHPacketDescriptor::~BHPacketDescriptor()
{
}

bool BHPacketDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<BHPacket *>(obj)!=NULL;
}

const char *BHPacketDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int BHPacketDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 6+basedesc->getFieldCount(object) : 6;
}

unsigned int BHPacketDescriptor::getFieldTypeFlags(void *object, int field) const
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
        FD_ISCOMPOUND,
    };
    return (field>=0 && field<6) ? fieldTypeFlags[field] : 0;
}

const char *BHPacketDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "boundHoleMode",
        "originalId",
        "holeId",
        "bForce",
        "iNode",
        "boundHoleNodes",
    };
    return (field>=0 && field<6) ? fieldNames[field] : NULL;
}

int BHPacketDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='b' && strcmp(fieldName, "boundHoleMode")==0) return base+0;
    if (fieldName[0]=='o' && strcmp(fieldName, "originalId")==0) return base+1;
    if (fieldName[0]=='h' && strcmp(fieldName, "holeId")==0) return base+2;
    if (fieldName[0]=='b' && strcmp(fieldName, "bForce")==0) return base+3;
    if (fieldName[0]=='i' && strcmp(fieldName, "iNode")==0) return base+4;
    if (fieldName[0]=='b' && strcmp(fieldName, "boundHoleNodes")==0) return base+5;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *BHPacketDescriptor::getFieldTypeString(void *object, int field) const
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
        "bool",
        "int",
        "Nodes",
    };
    return (field>=0 && field<6) ? fieldTypeStrings[field] : NULL;
}

const char *BHPacketDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int BHPacketDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    BHPacket *pp = (BHPacket *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string BHPacketDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    BHPacket *pp = (BHPacket *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getBoundHoleMode());
        case 1: return long2string(pp->getOriginalId());
        case 2: return long2string(pp->getHoleId());
        case 3: return bool2string(pp->getBForce());
        case 4: return long2string(pp->getINode());
        case 5: {std::stringstream out; out << pp->getBoundHoleNodes(); return out.str();}
        default: return "";
    }
}

bool BHPacketDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    BHPacket *pp = (BHPacket *)object; (void)pp;
    switch (field) {
        case 0: pp->setBoundHoleMode(string2long(value)); return true;
        case 1: pp->setOriginalId(string2long(value)); return true;
        case 2: pp->setHoleId(string2long(value)); return true;
        case 3: pp->setBForce(string2bool(value)); return true;
        case 4: pp->setINode(string2long(value)); return true;
        default: return false;
    }
}

const char *BHPacketDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 5: return opp_typename(typeid(Nodes));
        default: return NULL;
    };
}

void *BHPacketDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    BHPacket *pp = (BHPacket *)object; (void)pp;
    switch (field) {
        case 5: return (void *)(&pp->getBoundHoleNodes()); break;
        default: return NULL;
    }
}


