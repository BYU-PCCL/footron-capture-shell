#include "glLowLatency.h"

#ifdef LIBMWVIDEORENDER_LINUX_DEF
#else
  #pragma comment(lib,"opengl32.lib") 
#endif

static char *v_rgb_str =
#ifdef LIBMWVIDEORENDER_LINUX_DEF
  "#version 130 \n"
#else
  "#version 430 core \n"
#endif
"in vec2 vertexIn; \n"
"in vec2 textureIn; \n"
"out vec2 textureOut; \n"
"void main(void) \n"
"{ \n"
"   gl_Position = vec4(vertexIn, 0.0, 1); \n"
"   textureOut = textureIn; \n"
"} \n";

static char *f_rgb_str =
#ifdef LIBMWVIDEORENDER_LINUX_DEF
  "#version 130 \n"
#else
  "#version 430 core \n"
#endif
"uniform sampler2D tex_rgb; \n"
"in vec2 textureOut; \n"
"void main(void) \n"
"{ \n"
"  float r, g, b; \n"
"  r = texture2D(tex_rgb, textureOut).b; \n"
"  g = texture2D(tex_rgb, textureOut).g; \n"
"  b = texture2D(tex_rgb, textureOut).r; \n"
"  gl_FragColor=vec4(r,g,b,1.0); \n"
"} \n";

static char *v_yuyv_str =
#ifdef LIBMWVIDEORENDER_LINUX_DEF
  "#version 130 \n"
#else
  "#version 430 core \n"
#endif
"in vec2 vertexIn; \n"
"in vec2 textureIn; \n"
"out vec2 textureOut; \n"
"void main(void) \n"
"{ \n"
"   gl_Position = vec4(vertexIn, 0.0, 1); \n"
"   textureOut = textureIn; \n"
"} \n";

static char *f_yuyv_str =
#ifdef LIBMWVIDEORENDER_LINUX_DEF
  "#version 130 \n"
#else
  "#version 430 core \n"
#endif
"uniform sampler2D tex_yuv; \n"
"uniform int cx; \n"
"uniform int cy; \n"
"in vec2 textureOut; \n"
"void main(void) \n"
"{ \n"
"   vec3 rgb; \n"
"   vec3 yuv; \n"
"   highp float fxDD; \n"
"   int t_cx=cx; \n"
"   int t_cy=cy; \n"
"   highp float width=float(t_cx); \n"
"   float r, g, b, y, u, v; \n"
"   int x=int(floor(width*textureOut.x)); \n"
"   int imod=int(x/2); \n"
"   int t_imod=imod; \n"
"   int i=x-(t_imod*2); \n"
"   if(i==0){ \n"
"     fxDD=textureOut.x + (1.0f/width); \n"
"     y = texture2D(tex_yuv, textureOut).r; \n"
"     u = texture2D(tex_yuv, textureOut).g; \n"
"     v = texture2D(tex_yuv, vec2(fxDD,textureOut.y)).g; \n"
"     \n"
"     y = 1.1643*(y-0.0625); \n"
"     u = u - 0.5; \n"
"     v = v - 0.5; \n"
"     r = y+1.5958*v; \n"
"     g = y-0.39173*u-0.81290*v; \n"
"     b = y+2.017*u; \n"
"     gl_FragColor=vec4(r,g,b,1.0); \n"
"   } \n"
"   else{ \n"
"     fxDD=textureOut.x - (1.0f/width); \n"
"     y = texture2D(tex_yuv, textureOut).r; \n"
"     u = texture2D(tex_yuv,vec2(fxDD,textureOut.y)).g; \n"
"     v = texture2D(tex_yuv,textureOut).g; \n"
"     \n"
"     y = 1.1643*(y-0.0625); \n"
"     u = u - 0.5; \n"
"     v = v - 0.5; \n"
"     r = y+1.5958*v; \n"
"     g = y-0.39173*u-0.81290*v; \n"
"     b = y+2.017*u; \n"
"     gl_FragColor=vec4(r,g,b,1.0); \n"
"   } \n"
"} \n";

static char *v_nv12_str =
#ifdef LIBMWVIDEORENDER_LINUX_DEF
  "#version 130 \n"
#else
  "#version 430 core \n"
#endif
"in vec2 vertexIn; \n"
"in vec2 textureIn; \n"
"in vec2 textureIn2; \n"
"out vec2 textureOut; \n"
"out vec2 textureOut2; \n"
"void main(void) \n"
"{ \n"
"  gl_Position = vec4(vertexIn, 0.0, 1); \n"
"  textureOut = textureIn; \n"
"  textureOut2 = textureIn2; \n"
"} \n";

static char *f_nv12_str =
#ifdef LIBMWVIDEORENDER_LINUX_DEF
  "#version 130 \n"
#else
  "#version 430 core \n"
#endif
"in vec2 textureOut; \n"
"in vec2 textureOut2; \n"
"uniform sampler2D tex_nv12; \n"
"uniform int cx; \n"
"uniform int cy; \n"
"void main(void) \n"
"{ \n"
"  float r, g, b, my, mu, mv; \n"
"  highp float fxDD,fyDD; \n"
"  int t_cx = cx; \n"
"  int t_cy = cy; \n"
"  highp float width = float(t_cx); \n"
"  highp float height = float(t_cy); \n"
"  my = texture2D(tex_nv12, vec2(textureOut.x,textureOut.y)).r; \n"
"  int x = int(floor(width*textureOut2.x)); \n"
"  int imod = int(x/2); \n"
"  int t_imod = imod; \n"
"  int i = x - (t_imod*2); \n"
"  if(i==0) \n"
"  { \n"
"    fxDD = textureOut2.x + (1.0f/width); \n"
"    mu = texture2D(tex_nv12, vec2(textureOut2.x,textureOut2.y)).r; \n"
"    mv = texture2D(tex_nv12, vec2(fxDD,textureOut2.y)).r; \n"
"  } \n"
"  else \n"
"  { \n"
"    fxDD = textureOut2.x - (1.0f/width); \n"
"    mu = texture2D(tex_nv12, vec2(fxDD,textureOut2.y)).r; \n"
"    mv = texture2D(tex_nv12, vec2(textureOut2.x,textureOut2.y)).r; \n"
"  } \n"
"  my = 1.1643*(my-0.0625); \n"
"  mu = mu - 0.5; \n"
"  mv = mv - 0.5; \n"
"  r = my+1.5958*mv; \n"
"  g = my-0.39173*mu-0.81290*mv; \n"
"  b = my+2.017*mu; \n"
"  gl_FragColor=vec4(r,g,b,1.0); \n"
"} \n";



static char *v_p010_str =
#ifdef LIBMWVIDEORENDER_LINUX_DEF
  "#version 130 \n"
#else
  "#version 430 core \n"
#endif
"in vec2 vertexIn; \n"
"in vec2 textureIn; \n"
"in vec2 textureIn2; \n"
"out vec2 textureOut; \n"
"out vec2 textureOut2; \n"
"void main(void) \n"
"{ \n"
"  gl_Position = vec4(vertexIn, 0.0, 1); \n"
"  textureOut = textureIn; \n"
"  textureOut2 = textureIn2; \n"
"} \n";


static char *f_p010_str =
#ifdef LIBMWVIDEORENDER_LINUX_DEF
  "#version 130 \n"
#else
  "#version 430 core \n"
