#include "KW_widget_internal.h"

void AddWidgetHandler(KW_Widget * widget, KW_WidgetEventHandlerType handlertype, void * handler) {
  /* don't add multiple mouse over handlers */
  unsigned int * count = &(widget->eventhandlers[handlertype].count);
  
  /* check if handler is there */
  int i;
  for (i = 0; i < *count; ++i) {
    if (widget->eventhandlers[handlertype].handlers[i] == handler)
      return;
  }
  
  /* add the handler then */
  (*count)++;
  widget->eventhandlers[handlertype].handlers = realloc(widget->eventhandlers[handlertype].handlers, sizeof(void *) * (*count));
  widget->eventhandlers[handlertype].handlers[(*count) - 1] = handler;  
}

void RemoveWidgetHandler(KW_Widget * widget, KW_WidgetEventHandlerType handlertype, void * handler) {
  int i, j;
  unsigned int * count = &(widget->eventhandlers[handlertype].count);
  
  /* iterate to find the position of widget */
  for (i = 0; i < *count; i++) {
    if (widget->eventhandlers[handlertype].handlers[i] == handler) {
      j = i;
    }
    
    /* move everything in front of it */
    if (j >= 0 && i + 1 < *count) {
      widget->eventhandlers[handlertype].handlers[i] = widget->eventhandlers[handlertype].handlers[i+1];
    }
  }
  
  /* realloc children array */
  (*count)--;
  if (*count <= 0) {
    free(widget->eventhandlers[handlertype].handlers);
    widget->eventhandlers[handlertype].handlers = NULL;
  }
  else
    widget->eventhandlers[handlertype].handlers = realloc(widget->eventhandlers[handlertype].handlers, *count * sizeof(void *));  
}
