#!/bin/sh
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


#------------------------------------------------------------------
# Copyright (c) 2013 by Cisco Systems, Inc. All Rights Reserved.
#
# This work is subject to U.S. and international copyright laws and
# treaties. No part of this work may be used, practiced, performed,
# copied, distributed, revised, modified, translated, abridged, condensed,
# expanded, collected, compiled, linked, recast, transformed or adapted
# without the prior written consent of Cisco Systems, Inc. Any use or
# exploitation of this work without authorization could subject the
# perpetrator to criminal and civil liability.
#------------------------------------------------------------------


#------------------------------------------------------------------
# ENTRY
#------------------------------------------------------------------

TYPE=Gre

GRE_IFNAME="gretap0"
GRE_IFNAME_DUMMY="gretap_0"

source /etc/utopia/service.d/ut_plat.sh
source /etc/utopia/service.d/log_capture_path.sh
THIS=/etc/utopia/service.d/service_multinet/handle_gre.sh

export LOG4C_RCPATH=/fss/gw/rdklogger
BINPATH=/fss/gw/usr/ccsp

MTU_VAL=1400
MSS_VAL=1360

GRE_PSM_BASE=dmsb.cisco.gre
#HS_PSM_BASE=dmsb.hotspot.gre
HS_PSM_BASE=dmsb.hotspot.tunnel
GRE_PSM_NAME=name
#format for below is comma delimited FQDM
GRE_PSM_BRIDGES=AssociatedBridges 
#GRE_PSM_KAINT=KeepAlive.Interval
GRE_PSM_KAINT=RemoteEndpointHealthCheckPingInterval
#GRE_PSM_KAFINT=KeepAlive.FailInterval
GRE_PSM_KAFINT=RemoteEndpointHealthCheckPingIntervalInFailure
#GRE_PSM_KARECON=ReconnPrimary
GRE_PSM_KARECON=ReconnectToPrimaryRemoteEndpoint
#GRE_PSM_KATHRESH=KeepAlive.Threshold
GRE_PSM_KATHRESH=RemoteEndpointHealthCheckPingFailThreshold
#GRE_PSM_KAPOLICY=KeepAlive.Policy
GRE_PSM_KAPOLICY=KeepAlivePolicy
GRE_PSM_TOS=tos
GRE_PSM_KEY=key
GRE_PSM_CSUM=csumenabled
GRE_PSM_SEQ=seqnumenabled
#GRE_PSM_ENDPOINTS=Endpoints 
GRE_PSM_PRIENDPOINTS=PrimaryRemoteEndpoint
GRE_PSM_SECENDPOINTS=SecondaryRemoteEndpoint
GRE_PSM_ENDPOINT=endpoint
#GRE_PSM_KACOUNT=KeepAlive.Count
GRE_PSM_KACOUNT=RemoteEndpointHealthCheckPingCount
#GRE_PSM_SNOOPCIRC=DHCP.CircuitIDSSID
GRE_PSM_SNOOPCIRC=EnableCircuitID
#GRE_PSM_SNOOPREM=DHCP.RemoteID
GRE_PSM_SNOOPREM=EnableRemoteID
GRE_PSM_ENABLE=enable
HS_PSM_ENABLE=Enable
GRE_PSM_LOCALIFS=LocalInterfaces   
WIFI_PSM_PREFIX=eRT.com.cisco.spvtg.ccsp.Device.WiFi.Radio.SSID
WIFI_RADIO_INDEX=RadioIndex

GRE_ARP_PROC=hotspot_arpd
HOTSPOT_COMP=CcspHotspot
ARP_NFQUEUE=0

WAN_IF=erouter0

AB_SSID_DELIM=':'
AB_DELIM=","

BASEQUEUE=1

init_snooper_sysevents () {
    if [ x1 = x$SNOOP_CIRCUIT ]; then
        sysevent set snooper-circuit-enable 1
    else
        sysevent set snooper-circuit-enable 0
    fi
    
    if [ x1 = x$SNOOP_REMOTE ]; then
        sysevent set snooper-remote-enable 1
    else
        sysevent set snooper-remote-enable 0
    fi
}

