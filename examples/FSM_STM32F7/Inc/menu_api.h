/**
 * @file	menu_api.h
 * @brief	Operações a serem executadas em cada estado da Máquina
 * @author	Thiago Milioni
 *
 * Este exemplo implementa um menu de contexto para executar alterações nos parâmetros
 * de configuração de um equipamento a partir do presisonamento de botões de controle.
 *
 */
#ifndef __FSM_API_H__
#define __FSM_API_H__

/**
 * @defgroup menu_api_h doxygengroup
 * @{
 */

/**
 * Bibliotecas Públicas
 */
#include "fsm.h"

/**
 * Tipos de Dados Públicos
 */

/**
 * @brief  Enum dos Eventos
 */
typedef enum {
	EV_NONE,
	EV_SELECT,
	EV_UP,
	EV_DOWN,
	EV_LEFT,
	EV_RIGHT,

	EV_LIMIT
}evHandler;


/**
 * Protótipos de Funções Públicas
 */
evHandler menu_off		(fsm_handler_t* this);
evHandler menu_on		(fsm_handler_t* this);
evHandler menu_play		(fsm_handler_t* this);
evHandler menu_treble	(fsm_handler_t* this);
evHandler menu_mid		(fsm_handler_t* this);
evHandler menu_bass		(fsm_handler_t* this);

/**
 * @}
 */

#endif /* __FSM_API_H__ */
