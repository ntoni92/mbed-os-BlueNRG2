/*
 * Copyright (c) 2019 STMICROELECTRONICS. All Rights Reserved.
 *
 * The information contained herein is property of STMicroelectronics.
 * Terms and conditions of usage are described in detail in SOFTWARE
 * LICENSE AGREEMENT:
 *
 * (SLA0068 - PRODUCTION LIMITED LICENSE AGREEMENT FOR ST MATERIALS)
 *
 * You may obtain a copy of the License here: SLA0068.txt and at
 * STMicroelectronics website.
 *
 * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
 * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
 * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
 * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
 * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
 * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
 *
 */

#ifndef _BLUENRG1_API_H_
#define _BLUENRG1_API_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
/** Documentation for C struct Whitelist_Entry_t */
typedef struct Whitelist_Entry_t_s {
  /** Address type. 
  * Values:
  - 0x00: Public Device Address
  - 0x01: Random Device Address
  */
  uint8_t Peer_Address_Type;
  /** Public Device Address or Random Device Address of the device
to be added to the white list.
  */
  uint8_t Peer_Address[6];
} Whitelist_Entry_t;
/** Documentation for C struct Bonded_Device_Entry_t */
typedef struct Bonded_Device_Entry_t_s {
  /** Address type. 
  * Values:
  - 0x00: Public Device Address
  - 0x01: Random Device Address
  */
  uint8_t Address_Type;
  /** Public Device Address or Random Device Address of the device
to be added to the white list.
  */
  uint8_t Address[6];
} Bonded_Device_Entry_t;
/** Documentation for C struct Whitelist_Identity_Entry_t */
typedef struct Whitelist_Identity_Entry_t_s {
  /** Identity address type. 
  * Values:
  - 0x00: Public Identity Address
  - 0x01: Random (static) Identity Address
  */
  uint8_t Peer_Identity_Address_Type;
  /** Public or Random (static) Identity address of the peer device
  */
  uint8_t Peer_Identity_Address[6];
} Whitelist_Identity_Entry_t;
/** Documentation for C union Service_UUID_t */
typedef union Service_UUID_t_s {
  /** 16-bit UUID 
  */
  uint16_t Service_UUID_16;
  /** 128-bit UUID
  */
  uint8_t Service_UUID_128[16];
} Service_UUID_t;
/** Documentation for C union Include_UUID_t */
typedef union Include_UUID_t_s {
  /** 16-bit UUID 
  */
  uint16_t Include_UUID_16;
  /** 128-bit UUID
  */
  uint8_t Include_UUID_128[16];
} Include_UUID_t;
/** Documentation for C union Char_UUID_t */
typedef union Char_UUID_t_s {
  /** 16-bit UUID 
  */
  uint16_t Char_UUID_16;
  /** 128-bit UUID
  */
  uint8_t Char_UUID_128[16];
} Char_UUID_t;
/** Documentation for C union Char_Desc_Uuid_t */
typedef union Char_Desc_Uuid_t_s {
  /** 16-bit UUID 
  */
  uint16_t Char_UUID_16;
  /** 128-bit UUID
  */
  uint8_t Char_UUID_128[16];
} Char_Desc_Uuid_t;
/** Documentation for C union UUID_t */
typedef union UUID_t_s {
  /** 16-bit UUID 
  */
  uint16_t UUID_16;
  /** 128-bit UUID
  */
  uint8_t UUID_128[16];
} UUID_t;
/** Documentation for C struct Handle_Entry_t */
typedef struct Handle_Entry_t_s {
  /** The handles for which the attribute value has to be read 
  */
  uint16_t Handle;
} Handle_Entry_t;
typedef uint8_t tBleStatus;
/**
 *@defgroup HCI_API HCI API
 *@brief HCI API layer.
 *@{
 */
/**
  * @brief The @ref hci_disconnect is used to terminate an existing connection. The
Connection_Handle command parameter indicates which connection is to be
disconnected. The Reason command parameter indicates the reason for ending
the connection. The remote Controller will receive the Reason command
parameter in the @ref hci_disconnection_complete_event event. All synchronous connections
on a physical link should be disconnected before the ACL connection on the
same physical connection is disconnected.
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.1.6)
It is important to leave an 100 ms blank window before sending any new command (including system hardware reset),
since immediately after @ref hci_disconnection_complete_event event, system could save important information in non volatile memory.
  * @param Connection_Handle Connection handle for which the command is given.
  * Values:
  - 0x0000 ... 0x0EFF
  * @param Reason The reason for ending the connection.
  * Values:
  - 0x05: Authentication Failure
  - 0x13: Remote User Terminated Connection
  - 0x14: Remote Device Terminated Connection due to Low Resources
  - 0x15: Remote Device Terminated Connection due to Power Off
  - 0x1A: Unsupported Remote Feature
  - 0x3B: Unacceptable Connection Parameters
  * @retval Value indicating success or error code.
*/
tBleStatus hci_disconnect(uint16_t Connection_Handle,
                          uint8_t Reason);
/**
  * @brief This command will obtain the values for the version information for the remote
device identified by the Connection_Handle parameter. The Connection_Handle
must be a Connection_Handle for an ACL or LE connection.
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.1.23)
  * @param Connection_Handle Specifies which Connection_Handle's version information to get.
  * Values:
  - 0x0000 ... 0x0EFF
  * @retval Value indicating success or error code.
*/
tBleStatus hci_read_remote_version_information(uint16_t Connection_Handle);
/**
  * @brief The Set_Event_Mask command is used to control which events are generated
by the HCI for the Host.

If the bit in the Event_Mask is set to a one, then the
event associated with that bit will be enabled. For an LE Controller, the LE
Meta Event bit in the Event_Mask shall enable or disable all LE events in the
LE Meta Event (see Section 7.7.65). The Host has to deal with each event that
occurs. The event mask allows the Host to control how much it is interrupted.
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.3.1)
  * @param Event_Mask Event mask. Default: 0x00001FFFFFFFFFFF
  * Flags:
  - 0x0000000000000000: No events specified
  - 0x0000000000000001: Inquiry Complete Event
  - 0x0000000000000002: Inquiry Result Event
  - 0x0000000000000004: Connection Complete Event
  - 0x0000000000000008: Connection Request Event
  - 0x0000000000000010: Disconnection Complete Event
  - 0x0000000000000020: Authentication Complete Event
  - 0x0000000000000040: Remote Name Request Complete Event
  - 0x0000000000000080: Encryption Change Event
  - 0x0000000000000100: Change Connection Link Key Complete Event
  - 0x0000000000000200: Master Link Key Complete Event
  - 0x0000000000000400: Read Remote Supported Features Complete Event
  - 0x0000000000000800: Read Remote Version Information Complete Event
  - 0x0000000000001000: QoS Setup Complete Event
  - 0x0000000000008000: Hardware Error Event
  - 0x0000000000010000: Flush Occurred Event
  - 0x0000000000020000: Role Change Event
  - 0x0000000000080000: Mode Change Event
  - 0x0000000000100000: Return Link Keys Event
  - 0x0000000000200000: PIN Code Request Event
  - 0x0000000000400000: Link Key Request Event
  - 0x0000000000800000: Link Key Notification Event
  - 0x0000000001000000: Loopback Command Event
  - 0x0000000002000000: Data Buffer Overflow Event
  - 0x0000000004000000: Max Slots Change Event
  - 0x0000000008000000: Read Clock Offset Complete Event
  - 0x0000000010000000: Connection Packet Type Changed Event
  - 0x0000000020000000: QoS Violation Event
  - 0x0000000040000000: Page Scan Mode Change Event
  - 0x0000000080000000: Page Scan Repetition Mode Change Event
  - 0x0000000100000000: Flow Specification Complete Event
  - 0x0000000200000000: Inquiry Result with RSSI Event
  - 0x0000000400000000: Read Remote Extended Features Complete Event
  - 0x0000080000000000: Synchronous Connection Complete Event
  - 0x0000100000000000: Synchronous Connection Changed Event
  - 0x0000200000000000: Sniff Subrating Event
  - 0x0000400000000000: Extended Inquiry Result Event
  - 0x0000800000000000: Encryption Key Refresh Complete Event
  - 0x0001000000000000: IO Capability Request Event
  - 0x0002000000000000: IO Capability Request Reply Event
  - 0x0004000000000000: User Confirmation Request Event
  - 0x0008000000000000: User Passkey Request Event
  - 0x0010000000000000: Remote OOB Data Request Event
  - 0x0020000000000000: Simple Pairing Complete Event
  - 0x0080000000000000: Link Supervision Timeout Changed Event
  - 0x0100000000000000: Enhanced Flush Complete Event
  - 0x0400000000000000: User Passkey Notification Event
  - 0x0800000000000000: Keypress Notification Event
  - 0x1000000000000000: Remote Host Supported Features Notification Event
  - 0x2000000000000000: LE Meta-Event
  * @retval Value indicating success or error code.
*/
tBleStatus hci_set_event_mask(uint8_t Event_Mask[8]);
/**
  * @brief The Reset command will reset the Link Layer on an LE
Controller.

The Reset command shall not affect the used HCI transport layer since the HCI transport
layers may have reset mechanisms of their own. After the reset is completed,
the current operational state will be lost, the Controller will enter standby mode
and the Controller will automatically revert to the default values for the parameters
for which default values are defined in the specification.
Note: The Reset command will not necessarily perform a hardware reset. This
is implementation defined. 
The Host shall not send additional HCI commands before the Command Complete
event related to the Reset command has been received.
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.3.2)
  * @retval Value indicating success or error code.
*/
tBleStatus hci_reset(void);
/**
  * @brief This command reads the values for the Transmit_Power_Level parameter for
the specified Connection_Handle. The Connection_Handle shall be a Connection_Handle
for an ACL connection.
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.3.35)
  * @param Connection_Handle Specifies which Connection_Handle's Transmit Power Level setting to read.
  * Values:
  - 0x0000 ... 0x0EFF
  * @param Type Current or maximum transmit power level.
  * Values:
  - 0x00: Read Current Transmit Power Level.
  - 0x01: Read Maximum Transmit Power Level.
  * @param[out] Transmit_Power_Level Size: 1 Octet (signed integer)
Units: dBm
  * Values:
  - -30 ... 20
  * @retval Value indicating success or error code.
*/
tBleStatus hci_read_transmit_power_level(uint16_t Connection_Handle,
                                         uint8_t Type,
                                         uint8_t *Transmit_Power_Level);
/**
  * @brief This command reads the values for the version information for the local Controller.
The HCI Version information defines the version information of the HCI layer.
The LMP/PAL Version information defines the version of the LMP or PAL. The
Manufacturer_Name information indicates the manufacturer of the local device.
The HCI Revision and LMP/PAL Subversion are implementation dependent.
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.4.1)
  * @param[out] HCI_Version See Bluetooth Assigned Numbers (https://www.bluetooth.org/en-us/specification/assigned-numbers)
  * @param[out] HCI_Revision Revision of the Current HCI in the BR/EDR Controller.
  * @param[out] LMP_PAL_Version Version of the Current LMP or PAL in the Controller.
See Bluetooth Assigned Numbers (https://www.bluetooth.org/en-us/specification/assigned-numbers)
  * @param[out] Manufacturer_Name Manufacturer Name of the BR/EDR Controller.
See Bluetooth Assigned Numbers (https://www.bluetooth.org/en-us/specification/assigned-numbers)
  * @param[out] LMP_PAL_Subversion Subversion of the Current LMP or PAL in the Controller. This value is
implementation dependent.
  * @retval Value indicating success or error code.
*/
tBleStatus hci_read_local_version_information(uint8_t *HCI_Version,
                                              uint16_t *HCI_Revision,
                                              uint8_t *LMP_PAL_Version,
                                              uint16_t *Manufacturer_Name,
                                              uint16_t *LMP_PAL_Subversion);
/**
  * @brief This command reads the list of HCI commands supported for the local Controller.
This command shall return the Supported_Commands configuration parameter.
It is implied that if a command is listed as supported, the feature underlying
that command is also supported.
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.4.2)
  * @param[out] Supported_Commands Bit mask for each HCI Command. If a bit is 1, the Controller supports the
corresponding command and the features required for the command.
Unsupported or undefined commands shall be set to 0.
  * @retval Value indicating success or error code.
*/
tBleStatus hci_read_local_supported_commands(uint8_t Supported_Commands[64]);
/**
  * @brief This command requests a list of the supported features for the local 
Controller. This command will return a list of the LMP features. For details see
Part C, Link Manager Protocol Specification on page 227.
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.4.3)
  * @param[out] LMP_Features Bit Mask List of LMP features.
  * @retval Value indicating success or error code.
*/
tBleStatus hci_read_local_supported_features(uint8_t LMP_Features[8]);
/**
  * @brief On an LE Controller, this command shall read the Public Device Address as
defined in [Vol 6] Part B, Section 1.3, Device Address. If this Controller does
not have a Public Device Address, the value 0x000000000000 shall be
returned.
On an LE Controller, the public address shall be the same as the
BD_ADDR.
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.4.6)
  * @param[out] BD_ADDR BD_ADDR ( Bluetooth Device Address) of the Device.
  * @retval Value indicating success or error code.
*/
tBleStatus hci_read_bd_addr(uint8_t BD_ADDR[6]);
/**
  * @brief This command reads the Received Signal Strength Indication (RSSI) value from
a Controller.
For an LE transport, a Connection_Handle is used as the Handle command
parameter and return parameter. The meaning of the RSSI metric is an absolute
receiver signal strength value in dBm to +/- 6 dB accuracy. If the RSSI cannot
be read, the RSSI metric shall be set to 127.
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.5.4)
  * @param Connection_Handle Connection handle for which the command is given.
  * Values:
  - 0x0000 ... 0x0EFF
  * @param[out] RSSI N Size: 1 Octet (signed integer)
Units: dBm
  * Values:
  - 127: RSSI not available
  - -127 ... 20
  * @retval Value indicating success or error code.
*/
tBleStatus hci_read_rssi(uint16_t Connection_Handle,
                         uint8_t *RSSI);
/**
  * @brief The LE_Set_Event_Mask command is used to control which LE events are
generated by the HCI for the Host. If the bit in the LE_Event_Mask is set to a
one, then the event associated with that bit will be enabled. The Host has to
deal with each event that is generated by an LE Controller. The event mask
allows the Host to control which events will interrupt it.
For LE events to be generated, the LE Meta-Event bit in the Event_Mask shall
also be set. If that bit is not set, then LE events shall not be generated, regardless
of how the LE_Event_Mask is set.
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.8.1)
  * @param LE_Event_Mask LE event mask. Default: 0x000000000000001F.
  * Flags:
  - 0x0000000000000000: No LE events specified
  - 0x0000000000000001: LE Connection Complete Event
  - 0x0000000000000002: LE Advertising Report Event
  - 0x0000000000000004: LE Connection Update Complete Event
  - 0x0000000000000008: LE Read Remote Used Features Complete Event
  - 0x0000000000000010: LE Long Term Key Request Event
  - 0x0000000000000020: LE Remote Connection Parameter Request Event
  - 0x0000000000000040: LE Data Length Change Event
  - 0x0000000000000080: LE Read Local P-256 Public Key Complete Event
  - 0x0000000000000100: LE Generate DHKey Complete Event
  - 0x0000000000000200: LE Enhanced Connection Complete Event
  - 0x0000000000000400: LE Direct Advertising Report Event
  * @retval Value indicating success or error code.
*/
tBleStatus hci_le_set_event_mask(uint8_t LE_Event_Mask[8]);
/**
  * @brief The LE_Read_Buffer_Size command is used to read the maximum size of the
data portion of HCI LE ACL Data Packets sent from the Host to the Controller.
The Host will segment the data transmitted to the Controller according to these
values, so that the HCI Data Packets will contain data with up to this size. The
LE_Read_Buffer_Size command also returns the total number of HCI LE ACL
Data Packets that can be stored in the data buffers of the Controller. The
LE_Read_Buffer_Size command must be issued by the Host before it sends
any data to an LE Controller (see Section 4.1.1).
If the Controller returns a length value of zero, the Host shall use the
Read_Buffer_Size command to determine the size of the data buffers
Note: Both the Read_Buffer_Size and LE_Read_Buffer_Size commands may
return buffer length and number of packets parameter values that are nonzero.
The HC_LE_ACL_Data_Packet_Length return parameter shall be used to
determine the size of the L2CAP PDU segments contained in ACL Data
Packets, which are transferred from the Host to the Controller to be broken up
into packets by the Link Layer. Both the Host and the Controller shall support
command and event packets, where the data portion (excluding header)
contained in the packets is 255 octets in size. The
HC_Total_Num_LE_ACL_Data_Packets return parameter contains the total
number of HCI ACL Data Packets that can be stored in the data buffers of the
Controller. The Host determines how the buffers are to be divided between
different Connection Handles.
Note: The HC_LE_ACL_Data_Packet_Length return parameter does not
include the length of the HCI Data Packet header.
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.8.2)
  * @param[out] HC_LE_ACL_Data_Packet_Length 0x0000 No dedicated LE Buffer - use Read_Buffer_Size command.
0x0001 - 0xFFFF Maximum length (in octets) of the data portion of each HCI ACL Data
Packet that the Controller is able to accept.
  * @param[out] HC_Total_Num_LE_ACL_Data_Packets 0x00 No dedicated LE Buffer - use Read_Buffer_Size command.
0x01 - 0xFF Total number of HCI ACL Data Packets that can be stored in the data
buffers of the Controller.
  * @retval Value indicating success or error code.
*/
tBleStatus hci_le_read_buffer_size(uint16_t *HC_LE_ACL_Data_Packet_Length,
                                   uint8_t *HC_Total_Num_LE_ACL_Data_Packets);
/**
  * @brief This command requests the list of the supported LE features for the Controller.
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.8.3)
  * @param[out] LE_Features Bit Mask List of LE features. See Core v4.1, Vol. 6, Part B, Section 4.6.
  * @retval Value indicating success or error code.
*/
tBleStatus hci_le_read_local_supported_features(uint8_t LE_Features[8]);
/**
  * @brief The LE_Set_Random_Address command is used by the Host to set the LE
Random Device Address in the Controller (see [Vol 6] Part B, Section 1.3).
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.8.4)
  * @param Random_Address Random Device Address.
  * @retval Value indicating success or error code.
*/
tBleStatus hci_le_set_random_address(uint8_t Random_Address[6]);
/**
  * @brief The LE_Set_Advertising_Parameters command is used by the Host to set the
advertising parameters.
The Advertising_Interval_Min shall be less than or equal to the
Advertising_Interval_Max. The Advertising_Interval_Min and
Advertising_Interval_Max should not be the same value to enable the
Controller to determine the best advertising interval given other activities.
For high duty cycle directed advertising, i.e. when Advertising_Type is 0x01
(ADV_DIRECT_IND, high duty cycle), the Advertising_Interval_Min and
Advertising_Interval_Max parameters are not used and shall be ignored.
The Advertising_Type is used to determine the packet type that is used for
advertising when advertising is enabled.
Own_Address_Type parameter indicates the type of address being used in the
advertising packets.
If Own_Address_Type equals 0x02 or 0x03, the Peer_Address parameter
contains the peer's Identity Address and the Peer_Address_Type parameter
contains the Peer's Identity Type (i.e. 0x00 or 0x01). These parameters are
used to locate the corresponding local IRK in the resolving list; this IRK is used
to generate the own address used in the advertisement.
If directed advertising is performed, i.e. when Advertising_Type is set to 0x01
(ADV_DIRECT_IND, high duty cycle) or 0x04 (ADV_DIRECT_IND, low duty
cycle mode), then the Peer_Address_Type and Peer_Address shall be valid.
If Own_Address_Type equals 0x02 or 0x03, the Controller generates the
peer's Resolvable Private Address using the peer's IRK corresponding to the
peer's Identity Address contained in the Peer_Address parameter and peer's
Identity Address Type (i.e. 0x00 or 0x01) contained in the Peer_Address_Type
parameter.
The Advertising_Channel_Map is a bit field that indicates the advertising
channels that shall be used when transmitting advertising packets. At least one
channel bit shall be set in the Advertising_Channel_Map parameter.
The Advertising_Filter_Policy parameter shall be ignored when directed
advertising is enabled.
The Host shall not issue this command when advertising is enabled in the
Controller; if it is the Command Disallowed error code shall be used.
If the advertising interval range provided by the Host (Advertising_Interval_Min,
Advertising_Interval_Max) is outside the advertising interval range supported
by the Controller, then the Controller shall return the Unsupported Feature or
Parameter Value (0x11) error code.
  * @param Advertising_Interval_Min Minimum advertising interval.
Time = N * 0.625 msec.
  * Values:
  - 0x0020 (20.000 ms)  ... 0x4000 (10240.000 ms) 
  * @param Advertising_Interval_Max Maximum advertising interval.
Time = N * 0.625 msec.
  * Values:
  - 0x0020 (20.000 ms)  ... 0x4000 (10240.000 ms) 
  * @param Advertising_Type Advertising type.
  * Values:
  - 0x00: ADV_IND (Connectable undirected advertising)
  - 0x01: ADV_DIRECT_IND, high duty cycle (Connectable high duty cycle directed advertising)
  - 0x02: ADV_SCAN_IND (Scannable undirected advertising)
  - 0x03: ADV_NONCONN_IND (Non connectable undirected advertising)
  - 0x04: ADV_DIRECT_IND, low duty cycle (Connectable low duty cycle directed advertising)
  * @param Own_Address_Type Own address type.
 - 0x00: Public Device Address
 - 0x01 Random Device Address
 - 0x02: Controller generates Resolvable Private Address based on the local
         IRK from resolving list. If resolving list contains no matching entry,
         use public address.
 - 0x03: Controller generates Resolvable Private Address based on the local
         IRK from resolving list. If resolving list contains no matching entry,
         use random address from LE_Set_Random_Address.
  * Values:
  - 0x00: Public Device Address
  - 0x01: Random Device Address
  - 0x02: Resolvable Private Address or Public Address
  - 0x03: Resolvable Private Address or Random Address
  * @param Peer_Address_Type Peer Address type.
  * Values:
  - 0x00: Public Device Address or Public Identity Address
  - 0x01: Random Device Address or Random (static) Identity Address
  * @param Peer_Address Public Device Address, Random Device Address, Public Identity
Address or Random (static) Identity Address of the device to be connected.
  * @param Advertising_Channel_Map Advertising channel map.
Default: 00000111b (all channels enabled).
  * Flags:
  - 0x01: ch 37
  - 0x02: ch 38
  - 0x04: ch 39
  * @param Advertising_Filter_Policy Advertising filter policy.
  * Values:
  - 0x00: Allow Scan Request from Any, Allow Connect Request from Any
  - 0x01: Allow Scan Request from White List Only, Allow Connect Request from Any
  - 0x02: Allow Scan Request from Any, Allow Connect Request from White List Only
  - 0x03: Allow Scan Request from White List Only, Allow Connect Request from White List Only
  * @retval Value indicating success or error code.
*/
tBleStatus hci_le_set_advertising_parameters(uint16_t Advertising_Interval_Min,
                                             uint16_t Advertising_Interval_Max,
                                             uint8_t Advertising_Type,
                                             uint8_t Own_Address_Type,
                                             uint8_t Peer_Address_Type,
                                             uint8_t Peer_Address[6],
                                             uint8_t Advertising_Channel_Map,
                                             uint8_t Advertising_Filter_Policy);
