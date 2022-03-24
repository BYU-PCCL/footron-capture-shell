// LibMWVideoRender.cpp : Defines the exported functions for the DLL application.
//

#include "glLowLatency.h"
#include "LibMWVideoRender.h"


HMWVIDEORENDER
	LIBMWVIDEORENDER_API MWCreateVideoRender()
{
	CLLRender *t_videorender=new CLLRender();
	return (HMWVIDEORENDER)t_videorender;
}

void
	LIBMWVIDEORENDER_API MWDestoryVideoRender(HMWVIDEORENDER t_hvideorender)
{
	CLLRender *t_videorender=(CLLRender*)t_hvideorender;
	if(t_videorender!=NULL){
		t_videorender->Close();
		//delete t_videorender;
	}
}

mw_videorender_result_t
	LIBMWVIDEORENDER_API MWInitRenderWithHWND(HWND t_hwnd, HMWVIDEORENDER t_hvideorender, mw_init_setting_t *t_setting)
{
	CLLRender *t_videorender=(CLLRender*)t_hvideorender;
	if(t_videorender==NULL)
		return MW_VIDEORENDER_RENDER_NULL;
	
	mw_videorender_result_t t_b_re=t_videorender->init_context(t_hwnd);
	if(t_b_re!=MW_VIDEORENDER_NO_ERROR)
		return t_b_re;

	t_b_re=t_videorender->open(t_setting);
	return t_b_re;
}

mw_videorender_result_t
	LIBMWVIDEORENDER_API MWInitRender(HMWVIDEORENDER t_hvideorender,mw_init_setting_t *t_setting)
{
	CLLRender *t_videorender=(CLLRender*)t_hvideorender;
	if(t_videorender==NULL)
		return MW_VIDEORENDER_RENDER_NULL;

	mw_videorender_result_t t_b_re=t_videorender->open(t_setting);
	return t_b_re;
}

mw_videorender_result_t
	LIBMWVIDEORENDER_API MWRenderFrame(HMWVIDEORENDER t_hvideorender, void *data, mw_render_ctrl_setting_t t_setting, unsigned int t_glvar)
{
	CLLRender *t_videorender=(CLLRender*)t_hvideorender;
	if(t_videorender==NULL)
		return MW_VIDEORENDER_RENDER_NULL;

	mw_videorender_result_t t_b_re=t_videorender->render(data,&t_setting,(GLuint)t_glvar);
	return t_b_re;
}