#args: remote endpoint, gre tunnel ifname
create_tunnel () {
    echo "Creating tunnel... remote:$1"
    
    read_tunnel_params $2
    
    local extra=""
    if [ x1 = x$CSUM ]; then
        extra="csum"
    fi
    
    if [ x != x$KEY ]; then
        extra="$extra key $KEY"
    fi
    
    if [ x != x$TOS ]; then
        extra="$extra dsfield $TOS"
    fi
    
    # TODO: sequence number
    
    # TODO: use assigned lower layer instead
    WAN_IF=`sysevent get current_wan_ifname`
    
    update_bridge_frag_config $inst $1
    
    isgretap0Present=`ip link show | grep gretap0`
    if [ "$isgretap0Present" != "" ]; then
        echo "gretap0 is already present rename it before creating"
        ip link set dev $GRE_IFNAME name $GRE_IFNAME_DUMMY
    fi

    ip link add $2 type gretap remote $1 dev $WAN_IF $extra
    sysevent set gre_current_endpoint $1
    sysevent set if_${2}-status $IF_READY
    
}

destroy_tunnel () {
    echo "Destroying tunnel... remote"
    #kill `sysevent get dhcpsnoopd_pid`
    ip link del $1
    sysevent set gre_current_endpoint
    #sysevent set dhcpsnoopd_pid
    #sysevent set snooper-log-enable 0
    sysevent set if_${1}-status $IF_DOWN
}

gre_preproc () {
    #zqiu: fix for XHH 5G not get IP issue
    #if [ -f $UTOPIAROOT/hhs_validate.sh ]; then
    #    $UTOPIAROOT/hhs_validate.sh
    #fi
    allGreInst="`psmcli getallinst $GRE_PSM_BASE.`"
    query=""
    
    # TODO break 1 to 1 dependence on instance numbers (hotspot and gre interface)
    for i in $allGreInst; do 
        query="$query GRE_$i $GRE_PSM_BASE.$i.$GRE_PSM_NAME"
    done
    
    eval `psmcli get -e $query`
    
    for i in $allGreInst; do
        eval sysevent set gre_\${GRE_${i}}_inst $i
    done
}

init_keepalive_sysevents () {
    keepalive_args="-n `sysevent get wan_ifname`"
    #PRIMARY=`echo $ENDPOINTS | cut -f 1 -d ","`
    #SECONDARY=`echo $ENDPOINTS | cut -f 2 -d "," -s`
    if [ x = x`sysevent get hotspotfd-primary` ]; then
        sysevent set hotspotfd-primary $PRIMARY
    fi
    
    if [ x = x`sysevent get hotspotfd-secondary` ]; then
        sysevent set hotspotfd-secondary $SECONDARY
    fi
    
    if [ x = x`sysevent get hotspotfd-threshold` ]; then
        sysevent set hotspotfd-threshold $KA_THRESH
    fi
    
    if [ x = x`sysevent get hotspotfd-keep-alive` ]; then
        sysevent set hotspotfd-keep-alive $KA_INTERVAL
    fi
    
    if [ x = x`sysevent get hotspotfd-max-secondary` ]; then
        sysevent set hotspotfd-max-secondary $KA_RECON_PRIM
    fi
    
    if [ x = x`sysevent get hotspotfd-policy` ]; then
        sysevent set hotspotfd-policy $KA_POLICY
    fi
    
    if [ x = x`sysevent get hotspotfd-count` ]; then
        sysevent set hotspotfd-count $KA_COUNT
    fi
    
    if [ x = x`sysevent get hotspotfd-dead-interval` ]; then
        sysevent set hotspotfd-dead-interval $KA_FAIL_INTERVAL
    fi
    
    if [ x"started" = x`sysevent get wan-status` ]; then
        sysevent set hotspotfd-enable 1
        keepalive_args="$keepalive_args -e 1"
    else
        sysevent set hotspotfd-enable 0
    fi

    ##Disable the keepalive until we see an associated client
    #sysevent set hotspotfd-enable 0
    
    sysevent set hotspotfd-log-enable 1
    
}

bInst_to_bNames () {
    BRIDGES=""
    local binst=""
    local query=""
    local num=0
    local num2=0
    OLD_IFS="$IFS"
    
    IFS="$AB_SSID_DELIM"
    for x in $2; do 
        num=`expr $num + 1`
        IFS="$AB_DELIM"
        for i in $x; do
            num2=`expr $num2 + 1`
#            binst=`echo $i |cut -d . -f 4`
            query="$query WECBB_${num}_${num2} $NET_IDS_DM.$i.$NET_IFNAME"
            eval WECBB_${num}=\"\${WECBB_${num}} \"\'\$WECBB_\'${num}'_'${num2}
        done
        IFS="$AB_SSID_DELIM"
#        eval BRIDGE_$num=\$AB_SSID_DELIM
    done
    
    num=0
    IFS="$AB_DELIM"
    for i in $1; do
        num=`expr $num + 1`
        binst=`echo $i |cut -d . -f 4`
        query="$query BRIDGE_$num $NET_IDS_DM.$binst.$NET_IFNAME"
    done
    IFS="$OLD_IFS"
    
    if [ x != x"$query" ]; then
        eval `eval psmcli get -e $query`
    fi
    
    
    for i in `seq $num`; do
        eval eval BRIDGES=\\\"\\\$BRIDGES \${BRIDGE_${i}} \${WECBB_${i}} \\\$AB_SSID_DELIM \\\"
    done
}

