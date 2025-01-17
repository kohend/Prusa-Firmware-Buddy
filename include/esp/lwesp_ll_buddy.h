#pragma once

#include "esp/esp.h"
#include "main.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define ESP_UNINITIALIZED_MODE 0UL
#define ESP_RUNNING_MODE       1UL
#define ESP_FLASHING_MODE      2UL

////////////////////////////////////////////////////////////////////////////
/// @brief Called from interrupt that data are ready in the DMA buffer
///        Setting the event
/// @param[in] device UART device
extern void esp_receive_data(UART_HandleTypeDef *);

////////////////////////////////////////////////////////////////////////////
/// @brief Transmit data to the ESP
/// @param[in] data Pointer to an array of bytes to transmit
/// @param[in] length Number of bytes to transmit
/// @return Return number of bytes successfully transmitted
extern size_t esp_transmit_data(const void *, size_t);

////////////////////////////////////////////////////////////////////////////
/// @brief Set usage of the UART
///        operating mode by ESP_RUNNING_MODE
///        flashing mode by ESP_FLASHING_MODE
/// @param[in] mode Collection of rectangles to merge
extern void esp_set_operating_mode(uint32_t);

////////////////////////////////////////////////////////////////////////////
/// @brief Gets UART an operating mode
/// @param[in] rectangles Collection of rectangles to merge
/// @return Return UART an operating mode
extern uint32_t esp_get_operating_mode(void);

////////////////////////////////////////////////////////////////////////////
/// @brief Reconfigure UART baudrate
/// @param[in] baudrate Desired baudrate
/// @return ESP error code
extern espr_t esp_reconfigure_uart(const uint32_t baudrate);

////////////////////////////////////////////////////////////////////////////
/// @brief Set ESP communication baudrate
/// @param[in] baudrate Desired baudrate
/// @return ESP error code
extern espr_t esp_set_baudrate(uint32_t baudrate);

////////////////////////////////////////////////////////////////////////////
/// @brief Hard reset ESP device using a reset pin
extern uint8_t esp_hard_reset_device(uint8_t state);

////////////////////////////////////////////////////////////////////////////
/// @brief Deinitialize ESP low level
extern espr_t esp_ll_deinit(esp_ll_t *ll);

////////////////////////////////////////////////////////////////////////////
/// @brief Initialize ESP for flash write
extern espr_t esp_flash_initialize();

// UART buffer stuff
// Buffer size should be >= ESP mem size. As LwESP requests data from ESP
// based on its available mem. The data received should fit into the buffer.
// Or, some guaratees has to be provided to ensure the excessive data can
// be copied from the RX buffer to ESP mem before the buffer overflows.
#define RX_BUFFER_LEN 0x1000
#if !defined(ESP_MEM_SIZE)
    #define ESP_MEM_SIZE 0x1000
#endif /* !defined(ESP_MEM_SIZE) */

extern uint8_t dma_buffer_rx[RX_BUFFER_LEN];

#ifdef __cplusplus
}
#endif /* __cplusplus */
