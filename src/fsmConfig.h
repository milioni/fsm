/**
 * @file	fsmConfig.h
 * @brief	Global settings used in the Finite State Machine Design Pattern
 * @author	Thiago Milioni
 * @version	0.2
 * @date	28 Abr 2024
 * 
 * Configurações globais utilizadas no Padrão de Design para modelagem de
 * Máquinas de Estado Finito.
 * 
 */
#ifndef __FSM_CONFIG_H__
#define __FSM_CONFIG_H__

/**
 * @defgroup fsmConfig_h doxygengroup
 * @{
 */

/**
 * @brief Configuração do modo de Debug
 *
 * Bitmap que habilita o nível de Debug para geração de alertas 
 *
 * 0 = Desabilita a geração de mensagens
 * 1 = Habilita a geração de alertas de Erro
 * 2 = Habilita a geração de todos os alertas
 */
#define FSM_DEBUG_LEVEL 0

/**
 * @brief Configuração do modo de alocação de memória
 * 
 * Configura se a estrutura FSM será alocada estática ou dinamicamente
 * @code
 * #define FSM_STATIC_ONLY 1
 * FSM fsm;
 * fsm_create(&fsm, stateTable, (void*)fnInit, "StateMachine", EV_LIMIT);
 * @endcode
 * Or
 * @code
 * #define FSM_STATIC_ONLY 0
 * FSM *fsm;
 * fsm_create(fsm, stateTable, (void*)fnInit, "StateMachine", EV_LIMIT);
 * @endcode
 */
#define FSM_STATIC_ONLY 1

/**
 * @brief Configura o tamanho máximo da string que identifica a FSM
 *
 */
#define FSM_NAME_MAX_LENGTH 16

/**
 * @}
 */

#endif