read_init_params () {
    gre_preproc
    #zqiu: short term fix for XHH 5G not get IP issue
    inst=`dmcli eRT setv Device.Bridging.Bridge.4.Port.2.LowerLayers string Device.WiFi.SSID.6`;
    
    inst=`sysevent get gre_$1_inst`
    #eval `psmcli get -e ENDPOINTS $HS_PSM_BASE.${inst}.$GRE_PSM_ENDPOINTS BRIDGE_INSTS $HS_PSM_BASE.${inst}.$GRE_PSM_BRIDGES  KA_INTERVAL $HS_PSM_BASE.${inst}.$GRE_PSM_KAINT KA_FAIL_INTERVAL $HS_PSM_BASE.${inst}.$GRE_PSM_KAFINT KA_POLICY $HS_PSM_BASE.${inst}.$GRE_PSM_KAPOLICY KA_THRESH $HS_PSM_BASE.${inst}.$GRE_PSM_KATHRESH KA_COUNT $HS_PSM_BASE.${inst}.$GRE_PSM_KACOUNT KA_RECON_PRIM $HS_PSM_BASE.${inst}.$GRE_PSM_KARECON SNOOP_CIRCUIT $HS_PSM_BASE.${inst}.$GRE_PSM_SNOOPCIRC SNOOP_REMOTE $HS_PSM_BASE.${inst}.$GRE_PSM_SNOOPREM WECB_BRIDGES dmsb.wecb.hhs_extra_bridges`
    eval `psmcli get -e PRIMARY $HS_PSM_BASE.${inst}.$GRE_PSM_PRIENDPOINTS SECONDARY $HS_PSM_BASE.${inst}.$GRE_PSM_SECENDPOINTS BRIDGE_INST_1 $HS_PSM_BASE.${inst}.interface.1.$GRE_PSM_BRIDGES BRIDGE_INST_2 $HS_PSM_BASE.${inst}.interface.2.$GRE_PSM_BRIDGES BRIDGE_INST_3 $HS_PSM_BASE.${inst}.interface.3.$GRE_PSM_BRIDGES BRIDGE_INST_4 $HS_PSM_BASE.${inst}.interface.4.$GRE_PSM_BRIDGES KA_INTERVAL $HS_PSM_BASE.${inst}.$GRE_PSM_KAINT KA_FAIL_INTERVAL $HS_PSM_BASE.${inst}.$GRE_PSM_KAFINT KA_POLICY $HS_PSM_BASE.${inst}.$GRE_PSM_KAPOLICY KA_THRESH $HS_PSM_BASE.${inst}.$GRE_PSM_KATHRESH KA_COUNT $HS_PSM_BASE.${inst}.$GRE_PSM_KACOUNT KA_RECON_PRIM $HS_PSM_BASE.${inst}.$GRE_PSM_KARECON SNOOP_CIRCUIT $HS_PSM_BASE.${inst}.$GRE_PSM_SNOOPCIRC SNOOP_REMOTE $HS_PSM_BASE.${inst}.$GRE_PSM_SNOOPREM WECB_BRIDGES dmsb.wecb.hhs_extra_bridges`
  BRIDGE_INSTS="$BRIDGE_INST_1,$BRIDGE_INST_2,$BRIDGE_INST_3,$BRIDGE_INST_4"
		
    bInst_to_bNames "$BRIDGE_INSTS" "$WECB_BRIDGES"
}

read_tunnel_params () {
    inst=`sysevent get gre_$1_inst`
    eval `psmcli get -e KEY $GRE_PSM_BASE.${inst}.$GRE_PSM_KEY CSUM $GRE_PSM_BASE.${inst}.$GRE_PSM_CSUM TOS $GRE_PSM_BASE.${inst}.$GRE_PSM_TOS`
}