#endif
"in vec2 textureOut; \n"
"in vec2 textureOut2; \n"
"uniform sampler2D tex_p010; \n"
"uniform int cx; \n"
"uniform int cy; \n"
"uniform int val_ctrl; \n"
"uniform int threshold; \n"
"float A = 0.15, B = 0.50, C = 0.10, D = 0.20, E = 0.02, F = 0.30; \n"
"float hable(float x) { \n"
" return (x*(A*x+C*B)+D*E)/(x*(A*x+B)+D*F)  - E/F; \n"
"} \n"
"void main(void) \n"
"{ \n"
"   float max_rgb=0.0; \n"
"   float fval = float(val_ctrl); \n"
"  float r, g, b, my, mu, mv; \n"
"  highp float fxDD,fyDD; \n"
"  int t_cx = cx; \n"
"  int t_cy = cy; \n"
"  highp float width = float(t_cx); \n"
"  highp float height = float(t_cy); \n"
"  my = texture2D(tex_p010, vec2(textureOut.x,textureOut.y)).r; \n"
"  int x = int(floor(width*textureOut2.x)); \n"
"  int imod = int(x/2); \n"
"  int t_imod = imod; \n"
"  int i = x - (t_imod*2); \n"
"  if(i==0) \n"
"  { \n"
"    fxDD = textureOut2.x + (1.0f/width); \n"
"    mu = texture2D(tex_p010, vec2(textureOut2.x,textureOut2.y)).r; \n"
"    mv = texture2D(tex_p010, vec2(fxDD,textureOut2.y)).r; \n"
"  } \n"
"  else \n"
"  { \n"
"    fxDD = textureOut2.x - (1.0f/width); \n"
"    mu = texture2D(tex_p010, vec2(fxDD,textureOut2.y)).r; \n"
"    mv = texture2D(tex_p010, vec2(textureOut2.x,textureOut2.y)).r; \n"
"  } \n"
"	r = (my + 1.5396*mv - 0.8448); \n"
"	g = (my - 0.1831*mu - 0.4577*mv + 0.2454); \n"
"	b = (my + 1.8142*mu - 0.9821); \n"
"   r = fval*pow(r,2.4); \n"
"   g = fval*pow(g,2.4); \n"
"   b = fval*pow(b,2.4); \n"
"   if(r>max_rgb) max_rgb = r; \n"
"   if(g>max_rgb) max_rgb = g; \n"
"   if(b>max_rgb) max_rgb = b; \n"
"   float ratio = hable(max_rgb) / hable(fval); \n"
"   if(val_ctrl <= threshold) \n"
"   { \n"
"     ratio = hable(r) / hable(fval); \n"
"   } \n"
"   r = r * ratio / max_rgb; \n"
"   if(val_ctrl <= threshold) \n"
"   { \n"
"     ratio = hable(g) / hable(fval); \n"
"   } \n"
"   g = g * ratio / max_rgb; \n"
"   if(val_ctrl <= threshold) \n"
"   { \n"
"     ratio = hable(b) / hable(fval); \n"
"   } \n"
"   b = b * ratio / max_rgb; \n"
" \n"
"	gl_FragColor = vec4(r, g, b, 1.0); \n"
"} \n";

static char *v_i420_str =
#ifdef LIBMWVIDEORENDER_LINUX_DEF
  "#version 130 \n"
#else
  "#version 430 core \n"
#endif
"in vec2 vertexIn; \n"
"in vec2 textureIn; \n"
"in vec2 textureIn2; \n"
"in vec2 textureIn3; \n"
"out vec2 textureOut; \n"
"out vec2 textureOut2; \n"
"out vec2 textureOut3; \n"
"void main(void) \n"
"{ \n"
"  gl_Position = vec4(vertexIn, 0.0, 1); \n"
"  textureOut = textureIn; \n"
"  textureOut2 = textureIn2; \n"
"  textureOut3 = textureIn3; \n"
"} \n";

static char *f_i420_str =
#ifdef LIBMWVIDEORENDER_LINUX_DEF
  "#version 130 \n"
#else
  "#version 430 core \n"
#endif
"in vec2 textureOut; \n"
"in vec2 textureOut2; \n"
"in vec2 textureOut3; \n"
"uniform sampler2D tex_i420; \n"
"uniform int cx; \n"
"uniform int cy; \n"
"void main(void) \n"
"{ \n"
"  float r, g, b, my, mu, mv; \n"
"  highp float fxDD,fyDD; \n"
"  int t_cx = cx; \n"
"  int t_cy = cy; \n"
"  highp float width = float(t_cx); \n"
"  highp float height = float(t_cy); \n"
"  my = texture2D(tex_i420, vec2(textureOut.x,textureOut.y)).r; \n"
"  int x,y,i,xmod,ymod; \n"
"  highp float fymod, fxmod, uv_x; \n"
"  x = int(floor(width*textureOut2.x)); \n"
"  y = int(floor(height*textureOut2.y)); \n"
"  ymod = int(y/2); \n"
"  fymod = float(ymod); \n"
"  fyDD = textureOut2.y; \n"
"  i = y - (ymod*2); \n"
"  xmod = int(x/2); \n"
"  fxmod = float(xmod); \n"
"  uv_x = fxmod/width; \n"
"  if(i==0) \n"
"  { \n"
"    fxDD = uv_x; \n"
"    mu = texture2D(tex_i420, vec2(fxDD,fyDD)).r; \n"
"  } \n"
"  else \n"
"  { \n"
"    fxDD = 0.5 + uv_x; \n"
"    mu = texture2D(tex_i420, vec2(fxDD,fyDD)).r; \n"
"  } \n"
"  x = int(floor(width*textureOut3.x)); \n"
"  y = int(floor(height*textureOut3.y)); \n"
"  ymod = int(y/2); \n"
"  fymod = float(ymod); \n"
"  fyDD = textureOut3.y; \n"
"  i = y - (ymod*2); \n"
"  xmod = int(x/2); \n"
"  fxmod = float(xmod); \n"
"  uv_x = fxmod/width; \n"
"  if(i==0) \n"
"  { \n"
"    fxDD = uv_x; \n"
"    mv = texture2D(tex_i420, vec2(fxDD,fyDD)).r; \n"
"  } \n"
"  else \n"
"  { \n"
"    fxDD = 0.5 + uv_x; \n"
"    mv = texture2D(tex_i420, vec2(fxDD,fyDD)).r; \n"
"  } \n"
"  my = 1.1643*(my-0.0625); \n"
"  mu = mu - 0.5; \n"
"  mv = mv - 0.5; \n"
"  r = my+1.5958*mv; \n"
"  g = my-0.39173*mu-0.81290*mv; \n"
"  b = my+2.017*mu; \n"
"  gl_FragColor=vec4(r,g,b,1.0); \n"
"} \n";

#ifndef NULL
#define NULL 0
#endif

static const GLfloat vertexVertices[] = {
	-1.0f, -1.0f,
	1.0f, -1.0f,
	-1.0f,  1.0f,
	1.0f,  1.0f,
};

static const GLfloat textureVertices[] = {
	0.0f,  0.0f,
	1.0f,  0.0f,
	0.0f,  1.0f,
	1.0f,  1.0f,
};

static const GLfloat rev_textureVertices[] = {
	0.0f,  1.0f,
	1.0f,  1.0f,
	0.0f,  0.0f,
	1.0f,  0.0f,
};


