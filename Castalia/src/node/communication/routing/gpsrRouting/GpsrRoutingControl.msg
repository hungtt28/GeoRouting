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

enum GpsrRoutingCommandDef {
	SET_GPSR_NODE_POS = 1;
	SET_GPSR_SINK_POS = 2;
	SET_GPSR_BOOL = 3; // for future usage
}

message GpsrRoutingControlCommand {
	int gpsrRoutingCommandKind enum (GpsrRoutingCommandDef);
	double double1 = 0;
	double double2 = 0;
	int int1 = 0;
	int int2 = 0;
	bool bool1 = false; // for future usage
}

