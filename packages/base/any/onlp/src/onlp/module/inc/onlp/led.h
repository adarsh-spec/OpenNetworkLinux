/************************************************************
 * <bsn.cl fy=2014 v=onl>
 *
 *        Copyright 2014, 2015 Big Switch Networks, Inc.
 *
 * Licensed under the Eclipse Public License, Version 1.0 (the
 * "License"); you may not use this file except in compliance
 * with the License. You may obtain a copy of the License at
 *
 *        http://www.eclipse.org/legal/epl-v10.html
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
 * either express or implied. See the License for the specific
 * language governing permissions and limitations under the
 * License.
 *
 * </bsn.cl>
 ************************************************************
 *
 * LED Management
 *
 ***********************************************************/
#ifndef __ONLP_LED_H__
#define __ONLP_LED_H__

#include <onlp/onlp.h>
#include <onlp/oids.h>

/* <auto.start.enum(tag:led).define> */
/** onlp_led_caps */
typedef enum onlp_led_caps_e {
    ONLP_LED_CAPS_ON_OFF = (1 << 0),           // 1
    ONLP_LED_CAPS_CHAR = (1 << 1),             // 2
    ONLP_LED_CAPS_RED = (1 << 2),               // 4
    ONLP_LED_CAPS_RED_BLINKING = (1 << 3),     // 8
    ONLP_LED_CAPS_ORANGE = (1 << 4),            // 16
    ONLP_LED_CAPS_ORANGE_BLINKING = (1 << 5),  // 32
    ONLP_LED_CAPS_YELLOW = (1 << 6),            // 64
    ONLP_LED_CAPS_YELLOW_BLINKING = (1 << 7),   // 128
    ONLP_LED_CAPS_GREEN = (1 << 8),             // 256
    ONLP_LED_CAPS_GREEN_BLINKING = (1 << 9),    // 512
    ONLP_LED_CAPS_BLUE = (1 << 10),             // 1024
    ONLP_LED_CAPS_BLUE_BLINKING = (1 << 11),    // 2048
    ONLP_LED_CAPS_PURPLE = (1 << 12),           // 4096
    ONLP_LED_CAPS_PURPLE_BLINKING = (1 << 13),  // 8192
    ONLP_LED_CAPS_AUTO = (1 << 14),             // 16384
    ONLP_LED_CAPS_AUTO_BLINKING = (1 << 15),    // 32768
} onlp_led_caps_t;

typedef enum onlp_led_mode_e {
    ONLP_LED_MODE_OFF = 0,                       // 0
    ONLP_LED_MODE_ON = 1,                        // 1
    ONLP_LED_MODE_BLINKING = 2,                  // 2
    ONLP_LED_MODE_RED = 3,                       // 3
    ONLP_LED_MODE_RED_BLINKING = 4,              // 4
    ONLP_LED_MODE_ORANGE = 5,                    // 5
    ONLP_LED_MODE_ORANGE_BLINKING = 6,           // 6
    ONLP_LED_MODE_YELLOW = 7,                    // 7
    ONLP_LED_MODE_YELLOW_BLINKING = 8,           // 8
    ONLP_LED_MODE_GREEN = 9,                     // 9
    ONLP_LED_MODE_GREEN_BLINKING = 10,           // 10
    ONLP_LED_MODE_BLUE = 11,                     // 11
    ONLP_LED_MODE_BLUE_BLINKING = 12,            // 12
    ONLP_LED_MODE_PURPLE = 13,                   // 13
    ONLP_LED_MODE_PURPLE_BLINKING = 14,          // 14
    ONLP_LED_MODE_AUTO = 15,                     // 15
    ONLP_LED_MODE_AUTO_BLINKING = 16,            // 16
} onlp_led_mode_t;

/** onlp_led_status */
typedef enum onlp_led_status_e {
    ONLP_LED_STATUS_PRESENT = (1 << 0),
    ONLP_LED_STATUS_FAILED = (1 << 1),
    ONLP_LED_STATUS_ON = (1 << 2),
} onlp_led_status_t;
/* <auto.end.enum(tag:led).define> */


/**
 * LED information structure.
 */
typedef struct onlp_led_info_s {
    /** Header */
    onlp_oid_hdr_t hdr;

    /** Status */
    uint32_t status;

    /** Capabilities */
    uint32_t caps;

    /** Current mode, if capable. */
    onlp_led_mode_t mode;

    /** Current char, if capable. */
    char character;

} onlp_led_info_t;