#args: gre ifname
update_bridge_config () {
    inst=`sysevent get gre_$1_inst`
    curBridges="`sysevent get gre_${inst}_current_bridges`"
    
    if [ x != x"$curBridges" ]; then
        remove_bridge_config ${inst} "$curBridges"
    fi
    
    queue=$BASEQUEUE
    
    for br in $BRIDGES; do
        if [ "$AB_SSID_DELIM" = $br ]; then
            queue=`expr $queue + 1`
            continue
        fi
        br_snoop_rule="`sysevent setunique GeneralPurposeFirewallRule " -A FORWARD -o $br -p udp --dport=67:68 -j NFQUEUE --queue-bypass --queue-num $queue"`"
        sysevent set gre_${inst}_${br}_snoop_rule "$br_snoop_rule"
        
        
        br_mss_rule=`sysevent setunique GeneralPurposeMangleRule " -A POSTROUTING -o $br -p tcp --tcp-flags SYN,RST SYN -j TCPMSS --set-mss $MTU_VAL"`
        sysevent set gre_${inst}_${br}_mss_rule "$br_mss_rule"
    done
    
    sysevent set gre_${inst}_current_bridges "$BRIDGES"
    
}
# TODO: verify indexes and proper teardown
#args gre ifname, "bridge list"
remove_bridge_config () {
        for br in $2; do
            if [ "$AB_SSID_DELIM" = $br ]; then
                continue
            fi
            sysevent set `sysevent get gre_${1}_${br}_snoop_rule`
            sysevent set `sysevent get gre_${1}_${br}_mss_rule`
        done
}

#args: gre inst, gw ip
update_bridge_frag_config () {

    BRIDGES="`sysevent get gre_${1}_current_bridges`"
    for br in $BRIDGES; do
        if [ "$AB_SSID_DELIM" = $br ]; then
            continue
        fi
        echo add br=$br mtu=$MTU_VAL icmp=y segment=y gw=$2 > /proc/net/mtu_mod
    done
}

#args: gre instance
#out: $ssids - ssid instances
#       $radios - radio instances
#       $ssid_${instance}_radio - radio for the specified ssid
get_ssids() {
    #localifs=`psmcli get $HS_PSM_BASE.${1}.$GRE_PSM_LOCALIFS`		
	localif_1=`psmcli get $HS_PSM_BASE.${1}.interface.1.$GRE_PSM_LOCALIFS`		
	localif_2=`psmcli get $HS_PSM_BASE.${1}.interface.2.$GRE_PSM_LOCALIFS`	
	localif_3=Device.WiFi.SSID.9.
	localif_4=Device.WiFi.SSID.10.
	localifs="$localif_1,$localif_2,$localif_3,$localif_4";
    OLD_IFS="$IFS"
    IFS=","
    for i in $localifs; do
        winst=`echo $i |cut -d . -f 4`
        ssids="$ssids $winst"
        #zqiu: Radio instance number should be get from the DML, instead of real radio id in bbhm +1
		#radio=$(( `psmcli get $WIFI_PSM_PREFIX.${winst}.${WIFI_RADIO_INDEX}` + 1 ))
        radio=`dmcli eRT getv ${i}LowerLayers  | grep string,  | awk '{print $5}' | cut -d . -f 4 `
        expr match "$radios" '.*\b\('$radio'\)\b.*' > /dev/null
        if [ 0 != $? ]; then
            #add this radio instance
            radios="$radios $radio"
            eval mask_$radio=0
        fi
        eval ssid_${winst}_radio=$radio
        
    done
    IFS="$OLD_IFS"
}

#args: gre instance, true | false
#bring_down_ssids () {
set_ssids_enabled() {
    #delay SSID manipulation if requested
    sleep `sysevent get hotspot_$1-delay` 2> /dev/null
    sysevent set hotspot_$1-delay 0
    
    get_ssids $1
    for instance in $ssids; do
       $BINPATH/ccsp_bus_client_tool eRT setv Device.WiFi.SSID.${instance}.X_CISCO_COM_RouterEnabled bool $2 &
       $BINPATH/ccsp_bus_client_tool eRT setv Device.WiFi.SSID.${instance}.X_CISCO_COM_EnableOnline bool true &
        eval eval mask=\\\${mask_\${ssid_${instance}_radio}}
        eval eval mask_\${ssid_${instance}_radio}=$(( (2 ** ($instance - 1)) + $mask )) 
    done
    for rad in $radios; do
        eval $BINPATH/ccsp_bus_client_tool eRT setv Device.WiFi.Radio.$rad.X_CISCO_COM_ApplySettingSSID int \${mask_${rad}}
        $BINPATH/ccsp_bus_client_tool eRT setv Device.WiFi.Radio.$rad.X_CISCO_COM_ApplySetting bool true &
    done
    
    sysevent set hotspot_ssids_up $2
}

