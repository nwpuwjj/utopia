/*
 * If not stated otherwise in this file or this component's Licenses.txt file the
 * following copyright and licenses apply:
 *
 * Copyright 2015 RDK Management
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
*/

/**********************************************************************
   Copyright [2014] [Cisco Systems, Inc.]
 
   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at
 
       http://www.apache.org/licenses/LICENSE-2.0
 
   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
**********************************************************************/

/*
 * Copyright (c) 2010 by Cisco Systems, Inc. All Rights Reserved.
 *
 * This work is subject to U.S. and international copyright laws and
 * treaties. No part of this work may be used, practiced, performed,
 * copied, distributed, revised, modified, translated, abridged, condensed,
 * expanded, collected, compiled, linked, recast, transformed or adapted
 * without the prior written consent of Cisco Systems, Inc. Any use or
 * exploitation of this work without authorization could subject the
 * perpetrator to criminal and civil liability.
 */
#include <stdio.h>
#include <stdlib.h>
#include "srvmgr.h"

const char* SERVICE_NAME            = "dhcp_server";
const char* SERVICE_DEFAULT_HANDLER = "/etc/utopia/service.d/service_dhcp_server.sh";
#if defined(_COSA_INTEL_USG_ARM_) && !defined(INTEL_PUMA7) && !defined(_COSA_BCM_ARM_)
const char* SERVICE_CUSTOM_EVENTS[] = { 
                                        "syslog-status|/etc/utopia/service.d/service_dhcp_server.sh",
                                        "lan-status|/usr/bin/service_dhcp",
										"dhcp_server-restart|/usr/bin/service_dhcp",
                                        "dhcp_server-start|/usr/bin/service_dhcp",
                                        "dhcp_server-stop|/usr/bin/service_dhcp",
                                        "dhcp_server-resync|/etc/utopia/service.d/service_dhcp_server.sh|NULL|"TUPLE_FLAG_EVENT,
                                        NULL 
                                      };
#else
const char* SERVICE_CUSTOM_EVENTS[] = { 
                                        "syslog-status|/etc/utopia/service.d/service_dhcp_server.sh",
                                        "lan-status|/etc/utopia/service.d/service_dhcp_server.sh",
                                        "dhcp_server-resync|/etc/utopia/service.d/service_dhcp_server.sh|NULL|"TUPLE_FLAG_EVENT,
                                        NULL 
                                      };
#endif

void srv_register(void) {
   DBG_PRINT("15_dhcp_server : %s Entry\n", __FUNCTION__);
   sm_register(SERVICE_NAME, SERVICE_DEFAULT_HANDLER, SERVICE_CUSTOM_EVENTS);
   system ("/etc/utopia/service.d/pmon.sh register dhcp_server");
   DBG_PRINT("15_dhcp_server : %s Exit\n", __FUNCTION__);
}

void srv_unregister(void) {
	DBG_PRINT("15_dhcp_server : %s Entry\n", __FUNCTION__);
   system ("/etc/utopia/service.d/pmon.sh unregister dhcp_server");
   sm_unregister(SERVICE_NAME);
   DBG_PRINT("15_dhcp_server : %s Exit\n", __FUNCTION__);
}

int main(int argc, char **argv)
{
	DBG_PRINT("15_dhcp_server : %s Entry\n", __FUNCTION__);

   cmd_type_t choice = parse_cmd_line(argc, argv);

   switch(choice) {
      case(nochoice):
      case(start):
         srv_register();
         break;
      case(stop):
         srv_unregister();
         break;
      case(restart):
         srv_unregister();
         srv_register();
         break;
      default:
         DBG_PRINT("%s called with invalid parameter (%s)\n", argv[0], 1==argc ? "" : argv[1]);
   }

   DBG_PRINT("15_dhcp_server : %s Exit\n", __FUNCTION__);
   
   return(0);
}
