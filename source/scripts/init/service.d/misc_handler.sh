#! /bin/sh
##########################################################################
# If not stated otherwise in this file or this component's Licenses.txt
# file the following copyright and licenses apply:
#
# Copyright 2015 RDK Management
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
##########################################################################

#######################################################################
#   Copyright [2014] [Cisco Systems, Inc.]
# 
#   Licensed under the Apache License, Version 2.0 (the \"License\");
#   you may not use this file except in compliance with the License.
#   You may obtain a copy of the License at
# 
#       http://www.apache.org/licenses/LICENSE-2.0
# 
#   Unless required by applicable law or agreed to in writing, software
#   distributed under the License is distributed on an \"AS IS\" BASIS,
#   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#   See the License for the specific language governing permissions and
#   limitations under the License.
#######################################################################

UPTIME=`cat /proc/uptime  | awk '{print $1}' | awk -F '.' '{print $1}'`
UTOPIA_PATH="/etc/utopia/service.d"
source $UTOPIA_PATH/log_env_var.sh
source /etc/utopia/service.d/ut_plat.sh

if [ "$UPTIME" -lt 600 ]
then
    exit 0
fi
LAN_WAN_READY=`sysevent get start-misc`
if [ "$LAN_WAN_READY" != "ready" ]
then

    echo "[`date +'%Y-%m-%d:%H:%M:%S:%6N'`] RDKB_SELFHEAL : RDKB Firewall Recovery" >> $SELFHEALFILE

    ipaddr=`sysevent get current_lan_ipaddr`
    index=4
    if [ x$ipaddr = x ]
    then
        echo " Current IP address is NULL "
	eval `psmcli get -e CUR_IPV4ADDR ${IPV4_NV_PREFIX}.$index.${IPV4_NV_IP}`
	if [ x$CUR_IPV4ADDR != x ]
	then
	    sysevent set current_lan_ipaddr $CUR_IPV4ADDR
	else
	    sysevent set current_lan_ipaddr `syscfg get lan_ipaddr`
	fi
    fi

#    gw_lan_refresh &
    firewall
    execute_dir /etc/utopia/post.d/ restart

    sysevent set start-misc ready	
    sysevent set misc-ready-from-mischandler true

    STARTED_FLG=`sysevent get parcon_nfq_status`

    if [ x"$STARTED_FLG" != x"started" ]; then
        BRLAN0_MAC=`ifconfig l2sd0 | grep HWaddr | awk '{print $5}'`
        ((nfq_handler 4 $BRLAN0_MAC &)&)
        ((nfq_handler 6 $BRLAN0_MAC &)&)
        sysevent set parcon_nfq_status started
    fi

    rm /etc/cron/cron.everyminute/misc_handler.sh
else
    RG_MD=`syscfg get last_erouter_mode`
    MLD_PID=`pidof mldproxy`
    IGMP_PID=`pidof igmpproxy`

    if [ "$IGMP_PID" = "" ]; then
      if [ "$RG_MD" = "1" -o "$RG_MD" = "3" ]; then
    	/etc/utopia/service.d/service_mcastproxy.sh lan-status&
      fi
    fi

    if [ "$MLD_PID" = "" ]; then
      if [ "$RG_MD" = "2" -o "$RG_MD" = "3" ]; then
    	/etc/utopia/service.d/service_mldproxy.sh lan-status&
      fi
    fi

    rm /etc/cron/cron.everyminute/misc_handler.sh
fi
