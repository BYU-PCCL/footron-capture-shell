#ifndef GLLOWLATENCY_H
#define GLLOWLATENCY_H

//#define  GLFW_IMGUI
#include <stdint.h>

#ifdef GLFW_IMGUI  
  #include <GL/glew.h> 
  #include <GLFW/glfw3.h>
#else  
  #include <GL/glew.h> 

#ifdef LIBMWVIDEORENDER_LINUX_DEF
#else
  #include <Windows.h>
#endif
  #include "LibMWVideoRender.h"

#endif	

class CLLRender
{
  public:
    CLLRender();
    ~CLLRender();

  public:
    mw_videorender_result_t open(mw_init_setting_t *rinit);
    void Close();
	mw_videorender_result_t render(void *data, mw_render_ctrl_setting_t *rctrl, GLuint glvar);
	
	mw_videorender_result_t init_context(HWND t_hwnd); 

  private:
 		void CleanUp();

protected:

	HWND m_hwnd;
#ifdef LIBMWVIDEORENDER_LINUX_DEF
	Window m_win;
	Display *m_dpy;
	XVisualInfo *m_vi;
        GLXContext m_glc;
#else	
	HDC m_hdc;
	HGLRC m_hglrc;
#endif

  private:
	GLuint glsl_tex;
	GLuint glsl_fbo;
	mw_colorformat_t render_mode;
	GLuint glsl_rbo;
	GLint  glsl_v;
	GLint  glsl_f;
	GLuint glsl_program;
	GLuint glsl_program_hdr;
	GLuint glsl_verLocation;
	GLuint glsl_texLocation;
	GLuint glsl_texLocation2;
	GLuint glsl_texLocation3;

	GLuint glsl_verLocation_rev;
	GLuint glsl_texLocation_rev;
	GLuint glsl_texLocation2_rev;
	GLuint glsl_texLocation3_rev;

	uint32_t width;
	uint32_t height;

	GLuint glsl_buf[100];
	uint8_t alloc_buf;
	uint8_t need_rev;
};

#endif
