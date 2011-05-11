PROG= iv

SRCS= main.c 

CFLAGS+= -I/usr/local/include
CFLAGS+= -I/usr/local/include/SDL
CFLAGS+= -D_GNU_SOURCE=1
CFLAGS+= -D_REENTRANT
CFLAGS+= -I/usr/X11R6/include
CFLAGS+= -DXTHREADS

LDFLAGS+= -L/usr/local/lib
LDFLAGS+= -lGL
LDFLAGS+= -lGLU
LDFLAGS+= -lSDL
LDFLAGS+= -pthread
LDFLAGS+= -L/usr/X11R6/lib
LDFLAGS+= -R/usr/X11R6/lib

.include <bsd.obj.mk>
.include <bsd.prog.mk>
