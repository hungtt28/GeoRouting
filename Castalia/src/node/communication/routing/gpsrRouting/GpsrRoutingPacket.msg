//*********************************************************/
//*  Copyright (c) 2011. University of Pau, France        */
//*  LIUPPA Laboratory, T2I Team                          */
//*                                                       */
//*  Permission to use, copy, modify and distribute this  */
//*  code, without fee, and without written agreement is  */
//*  hereby granted, provided that the above copyright    */
//*  notice and the authors appear in all copies          */
//*                                                       */
//*  GPSR Routing Protocol                                */
//*  Version:  1.0                                        */
//*  Authors: Diop Mamour <serignemamour.diop@gmail.com>  */
//*           Congduc Pham <congduc.pham@univ-pau.fr>     */
//*********************************************************/

cplusplus {{
#include "RoutingPacket_m.h"
}}

class RoutingPacket;

enum GpsrPacketDef {

    GPSR_DATA_PACKET             =   0;       // data packet
    GPSR_HELLO_MSG_PACKET        =   1;      // hello msg
    GPSR_REP_HELLO_MSG_PACKET    =   2;     // rep hello msg 
    GPSR_SINK_ADDRESS_PACKET     =   3;    // sink address
}; 

packet GpsrPacket extends RoutingPacket {
    int GpsrPacketKind enum (GpsrPacketDef);
    int x_src; 
    int y_src;
	int x_dst;	// for the sink when it is a data message
	int y_dst; 
}