/**
  * @brief The LE_Read_Advertising_Channel_Tx_Power command is used by the Host
to read the transmit power level used for LE advertising channel packets.
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.8.6)
  * @param[out] Transmit_Power_Level Size: 1 Octet (signed integer)
Units: dBm
Accuracy: +/- 4 dBm
  * Values:
  - -20 ... 10
  * @retval Value indicating success or error code.
*/
tBleStatus hci_le_read_advertising_channel_tx_power(uint8_t *Transmit_Power_Level);
/**
  * @brief The LE_Set_Advertising_Data command is used to set the data used in advertising
packets that have a data field.
Only the significant part of the Advertising_Data is transmitted in the advertising
packets, as defined in [Vol 3] Part C, Section 11.,
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.8.7)
  * @param Advertising_Data_Length The number of significant octets in the following data field
  * @param Advertising_Data 31 octets of data formatted as defined in [Vol 3] Part
C, Section 11.
  * @retval Value indicating success or error code.
*/
tBleStatus hci_le_set_advertising_data(uint8_t Advertising_Data_Length,
                                       uint8_t Advertising_Data[31]);
/**
  * @brief This command is used to provide data used in Scanning Packets that have a
data field.
Only the significant part of the Scan_Response_Data is transmitted in the
Scanning Packets, as defined in [Vol 3] Part C, Section 11.
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.8.8)
  * @param Scan_Response_Data_Length The number of significant octets in the following data field
  * @param Scan_Response_Data 31 octets of data formatted as defined in [Vol 3] Part
C, Section 11.
  * @retval Value indicating success or error code.
*/
tBleStatus hci_le_set_scan_response_data(uint8_t Scan_Response_Data_Length,
                                         uint8_t Scan_Response_Data[31]);
/**
  * @brief The LE_Set_Advertise_Enable command is used to request the Controller to
start or stop advertising. The Controller manages the timing of advertisements
as per the advertising parameters given in the LE_Set_Advertising_Parameters
command.
The Controller shall continue advertising until the Host issues an LE_Set_Advertise_Enable
command with Advertising_Enable set to 0x00 (Advertising is
disabled) or until a connection is created or until the Advertising is timed out
due to high duty cycle Directed Advertising. In these cases, advertising is then
disabled.
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.8.9)
  * @param Advertising_Enable Enable/disable advertise. Default is 0 (disabled).
  * Values:
  - 0x00: Advertising is disabled
  - 0x01: Advertising is enabled
  * @retval Value indicating success or error code.
*/
tBleStatus hci_le_set_advertise_enable(uint8_t Advertising_Enable);
/**
  * @brief The LE_Set_Scan_Parameters command is used to set the scan parameters.
The LE_Scan_Type parameter controls the type of scan to perform.
The LE_Scan_Interval and LE_Scan_Window parameters are recommendations
from the Host on how long (LE_Scan_Window) and how frequently
(LE_Scan_Interval) the Controller should scan (See [Vol 6] Part B, Section
4.5.3). The LE_Scan_Window parameter shall always be set to a value smaller
or equal to the value set for the LE_Scan_Interval parameter. If they are set to
the same value scanning should be run continuously.
The Own_Address_Type parameter determines the address used (Public or
Random Device Address) when performing active scan.
The Host shall not issue this command when scanning is enabled in the Controller;
if it is the Command Disallowed error code shall be used.
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.8.10)
  * @param LE_Scan_Type Passive or active scanning. With active scanning SCAN_REQ packets are sent.
  * Values:
  - 0x00: Passive Scanning
  - 0x01: Active scanning
  * @param LE_Scan_Interval This is defined as the time interval from when the Controller started
its last LE scan until it begins the subsequent LE scan.
Time = N * 0.625 msec.
  * Values:
  - 0x0004 (2.500 ms)  ... 0x4000 (10240.000 ms) 
  * @param LE_Scan_Window Amount of time for the duration of the LE scan. LE_Scan_Window
shall be less than or equal to LE_Scan_Interval.
Time = N * 0.625 msec.
  * Values:
  - 0x0004 (2.500 ms)  ... 0x4000 (10240.000 ms) 
  * @param Own_Address_Type Own address type.
 - 0x00: Public Device Address
 - 0x01 Random Device Address
 - 0x02: Controller generates Resolvable Private Address based on the local
         IRK from resolving list. If resolving list contains no matching entry,
         use public address.
 - 0x03: Controller generates Resolvable Private Address based on the local
         IRK from resolving list. If resolving list contains no matching entry,
         use random address from LE_Set_Random_Address.
  * Values:
  - 0x00: Public Device Address
  - 0x01: Random Device Address
  - 0x02: Resolvable Private Address or Public Address
  - 0x03: Resolvable Private Address or Random Address
  * @param Scanning_Filter_Policy 0x00 Accept all advertisement packets.
Directed advertising packets which are not addressed for this device
shall be ignored.
0x01 Ignore advertisement packets from devices not in the White List Only.
Directed advertising packets which are not addressed for this device
shall be ignored
0x02 Accept all undirected advertisement packets.
Directed advertisement packets where initiator address is a RPA and 
Directed advertisement packets addressed to this device shall be accepted.
0x03 Accept all undirected advertisement packets from devices that are in
the White List.Directed advertisement packets where initiator address is RPA and Directed advertisement packets addressed to this device shall be accepted.
  * Values:
  - 0x00: Accept all
  - 0x01: Ignore devices not in the White List
  - 0x02: Accept all (use resolving list)
  - 0x03: Ignore devices not in the White List (use resolving list)
  * @retval Value indicating success or error code.
*/
tBleStatus hci_le_set_scan_parameters(uint8_t LE_Scan_Type,
                                      uint16_t LE_Scan_Interval,
                                      uint16_t LE_Scan_Window,
                                      uint8_t Own_Address_Type,
                                      uint8_t Scanning_Filter_Policy);
/**
  * @brief The LE_Set_Scan_Enable command is used to start scanning. Scanning is
used to discover advertising devices nearby.
The Filter_Duplicates parameter controls whether the Link Layer shall filter
duplicate advertising reports to the Host, or if the Link Layer should generate
advertising reports for each packet received.
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.8.11)
  * @param LE_Scan_Enable Enable/disable scan. Default is 0 (disabled).
  * Values:
  - 0x00: Scanning disabled
  - 0x01: Scanning enabled
  * @param Filter_Duplicates Enable/disable duplicate filtering.
  * Values:
  - 0x00: Duplicate filtering disabled
  - 0x01: Duplicate filtering enabled
  * @retval Value indicating success or error code.
*/
tBleStatus hci_le_set_scan_enable(uint8_t LE_Scan_Enable,
                                  uint8_t Filter_Duplicates);
/**
  * @brief The LE_Create_Connection command is used to create a Link Layer connection
to a connectable advertiser.
The LE_Scan_Interval and LE_Scan_Window parameters are recommendations
from the Host on how long (LE_Scan_Window) and how frequently
(LE_Scan_Interval) the Controller should scan. The LE_Scan_Window parameter
shall be set to a value smaller or equal to the value set for the LE_Scan_Interval
parameter. If both are set to the same value, scanning should run
continuously.
The Initiator_Filter_Policy is used to determine whether the White List is used.
If the White List is not used, the Peer_Address_Type and the Peer_Address
parameters specify the address type and address of the advertising device to
connect to.
The Link Layer shall set the address in the CONNECT_REQ packets to either
the Public Device Address or the Random Device Addressed based on the
Own_Address_Type parameter.
The Conn_Interval_Min and Conn_Interval_Max parameters define the minimum
and maximum allowed connection interval. The Conn_Interval_Min
parameter shall not be greater than the Conn_Interval_Max parameter.
The Conn_Latency parameter defines the maximum allowed connection
latency (see [Vol 6] Part B, Section 4.5.1).
The Supervision_Timeout parameter defines the link supervision timeout for
the connection. The Supervision_Timeout in milliseconds shall be larger than
(1 + Conn_Latency) * Conn_Interval_Max * 2, where Conn_Interval_Max is
given in milliseconds. (See [Vol 6] Part B, Section 4.5.2).
The Minimum_CE_Length and Maximum_CE_Length parameters are informative
parameters providing the Controller with the expected minimum and maximum
length of the connection events. The Minimum_CE_Length parameter
shall be less than or equal to the Maximum_CE_Length parameter.
The Host shall not issue this command when another LE_Create_Connection
is pending in the Controller; if this does occur the Controller shall return the
Command Disallowed error code shall be used.
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.8.12)
  * @param LE_Scan_Interval This is defined as the time interval from when the Controller started
its last LE scan until it begins the subsequent LE scan.
Time = N * 0.625 msec.
  * Values:
  - 0x0004 (2.500 ms)  ... 0x4000 (10240.000 ms) 
  * @param LE_Scan_Window Amount of time for the duration of the LE scan. LE_Scan_Window
shall be less than or equal to LE_Scan_Interval.
Time = N * 0.625 msec.
  * Values:
  - 0x0004 (2.500 ms)  ... 0x4000 (10240.000 ms) 
  * @param Initiator_Filter_Policy 0x00 White list is not used to determine which advertiser to connect to.
Peer_Address_Type and Peer_Address shall be used.
0x01 White list is used to determine which advertiser to connect to.
Peer_Address_Type and Peer_Address shall be ignored.
  * Values:
  - 0x00: White list not used
  - 0x01: White list used
  * @param Peer_Address_Type 0x00 Public Device Address
0x01 Random Device Address
0x02 Public Identity Address (Corresponds to Resolved Private Address)
0x03 Random (Static) Identity Address (Corresponds to Resolved Private Address)
  * Values:
  - 0x00: Public Device Address
  - 0x01: Random Device Address
  - 0x02: Public Identity Address
  - 0x03: Random (Static) Identity Address
  * @param Peer_Address Public Device Address, Random Device Address, Public Identity
Address or Random (static) Identity Address of the advertising
device.
  * @param Own_Address_Type Own address type.
 - 0x00: Public Device Address
 - 0x01 Random Device Address
 - 0x02: Controller generates Resolvable Private Address based on the local
         IRK from resolving list. If resolving list contains no matching entry,
         use public address.
 - 0x03: Controller generates Resolvable Private Address based on the local
         IRK from resolving list. If resolving list contains no matching entry,
         use random address from LE_Set_Random_Address.
  * Values:
  - 0x00: Public Device Address
  - 0x01: Random Device Address
  - 0x02: Resolvable Private Address or Public Address
  - 0x03: Resolvable Private Address or Random Address
  * @param Conn_Interval_Min Minimum value for the connection event interval. This shall be less
than or equal to Conn_Interval_Max.
Time = N * 1.25 msec.
  * Values:
  - 0x0006 (7.50 ms)  ... 0x0C80 (4000.00 ms) 
  * @param Conn_Interval_Max Maximum value for the connection event interval. This shall be
greater than or equal to Conn_Interval_Min.
Time = N * 1.25 msec.
  * Values:
  - 0x0006 (7.50 ms)  ... 0x0C80 (4000.00 ms) 
  * @param Conn_Latency Slave latency for the connection in number of connection events.
  * Values:
  - 0x0000 ... 0x01F3
  * @param Supervision_Timeout Supervision timeout for the LE Link.
It shall be a multiple of 10 ms and larger than (1 + connSlaveLatency) * connInterval * 2.
Time = N * 10 msec.
  * Values:
  - 0x000A (100 ms)  ... 0x0C80 (32000 ms) 
  * @param Minimum_CE_Length Information parameter about the minimum length of connection
needed for this LE connection.
Time = N * 0.625 msec.
  * @param Maximum_CE_Length Information parameter about the maximum length of connection needed
for this LE connection.
Time = N * 0.625 msec.
  * @retval Value indicating success or error code.
*/
tBleStatus hci_le_create_connection(uint16_t LE_Scan_Interval,
                                    uint16_t LE_Scan_Window,
                                    uint8_t Initiator_Filter_Policy,
                                    uint8_t Peer_Address_Type,
                                    uint8_t Peer_Address[6],
                                    uint8_t Own_Address_Type,
                                    uint16_t Conn_Interval_Min,
                                    uint16_t Conn_Interval_Max,
                                    uint16_t Conn_Latency,
                                    uint16_t Supervision_Timeout,
                                    uint16_t Minimum_CE_Length,
                                    uint16_t Maximum_CE_Length);
/**
  * @brief The LE_Create_Connection_Cancel command is used to cancel the LE_Create_Connection
command. This command shall only be issued after the
LE_Create_Connection command has been issued, a Command Status event
has been received for the LE Create Connection command and before the LE
Connection Complete event.
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.8.13)
  * @retval Value indicating success or error code.
*/
tBleStatus hci_le_create_connection_cancel(void);
/**
  * @brief The LE_Read_White_List_Size command is used to read the total number of
white list entries that can be stored in the Controller.
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.8.14)
  * @param[out] White_List_Size Total number of white list entries that can be stored in the Controller.
  * @retval Value indicating success or error code.
*/
tBleStatus hci_le_read_white_list_size(uint8_t *White_List_Size);
/**
  * @brief The LE_Clear_White_List command is used to clear the white list stored in the
Controller.
This command can be used at any time except when:
- the advertising filter policy uses the white list and advertising is enabled.
- the scanning filter policy uses the white list and scanning is enabled.
- the initiator filter policy uses the white list and an LE_Create_Connection
command is outstanding.
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.8.15)
  * @retval Value indicating success or error code.
*/
tBleStatus hci_le_clear_white_list(void);
/**
  * @brief The LE_Add_Device_To_White_List command is used to add a single device
to the white list stored in the Controller.
This command can be used at any time except when:
- the advertising filter policy uses the white list and advertising is enabled.
- the scanning filter policy uses the white list and scanning is enabled.
- the initiator filter policy uses the white list and a create connection command
is outstanding.
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.8.16)
  * @param Address_Type Address type.
  * Values:
  - 0x00: Public Device Address
  - 0x01: Random Device Address
  * @param Address Public Device Address or Random Device Address of the device
to be added to the white list.
  * @retval Value indicating success or error code.
*/
tBleStatus hci_le_add_device_to_white_list(uint8_t Address_Type,
                                           uint8_t Address[6]);
/**
  * @brief The LE_Remove_Device_From_White_List command is used to remove a single
device from the white list stored in the Controller.
This command can be used at any time except when:
- the advertising filter policy uses the white list and advertising is enabled.
- the scanning filter policy uses the white list and scanning is enabled.
- the initiator filter policy uses the white list and a create connection command
is outstanding.
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.8.17)
  * @param Address_Type Address type.
  * Values:
  - 0x00: Public Device Address
  - 0x01: Random Device Address
  * @param Address Public Device Address or Random Device Address of the device
to be removed from the white list.
  * @retval Value indicating success or error code.
*/
tBleStatus hci_le_remove_device_from_white_list(uint8_t Address_Type,
                                                uint8_t Address[6]);
/**
  * @brief The LE_Connection_Update command is used to change the Link Layer connection
parameters of a connection. This command is supported only on master side.
The Conn_Interval_Min and Conn_Interval_Max parameters are used to define
the minimum and maximum allowed connection interval. The Conn_Interval_Min
parameter shall not be greater than the Conn_Interval_Max parameter.
The Conn_Latency parameter shall define the maximum allowed connection
latency.
The Supervision_Timeout parameter shall define the link supervision timeout
for the LE link. The Supervision_Timeout in milliseconds shall be larger than (1
+ Conn_Latency) * Conn_Interval_Max * 2, where Conn_Interval_Max is given
in milliseconds.
The Minimum_CE_Length and Maximum_CE_Length are information parameters
providing the Controller with a hint about the expected minimum and maximum
length of the connection events. The Minimum_CE_Length shall be less
than or equal to the Maximum_CE_Length.
The actual parameter values selected by the Link Layer may be different from
the parameter values provided by the Host through this command.
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.8.18)
  * @param Connection_Handle Connection handle for which the command is given.
  * Values:
  - 0x0000 ... 0x0EFF
  * @param Conn_Interval_Min Minimum value for the connection event interval. This shall be less
than or equal to Conn_Interval_Max.
Time = N * 1.25 msec.
  * Values:
  - 0x0006 (7.50 ms)  ... 0x0C80 (4000.00 ms) 
  * @param Conn_Interval_Max Maximum value for the connection event interval. This shall be
greater than or equal to Conn_Interval_Min.
Time = N * 1.25 msec.
  * Values:
  - 0x0006 (7.50 ms)  ... 0x0C80 (4000.00 ms) 
  * @param Conn_Latency Slave latency for the connection in number of connection events.
  * Values:
  - 0x0000 ... 0x01F3
  * @param Supervision_Timeout Supervision timeout for the LE Link.
It shall be a multiple of 10 ms and larger than (1 + connSlaveLatency) * connInterval * 2.
Time = N * 10 msec.
  * Values:
  - 0x000A (100 ms)  ... 0x0C80 (32000 ms) 
  * @param Minimum_CE_Length Information parameter about the minimum length of connection
needed for this LE connection.
Time = N * 0.625 msec.
  * @param Maximum_CE_Length Information parameter about the maximum length of connection needed
for this LE connection.
Time = N * 0.625 msec.
  * @retval Value indicating success or error code.
*/
tBleStatus hci_le_connection_update(uint16_t Connection_Handle,
                                    uint16_t Conn_Interval_Min,
                                    uint16_t Conn_Interval_Max,
                                    uint16_t Conn_Latency,
                                    uint16_t Supervision_Timeout,
                                    uint16_t Minimum_CE_Length,
                                    uint16_t Maximum_CE_Length);
/**
  * @brief The LE_Set_Host_Channel_Classification command allows the Host to specify
a channel classification for data channels based on its "local information". This
classification persists until overwritten with a subsequent LE_Set_Host_Channel_Classification
command or until the Controller is reset using the Reset
command (see [Vol 6] Part B, Section 4.5.8.1).
If this command is used, the Host should send it within 10 seconds of knowing
that the channel classification has changed. The interval between two successive
commands sent shall be at least one second.
This command shall only be used when the local device supports the Master
role.
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.8.19)
  * @param LE_Channel_Map This parameter contains 37 1-bit fields.
The nth such field (in the range 0 to 36) contains the value for the
link layer channel index n.
Channel n is bad = 0.
Channel n is unknown = 1.
The most significant bits are reserved and shall be set to 0.
At least one channel shall be marked as unknown.
  * @retval Value indicating success or error code.
*/
tBleStatus hci_le_set_host_channel_classification(uint8_t LE_Channel_Map[5]);
/**
  * @brief The LE_Read_Channel_Map command returns the current Channel_Map for
the specified Connection_Handle. The returned value indicates the state of the
Channel_Map specified by the last transmitted or received Channel_Map (in a
CONNECT_REQ or LL_CHANNEL_MAP_REQ message) for the specified
Connection_Handle, regardless of whether the Master has received an
acknowledgement.
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.8.20)
  * @param Connection_Handle Connection handle for which the command is given.
  * Values:
  - 0x0000 ... 0x0EFF
  * @param[out] LE_Channel_Map This parameter contains 37 1-bit fields.
The nth such field (in the range 0 to 36) contains the value for the
link layer channel index n.
Channel n is unused = 0.
Channel n is used = 1.
The most significant bits are reserved and shall be set to 0.
  * @retval Value indicating success or error code.
*/
tBleStatus hci_le_read_channel_map(uint16_t Connection_Handle,
                                   uint8_t LE_Channel_Map[5]);
/**
  * @brief This command requests a list of the used LE features from the remote device.
This command shall return a list of the used LE features. For details see [Vol 6]
Part B, Section 4.6.
This command may be issued on both the master and slave.
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.8.21)
  * @param Connection_Handle Connection handle for which the command is given.
  * Values:
  - 0x0000 ... 0x0EFF
  * @retval Value indicating success or error code.
*/
tBleStatus hci_le_read_remote_used_features(uint16_t Connection_Handle);
/**
  * @brief The LE_Encrypt command is used to request the Controller to encrypt the
Plaintext_Data in the command using the Key given in the command and
returns the Encrypted_Data to the Host. The AES-128 bit block cypher is
defined in NIST Publication FIPS-197 (http://csrc.nist.gov/publications/fips/
fips197/fips-197.pdf).
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.8.22)
  * @param Key 128 bit key for the encryption of the data given in the command.
  * @param Plaintext_Data 128 bit data block that is requested to be encrypted.
  * @param[out] Encrypted_Data 128 bit encrypted data block.
  * @retval Value indicating success or error code.
*/
tBleStatus hci_le_encrypt(uint8_t Key[16],
                          uint8_t Plaintext_Data[16],
                          uint8_t Encrypted_Data[16]);