static const GLfloat rev_textureVertices_rgb[] = {
	0.0f,  0.0f,
	1.0f,  0.0f,
	0.0f,  1.0f,
	1.0f,  1.0f,
};


static const GLfloat textureVertices2[] = {
	0.0f,  0.0f,
	1.0f,  0.0f,
	0.0f,  0.5f,
	1.0f,  0.5f,
};

static const GLfloat rev_textureVertices2[] = {
	0.0f,  0.5f,
	1.0f,  0.5f,
	0.0f,  0.0f,
	1.0f,  0.0f,
};

static const GLfloat textureVertices3[] = {
	0.0f,  0.5f,
	1.0f,  0.5f,
	0.0f,  0.75f,
	1.0f,  0.75f,
};

static const GLfloat rev_textureVertices3[] = {
	0.0f,  0.75f,
	1.0f,  0.75f,
	0.0f,  0.5f,
	1.0f,  0.5f,
};


static const GLfloat textureVertices4[] = {
	0.0f,  0.5f,
	1.0f,  0.5f,
	0.0f,  0.625f,
	1.0f,  0.625f,
};

static const GLfloat rev_textureVertices4[] = {
	0.0f,  0.625f,
	1.0f,  0.625f,
	0.0f,  0.5f,
	1.0f,  0.5f,
};


static const GLfloat textureVertices5[] = {
	0.0f,  0.625f,
	1.0f,  0.625f,
	0.0f,  0.75f,
	1.0f,  0.75f,
};

static const GLfloat rev_textureVertices5[] = {
	0.0f,  0.75f,
	1.0f,  0.75f,
	0.0f,  0.625f,
	1.0f,  0.625f,
};

CLLRender::CLLRender() 
{
  glsl_tex = 0;
  glsl_fbo = 0;
  render_mode = MW_RENDER_RGB24;
  glsl_rbo = 0;
  glsl_v = 0;
  glsl_f = 0;
  glsl_program = 0;
  glsl_program_hdr = 0;
  glsl_verLocation = 0;
  glsl_texLocation = 0;
  glsl_texLocation2 = 0;
  glsl_texLocation3 = 0;

  glsl_verLocation_rev = 0;
  glsl_texLocation_rev = 0;
  glsl_texLocation2_rev = 0;
  glsl_texLocation3_rev = 0;

  width = 0;
  height = 0;

  alloc_buf = 0;
  need_rev = 0;
  for (int i = 0; i < 100; i++)
  {
	  glsl_buf[i] = 0;
  }

}

CLLRender::~CLLRender() 
{
  CleanUp();
}

void CLLRender::CleanUp()
{

  if(glsl_fbo)
  {
    glDeleteFramebuffers(1, &glsl_fbo);
	glsl_fbo = 0;
  } 

  if (glsl_rbo) {
	  glDeleteRenderbuffers(1, &glsl_rbo);
	  glsl_rbo = 0;
  }

  if (glsl_v)
  {
	  glDeleteShader(glsl_v);
	  glsl_v = 0;
  }

  if (glsl_f)
  {
	  glDeleteShader(glsl_f);
	  glsl_f = 0;
  }

  if (glsl_program)
  {
	  glDeleteProgram(glsl_program);
	  glsl_program = 0;
  }

  if (glsl_program_hdr)
  {
	  glDeleteProgram(glsl_program_hdr);
	  glsl_program_hdr = 0;
  }

  for (int i = 0; i < 100; i++)
  {
	  if (glsl_buf[i]) {
		  glDeleteBuffers(1, &glsl_buf[i]);
		  glsl_buf[i] = 0;
	  }
  }

  if (glsl_tex)
  {
	  glDeleteTextures(1,&glsl_tex);
  }


} 	


void CLLRender::Close()
{
	CleanUp();
}


