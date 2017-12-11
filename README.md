# Castalia GeoRouting Protocol

1. [Installation](#installation)
2. [Castalia Overview](#castalia-overview)
3. [GeoRouting module](#georouting-module)
4. [Adding new GeoProtocol](#adding-new-geoprotocol)
5. [GPSR example](#gpsr-example)
6. [References](#references)
7. [License](#license)

Some word

## 1. Installation <a name="installation"></a>

This Castalia version 3.3 only be built with Omnet++ 4.6. To run in Omnet++ 5.x you must fix some "opp_error" function and others small things, but I'm not sure it would work well.

The addition module GeoRouting is built with Castalia.

### Windows

#### Build Omnet++

1. Download omnet++ 4.6 from https://omnetpp.org/
2. Extract omnetpp-4.6-src-windows.zip
3. Run mingwenv.cmd
4. ./configure
5. make

#### Build Castalia with GeoRouting

1. Run mingwend.cmd
2. cd path/to/Castalia
3. make clean
4. makemake
5. make depend
6. make

#### Run GeoRouting simulation test

1. cd Simulations/routingTest
2. ../../Castalia.exe

### Linux, MAC OS

I do not try but I think it do the same in Windows.

## 2. Castalia Overview <a name="castalia-overview"></a>

These details of Castalia you can find in it's documents.

> Castalia is built on top of OMNeT++. It follows the modular structure of OMNeT++ and modules communicate with each other by passing messages. Each node provides an interaction between the physical process and wireless channels.

![](image/a1.png)

![](image/b1.png)

## 3. GeoRouting module <a name="georouting-module"></a>

GeoRouting module contains 3 parts and can be extended in the future.

### Simulations/routingTest

#### omnetpp.ini
File config for whole module in the simulation test.

```bash
include ../Parameters/Castalia.ini
sim-time-limit = 300s
```

Include default configuration of Castalia Simualtion and set time duration for the test.

```bash
include ../Parameters/WirelessChannel/Ideal.ini
SN.node[*].Communication.Radio.RadioParametersFile = "../Parameters/Radio/CC2420.txt"
SN.node[*].Communication.Radio.mode = "IDEAL"
SN.node[*].Communication.Radio.collisionModel = 0
```

```bash
SN.node[*].Communication.MACProtocolName = "TunableMAC"
SN.node[*].Communication.MAC.dutyCycle = 1.0
SN.node[*].Communication.MAC.randomTxOffset = 0
SN.node[*].Communication.MAC.backoffType = 2
```

Config parameters for Radio Layer and MAC Layer.

```bash
# 40m -> PLd0 = (-5dBm - max(-95dBm, -100dBm)) - 10 * pathLossExponent * log(40m)
SN.wirelessChannel.sigma = 0
SN.wirelessChannel.bidirectionalSigma = 0
SN.node[*].Communication.Radio.TxOutputPower = "-5dBm"
SN.wirelessChannel.pathLossExponent = 2.4
SN.wirelessChannel.PLd0 = 51.55056
```

Config wirelessChannel to set radion range. In this simulation test, we concern more about radio range, Castalia give us converge equation to compute it. See detail in documentations.

```bash
SN.node[*].ApplicationName = "RoutingTest"
SN.node[*].Application.collectTraceInfo = false
```

Set application module we use.

```bash
SN.node[*].Communication.RoutingProtocolName = "GeoRouting"
SN.node[*].Communication.Routing.protocolName = "GPSR"
SN.node[*].Communication.Routing.protocolMode = "GG"
```

Set routing protocol we want to use.

```bash
include node_location.ini

SN.field_x = 200					# meters
SN.field_y = 400					# meters
SN.numNodes = 100

SN.node[0].Application.packet_rate = 0.2
SN.node[0].Application.maxData = 100
SN.node[0].Application.startupDelay = 15
SN.node[0].Application.nextRecipient = "99"
```

Import node coordnates from file node_location.ini. field_x, field_y are maximum coordinate of the map. numNode is number of node in the map.

Example sending packet from node 0 to node 99, we set nextRecipient of node 0 is "99".

#### node_location.ini

This file contains coordinates of nodes in the map with format:

```bash
SN.node[0].xCoor = 46
SN.node[0].yCoor = 82
SN.node[0].zCoor = 0
```

#### Castalia-Trace.txt

Trace file format:

```bash
20.208167204752   SN.node[65].Communication.Routing        SEND      PACKET #0         FROM 0         TO 99        currentHop 65        nextHop 99        
20.216755569946   SN.node[99].Communication.Routing        RECEIVE   PACKET #0         FROM 0         TO 99        currentHop 99        previousHop 65        
20.216755569946   SN.node[99].Communication.Routing        COMPLETE  PACKET #0         FROM 0         TO 99   
20.216755569946   SN.node[99].Communication.Routing        DROP      PACKET #0         FROM 0         TO 99   
```

Each row have format:
`<time event>`
`<module>`
`<operation> - SEND, RECEIVE, DROP, COMPLETE`
`<PACKET #number>`
`<FROM source>`
`<TO destination>`
`<currentHop address>`
`<nextHop address>`
`<previousHop address>`

### src/node/application/routingTest

#### RoutingTest application <a name="routingtest"></a>

```Cpp
GeoRoutingControl *cmd1 = new GeoRoutingControl("GEO set node pos", NETWORK_CONTROL_COMMAND);
cmd1->setGeoRoutingCommand(SET_GEO_NODE_POS);
cmd1->setNodeLocation(nodeLocation);
toNetworkLayer(cmd1);
```

This command message to let routing layer know node's location. Using *SET_GEO_NODE_POS* to update it's position.

```Cpp
GeoApplicationPacket *newPacket = new GeoApplicationPacket("Geo Application packet", APPLICATION_PACKET);
newPacket->setSequenceNumber(dataSN);
newPacket->setDestinationLocation(nodeLocation);
toNetworkLayer(newPacket, par("nextRecipient"));
```

To send a packet to destination, we create a **GeoApplicationPacket**, set destination location we want to send to, then send to NetworkLayer. NetworkLayer would forward this packet to nextHop.

#### GeoApplicationPacket.msg

```Cpp
packet GeoApplicationPacket extends ApplicationPacket {
    NodeLocation_type destinationLocation;
}
```

**GeoApplicationPacket** is **ApplicationPacket** added destination location.

### src/node/communication/routing/geoRouting

#### GeoRouting

##### GeoRouting::startup() <a name="georouting-startup"></a>

Initialize, setup environment variable for Routing Layer.

```Cpp
neighborTable = new NeighborTable();
geoProtocol = getGeoProtocol(par("protocolName"), par("protocolMode"));
```

Create NeighborTable and choose protocol to use.

##### GeoRouting::timerFiredCallback()

Timer callback, which handle events by SetTimer()

```Cpp
switch(index){
    case GEO_HELLO_MSG_REFRESH_TIMER :{
        sendHelloMessage();
        break;
    }
    default: break;
}
```

Event **GEO_HELLO_MSG_REFRESH_TIMER** to trigger sendHelloMessage() function.

##### GeoRouting::handleNetworkControlCommand()

Interface, which handle **NETWORK_CONTROL_COMMAND** sent from Application Layer. See [RoutingTest](#routingtest)

```Cpp
switch (cmd->getGeoRoutingCommand()) {

    case SET_GEO_NODE_POS: {
        nodeLocation.x = cmd->getNodeLocation().x;
        nodeLocation.y = cmd->getNodeLocation().y;
        ...
        sendHelloMessage();
    }
}
```

Command **SET_GEO_NODE_POS** to update current location of sensor to Routing Layer. When get new location, it would broadcast Hello message to neighbors.

##### GeoRouting::sendHelloMessage()

```Cpp
GeoBeaconPacket *helloMsg = new GeoBeaconPacket("Geo hello message packet", NETWORK_LAYER_PACKET);
helloMsg->setSource(SELF_NETWORK_ADDRESS);
helloMsg->setNodeLocation(nodeLocation);
toMacLayer(helloMsg, BROADCAST_MAC_ADDRESS);

seqHello++;
setTimer(GEO_HELLO_MSG_REFRESH_TIMER, helloInterval);
```

Broadcast Hello message **GeoBeaconPacket** to neighbors. The Hello message simplest contain address and position information of node.

##### GeoRouting::fromApplicationLayer() <a name="fromapplicationlayer"></a>

This interface receive message **NETWORK_LAYER_PACKET** from Application Layer. *ApplicationPacket* and *GeoApplicationPacket* has automatic set up when we create the packet.

When receive the packet and the destination, it add routing packet and forward to Mac Layer to send to it's neighbor.

```Cpp
GeoRoutingPacket *dataPacket = geoProtocol->createGeoRoutingPacket(this);
...
forwardDataPacket(dataPacket);
```

Create new **GeoRoutingPacket**, which contain information for geo routing and encapsule with packet from Application to send to MAC Layer.

##### GeoRouting::forwardDataPacket() <a name="forwarddatapacket"></a>

This function to call **GeoProtocol::findNextHop** to get neighbor to forward the packet. And then send it to Mac Layer. Mac Layer will transfer it to neighbor's Mac Layer.

```Cpp
auto t = geoProtocol->findNextHop(this, pkt);
int nextHop = std::get<0>(t);
GeoRoutingPacket *dataPacket = std::get<1>(t);
...
toMacLayer(dataPacket, nextHop);
```

##### GeoRouting::fromMacLayer()

**fromMacLayer** interface handle the message received by MacLayer from node's neighbors. When receive a packet, it have to decide to do next. In GeoRouting, we define two type of packet: **GEO_BEACON_PACKET** for hello message and **GEO_ROUTING_PACKET** for data packet transfer.

```Cpp
switch (netPacket->getGeoPacketType()) {

    // process hello msg
    case GEO_BEACON_PACKET: {
		...
        neighborTable->update(neighborRecord);
        break;
    }
```

If receive **GEO_BEACON_PACKET**, the node found a neighbor and update the neighborTable. If the packet is **GEO_ROUTING_PACKET**, the node decide to forward or drop it.

```Cpp
if ((destination.compare(SELF_NETWORK_ADDRESS) == 0)) {
    toApplicationLayer(routingPacket->decapsulate());
}
else {
    forwardDataPacket(routingPacket);
}
```

#### GeoRoutingControl
#### GeoPacket.msg
#### GeoBeaconPacket
#### GeoRoutingPacket
#### protocol

##### GeoProtocolHelper

Export **getGeoProtocol** function to select protocol use in simulation test. See [GeoRouting::startup](#georouting-startup).

##### GeoProtocol

Virtual class to create new geo routing protocol. GeoProtocol has 2 interface (may extend in future):

###### GeoProtocol::createGeoRoutingPacket()

Create new **GeoRoutingPacket**, which contain information for geo routing. See [GeoRouting::fromApplicationLayer](#fromapplicationlayer).

###### GeoProtocol::findNextHop()

Virtual interface to find next hop. See [GeoRouting::forwardDataPacket](#forwarddatapacket)
Default GeoProtocol::findNextHop() implemented Greedy Protocol.

##### NeighborTable
##### NeighborRecord
##### GeoHelper

## 4. Adding new GeoProtocol <a name="adding-new-geoprotocol"></a>

To create new geo routing protocol, you need create a class inherit from GeoProtocol class and your own routing message inherit from GeoRoutingPacket.

In your own geo routing protocol, you have to override two virtual interface **findNextHop** and **createGeoRoutingPacket**.

```Cpp
std::tuple<int, GeoRoutingPacket*> GeoProtocol::findNextHop(GeoRouting *routing, GeoRoutingPacket* pkt) {};

GeoRoutingPacket* GeoProtocol::createGeoRoutingPacket(GeoRouting *routing) {};
```

When you have your own protocol, you need add a switch case into **GeoProtocolHelper** to **RoutingTest** application know your protocol.

```Cpp
if (protocolType.compare(_GPSR_) == 0) {
    GPSR* gpsr = new GPSR();
    gpsr->setProtocolMode(protocolMode);
    return gpsr;
}
else {
    return new GeoProtocol();
}
```

Then, you can reconfig file **omnetpp.ini** to use your new protocol.

## 5. GPSR example <a name="gpsr-example"></a>

### GPSR protocol

```Cpp
GeoRoutingPacket* GPSR::createGeoRoutingPacket(GeoRouting *routing) {
	return new GPSRPacket("GPSR routing data packet", NETWORK_LAYER_PACKET);
}
```

```Cpp
std::tuple<int, GeoRoutingPacket*> GPSR::findNextHop(GeoRouting *routing, GeoRoutingPacket* pkt) {
	GPSRPacket *dataPacket = dynamic_cast <GPSRPacket*>(pkt->dup());
	int nextHop = -1;
    switch (dataPacket->getRoutingMode()) {
        case GPSR_GREEDY_ROUTING: {
			nextHop = findGreedyRoutingNextHop(routing, dataPacket);
			break;
		}
        case GPSR_PERIMETER_ROUTING: {
			nextHop = findPerimeterRoutingNextHop(routing, dataPacket);
			break;
		}
        default: break;
    }
	return std::make_tuple(nextHop, dataPacket);
}
```

### GPSRPacket

```Cpp
packet GPSRPacket extends GeoRoutingPacket {
    int routingMode = GPSR_GREEDY_ROUTING;		// M
	NodeLocation_type destinationLocation;		// D
	NodeLocation_type startPerimeterLocation;	// Lp
	NodeLocation_type forwardPerimeterLocation;	// Lf
	string firstSenderAddress;					// e0
	string firstReceiverAddress;				// e0
	string senderAddress;
}
```

### GeoProtocolHelper

```Cpp
if (protocolType.compare(_GPSR_) == 0) {
    GPSR* gpsr = new GPSR();
    gpsr->setProtocolMode(protocolMode);
    return gpsr;
}
else {
    return new GeoProtocol();
}
```

## 6. References <a name="references"></a>

1. [Castalia](https://github.com/boulis/Castalia)
2. [GPSR Routing Protocol, University of Pau, France, LIUPPA Laboratory, T2I Team](https://groups.google.com/forum/#!topic/castalia-simulator/fE3H83v1kkw)
3. [Wireless Sensor Network Simulations Using Castalia and a Data-Centric Storage Case Study](https://www.thesisscientist.com/docs/AnnaWills/5621d417-37b0-45cb-8302-d04284214f9d.pdf)

## 7. License <a name="license"></a>

Code licensed under the MIT License.