/**
  * @brief The LE_Rand command is used to request the Controller to generate 8 octets
of random data to be sent to the Host. The Random_Number shall be generated
according to [Vol 2] Part H, Section 2 if the LE Feature (LL Encryption) is
supported.
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.8.23)
  * @param[out] Random_Number Random Number
  * @retval Value indicating success or error code.
*/
tBleStatus hci_le_rand(uint8_t Random_Number[8]);
/**
  * @brief The LE_Start_Encryption command is used to authenticate the given encryption
key associated with the remote device specified by the connection handle,
and once authenticated will encrypt the connection. The parameters are as
defined in [Vol 3] Part H, Section 2.4.4.
If the connection is already encrypted then the Controller shall pause connection
encryption before attempting to authenticate the given encryption key, and
then re-encrypt the connection. While encryption is paused no user data shall
be transmitted.
On an authentication failure, the connection shall be automatically disconnected
by the Link Layer. If this command succeeds, then the connection shall
be encrypted.
This command shall only be used when the local device's role is Master.
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.8.24)
  * @param Connection_Handle Connection handle for which the command is given.
  * Values:
  - 0x0000 ... 0x0EFF
  * @param Random_Number 64 bit random number.
  * @param Encrypted_Diversifier 16 bit encrypted diversifier.
  * @param Long_Term_Key 128 bit long term key.
  * @retval Value indicating success or error code.
*/
tBleStatus hci_le_start_encryption(uint16_t Connection_Handle,
                                   uint8_t Random_Number[8],
                                   uint16_t Encrypted_Diversifier,
                                   uint8_t Long_Term_Key[16]);
/**
  * @brief The LE_Long_Term_Key_Request_Reply command is used to reply to an LE
Long Term Key Request event from the Controller, and specifies the
Long_Term_Key parameter that shall be used for this Connection_Handle. The
Long_Term_Key is used as defined in [Vol 6] Part B, Section 5.1.3.
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.8.25)
  * @param Connection_Handle Connection handle for which the command is given.
  * Values:
  - 0x0000 ... 0x0EFF
  * @param Long_Term_Key 128 bit long term key.
  * @retval Value indicating success or error code.
*/
tBleStatus hci_le_long_term_key_request_reply(uint16_t Connection_Handle,
                                              uint8_t Long_Term_Key[16]);
/**
  * @brief The LE_Long_Term_Key_Request_Negative_Reply command is used to reply
to an LE Long Term Key Request event from the Controller if the Host cannot
provide a Long Term Key for this Connection_Handle.
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.8.26)
  * @param Connection_Handle Connection handle for which the command is given.
  * Values:
  - 0x0000 ... 0x0EFF
  * @retval Value indicating success or error code.
*/
tBleStatus hci_le_long_term_key_requested_negative_reply(uint16_t Connection_Handle);
/**
  * @brief The LE_Read_Supported_States command reads the states and state combinations
that the link layer supports. See [Vol 6] Part B, Section 1.1.1.
LE_States is an 8-octet bit field. If a bit is set to 1 then this state or state combination
is supported by the Controller. Multiple bits in LE_States may be set to 1
to indicate support for multiple state and state combinations.
All the Advertising type with the Initiate State combinations shall be set only if
the corresponding Advertising types and Master Role combination are set.
All the Scanning types and the Initiate State combinations shall be set only if
the corresponding Scanning types and Master Role combination are set.
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.8.27)
  * @param[out] LE_States State or state combination is supported by the Controller.
See Core v4.1, Vol.2, part E, Ch. 7.8.27.
  * @retval Value indicating success or error code.
*/
tBleStatus hci_le_read_supported_states(uint8_t LE_States[8]);
/**
  * @brief The LE_Set_Data_Length command allows the Host to suggest maximum transmission packet size and maximum packet transmission time (connMaxTxOctets and connMaxTxTime - see [Vol 6] Part B, Section 4.5.10) to be used for a given connection. The Controller may use smaller or larger values based on local information.
  * @param Connection_Handle Connection_Handle to be used to identify a connection.
  * @param TxOctets Preferred maximum number of payload octets that the local Controller should include in a single Link Layer Data Channel PDU.
Range 0x001B-0x00FB (0x0000 - 0x001A and 0x00FC - 0xFFFF) Reserved for future use). Default: 27 bytes.
  * @param TxTime Preferred maximum number of microseconds that the local Controller should use to transmit a single Link Layer Data Channel PDU.
Range 0x0148-0x0848 (0x0000 - 0x0147 and 0x0849 - 0xFFFF Reserved for future use). Default: 328 bytes.
  * @retval Value indicating success or error code.
*/
tBleStatus hci_le_set_data_length(uint16_t Connection_Handle,
                                  uint16_t TxOctets,
                                  uint16_t TxTime);
/**
  * @brief The LE_Read_Suggested_Default_Data_Length command allows the Host to read the Host preferred values for the Controller maximum transmitted number of payload octets and maximum packet transmission time to be used for new connections (connInitialMaxTxOctets and connInitialMaxTxTime - see ([Vol 6] Part B, Section 4.5.10).
  * @param[out] SuggestedMaxTxOctets The Host suggested value for the Controller maximum transmitted number of payload octets to be used for new connections - connInitialMaxTxOctets.
Range 0x001B-0x00FB (0x0000 - 0x001A and 0x00FC - 0xFFFF Reserved for future use)
Default: 0x001B
  * @param[out] SuggestedMaxTxTime The Host suggested value for the Controller maximum packet transmission time to be used for new connections - connInitialMaxTx-Time.
Range 0x0148-0x0848 (0x0000 - 0x0147 and 0x0849 - 0xFFFF Reserved for future use)
Default: 0x0148
  * @retval Value indicating success or error code.
*/
tBleStatus hci_le_read_suggested_default_data_length(uint16_t *SuggestedMaxTxOctets,
                                                     uint16_t *SuggestedMaxTxTime);
/**
  * @brief The LE_Write_Suggested_Default_Data_Length command allows the Host to specify its preferred values for the Controller maximum transmission number of payload octets and maximum packet transmission time to be used for new connections (connInitialMaxTxOctets and connInitialMaxTxTime - see [Vol 6] Part B, Section 4.5.10). The Controller may use smaller or larger values based on local information.
  * @param SuggestedMaxTxOctets The Host suggested value for the Controller maximum transmitted number of payload octets to be used for new connections - connInitialMaxTxOctets.
Range 0x001B-0x00FB (0x0000 - 0x001A and 0x00FC - 0xFFFF Reserved for future use)
  * @param SuggestedMaxTxTime The Host suggested value for the Controller maximum packet transmission time to be used for new connections - connInitialMaxTx-Time.
Range 0x0148-0x0848 (0x0000 - 0x0147 and 0x0849 - 0xFFFF Reserved for future use)
  * @retval Value indicating success or error code.
*/
tBleStatus hci_le_write_suggested_default_data_length(uint16_t SuggestedMaxTxOctets,
                                                      uint16_t SuggestedMaxTxTime);
/**
  * @brief The LE_Read_Local_P-256_Public_Key command is used to return the local
P-256 public key from the Controller. The Controller shall generate a new P-256 public/private key pair upon receipt of this command.
(See Bluetooth Specification v.4.2, Vol. 2, Part E, 7.8.36)
  * @retval Value indicating success or error code.
*/
tBleStatus hci_le_read_local_p256_public_key(void);
/**
  * @brief The LE_Generate_DHKey command is used to initiate generation of a Diffie-
Hellman key in the Controller for use over the LE transport. This command
takes the remote P-256 public key as input. The Diffie-Hellman key generation
uses the private key generated by LE_Read_Local_P256_Public_Key command.
(See Bluetooth Specification v.4.2, Vol. 2, Part E, 7.8.37)
  * @param Remote_P256_Public_Key The remote P-256 public key:
X, Y format
Octets 31-0: X co-ordinate
Octets 63-32: Y co-ordinate
Little Endian Format
  * @retval Value indicating success or error code.
*/
tBleStatus hci_le_generate_dhkey(uint8_t Remote_P256_Public_Key[64]);
/**
  * @brief The LE_Add_Device_To_Resolving_List command is used to add one device
to the list of address translations used to resolve Resolvable Private Addresses
in the Controller.
This command cannot be used when address translation is enabled in the
Controller and:
- Advertising is enabled
- Scanning is enabled
- Create connection command is outstanding
This command can be used at any time when address translation is disabled in
the Controller.
When a Controller cannot add a device to the resolving list because the list is
full, it shall respond with error code 0x07 (Memory Capacity Exceeded).
(See Bluetooth Specification v.4.2, Vol. 2, Part E, 7.8.38)
  * @param Peer_Identity_Address_Type Identity address type.
  * Values:
  - 0x00: Public Identity Address
  - 0x01: Random (static) Identity Address
  * @param Peer_Identity_Address Public or Random (static) Identity address of the peer device
  * @param Peer_IRK IRK of the peer device
  * @param Local_IRK IRK of the local device
  * @retval Value indicating success or error code.
*/
tBleStatus hci_le_add_device_to_resolving_list(uint8_t Peer_Identity_Address_Type,
                                               uint8_t Peer_Identity_Address[6],
                                               uint8_t Peer_IRK[16],
                                               uint8_t Local_IRK[16]);
/**
  * @brief The LE_Remove_Device_From_Resolving_List command is used to remove
one device from the list of address translations used to resolve Resolvable
Private Addresses in the controller.
This command cannot be used when address translation is enabled in the
Controller and:
- Advertising is enabled
- Scanning is enabled
- Create connection command is outstanding
This command can be used at any time when address translation is disabled in
the Controller.
When a Controller cannot remove a device from the resolving list because it is
not found, it shall respond with error code 0x02 (Unknown Connection
Identifier).
(See Bluetooth Specification v.4.2, Vol. 2, Part E, 7.8.39)
  * @param Peer_Identity_Address_Type Identity address type.
  * Values:
  - 0x00: Public Identity Address
  - 0x01: Random (static) Identity Address
  * @param Peer_Identity_Address Public or Random (static) Identity address of the peer device
  * @retval Value indicating success or error code.
*/
tBleStatus hci_le_remove_device_from_resolving_list(uint8_t Peer_Identity_Address_Type,
                                                    uint8_t Peer_Identity_Address[6]);
/**
  * @brief The LE_Clear_Resolving_List command is used to remove all devices from the
list of address translations used to resolve Resolvable Private Addresses in the
Controller.
This command cannot be used when address translation is enabled in the
Controller and:
- Advertising is enabled
- Scanning is enabled
- Create connection command is outstanding
This command can be used at any time when address translation is disabled in
the Controller.
(See Bluetooth Specification v.4.2, Vol. 2, Part E, 7.8.40)
  * @retval Value indicating success or error code.
*/
tBleStatus hci_le_clear_resolving_list(void);
/**
  * @brief The LE_Read_Resolving_List_Size command is used to read the total number
of address translation entries in the resolving list that can be stored in the
Controller.
(See Bluetooth Specification v.4.2, Vol. 2, Part E, 7.8.41)
  * @param[out] Resolving_List_Size Number of address translation entries in the resolving list
  * @retval Value indicating success or error code.
*/
tBleStatus hci_le_read_resolving_list_size(uint8_t *Resolving_List_Size);
/**
  * @brief The LE_Read_Peer_Resolvable_Address command is used to get the current
peer Resolvable Private Address being used for the corresponding peer Public
and Random (static) Identity Address. The peer's resolvable address being
used may change after the command is called.
This command can be used at any time.
When a Controller cannot find a Resolvable Private Address associated with
the Peer Identity Address, it shall respond with error code 0x02 (Unknown
Connection Identifier).
(See Bluetooth Specification v.4.2, Vol. 2, Part E, 7.8.42)
  * @param Peer_Identity_Address_Type Identity address type.
  * Values:
  - 0x00: Public Identity Address
  - 0x01: Random (static) Identity Address
  * @param Peer_Identity_Address Public or Random (static) Identity address of the peer device
  * @param[out] Peer_Resolvable_Address Resolvable Private Address being used by the peer device
  * @retval Value indicating success or error code.
*/
tBleStatus hci_le_read_peer_resolvable_address(uint8_t Peer_Identity_Address_Type,
                                               uint8_t Peer_Identity_Address[6],
                                               uint8_t Peer_Resolvable_Address[6]);
/**
  * @brief The LE_Read_Local_Resolvable_Address command is used to get the current
local Resolvable Private Address being used for the corresponding peer
Identity Address. The local's resolvable address being used may change after
the command is called.
This command can be used at any time.
When a Controller cannot find a Resolvable Private Address associated with
the Peer Identity Address, it shall respond with error code 0x02 (Unknown
Connection Identifier).
(See Bluetooth Specification v.4.2, Vol. 2, Part E, 7.8.43)
  * @param Peer_Identity_Address_Type Identity address type.
  * Values:
  - 0x00: Public Identity Address
  - 0x01: Random (static) Identity Address
  * @param Peer_Identity_Address Public or Random (static) Identity address of the peer device
  * @param[out] Local_Resolvable_Address Resolvable Private Address being used by the local device
  * @retval Value indicating success or error code.
*/
tBleStatus hci_le_read_local_resolvable_address(uint8_t Peer_Identity_Address_Type,
                                                uint8_t Peer_Identity_Address[6],
                                                uint8_t Local_Resolvable_Address[6]);
/**
  * @brief The LE_Set_Address_Resolution_Enable command is used to enable
resolution of Resolvable Private Addresses in the Controller. This causes the
Controller to use the resolving list whenever the Controller receives a local or
peer Resolvable Private Address.
This command can be used at any time except when:
- Advertising is enabled
- Scanning is enabled
- Create connection command is outstanding
(See Bluetooth Specification v.4.2, Vol. 2, Part E, 7.8.44)
  * @param Address_Resolution_Enable Enable/disable address resolution in the controller.
0x00: Address Resolution in controller disabled (default),
0x01: Address Resolution in controller enabled
  * Values:
  - 0x00: Address Resolution in controller disabled (default)
  - 0x01: Address Resolution in controller enabled
  * @retval Value indicating success or error code.
*/
tBleStatus hci_le_set_address_resolution_enable(uint8_t Address_Resolution_Enable);
/**
  * @brief The LE_Set_Resolvable_Private_Address_Timeout command set the length of
time the controller uses a Resolvable Private Address before a new resolvable
private address is generated and starts being used.
This timeout applies to all addresses generated by the controller.
(See Bluetooth Specification v.4.2, Vol. 2, Part E, 7.8.45)
  * @param RPA_Timeout RPA_Timeout measured in seconds.
Range for N: 0x0001 - 0xA1B8 (1 sec - approximately 11.5 hours)
Default: N= 0x0384 (900 secs or 15 minutes)
  * @retval Value indicating success or error code.
*/
tBleStatus hci_le_set_resolvable_private_address_timeout(uint16_t RPA_Timeout);
/**
  * @brief The LE_Read_Maximum_Data_Length command allows the Host to read the Controller  maximum supported payload octets and packet duration times for transmission and reception (supportedMaxTxOctets and supportedMaxTxTime, supportedMaxRxOctets, and supportedMaxRxTime, see [Vol 6] Part B, Section 4.5.10). 
  * @param[out] supportedMaxTxOctets Maximum number of payload octets that the local Controller supports for transmission of a single Link Layer Data Channel PDU.
Range 0x001B-0x00FB (0x0000 - 0x001A and 0x00FC - 0xFFFF Reserved for future use)
  * @param[out] supportedMaxTxTime Maximum time, in microseconds, that the local Controller supports for transmission of a single Link Layer Data Channel PDU.
Range 0x0148-0x0848 (0x0000 - 0x0147 and 0x0849 - 0xFFFF Reserved for future use)
  * @param[out] supportedMaxRxOctets Maximum number of payload octets that the local Controller supports for reception of a single Link Layer Data Channel PDU.
Range 0x001B-0x00FB (0x0000 - 0x001A and 0x00FC - 0xFFFF Reserved for future use)
  * @param[out] supportedMaxRxTime Maximum time, in microseconds, that the local Controller supports for reception of a single Link Layer Data Channel PDU.
Range 0x0148-0x0848 (0x0000 - 0x0147 and 0x0849 - 0xFFFF Reserved for future use)
  * @retval Value indicating success or error code.
*/
tBleStatus hci_le_read_maximum_data_length(uint16_t *supportedMaxTxOctets,
                                           uint16_t *supportedMaxTxTime,
                                           uint16_t *supportedMaxRxOctets,
                                           uint16_t *supportedMaxRxTime);
/**
 * @}
 */
/**
 *@defgroup HCI_TESTING_API HCI TESTING API
 *@brief HCI TESTING API layer.
 *@{
 */
/**
  * @brief This command is used to start a test where the DUT receives test reference
packets at a fixed interval. The tester generates the test reference packets.
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.8.28)
  * @param RX_Frequency N = (F - 2402) / 2
Frequency Range : 2402 MHz to 2480 MHz
  * Values:
  - 0x00 ... 0x27
  * @retval Value indicating success or error code.
*/
tBleStatus hci_le_receiver_test(uint8_t RX_Frequency);
/**
  * @brief This command is used to start a test where the DUT generates test reference
packets at a fixed interval. The Controller shall transmit at maximum power.
An LE Controller supporting the LE_Transmitter_Test command shall support
Packet_Payload values 0x00, 0x01 and 0x02. An LE Controller may support
other values of Packet_Payload.
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.8.29)
  * @param TX_Frequency N = (F - 2402) / 2
                                Frequency Range : 2402 MHz to 2480 MHz
  * Values:
  - 0x00 ... 0x27
  * @param Length_Of_Test_Data Length in bytes of payload data in each packet.
    Supported ranges:
      - (0x00,0x25): BlueNRG-1 and BlueNRG-2 with BLE stack version < 2.1
      - (0x00,0xFF): BlueNRG-2 with BLE stack version >= 2.1 and extended packet length.
  * Values:
  - 0x00 ... 0xFF
  * @param Packet_Payload Type of packet payload.
  * Values:
  - 0x00: Pseudo-Random bit sequence 9
  - 0x01: Pattern of alternating bits '11110000'
  - 0x02: Pattern of alternating bits '10101010'
  - 0x03: Pseudo-Random bit sequence 15
  - 0x04: Pattern of All '1' bits
  - 0x05: Pattern of All '0' bits
  - 0x06: Pattern of alternating bits '00001111'
  - 0x07: Pattern of alternating bits '0101'
  * @retval Value indicating success or error code.
*/
tBleStatus hci_le_transmitter_test(uint8_t TX_Frequency,
                                   uint8_t Length_Of_Test_Data,
                                   uint8_t Packet_Payload);
/**
  * @brief This command is used to stop any test which is in progress. The Number_Of_Packets
for a transmitter test shall be reported as 0x0000. The Number_Of_Packets
is an unsigned number and contains the number of received
packets.
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.8.30)
  * @param[out] Number_Of_Packets Number of packets received
  * @retval Value indicating success or error code.
*/
tBleStatus hci_le_test_end(uint16_t *Number_Of_Packets);
/**
 * @}
 */
/**
 *@defgroup HAL_API HAL API
 *@brief HAL API layer.
 *@{
 */
/**
  * @brief This command returns the build number associated with the firmware version currently running
  * @param[out] Build_Number Build number of the firmware.
  * @retval Value indicating success or error code.
*/
tBleStatus aci_hal_get_fw_build_number(uint16_t *Build_Number);
/**
  * @brief This command writes a value to a low level configure data structure. It is useful to setup
directly some low level parameters for the system in the runtime.NOTE: This command shall not be called if a command different than Stack Init, HCI_RESET, ACI_HAL_WRITE_CONFIG_DATA or ACI_HAL_READ_CONFIG_DATA has already been called. 
  * @param Offset Offset of the element in the configuration data structure
which has to be written. The valid offsets are:

- 0x00: Bluetooth public address, Value length to be written: 6 bytes
- 0x06: DIV used to derive CSRK, Value length to be written: 2 bytes
- 0x08: Encryption root key used to derive LTK and CSRK, Value length to be written: 16 bytes
- 0x18: Identity root key used to derive LTK and CSRK, Value length to be written: 16 bytes
- 0x2C: Link layer without host (for certification purposes), Value length to be written: 1 byte
- 0x2E: If set, the stack uses this address as the static random address instead of the one stored in NVM.
- 0x2F: Disable watchdog (1=disable, 0=enable). Value length to be written: 1 byte
- 0xD1: Set the maximum allowed parameter values for Data Length Extension: 8 bytes, 2 bytes for each of the following parameters:
        supportedMaxTxOctets, supportedMaxTxTime, supportedMaxRxOctets, supportedMaxRxTime, in little-endian order.
        (default 251,2120,251,2120).
  * Values:
  - 0x00: CONFIG_DATA_PUBADDR_OFFSET
  - 0x06: CONFIG_DATA_DIV_OFFSET
  - 0x08: CONFIG_DATA_ER_OFFSET
  - 0x18: CONFIG_DATA_IR_OFFSET
  - 0x2C: LL_WITHOUT_HOST
  - 0x2E: CONFIG_DATA_STATIC_RANDOM_ADDRESS
  - 0x2F: CONFIG_DATA_WATCHDOG_DISABLE
  - 0xD1: CONFIG_DATA_DLE
  * @param Length Length of data to be written
  * @param Value Data to be written
  * @retval Value indicating success or error code.
*/
tBleStatus aci_hal_write_config_data(uint8_t Offset,
                                     uint8_t Length,
                                     uint8_t Value[]);
/**
  * @brief This command requests the value in the low level configure data structure.
The number of read bytes changes for different Offset. 
  * @param Offset Offset of the element in the configuration data structure
which has to be read. The valid offsets are:

* 0x00: Bluetooth public address, Value length returned: 6 bytes
* 0x06: DIV used to derive CSRK, Value length returned: 2 bytes
* 0x08: Encryption root key used to derive LTK and CSRK, Value length returned: 16 bytes
* 0x18: Identity root key used to derive LTK and CSRK, Value length returned: 16 bytes
* 0x2C: Link layer without host (for certification purposes), Value length returned: 1 byte
* 0x2F: Disable watchdog (1=disabled, 0=enable). Value length returned: 1 byte
* 0x80: The static random address stored in NVM. Value length returned: 6 bytes (read-only)
  * Values:
  - 0x00: CONFIG_DATA_PUBADDR_OFFSET
  - 0x06: CONFIG_DATA_DIV_OFFSET
  - 0x08: CONFIG_DATA_ER_OFFSET
  - 0x18: CONFIG_DATA_IR_OFFSET
  - 0x2C: LL_WITHOUT_HOST
  - 0x2F: CONFIG_DATA_WATCHDOG_DISABLE
  - 0x80: CONFIG_DATA_STORED_STATIC_RANDOM_ADDRESS
  * @param[out] Data_Length Length of Data in octets
  * @param[out] Data Data field associated with Offset parameter
  * @retval Value indicating success or error code.
*/
tBleStatus aci_hal_read_config_data(uint8_t Offset,
                                    uint8_t *Data_Length,
                                    uint8_t Data[]);
