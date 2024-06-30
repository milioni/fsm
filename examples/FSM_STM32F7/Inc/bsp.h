/**
 * @file	bsp.h
 * @brief	Board support package example
 * @author	Thiago Milioni
 *
 * Camada de software que gera uma abstração de hardware do dispositivo
 *
 */
#ifndef __BSP_H__
#define __BSP_H__

/**
 * @defgroup bsp_h doxygengroup
 * @{
 */

/**
 * Bibliotecas Públicas
 */
#include <stdint.h>
#include "stm32f7xx_hal.h"


/**
 * Macros Públicas
 */
#define BSP_BUTTON_SELECT_ADDR		GPIOB, GPIO_PIN_11
#define BSP_BUTTON_UP_ADDR			GPIOB, GPIO_PIN_12
#define BSP_BUTTON_DOWN_ADDR		GPIOB, GPIO_PIN_13
#define BSP_BUTTON_LEFT_ADDR		GPIOB, GPIO_PIN_14
#define BSP_BUTTON_RIGHT_ADDR		GPIOB, GPIO_PIN_15

#define BSP_BUTTON_DEBOUNCE			20
#define BSP_BUTTON_RETRIES			5

/**
 * Tipos de Dados Públicos
 */
typedef enum bsp_button
{
	BSP_BUTTON_UNKNOWN = 0,
	BSP_BUTTON_SELECT,
	BSP_BUTTON_UP,
	BSP_BUTTON_DOWN,
	BSP_BUTTON_LEFT,
	BSP_BUTTON_RIGHT,

	BSP_BUTTON_LIMIT
} bsp_button_t;

/**
 * @brief FSM Returns
 *
 * Lista de erros que podem ser retornados durante a execução da FSM
 */
bsp_button_t BSP_Wait_Buton(uint32_t timeout);

/**
 * @}
 */

#endif
