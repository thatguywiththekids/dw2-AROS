/*

Copyright (C) 2002-2025 Neil Cafferkey

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston,
MA 02111-1307, USA.

*/

#ifndef ETHERLINK3_H
#define ETHERLINK3_H


/* General */
/* ======= */

#define EL3_WINDOWSIZE 16
#define EL3_PREAMBLESIZE 4
#define EL3_FRAGLEN     2
#define EL3_CORKSCREWOFFSET 992


/* Registers */
/* ========= */

/* All Windows */

#define EL3REG_COMMAND            14
#define EL3REG_STATUS             14
#define EL3REG_DOWNLIST           36
#define EL3REG_UPLIST             56

/* Window 0 */

#define EL3REG_MAKERID             0
#define EL3REG_PRODUCTID           2
#define EL3REG_ADAPTERID           2
#define EL3REG_CONFIG              4
#define EL3REG_ADDRCONFIG          6
#define EL3REG_RESCONFIG           8   /* also in window 3 */
#define EL3REG_EEPROMCMD          10   /* window 2 has alternative version */
#define EL3REG_EEPROMDATA         12

/* Window 1 */

#define EL3REG_DATA0               0
#define EL3REG_DATA1               2
#define EL3REG_RXERROR             4   /* also in window 7 */
#define EL3REG_RXSTATUS            8
#define EL3REG_TIMER              10
#define EL3REG_TXSTATUS           11
#define EL3REG_TXSPACE            12   /* also in window 3 */

/* Window 2 */

#define EL3REG_ADDRESS0            0
#define EL3REG_ADDRESS1            1
#define EL3REG_ADDRESS2            2
#define EL3REG_ADDRESS3            3
#define EL3REG_ADDRESS4            4
#define EL3REG_ADDRESS5            5
#define EL3REG_SRAMDIAG            6
#define EL3REG_MULTIFUNCCONFIG     8
#define EL3REG_ALTEEPROMCMD       10
#define EL3REG_MASK0               6
#define EL3REG_MASK1               7
#define EL3REG_MASK2               8
#define EL3REG_MASK3               9
#define EL3REG_MASK4              10
#define EL3REG_MASK5              11
#define EL3REG_RESETOPTIONS       12

/* Window 3 */

#define EL3REG_INTERNALCONFIG      0
#define EL3REG_ROMCONTROL          4
#define EL3REG_TXRECLAIM           6
#define EL3REG_MACCONTROL          6
#define EL3REG_MEDIAOPTIONS        8   /* formerly EL3REG_RESETOPTIONS */
#define EL3REG_RXSPACE            10

/* Window 4 */

#define EL3REG_FIFODIAG            4
#define EL3REG_NETDIAG             6
#define EL3REG_CONTROLLERSTATUS    8
#define EL3REG_PHYMGMT             8
#define EL3REG_MEDIA              10
#define EL3REG_BADSSD             12
#define EL3REG_BYTESOKUPPER       13

/* Window 5 */

#define EL3REG_TXSTARTTHRESH       0
#define EL3REG_TXAVAILTHRESH       2
#define EL3REG_RXEARLYTHRESH       6
#define EL3REG_RXFILTER            8
#define EL3REG_INTMASK            10
#define EL3REG_READZEROMASK       12

/* Window 6 */

#define EL3REG_CARRIERLOST         0
#define EL3REG_SQEERRORS           1
#define EL3REG_MULTIPLECOLLISIONS  2
#define EL3REG_SINGLECOLLISIONS    3
#define EL3REG_LATECOLLISIONS      4
#define EL3REG_RXOVERRUNS          5
#define EL3REG_TXFRAMESOK          6
#define EL3REG_RXFRAMESOK          7
#define EL3REG_FRAMESDEFERRED      8
#define EL3REG_FRAMESOKUPPER       9
#define EL3REG_RXBYTESOK          10
#define EL3REG_TXBYTESOK          12


/* (Some) EEPROM data offsets */
/* ========================== */

#define EL3ROM_ADDRESS0       0
#define EL3ROM_ADDRESS1       1
#define EL3ROM_ADDRESS2       2
#define EL3ROM_PRODUCTID      3
#define EL3ROM_MANFDATA0      4
#define EL3ROM_MANFDATA1      5
#define EL3ROM_MANFDATA2      6
#define EL3ROM_MAKERID        7
#define EL3ROM_ADDRCONFIG     8
#define EL3ROM_RESCONFIG      9
#define EL3ROM_ALTADDRESS0   10
#define EL3ROM_ALTADDRESS1   11
#define EL3ROM_ALTADDRESS2   12
#define EL3ROM_SOFTWAREINFO  13
#define EL3ROM_COMPATIBILITY 14
/*#define EL3ROM_CHECKSUM      15*/ /* PCMCIA? */
#define EL3ROM_SOFTWAREINFO2 15
#define EL3ROM_CAPABILITIES  16
#define EL3ROM_CHECKSUM      23