/**
  * @brief This command sets the TX power level of the device. By controlling the
EN_HIGH_POWER and the PA_LEVEL, the combination of the 2 determines the output
power level (dBm). 
When the system starts up or reboots, the default TX power level will be used, which is the
maximum value of 8 dBm. Once this command is given, the output power will be changed
instantly, regardless if there is Bluetooth communication going on or not. For example, for
debugging purpose, the device can be set to advertise all the time. And use this
command to observe the signal strength changing.
The system will keep the last received TX power level from the command, i.e. the 2nd
command overwrites the previous TX power level. The new TX power level remains until
another Set TX Power command, or the system reboots.
  * @param En_High_Power Enable High Power mode
  * Values:
  - 0x01: High Power
  * @param PA_Level Power amplifier output level. Output power is indicative and it depends on the PCB layout and associated components
  * Values:
  - 0x00: -14 dBm (High Power)
  - 0x01: -11 dBm (High Power)
  - 0x02: -8 dBm (High Power)
  - 0x03: -5 dBm (High Power)
  - 0x04: -2 dBm (High Power)
  - 0x05: 2 dBm (High Power)
  - 0x06: 4 dBm (High Power)
  - 0x07: 8 dBm (High Power)
  * @retval Value indicating success or error code.
*/
tBleStatus aci_hal_set_tx_power_level(uint8_t En_High_Power,
                                      uint8_t PA_Level);
/**
  * @brief This command returns the number of packets sent in Direct Test Mode.
When the Direct TX test is started, a 32-bit counter is used to count how many packets have been transmitted. 
This command can be used to check how many packets have been sent during the Direct TX test.
The counter starts from 0 and counts upwards. The counter can wrap and start from 0 again. 
The counter is not cleared until the next Direct TX test starts. 
  * @param[out] Number_Of_Packets Number of packets sent during the last Direct TX test.
  * @retval Value indicating success or error code.
*/
tBleStatus aci_hal_le_tx_test_packet_number(uint32_t *Number_Of_Packets);
/**
  * @brief This command starts a carrier frequency, i.e. a tone, on a specific channel. The frequency
sine wave at the specific channel may be used for debugging purpose only. The channel ID
is a parameter from 0x00 to 0x27 for the 40 BLE channels, e.g. 0x00 for 2.402 GHz, 0x01
for 2.404 GHz etc.
This command should not be used when normal Bluetooth activities are ongoing.
The tone should be stopped by @ref aci_hal_tone_stop command.
  * @param RF_Channel BLE Channel ID, from 0x00 to 0x27 meaning (2.402 + 2*0xXX) GHz.
  * Values:
  - 0x00 ... 0x27
  * @param Offset Specify if the tone must be emitted with an offset from the channel center frequency.  If 0, the tone is emitted at the channel center frequency.
If 1 or 2, the device will continuously emit the tone at the center frequency plus or minus 250 kHz respectively.
  * Values:
  - 0x00: 0 kHz offset
  - 0x01: +250 kHz offset
  - 0x02: -250 kHz offset
  * @retval Value indicating success or error code.
*/
tBleStatus aci_hal_tone_start(uint8_t RF_Channel,
                              uint8_t Offset);
/**
  * @brief This command is used to stop the previously started @ref aci_hal_tone_start command.
  * @retval Value indicating success or error code.
*/
tBleStatus aci_hal_tone_stop(void);
/**
  * @brief This command returns the status of the 8 Bluetooth low energy links managed by the device
  * @param[out] Link_Status Array of link status (8 links). Each link status is 1 byte.
  * @param[out] Link_Connection_Handle Array of connection handles (2 bytes) for 8 links.
  * @retval Value indicating success or error code.
*/
tBleStatus aci_hal_get_link_status(uint8_t Link_Status[8],
                                   uint16_t Link_Connection_Handle[16 / 2]);
/**
  * @brief This command set the bitmask associated to @ref aci_hal_end_of_radio_activity_event. 
Only the radio activities enabled in the mask will be reported to application by @ref aci_hal_end_of_radio_activity_event
  * @param Radio_Activity_Mask Bitmask of radio events
  * Flags:
  - 0x0001: Idle
  - 0x0002: Advertising
  - 0x0004: Connection event slave
  - 0x0008: Scanning
  - 0x0010: Connection request
  - 0x0020: Connection event master
  - 0x0040: TX test mode
  - 0x0080: RX test mode
  * @retval Value indicating success or error code.
*/
tBleStatus aci_hal_set_radio_activity_mask(uint16_t Radio_Activity_Mask);
/**
  * @brief This command returns information about the Anchor Period to help application in selecting 
                      slot timings when operating in multi-link scenarios.
  * @param[out] Anchor_Period Current anchor period.
T = N * 0.625 ms.
  * @param[out] Max_Free_Slot Maximum available time that can be allocated for a new slot.
T = N * 0.625 ms.
  * @retval Value indicating success or error code.
*/
tBleStatus aci_hal_get_anchor_period(uint32_t *Anchor_Period,
                                     uint32_t *Max_Free_Slot);
/**
  * @brief  
  * @param Event_Mask Mask to enable/disable generation of HAL events
  * Flags:
  - 0x00000000: No events specified (Default)
  - 0x00000001: ACI_HAL_SCAN_REQ_REPORT_EVENT
  * @retval Value indicating success or error code.
*/
tBleStatus aci_hal_set_event_mask(uint32_t Event_Mask);
/**
 * @}
 */
/**
 *@defgroup GAP_API GAP API
 *@brief GAP API layer.
 *@{
 */
