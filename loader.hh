#if !defined(LOADER_H)
#define LOADER_H

#include "text.hh"
#include <vector>

using std::vector;
// apr_

/**
 * 
 */ 
extern vector<TextFrame> load_json(const char *path);

/**
 * 
 */
extern void debug_frames(vector<TextFrame>& l);


#endif // LOADER_H