/* EEPROM commands */
/* =============== */

#define EL3ECMD_WRITEDISABLE (0x0 << 4)
#define EL3ECMD_WRITEALL     (0x1 << 4)
#define EL3ECMD_ERASEALL     (0x2 << 4)
#define EL3ECMD_WRITEENABLE  (0x3 << 4)
#define EL3ECMD_WRITE        (0x4 << 4)
#define EL3ECMD_READ         (0x8 << 4)
#define EL3ECMD_ERASE        (0xc << 4)


/* Commands */
/* ======== */

#define EL3CMD_GLOBALRESET   (0 << 11)
#define EL3CMD_SELECTWINDOW  (1 << 11)
#define EL3CMD_STARTCOAX     (2 << 11)
#define EL3CMD_RXDISABLE     (3 << 11)
#define EL3CMD_RXENABLE      (4 << 11)
#define EL3CMD_RXRESET       (5 << 11)
#define EL3CMD_UPSTALL       (6 << 11)
#define EL3CMD_UPUNSTALL     (EL3CMD_UPSTALL + 1)
#define EL3CMD_DOWNSTALL     (EL3CMD_UPSTALL + 2)
#define EL3CMD_DOWNUNSTALL   (EL3CMD_UPSTALL + 3)
#define EL3CMD_RXDISCARD     (8 << 11)
#define EL3CMD_TXENABLE      (9 << 11)
#define EL3CMD_TXDISABLE    (10 << 11)
#define EL3CMD_TXRESET      (11 << 11)
#define EL3CMD_REQINT       (12 << 11)
#define EL3CMD_ACKINT       (13 << 11)
#define EL3CMD_SETINTMASK   (14 << 11)
#define EL3CMD_SETZEROMASK  (15 << 11)
#define EL3CMD_SETRXFILTER  (16 << 11)
#define EL3CMD_SETRXTHRESH  (17 << 11)
#define EL3CMD_SETTXTHRESH  (18 << 11)
#define EL3CMD_SETTXSTART   (19 << 11)
#define EL3CMD_STATSENABLE  (21 << 11)
#define EL3CMD_STATSDISABLE (22 << 11)
#define EL3CMD_STOPCOAX     (23 << 11)
#define EL3CMD_POWERUP      (27 << 11)
#define EL3CMD_POWERDOWN    (28 << 11)
#define EL3CMD_POWERAUTO    (29 << 11)


/* Interrupt Types */
/* =============== */

#define EL3INTB_UPDONE      10
#define EL3INTB_DOWNDONE     9
#define EL3INTB_LINKEVENT    8
#define EL3INTB_UPDATESTATS  7
#define EL3INTB_REQINT       6
#define EL3INTB_RXEARLY      5
#define EL3INTB_RXCOMPLETE   4
#define EL3INTB_TXAVAIL      3
#define EL3INTB_TXCOMPLETE   2
#define EL3INTB_FAILURE      1
#define EL3INTB_ANY          0

#define EL3INTF_UPDONE      (1 << EL3INTB_UPDONE)
#define EL3INTF_DOWNDONE    (1 << EL3INTB_DOWNDONE)
#define EL3INTF_UPDATESTATS (1 << EL3INTB_UPDATESTATS)
#define EL3INTF_REQINT      (1 << EL3INTB_REQINT)
#define EL3INTF_RXEARLY     (1 << EL3INTB_RXEARLY)
#define EL3INTF_RXCOMPLETE  (1 << EL3INTB_RXCOMPLETE)
#define EL3INTF_TXAVAIL     (1 << EL3INTB_TXAVAIL)
#define EL3INTF_TXCOMPLETE  (1 << EL3INTB_TXCOMPLETE)
#define EL3INTF_FAILURE     (1 << EL3INTB_FAILURE)
#define EL3INTF_ANY         (1 << EL3INTB_ANY)


/* Transceiver Types */
/* ================= */

#define EL3XCVR_10BASET   0
#define EL3XCVR_AUI       1
#define EL3XCVR_10BASE2   3
#define EL3XCVR_100BASETX 4
#define EL3XCVR_100BASEFX 5
#define EL3XCVR_MII       6
#define EL3XCVR_AUTONEG   8