/**
  * @brief Put the device in non-discoverable mode. This command disables the LL advertising.
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_set_non_discoverable(void);
/**
  * @brief Put the device in limited discoverable mode (as defined in Bluetooth Specification v.4.1,
Vol. 3, Part C, section 9.2.3). The device will be discoverable for maximum period of TGAP
(lim_adv_timeout) = 180 seconds (from errata). The advertising can be disabled at any time
by issuing @ref aci_gap_set_non_discoverable command.
The Adv_Interval_Min and Adv_Interval_Max parameters are optional. If both are set to 0,
the GAP will use default values for adv intervals for limited discoverable mode (250 ms
and 500 ms respectively).
To allow a fast connection, the host can set Local_Name, Service_Uuid_List,
Slave_Conn_Interval_Min and Slave_Conn_Interval_Max. If provided, these data will be 
inserted into the advertising packet payload as AD data. These parameters are optional
in this command. These values can be set in advertised data using GAP_Update_Adv_Data
command separately.
The total size of data in advertising packet cannot exceed 31 bytes.
With this command, the BLE Stack will also add automatically the following
standard AD types:
- AD Flags
- Power Level
When advertising timeout happens (i.e. limited discovery period has elapsed), controller generates
@ref aci_gap_limited_discoverable_event event. 
  * @param Advertising_Type Advertising type. Advertising_Type type cannot be any of GAP_ADV_HIGH_DC_DIRECT_IND or GAP_ADV_HIGH_DC_DIRECT_IND.
  * Values:
  - 0x00: ADV_IND (Connectable undirected advertising)
  - 0x01: ADV_DIRECT_IND (Connectable directed advertising)
  - 0x02: ADV_SCAN_IND (Scannable undirected advertising)
  - 0x03: ADV_NONCONN_IND (Non connectable undirected advertising)
  * @param Advertising_Interval_Min Minimum advertising interval.
Time = N * 0.625 msec.
  * Values:
  - 0x0020 (20.000 ms)  ... 0x4000 (10240.000 ms) 
  * @param Advertising_Interval_Max Maximum advertising interval.
Time = N * 0.625 msec.
  * Values:
  - 0x0020 (20.000 ms)  ... 0x4000 (10240.000 ms) 
  * @param Own_Address_Type Own address type:
 - 0x00: Public Device Address (it is allowed only if privacy is disabled)
 - 0x01: Random Device Address (it is allowed only if privacy is disabled)
 - 0x02: Resolvable Private Address (it is allowed only if privacy is enabled)
 - 0x03: Non Resolvable Private Address (it is allowed only if privacy is enabled)
  * Values:
  - 0x00: Public Device Address 
  - 0x01: Random Device Address 
  - 0x02: Resolvable Private Address
  - 0x03: Non Resolvable Private Address
  * @param Advertising_Filter_Policy Advertising filter policy: not applicable (the value of Advertising_Filter_Policy parameter is not used inside the Stack)
  * @param Local_Name_Length Length of the local_name field in octets.
If length is set to 0x00, Local_Name parameter is not used.
  * @param Local_Name Local name of the device. First byte must be 0x08 for Shortened Local Name 
or 0x09 for Complete Local Name. No NULL character at the end.
  * @param Service_Uuid_length Length of the Service Uuid List in octets.
If there is no service to be advertised, set this field to 0x00.
  * @param Service_Uuid_List This is the list of the UUIDs as defined in Volume 3,
Section 11 of GAP Specification. First byte is the AD Type.
See also Supplement to the Bluetooth Core specification.
  * @param Slave_Conn_Interval_Min Slave connection interval minimum value suggested by Peripheral.
If Slave_Conn_Interval_Min and Slave_Conn_Interval_Max are not 0x0000,
Slave Connection Interval Range AD structure will be added in advertising
data.
Connection interval is defined in the following manner:
connIntervalmin = Slave_Conn_Interval_Min x 1.25ms.
  * Values:
  - 0x0000 (NaN) 
  - 0xFFFF (NaN) : No specific minimum
  - 0x0006 (7.50 ms)  ... 0x0C80 (4000.00 ms) 
  * @param Slave_Conn_Interval_Max Slave connection interval maximum value suggested by Peripheral.
If Slave_Conn_Interval_Min and Slave_Conn_Interval_Max are not 0x0000,
Slave Connection Interval Range AD structure will be added in advertising
data.
Connection interval is defined in the following manner:
connIntervalmax = Slave_Conn_Interval_Max x 1.25ms
  * Values:
  - 0x0000 (NaN) 
  - 0xFFFF (NaN) : No specific maximum
  - 0x0006 (7.50 ms)  ... 0x0C80 (4000.00 ms) 
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_set_limited_discoverable(uint8_t Advertising_Type,
                                            uint16_t Advertising_Interval_Min,
                                            uint16_t Advertising_Interval_Max,
                                            uint8_t Own_Address_Type,
                                            uint8_t Advertising_Filter_Policy,
                                            uint8_t Local_Name_Length,
                                            uint8_t Local_Name[],
                                            uint8_t Service_Uuid_length,
                                            uint8_t Service_Uuid_List[],
                                            uint16_t Slave_Conn_Interval_Min,
                                            uint16_t Slave_Conn_Interval_Max);
/**
  * @brief Put the device in general discoverable mode (as defined in Bluetooth Specification v.4.1,
Vol. 3, Part C, section 9.2.4). The device will be discoverable until the host issues 
the @ref aci_gap_set_non_discoverable command. The Adv_Interval_Min and Adv_Interval_Max
parameters are optional. If both are set to 0, the GAP uses the default values for adv
intervals for general discoverable mode.
When using connectable undirected advertising events:
- Adv_Interval_Min = 30 ms 
- Adv_Interval_Max = 60 ms
When using non-connectable advertising events or scannable undirected advertising events:
- Adv_Interval_Min = 100 ms 
- Adv_Interval_Max = 150 ms 
Host can set the Local Name, a Service UUID list and the Slave Connection Interval Range.
If provided, these data will be inserted into the advertising packet payload as AD data.
These parameters are optional in this command. These values can be also set using
aci_gap_update_adv_data() separately.
The total size of data in advertising packet cannot exceed 31 bytes.
With this command, the BLE Stack will also add automatically the following standard
AD types:
- AD Flags
- TX Power Level
  * @param Advertising_Type Advertising type. Advertising_Type type cannot be any of GAP_ADV_HIGH_DC_DIRECT_IND or GAP_ADV_HIGH_DC_DIRECT_IND.
  * Values:
  - 0x00: ADV_IND (Connectable undirected advertising)
  - 0x01: ADV_DIRECT_IND (Connectable directed advertising)
  - 0x02: ADV_SCAN_IND (Scannable undirected advertising)
  - 0x03: ADV_NONCONN_IND (Non connectable undirected advertising)
  * @param Advertising_Interval_Min Minimum advertising interval.
Time = N * 0.625 msec.
  * Values:
  - 0x0020 (20.000 ms)  ... 0x4000 (10240.000 ms) 
  * @param Advertising_Interval_Max Maximum advertising interval.
Time = N * 0.625 msec.
  * Values:
  - 0x0020 (20.000 ms)  ... 0x4000 (10240.000 ms) 
  * @param Own_Address_Type Own address type:
 - 0x00: Public Device Address (it is allowed only if privacy is disabled)
 - 0x01: Random Device Address (it is allowed only if privacy is disabled)
 - 0x02: Resolvable Private Address (it is allowed only if privacy is enabled)
 - 0x03: Non Resolvable Private Address (it is allowed only if privacy is enabled)
  * Values:
  - 0x00: Public Device Address 
  - 0x01: Random Device Address 
  - 0x02: Resolvable Private Address
  - 0x03: Non Resolvable Private Address
  * @param Advertising_Filter_Policy Advertising filter policy: not applicable (the value of Advertising_Filter_Policy parameter is not used inside the Stack)
  * @param Local_Name_Length Length of the local_name field in octets.
If length is set to 0x00, Local_Name parameter is not used.
  * @param Local_Name Local name of the device. First byte must be 0x08 for Shortened Local Name 
or 0x09 for Complete Local Name. No NULL character at the end.
  * @param Service_Uuid_length Length of the Service Uuid List in octets.
If there is no service to be advertised, set this field to 0x00.
  * @param Service_Uuid_List This is the list of the UUIDs as defined in Volume 3,
Section 11 of GAP Specification. First byte is the AD Type.
See also Supplement to the Bluetooth Core specification.
  * @param Slave_Conn_Interval_Min Slave connection interval minimum value suggested by Peripheral.
If Slave_Conn_Interval_Min and Slave_Conn_Interval_Max are not 0x0000,
Slave Connection Interval Range AD structure will be added in advertising
data.
Connection interval is defined in the following manner:
connIntervalmin = Slave_Conn_Interval_Min x 1.25ms.
  * Values:
  - 0x0000 (NaN) 
  - 0xFFFF (NaN) : No specific minimum
  - 0x0006 (7.50 ms)  ... 0x0C80 (4000.00 ms) 
  * @param Slave_Conn_Interval_Max Slave connection interval maximum value suggested by Peripheral.
If Slave_Conn_Interval_Min and Slave_Conn_Interval_Max are not 0x0000,
Slave Connection Interval Range AD structure will be added in advertising
data.
Connection interval is defined in the following manner:
connIntervalmax = Slave_Conn_Interval_Max x 1.25ms
  * Values:
  - 0x0000 (NaN) 
  - 0xFFFF (NaN) : No specific maximum
  - 0x0006 (7.50 ms)  ... 0x0C80 (4000.00 ms) 
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_set_discoverable(uint8_t Advertising_Type,
                                    uint16_t Advertising_Interval_Min,
                                    uint16_t Advertising_Interval_Max,
                                    uint8_t Own_Address_Type,
                                    uint8_t Advertising_Filter_Policy,
                                    uint8_t Local_Name_Length,
                                    uint8_t Local_Name[],
                                    uint8_t Service_Uuid_length,
                                    uint8_t Service_Uuid_List[],
                                    uint16_t Slave_Conn_Interval_Min,
                                    uint16_t Slave_Conn_Interval_Max);
/**
  * @brief 
    Set the device in direct connectable mode (as defined in Bluetooth Specification v.4.1,
Vol. 3, Part C, section 9.3.3). Device uses direct connectable mode to advertise using High Duty
cycle advertisement events or Low Duty cycle advertisement events and the address as
either what is specified in the Own Address Type parameter. The command specifies the type of the advertising used.
If the privacy is enabled, the Type parameter in reconnection address is used for advertising, otherwise the address
of the type specified in OwnAddrType is used.
The device will be in directed connectable mode only for 1.28 seconds. If no connection
is established within this duration, the device enters non discoverable mode and
advertising will have to be again enabled explicitly.
The controller generates a @ref hci_le_connection_complete_event event with the status set to
0x3C (Directed Advertising Timeout) if the connection was not established and 0x00 if the
connection was successfully established.
If Host privacy (i.e. privacy 1.1) is enabled this command returns BLE_STATUS_INVALID_PARAMS.
  * @param Own_Address_Type Own address type:
 - 0x00: Public Device Address (only if privacy is disabled)
 - 0x01: Random Device Address (only if privacy is disabled)
 - 0x02: Resolvable Private Address (only if privacy is enabled)
  * Values:
  - 0x00: Public Device Address 
  - 0x01: Random Device Address 
  - 0x02: Resolvable Private Address
  * @param Directed_Advertising_Type Type of directed advertising.
  * Values:
  - 0x01: High Duty Cycle Directed Advertising
  - 0x04: Low Duty Cycle Directed Advertising
  * @param Direct_Address_Type Peer Address type.
  * Values:
  - 0x00: Public Device Address or Public Identity Address
  - 0x01: Random Device Address or Random (static) Identity Address
  * @param Direct_Address Initiator Bluetooth address
  * @param Advertising_Interval_Min Minimum advertising interval.
Time = N * 0.625 msec.
  * Values:
  - 0x0020 (20.000 ms)  ... 0x4000 (10240.000 ms) 
  * @param Advertising_Interval_Max Maximum advertising interval.
Time = N * 0.625 msec.
  * Values:
  - 0x0020 (20.000 ms)  ... 0x4000 (10240.000 ms) 
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_set_direct_connectable(uint8_t Own_Address_Type,
                                          uint8_t Directed_Advertising_Type,
                                          uint8_t Direct_Address_Type,
                                          uint8_t Direct_Address[6],
                                          uint16_t Advertising_Interval_Min,
                                          uint16_t Advertising_Interval_Max);
/**
  * @brief Set the IO capabilities of the device. This command has to be given only when the device is
not in a connected state.

  * @param IO_Capability IO capability of the device.
  * Values:
  - 0x00: IO_CAP_DISPLAY_ONLY
  - 0x01: IO_CAP_DISPLAY_YES_NO
  - 0x02: IO_CAP_KEYBOARD_ONLY
  - 0x03: IO_CAP_NO_INPUT_NO_OUTPUT
  - 0x04: IO_CAP_KEYBOARD_DISPLAY
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_set_io_capability(uint8_t IO_Capability);
/**
  * @brief Set the authentication requirements for the device. This command has to be
given only when the device is not in a connected state.
  * @param Bonding_Mode Bonding mode.
Only if bonding is enabled (0x01), the bonding
information is stored in flash
  * Values:
  - 0x00: No-bonding mode
  - 0x01: Bonding mode
  * @param MITM_Mode MITM mode.
  * Values:
  - 0x00: MITM protection not required
  - 0x01: MITM protection required
  * @param SC_Support LE Secure connections support
  * Values:
  - 0x00: Secure Connections Pairing not supported
  - 0x01: Secure Connections Pairing supported but optional
  - 0x02: Secure Connections Pairing supported and mandatory (SC Only Mode)
  * @param KeyPress_Notification_Support Keypress notification support
  * Values:
  - 0x00: Keypress notification not supported
  - 0x01: Keypress notification supported
  * @param Min_Encryption_Key_Size Minimum encryption key size to be used during pairing
  * @param Max_Encryption_Key_Size Maximum encryption key size to be used during pairing
  * @param Use_Fixed_Pin Use or not fixed pin. If set to 0x00, then during the pairing process
the application will not be requested for a pin (Fixed_Pin will be used).
If set to 0x01, then during pairing process if a
passkey is required the application will be
notified
  * Values:
  - 0x00: use a fixed pin
  - 0x01: do not use a fixed pin
  * @param Fixed_Pin Fixed pin to be used during pairing if MIMT protection is enabled.
Any random value between 0 to 999999
  * Values:
  - 0 ... 999999
  * @param Identity_Address_Type Identity address type.
  * Values:
  - 0x00: Public Identity Address
  - 0x01: Random (static) Identity Address
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_set_authentication_requirement(uint8_t Bonding_Mode,
                                                  uint8_t MITM_Mode,
                                                  uint8_t SC_Support,
                                                  uint8_t KeyPress_Notification_Support,
                                                  uint8_t Min_Encryption_Key_Size,
                                                  uint8_t Max_Encryption_Key_Size,
                                                  uint8_t Use_Fixed_Pin,
                                                  uint32_t Fixed_Pin,
                                                  uint8_t Identity_Address_Type);
/**
  * @brief Set the authorization requirements of the device. This command has to be given when connected
to a device if authorization is required to access services which require authorization.
  * @param Connection_Handle Connection handle for which the command is given.
  * Values:
  - 0x0000 ... 0x0EFF
  * @param Authorization_Enable Enable the authorization in the device
and when a remote device tries to read/write a characteristic with authorization
requirements, the stack will send back an error response with
"Insufficient authorization" error code. After pairing is complete a
ACI_GAP_AUTHORIZATION_REQ_EVENT will be sent to the Host.
  * Values:
  - 0x00: Authorization not required
  - 0x01: Authorization required
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_set_authorization_requirement(uint16_t Connection_Handle,
                                                 uint8_t Authorization_Enable);
/**
  * @brief This command should be send by the host in response to @ref aci_gap_pass_key_req_event
event. The command parameter contains the pass key which will be used during the pairing
process.
  * @param Connection_Handle Connection handle for which the command is given.
  * Values:
  - 0x0000 ... 0x0EFF
  * @param Pass_Key Pass key that will be used during the pairing process. 
Must be a six-digit decimal number.
  * Values:
  - 0 ... 999999
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_pass_key_resp(uint16_t Connection_Handle,
                                 uint32_t Pass_Key);
/**
  * @brief Authorize a device to access attributes. This command should be send by the host in
response to @ref aci_gap_authorization_req_event event.
  * @param Connection_Handle Connection handle for which the command is given.
  * Values:
  - 0x0000 ... 0x0EFF
  * @param Authorize Authorization response.
  * Values:
  - 0x01: Authorize
  - 0x02: Reject
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_authorization_resp(uint16_t Connection_Handle,
                                      uint8_t Authorize);
/**
  * @brief Initialize the GAP layer. Register the GAP service with the GATT.
All the standard GAP characteristics will also be added:
- Device Name
- Appearance
- Peripheral Preferred Connection Parameters (peripheral role only)
  * @param Role Bitmap of allowed roles.
  * Flags:
  - 0x01: Peripheral
  - 0x02: Broadcaster
  - 0x04: Central
  - 0x08: Observer
  * @param privacy_enabled Specify if privacy is enabled or not and which one .
  * Values:
  - 0x00: Privacy disabled
  - 0x01: Privacy host enabled
  - 0x02: Privacy controller enabled
  * @param device_name_char_len Length of the device name characteristic
  * @param[out] Service_Handle Handle of the GAP service
  * @param[out] Dev_Name_Char_Handle Device Name Characteristic handle
  * @param[out] Appearance_Char_Handle Appearance Characteristic handle
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_init(uint8_t Role,
                        uint8_t privacy_enabled,
                        uint8_t device_name_char_len,
                        uint16_t *Service_Handle,
                        uint16_t *Dev_Name_Char_Handle,
                        uint16_t *Appearance_Char_Handle);
/**
  * @brief Put the device into non connectable mode. This mode does not support connection. The
privacy setting done in the @ref aci_gap_init command plays a role in deciding the valid 
parameters for this command.
Advertiser filter policy is internally set to 0x00
  * @param Advertising_Event_Type Advertising type.
  * Values:
  - 0x02: ADV_SCAN_IND (Scannable undirected advertising)
  - 0x03: ADV_NONCONN_IND (Non connectable undirected advertising)
  * @param Own_Address_Type Own address type:
 - 0x00: Public Device Address (it is allowed only if privacy is disabled)
 - 0x01: Random Device Address (it is allowed only if privacy is disabled)
 - 0x02: Resolvable Private Address (it is allowed only if privacy is enabled)
 - 0x03: Non Resolvable Private Address (it is allowed only if privacy is enabled)
  * Values:
  - 0x00: Public Device Address 
  - 0x01: Random Device Address 
  - 0x02: Resolvable Private Address
  - 0x03: Non Resolvable Private Address
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_set_non_connectable(uint8_t Advertising_Event_Type,
                                       uint8_t Own_Address_Type);
/**
  * @brief Put the device into undirected connectable mode.
If privacy is enabled in the device, a resolvable private address is generated and used as the 
advertiser's address. If not, the address of the type specified in own_addr_type is used for
advertising.
  * @param Advertising_Interval_Min Minimum advertising interval.
Time = N * 0.625 msec.
  * Values:
  - 0x0020 (20.000 ms)  ... 0x4000 (10240.000 ms) 
  * @param Advertising_Interval_Max Maximum advertising interval.
Time = N * 0.625 msec.
  * Values:
  - 0x0020 (20.000 ms)  ... 0x4000 (10240.000 ms) 
  * @param Own_Address_Type Own address type:
 - 0x00: Public Device Address (it is allowed only if privacy is disabled)
 - 0x01: Random Device Address (it is allowed only if privacy is disabled)
 - 0x02: Resolvable Private Address (it is allowed only if controller privacy is enabled or if Host privacy (i.e. privacy 1.1) is enabled)
 - 0x03: Non Resolvable Private Address (it is allowed only if Host privacy (i.e. privacy 1.1) is enabled)
  * Values:
  - 0x00: Public Device Address 
  - 0x01: Random Device Address 
  - 0x02: Resolvable Private Address
  - 0x03: Non Resolvable Private Address
  * @param Adv_Filter_Policy Advertising filter policy.
  * Values:
  - 0x00: Allow Scan Request from Any, Allow Connect Request from Any
  - 0x03: Allow Scan Request from White List Only, Allow Connect Request from White List Only
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_set_undirected_connectable(uint16_t Advertising_Interval_Min,
                                              uint16_t Advertising_Interval_Max,
                                              uint8_t Own_Address_Type,
                                              uint8_t Adv_Filter_Policy);
/**
  * @brief Send a slave security request to the master.
This command has to be issued to notify the master of the security requirements of the slave.
The master may encrypt the link, initiate the pairing procedure, or reject the request.
  * @param Connection_Handle Connection handle for which the command is given.
  * Values:
  - 0x0000 ... 0x0EFF
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_slave_security_req(uint16_t Connection_Handle);
/**
  * @brief This command can be used to update the advertising data for a particular AD type. If the AD
type specified does not exist, then it is added to the advertising data. If the overall
advertising data length is more than 31 octets after the update, then the command is
rejected and the old data is retained.
  * @param AdvDataLen Length of AdvData in octets
  * @param AdvData Advertising data used by the device while advertising.
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_update_adv_data(uint8_t AdvDataLen,
                                   uint8_t AdvData[]);
/**
  * @brief This command can be used to delete the specified AD type from the advertisement data if
present.
  * @param ADType One of the AD types like in Bluetooth specification (see volume 3, Part C, 11.1)
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_delete_ad_type(uint8_t ADType);
/**
  * @brief This command can be used to get the current security settings of the device.
  * @param Connection_Handle Connection handle for which the command is given.
  * Values:
  - 0x0000 ... 0x0EFF
  * @param[out] Security_Mode Security mode.
  * Values:
  - 0x01: Security Mode 1
  - 0x02: Security Mode 2
  * @param[out] Security_Level Security Level.
  * Values:
  - 0x01: Security Level 1
  - 0x02: Security Level 2
  - 0x03: Security Level 3
  - 0x04: Security Level 4
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_get_security_level(uint16_t Connection_Handle,
                                      uint8_t *Security_Mode,
                                      uint8_t *Security_Level);
/**
  * @brief It allows masking events from the GAP. The default configuration is all the events masked.
  * @param GAP_Evt_Mask GAP event mask. Default: 0xFFFF.
  * Flags:
  - 0x0000: No events
  - 0x0001: ACI_GAP_LIMITED_DISCOVERABLE_EVENT
  - 0x0002: ACI_GAP_PAIRING_COMPLETE_EVENT
  - 0x0004: ACI_GAP_PASS_KEY_REQ_EVENT
  - 0x0008: ACI_GAP_AUTHORIZATION_REQ_EVENT
  - 0x0010: ACI_GAP_SLAVE_SECURITY_INITIATED_EVENT
  - 0x0020: ACI_GAP_BOND_LOST_EVENT
  - 0x0080: ACI_GAP_PROC_COMPLETE_EVENT
  - 0x0100: ACI_L2CAP_CONNECTION_UPDATE_REQ_EVENT
  - 0x0200: ACI_L2CAP_CONNECTION_UPDATE_RESP_EVENT
  - 0x0400: ACI_L2CAP_PROC_TIMEOUT_EVENT
  - 0x0800: ACI_GAP_ADDR_NOT_RESOLVED_EVENT
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_set_event_mask(uint16_t GAP_Evt_Mask);
/**
  * @brief Add addresses of bonded devices into the controller's whitelist.
The command will return an error if there are no devices in the database or if it was  
unable to add the device into the whitelist.
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_configure_whitelist(void);
/**
  * @brief Command the controller to terminate the connection.
A @ref hci_disconnection_complete_event event will be generated when the link is disconnected. It is important to leave an 100 ms blank window
before sending any new command (including system hardware reset), since immediately after @ref hci_disconnection_complete_event event,
system could save important information in non volatile memory.
  * @param Connection_Handle Connection handle for which the command is given.
  * Values:
  - 0x0000 ... 0x0EFF
  * @param Reason The reason for ending the connection.
  * Values:
  - 0x05: Authentication Failure
  - 0x13: Remote User Terminated Connection
  - 0x14: Remote Device Terminated Connection due to Low Resources
  - 0x15: Remote Device Terminated Connection due to Power Off
  - 0x1A: Unsupported Remote Feature
  - 0x3B: Unacceptable Connection Parameters
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_terminate(uint16_t Connection_Handle,
                             uint8_t Reason);
/**
  * @brief Clear the security database. All the devices in the security database will be removed.
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_clear_security_db(void);
/**
  * @brief Allows the security manager to complete the pairing procedure and re-bond with the master.
This command should be given by the application when it receives the
ACI_GAP_BOND_LOST_EVENT if it wants the re-bonding to happen successfully. If this
command is not given on receiving the event, the bonding procedure will timeout.
  * @param Connection_Handle Connection handle for which the command is given.
  * Values:
  - 0x0000 ... 0x0EFF
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_allow_rebond(uint16_t Connection_Handle);
/**
  * @brief Start the limited discovery procedure. The controller is commanded to start active scanning.
When this procedure is started, only the devices in limited discoverable mode are returned
to the upper layers.
The procedure is terminated when either the upper layers issue a command to terminate 
the procedure by issuing the command @ref aci_gap_terminate_gap_proc with the procedure 
code set to 0x01 or a timeout happens. When the procedure is terminated due to any of the 
above  reasons, @ref aci_gap_proc_complete_event event is returned with the procedure code
set to 0x01.
The device found when the procedure is ongoing is returned to the upper layers through the
event @ref hci_le_advertising_report_event.
  * @param LE_Scan_Interval This is defined as the time interval from when the Controller started
its last LE scan until it begins the subsequent LE scan.
Time = N * 0.625 msec.
  * Values:
  - 0x0004 (2.500 ms)  ... 0x4000 (10240.000 ms) 
  * @param LE_Scan_Window Amount of time for the duration of the LE scan. LE_Scan_Window
shall be less than or equal to LE_Scan_Interval.
Time = N * 0.625 msec.
  * Values:
  - 0x0004 (2.500 ms)  ... 0x4000 (10240.000 ms) 
  * @param Own_Address_Type Own address type:
 - 0x00: Public Device Address (it is allowed only if privacy is disabled)
 - 0x01: Random Device Address (it is allowed only if privacy is disabled)
 - 0x02: Resolvable Private Address (it is allowed only if privacy is enabled)
 - 0x03: Non Resolvable Private Address (it is allowed only if privacy is enabled)
  * Values:
  - 0x00: Public Device Address 
  - 0x01: Random Device Address 
  - 0x02: Resolvable Private Address
  - 0x03: Non Resolvable Private Address
  * @param Filter_Duplicates Enable/disable duplicate filtering.
  * Values:
  - 0x00: Duplicate filtering disabled
  - 0x01: Duplicate filtering enabled
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_start_limited_discovery_proc(uint16_t LE_Scan_Interval,
                                                uint16_t LE_Scan_Window,
                                                uint8_t Own_Address_Type,
                                                uint8_t Filter_Duplicates);
/**
  * @brief Start the general discovery procedure. The controller is commanded to start active
scanning. The procedure is terminated when  either the upper layers issue a command
to terminate the procedure by issuing the command @ref aci_gap_terminate_gap_proc
with the procedure code set to 0x02 or a timeout happens. When the procedure is
terminated due to any of the above reasons, @ref aci_gap_proc_complete_event event
is returned with the procedure code set to 0x02. The device found when the procedure
is ongoing is returned to @ref hci_le_advertising_report_event.
  * @param LE_Scan_Interval This is defined as the time interval from when the Controller started
its last LE scan until it begins the subsequent LE scan.
Time = N * 0.625 msec.
  * Values:
  - 0x0004 (2.500 ms)  ... 0x4000 (10240.000 ms) 
  * @param LE_Scan_Window Amount of time for the duration of the LE scan. LE_Scan_Window
shall be less than or equal to LE_Scan_Interval.
Time = N * 0.625 msec.
  * Values:
  - 0x0004 (2.500 ms)  ... 0x4000 (10240.000 ms) 
  * @param Own_Address_Type Own address type:
 - 0x00: Public Device Address (it is allowed only if privacy is disabled)
 - 0x01: Random Device Address (it is allowed only if privacy is disabled)
 - 0x02: Resolvable Private Address (it is allowed only if privacy is enabled)
 - 0x03: Non Resolvable Private Address (it is allowed only if privacy is enabled)
  * Values:
  - 0x00: Public Device Address 
  - 0x01: Random Device Address 
  - 0x02: Resolvable Private Address
  - 0x03: Non Resolvable Private Address
  * @param Filter_Duplicates Enable/disable duplicate filtering.
  * Values:
  - 0x00: Duplicate filtering disabled
  - 0x01: Duplicate filtering enabled
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_start_general_discovery_proc(uint16_t LE_Scan_Interval,
                                                uint16_t LE_Scan_Window,
                                                uint8_t Own_Address_Type,
                                                uint8_t Filter_Duplicates);
/**
  * @brief Start the name discovery procedure. A LE_Create_Connection call will be made to the
controller by GAP with the initiator filter policy set to "ignore whitelist and process
connectable advertising packets only for the specified device". Once a connection is
established, GATT procedure is started to read the device name characteristic. When the
read is completed (successfully or unsuccessfully), a @ref aci_gap_proc_complete_event
event is given to the upper layer. The event also contains the name of the device if the
device name was read successfully.
  * @param LE_Scan_Interval This is defined as the time interval from when the Controller started
its last LE scan until it begins the subsequent LE scan.
Time = N * 0.625 msec.
  * Values:
  - 0x0004 (2.500 ms)  ... 0x4000 (10240.000 ms) 
  * @param LE_Scan_Window Amount of time for the duration of the LE scan. LE_Scan_Window
shall be less than or equal to LE_Scan_Interval.
Time = N * 0.625 msec.
  * Values:
  - 0x0004 (2.500 ms)  ... 0x4000 (10240.000 ms) 
  * @param Peer_Address_Type Address type.
  * Values:
  - 0x00: Public Device Address
  - 0x01: Random Device Address
  * @param Peer_Address Public Device Address, Random Device Address, Public Identity
Address or Random (static) Identity Address of the advertising
device.
  * @param Own_Address_Type Own address type:
 - 0x00: Public Device Address (it is allowed only if privacy is disabled)
 - 0x01: Random Device Address (it is allowed only if privacy is disabled)
 - 0x02: Resolvable Private Address (it is allowed only if privacy is enabled)
 - 0x03: Non Resolvable Private Address (it is allowed only if privacy is enabled)
  * Values:
  - 0x00: Public Device Address 
  - 0x01: Random Device Address 
  - 0x02: Resolvable Private Address
  - 0x03: Non Resolvable Private Address
  * @param Conn_Interval_Min Minimum value for the connection event interval. This shall be less
than or equal to Conn_Interval_Max.
Time = N * 1.25 msec.
  * Values:
  - 0x0006 (7.50 ms)  ... 0x0C80 (4000.00 ms) 
  * @param Conn_Interval_Max Maximum value for the connection event interval. This shall be
greater than or equal to Conn_Interval_Min.
Time = N * 1.25 msec.
  * Values:
  - 0x0006 (7.50 ms)  ... 0x0C80 (4000.00 ms) 
  * @param Conn_Latency Slave latency for the connection in number of connection events.
  * Values:
  - 0x0000 ... 0x01F3
  * @param Supervision_Timeout Supervision timeout for the LE Link.
It shall be a multiple of 10 ms and larger than (1 + connSlaveLatency) * connInterval * 2.
Time = N * 10 msec.
  * Values:
  - 0x000A (100 ms)  ... 0x0C80 (32000 ms) 
  * @param Minimum_CE_Length Information parameter about the minimum length of connection
needed for this LE connection.
Time = N * 0.625 msec.
  * @param Maximum_CE_Length Information parameter about the maximum length of connection needed
for this LE connection.
Time = N * 0.625 msec.
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_start_name_discovery_proc(uint16_t LE_Scan_Interval,
                                             uint16_t LE_Scan_Window,
                                             uint8_t Peer_Address_Type,
                                             uint8_t Peer_Address[6],
                                             uint8_t Own_Address_Type,
                                             uint16_t Conn_Interval_Min,
                                             uint16_t Conn_Interval_Max,
                                             uint16_t Conn_Latency,
                                             uint16_t Supervision_Timeout,
                                             uint16_t Minimum_CE_Length,
                                             uint16_t Maximum_CE_Length);
/**
  * @brief Start the auto connection establishment procedure. The devices specified are added to the
white list of the controller and a LE_Create_Connection call will be made to the controller by
GAP with the initiator filter policy set to "use whitelist to determine which advertiser to
connect to". When a command is issued to terminate the procedure by upper layer, a
LE_Create_Connection_Cancel call will be made to the controller by GAP.
The procedure is terminated when either a connection is successfully established with one of
the specified devices in the white list or the procedure is explicitly terminated by issuing
the command @ref aci_gap_terminate_gap_proc with the procedure code set to 0x08. A
@ref aci_gap_proc_complete_event event is returned with the procedure code set to 0x08.
If controller privacy is enabled and the peer device (advertiser) is in the resolving list then
 the link layer will generate a RPA, if it is not then the RPA/NRPA generated by the Host will be used.
  * @param LE_Scan_Interval This is defined as the time interval from when the Controller started
its last LE scan until it begins the subsequent LE scan.
Time = N * 0.625 msec.
  * Values:
  - 0x0004 (2.500 ms)  ... 0x4000 (10240.000 ms) 
  * @param LE_Scan_Window Amount of time for the duration of the LE scan. LE_Scan_Window
shall be less than or equal to LE_Scan_Interval.
Time = N * 0.625 msec.
  * Values:
  - 0x0004 (2.500 ms)  ... 0x4000 (10240.000 ms) 
  * @param Own_Address_Type Own address type:
 - 0x00: Public Device Address (it is allowed only if privacy is disabled)
 - 0x01: Random Device Address (it is allowed only if privacy is disabled)
 - 0x02: Resolvable Private Address (it is allowed only if privacy is enabled)
 - 0x03: Non Resolvable Private Address (it is allowed only if privacy is enabled)
  * Values:
  - 0x00: Public Device Address 
  - 0x01: Random Device Address 
  - 0x02: Resolvable Private Address
  - 0x03: Non Resolvable Private Address
  * @param Conn_Interval_Min Minimum value for the connection event interval. This shall be less
than or equal to Conn_Interval_Max.
Time = N * 1.25 msec.
  * Values:
  - 0x0006 (7.50 ms)  ... 0x0C80 (4000.00 ms) 
  * @param Conn_Interval_Max Maximum value for the connection event interval. This shall be
greater than or equal to Conn_Interval_Min.
Time = N * 1.25 msec.
  * Values:
  - 0x0006 (7.50 ms)  ... 0x0C80 (4000.00 ms) 
  * @param Conn_Latency Slave latency for the connection in number of connection events.
  * Values:
  - 0x0000 ... 0x01F3
  * @param Supervision_Timeout Supervision timeout for the LE Link.
It shall be a multiple of 10 ms and larger than (1 + connSlaveLatency) * connInterval * 2.
Time = N * 10 msec.
  * Values:
  - 0x000A (100 ms)  ... 0x0C80 (32000 ms) 
  * @param Minimum_CE_Length Information parameter about the minimum length of connection
needed for this LE connection.
Time = N * 0.625 msec.
  * @param Maximum_CE_Length Information parameter about the maximum length of connection needed
for this LE connection.
Time = N * 0.625 msec.
  * @param Num_of_Whitelist_Entries Number of devices that have to be added to the whitelist.
  * @param Whitelist_Entry See @ref Whitelist_Entry_t
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_start_auto_connection_establish_proc(uint16_t LE_Scan_Interval,
                                                        uint16_t LE_Scan_Window,
                                                        uint8_t Own_Address_Type,
                                                        uint16_t Conn_Interval_Min,
                                                        uint16_t Conn_Interval_Max,
                                                        uint16_t Conn_Latency,
                                                        uint16_t Supervision_Timeout,
                                                        uint16_t Minimum_CE_Length,
                                                        uint16_t Maximum_CE_Length,
                                                        uint8_t Num_of_Whitelist_Entries,
                                                        Whitelist_Entry_t Whitelist_Entry[]);
/**
  * @brief Start a general connection establishment procedure. The host enables scanning in the
controller with the scanner filter policy set to "accept all advertising packets" and from the
scanning results, all the devices are sent to the upper layer using the event
LE_Advertising_Report. The upper layer then has to select one of the devices to which it
wants to connect by issuing the command @ref aci_gap_create_connection. If privacy is
enabled, then either a private resolvable address or a non resolvable address, based on the
address type specified in the command is set as the scanner address but the gap create
connection always uses a private resolvable address if the general connection
establishment procedure is active.
The procedure is terminated when a connection is established or the upper layer terminates
the procedure by issuing the command @ref aci_gap_terminate_gap_proc with the procedure
code set to 0x10. On completion of the procedure a @ref aci_gap_proc_complete_event event
is generated with the procedure code set to 0x10.
If controller privacy is enabled and the peer device (advertiser) is in the resolving list then
the link layer will generate a RPA, if it is not then the RPA/NRPA generated by the Host will be used.
  * @param LE_Scan_Type Passive or active scanning. With active scanning SCAN_REQ packets are sent.
  * Values:
  - 0x00: Passive Scanning
  - 0x01: Active scanning
  * @param LE_Scan_Interval This is defined as the time interval from when the Controller started
its last LE scan until it begins the subsequent LE scan.
Time = N * 0.625 msec.
  * Values:
  - 0x0004 (2.500 ms)  ... 0x4000 (10240.000 ms) 
  * @param LE_Scan_Window Amount of time for the duration of the LE scan. LE_Scan_Window
shall be less than or equal to LE_Scan_Interval.
Time = N * 0.625 msec.
  * Values:
  - 0x0004 (2.500 ms)  ... 0x4000 (10240.000 ms) 
  * @param Own_Address_Type Own address type:
 - 0x00: Public Device Address (it is allowed only if privacy is disabled)
 - 0x01: Random Device Address (it is allowed only if privacy is disabled)
 - 0x02: Resolvable Private Address (it is allowed only if privacy is enabled)
 - 0x03: Non Resolvable Private Address (it is allowed only if privacy is enabled)
  * Values:
  - 0x00: Public Device Address 
  - 0x01: Random Device Address 
  - 0x02: Resolvable Private Address
  - 0x03: Non Resolvable Private Address
  * @param Scanning_Filter_Policy Scanning filter policy:
 - 0x00 Accept all advertisement packets.Directed advertising packets which are not addressed for this device shall be ignored.
 - 0x01 Ignore advertisement packets from devices not in the White List Only.Directed advertising packets which are not addressed for this device shall be ignored.
 - 0x02 Accept all undirected advertisement packets (it is allowed only if controller privacy or host privacy is enabled).Directed advertisement packets where initiator address is a RPA and Directed advertisement packets addressed to this device shall be accepted.
 - 0x03 Accept all undirected advertisement packets from devices that are in the White List.Directed advertisement packets where initiator address is RPA and Directed advertisement packets addressed to this device shall be accepted.
 - NOTE: if controller privacy is enabled Scanning_Filter_Policy can only assume values 0x00 or 0x02; if Host privacy is enabled Scanning_Filter_Policy can only assume value 0x00.
  * Values:
  - 0x00: Accept all
  - 0x01: Ignore devices not in the White List
  - 0x02: Accept all (use resolving list)
  - 0x03: Ignore devices not in the White List (use resolving list)
  * @param Filter_Duplicates Enable/disable duplicate filtering.
  * Values:
  - 0x00: Duplicate filtering disabled
  - 0x01: Duplicate filtering enabled
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_start_general_connection_establish_proc(uint8_t LE_Scan_Type,
                                                           uint16_t LE_Scan_Interval,
                                                           uint16_t LE_Scan_Window,
                                                           uint8_t Own_Address_Type,
                                                           uint8_t Scanning_Filter_Policy,
                                                           uint8_t Filter_Duplicates);
/**
  * @brief Start a selective connection establishment procedure. The GAP adds the specified device
addresses into white list and enables scanning in the controller with the scanner filter policy
set to "accept packets only from devices in whitelist". All the devices found are sent to the
upper layer by the event @ref hci_le_advertising_report_event. The upper layer then has to select one of
the devices to which it wants to connect by issuing the command @ref aci_gap_create_connection.
On completion of the procedure a @ref aci_gap_proc_complete_event event is generated with
the procedure code set to 0x20. The procedure is terminated when a connection is established
or the upper layer terminates the procedure by issuing the command
@ref aci_gap_terminate_gap_proc with the procedure code set to 0x20.
If controller privacy is enabled and the peer device (advertiser) is in the resolving list then
 the link layer will generate a RPA, if it is not then the RPA/NRPA generated by the Host will be used.
  * @param LE_Scan_Type Passive or active scanning. With active scanning SCAN_REQ packets are sent.
  * Values:
  - 0x00: Passive Scanning
  - 0x01: Active scanning
  * @param LE_Scan_Interval This is defined as the time interval from when the Controller started
its last LE scan until it begins the subsequent LE scan.
Time = N * 0.625 msec.
  * Values:
  - 0x0004 (2.500 ms)  ... 0x4000 (10240.000 ms) 
  * @param LE_Scan_Window Amount of time for the duration of the LE scan. LE_Scan_Window
shall be less than or equal to LE_Scan_Interval.
Time = N * 0.625 msec.
  * Values:
  - 0x0004 (2.500 ms)  ... 0x4000 (10240.000 ms) 
  * @param Own_Address_Type Own address type:
 - 0x00: Public Device Address (it is allowed only if privacy is disabled)
 - 0x01: Random Device Address (it is allowed only if privacy is disabled)
 - 0x02: Resolvable Private Address (it is allowed only if privacy is enabled)
 - 0x03: Non Resolvable Private Address (it is allowed only if privacy is enabled)
  * Values:
  - 0x00: Public Device Address 
  - 0x01: Random Device Address 
  - 0x02: Resolvable Private Address
  - 0x03: Non Resolvable Private Address
  * @param Scanning_Filter_Policy Scanning filter policy:
 - 0x00 Accept all advertisement packets.Directed advertising packets which are not addressed for this device shall be ignored.
 - 0x01 Ignore advertisement packets from devices not in the White List Only.Directed advertising packets which are not addressed for this device shall be ignored.
 - 0x02 Accept all undirected advertisement packets (it is allowed only if controller privacy or host privacy is enabled).Directed advertisement packets where initiator address is a RPA and Directed advertisement packets addressed to this device shall be accepted.
 - 0x03 Accept all undirected advertisement packets from devices that are in the White List.Directed advertisement packets where initiator address is RPA and Directed advertisement packets addressed to this device shall be accepted.
 - NOTE: if controller privacy is enabled Scanning_Filter_Policy can only assume values 0x01 or 0x03; if Host privacy is enabled Scanning_Filter_Policy can only assume value 0x01.
  * Values:
  - 0x00: Accept all
  - 0x01: Ignore devices not in the White List
  - 0x02: Accept all (use resolving list)
  - 0x03: Ignore devices not in the White List (use resolving list)
  * @param Filter_Duplicates Enable/disable duplicate filtering.
  * Values:
  - 0x00: Duplicate filtering disabled
  - 0x01: Duplicate filtering enabled
  * @param Num_of_Whitelist_Entries Number of devices that have to be added to the whitelist.
  * @param Whitelist_Entry See @ref Whitelist_Entry_t
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_start_selective_connection_establish_proc(uint8_t LE_Scan_Type,
                                                             uint16_t LE_Scan_Interval,
                                                             uint16_t LE_Scan_Window,
                                                             uint8_t Own_Address_Type,
                                                             uint8_t Scanning_Filter_Policy,
                                                             uint8_t Filter_Duplicates,
                                                             uint8_t Num_of_Whitelist_Entries,
                                                             Whitelist_Entry_t Whitelist_Entry[]);
/**
  * @brief Start the direct connection establishment procedure. A LE_Create_Connection call will be
made to the controller by GAP with the initiator filter policy set to "ignore whitelist and
process connectable advertising packets only for the specified device". The procedure can
be terminated explicitly by the upper layer by issuing the command
@ref aci_gap_terminate_gap_proc. When a command is issued to terminate the
procedure by upper layer, a @ref hci_le_create_connection_cancel call will be made to the
controller by GAP.
On termination of the procedure, a @ref hci_le_connection_complete_event event is returned. The  
procedure can be explicitly terminated by the upper layer by issuing the command
@ref aci_gap_terminate_gap_proc with the procedure_code set to 0x40.
If controller privacy is enabled and the peer device (advertiser) is in the resolving list then
the link layer will generate a RPA, if it is not then the RPA/NRPA generated by the Host will be used.
  * @param LE_Scan_Interval This is defined as the time interval from when the Controller started
its last LE scan until it begins the subsequent LE scan.
Time = N * 0.625 msec.
  * Values:
  - 0x0004 (2.500 ms)  ... 0x4000 (10240.000 ms) 
  * @param LE_Scan_Window Amount of time for the duration of the LE scan. LE_Scan_Window
shall be less than or equal to LE_Scan_Interval.
Time = N * 0.625 msec.
  * Values:
  - 0x0004 (2.500 ms)  ... 0x4000 (10240.000 ms) 
  * @param Peer_Address_Type Peer Address type.
  * Values:
  - 0x00: Public Device Address or Public Identity Address
  - 0x01: Random Device Address or Random (static) Identity Address
  * @param Peer_Address Public Device Address, Random Device Address, Public Identity
Address or Random (static) Identity Address of the advertising
device.
  * @param Own_Address_Type Own address type:
 - 0x00: Public Device Address (it is allowed only if privacy is disabled)
 - 0x01: Random Device Address (it is allowed only if privacy is disabled)
 - 0x02: Resolvable Private Address (it is allowed only if privacy is enabled)
 - 0x03: Non Resolvable Private Address (it is allowed only if privacy is enabled)
  * Values:
  - 0x00: Public Device Address 
  - 0x01: Random Device Address 
  - 0x02: Resolvable Private Address
  - 0x03: Non Resolvable Private Address
  * @param Conn_Interval_Min Minimum value for the connection event interval. This shall be less
than or equal to Conn_Interval_Max.
Time = N * 1.25 msec.
  * Values:
  - 0x0006 (7.50 ms)  ... 0x0C80 (4000.00 ms) 
  * @param Conn_Interval_Max Maximum value for the connection event interval. This shall be
greater than or equal to Conn_Interval_Min.
Time = N * 1.25 msec.
  * Values:
  - 0x0006 (7.50 ms)  ... 0x0C80 (4000.00 ms) 
  * @param Conn_Latency Slave latency for the connection in number of connection events.
  * Values:
  - 0x0000 ... 0x01F3
  * @param Supervision_Timeout Supervision timeout for the LE Link.
It shall be a multiple of 10 ms and larger than (1 + connSlaveLatency) * connInterval * 2.
Time = N * 10 msec.
  * Values:
  - 0x000A (100 ms)  ... 0x0C80 (32000 ms) 
  * @param Minimum_CE_Length Information parameter about the minimum length of connection
needed for this LE connection.
Time = N * 0.625 msec.
  * @param Maximum_CE_Length Information parameter about the maximum length of connection needed
for this LE connection.
Time = N * 0.625 msec.
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_create_connection(uint16_t LE_Scan_Interval,
                                     uint16_t LE_Scan_Window,
                                     uint8_t Peer_Address_Type,
                                     uint8_t Peer_Address[6],
                                     uint8_t Own_Address_Type,
                                     uint16_t Conn_Interval_Min,
                                     uint16_t Conn_Interval_Max,
                                     uint16_t Conn_Latency,
                                     uint16_t Supervision_Timeout,
                                     uint16_t Minimum_CE_Length,
                                     uint16_t Maximum_CE_Length);
/**
  * @brief Terminate the specified GATT procedure. An @ref aci_gap_proc_complete_event event is
returned with the procedure code set to the corresponding procedure.
  * @param Procedure_Code GAP procedure bitmap.
  * Values:
  - 0x00: No events
  - 0x01: LIMITED_DISCOVERY_PROC
  - 0x02: GENERAL_DISCOVERY_PROC
  - 0x04: NAME_DISCOVERY_PROC
  - 0x08: AUTO_CONNECTION_ESTABLISHMENT_PROC
  - 0x10: GENERAL_CONNECTION_ESTABLISHMENT_PROC
  - 0x20: SELECTIVE_CONNECTION_ESTABLISHMENT_PROC
  - 0x40: DIRECT_CONNECTION_ESTABLISHMENT_PROC
  - 0x80: OBSERVATION_PROC
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_terminate_gap_proc(uint8_t Procedure_Code);
/**
  * @brief Start the connection update procedure (only when role is Master). A @ref hci_le_connection_update is called.
On completion of the procedure, an @ref hci_le_connection_update_complete_event event is returned to
the upper layer.
  * @param Connection_Handle Connection handle for which the command is given.
  * Values:
  - 0x0000 ... 0x0EFF
  * @param Conn_Interval_Min Minimum value for the connection event interval. This shall be less
than or equal to Conn_Interval_Max.
Time = N * 1.25 msec.
  * Values:
  - 0x0006 (7.50 ms)  ... 0x0C80 (4000.00 ms) 
  * @param Conn_Interval_Max Maximum value for the connection event interval. This shall be
greater than or equal to Conn_Interval_Min.
Time = N * 1.25 msec.
  * Values:
  - 0x0006 (7.50 ms)  ... 0x0C80 (4000.00 ms) 
  * @param Conn_Latency Slave latency for the connection in number of connection events.
  * Values:
  - 0x0000 ... 0x01F3
  * @param Supervision_Timeout Supervision timeout for the LE Link.
It shall be a multiple of 10 ms and larger than (1 + connSlaveLatency) * connInterval * 2.
Time = N * 10 msec.
  * Values:
  - 0x000A (100 ms)  ... 0x0C80 (32000 ms) 
  * @param Minimum_CE_Length Information parameter about the minimum length of connection
needed for this LE connection.
Time = N * 0.625 msec.
  * @param Maximum_CE_Length Information parameter about the maximum length of connection needed
for this LE connection.
Time = N * 0.625 msec.
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_start_connection_update(uint16_t Connection_Handle,
                                           uint16_t Conn_Interval_Min,
                                           uint16_t Conn_Interval_Max,
                                           uint16_t Conn_Latency,
                                           uint16_t Supervision_Timeout,
                                           uint16_t Minimum_CE_Length,
                                           uint16_t Maximum_CE_Length);
/**
  * @brief Send the SM pairing request to start a pairing process. The authentication requirements and
IO capabilities should be set before issuing this command using the
@ref aci_gap_set_io_capability and @ref aci_gap_set_authentication_requirement commands.
A @ref aci_gap_pairing_complete_event event is returned after the pairing process is completed.
  * @param Connection_Handle Connection handle for which the command is given.
  * Values:
  - 0x0000 ... 0x0EFF
  * @param Force_Rebond If 1, Pairing request will be sent even if the device was previously bonded,
 otherwise pairing request is not sent.
  * Values:
  - 0x00: NO
  - 0x01: YES
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_send_pairing_req(uint16_t Connection_Handle,
                                    uint8_t Force_Rebond);
/**
  * @brief This command tries to resolve the address provided with the IRKs present in its database. If
the address is resolved successfully with any one of the IRKs present in the database, it
returns success and also the corresponding public/static random address stored with the
IRK in the database.
  * @param Address Address to be resolved
  * @param[out] Actual_Address The public or static random address of the peer device, distributed during pairing phase.
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_resolve_private_addr(uint8_t Address[6],
                                        uint8_t Actual_Address[6]);
/**
  * @brief This command puts the device into broadcast mode. A privacy enabled device uses either a
resolvable private address or a non-resolvable private address as specified in the
Own_Addr_Type parameter of the command.
  * @param Advertising_Interval_Min Minimum advertising interval.
Time = N * 0.625 msec.
  * Values:
  - 0x0020 (20.000 ms)  ... 0x4000 (10240.000 ms) 
  * @param Advertising_Interval_Max Maximum advertising interval.
Time = N * 0.625 msec.
  * Values:
  - 0x0020 (20.000 ms)  ... 0x4000 (10240.000 ms) 
  * @param Advertising_Type Non connectable advertising type
  * Values:
  - 0x02: ADV_SCAN_IND (Scannable undirected advertising)
  - 0x03: ADV_NONCONN_IND (Non connectable undirected advertising)
  * @param Own_Address_Type If Privacy is disabled, then the address can be public or static random.
If Privacy is enabled, then the address can be a resolvable private address or a non-resolvable private address.
  * Values:
  - 0x00: Public address
  - 0x01: Static random address
  - 0x02: Resolvable private address
  - 0x03: Non-resolvable private address
  * @param Adv_Data_Length Length of the advertising data in the advertising packet.
  * @param Adv_Data Advertising data used by the device while advertising.
  * @param Num_of_Whitelist_Entries Number of devices that have to be added to the whitelist.
  * @param Whitelist_Entry See @ref Whitelist_Entry_t
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_set_broadcast_mode(uint16_t Advertising_Interval_Min,
                                      uint16_t Advertising_Interval_Max,
                                      uint8_t Advertising_Type,
                                      uint8_t Own_Address_Type,
                                      uint8_t Adv_Data_Length,
                                      uint8_t Adv_Data[],
                                      uint8_t Num_of_Whitelist_Entries,
                                      Whitelist_Entry_t Whitelist_Entry[]);
/**
  * @brief Starts an Observation procedure, when the device is in Observer Role. The host enables
scanning in the controller. The advertising reports are sent to the upper layer using standard
LE Advertising Report Event. (See Bluetooth Core v4.1, Vol. 2, part E, Ch. 7.7.65.2, LE
Advertising Report Event).
If controller privacy is enabled and the peer device (advertiser) is in the resolving list then
the link layer will generate a RPA, if it is not then the RPA/NRPA generated by the Host will be used.
  * @param LE_Scan_Interval This is defined as the time interval from when the Controller started
its last LE scan until it begins the subsequent LE scan.
Time = N * 0.625 msec.
  * Values:
  - 0x0004 (2.500 ms)  ... 0x4000 (10240.000 ms) 
  * @param LE_Scan_Window Amount of time for the duration of the LE scan. LE_Scan_Window
shall be less than or equal to LE_Scan_Interval.
Time = N * 0.625 msec.
  * Values:
  - 0x0004 (2.500 ms)  ... 0x4000 (10240.000 ms) 
  * @param LE_Scan_Type Passive or active scanning. With active scanning SCAN_REQ packets are sent.
  * Values:
  - 0x00: Passive Scanning
  - 0x01: Active scanning
  * @param Own_Address_Type Own address type:
 - 0x00: Public Device Address (it is allowed only if privacy is disabled)
 - 0x01: Random Device Address (it is allowed only if privacy is disabled)
 - 0x02: Resolvable Private Address (it is allowed only if privacy is enabled)
 - 0x03: Non Resolvable Private Address (it is allowed only if privacy is enabled)
  * Values:
  - 0x00: Public Device Address 
  - 0x01: Random Device Address 
  - 0x02: Resolvable Private Address
  - 0x03: Non Resolvable Private Address
  * @param Filter_Duplicates Enable/disable duplicate filtering.
  * Values:
  - 0x00: Duplicate filtering disabled
  - 0x01: Duplicate filtering enabled
  * @param Scanning_Filter_Policy Scanning filter policy:
 - 0x00 Accept all advertisement packets (it is allowed only if controller privacy is enabled).Directed advertising packets which are not addressed for this device shall be ignored.
 - 0x01 Ignore advertisement packets from devices not in the White List Only.Directed advertising packets which are not addressed for this device shall be ignored.
 - 0x02 Accept all undirected advertisement packets (it is allowed only if controller privacy or host privacy is enabled).Directed advertisement packets where initiator address is a RPA and Directed advertisement packets addressed to this device shall be accepted.
 - 0x03 Accept all undirected advertisement packets from devices that are in the White List.Directed advertisement packets where initiator address is RPA and Directed advertisement packets addressed to this device shall be accepted.
 - NOTE: If Host privacy is enabled Scanning_Filter_Policy can only take values 0x00 or 0x01;
  * Values:
  - 0x00: Accept all
  - 0x01: Ignore devices not in the White List
  - 0x02: Accept all (use resolving list)
  - 0x03: Ignore devices not in the White List (use resolving list)
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_start_observation_proc(uint16_t LE_Scan_Interval,
                                          uint16_t LE_Scan_Window,
                                          uint8_t LE_Scan_Type,
                                          uint8_t Own_Address_Type,
                                          uint8_t Filter_Duplicates,
                                          uint8_t Scanning_Filter_Policy);
/**
  * @brief This command gets the list of the devices which are bonded. It returns the
number of addresses and the corresponding address types and values.
  * @param[out] Num_of_Addresses The number of bonded devices
  * @param[out] Bonded_Device_Entry See @ref Bonded_Device_Entry_t
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_get_bonded_devices(uint8_t *Num_of_Addresses,
                                      Bonded_Device_Entry_t Bonded_Device_Entry[]);
/**
  * @brief The command finds whether the device, whose address is specified in the command, is
bonded. If the device is using a resolvable private address and it has been bonded, then the
command will return BLE_STATUS_SUCCESS.
  * @param Peer_Address_Type Address type.
  * Values:
  - 0x00: Public Device Address
  - 0x01: Random Device Address
  * @param Peer_Address Address used by the peer device while advertising
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_is_device_bonded(uint8_t Peer_Address_Type,
                                    uint8_t Peer_Address[6]);
/**
  * @brief This command allows the User to validate/confirm or not the Numeric Comparison value showed through the ACI_GAP_Numeric_Comparison_Value_Event.
  * @param Connection_Handle Connection handle for which the command is given.
  * Values:
  - 0x0000 ... 0x0EFF
  * @param Confirm_Yes_No 0 : The Numeric Values showed on both local and peer device are different!
1 : The Numeric Values showed on both local and peer device are equal!
  * Values:
  - 0x00: No
  - 0x01: YES
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_numeric_comparison_value_confirm_yesno(uint16_t Connection_Handle,
                                                          uint8_t Confirm_Yes_No);
/**
  * @brief This command permits to signal to the Stack the input type detected during Passkey input.
  * @param Connection_Handle Connection handle for which the command is given.
  * Values:
  - 0x0000 ... 0x0EFF
  * @param Input_Type Passkey input type detected
  * Values:
  - 0x00: Passkey entry started
  - 0x01: Passkey digit entered
  - 0x02: Passkey digit erased
  - 0x03: Passkey cleared
  - 0x04: Passkey entry completed
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_passkey_input(uint16_t Connection_Handle,
                                 uint8_t Input_Type);
/**
  * @brief This command is sent by the User to get (i.e. to extract from the Stack) the OOB data generated by the Stack itself.
In a complete system (i.e. having an OOB channel fully handled) this command should be invoked by the OOB Channel manager to require the local OOB data
(hence without user interaction) to be sent via OOB to the remote peer candidate device.
The requested OOB data are returned in response to the incoming command. The OOB data are not generated on the fly, but they are already available in the Stack.
  * @param OOB_Data_Type OOB Data type
  * Values:
  - 0x00: Legacy Privacy (LP) v.4.1 TK (Temporary Key)
  - 0x01: Secure Connections (SC) v.4.2 Random value r used for generation of Confirm
  - 0x02: Secure Connections (SC) v.4.2 Confirm value C generated through AES-CMAC-128 based cryptographic function: C=f4(PKx, PKx, r, 0)
  * @param[out] Address_Type Identity address type.
  * Values:
  - 0x00: Public Identity Address
  - 0x01: Random (static) Identity Address
  * @param[out] Address Public or Random (static) address of this  device
  * @param[out] OOB_Data_Len Length of OOB Data carried by next data field
  * @param[out] OOB_Data OOB Data to be exported via OOB.
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_get_oob_data(uint8_t OOB_Data_Type,
                                uint8_t *Address_Type,
                                uint8_t Address[6],
                                uint8_t *OOB_Data_Len,
                                uint8_t OOB_Data[16]);
/**
  * @brief This command is sent (by the User) to input the OOB data arrived via OOB communication.
It may be sent to set either the OOB Authentication data of the Local device, or the data received via OOB by the Remote peer candidate device.
It can be used with OOB_Data_Len set to 0 to generate OOB authentication data for Secure Connections.
In a complete system (i.e. having an OOB channel fully handled) this command should be invoked by the OOB Channel manager when receiving the OOB data (hence without user interaction).
Since the BLE stack v 2.x implementation supports just one entry for the Remote peer candidate list containing the OOB data, at every command invocation the data existing in that entry are overwritten.
  * @param Device_Type OOB Device type:
 - 0x00: The Address information are ignored.
   - OOB_Data_Len= 0x00: this triggers the automatic regeneration of OOB Authentication data (for Secure Connections only; a ECDH-Public Key must).
   - OOB_Data_Len in [0..16]: the OOB_Data carried by the command will overwrite the current local Authentication OOB Data.
 - 0x01: The Address information is used to search the entry of the Remote peer candidate list containing the OOB data for that specific remote device; if no entry exists, the a new entry is used, if available (current implementation supports just 1 entry in this list).
   - OOB_Data_Len in [0..16]: the OOB_Data carried by the command overwrites (if present) the remote Authentication OOB Data.
  * Values:
  - 0x00: Local device
  - 0x01: Remote device
  * @param Address_Type Identity address type.
  * Values:
  - 0x00: Public Identity Address
  - 0x01: Random (static) Identity Address
  * @param Address Public or Random (static) address of the peer device
  * @param OOB_Data_Type OOB Data type
  * Values:
  - 0x00: Legacy Privacy (LP) v.4.1 TK (Temporary Key)
  - 0x01: Secure Connections (SC) v.4.2 Random value r used for generation of Confirm
  - 0x02: Secure Connections (SC) v.4.2 Confirm value C generated through AES-CMAC-128 based cryptographic function: C=f4(PKx, PKx, r, 0)
  * @param OOB_Data_Len Length of OOB Data carried by next data field
  * @param OOB_Data OOB Data to be exported via OOB.
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_set_oob_data(uint8_t Device_Type,
                                uint8_t Address_Type,
                                uint8_t Address[6],
                                uint8_t OOB_Data_Type,
                                uint8_t OOB_Data_Len,
                                uint8_t OOB_Data[16]);
/**
  * @brief This  command is used to add one device to the list of address translations used to resolve Resolvable Private Addresses in the Controller.
  * @param Num_of_Resolving_list_Entries Number of devices that have to be added to the resolving list.
  * @param Whitelist_Identity_Entry See @ref Whitelist_Identity_Entry_t
  * @param Clear_Resolving_List Clear the resolving list
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_add_devices_to_resolving_list(uint8_t Num_of_Resolving_list_Entries,
                                                 Whitelist_Identity_Entry_t Whitelist_Identity_Entry[],
                                                 uint8_t Clear_Resolving_List);
/**
  * @brief This command can be used to remove a specified device from the bonding table.
  * @param Peer_Identity_Address_Type Identity address type.
  * Values:
  - 0x00: Public Identity Address
  - 0x01: Random (static) Identity Address
  * @param Peer_Identity_Address Public or Random (static) Identity address of the peer device
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_remove_bonded_device(uint8_t Peer_Identity_Address_Type,
                                        uint8_t Peer_Identity_Address[6]);
/**
 * @}
 */
