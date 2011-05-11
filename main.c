#include "SDL.h"
#include "SDL_opengl.h"

#include <stdio.h>

int
init(SDL_Surface* screen)
{
	if ( SDL_Init (SDL_INIT_VIDEO) != 0 )
	{
		printf ("Unable to initialize SDL: %s\n", SDL_GetError());
		return (0);
	}

	SDL_GL_SetAttribute ( SDL_GL_DOUBLEBUFFER, 1 );

	screen = SDL_SetVideoMode ( 1024, 600, 16, SDL_OPENGL | SDL_FULLSCREEN );
	if ( !screen )
	{
		printf ("Unable to set video mode: %s\n", SDL_GetError());
		return (0);
	}

	glClearColor ( 0, 0, 0, 0);
	glEnable ( GL_TEXTURE_2D );

	glViewport ( 0, 0, 640, 480 );

	glMatrixMode ( GL_PROJECTION );
	glLoadIdentity ();

	glOrtho ( 0, 640, 480, 0, -1, 1 );

	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity ();

	return (1);
}

int
get_texture (GLuint* texture, char* name)
{
	SDL_Surface* surface;

	if ( (surface = SDL_LoadBMP (name) ) == NULL)
	{
		printf ("SDL could not load image.bmp: %s\n", SDL_GetError () );
		return (1);
	}
	if ( (surface->w & (surface->w - 1) ) != 0 )
	{
	    printf ("warning: image.bmp's width is not a power of 2\n");
	}

	if ( (surface->h & (surface->h - 1) ) != 0 )
	{
	    printf ("warning: image.bmp's height is not a power of 2\n");
	}
	
	glGenTextures ( 1, texture );
	glBindTexture ( GL_TEXTURE_2D, *texture );

	glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

	glTexImage2D ( GL_TEXTURE_2D, 0, 3, surface->w, surface->h, 0, GL_BGR, GL_UNSIGNED_BYTE, surface->pixels );
	
	if ( surface )
	{ 
		SDL_FreeSurface ( surface );
	}

	return (0);
}

int
draw_quad (int x, int y, int size)
{
	glBegin ( GL_QUADS );
	glTexCoord2i ( 0, 0 );
	glVertex3f ( 100, 100, 0 );

	glTexCoord2i ( 1, 0 );
	glVertex3f ( 228, 100, 0 );

	glTexCoord2i ( 1, 1 );
	glVertex3f ( 228, 228, 0 );

	glTexCoord2i ( 0, 1 );
	glVertex3f ( 100, 228, 0 );
	glEnd ();
}

int 
main (int argc, char *argv[])
{
	SDL_Surface* screen = NULL;
	if (!init (screen) )
	{
		return (1);
	}
	
	GLuint texture;
	
	if ( get_texture( &texture, "slides/slide1.bmp") != 0 )
	{
		SDL_Quit ();
		return (1);
	}

	glClear ( GL_COLOR_BUFFER_BIT );

	draw_quad (0,0,0);
	
	SDL_GL_SwapBuffers ();

	SDL_Delay (3000);

	glDeleteTextures ( 1, &texture );

	SDL_Quit ();

	return (0);
}
