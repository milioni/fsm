/**
 * @file	menu_api.c
 * @brief	Operações a serem executadas em cada estado da Máquina
 * @author	Thiago Milioni
 *
 * Este exemplo implementa um menu de contexto para executar alterações nos parâmetros
 * de configuração de um equipamento a partir do presisonamento de botões de controle.
 *
 */

/**
 * Bibliotecas Privadas
 */
#include <stdio.h>
#include <stdint.h>
#include "bsp.h"
#include "menu_api.h"

/**
 * @defgroup menu_api_c doxygengroup
 * @{
 */

/**
 * @}
 */

/**
 * @brief	Estado inicial da máquina
 * @param	fsm ponteiro para estrutura FSM
 * @param	this Manipulador do objeto de máquina de estados
 * @return	sinal de resposta obtido durante a execução do estado
 */
evHandler menu_init(fsm_handler_t* this)
{
	// Executa as inicializações necessárias
	// ...

	// Avança para o Menu principal
	return(EV_NEXT);
}

/**
 * @brief	Exibe a tela inicial
 * @param	fsm ponteiro para estrutura FSM
 * @param	this Manipulador do objeto de máquina de estados
 * @return	sinal de resposta obtido durante a execução do estado
 */
evHandler menu_main(fsm_handler_t* this)
{
	// Aguarda se a tecla SELECT ser pressionada
	switch(BSP_Wait_Buton(1000))
	{
	case BSP_BUTTON_SELECT:
		// Abre o Menu de configurações
		return(EV_NEXT);

	default:
		break;
	}

	// Não faz nada
	return(EV_NONE);
}

/**
 * @brief	Exibe a tela para configuração do parâmetro brilho
 * @param	fsm ponteiro para estrutura FSM
 * @param	this Manipulador do objeto de máquina de estados
 * @return	sinal de resposta obtido durante a execução do estado
 */
evHandler menu_brightness(fsm_handler_t* this)
{
	switch(BSP_Wait_Buton(5000))
	{
	case BSP_BUTTON_SELECT:
		// Abre o próximo Menu de configurações
		return(EV_NEXT);

	case BSP_BUTTON_LEFT:
		// Diminui o brilho
		return(EV_NONE);

	case BSP_BUTTON_RIGHT:
		// Aumenta o brilho
		return(EV_NONE);

	default:
		break;
	}

	// Retorna para Menu principal
	return(EV_BACK);
}

/**
 * @brief	Exibe a tela para configuração do parâmetro contraste
 * @param	fsm ponteiro para estrutura FSM
 * @param	this Manipulador do objeto de máquina de estados
 * @return	sinal de resposta obtido durante a execução do estado
 */
evHandler menu_contrast(fsm_handler_t* this)
{
	switch(BSP_Wait_Buton(5000))
	{
	case BSP_BUTTON_SELECT:
		// Abre o próximo Menu de configurações
		return(EV_NEXT);

	case BSP_BUTTON_LEFT:
		// Diminui o contraste
		return(EV_NONE);

	case BSP_BUTTON_RIGHT:
		// Aumenta o contraste
		return(EV_NONE);

	default:
		break;
	}

	// Retorna para Menu principal
	return(EV_BACK);
}