/* Register Details */
/* ================ */

/* Configuration Control Register */

#define EL3REG_CONFIGB_NOTPCCARD   14
#define EL3REG_CONFIGB_AUI         13
#define EL3REG_CONFIGB_10BASE2     12
#define EL3REG_CONFIGB_10BASET      9
#define EL3REG_CONFIGB_USEINTERNAL  8
#define EL3REG_CONFIGB_RESET        2
#define EL3REG_CONFIGB_ENABLE       0

#define EL3REG_CONFIGF_NOTPCCARD   (1 << EL3REG_CONFIGB_NOTPCCARD)
#define EL3REG_CONFIGF_AUI         (1 << EL3REG_CONFIGB_AUI)
#define EL3REG_CONFIGF_10BASE2     (1 << EL3REG_CONFIGB_10BASE2)
#define EL3REG_CONFIGF_10BASET     (1 << EL3REG_CONFIGB_10BASET)
#define EL3REG_CONFIGF_USEINTERNAL (1 << EL3REG_CONFIGB_USEINTERNAL)
#define EL3REG_CONFIGF_RESET       (1 << EL3REG_CONFIGB_RESET)
#define EL3REG_CONFIGF_ENABLE      (1 << EL3REG_CONFIGB_ENABLE)

/* Address Configuration Register */

#define EL3REG_ADDRCONFIGB_XCVR       14
#define EL3REG_ADDRCONFIGB_AUTOSELECT  7

#define EL3REG_ADDRCONFIGF_AUTOSELECT (1 << EL3REG_ADDRCONFIGB_AUTOSELECT)
#define EL3REG_ADDRCONFIGF_XCVR 0xc000

/* Status Register */

#define EL3REG_STATUSB_WINDOW        13
#define EL3REG_STATUSB_CMDINPROGRESS 12

#define EL3REG_STATUSF_WINDOW 0xe0
#define EL3REG_STATUSF_CMDINPROGRESS (1 << EL3REG_STATUSB_CMDINPROGRESS)

/* EEPROM Command Register */

#define EL3REG_EEPROMCMDB_BUSY 15

#define EL3REG_EEPROMCMDF_BUSY (1 << EL3REG_EEPROMCMDB_BUSY)

/* RX Status Register */

#define EL3REG_RXSTATUSB_INCOMPLETE 15
#define EL3REG_RXSTATUSB_ERROR      14

#define EL3REG_RXSTATUSF_INCOMPLETE (1 << EL3REG_RXSTATUSB_INCOMPLETE)
#define EL3REG_RXSTATUSF_ERROR      (1 << EL3REG_RXSTATUSB_ERROR)

#define EL3REG_RXSTATUS_ERRORMASK   0x3800
#define EL3REG_RXSTATUS_SIZEMASK    0x07ff

/* TX Status Register */

#define EL3REG_TXSTATUSB_COMPLETE      7
#define EL3REG_TXSTATUSB_ONSUCCESS     6
#define EL3REG_TXSTATUSB_JABBER        5
#define EL3REG_TXSTATUSB_UNDERRUN      4
#define EL3REG_TXSTATUSB_MAXCOLLISIONS 3
#define EL3REG_TXSTATUSB_OVERFLOW      2
#define EL3REG_TXSTATUSB_RECLAIMERROR  1

#define EL3REG_TXSTATUSF_COMPLETE      (1 << EL3REG_TXSTATUSB_COMPLETE)
#define EL3REG_TXSTATUSF_ONSUCCESS     (1 << EL3REG_TXSTATUSB_ONSUCCESS)
#define EL3REG_TXSTATUSF_JABBER        (1 << EL3REG_TXSTATUSB_JABBER)
#define EL3REG_TXSTATUSF_UNDERRUN      (1 << EL3REG_TXSTATUSB_UNDERRUN)
#define EL3REG_TXSTATUSF_MAXCOLLISIONS (1 << EL3REG_TXSTATUSB_MAXCOLLISIONS)
#define EL3REG_TXSTATUSF_OVERFLOW      (1 << EL3REG_TXSTATUSB_OVERFLOW)
#define EL3REG_TXSTATUSF_RECLAIMERROR  (1 << EL3REG_TXSTATUSB_RECLAIMERROR)

/* Internal Config Register */