/**
 *@defgroup GATT_API GATT API
 *@brief GATT API layer.
 *@{
 */
/**
  * @brief Initialize the GATT layer for server and client roles. 
It adds also the GATT service with Service Changed Characteristic. 
Until this command is issued the GATT channel will not process any commands even if the 
connection is opened. This command has to be given before using any of the GAP features. 
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_init(void);
/**
  * @brief Add a service to GATT Server. When a service is created in the server, the host needs to
reserve the handle ranges for this service using Max_Attribute_Records parameter. This
parameter specifies the maximum number of attribute records that can be added to this
service (including the service attribute, include attribute, characteristic attribute,
characteristic value attribute and characteristic descriptor attribute). Handle of the created
service is returned in command complete event. Service declaration is taken from the service pool. 
The attributes for characteristics and descriptors are allocated from the attribute pool.
  * @param Service_UUID_Type UUID type.
  * @param Service_UUID See @ref Service_UUID_t
  * @param Service_Type Service type.
  * Values:
  - 0x01: Primary Service
  - 0x02: Secondary Service
  * @param Max_Attribute_Records Maximum number of attribute records that can be added to this service
  * @param[out] Service_Handle Handle of the Service.
When this service is added, a handle is allocated by the server for this service. 
Server also allocates a range of handles for this service from serviceHandle to <serviceHandle + max_attr_records - 1>
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_add_service(uint8_t Service_UUID_Type,
                                Service_UUID_t *Service_UUID,
                                uint8_t Service_Type,
                                uint8_t Max_Attribute_Records,
                                uint16_t *Service_Handle);
/**
  * @brief Include a service given by Include_Start_Handle and Include_End_Handle to another 
service given by Service_Handle. Attribute server creates an INCLUDE definition 
attribute and return the handle of this attribute in Included_handle.
  * @param Service_Handle Handle of the Service to which another service has to be included.
  * @param Include_Start_Handle Start Handle of the Service which has to be included in service
  * @param Include_End_Handle End Handle of the Service which has to be included in service
  * @param Include_UUID_Type UUID type.
  * @param Include_UUID See @ref Include_UUID_t
  * @param[out] Include_Handle Handle of the include declaration
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_include_service(uint16_t Service_Handle,
                                    uint16_t Include_Start_Handle,
                                    uint16_t Include_End_Handle,
                                    uint8_t Include_UUID_Type,
                                    Include_UUID_t *Include_UUID,
                                    uint16_t *Include_Handle);
/**
  * @brief Add a characteristic to a service.
  * @param Service_Handle Handle of the Service to which the characteristic will be added
  * @param Char_UUID_Type UUID type.
  * @param Char_UUID See @ref Char_UUID_t
  * @param Char_Value_Length Maximum length of the characteristic value.
  * @param Char_Properties Characteristic Properties (Volume 3, Part G, section 3.3.1.1 of Bluetooth Specification 4.1)
  * Flags:
  - 0x00: CHAR_PROP_NONE
  - 0x01: CHAR_PROP_BROADCAST (Broadcast)
  - 0x02: CHAR_PROP_READ (Read)
  - 0x04: CHAR_PROP_WRITE_WITHOUT_RESP (Write w/o resp)
  - 0x08: CHAR_PROP_WRITE (Write)
  - 0x10: CHAR_PROP_NOTIFY (Notify)
  - 0x20: CHAR_PROP_INDICATE (Indicate)
  - 0x40: CHAR_PROP_SIGNED_WRITE (Authenticated Signed Writes)
  - 0x80: CHAR_PROP_EXT (Extended Properties)
  * @param Security_Permissions Security permission flags.
  * Flags:
  - 0x00: None
  - 0x01: AUTHEN_READ (Need authentication to read)
  - 0x02: AUTHOR_READ (Need authorization to read)
  - 0x04: ENCRY_READ (Need encryption to read)
  - 0x08: AUTHEN_WRITE (need authentication to write)
  - 0x10: AUTHOR_WRITE (need authorization to write)
  - 0x20: ENCRY_WRITE (need encryption to write)
  * @param GATT_Evt_Mask GATT event mask.
  * Flags:
  - 0x00: GATT_DONT_NOTIFY_EVENTS
  - 0x01: GATT_NOTIFY_ATTRIBUTE_WRITE
  - 0x02: GATT_NOTIFY_WRITE_REQ_AND_WAIT_FOR_APPL_RESP
  - 0x04: GATT_NOTIFY_READ_REQ_AND_WAIT_FOR_APPL_RESP
  * @param Enc_Key_Size Minimum encryption key size required to read the characteristic.
  * Values:
  - 0x07 ... 0x10
  * @param Is_Variable Specify if the characteristic value has a fixed length or
a variable length.
  * Values:
  - 0x00: Fixed length
  - 0x01: Variable length
  * @param[out] Char_Handle Handle of the Characteristic that has been added. 
It is the handle of the characteristic declaration. 
The attribute that holds the characteristic value is allocated at the next handle, 
followed by the Client Characteristic Configuration descriptor if the characteristic 
has CHAR_PROP_NOTIFY or CHAR_PROP_INDICATE properties.
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_add_char(uint16_t Service_Handle,
                             uint8_t Char_UUID_Type,
                             Char_UUID_t *Char_UUID,
                             uint16_t Char_Value_Length,
                             uint8_t Char_Properties,
                             uint8_t Security_Permissions,
                             uint8_t GATT_Evt_Mask,
                             uint8_t Enc_Key_Size,
                             uint8_t Is_Variable,
                             uint16_t *Char_Handle);
/**
  * @brief Add a characteristic descriptor to a service.
  * @param Service_Handle Handle of service to which the characteristic belongs
  * @param Char_Handle Handle of the characteristic to which description has to be added
  * @param Char_Desc_Uuid_Type UUID type.
  * @param Char_Desc_Uuid See @ref Char_Desc_Uuid_t
  * @param Char_Desc_Value_Max_Len The maximum length of the descriptor value
  * @param Char_Desc_Value_Length Current Length of the characteristic descriptor value
  * @param Char_Desc_Value Value of the characteristic description
  * @param Security_Permissions Security permission flags.
  * Flags:
  - 0x00: None
  - 0x01: AUTHEN_READ (Need authentication to read)
  - 0x02: AUTHOR_READ (Need authorization to read)
  - 0x04: ENCRY_READ (Need encryption to read)
  - 0x08: AUTHEN_WRITE (need authentication to write)
  - 0x10: AUTHOR_WRITE (need authorization to write)
  - 0x20: ENCRY_WRITE (need encryption to write)
  * @param Access_Permissions Access permission
  * Flags:
  - 0x00: None
  - 0x01: READ
  - 0x02: WRITE
  - 0x04: WRITE_WO_RESP
  - 0x08: SIGNED_WRITE
  * @param GATT_Evt_Mask GATT event mask.
  * Flags:
  - 0x00: GATT_DONT_NOTIFY_EVENTS
  - 0x01: GATT_NOTIFY_ATTRIBUTE_WRITE
  - 0x02: GATT_NOTIFY_WRITE_REQ_AND_WAIT_FOR_APPL_RESP
  - 0x04: GATT_NOTIFY_READ_REQ_AND_WAIT_FOR_APPL_RESP
  * @param Enc_Key_Size Minimum encryption key size required to read the characteristic.
  * Values:
  - 0x07 ... 0x10
  * @param Is_Variable Specify if the characteristic value has a fixed length or
a variable length.
  * Values:
  - 0x00: Fixed length
  - 0x01: Variable length
  * @param[out] Char_Desc_Handle Handle of the characteristic descriptor
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_add_char_desc(uint16_t Service_Handle,
                                  uint16_t Char_Handle,
                                  uint8_t Char_Desc_Uuid_Type,
                                  Char_Desc_Uuid_t *Char_Desc_Uuid,
                                  uint8_t Char_Desc_Value_Max_Len,
                                  uint8_t Char_Desc_Value_Length,
                                  uint8_t Char_Desc_Value[],
                                  uint8_t Security_Permissions,
                                  uint8_t Access_Permissions,
                                  uint8_t GATT_Evt_Mask,
                                  uint8_t Enc_Key_Size,
                                  uint8_t Is_Variable,
                                  uint16_t *Char_Desc_Handle);
/**
  * @brief Update a characteristic value in a service. 
If notifications (or indications) are enabled on that characteristic, 
a notification (or indication) will be sent to the client after sending 
this command to the BlueNRG. The command is queued into the BlueNRG command queue. 
If the buffer is full, because previous commands could not be still processed,
the function will return BLE_STATUS_INSUFFICIENT_RESOURCES. This will happen 
if notifications (or indications) are enabled and the application calls 
@ref aci_gatt_update_char_value at an higher rate than what is allowed by the link. 
Throughput on BLE link depends on connection interval and connection length 
parameters (decided by the master, see aci_l2cap_connection_parameter_update_request() 
for more info on how to suggest new connection parameters from a slave). If the 
application does not want to lose notifications because BlueNRG buffer becomes full, 
it has to retry again till the function returns BLE_STATUS_SUCCESS or any other error code.
DEPRECATED API (still supported but not recommended).
  * @param Service_Handle Handle of service to which the characteristic belongs
  * @param Char_Handle Handle of the characteristic
  * @param Val_Offset The offset from which the attribute value has to be updated. 
If this is set to 0 and the attribute value is of variable length, then the length of the attribute will be set to the Char_Value_Length. 
If the Val_Offset is set to a value greater than 0, then the length of the attribute will be set to the maximum length as 
specified for the attribute while adding the characteristic.
  * @param Char_Value_Length Length of the characteristic value in octets
  * @param Char_Value Characteristic value
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_update_char_value(uint16_t Service_Handle,
                                      uint16_t Char_Handle,
                                      uint8_t Val_Offset,
                                      uint8_t Char_Value_Length,
                                      uint8_t Char_Value[]);
/**
  * @brief Delete the specified characteristic from the service.
  * @param Serv_Handle Handle of service to which the characteristic belongs
  * @param Char_Handle Handle of the characteristic which has to be deleted
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_del_char(uint16_t Serv_Handle,
                             uint16_t Char_Handle);
/**
  * @brief Delete the specified service from the GATT server database.
  * @param Serv_Handle Handle of the service to be deleted
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_del_service(uint16_t Serv_Handle);
/**
  * @brief Delete the Include definition from the service.
  * @param Serv_Handle Handle of the service to which the include service belongs
  * @param Include_Handle Handle of the included service which has to be deleted
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_del_include_service(uint16_t Serv_Handle,
                                        uint16_t Include_Handle);
/**
  * @brief Mask events from the GATT. The default configuration is all the events masked.
  * @param GATT_Evt_Mask GATT/ATT event mask.
  * Values:
  - 0x00000001: ACI_GATT_ATTRIBUTE_MODIFIED_EVENT
  - 0x00000002: ACI_GATT_PROC_TIMEOUT_EVENT
  - 0x00000004: ACI_ATT_EXCHANGE_MTU_RESP_EVENT
  - 0x00000008: ACI_ATT_FIND_INFO_RESP_EVENT
  - 0x00000010: ACI_ATT_FIND_BY_TYPE_VALUE_RESP_EVENT
  - 0x00000020: ACI_ATT_READ_BY_TYPE_RESP_EVENT
  - 0x00000040: ACI_ATT_READ_RESP_EVENT
  - 0x00000080: ACI_ATT_READ_BLOB_RESP_EVENT
  - 0x00000100: ACI_ATT_READ_MULTIPLE_RESP_EVENT
  - 0x00000200: ACI_ATT_READ_BY_GROUP_TYPE_RESP_EVENT
  - 0x00000800: ACI_ATT_PREPARE_WRITE_RESP_EVENT
  - 0x00001000: ACI_ATT_EXEC_WRITE_RESP_EVENT
  - 0x00002000: ACI_GATT_INDICATION_EVENT
  - 0x00004000: ACI_GATT_NOTIFICATION_EVENT
  - 0x00008000: ACI_GATT_ERROR_RESP_EVENT
  - 0x00010000: ACI_GATT_PROC_COMPLETE_EVENT
  - 0x00020000: ACI_GATT_DISC_READ_CHAR_BY_UUID_RESP_EVENT
  - 0x00040000: ACI_GATT_TX_POOL_AVAILABLE_EVENT
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_set_event_mask(uint32_t GATT_Evt_Mask);
/**
  * @brief Perform an ATT MTU exchange procedure.
When the ATT MTU exchange procedure is completed, a @ref aci_att_exchange_mtu_resp_event
event is generated. A @ref aci_gatt_proc_complete_event event is also generated
to indicate the end of the procedure.
  * @param Connection_Handle Connection handle for which the command is given.
  * Values:
  - 0x0000 ... 0x0EFF
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_exchange_config(uint16_t Connection_Handle);
/**
  * @brief Send a Find Information Request.
This command is used to obtain the mapping of attribute handles with their associated
types. The responses of the procedure are given through the 
@ref aci_att_find_info_resp_event event. The end of the procedure is indicated by
a @ref aci_gatt_proc_complete_event event.
  * @param Connection_Handle Connection handle for which the command is given.
  * Values:
  - 0x0000 ... 0x0EFF
  * @param Start_Handle First requested handle number
  * @param End_Handle Last requested handle number
  * @retval Value indicating success or error code.
*/
tBleStatus aci_att_find_info_req(uint16_t Connection_Handle,
                                 uint16_t Start_Handle,
                                 uint16_t End_Handle);
