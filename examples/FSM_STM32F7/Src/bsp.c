/**
 * @file	bsp.c
 * @brief	Board support package example
 * @author	Thiago Milioni
 *
 * Camada de software que gera uma abstração de hardware do dispositivo
 *
 */

/**
 * Bibliotecas Privadas
 */
#include "bsp.h"

/**
 * @defgroup bsp_c doxygengroup
 * @{
 */

/**
 * @}
 */

/**
 * @brief	Retorna o índice do botão pressionado
 * @details	Aguarda por um determinado tempo algum botão do dispositivo ser pressionado
 * @param	timeout tempo máximo de espera
 * @return	Identificador do botão pressionado
 * @retval	BSP_BUTTON_UNKNOWN caso nenhum botão for pressioando no limite de tempo definido
 */
bsp_button_t BSP_Wait_Buton(uint32_t timeout)
{
	bsp_button_t result = BSP_BUTTON_UNKNOWN;
	uint32_t ticks;
	ticks = HAL_GetTick();

	if( timeout < (0xFFFFFFFF-ticks) )
	{
		timeout += HAL_GetTick();
	}

	// Debounce por software
	uint8_t retries = 0;
	do
	{
		retries++;
		if( HAL_GPIO_ReadPin( BSP_BUTTON_SELECT_ADDR ) == 0 )
		{
			if(result != BSP_BUTTON_SELECT)
			{
				retries = 0;
				result = BSP_BUTTON_SELECT;
			}
		}
		else if( HAL_GPIO_ReadPin( BSP_BUTTON_UP_ADDR ) == 0 )
		{
			if(result != BSP_BUTTON_UP)
			{
				retries = 0;
				result = BSP_BUTTON_UP;
			}
		}
		else if( HAL_GPIO_ReadPin( BSP_BUTTON_DOWN_ADDR ) == 0 )
		{
			if(result != BSP_BUTTON_DOWN)
			{
				retries = 0;
				result = BSP_BUTTON_DOWN;
			}
		}
		else if( HAL_GPIO_ReadPin( BSP_BUTTON_LEFT_ADDR ) == 0 )
		{
			if(result != BSP_BUTTON_LEFT)
			{
				retries = 0;
				result = BSP_BUTTON_LEFT;
			}
		}
		else if( HAL_GPIO_ReadPin( BSP_BUTTON_RIGHT_ADDR ) == 0 )
		{
			if(result != BSP_BUTTON_RIGHT)
			{
				retries = 0;
				result = BSP_BUTTON_RIGHT;
			}
		}
		else
		{
			retries = 0;
		}

		if( retries >= BSP_BUTTON_RETRIES )
		{
			break;
		}
		else
		{
			HAL_Delay(BSP_BUTTON_DEBOUNCE);
		}

	} while( HAL_GetTick() < timeout );

	// Retorna o índice do botão pressionado
	return( result );
}
