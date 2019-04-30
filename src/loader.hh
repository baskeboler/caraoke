#if !defined(LOADER_H)
#define LOADER_H

#include "text.hh"
#include <memory>
#include <vector>
using std::shared_ptr;

// apr_

/**
 *
 */
extern FrameVec load_json(const char *path);

/**
 *
 */
extern void debug_frames(FrameVec &l);

#endif // LOADER_H
