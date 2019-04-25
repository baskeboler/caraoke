#if !defined(LOADER_H)
#define LOADER_H

#include "text.h"
#include "list.h"

// apr_

/**
 * 
 */ 
extern list_t load_json(const char *path);

/**
 * 
 */
extern void debug_frames(list_t l);


#endif // LOADER_H
