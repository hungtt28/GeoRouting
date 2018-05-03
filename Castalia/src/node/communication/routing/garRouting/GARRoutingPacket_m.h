//
// Generated file, do not edit! Created by nedtool 4.6 from src/node/communication/routing/garRouting/GARRoutingPacket.msg.
//

#ifndef _GARROUTINGPACKET_M_H_
#define _GARROUTINGPACKET_M_H_

#include <omnetpp.h>

// nedtool version check
#define MSGC_VERSION 0x0406
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of nedtool: 'make clean' should help.
#endif



// cplusplus {{
#include "GeoRoutingPacket_m.h"
#include "VirtualMobilityManager.h"
// }}

/**
 * Enum generated from <tt>src/node/communication/routing/garRouting/GARRoutingPacket.msg:28</tt> by nedtool.
 * <pre>
 * enum GARForwardingMode
 * {
 * 
 *     GAR_GREEDY_ROUTING = 0;
 *     GAR_GAR_ROUTING = 1;
 * }
 * </pre>
 */
enum GARForwardingMode {
    GAR_GREEDY_ROUTING = 0,
    GAR_GAR_ROUTING = 1
};

/**
 * Class generated from <tt>src/node/communication/routing/garRouting/GARRoutingPacket.msg:33</tt> by nedtool.
 * <pre>
 * packet GARRoutingPacket extends GeoRoutingPacket
 * {
 *     int routingMode = GAR_GREEDY_ROUTING;    // M
 *     NodeLocation_type destinationLocation;      // D
 *     NodeLocation_type startPerimeterLocation;	// Lp
 *     NodeLocation_type forwardPerimeterLocation;	// Lf
 *     string firstSenderAddress;					// e0
 *     string firstReceiverAddress;				// e0
 *     string senderAddress;
 * }
 * </pre>
 */
class GARRoutingPacket : public ::GeoRoutingPacket
{
  protected:
    int routingMode_var;
    NodeLocation_type destinationLocation_var;
    NodeLocation_type startPerimeterLocation_var;
    NodeLocation_type forwardPerimeterLocation_var;
    opp_string firstSenderAddress_var;
    opp_string firstReceiverAddress_var;
    opp_string senderAddress_var;

  private:
    void copy(const GARRoutingPacket& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const GARRoutingPacket&);

  public:
    GARRoutingPacket(const char *name=NULL, int kind=0);
    GARRoutingPacket(const GARRoutingPacket& other);
    virtual ~GARRoutingPacket();
    GARRoutingPacket& operator=(const GARRoutingPacket& other);
    virtual GARRoutingPacket *dup() const {return new GARRoutingPacket(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual int getRoutingMode() const;
    virtual void setRoutingMode(int routingMode);
    virtual NodeLocation_type& getDestinationLocation();
    virtual const NodeLocation_type& getDestinationLocation() const {return const_cast<GARRoutingPacket*>(this)->getDestinationLocation();}
    virtual void setDestinationLocation(const NodeLocation_type& destinationLocation);
    virtual NodeLocation_type& getStartPerimeterLocation();
    virtual const NodeLocation_type& getStartPerimeterLocation() const {return const_cast<GARRoutingPacket*>(this)->getStartPerimeterLocation();}
    virtual void setStartPerimeterLocation(const NodeLocation_type& startPerimeterLocation);
    virtual NodeLocation_type& getForwardPerimeterLocation();
    virtual const NodeLocation_type& getForwardPerimeterLocation() const {return const_cast<GARRoutingPacket*>(this)->getForwardPerimeterLocation();}
    virtual void setForwardPerimeterLocation(const NodeLocation_type& forwardPerimeterLocation);
    virtual const char * getFirstSenderAddress() const;
    virtual void setFirstSenderAddress(const char * firstSenderAddress);
    virtual const char * getFirstReceiverAddress() const;
    virtual void setFirstReceiverAddress(const char * firstReceiverAddress);
    virtual const char * getSenderAddress() const;
    virtual void setSenderAddress(const char * senderAddress);
};

inline void doPacking(cCommBuffer *b, GARRoutingPacket& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, GARRoutingPacket& obj) {obj.parsimUnpack(b);}


#endif // ifndef _GARROUTINGPACKET_M_H_