/**
  * @brief Send a Find By Type Value Request
The Find By Type Value Request is used to obtain the handles of attributes that
have a given 16-bit UUID attribute type and a given attribute value.
The responses of the procedure are given through the @ref aci_att_find_by_type_value_resp_event event.
The end of the procedure is indicated by a @ref aci_gatt_proc_complete_event event.
  * @param Connection_Handle Connection handle for which the command is given.
  * Values:
  - 0x0000 ... 0x0EFF
  * @param Start_Handle First requested handle number
  * @param End_Handle Last requested handle number
  * @param UUID 2 octet UUID to find (little-endian)
  * @param Attribute_Val_Length Length of attribute value (maximum value is ATT_MTU - 7).
  * @param Attribute_Val Attribute value to find
  * @retval Value indicating success or error code.
*/
tBleStatus aci_att_find_by_type_value_req(uint16_t Connection_Handle,
                                          uint16_t Start_Handle,
                                          uint16_t End_Handle,
                                          uint16_t UUID,
                                          uint8_t Attribute_Val_Length,
                                          uint8_t Attribute_Val[]);
/**
  * @brief Send a Read By Type Request.
The Read By Type Request is used to obtain the values of attributes where the attribute
type is known but the handle is not known.
The responses of the procedure are given through the @ref aci_att_read_by_type_resp_event event.
The end of the procedure is indicated by a @ref aci_gatt_proc_complete_event event.
  * @param Connection_Handle Connection handle for which the command is given.
  * Values:
  - 0x0000 ... 0x0EFF
  * @param Start_Handle First requested handle number
  * @param End_Handle Last requested handle number
  * @param UUID_Type UUID type.
  * @param UUID See @ref UUID_t
  * @retval Value indicating success or error code.
*/
tBleStatus aci_att_read_by_type_req(uint16_t Connection_Handle,
                                    uint16_t Start_Handle,
                                    uint16_t End_Handle,
                                    uint8_t UUID_Type,
                                    UUID_t *UUID);
/**
  * @brief Send a Read By Group Type Request. 
The Read By Group Type Request is used to obtain the values of grouping attributes where
the attribute type is known but the handle is not known. Grouping attributes are defined 
at GATT layer. The grouping attribute types are: "Primary Service", "Secondary Service" 
and "Characteristic". 
The responses of the procedure are given through the @ref aci_att_read_by_group_type_resp_event event. 
The end of the procedure is indicated by a @ref aci_gatt_proc_complete_event.
  * @param Connection_Handle Connection handle for which the command is given.
  * Values:
  - 0x0000 ... 0x0EFF
  * @param Start_Handle First requested handle number
  * @param End_Handle Last requested handle number
  * @param UUID_Type UUID type.
  * @param UUID See @ref UUID_t
  * @retval Value indicating success or error code.
*/
tBleStatus aci_att_read_by_group_type_req(uint16_t Connection_Handle,
                                          uint16_t Start_Handle,
                                          uint16_t End_Handle,
                                          uint8_t UUID_Type,
                                          UUID_t *UUID);
/**
  * @brief Send a Prepare Write Request.
The Prepare Write Request is used to request the server to prepare to write the value of an attribute. 
The responses of the procedure are given through the @ref aci_att_prepare_write_resp_event event. 
The end of the procedure is indicated by a @ref aci_gatt_proc_complete_event. 
  * @param Connection_Handle Connection handle for which the command is given.
  * Values:
  - 0x0000 ... 0x0EFF
  * @param Attr_Handle Handle of the attribute to be written
  * @param Val_Offset The offset of the first octet to be written
  * @param Attribute_Val_Length Length of attribute value (maximum value is ATT_MTU - 5).
  * @param Attribute_Val The value of the attribute to be written
  * @retval Value indicating success or error code.
*/
tBleStatus aci_att_prepare_write_req(uint16_t Connection_Handle,
                                     uint16_t Attr_Handle,
                                     uint16_t Val_Offset,
                                     uint8_t Attribute_Val_Length,
                                     uint8_t Attribute_Val[]);
/**
  * @brief Send an Execute Write Request.
The Execute Write Request is used to request the server to write or cancel the write 
of all the prepared values currently held in the prepare queue from this client. 
The result of the procedure is given through the @ref aci_att_exec_write_resp_event event. 
The end of the procedure is indicated by a @ref aci_gatt_proc_complete_event event. 
  * @param Connection_Handle Connection handle for which the command is given.
  * Values:
  - 0x0000 ... 0x0EFF
  * @param Execute Execute or cancel writes.
  * Values:
  - 0x00: Cancel all prepared writes
  - 0x01: Immediately write all pending prepared values
  * @retval Value indicating success or error code.
*/
tBleStatus aci_att_execute_write_req(uint16_t Connection_Handle,
                                     uint8_t Execute);
