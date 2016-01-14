﻿#ifndef HGL_SHADER_STRING_LIST_INCLUDE
#define HGL_SHADER_STRING_LIST_INCLUDE

#include"GLSL.h"
namespace hgl
{
	namespace graph
	{
		namespace shadergen
		{
			#define SHADER_VALUE_NAME_MAX_LENGTH	128

			/**
			* shader 传输限定符
			*/
			enum shader_io_qualifiers
			{
				ioqNone=0,

				ioqSmooth,			//透视校正
				ioqFlat,			//无校正
				ioqNoPerspective,	//无透视校正，普通线性变换

				ioqEnd
			};//enum shader_io_qualifiers

			/**
			* shader 输入数据类型
			*/
			enum shader_in_type
			{
				sitNone=0,			//无此数据

				sitUniform,			//一致变量
				sitVertexAttrib,	//顶点属性
				sitTBO,				//TBO

				sitEnd
			};

			extern const char shader_float_type[4][8];
			extern const char shader_sampler[3][16];
			extern const char shader_sampler_shadow[2][16];

			extern const char shader_get_sampler_color[3][16];

			struct shader_stringlist
			{
			protected:

				UTF8String shader_string;

			public:

				shader_stringlist(){}
				virtual ~shader_stringlist(){}

				char *end_get()
				{
					return shader_string.Discard();
				}

				void add(const char *line="\n"){shader_string.Strcat(line,::strlen(line));}

				void debug_out(const os_char *filename);

#define ADD_IOU(type)	void add_in_##type		(const char *name){add("in "		#type);add(" ");add(name);add(";\n");}	\
						void add_out_##type		(const char *name){add("out "		#type);add(" ");add(name);add(";\n");}	\
						void add_uniform_##type	(const char *name){add("uniform "	#type);add(" ");add(name);add(";\n");}

				ADD_IOU(int);
				ADD_IOU(uint);
				ADD_IOU(bool);
				ADD_IOU(float);

				ADD_IOU(vec2);
				ADD_IOU(vec3);
				ADD_IOU(vec4);

				ADD_IOU(mat3);
				ADD_IOU(mat4);

#undef ADD_IOU
				void add_in_fv			(const char *name,int num){add("in "		);add(shader_float_type[num-1]);add(" ");add(name);add(";\n");}
				void add_out_fv			(const char *name,int num){add("out "		);add(shader_float_type[num-1]);add(" ");add(name);add(";\n");}
				void add_uniform_fv		(const char *name,int num){add("uniform "	);add(shader_float_type[num-1]);add(" ");add(name);add(";\n");}

				void add_sampler		(const char *name,int num){add("uniform "	);add(shader_sampler		[num-1]);add(" ");add(name);add(";\n");}
				void add_sampler_shadow	(const char *name,int num){add("uniform "	);add(shader_sampler_shadow	[num-1]);add(" ");add(name);add(";\n");}

			public:

				void add_version(int=440);
				void add_main_begin();
				void add_main_end();
			};//struct shader_stringlist
		}//namespace shadergen
	}//namespace graph
}//namespace hgl
#endif//HGL_SHADER_STRING_LIST_INCLUDE