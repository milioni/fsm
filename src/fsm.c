/**
 * @file	fsm.c
 * @brief	Finite State Machine Design Pattern
 * @author	Thiago Milioni
 * @version	0.2
 * @date	28 Abr 2024
 * 
 * Padrão de Design para modelagem de Máquinas de Estado Finito na forma de
 * Tabela de Transição e geração automática de diagrama de estados.
 * 
 */

/**
 * Bibliotecas Privadas
 */
#include "fsm.h"
#include "string.h"

/**
 * @defgroup fsm_c doxygengroup
 * @{
 */

/**
 * Protótipos de Funções Privadas
 */
fsm_result_t fsm_checkStateTable(fsm_state_t *stateTable, uint16_t number_events);

/**
 * @}
 */

/**
 * @brief		Cria uma Máquina de Estado
 * @details		Função que cria uma FSM. A forma de utilizar essa função pode variar de acordo
 *				com a forma de alocação que foi configurado em fsmConfig.h
 * @see			FSM_STATIC_ONLY
 * @param		fsm ponteiro para estrutura FSM
 * @param		stateTable ponteiro para tabela de transição de estados
 * @param		initial_state ponteiro para a função que será executada na primeira iteração da FSM
 * @param		fsm_name ponteiro para a string com o nome da FSM
 * @param		number_events quantidade de eventos no enum da FSM
 * @return		Return value of method
 * @retval		Verbose explanation of return values
 */
fsm_result_t fsm_create(fsm_handler_t *fsm, fsm_state_t *stateTable, void* initial_state, char* fsm_name, uint16_t number_events)
{  
	uint16_t len;

	FSM_DBG("fsm create %s ", fsm_name);

	if(fsm==NULL )
	{ 
		FSM_ERR("ERROR: fsm null\r\n");
		return(FSM_NULL);
	}

	if(stateTable==NULL)
	{ 
		FSM_ERR("ERROR: state table null\r\n");
		return(FSM_STATE_NULL);
	}

	if(initial_state==NULL)
	{
		FSM_ERR("ERROR: initial state null\r\n");
		return(FSM_FUNCTION_NULL);
	}

	if(fsm_name==NULL)
	{
		FSM_ERR("ERROR: fsm name null\r\n");
		return(FSM_NAME_NULL);
	}

	if(fsm_checkStateTable(stateTable, number_events) != FSM_OK)
	{ 
		FSM_ERR("ERROR: invalid state\r\n");
		return(FSM_STATE_ERROR);
	}

#if !FSM_STATIC_ONLY
	fsm = (fsm_handler_t*)malloc(sizeof(fsm_handler_t));
	if(fsm == NULL)
	{ 
		FSM_ERR("ERROR: without resources\r\n");
		return(FSM_NO_RESOURCES);
	}
#endif

	memset(fsm, 0, sizeof(fsm_handler_t));
	len = strlen(fsm_name);
	if( len > (FSM_NAME_MAX_LENGTH-1) )
	{
		len = (FSM_NAME_MAX_LENGTH-1);
	} 
	memcpy(fsm->fsm_name, fsm_name, len);

	fsm->cb_state		= initial_state;
	fsm->eventID		= number_events;
	fsm->number_events	= number_events;

	fsm->stateTable		= stateTable;

	FSM_DBG("success\r\n");
	return(FSM_OK);
}

/**
 * @brief Destroy uma FSM
 * 
 * @param *fsm ponteiro para estrutura FSM
 */
fsm_result_t fsm_destroy (fsm_handler_t *fsm)
{  
	FSM_DBG("fsm destroy %s ", fsm->fsm_name);

	if(fsm==NULL)
	{ 
		FSM_ERR("ERROR: null pointer\r\n");
		return(FSM_NULL);
	}

	memset(fsm, 0, sizeof(fsm_handler_t));
	#if FSM_STATIC_ONLY != 1
	free(fsm);	
	#endif

	FSM_DBG("success\r\n");
	return(FSM_OK);
}

