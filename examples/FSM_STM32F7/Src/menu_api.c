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
 * @brief	Estado inicial da máquina (inativo)
 * @param	fsm ponteiro para estrutura FSM
 * @param	this Manipulador do objeto de máquina de estados
 * @return	sinal de resposta obtido durante a execução do estado
 */
evHandler menu_off(fsm_handler_t* this)
{
	// Apaga o backlight
	// ...

	// Aguarda a tecla SELECT ser pressionada
	if(BSP_Wait_Buton(-1) == BSP_BUTTON_SELECT)
	{	// Abre o Menu de configurações
		return(EV_SELECT);
	}

	// Continua no estado atual
	return(EV_NONE);
}

/**
 * @brief	Estado ativo da máquina
 * @param	fsm ponteiro para estrutura FSM
 * @param	this Manipulador do objeto de máquina de estados
 * @return	sinal de resposta obtido durante a execução do estado
 */
evHandler menu_on(fsm_handler_t* this)
{
	// Liga o backlight
	// ...

	// Capura a tecla pressionada
	switch(BSP_Wait_Buton(60000))
	{
	case BSP_BUTTON_SELECT:
		// Play
		return(EV_SELECT);

	case BSP_BUTTON_UP:
		// Abre o menu de configurações
		return(EV_UP);

	case BSP_BUTTON_DOWN:
		// Abre o menu de configurações
		return(EV_DOWN);

	default:
		break;
	}

	// Continua no estado atual
	return(EV_NONE);
}

/**
 * @brief	Exibe a tela tocando
 * @param	fsm ponteiro para estrutura FSM
 * @param	this Manipulador do objeto de máquina de estados
 * @return	sinal de resposta obtido durante a execução do estado
 */
evHandler menu_play(fsm_handler_t* this)
{
	// Capura a tecla pressionada
	switch(BSP_Wait_Buton(1000))
	{
	case BSP_BUTTON_SELECT:
		// Pause
		return(EV_SELECT);

	case BSP_BUTTON_UP:
		// Aumenta o volume
		break;

	case BSP_BUTTON_DOWN:
		// Diminui o volume
		break;

	case BSP_BUTTON_LEFT:
		// Volta musica
		break;

	case BSP_BUTTON_RIGHT:
		// Avança musica
		break;

	default:
		break;
	}

	// Continua no estado atual
	return(EV_NONE);
}

/**
 * @brief	Exibe a tela para configuração do parâmetro agudos
 * @param	fsm ponteiro para estrutura FSM
 * @param	this Manipulador do objeto de máquina de estados
 * @return	sinal de resposta obtido durante a execução do estado
 */
evHandler menu_treble(fsm_handler_t* this)
{
	switch(BSP_Wait_Buton(5000))
	{
	case BSP_BUTTON_UP:
		// Aumenta o agudo
		break;

	case BSP_BUTTON_DOWN:
		// Diminuio o Agudo
		break;

	case BSP_BUTTON_LEFT:
		// Volta para o estado ativo daa máquina
		return(EV_UP);

	case BSP_BUTTON_RIGHT:
		// Abre o próximo Menu de configurações
		return(EV_DOWN);

	default:
		break;
	}

	// Continua no estado atual
	return(EV_NONE);
}

/**
 * @brief	Exibe a tela para configuração do parâmetro médio
 * @param	fsm ponteiro para estrutura FSM
 * @param	this Manipulador do objeto de máquina de estados
 * @return	sinal de resposta obtido durante a execução do estado
 */
evHandler menu_mid(fsm_handler_t* this)
{
	switch(BSP_Wait_Buton(5000))
	{
	case BSP_BUTTON_UP:
		// Aumenta o equalizador de médios
		break;

	case BSP_BUTTON_DOWN:
		// Diminui o equalizador de médios
		break;

	case BSP_BUTTON_LEFT:
		// Abre o Menu de configurações anterior
		return(EV_UP);

	case BSP_BUTTON_RIGHT:
		// Abre o próximo Menu de configurações
		return(EV_DOWN);

	default:
		break;
	}

	// Continua no estado atual
	return(EV_NONE);
}

/**
 * @brief	Exibe a tela para configuração do parâmetro grave
 * @param	fsm ponteiro para estrutura FSM
 * @param	this Manipulador do objeto de máquina de estados
 * @return	sinal de resposta obtido durante a execução do estado
 */
evHandler menu_bass(fsm_handler_t* this)
{
	switch(BSP_Wait_Buton(5000))
	{
	case BSP_BUTTON_UP:
		// Aumenta o equalizador de grave
		break;

	case BSP_BUTTON_DOWN:
		// Diminui o equalizador de grave
		break;

	case BSP_BUTTON_LEFT:
		// Abre o Menu de configurações anterior
		return(EV_UP);

	case BSP_BUTTON_RIGHT:
		// Abre o próximo Menu de configurações
		return(EV_DOWN);

	default:
		break;

	}

	// Continua no estado atual
	return(EV_NONE);
}
