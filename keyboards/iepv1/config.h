// Copyright 2024 er1c-zh (@er1c-zh)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT

/* common */
#define SERIAL_DEBUG
#define OS_DETECTION_DEBUG_ENABLE

/* ws2812 */

// #define RGBLIGHT_LED_COUNT 2
// #define RGBLIGHT_LAYERS
// #define WS2812_BYTE_ORDER WS2812_BYTE_ORDER_GRB
// #define WS2812_DI_PIN A14

/* led indicators */
// #define LED_CAPS_LOCK_PIN B12

/* split keyboard */
#define EE_HANDS
// #define MASTER_LEFT
// #define SPLIT_USB_DETECT
#define SERIAL_USART_FULL_DUPLEX   // Enable full duplex operation mode.
#define SERIAL_USART_PIN_SWAP
#define SERIAL_USART_TX_PIN A9      // USART TX pin
#define SERIAL_USART_TX_PAL_MODE 1
#define SERIAL_USART_RX_PIN A10     // USART RX pin
#define SERIAL_USART_RX_PAL_MODE 1
#define SERIAL_USART_DRIVER SD1
#define SPLIT_TRANSPORT_MIRROR
#define SPLIT_LED_STATE_ENABLE
#define SPLIT_LAYER_STATE_ENABLE // 同步 layer 状态
#define SPLIT_DETECTED_OS_ENABLE

// #define SPLIT_TRANSACTION_IDS_USER USER_LAYER_LIGHT
