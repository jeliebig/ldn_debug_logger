#pragma once
#include <cstring>
#include <atomic>

#include <stratosphere.hpp>

#include "../wlan_lcl_types.hpp"

// NOTE: Cmd 48 supported firmwares: 4.0.0-8.1.0 and 10.0.0+
// NOTE: Cmd 49-52 different for the following firmware versions: [6.0.0-8.1.0] and [13.0.0+]

#define AMS_WLAN_LCL_INTERFACE_INFO(C, H)                                                                                                                                                \
    AMS_SF_METHOD_INFO(C, H, 0, Result, OpenMode, (ams::mitm::wlan::Mode mode), (mode))                                                                                                  \
    AMS_SF_METHOD_INFO(C, H, 1, Result, CloseMode, (ams::mitm::wlan::Mode mode), (mode))                                                                                                 \
    AMS_SF_METHOD_INFO(C, H, 2, Result, GetMacAddress, (ams::sf::Out<LdnMacAddress> out), (out))                                                                                         \
    AMS_SF_METHOD_INFO(C, H, 3, Result, CreateBss, (ams::mitm::wlan::Bss in), (in))                                                                                                      \
    AMS_SF_METHOD_INFO(C, H, 4, Result, DestroyBss, (), ())                                                                                                                              \
    AMS_SF_METHOD_INFO(C, H, 5, Result, StartScan, (const ams::sf::InMapAliasArray<ams::mitm::wlan::ScanRequest> &request), (request))                                                                             \
    AMS_SF_METHOD_INFO(C, H, 6, Result, StopScan, (), ())                                                                                                                                \
    AMS_SF_METHOD_INFO(C, H, 7, Result, Connect, (ams::mitm::wlan::ConnectParam in), (in))                                                                                               \
    AMS_SF_METHOD_INFO(C, H, 8, Result, CancelConnect, (), ())                                                                                                                           \
    AMS_SF_METHOD_INFO(C, H, 9, Result, Join, (ams::mitm::wlan::ConnectParam in), (in))                                                                                                  \
    AMS_SF_METHOD_INFO(C, H, 10, Result, CancelJoin, (), ())                                                                                                                             \
    AMS_SF_METHOD_INFO(C, H, 11, Result, Disconnect, (ams::mitm::wlan::DisconnectData in), (in))                                                                                         \
    AMS_SF_METHOD_INFO(C, H, 12, Result, SetBeaconLostCount, (u32 beaconLostCount), (beaconLostCount))                                                                                   \
    AMS_SF_METHOD_INFO(C, H, 13, Result, GetSystemEvent, (u32 systemEventType, ams::sf::Out<ams::sf::CopyHandle> eventHandle), (systemEventType, eventHandle))                           \
    AMS_SF_METHOD_INFO(C, H, 14, Result, GetConnectionStatus, (ams::sf::Out<ams::mitm::wlan::ConnectionStatus> status), (status))                                                        \
    AMS_SF_METHOD_INFO(C, H, 15, Result, GetClientStatus, (ams::sf::OutMapAliasArray<ams::mitm::wlan::ClientStatus> status), (status))                                                   \
    AMS_SF_METHOD_INFO(C, H, 16, Result, GetBssIndicationEvent, (ams::sf::Out<ams::sf::CopyHandle> eventHandle), (eventHandle))                                                          \
    AMS_SF_METHOD_INFO(C, H, 17, Result, GetBssIndicationInfo, (ams::sf::OutMapAliasBuffer data), (data))                                                                                \
    AMS_SF_METHOD_INFO(C, H, 18, Result, GetState, (ams::sf::Out<ams::mitm::wlan::State> state), (state))                                                                                \
    AMS_SF_METHOD_INFO(C, H, 19, Result, GetAllowedChannels, (ams::sf::Out<u32> allowedChannelsCount, ams::sf::OutPointerBuffer out_data), (allowedChannelsCount, out_data))             \
    AMS_SF_METHOD_INFO(C, H, 20, Result, AddIe, (u32 managementFrameType, ams::sf::Out<u32> ie, const ams::sf::InBuffer &in_buffer), (managementFrameType, ie, in_buffer))               \
    AMS_SF_METHOD_INFO(C, H, 21, Result, DeleteIe, (u32 ie), (ie))                                                                                                                       \
    AMS_SF_METHOD_INFO(C, H, 22, Result, PutFrameRaw, (const ams::sf::InBuffer &in_buffer), (in_buffer))                                                                                 \
    AMS_SF_METHOD_INFO(C, H, 23, Result, CancelGetFrame, (u32 rxId), (rxId))                                                                                                             \
    AMS_SF_METHOD_INFO(C, H, 24, Result, CreateRxEntry, (u32 capacity, ams::sf::Out<u32> rxId, const ams::sf::InPointerBuffer &in_array), (capacity, rxId, in_array))                    \
    AMS_SF_METHOD_INFO(C, H, 25, Result, DeleteRxEntry, (u32 rxId), (rxId))                                                                                                              \
    AMS_SF_METHOD_INFO(C, H, 26, Result, AddEthertypeToRxEntry, (u32 rxId, u32 protocol), (rxId, protocol))                                                                              \
    AMS_SF_METHOD_INFO(C, H, 27, Result, DeleteEthertypeFromRxEntry, (u16 protocol, ams::sf::Out<u32> out), (protocol, out))                                                             \
    AMS_SF_METHOD_INFO(C, H, 28, Result, AddMatchingDataToRxEntry, (u32 rxId, const ams::sf::InPointerBuffer &in_buffer), (rxId, in_buffer))                                             \
    AMS_SF_METHOD_INFO(C, H, 29, Result, RemoveMatchingDataFromRxEntry, (u32 rxId, const ams::sf::InPointerBuffer &in_buffer), (rxId, in_buffer))                                        \
    AMS_SF_METHOD_INFO(C, H, 30, Result, GetScanResult, (const ams::sf::InPointerBuffer &in_buffer, ams::sf::OutMapAliasArray<ams::mitm::wlan::ScanResult> result), (in_buffer, result)) \
    AMS_SF_METHOD_INFO(C, H, 31, Result, PutActionFrameOneShot, (ams::mitm::wlan::PutActionFrameOneShotData in, const ams::sf::InMapAliasBuffer &in_array), (in, in_array))              \
    AMS_SF_METHOD_INFO(C, H, 32, Result, SetActionFrameWithBeacon, (const ams::sf::InMapAliasBuffer &in_buffer), (in_buffer))                                                            \
    AMS_SF_METHOD_INFO(C, H, 33, Result, CancelActionFrameWithBeacon, (), ())                                                                                                            \
    AMS_SF_METHOD_INFO(C, H, 34, Result, CreateRxEntryForActionFrame, (u32 capacity, ams::sf::Out<u32> rxId, const ams::sf::InPointerBuffer &in_buffer), (capacity, rxId, in_buffer))    \
    AMS_SF_METHOD_INFO(C, H, 35, Result, DeleteRxEntryForActionFrame, (u32 rxId), (rxId))                                                                                                \
    AMS_SF_METHOD_INFO(C, H, 36, Result, AddSubtypeToRxEntryForActionFrame, (u32 rxId, u32 subType), (rxId, subType))                                                                    \
    AMS_SF_METHOD_INFO(C, H, 37, Result, DeleteSubtypeFromRxEntryForActionFrame, (u32 subType, ams::sf::Out<u32> out), (subType, out))                                                   \
    AMS_SF_METHOD_INFO(C, H, 38, Result, CancelGetActionFrame, (u32 rxId), (rxId))                                                                                                       \
    AMS_SF_METHOD_INFO(C, H, 39, Result, GetRssi, (ams::sf::Out<u32> rssi), (rssi))                                                                                                      \
    AMS_SF_METHOD_INFO(C, H, 40, Result, SetMaxAssociationNumber, (u32 maxAssociationNumber), (maxAssociationNumber))                                                                    \
    AMS_SF_METHOD_INFO(C, H, 41, Result, Cmd41, (ams::sf::Out<u32> out, ams::sf::OutPointerBuffer out_buffer), (out, out_buffer))                                                        \
    AMS_SF_METHOD_INFO(C, H, 42, Result, Cmd42, (u8 in), (in))                                                                                                                           \
    AMS_SF_METHOD_INFO(C, H, 43, Result, Cmd43, (ams::mitm::wlan::Cmd43Data in), (in))                                                                                                   \
    AMS_SF_METHOD_INFO(C, H, 44, Result, Cmd44, (ams::mitm::wlan::Bss in), (in))                                                                                                         \
    AMS_SF_METHOD_INFO(C, H, 45, Result, Cmd45, (ams::mitm::wlan::Cmd45Data in, const ams::sf::InMapAliasBuffer &in_buffer), (in, in_buffer), hos::Version_4_0_0)                        \
    AMS_SF_METHOD_INFO(C, H, 46, Result, Cmd46, (u8 in), (in), hos::Version_4_0_0)                                                                                                       \
    AMS_SF_METHOD_INFO(C, H, 47, Result, Cmd47, (ams::mitm::wlan::Cmd47Data in, ams::sf::Out<u32> out), (in, out), hos::Version_4_0_0)                                                   \
    AMS_SF_METHOD_INFO(C, H, 48, Result, Cmd48, (u32 in), (in), hos::Version_10_0_0)                                                                                                     \
    AMS_SF_METHOD_INFO(C, H, 49, Result, Cmd49, (u32 in), (in), hos::Version_13_0_0)                                                                                                     \
    AMS_SF_METHOD_INFO(C, H, 50, Result, Cmd50, (), (), hos::Version_13_0_0)                                                                                                             \
    AMS_SF_METHOD_INFO(C, H, 51, Result, Cmd51, (ams::sf::Out<u32> out), (out), hos::Version_13_0_0)

AMS_SF_DEFINE_MITM_INTERFACE(ams::mitm::wlan, IWlanLclMitmInterface, AMS_WLAN_LCL_INTERFACE_INFO, 0x4F84FB56)