#define EL3REG_INTERNALCONFIGB_AUTOXCVR 24
#define EL3REG_INTERNALCONFIGB_XCVR     20
#define EL3REG_INTERNALCONFIGB_RAMSPLIT 16
#define EL3REG_INTERNALCONFIGB_SSDOFF    8
#define EL3REG_INTERNALCONFIGB_ROMSIZE   6
#define EL3REG_INTERNALCONFIGB_RAMSPEED  4
#define EL3REG_INTERNALCONFIGB_RAMWIDTH  3
#define EL3REG_INTERNALCONFIGB_RAMSIZE   0

#define EL3REG_INTERNALCONFIGF_AUTOXCVR (1 << EL3REG_INTERNALCONFIGB_AUTOXCVR)
#define EL3REG_INTERNALCONFIGF_XCVR     0x00f00000

/* MAC Control Register */

#define EL3REG_MACCONTROLB_FULLDUPLEX 5

#define EL3REG_MACCONTROLF_FULLDUPLEX (1 << EL3REG_MACCONTROLB_FULLDUPLEX)

/* Media Options Register (formerly Reset Options Register) */

#define EL3REG_MEDIAOPTIONSB_MII       6
#define EL3REG_MEDIAOPTIONSB_AUI       5
#define EL3REG_MEDIAOPTIONSB_10BASE2   4
#define EL3REG_MEDIAOPTIONSB_10BASET   3
#define EL3REG_MEDIAOPTIONSB_100BASEFX 2
#define EL3REG_MEDIAOPTIONSB_100BASETX 1
#define EL3REG_MEDIAOPTIONSB_100BASET4 0

#define EL3REG_MEDIAOPTIONSF_MII       (1 << EL3REG_MEDIAOPTIONSB_MII)
#define EL3REG_MEDIAOPTIONSF_AUI       (1 << EL3REG_MEDIAOPTIONSB_AUI)
#define EL3REG_MEDIAOPTIONSF_10BASE2   (1 << EL3REG_MEDIAOPTIONSB_10BASE2)
#define EL3REG_MEDIAOPTIONSF_10BASET   (1 << EL3REG_MEDIAOPTIONSB_10BASET)
#define EL3REG_MEDIAOPTIONSF_100BASEFX (1 << EL3REG_MEDIAOPTIONSB_100BASEFX)
#define EL3REG_MEDIAOPTIONSF_100BASETX (1 << EL3REG_MEDIAOPTIONSB_100BASETX)
#define EL3REG_MEDIAOPTIONSF_100BASET4 (1 << EL3REG_MEDIAOPTIONSB_100BASET4)

/* Net Diagnostic Port Register */

#define EL3REG_NETDIAGB_EXTERNALLOOP   15
#define EL3REG_NETDIAGB_ENDECLOOP      14
#define EL3REG_NETDIAGB_CONTROLLERLOOP 13
#define EL3REG_NETDIAGB_FIFOLOOP       12
#define EL3REG_NETDIAGB_TXON           11
#define EL3REG_NETDIAGB_RXON           10
#define EL3REG_NETDIAGB_TXING           9
#define EL3REG_NETDIAGB_NEEDTXRESET     8
#define EL3REG_NETDIAGB_STATSON         7
#define EL3REG_NETDIAGB_WIDESTATS       6
#define EL3REG_NETDIAGB_TESTLVD         0

#define EL3REG_NETDIAGF_EXTERNALLOOP   (1 << EL3REG_NETDIAGB_EXTERNALLOOP)
#define EL3REG_NETDIAGF_ENDECLOOP      (1 << EL3REG_NETDIAGB_ENDECLOOP)
#define EL3REG_NETDIAGF_CONTROLLERLOOP (1 << EL3REG_NETDIAGB_CONTROLLERLOOP)
#define EL3REG_NETDIAGF_FIFOLOOP       (1 << EL3REG_NETDIAGB_FIFOLOOP)
#define EL3REG_NETDIAGF_TXON           (1 << EL3REG_NETDIAGB_TXON)
#define EL3REG_NETDIAGF_RXON           (1 << EL3REG_NETDIAGB_RXON)
#define EL3REG_NETDIAGF_TXING          (1 << EL3REG_NETDIAGB_TXING)
#define EL3REG_NETDIAGF_NEEDTXRESET    (1 << EL3REG_NETDIAGB_NEEDTXRESET)
#define EL3REG_NETDIAGF_STATSON        (1 << EL3REG_NETDIAGB_STATSON)
#define EL3REG_NETDIAGF_WIDESTATS      (1 << EL3REG_NETDIAGB_WIDESTATS)
#define EL3REG_NETDIAGF_TESTLVD        (1 << EL3REG_NETDIAGB_TESTLVD)