# NOTE: Hard coded solution
set_apisolation() {
    get_ssids $1
    for instance in $ssids; do
        $BINPATH/ccsp_bus_client_tool eRT setv Device.WiFi.AccessPoint.$instance.IsolationEnable bool true
    done
}

#args: "wifi instances"
kick_clients () {
    get_ssids $1
    for instance in $ssids; do
        $BINPATH/ccsp_bus_client_tool eRT setv Device.WiFi.AccessPoint.${instance}.X_CISCO_COM_KickAssocDevices bool true &
    done
}
#args: hotspot instance
kill_procs () {
#     kill `sysevent get ${1}_keepalive_pid`
#     sysevent set ${1}_keepalive_pid
#     
#     kill `sysevent get dhcpsnoopd_pid`
#     sysevent set dhcpsnoopd_pid
# TODO: develop scheme for only killing related pids. background task var $1 doesn't work as these processes daemonize
    killall $HOTSPOT_COMP
    sysevent set ${1}_keepalive_pid
    killall $GRE_ARP_PROC
    
}
#args: hotspot instance
hotspot_down() {

    inst=$1
    
    #Set a delay for SSID manipulation
    sysevent set hotspot_${inst}-delay 10
    
    sysevent rm_async `sysevent get gre_wan_async`
    sysevent rm_async `sysevent get gre_ep_async`
#    sysevent rm_async `sysevent get gre_snooper_clients_async`
    sysevent rm_async `sysevent get gre_primary_async`
    sysevent set gre_ep_async
    sysevent set gre_wan_async
#    sysevent set gre_snooper_clients_async
    sysevent get gre_primary_async
    
    #bridgeFQDM=`psmcli get $HS_PSM_BASE.${inst}.$GRE_PSM_BRIDGES`	
	BRIDGE_INST_1=`psmcli get $HS_PSM_BASE.${inst}.interface.1.$GRE_PSM_BRIDGES`
	BRIDGE_INST_2=`psmcli get $HS_PSM_BASE.${inst}.interface.2.$GRE_PSM_BRIDGES`
	BRIDGE_INST_3=`psmcli get $HS_PSM_BASE.${inst}.interface.3.$GRE_PSM_BRIDGES`
	BRIDGE_INST_4=`psmcli get $HS_PSM_BASE.${inst}.interface.4.$GRE_PSM_BRIDGES`
	
    bridgeFQDM="$BRIDGE_INST_1,$BRIDGE_INST_2,$BRIDGE_INST_3,$BRIDGE_INST_4"
	
    remove_bridge_config ${inst} "`sysevent get gre_${inst}_current_bridges`"

    brinst=""
    OLD_IFS="$IFS"
    IFS=","
    for i in $bridgeFQDM; do
        brinst=`echo $i |cut -d . -f 4`
        sysevent set multinet-down $brinst
    done
    IFS="$OLD_IFS"
    
    kill_procs $inst
    
    set_ssids_enabled $inst false
    
    sysevent set `sysevent get ${inst}_arp_queue_rule`
    sysevent set ${inst}_arp_queue_rule
    
    sysevent set hotspotfd-tunnelEP
    sysevent set snooper-wifi-clients
    
    sysevent set hotspot_${inst}-status stopped
    
    sysevent set hotspot_ssids_up
    sysevent set hotspot_${inst}-delay

}
#args: hotspot instance
hotspot_up() {
    inst=$1
    #eval `psmcli get -e bridgeFQDM $HS_PSM_BASE.${inst}.$GRE_PSM_BRIDGES ENABLED $HS_PSM_BASE.${inst}.$HS_PSM_ENABLE GRE_ENABLED $GRE_PSM_BASE.${inst}.$GRE_PSM_ENABLE WECB_BRIDGES dmsb.wecb.hhs_extra_bridges`
    eval `psmcli get -e BRIDGE_INST_1 $HS_PSM_BASE.${inst}.interface.1.$GRE_PSM_BRIDGES BRIDGE_INST_2 $HS_PSM_BASE.${inst}.interface.2.$GRE_PSM_BRIDGES BRIDGE_INST_3 $HS_PSM_BASE.${inst}.interface.3.$GRE_PSM_BRIDGES BRIDGE_INST_4 $HS_PSM_BASE.${inst}.interface.4.$GRE_PSM_BRIDGES ENABLED $HS_PSM_BASE.${inst}.$HS_PSM_ENABLE GRE_ENABLED $GRE_PSM_BASE.${inst}.$GRE_PSM_ENABLE WECB_BRIDGES dmsb.wecb.hhs_extra_bridges`
    bridgeFQDM="$BRIDGE_INST_1,$BRIDGE_INST_2,$BRIDGE_INST_3,$BRIDGE_INST_4"
	
    if [ x"1" != x$ENABLED -o x"1" != x$GRE_ENABLED ]; then
        exit 0
    fi
    
    #Set a delay for first SSID manipulation
    sysevent set hotspot_${inst}-delay 10

    #Hard code for old images
    set_apisolation $inst
    
    brinst=""
    OLD_IFS="$IFS"
    IFS="${AB_DELIM}${AB_SSID_DELIM}"
    for i in $bridgeFQDM; do
        brinst=`echo $i |cut -d . -f 4`
        sysevent set multinet-start $brinst
    done
    
    for i in $WECB_BRIDGES; do
        sysevent set multinet-start $i
    done
    
    sysevent set hotspot_${inst}-status started
    
    IFS="$OLD_IFS"
}

