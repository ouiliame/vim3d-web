#ifndef OPENGLINC_H
#define OPENGLINC_H

// -- Use includes from emscripten-core/emscripten:system/include --
//#if defined(_WIN32)
//#include <gl/glut.h>
//#elif defined(macintosh) || defined(__MACH__) && defined(__APPLE__)
//#include <OpenGL/gl.h>
//#include <OpenGL/glu.h>
//#include <GLUT/glut.h>
//#else
//#include <GL/glut.h>
//#endif

#ifndef USE_CUSTOM_GL

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#else

#include "custom_gl/gl.h"
#include "custom_gl/glu.h"
#include "custom_gl/glut.h"

#endif

#endif