#define EL3REG_NETDIAG_REVMASK         0x3e

/* Physical Management Register */

#define EL3REG_PHYMGMTB_NOCAT5LINKTEST 15
#define EL3REG_PHYMGMTB_WRITE           2
#define EL3REG_PHYMGMTB_DATA            1
#define EL3REG_PHYMGMTB_CLK             0

#define EL3REG_PHYMGMTF_NOCAT5LINKTEST (1 << EL3REG_PHYMGMTB_NOCAT5LINKTEST)
#define EL3REG_PHYMGMTF_WRITE          (1 << EL3REG_PHYMGMTB_WRITE)
#define EL3REG_PHYMGMTF_DATA           (1 << EL3REG_PHYMGMTB_DATA)
#define EL3REG_PHYMGMTF_CLK            (1 << EL3REG_PHYMGMTB_CLK)

/* Media Type and Status Register */

#define EL3REG_MEDIAB_TP              15
#define EL3REG_MEDIAB_COAX            14
#define EL3REG_MEDIAB_SQE             12
#define EL3REG_MEDIAB_BEAT            11
#define EL3REG_MEDIAB_POLEREV         10
#define EL3REG_MEDIAB_JABBER           9
#define EL3REG_MEDIAB_UNSQUELCH        8
#define EL3REG_MEDIAB_BEATCHECK        7
#define EL3REG_MEDIAB_JABBERCHECK      6
#define EL3REG_MEDIAB_CRS              5
#define EL3REG_MEDIAB_COLLISION        4
#define EL3REG_MEDIAB_SQESTATSENABLE   3
#define EL3REG_MEDIAB_CRCSTRIPDISABLE  2
#define EL3REG_MEDIAB_LINKLIGHT        0

#define EL3REG_MEDIAF_TP              (1 << EL3REG_MEDIAB_TP)
#define EL3REG_MEDIAF_COAX            (1 << EL3REG_MEDIAB_COAX)
#define EL3REG_MEDIAF_SQE             (1 << EL3REG_MEDIAB_SQE)
#define EL3REG_MEDIAF_BEAT            (1 << EL3REG_MEDIAB_BEAT)
#define EL3REG_MEDIAF_POLEREV         (1 << EL3REG_MEDIAB_POLEREV)
#define EL3REG_MEDIAF_JABBER          (1 << EL3REG_MEDIAB_JABBER)
#define EL3REG_MEDIAF_UNSQUELCH       (1 << EL3REG_MEDIAB_UNSQUELCH)
#define EL3REG_MEDIAF_BEATCHECK       (1 << EL3REG_MEDIAB_BEATCHECK)
#define EL3REG_MEDIAF_JABBERCHECK     (1 << EL3REG_MEDIAB_JABBERCHECK)
#define EL3REG_MEDIAF_CRS             (1 << EL3REG_MEDIAB_CRS)
#define EL3REG_MEDIAF_COLLISION       (1 << EL3REG_MEDIAB_COLLISION)
#define EL3REG_MEDIAF_SQESTATSENABLE  (1 << EL3REG_MEDIAB_SQESTATSENABLE)
#define EL3REG_MEDIAF_CRCSTRIPDISABLE (1 << EL3REG_MEDIAB_CRCSTRIPDISABLE)
#define EL3REG_MEDIAF_LINKLIGHT       (1 << EL3REG_MEDIAB_LINKLIGHT)


/* Command parameters */
/* ================== */

#define EL3CMD_RXRESETB_SKIPNETWORK 2

#define EL3CMD_RXRESETF_SKIPNETWORK (1 << EL3CMD_RXRESETB_SKIPNETWORK)

#define EL3CMD_SETRXFILTERB_UCAST 0
#define EL3CMD_SETRXFILTERB_MCAST 1
#define EL3CMD_SETRXFILTERB_BCAST 2
#define EL3CMD_SETRXFILTERB_PROM  3

#define EL3CMD_SETRXFILTERF_UCAST (1 << EL3CMD_SETRXFILTERB_UCAST)
#define EL3CMD_SETRXFILTERF_MCAST (1 << EL3CMD_SETRXFILTERB_MCAST)
#define EL3CMD_SETRXFILTERF_BCAST (1 << EL3CMD_SETRXFILTERB_BCAST)
#define EL3CMD_SETRXFILTERF_PROM  (1 << EL3CMD_SETRXFILTERB_PROM)