check_ssids () {
    EP="`sysevent get hotspotfd-tunnelEP`"
    WAN="`sysevent get wan-status`"
    curSSIDSTATE="`sysevent get hotspot_ssids_up`"
    
    if [ x = x$1 ]; then
            allGreInst="`psmcli getallinst $HS_PSM_BASE.`"
            inst=`echo $allGreInst | cut -f 1`
            if [ x = x$inst ]; then
                exit 0
            fi
    else
        inst=$1
    fi
    
    if [ x"started" = x$WAN -a x != x$EP -a x"0.0.0.0" != x$EP ]; then
        if [ x"true" = x$curSSIDSTATE ]; then
            kick_clients 1
        else
            set_ssids_enabled $inst true > /dev/null
        fi
    else
        #SSIDs should be down
        if [ x"true" = x$curSSIDSTATE ]; then
            set_ssids_enabled $inst false > /dev/null
        fi
    fi
}

#args: 
set_wecb_bridges() {
    # TODO: parameterize the instance number "1"
    #BRIDGE_INS="`psmcli get $HS_PSM_BASE.1.$GRE_PSM_BRIDGES`"	
    BRIDGE_INST_1="`psmcli get $HS_PSM_BASE.1.interface.1.$GRE_PSM_BRIDGES`"
	BRIDGE_INST_2="`psmcli get $HS_PSM_BASE.1.interface.2.$GRE_PSM_BRIDGES`"
	BRIDGE_INST_3="`psmcli get $HS_PSM_BASE.1.interface.3.$GRE_PSM_BRIDGES`"
	BRIDGE_INST_4="`psmcli get $HS_PSM_BASE.1.interface.4.$GRE_PSM_BRIDGES`"
	BRIDGE_INS="$BRIDGE_INST_1,$BRIDGE_INST_2,$BRIDGE_INST_3,$BRIDGE_INST_4"
	
    local binst=""
    local query=""
    local num=0
    OLD_IFS="$IFS"
    
    IFS="$AB_SSID_DELIM"
    for x in $BRIDGE_INS; do 
        IFS="$AB_DELIM"
        for i in $x; do
            if [ 0 = $num ]; then
                num=1
                continue
            fi
            binst=`echo $i |cut -d . -f 4`
            query="$query $binst"
        done
        num=0
    done
    IFS="$OLD_IFS"
    
    sysevent set wecb_hhs_bridges "$query"
}


#service_init
case "$1" in
#  Synchronous calls from bridge
    #Args: netid, members
    create)
        echo "GRE CREATE: $3" > /dev/console
        
        read_init_params $3 > /dev/null
        
        #Initialize
        if [ x = x`sysevent get ${inst}_keepalive_pid` ]; then
            echo "GRE INITIALIZING..." > /dev/console
            async="`sysevent async hotspotfd-tunnelEP $THIS`"
            sysevent set gre_ep_async "$async" > /dev/null
