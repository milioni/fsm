/**
 * @file	menu_tsk.c
 * @brief	Operações a serem executadas pela Thread que contra o menu
 * @author	Thiago Milioni
 *
 * Este exemplo implementa a thread que cria as telas do menu de contexto para
 * executar alterações nos parâmetros de configuração de um equipamento.
 *
 */

/**
 * Bibliotecas Privadas
 */
#include <stdio.h>
#include <stdint.h>
#include "menu_api.h"
#include "menu_tsk.h"

/**
 * @defgroup fsm_c doxygengroup
 * @{
 */

/**
 * Variáveis privadas
 */
static fsm_handler_t fsm;

// Tabela relacional dos estados / Funções
static fsm_state_t stateTable[] = {
	/* callback state	event			next state */
	{ (void*)menu_init,			EV_NEXT,	(void*)menu_main		},
	{ (void*)menu_main,			EV_NEXT,	(void*)menu_brightness	},
	{ (void*)menu_brightness, 	EV_BACK,	(void*)menu_main		},
	{ (void*)menu_brightness,	EV_NEXT,	(void*)menu_contrast	},
	{ (void*)menu_contrast,		EV_BACK,	(void*)menu_main		},
	{ (void*)menu_contrast,		EV_NEXT,	(void*)menu_brightness	},
	{ NULL,						EV_LIMIT,	NULL,					}
};

/**
 * @}
 */

/**
 * @brief	Inicializa a Máquina de estados do Menu de controle
 * @return	Resultado retornado pela execução da FSM
 * @retval	Qualquer valor diferente de FSM_OK indica um código de erro
 */
int Menu_TaskInit(void)
{
	fsm_result_t ret;
	ret = fsm_create(&fsm, stateTable, (void*)menu_init, "StateMachine", EV_LIMIT);
	return(ret != FSM_OK);
}

/**
 * @brief Finaliza a Máquina de estados do Menu de controle
 * @return	Resultado retornado pela execução da FSM
 * @retval	Qualquer valor diferente de FSM_OK indica um código de erro
 */
int Menu_TaskDestroy(void)
{
	fsm_result_t ret;
	ret = fsm_destroy(&fsm);

	return(ret != FSM_OK);
}

/**
 * @brief Executa um passo na Máquina de estados do Menu de controle
 * @return	Resultado retornado pela execução da FSM
 * @retval	Qualquer valor diferente de FSM_OK indica um código de erro
 */
int Menu_TaskProcedure(void)
{
	fsm_result_t ret;
	ret = fsm_engine(&fsm);

	return(ret != FSM_OK);
}
