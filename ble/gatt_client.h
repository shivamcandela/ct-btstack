/*
 * Copyright (C) 2011-2014 by BlueKitchen GmbH
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the copyright holders nor the names of
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 * 4. This software may not be used in a commercial product
 *    without an explicit license granted by the copyright holder.
 *
 * THIS SOFTWARE IS PROVIDED BY MATTHIAS RINGWALD AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL MATTHIAS
 * RINGWALD OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF
 * THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 */


#ifndef btstack_gatt_client_h
#define btstack_gatt_client_h

#include "hci.h"

#if defined __cplusplus
extern "C" {
#endif
    
//*************** gatt client
typedef enum {
    P_READY,
    P_W2_SEND_SERVICE_QUERY,
    P_W4_SERVICE_QUERY_RESULT,
    P_W2_SEND_SERVICE_WITH_UUID_QUERY,
    P_W4_SERVICE_WITH_UUID_RESULT,
    
    P_W2_SEND_CHARACTERISTIC_QUERY,
    P_W4_CHARACTERISTIC_QUERY_RESULT,
    P_W2_SEND_CHARACTERISTIC_WITH_UUID_QUERY,
    P_W4_CHARACTERISTIC_WITH_UUID_QUERY_RESULT,
    
    P_W2_SEND_ALL_CHARACTERISTIC_DESCRIPTORS_QUERY,
    P_W4_ALL_CHARACTERISTIC_DESCRIPTORS_QUERY_RESULT,
    
    P_W2_SEND_INCLUDED_SERVICE_QUERY,
    P_W4_INCLUDED_SERVICE_QUERY_RESULT,
    P_W2_SEND_INCLUDED_SERVICE_WITH_UUID_QUERY,
    P_W4_INCLUDED_SERVICE_UUID_WITH_QUERY_RESULT,
    
    P_W2_SEND_READ_CHARACTERISTIC_VALUE_QUERY,
    P_W4_READ_CHARACTERISTIC_VALUE_RESULT,
    
    P_W2_SEND_READ_BLOB_QUERY,
    P_W4_READ_BLOB_RESULT,
    
    P_W2_SEND_WRITE_CHARACTERISTIC_VALUE,
    P_W4_WRITE_CHARACTERISTIC_VALUE_RESULT,
    
    P_W2_PREPARE_WRITE,
    P_W4_PREPARE_WRITE_RESULT,
    P_W2_PREPARE_RELIABLE_WRITE,
    P_W4_PREPARE_RELIABLE_WRITE_RESULT,
    
    P_W2_EXECUTE_PREPARED_WRITE,
    P_W4_EXECUTE_PREPARED_WRITE_RESULT,
    P_W2_CANCEL_PREPARED_WRITE,
    P_W4_CANCEL_PREPARED_WRITE_RESULT,
    
    P_W2_SEND_READ_CLIENT_CHARACTERISTIC_CONFIGURATION_QUERY,
    P_W4_READ_CLIENT_CHARACTERISTIC_CONFIGURATION_QUERY_RESULT,
    P_W2_WRITE_CLIENT_CHARACTERISTIC_CONFIGURATION,
    P_W4_CLIENT_CHARACTERISTIC_CONFIGURATION_RESULT,
    
    P_W2_SEND_READ_CHARACTERISTIC_DESCRIPTOR_QUERY,
    P_W4_READ_CHARACTERISTIC_DESCRIPTOR_RESULT,
    
    P_W2_SEND_READ_BLOB_CHARACTERISTIC_DESCRIPTOR_QUERY,
    P_W4_READ_BLOB_CHARACTERISTIC_DESCRIPTOR_RESULT,
    
    P_W2_SEND_WRITE_CHARACTERISTIC_DESCRIPTOR,
    P_W4_WRITE_CHARACTERISTIC_DESCRIPTOR_RESULT,
    
    P_W2_PREPARE_WRITE_CHARACTERISTIC_DESCRIPTOR,
    P_W4_PREPARE_WRITE_CHARACTERISTIC_DESCRIPTOR_RESULT,
    P_W2_EXECUTE_PREPARED_WRITE_CHARACTERISTIC_DESCRIPTOR,
    P_W4_EXECUTE_PREPARED_WRITE_CHARACTERISTIC_DESCRIPTOR_RESULT
} gatt_client_state_t;
    
    
typedef enum{
    SEND_MTU_EXCHANGE,
    SENT_MTU_EXCHANGE,
    MTU_EXCHANGED
} gatt_client_mtu_t;

typedef struct gatt_client{
    linked_item_t    item;
    gatt_client_state_t gatt_client_state;
    // le_central_state_t le_central_state;
    
    uint16_t handle;
    
    uint8_t   address_type;
    bd_addr_t address;
    uint16_t mtu;
    gatt_client_mtu_t mtu_state;
    
    uint16_t uuid16;
    uint8_t  uuid128[16];
    
    uint16_t start_group_handle;
    uint16_t end_group_handle;
    
    uint16_t query_start_handle;
    uint16_t query_end_handle;
    
    uint8_t  characteristic_properties;
    uint16_t characteristic_start_handle;
    
    uint16_t attribute_handle;
    uint16_t attribute_offset;
    uint16_t attribute_length;
    uint8_t* attribute_value;
    
    uint16_t client_characteristic_configuration_handle;
    uint8_t client_characteristic_configuration_value[2];
    
    uint8_t  filter_with_uuid;
    uint8_t  send_confirmation;
    
} gatt_client_t;

typedef struct gatt_complete_event{
    uint8_t   type;
    gatt_client_t * device;
    uint8_t status;
} gatt_complete_event_t;

typedef struct le_service{
    uint16_t start_group_handle;
    uint16_t end_group_handle;
    uint16_t uuid16;
    uint8_t  uuid128[16];
} le_service_t;

typedef struct le_service_event{
    uint8_t  type;
    le_service_t service;
} le_service_event_t;

typedef struct le_characteristic{
    uint16_t start_handle;
    uint16_t value_handle;
    uint16_t end_handle;
    uint16_t properties;
    uint16_t uuid16;
    uint8_t  uuid128[16];
} le_characteristic_t;

typedef struct le_characteristic_event{
    uint8_t  type;
    le_characteristic_t characteristic;
} le_characteristic_event_t;

typedef struct le_characteristic_descriptor{
    // no properties
    uint16_t handle;
    uint16_t uuid16;
    uint8_t  uuid128[16];
    // TODO move to le_characteristic_descriptor_event_t
    uint16_t value_length;
    uint16_t value_offset;
    uint8_t * value;
} le_characteristic_descriptor_t;

typedef struct le_characteristic_descriptor_event{
    uint8_t  type;
    le_characteristic_descriptor_t characteristic_descriptor;
} le_characteristic_descriptor_event_t;

typedef struct le_characteristic_value{
    
} le_characteristic_value_t;

typedef struct le_characteristic_value_event{
    uint8_t  type;
    uint16_t characteristic_value_handle;
    uint16_t characteristic_value_blob_length;
    uint16_t characteristic_value_offset;
    uint8_t * characteristic_value; 
} le_characteristic_value_event_t;

    
void gatt_client_init();
void gatt_client_register_handler(void (*le_callback)(le_event_t * event));
void gatt_packet_handler(void * connection, uint8_t packet_type, uint16_t channel, uint8_t *packet, uint16_t size);

// start/stop gatt client
void gatt_client_start(gatt_client_t *context, uint16_t handle);
void gatt_client_stop(gatt_client_t *context);
gatt_client_t * get_gatt_client_context_for_handle(uint16_t handle);

// returns primary services
le_command_status_t gatt_client_discover_primary_services(gatt_client_t *context);
// { type (8), gatt_client_t *context, le_service * }


//TODO: define uuid type
le_command_status_t gatt_client_discover_primary_services_by_uuid16(gatt_client_t *context, uint16_t uuid16);
le_command_status_t gatt_client_discover_primary_services_by_uuid128(gatt_client_t *context, const uint8_t * uuid);

// Returns included services.
// Information about service type (primary/secondary) can be retrieved either by sending an ATT find query or
// by comparing the service to the list of primary services obtained by calling le_central_get_services.
le_command_status_t gatt_client_find_included_services_for_service(gatt_client_t *context, le_service_t *service);
// { type (8), gatt_client_t *context, le_service * }

// returns characteristics, no included services
le_command_status_t gatt_client_discover_characteristics_for_service(gatt_client_t *context, le_service_t *service);
// { type (8), gatt_client_t *context, service_handle, le_characteristic *}

// gets all characteristics in handle range, and returns those that match the given UUID.
le_command_status_t gatt_client_discover_characteristics_for_handle_range_by_uuid16(gatt_client_t *context, uint16_t start_handle, uint16_t end_handle, uint16_t uuid16);
// { type (8), gatt_client_t *context, service_handle, le_characteristic *}
le_command_status_t gatt_client_discover_characteristics_for_handle_range_by_uuid128(gatt_client_t *context, uint16_t start_handle, uint16_t end_handle, uint8_t * uuid);
// { type (8), gatt_client_t *context, service_handle, le_characteristic *}

// more convenience
le_command_status_t gatt_client_discover_characteristics_for_service_by_uuid16 (gatt_client_t *context, le_service_t *service, uint16_t  uuid16);
le_command_status_t gatt_client_discover_characteristics_for_service_by_uuid128(gatt_client_t *context, le_service_t *service, uint8_t * uuid128);

// returns handle and uuid16 of a descriptor
le_command_status_t gatt_client_discover_characteristic_descriptors(gatt_client_t *context, le_characteristic_t *characteristic);

// Reads value of characteristic using characteristic value handle
le_command_status_t gatt_client_read_value_of_characteristic(gatt_client_t *context, le_characteristic_t *characteristic);
le_command_status_t gatt_client_read_value_of_characteristic_using_value_handle(gatt_client_t *context, uint16_t characteristic_value_handle);

// Reads long caharacteristic value.
le_command_status_t gatt_client_read_long_value_of_characteristic(gatt_client_t *context, le_characteristic_t *characteristic);
le_command_status_t gatt_client_read_long_value_of_characteristic_using_value_handle(gatt_client_t *context, uint16_t characteristic_value_handle);


le_command_status_t gatt_client_write_value_of_characteristic_without_response(gatt_client_t *context, uint16_t characteristic_value_handle, uint16_t length, uint8_t * data);
le_command_status_t gatt_client_write_value_of_characteristic(gatt_client_t *context, uint16_t characteristic_value_handle, uint16_t length, uint8_t * data);

le_command_status_t gatt_client_write_long_value_of_characteristic(gatt_client_t *context, uint16_t characteristic_value_handle, uint16_t length, uint8_t * data);
le_command_status_t gatt_client_reliable_write_long_value_of_characteristic(gatt_client_t *context, uint16_t characteristic_value_handle, uint16_t length, uint8_t * data);


le_command_status_t gatt_client_read_characteristic_descriptor(gatt_client_t *context, le_characteristic_descriptor_t * descriptor);
le_command_status_t gatt_client_read_long_characteristic_descriptor(gatt_client_t *context, le_characteristic_descriptor_t * descriptor);

le_command_status_t gatt_client_write_characteristic_descriptor(gatt_client_t *context, le_characteristic_descriptor_t * descriptor, uint16_t length, uint8_t * data);
le_command_status_t gatt_client_write_long_characteristic_descriptor(gatt_client_t *context, le_characteristic_descriptor_t * descriptor, uint16_t length, uint8_t * data);

le_command_status_t gatt_client_write_client_characteristic_configuration(gatt_client_t *context, le_characteristic_t * characteristic, uint16_t configuration);

// { read/write/subscribe/unsubscribe confirm/result}

// { type, le_peripheral *, characteristic handle, int len, uint8_t data[]?}

#if defined __cplusplus
}
#endif

#endif