#             async="`sysevent async snooper-wifi-clients $THIS`"
#             sysevent set gre_snooper_clients_async "$async" > /dev/null
            async="`sysevent async wan-status $THIS`"
            sysevent set gre_wan_async "$async" > /dev/null
            async="`sysevent async hotspotfd-primary $THIS`"
            sysevent set gre_primary_async "$async" > /dev/null
            
            init_keepalive_sysevents > /dev/null
            init_snooper_sysevents
            sysevent set snooper-log-enable 1
            echo "Starting hotspot component" > /dev/console
            $HOTSPOT_COMP -subsys eRT. > /dev/null &
            sysevent set ${inst}_keepalive_pid $! > /dev/null
            
            update_bridge_config $3 > /dev/null
            
            arpFWrule=`sysevent setunique GeneralPurposeFirewallRule " -I OUTPUT -o $WAN_IF -p icmp --icmp-type 3 -j NFQUEUE --queue-bypass --queue-num $ARP_NFQUEUE"`
            sysevent set ${inst}_arp_queue_rule "$arpFWrule" > /dev/null
            $GRE_ARP_PROC -q $ARP_NFQUEUE  > /dev/null &
            echo "handle_gre : Triggering RDKB_FIREWALL_RESTART"
            sysevent set firewall-restart > /dev/null
            
            #check_ssids
            
        fi
    
        if [ x"up" = x`sysevent get if_${3}-status` ]; then 
            echo ${TYPE}_READY=\"$3\"
        else
            echo ${TYPE}_READY=\"\"
        fi
        
        ;;
    destroy)
        service_stop
        ;;
    #Args: netid, netvid, members
    addVlan)
 #     if [ x"unknown" != x"$SYSEVENT_current_hsd_mode" ]; then
        
 #     fi
      ;;
    #Args: netid, netvid, members
    delVlan)
    
    ;;
      
#  Sysevent calls
    hotspotfd-tunnelEP)
    
        echo "GRE EP called : $2"
        curep=`sysevent get gre_current_endpoint`
        if [ x != x$curep -a x$curep != x${2} ]; then
            destroy_tunnel $GRE_IFNAME
        fi
        
        if [ x"NULL" != x${2} ]; then
            create_tunnel $2 $GRE_IFNAME
        fi
        
        check_ssids 1
    
    ;;
    
    wan-status)
    # TODO make this multi-instance
        if [ x"started" = x${2} ]; then
            #clients=`sysevent get snooper-wifi-clients`
            #if [ x != x$clients -a x0 != x$clients ]; then
                sysevent set hotspotfd-enable 1
            #fi
            if [ x != x`sysevent get gre_current_endpoint` ]; then
                ifconfig $GRE_IFNAME up
                sysevent set if_${GRE_IFNAME}-status $IF_READY
            fi
        else
            sysevent set hotspotfd-enable 0
            ifconfig ${GRE_IFNAME} down
            sysevent set if_${GRE_IFNAME}-status $IF_DOWN
        fi
        check_ssids
    ;;
    
    snmp_subagent-status)
        #This is an entry point guaranteed to indicate the PSM is available.
        gre_preproc
        set_wecb_bridges
    ;;
    
    hotspot-start)
        
        if [ x"NULL" = x$2 ]; then
            allGreInst="`psmcli getallinst $HS_PSM_BASE.`"
            inst=`echo $allGreInst | cut -f 1`
            if [ x = x$inst ]; then
                exit 0
            fi
        else
            inst=$2
        fi
        
        hotspot_up $inst
    ;;
    
    hotspot-stop)
        if [ x"NULL" = x$2 ]; then
            allGreInst="`psmcli getallinst $HS_PSM_BASE.`"
            inst=`echo $allGreInst | cut -f 1`
            if [ x = x$inst ]; then
                exit 0
            fi
        else
            inst=$2
        fi
        
        hotspot_down $inst
    ;;
    
    hotspot-restart)
    
    ;;
    
    #args: hotspot gre instance
    gre-restart|gre-forceRestart)
        curr_tunnel=`sysevent get gre_current_endpoint`
        # NOTE: assuming 1-to-1, identical gre to hotspot instance mapping
        hotspot_started=`sysevent get hotspot_${2}-status`