mw_videorender_result_t CLLRender::open(mw_init_setting_t *rinit)//(uint8_t mode, uint32_t tex_w, uint32_t tex_h, uint8_t need_rev)
{	
  uint32_t tex_w = rinit->m_u32_width;
  uint32_t tex_h = rinit->m_u32_height;
  need_rev = rinit->m_b_reverse?1:0;
  uint8_t buf_num = 0;
  void **aptr;

  if (rinit->m_u32_buf_num)
  {
	  if (rinit->m_u32_buf_num > 100)
	  {
		  return MW_VIDEORENDER_BUF_NUM_OUTOFRANGE;
	  }
	  else
	  {
		  buf_num = rinit->m_u32_buf_num;
	  }
	  aptr = new void *[buf_num];
	  if (NULL == aptr)
	  {
		  rinit->m_u32_buf_num = 0;
		  return MW_VIDEORENDER_BUF_CREATE_FAIL;
	  }
  }

  if(rinit->m_format > MW_RENDER_P010)
  {
    return MW_VIDEORENDER_COLORFORMAT_ERROR;
  }
  else
  {
    render_mode = rinit->m_format;
  }

  GLbitfield flags = GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT;
  width = tex_w;
  height = tex_h;

  GLint vertCompiled = 0, fragCompiled = 0, linked = 0;
  void *ptr;
  if (MW_RENDER_RGB24 == render_mode)
  {
	  if (buf_num)
	  {
		  glGenTextures(1, &glsl_tex);
		  if (!glsl_tex)
		  {
			  CleanUp();
			  return MW_VIDEORENDER_GEN_TEXTURE_ERROR;
		  }
		  glBindTexture(GL_TEXTURE_2D, glsl_tex);
		  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
		  glBindTexture(GL_TEXTURE_2D, 0);

		  for (int i = 0; i < buf_num; i++)
		  {
			  glGenBuffers(1, &glsl_buf[i]);
			  glBindBuffer(GL_PIXEL_UNPACK_BUFFER, glsl_buf[i]);
			  glBufferStorage(GL_PIXEL_UNPACK_BUFFER, width * height * 3, 0, flags);
			  //Map the buffer forever
			  ptr = (uint8_t *)glMapBufferRange(GL_PIXEL_UNPACK_BUFFER, 0, width * height * 3, flags);
			  if (!ptr)
			  {
				  CleanUp();
				  rinit->m_u32_buf_num = i;
				  return MW_VIDEORENDER_MAPBUFFER_ERROR;
			  }
			  aptr[i] = ptr;
		  }
		  rinit->m_pptr = aptr;
		  rinit->m_glptr = glsl_buf;
		  alloc_buf = 1;
	  }
	  else
	  {
		  glGenTextures(1, &glsl_tex);
		  if (!glsl_tex)
		  {
			  CleanUp();
			  return MW_VIDEORENDER_GEN_TEXTURE_ERROR;
		  }
		  glBindTexture(GL_TEXTURE_2D, glsl_tex);
		  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		  glBindTexture(GL_TEXTURE_2D, 0);
	  }

	  glsl_v = glCreateShader(GL_VERTEX_SHADER);
	  if (!glsl_v)
	  {
		  CleanUp();
		  return MW_VIDEORENDER_CREATE_SHADER_ERROR;
	  }
	  glsl_f = glCreateShader(GL_FRAGMENT_SHADER);
	  if (!glsl_f)
	  {
		  CleanUp();
		  return MW_VIDEORENDER_CREATE_SHADER_ERROR;
	  }

	  glShaderSource(glsl_v, 1, (const GLchar **)&v_rgb_str, NULL);
	  glShaderSource(glsl_f, 1, (const GLchar **)&f_rgb_str, NULL);

	  glCompileShader(glsl_v);
	  glGetShaderiv(glsl_v, GL_COMPILE_STATUS, &vertCompiled);
	  if (!vertCompiled)
	  {
		  CleanUp();
		  return MW_VIDEORENDER_COMPILE_SHADER_ERROR;
	  }
	  glCompileShader(glsl_f);
	  glGetShaderiv(glsl_f, GL_COMPILE_STATUS, &fragCompiled);
	  if (!fragCompiled)
	  {
		  CleanUp();
		  return MW_VIDEORENDER_COMPILE_SHADER_ERROR;
	  }
	  glsl_program = glCreateProgram();
	  glAttachShader(glsl_program, glsl_v);
	  glAttachShader(glsl_program, glsl_f);
	  glLinkProgram(glsl_program);
	  glGetProgramiv(glsl_program, GL_LINK_STATUS, &linked);
	  if (!linked)
	  {
		  CleanUp();
		  return MW_VIDEORENDER_LINK_ERROR;
	  }

	  glsl_verLocation = glGetAttribLocation(glsl_program, "vertexIn");
	  glsl_texLocation = glGetAttribLocation(glsl_program, "textureIn");

	  glVertexAttribPointer(glsl_verLocation, 2, GL_FLOAT, 0, 0, vertexVertices);
	  glEnableVertexAttribArray(glsl_verLocation);
	  if (need_rev)
	  {
		  glVertexAttribPointer(glsl_texLocation, 2, GL_FLOAT, 0, 0, rev_textureVertices_rgb);
		  glEnableVertexAttribArray(glsl_texLocation);
	  }
	  else
	  {
		  glVertexAttribPointer(glsl_texLocation, 2, GL_FLOAT, 0, 0, textureVertices);
		  glEnableVertexAttribArray(glsl_texLocation);
	  }

	  glGenFramebuffers(1, &glsl_fbo);
	  if (!glsl_fbo)
	  {
		  CleanUp();
		  return MW_VIDEORENDER_GEN_FBO_ERROR;
	  }
	  glBindFramebuffer(GL_FRAMEBUFFER, glsl_fbo);
	  glGenRenderbuffers(1, &glsl_rbo);
	  if (!glsl_rbo)
	  {
		  CleanUp();
		  return MW_VIDEORENDER_GEN_RBO_ERROR;
	  }
	  glBindRenderbuffer(GL_RENDERBUFFER, glsl_rbo);
	  glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA8, width, height);
	  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, glsl_rbo);
	  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  }

  if (MW_RENDER_YUY2 == render_mode)
  {

	  if (buf_num)
	  {
		  glGenTextures(1, &glsl_tex);
		  if (!glsl_tex)
		  {
			  CleanUp();
			  return MW_VIDEORENDER_GEN_TEXTURE_ERROR;
		  }
		  glBindTexture(GL_TEXTURE_2D, glsl_tex);
		  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		  glTexImage2D(GL_TEXTURE_2D, 0, GL_RG, width, height, 0, GL_RG, GL_UNSIGNED_BYTE, 0);
		  glBindTexture(GL_TEXTURE_2D, 0);

		  for (int i = 0; i < buf_num; i++)
		  {
			  glGenBuffers(1, &glsl_buf[i]);
			  glBindBuffer(GL_PIXEL_UNPACK_BUFFER, glsl_buf[i]);
			  glBufferStorage(GL_PIXEL_UNPACK_BUFFER, width * height * 2, 0, flags);
			  //Map the buffer forever
			  ptr = (uint8_t *)glMapBufferRange(GL_PIXEL_UNPACK_BUFFER, 0, width * height * 2, flags);
			  if (!ptr)
			  {
				  CleanUp();
				  rinit->m_u32_buf_num = i;
				  return MW_VIDEORENDER_MAPBUFFER_ERROR;
			  }
			  aptr[i] = ptr;
		  }
		  rinit->m_pptr = aptr;
		  rinit->m_glptr = glsl_buf;
		  alloc_buf = 1;
	  }
	  else
	  {
		  glGenTextures(1, &glsl_tex);
		  if (!glsl_tex)
		  {
			  CleanUp();
			  return MW_VIDEORENDER_GEN_TEXTURE_ERROR;
		  }
		  glBindTexture(GL_TEXTURE_2D, glsl_tex);
		  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	  }

	  glsl_v = glCreateShader(GL_VERTEX_SHADER);
	  if (!glsl_v)
	  {
		  CleanUp();
		  return MW_VIDEORENDER_CREATE_SHADER_ERROR;
	  }
	  glsl_f = glCreateShader(GL_FRAGMENT_SHADER);
	  if (!glsl_f)
	  {
		  CleanUp();
		  return MW_VIDEORENDER_CREATE_SHADER_ERROR;
	  }
	  glShaderSource(glsl_v, 1, (const GLchar **)&v_yuyv_str, NULL);
	  glShaderSource(glsl_f, 1, (const GLchar **)&f_yuyv_str, NULL);

	  glCompileShader(glsl_v);
	  glGetShaderiv(glsl_v, GL_COMPILE_STATUS, &vertCompiled);
	  if (!vertCompiled)
	  {
		  CleanUp();
		  return MW_VIDEORENDER_COMPILE_SHADER_ERROR;
	  }
	  glCompileShader(glsl_f);
	  glGetShaderiv(glsl_f, GL_COMPILE_STATUS, &fragCompiled);
	  if (!fragCompiled)
	  {
		  CleanUp();
		  return MW_VIDEORENDER_COMPILE_SHADER_ERROR;
	  }

	  glsl_program = glCreateProgram();
	  glAttachShader(glsl_program, glsl_v);
	  glAttachShader(glsl_program, glsl_f);
	  glLinkProgram(glsl_program);
	  glGetProgramiv(glsl_program, GL_LINK_STATUS, &linked);
	  if (!linked)
	  {
		  CleanUp();
		  return MW_VIDEORENDER_LINK_ERROR;
	  }

	  glsl_verLocation = glGetAttribLocation(glsl_program, "vertexIn");
	  glsl_texLocation = glGetAttribLocation(glsl_program, "textureIn");

	  glVertexAttribPointer(glsl_verLocation, 2, GL_FLOAT, 0, 0, vertexVertices);
	  glEnableVertexAttribArray(glsl_verLocation);
	  if (need_rev)
	  {
		  glVertexAttribPointer(glsl_texLocation, 2, GL_FLOAT, 0, 0, rev_textureVertices);
		  glEnableVertexAttribArray(glsl_texLocation);
	  }
	  else
	  {
		  glVertexAttribPointer(glsl_texLocation, 2, GL_FLOAT, 0, 0, textureVertices);
		  glEnableVertexAttribArray(glsl_texLocation);
	  }


	  glGenFramebuffers(1, &glsl_fbo);
	  if (!glsl_fbo)
	  {
		  CleanUp();
		  return MW_VIDEORENDER_GEN_FBO_ERROR;
	  }
	  glBindFramebuffer(GL_FRAMEBUFFER, glsl_fbo);
	  glGenRenderbuffers(1, &glsl_rbo);
	  if (!glsl_rbo)
	  {
		  CleanUp();
		  return MW_VIDEORENDER_GEN_RBO_ERROR;
	  }
	  glBindRenderbuffer(GL_RENDERBUFFER, glsl_rbo);
	  glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA8, width, height); 
	  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, glsl_rbo); 
	  glBindFramebuffer(GL_FRAMEBUFFER, 0);
	  
  }


  if (MW_RENDER_I420 == render_mode)
  {
	  if (buf_num)
	  {
		  glGenTextures(1, &glsl_tex);
		  if (!glsl_tex)
		  {
			  CleanUp();
			  return MW_VIDEORENDER_GEN_TEXTURE_ERROR;
		  }
		  glBindTexture(GL_TEXTURE_2D, glsl_tex);
		  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		  glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, (height * 2), 0, GL_RED, GL_UNSIGNED_BYTE, 0);
		  glBindTexture(GL_TEXTURE_2D, 0);

		  for (int i = 0; i < buf_num; i++)
		  {
			  glGenBuffers(1, &glsl_buf[i]);
			  glBindBuffer(GL_PIXEL_UNPACK_BUFFER, glsl_buf[i]);
			  glBufferStorage(GL_PIXEL_UNPACK_BUFFER, width * height * 2, 0, flags);
			  //Map the buffer forever
			  ptr = (uint8_t *)glMapBufferRange(GL_PIXEL_UNPACK_BUFFER, 0, width * height * 2, flags);
			  if (!ptr)
			  {
				  CleanUp();
				  rinit->m_u32_buf_num = i;
				  return MW_VIDEORENDER_MAPBUFFER_ERROR;
			  }
			  aptr[i] = ptr;
		  }
		  rinit->m_pptr = aptr;
		  rinit->m_glptr = glsl_buf;
		  alloc_buf = 1;
	  }
	  else
	  {
		  glGenTextures(1, &glsl_tex);
		  if (!glsl_tex)
		  {
			  return MW_VIDEORENDER_GEN_TEXTURE_ERROR;
		  }
		  glBindTexture(GL_TEXTURE_2D, glsl_tex);
		  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	  }

	  glsl_v = glCreateShader(GL_VERTEX_SHADER);
	  if (!glsl_v)
	  {
		  return MW_VIDEORENDER_CREATE_SHADER_ERROR;
	  }
	  glsl_f = glCreateShader(GL_FRAGMENT_SHADER);
	  if (!glsl_f)
	  {
		  return MW_VIDEORENDER_CREATE_SHADER_ERROR;
	  }

	  glShaderSource(glsl_v, 1, (const GLchar **)&v_i420_str, NULL);
	  glShaderSource(glsl_f, 1, (const GLchar **)&f_i420_str, NULL);

	  glCompileShader(glsl_v);
	  glGetShaderiv(glsl_v, GL_COMPILE_STATUS, &vertCompiled);
	  if (!vertCompiled)
	  {
		  return MW_VIDEORENDER_COMPILE_SHADER_ERROR;
	  }
	  glCompileShader(glsl_f);
	  glGetShaderiv(glsl_f, GL_COMPILE_STATUS, &fragCompiled);
	  if (!fragCompiled)
	  {
		  return MW_VIDEORENDER_COMPILE_SHADER_ERROR;
	  }

	  glsl_program = glCreateProgram();
	  glAttachShader(glsl_program, glsl_v);
	  glAttachShader(glsl_program, glsl_f);
	  glLinkProgram(glsl_program);
	  glGetProgramiv(glsl_program, GL_LINK_STATUS, &linked);
	  if (!linked)
	  {
		  return MW_VIDEORENDER_LINK_ERROR;
	  }
	  glsl_verLocation = glGetAttribLocation(glsl_program, "vertexIn");
	  glsl_texLocation = glGetAttribLocation(glsl_program, "textureIn");
	  glsl_texLocation2 = glGetAttribLocation(glsl_program, "textureIn2");
	  glsl_texLocation3 = glGetAttribLocation(glsl_program, "textureIn3");


	  glVertexAttribPointer(glsl_verLocation, 2, GL_FLOAT, 0, 0, vertexVertices);
	  glEnableVertexAttribArray(glsl_verLocation);
	  if (need_rev)
	  {
		  glVertexAttribPointer(glsl_texLocation, 2, GL_FLOAT, 0, 0, rev_textureVertices2);
		  glEnableVertexAttribArray(glsl_texLocation);
		  glVertexAttribPointer(glsl_texLocation2, 2, GL_FLOAT, 0, 0, rev_textureVertices4);
		  glEnableVertexAttribArray(glsl_texLocation2);
		  glVertexAttribPointer(glsl_texLocation3, 2, GL_FLOAT, 0, 0, rev_textureVertices5);
		  glEnableVertexAttribArray(glsl_texLocation3);
	  }
	  else
	  {
		  glVertexAttribPointer(glsl_texLocation, 2, GL_FLOAT, 0, 0, textureVertices2);
		  glEnableVertexAttribArray(glsl_texLocation);
		  glVertexAttribPointer(glsl_texLocation2, 2, GL_FLOAT, 0, 0, textureVertices4);
		  glEnableVertexAttribArray(glsl_texLocation2);
		  glVertexAttribPointer(glsl_texLocation3, 2, GL_FLOAT, 0, 0, textureVertices5);
		  glEnableVertexAttribArray(glsl_texLocation3);
	  }

	  glGenFramebuffers(1, &glsl_fbo);
	  if (!glsl_fbo)
	  {
		  return MW_VIDEORENDER_GEN_FBO_ERROR;
	  }
	  glBindFramebuffer(GL_FRAMEBUFFER, glsl_fbo);
	  glGenRenderbuffers(1, &glsl_rbo);
	  if (!glsl_rbo)
	  {
		  return MW_VIDEORENDER_GEN_RBO_ERROR;
	  }
	  glBindRenderbuffer(GL_RENDERBUFFER, glsl_rbo);
	  glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA8, width, height);
	  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, glsl_rbo);
	  glBindFramebuffer(GL_FRAMEBUFFER, 0);


  }


  if (MW_RENDER_NV12 == render_mode)
  {
	  if (buf_num)
	  {
		  glGenTextures(1, &glsl_tex);
		  if (!glsl_tex)
		  {
			  CleanUp();
			  return MW_VIDEORENDER_GEN_TEXTURE_ERROR;
		  }
		  glBindTexture(GL_TEXTURE_2D, glsl_tex);
		  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		  glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, (height * 2), 0, GL_RED, GL_UNSIGNED_BYTE, 0);
		  glBindTexture(GL_TEXTURE_2D, 0);

		  for (int i = 0; i < buf_num; i++)
		  {
			  glGenBuffers(1, &glsl_buf[i]);
			  glBindBuffer(GL_PIXEL_UNPACK_BUFFER, glsl_buf[i]);
			  glBufferStorage(GL_PIXEL_UNPACK_BUFFER, width * height * 2, 0, flags);
			  //Map the buffer forever
			  ptr = (uint8_t *)glMapBufferRange(GL_PIXEL_UNPACK_BUFFER, 0, width * height * 2, flags);
			  if (!ptr)
			  {
				  CleanUp();
				  rinit->m_u32_buf_num = i;
				  return MW_VIDEORENDER_MAPBUFFER_ERROR;
			  }
			  aptr[i] = ptr;
		  }
		  rinit->m_pptr = aptr;
		  rinit->m_glptr = glsl_buf;
		  alloc_buf = 1;
	  }
	  else
	  {
		  glGenTextures(1, &glsl_tex);
		  if (!glsl_tex)
		  {
			  return MW_VIDEORENDER_GEN_TEXTURE_ERROR;
		  }
		  glBindTexture(GL_TEXTURE_2D, glsl_tex);
		  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	  }

	  glsl_v = glCreateShader(GL_VERTEX_SHADER);
	  if (!glsl_v)
	  {
		  return MW_VIDEORENDER_CREATE_SHADER_ERROR;
	  }
	  glsl_f = glCreateShader(GL_FRAGMENT_SHADER);
	  if (!glsl_f)
	  {
		  return MW_VIDEORENDER_CREATE_SHADER_ERROR;
	  }

	  glShaderSource(glsl_v, 1, (const GLchar **)&v_nv12_str, NULL);
	  glShaderSource(glsl_f, 1, (const GLchar **)&f_nv12_str, NULL);

	  glCompileShader(glsl_v);
	  glGetShaderiv(glsl_v, GL_COMPILE_STATUS, &vertCompiled);
	  if (!vertCompiled)
	  {
		  return MW_VIDEORENDER_COMPILE_SHADER_ERROR;
	  }
	  glCompileShader(glsl_f);
	  glGetShaderiv(glsl_f, GL_COMPILE_STATUS, &fragCompiled);
	  if (!fragCompiled)
	  {
		  return MW_VIDEORENDER_COMPILE_SHADER_ERROR;
	  }

	  glsl_program = glCreateProgram();
	  glAttachShader(glsl_program, glsl_v);
	  glAttachShader(glsl_program, glsl_f);
	  glLinkProgram(glsl_program);
	  glGetProgramiv(glsl_program, GL_LINK_STATUS, &linked);
	  if (!linked)
	  {
		  return MW_VIDEORENDER_LINK_ERROR;
	  }

	  glsl_verLocation = glGetAttribLocation(glsl_program, "vertexIn");
	  glsl_texLocation = glGetAttribLocation(glsl_program, "textureIn");
	  glsl_texLocation2 = glGetAttribLocation(glsl_program, "textureIn2");

	  glVertexAttribPointer(glsl_verLocation, 2, GL_FLOAT, 0, 0, vertexVertices);
	  glEnableVertexAttribArray(glsl_verLocation);
	  if (need_rev)
	  {
		  glVertexAttribPointer(glsl_texLocation, 2, GL_FLOAT, 0, 0, rev_textureVertices2);
		  glEnableVertexAttribArray(glsl_texLocation);
		  glVertexAttribPointer(glsl_texLocation2, 2, GL_FLOAT, 0, 0, rev_textureVertices3);
		  glEnableVertexAttribArray(glsl_texLocation2);
	  }
	  else
	  {
		  glVertexAttribPointer(glsl_texLocation, 2, GL_FLOAT, 0, 0, textureVertices2);
		  glEnableVertexAttribArray(glsl_texLocation);
		  glVertexAttribPointer(glsl_texLocation2, 2, GL_FLOAT, 0, 0, textureVertices3);
		  glEnableVertexAttribArray(glsl_texLocation2);
	  }

	  glGenFramebuffers(1, &glsl_fbo);
	  if (!glsl_fbo)
	  {
		  return MW_VIDEORENDER_GEN_FBO_ERROR;
	  }
	  glBindFramebuffer(GL_FRAMEBUFFER, glsl_fbo);
	  glGenRenderbuffers(1, &glsl_rbo);
	  if (!glsl_rbo)
	  {
		  return MW_VIDEORENDER_GEN_RBO_ERROR;
	  }
	  glBindRenderbuffer(GL_RENDERBUFFER, glsl_rbo);
	  glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA8, width, height);
	  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, glsl_rbo);
	  glBindFramebuffer(GL_FRAMEBUFFER, 0);

  }

  if (MW_RENDER_P010 == render_mode)
  {
	  if (buf_num)
	  {
		  glGenTextures(1, &glsl_tex);
		  if (!glsl_tex)
		  {
			  CleanUp();
			  return MW_VIDEORENDER_GEN_TEXTURE_ERROR;
		  }
		  glBindTexture(GL_TEXTURE_2D, glsl_tex);
		  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		  glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, (height * 2), 0, GL_RED, GL_UNSIGNED_SHORT, 0);
		  glBindTexture(GL_TEXTURE_2D, 0);

		  for (int i = 0; i < buf_num; i++)
		  {
			  glGenBuffers(1, &glsl_buf[i]);
			  glBindBuffer(GL_PIXEL_UNPACK_BUFFER, glsl_buf[i]);
			  glBufferStorage(GL_PIXEL_UNPACK_BUFFER, width * height * 4, 0, flags);
			  //Map the buffer forever
			  ptr = (uint8_t *)glMapBufferRange(GL_PIXEL_UNPACK_BUFFER, 0, width * height * 4, flags);
			  if (!ptr)
			  {
				  CleanUp();
				  rinit->m_u32_buf_num = i;
				  return MW_VIDEORENDER_BUF_NUM_OUTOFRANGE;
			  }
			  aptr[i] = ptr;
		  }
		  rinit->m_pptr = aptr;
		  rinit->m_glptr = glsl_buf;
		  alloc_buf = 1;
	  }
	  else
	  {
		  glGenTextures(1, &glsl_tex);
		  if (!glsl_tex)
		  {
			  return MW_VIDEORENDER_GEN_TEXTURE_ERROR;
		  }
		  glBindTexture(GL_TEXTURE_2D, glsl_tex);
		  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	  }




	  glsl_v = glCreateShader(GL_VERTEX_SHADER);
	  if (!glsl_v)
	  {
		  return MW_VIDEORENDER_CREATE_SHADER_ERROR;
	  }
	  glsl_f = glCreateShader(GL_FRAGMENT_SHADER);
	  if (!glsl_f)
	  {
		  return MW_VIDEORENDER_CREATE_SHADER_ERROR;
	  }

	  glShaderSource(glsl_v, 1, (const GLchar **)&v_p010_str, NULL);
	  glShaderSource(glsl_f, 1, (const GLchar **)&f_p010_str, NULL);

	  glCompileShader(glsl_v);
	  glGetShaderiv(glsl_v, GL_COMPILE_STATUS, &vertCompiled);
	  if (!vertCompiled)
	  {
		  return MW_VIDEORENDER_COMPILE_SHADER_ERROR;
	  }
	  glCompileShader(glsl_f);
	  glGetShaderiv(glsl_f, GL_COMPILE_STATUS, &fragCompiled);
	  if (!fragCompiled)
	  {
		  return MW_VIDEORENDER_COMPILE_SHADER_ERROR;
	  }

	  glsl_program_hdr = glCreateProgram();
	  glAttachShader(glsl_program_hdr, glsl_v);
	  glAttachShader(glsl_program_hdr, glsl_f);
	  glLinkProgram(glsl_program_hdr);
	  glGetProgramiv(glsl_program_hdr, GL_LINK_STATUS, &linked);
	  if (!linked)
	  {
		  return MW_VIDEORENDER_LINK_ERROR;
	  }

	  glsl_verLocation = glGetAttribLocation(glsl_program_hdr, "vertexIn");
	  glsl_texLocation = glGetAttribLocation(glsl_program_hdr, "textureIn");
	  glsl_texLocation2 = glGetAttribLocation(glsl_program_hdr, "textureIn2");

	  glVertexAttribPointer(glsl_verLocation, 2, GL_FLOAT, 0, 0, vertexVertices);
	  glEnableVertexAttribArray(glsl_verLocation);
	  if (need_rev)
	  {
		  glVertexAttribPointer(glsl_texLocation, 2, GL_FLOAT, 0, 0, rev_textureVertices2);
		  glEnableVertexAttribArray(glsl_texLocation);
		  glVertexAttribPointer(glsl_texLocation2, 2, GL_FLOAT, 0, 0, rev_textureVertices3);
		  glEnableVertexAttribArray(glsl_texLocation2);
	  }
	  else
	  {
		  glVertexAttribPointer(glsl_texLocation, 2, GL_FLOAT, 0, 0, textureVertices2);
		  glEnableVertexAttribArray(glsl_texLocation);
		  glVertexAttribPointer(glsl_texLocation2, 2, GL_FLOAT, 0, 0, textureVertices3);
		  glEnableVertexAttribArray(glsl_texLocation2);
	  }


	  glShaderSource(glsl_v, 1, (const GLchar **)&v_nv12_str, NULL);
	  glShaderSource(glsl_f, 1, (const GLchar **)&f_nv12_str, NULL);

	  glCompileShader(glsl_v);
	  glGetShaderiv(glsl_v, GL_COMPILE_STATUS, &vertCompiled);
	  if (!vertCompiled)
	  {
		  return MW_VIDEORENDER_COMPILE_SHADER_ERROR;
	  }
	  glCompileShader(glsl_f);
	  glGetShaderiv(glsl_f, GL_COMPILE_STATUS, &fragCompiled);
	  if (!fragCompiled)
	  {
		  return MW_VIDEORENDER_COMPILE_SHADER_ERROR;
	  }

	  glsl_program = glCreateProgram();
	  glAttachShader(glsl_program, glsl_v);
	  glAttachShader(glsl_program, glsl_f);
	  glLinkProgram(glsl_program);
	  glGetProgramiv(glsl_program, GL_LINK_STATUS, &linked);
	  if (!linked)
	  {
		  return MW_VIDEORENDER_LINK_ERROR;
	  }

	  glsl_verLocation = glGetAttribLocation(glsl_program, "vertexIn");
	  glsl_texLocation = glGetAttribLocation(glsl_program, "textureIn");
	  glsl_texLocation2 = glGetAttribLocation(glsl_program, "textureIn2");

	  glVertexAttribPointer(glsl_verLocation, 2, GL_FLOAT, 0, 0, vertexVertices);
	  glEnableVertexAttribArray(glsl_verLocation);
	  if (need_rev)
	  {
		  glVertexAttribPointer(glsl_texLocation, 2, GL_FLOAT, 0, 0, rev_textureVertices2);
		  glEnableVertexAttribArray(glsl_texLocation);
		  glVertexAttribPointer(glsl_texLocation2, 2, GL_FLOAT, 0, 0, rev_textureVertices3);
		  glEnableVertexAttribArray(glsl_texLocation2);
	  }
	  else
	  {
		  glVertexAttribPointer(glsl_texLocation, 2, GL_FLOAT, 0, 0, textureVertices2);
		  glEnableVertexAttribArray(glsl_texLocation);
		  glVertexAttribPointer(glsl_texLocation2, 2, GL_FLOAT, 0, 0, textureVertices3);
		  glEnableVertexAttribArray(glsl_texLocation2);
	  }

	  glGenFramebuffers(1, &glsl_fbo);
	  if (!glsl_fbo)
	  {
		  return MW_VIDEORENDER_GEN_FBO_ERROR;
	  }
	  glBindFramebuffer(GL_FRAMEBUFFER, glsl_fbo);
	  glGenRenderbuffers(1, &glsl_rbo);
	  if (!glsl_rbo)
	  {
		  return MW_VIDEORENDER_GEN_RBO_ERROR;
	  }
	  glBindRenderbuffer(GL_RENDERBUFFER, glsl_rbo);
	  glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA8, width, height);
	  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, glsl_rbo);
	  glBindFramebuffer(GL_FRAMEBUFFER, 0);

  }

  glClearColor(0.0, 0.0, 0.0, 1.0);

  return MW_VIDEORENDER_NO_ERROR;		 	    
}



