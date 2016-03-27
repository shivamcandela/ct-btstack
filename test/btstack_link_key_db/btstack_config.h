//
// btstack_config.h for Arduino port
//

#ifndef __BTSTACK_CONFIG
#define __BTSTACK_CONFIG

// Port related features
#define HAVE_INIT_SCRIPT
#define HAVE_TIME

// BTstack features that can be enabled
#define ENABLE_BLE
#define ENABLE_LOG_DEBUG
#define ENABLE_LOG_ERROR
#define ENABLE_LOG_INFO 
#define ENABLE_LOG_INTO_HCI_DUMP
#define ENABLE_SDP_DES_DUMP
#define ENABLE_SDP_EXTRA_QUERIES

// BTstack configuration. buffers, sizes, ...
#define HCI_ACL_PAYLOAD_SIZE 52
#define HCI_INCOMING_PRE_BUFFER_SIZE 4

#define MAX_NO_HCI_CONNECTIONS 0
#define MAX_NO_GATT_CLIENTS 0
#define MAX_NO_GATT_SUBCLIENTS 0
#define MAX_NO_L2CAP_SERVICES  0
#define MAX_NO_L2CAP_CHANNELS  0
#define MAX_NO_RFCOMM_MULTIPLEXERS 0
#define MAX_NO_RFCOMM_SERVICES 0
#define MAX_NO_RFCOMM_CHANNELS 0
#define MAX_NO_BNEP_SERVICES 0
#define MAX_NO_BNEP_CHANNELS 0
#define MAX_NO_BTSTACK_LINK_KEY_DB_MEMORYS  2
#define MAX_NO_HFP_CONNECTIONS 0
#define MAX_NO_WHITELIST_ENTRIES 0
#define MAX_NO_SM_LOOKUP_ENTRIES 0
#define MAX_NO_SERVICE_RECORD_ITEMS 0

#endif