#         if [ x = x$curr_tunnel ]; then
#             exit 0
#         fi
        set_wecb_bridges
		
		#eval `psmcli get -e bridgeFQDM $HS_PSM_BASE.${2}.$GRE_PSM_BRIDGES ENABLED $HS_PSM_BASE.${2}.$HS_PSM_ENABLE GRE_ENABLED $GRE_PSM_BASE.${2}.$GRE_PSM_ENABLE name $GRE_PSM_BASE.$2.$GRE_PSM_NAME`
        eval `psmcli get -e BRIDGE_INST_1 $HS_PSM_BASE.${2}.interface.1.$GRE_PSM_BRIDGES BRIDGE_INST_2 $HS_PSM_BASE.${2}.interface.2.$GRE_PSM_BRIDGES BRIDGE_INST_3 $HS_PSM_BASE.${2}.interface.3.$GRE_PSM_BRIDGES BRIDGE_INST_4 $HS_PSM_BASE.${2}.interface.4.$GRE_PSM_BRIDGES ENABLED $HS_PSM_BASE.${2}.$HS_PSM_ENABLE GRE_ENABLED $GRE_PSM_BASE.${2}.$GRE_PSM_ENABLE name $GRE_PSM_BASE.$2.$GRE_PSM_NAME`
        bridgeFQDM="$BRIDGE_INST_1,$BRIDGE_INST_2,$BRIDGE_INST_3,$BRIDGE_INST_4"
		
		if [ x != x$curr_tunnel ]; then
            destroy_tunnel $name
        fi
        
        if [ x"1" != x$ENABLED -o x"1" != x$GRE_ENABLED ]; then
            #Disabled
            if [ xstarted = x$hotspot_started ]; then
                hotspot_down $2
            fi
        else
            #Enabled
            if [ xstarted = x$hotspot_started ]; then
                if [ x != x$curr_tunnel ]; then
                    create_tunnel $curr_tunnel $name
                fi
                #if forceRestart is given, an apply settings is desired. Only set if ssids are already up.
                if [ gre-forceRestart = $1 -a x`sysevent get hotspot_ssids_up` = xtrue ]; then
                    set_ssids_enabled $2 true
                fi
            else
                hotspot_up $2
            fi
        fi
#         name=`psmcli get $GRE_PSM_BASE.$2.$GRE_PSM_NAME`
#         destroy_tunnel $name
#         create_tunnel $curr_tunnel $name
    ;;
    
    #args: hotspot gre instance
    hotspot-update_bridges)
		eval `psmcli get -e BRIDGE_INST_1 $HS_PSM_BASE.${2}.interface.1.$GRE_PSM_BRIDGES BRIDGE_INST_2 $HS_PSM_BASE.${2}.interface.2.$GRE_PSM_BRIDGES BRIDGE_INST_3 $HS_PSM_BASE.${2}.interface.3.$GRE_PSM_BRIDGES BRIDGE_INST_4 $HS_PSM_BASE.${2}.interface.4.$GRE_PSM_BRIDGES WECB_BRIDGES dmsb.wecb.hhs_extra_bridges NAME $GRE_PSM_BASE.$2.$GRE_PSM_NAME`
        BRIDGE_INSTS="$BRIDGE_INST_1,$BRIDGE_INST_2,$BRIDGE_INST_3,$BRIDGE_INST_4"
        start=""
        brinst=""
        OLD_IFS="$IFS"
        IFS="${AB_DELIM}${AB_SSID_DELIM}"
        for i in $BRIDGE_INSTS; do
            brinst=`echo $i |cut -d . -f 4`
            status=`sysevent get multinet_$brinst-status`
            if [ x = x$status -o x$STOPPED_STATUS = x$status ]; then
                sysevent set multinet-start $brinst
                start=1
            fi
        done
        
        for i in $WECB_BRIDGES; do
            if [ x = x"$i" ]; then
                continue
            fi
            status=`sysevent get multinet_$i-status`
            if [ x = x$status -o x$STOPPED_STATUS = x$status ]; then
                sysevent set multinet-start $i
                start=1
            fi
        done
        IFS="$OLD_IFS"
        
        bInst_to_bNames "$BRIDGE_INSTS" "$WECB_BRIDGES"
        update_bridge_config $NAME
        curr_tunnel=`sysevent get gre_current_endpoint`
        if [ x != x$curr_tunnel ]; then
            update_bridge_frag_config $2 $curr_tunnel
        fi
        
        if [ x = x$start ]; then
          echo "handle_gre : Triggering RDKB_FIREWALL_RESTART in update bridges"
            sysevent set firewall-restart
        fi
    ;;
    
#     snooper-wifi-clients) 
#         if [ x$2 = x0 ]; then
#             sysevent set hotspotfd-enable 0
#         else
#             sysevent set hotspotfd-enable 1
#         fi
#     ;;
    *)
        exit 3
        ;;
esac


# TODO 
# modify hotspot params
# modify hotspot bridge structure
# generic gre if impl
# remove name hard code
