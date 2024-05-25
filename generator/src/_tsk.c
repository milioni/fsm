#include <stdio.h>
#include <stdint.h>

#include "$FSM_NAME$_tsk.h"

fsm_handler_t $FSM_NAME$_obj;

static fsm_state_t $FSM_NAME$_stateTable[] = {
  $FSM_TABLE${ NULL, $FSM_NAME$_EV_LIMIT, NULL, }
};

// Return 0 = OK
int $FSM_NAME$_TaskInit(void)
{
  fsm_result_t ret;
  ret = fsm_create(&$FSM_NAME$_obj, $FSM_NAME$_stateTable, (void*)$FSM_START_CB$, "$FSM_NAME$", $FSM_NAME$_EV_LIMIT);
  
  return(ret != FSM_OK);
}

// Return 0 = OK
int $FSM_NAME$_TaskDestroy(void)
{
  fsm_result_t ret;
  ret = fsm_destroy(&$FSM_NAME$_obj);
  
  return(ret != FSM_OK);
}

// Return 0 = OK
int $FSM_NAME$_TaskProcedure(void)
{
  fsm_result_t ret;
  ret = fsm_engine(&$FSM_NAME$_obj);
  
  return(ret != FSM_OK);
}