/* EEPROM field details */
/* ==================== */

#define EL3ROM_CAPABILITIESB_POWERSAVE  13
#define EL3ROM_CAPABILITIESB_100MBPS    12
#define EL3ROM_CAPABILITIESB_SNOOP      11
#define EL3ROM_CAPABILITIESB_RXREPEAT   10
#define EL3ROM_CAPABILITIESB_NOTXLEN     9
#define EL3ROM_CAPABILITIESB_TXDONE      8
#define EL3ROM_CAPABILITIESB_CRCPASS     7
#define EL3ROM_CAPABILITIESB_MASTER      6
#define EL3ROM_CAPABILITIESB_FULLMASTER  5
#define EL3ROM_CAPABILITIESB_2NDDMA      4
#define EL3ROM_CAPABILITIESB_SLAVEDMA    3
#define EL3ROM_CAPABILITIESB_BIGPACKETS  2
#define EL3ROM_CAPABILITIESB_DUPLEX      1
#define EL3ROM_CAPABILITIESB_PNP         0

#define EL3ROM_CAPABILITIESF_POWERSAVE  (1 << EL3ROM_CAPABILITIESB_POWERSAVE)
#define EL3ROM_CAPABILITIESF_100MBPS    (1 << EL3ROM_CAPABILITIESB_100MBPS)
#define EL3ROM_CAPABILITIESF_SNOOP      (1 << EL3ROM_CAPABILITIESB_SNOOP)
#define EL3ROM_CAPABILITIESF_RXREPEAT   (1 << EL3ROM_CAPABILITIESB_RXREPEAT)
#define EL3ROM_CAPABILITIESF_NOTXLEN    (1 << EL3ROM_CAPABILITIESB_NOTXLEN)
#define EL3ROM_CAPABILITIESF_TXDONE     (1 << EL3ROM_CAPABILITIESB_TXDONE)
#define EL3ROM_CAPABILITIESF_CRCPASS    (1 << EL3ROM_CAPABILITIESB_CRCPASS)
#define EL3ROM_CAPABILITIESF_MASTER     (1 << EL3ROM_CAPABILITIESB_MASTER)
#define EL3ROM_CAPABILITIESF_FULLMASTER (1 << EL3ROM_CAPABILITIESB_FULLMASTER)
#define EL3ROM_CAPABILITIESF_2NDDMA     (1 << EL3ROM_CAPABILITIESB_2NDDMA)
#define EL3ROM_CAPABILITIESF_SLAVEDMA   (1 << EL3ROM_CAPABILITIESB_SLAVEDMA)
#define EL3ROM_CAPABILITIESF_BIGPACKETS (1 << EL3ROM_CAPABILITIESB_BIGPACKETS)
#define EL3ROM_CAPABILITIESF_DUPLEX     (1 << EL3ROM_CAPABILITIESB_DUPLEX)
#define EL3ROM_CAPABILITIESF_PNP        (1 << EL3ROM_CAPABILITIESB_PNP)


/* DMA Packet Descriptors */
/* ====================== */

/* Fragments */

#define EL3FRAG_ADDR 0
#define EL3FRAG_LEN 1

#define EL3FRAG_LENB_LAST 31

#define EL3FRAG_LENF_LAST (1 << EL3FRAG_LENB_LAST)

/* Download Packet Descriptors */

#define EL3DPD_NEXT 0
#define EL3DPD_HEADER 1
#define EL3DPD_FIRSTFRAG 2

#define EL3DPD_HEADERB_DLINT    31
#define EL3DPD_HEADERB_COMPLETE 16
#define EL3DPD_HEADERB_TXINT    15

#define EL3DPD_HEADERF_DLINT    (1 << EL3DPD_HEADERB_DLINT)
#define EL3DPD_HEADERF_COMPLETE (1 << EL3DPD_HEADERB_COMPLETE)
#define EL3DPD_HEADERF_TXINT    (1 << EL3DPD_HEADERB_TXINT)

/* Upload Packet Descriptors */

#define EL3UPD_NEXT 0
#define EL3UPD_STATUS 1
#define EL3UPD_FIRSTFRAG 2

#define EL3UPD_STATUSB_COMPLETE 15
#define EL3UPD_STATUSB_ERROR 14

#define EL3UPD_STATUSF_COMPLETE (1 << EL3UPD_STATUSB_COMPLETE)
#define EL3UPD_STATUSF_ERROR (1 << EL3UPD_STATUSB_ERROR)
#define EL3UPD_STATUSF_SIZE 0x1fff


#endif
