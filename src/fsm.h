/**
 * @file	fsm.h
 * @brief	Finite State Machine Design Pattern
 * @author	Thiago Milioni
 * @version	0.2
 * @date	28 Abr 2024
 * 
 * Padrão de Design para modelagem de Máquinas de Estado Finito na forma de
 * Tabela de Transição e geração automática de diagrama de estados.
 * 
 */
#ifndef __FSM_H__
#define __FSM_H__

/**
 * @defgroup fsm_h doxygengroup
 * @{
 */

/**
 * Bibliotecas Públicas
 */
#include <stdint.h>
#include "fsmConfig.h"

/**
 * Macros Públicas
 */
#if FSM_STATIC_ONLY == 0
#	include <stdlib.h>
#endif

#if FSM_DEBUG_LEVEL > 0
#	include <stdio.h>
#	include <stdarg.h>
#endif

#if FSM_DEBUG_LEVEL >= 2
#	define FSM_DBG(fmt, ...) printf(fmt, ##__VA_ARGS__)
#else
#	define FSM_DBG(fmt, ...)
#endif

#if FSM_DEBUG_LEVEL >= 1
#	define FSM_ERR(fmt, ...) printf(fmt, ##__VA_ARGS__)
#else
#	define FSM_ERR(fmt, ...)
#endif



/**
 * Tipos de Dados Públicos
 */

/**
 * @brief FSM State
 * 
 * Estrutura que encapsula a regra para fazer a transição de um estado dentro da
 * FSM para outro a partir de um Id de Evento conhecido
 */
typedef struct fsm_state
{
	void*		cb_state;
	uint16_t	eventID;
	void*		cb_next;
} fsm_state_t;

/**
 * @brief FSM Object
 * 
 * Estrutura principal da FSM que pode ser alocada tanto estática como
 * dinamicamente e que contém todas as variáveis necessárias para gerar a
 * transição de estados a partir de eventos disparados durante sua execução
 */
typedef struct fsm_handler
{
	char			fsm_name[FSM_NAME_MAX_LENGTH];	/**< Nome da FSM */
	void*			cb_state;						/**< Ponteiro para o estado atual da FSM */
	uint16_t		eventID;						/**< Id de evento aguardando para ser processado */
	uint16_t		number_events;					/**< Quantidade de eventos válidos para a FSM */
	fsm_state_t*	stateTable;						/**< Ponteiro para a tabela com as regras de transição de estado da FSM */
} fsm_handler_t;

/**
 * @brief FSM Returns
 * 
 * Lista de erros que podem ser retornados durante a execução da FSM
 */
typedef enum fsm_result
{
	FSM_OK = 0,		/**< Evento genérico de sucesso */
	FSM_NULL,
	FSM_STATE_NULL,
	FSM_NAME_NULL,
	FSM_FUNCTION_NULL,

	FSM_STATE_ERROR,
	FSM_STT_ERROR,
	FSM_EVENT_ERROR,
	FSM_NO_RESOURCES,
	FSM_NO_TRANSITION,
} fsm_result_t;

/**
 * Protótipos de Funções Públicas
 */
fsm_result_t fsm_create	(fsm_handler_t *fsm, fsm_state_t *stateTable, void* initial_state, char* fsm_name, uint16_t number_events);
fsm_result_t fsm_destroy(fsm_handler_t *fsm);
fsm_result_t fsm_engine	(fsm_handler_t *fsm);

/**
 * @}
 */

#endif