/**
 * @brief Initialize the LED subsystem.
 */
int onlp_led_init(void);

/**
 * @brief Get LED information.
 * @param id The LED OID
 * @param rv [out] Receives the information structure.
 */
int onlp_led_info_get(onlp_oid_t id, onlp_led_info_t* rv);

/**
 * @brief Get the LED operational status.
 * @param id The LED OID
 * @param rv [out] Receives the operational status.
 */
int onlp_led_status_get(onlp_oid_t id, uint32_t* rv);

/**
 * @brief Get the LED header.
 * @param id The LED OID
 * @param rv [out] Receives the header.
 */
int onlp_led_hdr_get(onlp_oid_t id, onlp_oid_hdr_t* rv);

/**
 * @brief Turn an LED on or off.
 * @param id The LED OID
 * @param on_or_off Led on (1) or LED off (0)
 * @param Relevant if the LED has the ON_OFF capability.
 * @note For the purposes of this function the
 * interpretation of "on" for multi-mode or multi-color LEDs
 * is up to the platform implementation.
 */
int onlp_led_set(onlp_oid_t id, int on_or_off);

/**
 * @brief Set the LED color
 * @param id The LED OID
 * @param color The color.
 * @note Only relevant if the LED supports the color capability.
 */
int onlp_led_mode_set(onlp_oid_t id, onlp_led_mode_t color);


/**
 * @brief Set the LED char
 * @param id The LED OID
 * @param c The character.
 * @note Only relevant if the LED supports the char capability.
 */
int onlp_led_char_set(onlp_oid_t id, char c);

/**
 * @brief LED OID debug dump
 * @param id The LED OID
 * @param pvs The output pvs
 * @param flags The output flags
 */
void onlp_led_dump(onlp_oid_t oid, aim_pvs_t* pvs, uint32_t flags);

/**
 * @brief Show the given LED OID.
 * @param id The LED OID
 * @param pvs The output pvs
 * @param flags The output flags
 */
void onlp_led_show(onlp_oid_t id, aim_pvs_t* pvs, uint32_t flags);




/******************************************************************************
 *
 * Enumeration Support Definitions.
 *
 * Please do not add additional code beyond this point.
 *
 *****************************************************************************/
/* <auto.start.enum(tag:led).supportheader> */
/** Enum names. */
const char* onlp_led_caps_name(onlp_led_caps_t e);

/** Enum values. */
int onlp_led_caps_value(const char* str, onlp_led_caps_t* e, int substr);

/** Enum descriptions. */
const char* onlp_led_caps_desc(onlp_led_caps_t e);

/** Enum validator. */
int onlp_led_caps_valid(onlp_led_caps_t e);

/** validator */
#define ONLP_LED_CAPS_VALID(_e) \
    (onlp_led_caps_valid((_e)))

/** onlp_led_caps_map table. */
extern aim_map_si_t onlp_led_caps_map[];
/** onlp_led_caps_desc_map table. */
extern aim_map_si_t onlp_led_caps_desc_map[];

/** Enum names. */
const char* onlp_led_mode_name(onlp_led_mode_t e);

/** Enum values. */
int onlp_led_mode_value(const char* str, onlp_led_mode_t* e, int substr);

/** Enum descriptions. */
const char* onlp_led_mode_desc(onlp_led_mode_t e);

/** Enum validator. */
int onlp_led_mode_valid(onlp_led_mode_t e);

/** validator */
#define ONLP_LED_MODE_VALID(_e) \
    (onlp_led_mode_valid((_e)))

/** onlp_led_mode_map table. */
extern aim_map_si_t onlp_led_mode_map[];
/** onlp_led_mode_desc_map table. */
extern aim_map_si_t onlp_led_mode_desc_map[];

/** Enum names. */
const char* onlp_led_status_name(onlp_led_status_t e);

/** Enum values. */
int onlp_led_status_value(const char* str, onlp_led_status_t* e, int substr);

/** Enum descriptions. */
const char* onlp_led_status_desc(onlp_led_status_t e);

/** Enum validator. */
int onlp_led_status_valid(onlp_led_status_t e);

/** validator */
#define ONLP_LED_STATUS_VALID(_e) \
    (onlp_led_status_valid((_e)))

/** onlp_led_status_map table. */
extern aim_map_si_t onlp_led_status_map[];
/** onlp_led_status_desc_map table. */
extern aim_map_si_t onlp_led_status_desc_map[];
/* <auto.end.enum(tag:led).supportheader> */

#endif /* __ONLP_LED_H__ */
