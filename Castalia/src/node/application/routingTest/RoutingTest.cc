/****************************************************************************
 *  Copyright: National ICT Australia,  2007 - 2011                         *
 *  Developed at the ATP lab, Networked Systems research theme              *
 *  Author(s): Athanassios Boulis, Yuriy Tselishchev                        *
 *  This file is distributed under the terms in the attached LICENSE file.  *
 *  If you do not find this file, copies can be found by writing to:        *
 *                                                                          *
 *      NICTA, Locked Bag 9013, Alexandria, NSW 1435, Australia             *
 *      Attention:  License Inquiry.                                        *
 *                                                                          *
 ****************************************************************************/

#include "RoutingTest.h"

#include "GeoRoutingControl_m.h"

Define_Module(RoutingTest);

void RoutingTest::startup()
{
	packet_rate = par("packet_rate");
	recipientAddress = par("nextRecipient").stringValue();
	startupDelay = par("startupDelay");

	packet_spacing = packet_rate > 0 ? 1 / float (packet_rate) : -1;
	dataSN = 0;

	// set the node's coordinate, this will also trigger HELLO msg from the GPSR routing layer
	NodeLocation_type nodeLocation;

	nodeLocation=mobilityModule->getLocation();

	trace() << "Node " << self << " has position (" << nodeLocation.x << "," << nodeLocation.y << ")" << endl;

	// set the node's position for the routing layer 
	GeoRoutingControl *cmd1 = new GeoRoutingControl("GEO set node pos", NETWORK_CONTROL_COMMAND);
	cmd1->setGeoRoutingCommand(SET_GEO_NODE_POS);
	cmd1->setNodeLocation(nodeLocation);
	toNetworkLayer(cmd1);
		
	if (packet_spacing > 0 && recipientAddress.compare(SELF_NETWORK_ADDRESS) != 0) {
		//
		setTimer(SEND_PACKET, packet_spacing + startupDelay);
	}
	else
		trace() << "Not sending packets";
	
	declareOutput("Packets received per node");
}

void RoutingTest::fromNetworkLayer(ApplicationPacket * rcvPacket,
		const char *source, double rssi, double lqi)
{
	int sequenceNumber = rcvPacket->getSequenceNumber();

	trace() << "Received packet #" << sequenceNumber << " from node " << source;
	collectOutput("Packets received per node", atoi(source));
}

void RoutingTest::timerFiredCallback(int index)
{
	switch (index) {
		case SEND_PACKET:{
			trace() << "Sending packet #" << dataSN;
			
			recipientAddress = par("nextRecipient").stringValue();
			
			NodeLocation_type nodeLocation;
			VirtualMobilityManager *sinkMobilityModule;
			sinkMobilityModule = check_and_cast <VirtualMobilityManager*>(getParentModule()->getParentModule()->getSubmodule("node",atoi(recipientAddress.c_str()))->getSubmodule("MobilityManager"));		
			nodeLocation=sinkMobilityModule->getLocation();
			
			GeoApplicationPacket *newPacket = new GeoApplicationPacket("Geo Application packet", APPLICATION_PACKET);
			newPacket->setSequenceNumber(dataSN);
			newPacket->setDestinationLocation(nodeLocation);
			toNetworkLayer(newPacket, par("nextRecipient"));
			dataSN++;
			// setTimer(SEND_PACKET, packet_spacing);
			break;
		}
	}
}

// This method processes a received carrier sense interupt. Used only for demo purposes
// in some simulations. Feel free to comment out the trace command.
void RoutingTest::handleRadioControlMessage(RadioControlMessage *radioMsg)
{
	switch (radioMsg->getRadioControlMessageKind()) {
		case CARRIER_SENSE_INTERRUPT:
			trace() << "CS Interrupt received! current RSSI value is: " << radioModule->readRSSI();
                        break;
	}
}