mw_videorender_result_t CLLRender::render(void *data, mw_render_ctrl_setting_t *rctrl, GLuint glvar)
{
  uint32_t display_w = rctrl->m_u32_display_w;
  uint32_t display_h = rctrl->m_u32_display_h;

  if (MW_RENDER_RGB24 == render_mode)
  {
	  glViewport(0, 0, width, height);
	  glUseProgram(glsl_program);

	  glBindFramebuffer(GL_FRAMEBUFFER, glsl_fbo);
	  glActiveTexture(GL_TEXTURE0);
	  glBindTexture(GL_TEXTURE_2D, glsl_tex);

	  if (alloc_buf)
	  {
		  if (glvar)
		  {
			  glBindBuffer(GL_PIXEL_UNPACK_BUFFER, glvar);
			  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
			  glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
		  }
	  }
	  else
	  {
		  if (data)
		  {
			  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		  }
	  }


	  glUniform1i(glGetUniformLocation(glsl_program, "tex_rgb"), 0);
	  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	  glBindFramebuffer(GL_READ_FRAMEBUFFER, glsl_fbo);
	  glViewport(0, 0, display_w, display_h);
	  glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	  glBlitFramebuffer(0, 0, width, height, 0, 0, display_w, display_h, GL_COLOR_BUFFER_BIT, GL_NEAREST);
  }

  if (MW_RENDER_YUY2 == render_mode)
  {
	  glViewport(0, 0, width, height);
	  glUseProgram(glsl_program);

	  glBindFramebuffer(GL_FRAMEBUFFER, glsl_fbo);
	  glActiveTexture(GL_TEXTURE0);
	  glBindTexture(GL_TEXTURE_2D, glsl_tex);

	  if (alloc_buf)
	  {
		  if (glvar)
		  {
			  glBindBuffer(GL_PIXEL_UNPACK_BUFFER, glvar);
			  glTexImage2D(GL_TEXTURE_2D, 0, GL_RG, width, height, 0, GL_RG, GL_UNSIGNED_BYTE, 0);
			  glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
		  }
	  }
	  else
	  {
		  if (data)
		  {
			  glTexImage2D(GL_TEXTURE_2D, 0, GL_RG, width, height, 0, GL_RG, GL_UNSIGNED_BYTE, data);
		  }
	  }

	  glUniform1i(glGetUniformLocation(glsl_program, "tex_yuv"), 0);
	  glUniform1i(glGetUniformLocation(glsl_program, "cx"), width);
	  glUniform1i(glGetUniformLocation(glsl_program, "cy"), height);

	  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	  glBindFramebuffer(GL_READ_FRAMEBUFFER, glsl_fbo);
	  glViewport(0, 0, display_w, display_h);
	  glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	  glBlitFramebuffer(0, 0, width, height, 0, 0, display_w, display_h, GL_COLOR_BUFFER_BIT, GL_NEAREST);
  }

  if (MW_RENDER_I420 == render_mode)
  {
	  glViewport(0, 0, width, height);
	  glUseProgram(glsl_program);


	  glBindFramebuffer(GL_FRAMEBUFFER, glsl_fbo);
	  glActiveTexture(GL_TEXTURE0);
	  glBindTexture(GL_TEXTURE_2D, glsl_tex);

	  if (alloc_buf)
	  {
		  if (glvar)
		  {
			  glBindBuffer(GL_PIXEL_UNPACK_BUFFER, glvar);
			  glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, (height * 2), 0, GL_RED, GL_UNSIGNED_BYTE, 0);
			  glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
		  }
	  }
	  else
	  {
		  if (data)
		  {
			  glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, (height * 2), 0, GL_RED, GL_UNSIGNED_BYTE, data);
		  }
	  }
	  glUniform1i(glGetUniformLocation(glsl_program, "tex_i420"), 0);
	  glUniform1i(glGetUniformLocation(glsl_program, "cx"), width);
	  glUniform1i(glGetUniformLocation(glsl_program, "cy"), height);
	  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	  glBindFramebuffer(GL_READ_FRAMEBUFFER, glsl_fbo);
	  glViewport(0, 0, display_w, display_h);
	  glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	  glBlitFramebuffer(0, 0, width, height, 0, 0, display_w, display_h, GL_COLOR_BUFFER_BIT, GL_NEAREST);


  }

  if (MW_RENDER_NV12 == render_mode)
  {
	  glViewport(0, 0, width, height);
	  glUseProgram(glsl_program);

	  glBindFramebuffer(GL_FRAMEBUFFER, glsl_fbo);
	  glActiveTexture(GL_TEXTURE0);
	  glBindTexture(GL_TEXTURE_2D, glsl_tex);

	  if (alloc_buf)
	  {
		  if (glvar)
		  {
			  glBindBuffer(GL_PIXEL_UNPACK_BUFFER, glvar);
			  glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, (height * 2), 0, GL_RED, GL_UNSIGNED_BYTE, 0);
			  glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
		  }
	  }
	  else
	  {
		  if (data)
		  {
			  glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, (height * 2), 0, GL_RED, GL_UNSIGNED_BYTE, data);
		  }
	  }

	  glUniform1i(glGetUniformLocation(glsl_program, "tex_nv12"), 0);
	  glUniform1i(glGetUniformLocation(glsl_program, "cx"), width);
	  glUniform1i(glGetUniformLocation(glsl_program, "cy"), height);
	  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	  glBindFramebuffer(GL_READ_FRAMEBUFFER, glsl_fbo);
	  glViewport(0, 0, display_w, display_h);
	  glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	  glBlitFramebuffer(0, 0, width, height, 0, 0, display_w, display_h, GL_COLOR_BUFFER_BIT, GL_NEAREST);

  }


  if (MW_RENDER_P010 == render_mode)
  {
	  uint8_t val_ctrl;
	  uint8_t threshold;

	  if (rctrl->m_u8_val_ctrl > 100)
	  {
		  val_ctrl = 100;
	  }
	  else
	  {
		  val_ctrl = rctrl->m_u8_val_ctrl;
	  }

	  if (rctrl->m_u8_threshold > 100)
	  {
		  threshold = 100;
	  }
	  else
	  {
		  threshold = rctrl->m_u8_threshold;
	  }

	  glViewport(0, 0, width, height);
	  if (rctrl->m_b_hdr)
	  {
		  glUseProgram(glsl_program_hdr);
	  }
	  else
	  {
		  glUseProgram(glsl_program);
	  }


	  glBindFramebuffer(GL_FRAMEBUFFER, glsl_fbo);
	  glActiveTexture(GL_TEXTURE0);
	  glBindTexture(GL_TEXTURE_2D, glsl_tex);

	  if (alloc_buf)
	  {
		  if (glvar)
		  {
			  glBindBuffer(GL_PIXEL_UNPACK_BUFFER, glvar);
			  glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, (height * 2), 0, GL_RED, GL_UNSIGNED_SHORT, 0);
			  glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
		  }
	  }
	  else
	  {
		  if (data)
		  {
			  glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, (height * 2), 0, GL_RED, GL_UNSIGNED_SHORT, data);
		  }
	  }
	  if (rctrl->m_b_hdr)
	  {
		  glUniform1i(glGetUniformLocation(glsl_program_hdr, "tex_p010"), 0);
		  glUniform1i(glGetUniformLocation(glsl_program_hdr, "cx"), width);
		  glUniform1i(glGetUniformLocation(glsl_program_hdr, "cy"), height);
		  glUniform1i(glGetUniformLocation(glsl_program_hdr, "threshold"), threshold);
		  glUniform1i(glGetUniformLocation(glsl_program_hdr, "val_ctrl"), val_ctrl);
	  }
	  else
	  {
		  glUniform1i(glGetUniformLocation(glsl_program, "tex_p010"), 0);
		  glUniform1i(glGetUniformLocation(glsl_program, "cx"), width);
		  glUniform1i(glGetUniformLocation(glsl_program, "cy"), height);
	  }



	  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	  glBindFramebuffer(GL_READ_FRAMEBUFFER, glsl_fbo);
	  glViewport(0, 0, display_w, display_h);
	  glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	  glBlitFramebuffer(0, 0, width, height, 0, 0, display_w, display_h, GL_COLOR_BUFFER_BIT, GL_NEAREST);

  }

  return MW_VIDEORENDER_NO_ERROR;	
}