/**
 * @brief Executa a máquina de estado
 * 
 * A cada chamada dessa função será executado um loop da máquina de estado
 * @param *fsm ponteiro para estrutura FSM
 */
fsm_result_t fsm_engine(fsm_handler_t *fsm)
{
	//fsm_state_t *state;
	uint16_t stateID;
	fsm_result_t ret = FSM_OK;

	FSM_DBG("fms engine %s ", fsm->fsm_name);

	if(fsm==NULL)
	{ 
		FSM_ERR("ERROR: invalid fsm\r\n");
		return(FSM_NULL);
	}

	if( fsm->eventID < fsm->number_events )
	{
		for( stateID=0; fsm->stateTable[stateID].cb_state != NULL; stateID++ )
		{
			//state = fsm->stateTable[stateID];
			if( (fsm->stateTable[stateID].cb_state == fsm->cb_state ) &&
				(fsm->stateTable[stateID].eventID  == fsm->eventID  ) )
			{ 
				fsm->cb_state = fsm->stateTable[stateID].cb_next;
				fsm->eventID  = fsm->number_events;

				break;
			}
		}

		if( fsm->stateTable[stateID].cb_state == NULL )
		{ 
			ret = FSM_EVENT_ERROR;
		}
	}
	else
	{ 
		ret = FSM_NO_TRANSITION;
	}

	if( fsm->cb_state==NULL )
	{     
		FSM_ERR("ERROR: invalid state\r\n");
		return(FSM_STATE_NULL);
	}

	uint16_t (*fn_ptr)(fsm_handler_t*) = (uint16_t(*)(fsm_handler_t*)) fsm->cb_state;
	fsm->eventID = fn_ptr(fsm);

	FSM_DBG("success\r\n");
	return(ret);
}

/**
 * @brief fsm_checkStateTable
 * 
 * Função privada utilizada para listar se existe algum erro na FSM
 */
fsm_result_t fsm_checkStateTable(fsm_state_t *stateTable, uint16_t number_events)
{
	uint16_t state, check;
	FSM_DBG("fms check state table ");

	for( state=0; stateTable[state].cb_state != NULL; state++ )
	{
		if( stateTable[state].eventID > number_events )
		{
			FSM_ERR("ERROR: eventId out of bunds\r\n");
			return(FSM_EVENT_ERROR);
		}
		for( check=state+1; stateTable[check].cb_state != NULL; check++ )
		{
			if( (stateTable[state].cb_state == stateTable[check].cb_state) &&
				(stateTable[state].eventID  == stateTable[check].eventID ) )
			{
				FSM_ERR("ERROR: eventId duplicate\r\n");
				return(FSM_EVENT_ERROR);
			}
		}
	}
	for( state=0; stateTable[state].cb_state != NULL; state++ )
	{
		for( check=state+1; stateTable[check].cb_state != NULL; check++ )
		{
			if( (stateTable[state].cb_state == stateTable[check].cb_state) &&
				(stateTable[state].cb_next  == stateTable[check].cb_next ) &&
				(stateTable[state].eventID  != stateTable[check].eventID ) )
			{
				FSM_ERR("ERROR: eventId duplicate\r\n");
				return(FSM_EVENT_ERROR);
			}    
		}
	}
	FSM_DBG("success\r\n");
	return(FSM_OK);
}

/*
fsm_state_t* fsm_getStatePtrFromStateIdTable(uint16_t stateID, fsm_state_t *stateTable, uint16_t limit)
{
	uint16_t state;
	for(state=0; state<limit; state++)
	{
		if( stateTable->stateID == stateID )
		{
			break;
		}
		stateTable += sizeof(fsm_state_t);
	}
	if( state<limit )
	{
		return(stateTable);
	}
	else
	{
		return((fsm_state_t*)NULL);
	}
}
*/