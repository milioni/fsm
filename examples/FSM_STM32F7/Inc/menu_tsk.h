/**
 * @file	menu_tsk.h
 * @brief	Operações a serem executadas pela Thread que contra o menu
 * @author	Thiago Milioni
 *
 * Este exemplo implementa a thread que cria as telas do menu de contexto para
 * executar alterações nos parâmetros de configuração de um equipamento.
 *
 */
#ifndef __FSM_TSK_H__
#define __FSM_TSK_H__

/**
 * @defgroup fsm_h doxygengroup
 * @{
 */

/**
 * Protótipos de Funções Públicas
 */
int Menu_TaskInit      (void);
int Menu_TaskDestroy   (void);
int Menu_TaskProcedure (void);

/**
 * @}
 */

#endif