mw_videorender_result_t CLLRender::init_context(HWND t_hwnd)
{
#ifdef LIBMWVIDEORENDER_LINUX_DEF
	m_hwnd = t_hwnd;
	m_win = m_hwnd.win;
	m_dpy = m_hwnd.dpy;
	m_vi = m_hwnd.vi;

	m_glc = glXCreateContext(m_dpy, m_vi, NULL, GL_TRUE);
	if (!m_glc)
		return MW_VIDEORENDER_SETCONTEXT_ERROR;
	glXMakeCurrent(m_dpy, m_win, m_glc);

#else
	m_hwnd=t_hwnd;
	m_hdc = GetDC(m_hwnd);
	static PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),  // size of this pfd
		1,                              // version number
		PFD_DRAW_TO_WINDOW |            // support window
		PFD_SUPPORT_OPENGL |            // support OpenGL
		PFD_DOUBLEBUFFER,                // double buffered
		PFD_TYPE_RGBA,                  // RGBA type
		24,                             // 24-bit color depth
		0, 0, 0, 0, 0, 0,               // color bits ignored
		0,                              // no alpha buffer
		0,                              // shift bit ignored
		0,                              // no accumulation buffer
		0, 0, 0, 0,                     // accum bits ignored
		16,                             // 16-bit z-buffer
		0,                              // no stencil buffer
		0,                              // no auxiliary buffer
		PFD_MAIN_PLANE,                 // main layer
		0,                              // reserved
		0, 0, 0                         // layer masks ignored
	};
	int m_nPixelFormat = ::ChoosePixelFormat(m_hdc, &pfd);
	bool t_bs=SetPixelFormat(m_hdc, m_nPixelFormat, &pfd);
	if(!t_bs)
		return MW_VIDEORENDER_SETPIXELFORMAT_ERROR;

	m_hglrc=wglCreateContext(m_hdc);
	bool t_b=wglMakeCurrent(m_hdc, m_hglrc);
	if(!t_b)
		return MW_VIDEORENDER_SETCONTEXT_ERROR;
#endif
	glewInit();

	return MW_VIDEORENDER_NO_ERROR;
}




