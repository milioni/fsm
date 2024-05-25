#ifndef __$FSM_NAME$_API_H__
#  define __$FSM_NAME$_API_H__

#  include "fsm.h"
#  include "$FSM_NAME$_api.h"

/**
 * @brief Enum dos Eventos
 */
typedef enum {
  $FSM_EVENT_LIST$
  $FSM_NAME$_EV_LIMIT
}$FSM_NAME$_evHandler;

$FSM_PROTOTYPE$
#endif /* __$FSM_NAME$_API_H__ */