/**
  * @brief Start the GATT client procedure to discover all primary services on the server.
The responses of the procedure are given through the @ref aci_att_read_by_group_type_resp_event event.
  * @param Connection_Handle Connection handle for which the command is given.
  * Values:
  - 0x0000 ... 0x0EFF
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_disc_all_primary_services(uint16_t Connection_Handle);
/**
  * @brief Start the procedure to discover the primary services of the specified UUID on the server.
The responses of the procedure are given through the @ref aci_att_find_by_type_value_resp_event event.
The end of the procedure is indicated by a @ref aci_gatt_proc_complete_event event.
  * @param Connection_Handle Connection handle for which the command is given.
  * Values:
  - 0x0000 ... 0x0EFF
  * @param UUID_Type UUID type.
  * @param UUID See @ref UUID_t
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_disc_primary_service_by_uuid(uint16_t Connection_Handle,
                                                 uint8_t UUID_Type,
                                                 UUID_t *UUID);
/**
  * @brief Start the procedure to find all included services.
The responses of the procedure are given through the @ref aci_att_read_by_type_resp_event event.
The end of the procedure is indicated by a @ref aci_gatt_proc_complete_event event.
  * @param Connection_Handle Connection handle for which the command is given.
  * Values:
  - 0x0000 ... 0x0EFF
  * @param Start_Handle Start attribute handle of the service
  * @param End_Handle End attribute handle of the service
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_find_included_services(uint16_t Connection_Handle,
                                           uint16_t Start_Handle,
                                           uint16_t End_Handle);
/**
  * @brief Start the procedure to discover all the characteristics of a given service.
When the procedure is completed, a @ref aci_gatt_proc_complete_event event is generated.
Before procedure completion the response packets are given through
@ref aci_att_read_by_type_resp_event event.
  * @param Connection_Handle Connection handle for which the command is given.
  * Values:
  - 0x0000 ... 0x0EFF
  * @param Start_Handle Start attribute handle of the service
  * @param End_Handle End attribute handle of the service
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_disc_all_char_of_service(uint16_t Connection_Handle,
                                             uint16_t Start_Handle,
                                             uint16_t End_Handle);
/**
  * @brief Start the procedure to discover all the characteristics specified by a UUID.
When the procedure is completed, a @ref aci_gatt_proc_complete_event event is generated.
Before procedure completion the response packets are given through
@ref aci_gatt_disc_read_char_by_uuid_resp_event event.
  * @param Connection_Handle Connection handle for which the command is given.
  * Values:
  - 0x0000 ... 0x0EFF
  * @param Start_Handle Start attribute handle of the service
  * @param End_Handle End attribute handle of the service
  * @param UUID_Type UUID type.
  * @param UUID See @ref UUID_t
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_disc_char_by_uuid(uint16_t Connection_Handle,
                                      uint16_t Start_Handle,
                                      uint16_t End_Handle,
                                      uint8_t UUID_Type,
                                      UUID_t *UUID);
/**
  * @brief Start the procedure to discover all characteristic descriptors on the server.
When the procedure is completed, a @ref aci_gatt_proc_complete_event event is generated.
Before procedure completion the response packets are given through
@ref aci_att_find_info_resp_event event.
  * @param Connection_Handle Connection handle for which the command is given.
  * Values:
  - 0x0000 ... 0x0EFF
  * @param Char_Handle Handle of the characteristic value
  * @param End_Handle End handle of the characteristic
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_disc_all_char_desc(uint16_t Connection_Handle,
                                       uint16_t Char_Handle,
                                       uint16_t End_Handle);
/**
  * @brief Start the procedure to read the attribute value.
When the procedure is completed, a @ref aci_gatt_proc_complete_event event is generated.
Before procedure completion the response packet is given through @ref aci_att_read_resp_event event.
  * @param Connection_Handle Connection handle for which the command is given.
  * Values:
  - 0x0000 ... 0x0EFF
  * @param Attr_Handle Handle of the characteristic to be read
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_read_char_value(uint16_t Connection_Handle,
                                    uint16_t Attr_Handle);
/**
  * @brief Start the procedure to read all the characteristics specified by the UUID.
When the procedure is completed, a @ref aci_gatt_proc_complete_event event is generated.
Before procedure completion the response packets are given through
@ref aci_gatt_disc_read_char_by_uuid_resp_event event.
  * @param Connection_Handle Connection handle for which the command is given.
  * Values:
  - 0x0000 ... 0x0EFF
  * @param Start_Handle Starting handle of the range to be searched
  * @param End_Handle End handle of the range to be searched
  * @param UUID_Type UUID type.
  * @param UUID See @ref UUID_t
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_read_using_char_uuid(uint16_t Connection_Handle,
                                         uint16_t Start_Handle,
                                         uint16_t End_Handle,
                                         uint8_t UUID_Type,
                                         UUID_t *UUID);
/**
  * @brief Start the procedure to read a long characteristic value.
the procedure is completed, a @ref aci_gatt_proc_complete_event event is generated.
Before procedure completion the response packets are given through @ref aci_att_read_blob_resp_event event.
  * @param Connection_Handle Connection handle for which the command is given.
  * Values:
  - 0x0000 ... 0x0EFF
  * @param Attr_Handle Handle of the characteristic to be read
  * @param Val_Offset Offset from which the value needs to be read
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_read_long_char_value(uint16_t Connection_Handle,
                                         uint16_t Attr_Handle,
                                         uint16_t Val_Offset);
/**
  * @brief Start a procedure to read multiple characteristic values from a server.
This sub-procedure is used to read multiple Characteristic Values from a server when the
client knows the Characteristic Value Handles.
When the procedure is completed, a @ref aci_gatt_proc_complete_event event is generated.
Before procedure completion the response packets are given through
@ref aci_att_read_multiple_resp_event event.
  * @param Connection_Handle Connection handle for which the command is given.
  * Values:
  - 0x0000 ... 0x0EFF
  * @param Number_of_Handles The number of handles for which the value has to be read
  * @param Handle_Entry See @ref Handle_Entry_t
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_read_multiple_char_value(uint16_t Connection_Handle,
                                             uint8_t Number_of_Handles,
                                             Handle_Entry_t Handle_Entry[]);
/**
  * @brief Start the procedure to write a long characteristic value.
When the procedure is completed, a @ref aci_gatt_proc_complete_event event is generated.
During the procedure, @ref aci_att_prepare_write_resp_event and @ref aci_att_exec_write_resp_event
events are raised.
  * @param Connection_Handle Connection handle for which the command is given.
  * Values:
  - 0x0000 ... 0x0EFF
  * @param Attr_Handle Handle of the characteristic to be written
  * @param Attribute_Val_Length Length of the value to be written
  * @param Attribute_Val Value to be written
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_write_char_value(uint16_t Connection_Handle,
                                     uint16_t Attr_Handle,
                                     uint8_t Attribute_Val_Length,
                                     uint8_t Attribute_Val[]);
/**
  * @brief Start the procedure to write a long characteristic value.
When the procedure is completed, a @ref aci_gatt_proc_complete_event event is generated.
During the procedure, @ref aci_att_prepare_write_resp_event and @ref aci_att_exec_write_resp_event
events are raised.
  * @param Connection_Handle Connection handle for which the command is given.
  * Values:
  - 0x0000 ... 0x0EFF
  * @param Attr_Handle Handle of the attribute to be written
  * @param Val_Offset Offset at which the attribute has to be written
  * @param Attribute_Val_Length Length of the value to be written
  * @param Attribute_Val Value to be written
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_write_long_char_value(uint16_t Connection_Handle,
                                          uint16_t Attr_Handle,
                                          uint16_t Val_Offset,
                                          uint8_t Attribute_Val_Length,
                                          uint8_t Attribute_Val[]);
/**
  * @brief Start the procedure to write a characteristic reliably.
When the procedure is completed, a  @ref aci_gatt_proc_complete_event event is generated.
During the procedure, @ref aci_att_prepare_write_resp_event and @ref aci_att_exec_write_resp_event
events are raised.
  * @param Connection_Handle Connection handle for which the command is given.
  * Values:
  - 0x0000 ... 0x0EFF
  * @param Attr_Handle Handle of the attribute to be written
  * @param Val_Offset Offset at which the attribute has to be written
  * @param Attribute_Val_Length Length of the value to be written
  * @param Attribute_Val Value to be written
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_write_char_reliable(uint16_t Connection_Handle,
                                        uint16_t Attr_Handle,
                                        uint16_t Val_Offset,
                                        uint8_t Attribute_Val_Length,
                                        uint8_t Attribute_Val[]);
/**
  * @brief Start the procedure to write a long characteristic descriptor.
When the procedure is completed, a @ref aci_gatt_proc_complete_event event is generated.
During the procedure, @ref aci_att_prepare_write_resp_event and @ref aci_att_exec_write_resp_event
events are raised.
  * @param Connection_Handle Connection handle for which the command is given.
  * Values:
  - 0x0000 ... 0x0EFF
  * @param Attr_Handle Handle of the attribute to be written
  * @param Val_Offset Offset at which the attribute has to be written
  * @param Attribute_Val_Length Length of the value to be written
  * @param Attribute_Val Value to be written
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_write_long_char_desc(uint16_t Connection_Handle,
                                         uint16_t Attr_Handle,
                                         uint16_t Val_Offset,
                                         uint8_t Attribute_Val_Length,
                                         uint8_t Attribute_Val[]);
/**
  * @brief Start the procedure to read a long characteristic value.
When the procedure is completed, a @ref aci_gatt_proc_complete_event event is
generated. Before procedure completion the response packets are given through
@ref aci_att_read_blob_resp_event event.
  * @param Connection_Handle Connection handle for which the command is given.
  * Values:
  - 0x0000 ... 0x0EFF
  * @param Attr_Handle Handle of the characteristic descriptor
  * @param Val_Offset Offset from which the value needs to be read
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_read_long_char_desc(uint16_t Connection_Handle,
                                        uint16_t Attr_Handle,
                                        uint16_t Val_Offset);
/**
  * @brief Start the procedure to write a characteristic descriptor.
When the procedure is completed, a @ref aci_gatt_proc_complete_event event is generated.
  * @param Connection_Handle Connection handle for which the command is given.
  * Values:
  - 0x0000 ... 0x0EFF
  * @param Attr_Handle Handle of the attribute to be written
  * @param Attribute_Val_Length Length of the value to be written
  * @param Attribute_Val Value to be written
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_write_char_desc(uint16_t Connection_Handle,
                                    uint16_t Attr_Handle,
                                    uint8_t Attribute_Val_Length,
                                    uint8_t Attribute_Val[]);
/**
  * @brief Start the procedure to read the descriptor specified.
When the procedure is completed, a @ref aci_gatt_proc_complete_event event is generated.
Before procedure completion the response packet is given through @ref aci_att_read_resp_event event.
  * @param Connection_Handle Connection handle for which the command is given.
  * Values:
  - 0x0000 ... 0x0EFF
  * @param Attr_Handle Handle of the descriptor to be read
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_read_char_desc(uint16_t Connection_Handle,
                                   uint16_t Attr_Handle);
/**
  * @brief Start the procedure to write a characteristic value without waiting for any response from the
server. No events are generated after this command is executed.
  * @param Connection_Handle Connection handle for which the command is given.
  * Values:
  - 0x0000 ... 0x0EFF
  * @param Attr_Handle Handle of the attribute to be written
  * @param Attribute_Val_Length Length of the value to be written (maximum value is ATT_MTU - 3)
  * @param Attribute_Val Value to be written
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_write_without_resp(uint16_t Connection_Handle,
                                       uint16_t Attr_Handle,
                                       uint8_t Attribute_Val_Length,
                                       uint8_t Attribute_Val[]);
/**
  * @brief Start a signed write without response from the server.
The procedure is used to write a characteristic value with an authentication signature without waiting
for any response from the server. It cannot be used when the link is encrypted.
  * @param Connection_Handle Connection handle for which the command is given.
  * Values:
  - 0x0000 ... 0x0EFF
  * @param Attr_Handle Handle of the attribute to be written
  * @param Attribute_Val_Length Length of the value to be written (up to ATT_MTU - 13)
  * @param Attribute_Val Value to be written
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_signed_write_without_resp(uint16_t Connection_Handle,
                                              uint16_t Attr_Handle,
                                              uint8_t Attribute_Val_Length,
                                              uint8_t Attribute_Val[]);
/**
  * @brief Allow application to confirm indication. This command has to be sent when the application
receives the event @ref aci_gatt_indication_event.
  * @param Connection_Handle Connection handle for which the command is given.
  * Values:
  - 0x0000 ... 0x0EFF
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_confirm_indication(uint16_t Connection_Handle);
/**
  * @brief Allow or reject a write request from a client.
This command has to be sent by the application when it receives the
@ref aci_gatt_write_permit_req_event. If the write can be allowed, then the status and error
code has to be set to 0. If the write cannot be allowed, then the status has to be set to 1 and
the error code has to be set to the error code that has to be passed to the client.
  * @param Connection_Handle Connection handle for which the command is given.
  * Values:
  - 0x0000 ... 0x0EFF
  * @param Attr_Handle Handle of the attribute that was passed in the event EVT_BLUE_GATT_WRITE_PERMIT_REQ
  * @param Write_status If the value can be written or not.
  * Values:
  - 0x00: The value can be written to the attribute specified by attr_handle
  - 0x01: The value cannot be written to the attribute specified by the attr_handle
  * @param Error_Code The error code that has to be passed to the client in case the write has to be rejected
  * @param Attribute_Val_Length Length of the value to be written as passed in the event EVT_BLUE_GATT_WRITE_PERMIT_REQ
  * @param Attribute_Val Value as passed in the event EVT_BLUE_GATT_WRITE_PERMIT_REQ
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_write_resp(uint16_t Connection_Handle,
                               uint16_t Attr_Handle,
                               uint8_t Write_status,
                               uint8_t Error_Code,
                               uint8_t Attribute_Val_Length,
                               uint8_t Attribute_Val[]);
/**
  * @brief Allow the GATT server to send a response to a read request from a client.
The application has to send this command when it receives the
@ref aci_gatt_read_permit_req_event or @ref aci_gatt_read_multi_permit_req_event. This
command indicates to the stack that the response can be sent to the client. So if the
application wishes to update any of the attributes before they are read by the client, it has to
update the characteristic values using the @ref aci_gatt_update_char_value and then give
this command. The application should perform the required operations within 30 seconds.
Otherwise the GATT procedure will be timeout.
  * @param Connection_Handle Connection handle for which the command is given.
  * Values:
  - 0x0000 ... 0x0EFF
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_allow_read(uint16_t Connection_Handle);
/**
  * @brief This command sets the security permission for the attribute handle specified. Currently the
setting of security permission is allowed only for client configuration descriptor.
  * @param Serv_Handle Handle of the service which contains the attribute whose security permission has to be modified
  * @param Attr_Handle Handle of the attribute whose security permission has to be modified
  * @param Security_Permissions Security permission flags.
  * Flags:
  - 0x00: None
  - 0x01: AUTHEN_READ (Need authentication to read)
  - 0x02: AUTHOR_READ (Need authorization to read)
  - 0x04: ENCRY_READ (Need encryption to read)
  - 0x08: AUTHEN_WRITE (need authentication to write)
  - 0x10: AUTHOR_WRITE (need authorization to write)
  - 0x20: ENCRY_WRITE (need encryption to write)
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_set_security_permission(uint16_t Serv_Handle,
                                            uint16_t Attr_Handle,
                                            uint8_t Security_Permissions);
/**
  * @brief This command sets the value of the descriptor specified by charDescHandle.
  * @param Serv_Handle Handle of the service which contains the characteristic descriptor
  * @param Char_Handle Handle of the characteristic which contains the descriptor
  * @param Char_Desc_Handle Handle of the descriptor whose value has to be set
  * @param Val_Offset Offset from which the descriptor value has to be updated
  * @param Char_Desc_Value_Length Length of the descriptor value
  * @param Char_Desc_Value Descriptor value
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_set_desc_value(uint16_t Serv_Handle,
                                   uint16_t Char_Handle,
                                   uint16_t Char_Desc_Handle,
                                   uint16_t Val_Offset,
                                   uint8_t Char_Desc_Value_Length,
                                   uint8_t Char_Desc_Value[]);
/**
  * @brief Reads the value of the attribute handle specified from the local GATT database.
  * @param Attr_Handle Handle of the attribute to read
  * @param Offset Offset from which the value needs to be read
  * @param Value_Length_Requested Maximum number of octets to be returned as attribute value
  * @param[out] Length Length of the attribute value
  * @param[out] Value_Length Length in octets of the Value parameter
  * @param[out] Value Attribute value
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_read_handle_value(uint16_t Attr_Handle,
                                      uint16_t Offset,
                                      uint16_t Value_Length_Requested,
                                      uint16_t *Length,
                                      uint16_t *Value_Length,
                                      uint8_t Value[]);
/**
  * @brief This command is a more flexible version of @ref aci_gatt_update_char_value
                      to support update of long attribute up to 512 bytes and indicate selectively the generation of Indication/Notification.
  * @param Conn_Handle_To_Notify Connection handle to notify. Notify all subscribed clients if equal to 0x0000: DEPRECATED feature (still supported but not recommended).
  * @param Service_Handle Handle of service to which the characteristic belongs
  * @param Char_Handle Handle of the characteristic
  * @param Update_Type Allow Notification or Indication generation, if enabled in the client characteristic configuration descriptor. It also allows to enable the no retry feature if supported
  * Flags:
  - 0x00: No notification or indication (local characteristic value update) 
  - 0x01: Notification
  - 0x02: Indication
  - 0x04: Disable standard BLE Link Layer retransmission mechanism for notifications PDUs that are not acknowledged by the Link Layer of the peer device
  * @param Char_Length Total length of the characteristic value.
                                                  In case of a variable size characteristic, this field specifies the new length of the characteristic value after the update; in case of fixed length characteristic this field is ignored.
  * @param Value_Offset The offset from which the attribute value has to be updated.
  * @param Value_Length Length of the Value parameter in octets
  * @param Value Updated characteristic value
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_update_char_value_ext(uint16_t Conn_Handle_To_Notify,
                                          uint16_t Service_Handle,
                                          uint16_t Char_Handle,
                                          uint8_t Update_Type,
                                          uint16_t Char_Length,
                                          uint16_t Value_Offset,
                                          uint8_t Value_Length,
                                          uint8_t Value[]);
/**
  * @brief Deny the GATT server to send a response to a read request from a client.
The application may send this command when it receives the @ref aci_gatt_read_permit_req_event or  @ref aci_gatt_read_multi_permit_req_event.
This command indicates to the stack that the client is not allowed to read the requested characteristic due to e.g. application restrictions.
The Error code shall be either 0x08 (Insufficient Authorization) or a value in the range 0x80-0x9F (Application Error).
The application should issue the @ref aci_gatt_deny_read  or @ref aci_gatt_allow_read command within 30 seconds from the reception of
the @ref aci_gatt_read_permit_req_event or  @ref aci_gatt_read_multi_permit_req_event events otherwise the GATT procedure will issue a timeout.
  * @param Connection_Handle Connection handle for which the command is given.
  * Values:
  - 0x0000 ... 0x0EFF
  * @param Error_Code Error code for the command
  * Values:
  - 0x08: Insufficient Authorization
  - 0x80 ... 0x9F: Application Error
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_deny_read(uint16_t Connection_Handle,
                              uint8_t Error_Code);
/**
  * @brief This command sets the access permission for the attribute handle specified.
  * @param Serv_Handle Handle of the service which contains the attribute whose access permission has to be modified
  * @param Attr_Handle Handle of the attribute whose security permission has to be modified
  * @param Access_Permissions Access permission
  * Values:
  - 0x00: None
  - 0x01: READ
  - 0x02: WRITE
  - 0x04: WRITE_NO_RESP
  - 0x08: SIGNED_WRITE
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_set_access_permission(uint16_t Serv_Handle,
                                          uint16_t Attr_Handle,
                                          uint8_t Access_Permissions);
/**
 * @}
 */
/**
 *@defgroup L2CAP_API L2CAP API
 *@brief L2CAP API layer.
 *@{
 */
/**
  * @brief Send an L2CAP connection parameter update request from the slave to the master.
An @ref aci_l2cap_connection_update_resp_event event will be raised when the master will respond to the 
request (accepts or rejects).
  * @param Connection_Handle Connection handle for which the command is given.
  * Values:
  - 0x0000 ... 0x0EFF
  * @param Conn_Interval_Min Minimum value for the connection event interval. This shall be less
than or equal to Conn_Interval_Max.
Time = N * 1.25 msec.
  * Values:
  - 0x0006 (7.50 ms)  ... 0x0C80 (4000.00 ms) 
  * @param Conn_Interval_Max Maximum value for the connection event interval. This shall be
greater than or equal to Conn_Interval_Min.
Time = N * 1.25 msec.
  * Values:
  - 0x0006 (7.50 ms)  ... 0x0C80 (4000.00 ms) 
  * @param Slave_latency Slave latency for the connection in number of connection events.
  * Values:
  - 0x0000 ... 0x01F3
  * @param Timeout_Multiplier Defines connection timeout parameter in the following manner: Timeout Multiplier * 10ms.
  * @retval Value indicating success or error code.
*/
tBleStatus aci_l2cap_connection_parameter_update_req(uint16_t Connection_Handle,
                                                     uint16_t Conn_Interval_Min,
                                                     uint16_t Conn_Interval_Max,
                                                     uint16_t Slave_latency,
                                                     uint16_t Timeout_Multiplier);
/**
  * @brief Accept or reject a connection update. This command should be sent in response
to a @ref aci_l2cap_connection_update_req_event event from the controller. The accept parameter has to be
set if the connection parameters given in the event are acceptable.
  * @param Connection_Handle Connection handle for which the command is given.
  * Values:
  - 0x0000 ... 0x0EFF
  * @param Conn_Interval_Min Minimum value for the connection event interval. This shall be less
than or equal to Conn_Interval_Max.
Time = N * 1.25 msec.
  * Values:
  - 0x0006 (7.50 ms)  ... 0x0C80 (4000.00 ms) 
  * @param Conn_Interval_Max Maximum value for the connection event interval. This shall be
greater than or equal to Conn_Interval_Min.
Time = N * 1.25 msec.
  * Values:
  - 0x0006 (7.50 ms)  ... 0x0C80 (4000.00 ms) 
  * @param Slave_latency Slave latency for the connection in number of connection events.
  * Values:
  - 0x0000 ... 0x01F3
  * @param Timeout_Multiplier Defines connection timeout parameter in the following manner: Timeout Multiplier * 10ms.
  * @param Minimum_CE_Length Information parameter about the minimum length of connection
needed for this LE connection.
Time = N * 0.625 msec.
  * @param Maximum_CE_Length Information parameter about the maximum length of connection needed
for this LE connection.
Time = N * 0.625 msec.
  * @param Identifier Identifier received in ACI_L2CAP_Connection_Update_Req event.
  * @param Accept Specify if connection update parameters are acceptable or not.
  * Values:
  - 0x00: Reject
  - 0x01: Accept
  * @retval Value indicating success or error code.
*/
tBleStatus aci_l2cap_connection_parameter_update_resp(uint16_t Connection_Handle,
                                                      uint16_t Conn_Interval_Min,
                                                      uint16_t Conn_Interval_Max,
                                                      uint16_t Slave_latency,
                                                      uint16_t Timeout_Multiplier,
                                                      uint16_t Minimum_CE_Length,
                                                      uint16_t Maximum_CE_Length,
                                                      uint8_t Identifier,
                                                      uint8_t Accept);
/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* _BLUENRG1_API_H_ */
