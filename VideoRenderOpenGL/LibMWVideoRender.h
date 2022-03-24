#ifndef LIBMWVIDEORENDER_H
#define LIBMWVIDEORENDER_H

#ifdef LIBMWVIDEORENDER_LINUX_DEF
#define LIBMWVIDEORENDER_API 
#else
  #ifdef LIBMWVIDEORENDER_EXPORTS
    #define LIBMWVIDEORENDER_API __declspec(dllexport)
  #else
    #define LIBMWVIDEORENDER_API __declspec(dllimport)
  #endif
#endif

#include <stdint.h>

#ifdef LIBMWVIDEORENDER_LINUX_DEF
#else
  #include "stdafx.h"
#endif

#ifdef LIBMWVIDEORENDER_LINUX_DEF
  #include<X11/X.h>
  #include<X11/Xlib.h>
  #include<GL/gl.h>
  #include<GL/glx.h>
  #include<GL/glu.h>

  typedef struct HWND
  {
	Window win;
	Display *dpy;
	XVisualInfo *vi;
  }HWND;

#endif


#ifdef __cplusplus

typedef enum _videorender_result{
	MW_VIDEORENDER_NO_ERROR=0,

	MW_VIDEORENDER_BUF_NUM_OUTOFRANGE,
	MW_VIDEORENDER_BUF_CREATE_FAIL,

	MW_VIDEORENDER_COLORFORMAT_ERROR,

	MW_VIDEORENDER_GEN_TEXTURE_ERROR=5,
	MW_VIDEORENDER_MAPBUFFER_ERROR,
	MW_VIDEORENDER_CREATE_SHADER_ERROR,
	MW_VIDEORENDER_COMPILE_SHADER_ERROR,
	MW_VIDEORENDER_LINK_ERROR,
	MW_VIDEORENDER_GEN_FBO_ERROR,
	MW_VIDEORENDER_GEN_RBO_ERROR,

	MW_VIDEORENDER_SETPIXELFORMAT_ERROR=20,
	MW_VIDEORENDER_SETCONTEXT_ERROR,
	MW_VIDEORENDER_RENDER_NULL
}mw_videorender_result_t;


typedef enum _colorformat{
	MW_RENDER_RGB24,
	MW_RENDER_YUY2,
	MW_RENDER_NV12,
	MW_RENDER_I420,
	MW_RENDER_P010
}mw_colorformat_t;

typedef struct _init_setting{
	bool m_b_reverse;
	mw_colorformat_t m_format;
	uint32_t m_u32_width;
	uint32_t m_u32_height;
	uint32_t m_u32_buf_num;
	void **m_pptr;
	unsigned int *m_glptr;
}mw_init_setting_t;

typedef struct _render_ctrl_setting
{
	uint32_t m_u32_display_w;
	uint32_t m_u32_display_h;
	bool  m_b_hdr;
	uint8_t  m_u8_val_ctrl;
	uint8_t  m_u8_threshold;
}mw_render_ctrl_setting_t;

extern "C"
{
#endif

	/////////////////////////
	// MWVIDEORENDER


#ifdef LIBMWVIDEORENDER_LINUX_DEF
        typedef void*   HMWVIDEORENDER;  
 
#else
	DECLARE_HANDLE(HMWVIDEORENDER); 
#endif

	HMWVIDEORENDER
		LIBMWVIDEORENDER_API
		MWCreateVideoRender();

	void
		LIBMWVIDEORENDER_API
		MWDestoryVideoRender(
		HMWVIDEORENDER t_hvideorender
		);

	mw_videorender_result_t
		LIBMWVIDEORENDER_API
		MWInitRenderWithHWND(
		HWND t_hwnd,
		HMWVIDEORENDER t_hvideorender,
		mw_init_setting_t *t_setting
		);

	mw_videorender_result_t
		LIBMWVIDEORENDER_API
		MWInitRender(
		HMWVIDEORENDER t_hvideorender,
		mw_init_setting_t *t_setting
		);

	mw_videorender_result_t
		LIBMWVIDEORENDER_API
		MWRenderFrame(
		HMWVIDEORENDER t_hvideorender,
		void *data,
		mw_render_ctrl_setting_t t_setting,
		unsigned int t_glvar
		);


#ifdef __cplusplus
}
#endif

#endif
