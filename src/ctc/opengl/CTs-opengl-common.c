//
// Copyright (c) 2014 Samsung Electronics Co., Ltd.
//
// Licensed under the Apache License, Version 2.0 (the License);
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
#include "CTs-opengl-common.h"

/** @addtogroup ctc-opengl
* @ingroup		ctc
* @{
*/

//Add helper function definitions here

/**
* @function		OpenGl2ElmShutdown
* @description	Clears elementary buffers
* @parameter	NA
* @return		NA
*/
void OpenGl2ElmShutdown(void)
{
	// @NOTE: Auto hide application after a certain delay
	sleep(TIME_DELAY);

	elm_exit();

	g_pstOpenGl2ProjectionMat = NULL;
	g_pstOpenGl2ModelViewMat = NULL;
	g_pstOpenGl2MVPMat = NULL;
	g_nOpenGl2Delay = 0;
	g_nOpenGl2FrameCount = 0;
}

/**
* @function		OpenGl2ScaleMatrix
* @description	Scales an Identity Matrix
* @parameter	[IN] gl2_matrix_st *pstResult
* 				[IN] GLfloat SX,
* 				[IN] GLfloat SY
* 				[IN] GLfloat SZ
* @return		NA
*/
void OpenGl2ScaleMatrix(gl2_matrix_st *pstResult, GLfloat SX, GLfloat SY, GLfloat SZ)
{
	pstResult->Mat[0][0] *= SX;
	pstResult->Mat[0][1] *= SX;
	pstResult->Mat[0][2] *= SX;
	pstResult->Mat[0][3] *= SX;

	pstResult->Mat[1][0] *= SY;
	pstResult->Mat[1][1] *= SY;
	pstResult->Mat[1][2] *= SY;
	pstResult->Mat[1][3] *= SY;

	pstResult->Mat[2][0] *= SZ;
	pstResult->Mat[2][1] *= SZ;
	pstResult->Mat[2][2] *= SZ;
	pstResult->Mat[2][3] *= SZ;
}

/**
* @function		OpenGl2FrustumMatrix
* @description	Set the Frustrum Matrix
* @parameter	[IN] gl2_matrix_st *pstResult,
* 				[IN] float fLeft,
* 				[IN] float fRight
* 				[IN] float fBottom
* 				[IN] float fTop,
* 				[IN] float fNearZ
* 				[IN] float fFarZ
* @return		NA
*/
void OpenGl2FrustumMatrix(gl2_matrix_st *pstResult, float fLeft, float fRight, float fBottom, float fTop, float fNearZ, float fFarZ)
{
	float       fDeltaX = fRight - fLeft;
	float       fDeltaY = fTop - fBottom;
	float       fDeltaZ = fFarZ - fNearZ;
	gl2_matrix_st stFrust;

	if ( (fNearZ <= 0.0f) || (fFarZ <= 0.0f) ||
		(fDeltaX <= 0.0f) || (fDeltaY <= 0.0f) || (fDeltaZ <= 0.0f) )
	{
		return;
	}

	stFrust.Mat[0][0] = 2.0f * fNearZ / fDeltaX;
	stFrust.Mat[0][1] = stFrust.Mat[0][2] = stFrust.Mat[0][3] = 0.0f;

	stFrust.Mat[1][1] = 2.0f * fNearZ / fDeltaY;
	stFrust.Mat[1][0] = stFrust.Mat[1][2] = stFrust.Mat[1][3] = 0.0f;

	stFrust.Mat[2][0] = (fRight + fLeft) / fDeltaX;
	stFrust.Mat[2][1] = (fTop + fBottom) / fDeltaY;
	stFrust.Mat[2][2] = -(fNearZ + fFarZ) / fDeltaZ;
	stFrust.Mat[2][3] = -1.0f;

	stFrust.Mat[3][2] = -2.0f * fNearZ * fFarZ / fDeltaZ;
	stFrust.Mat[3][0] = stFrust.Mat[3][1] = stFrust.Mat[3][3] = 0.0f;

	OpenGl2MulMatrix(pstResult, &stFrust, pstResult);
}

/**
* @function		OpenGl2LoadIdentity
* @description	Loads an Identity Matrix
* @parameter	[IN] gl2_matrix_st *pstResult
* @return		NA
*/
void OpenGl2LoadIdentity(gl2_matrix_st *pstResult)
{
	memset(pstResult, 0x0, sizeof(gl2_matrix_st));
	pstResult->Mat[0][0] = 1.0f;
	pstResult->Mat[1][1] = 1.0f;
	pstResult->Mat[2][2] = 1.0f;
	pstResult->Mat[3][3] = 1.0f;
}

/**
* @function		OpenGl2MulMatrix
* @description	Multiplies two matrix
* @parameter	[IN] gl2_matrix_st *pstResult,
* 				[IN] gl2_matrix_st *pstSrcA,
* 				[IN] gl2_matrix_st *pstSrcB
* @return		NA
*/
void OpenGl2MulMatrix(gl2_matrix_st *pstResult, gl2_matrix_st *pstSrcA, gl2_matrix_st *pstSrcB)
{
	gl2_matrix_st stTmp;
	int nLoop = 0;

	for ( nLoop=0; nLoop<4; nLoop++ )
	{
		stTmp.Mat[nLoop][0] = (pstSrcA->Mat[nLoop][0] * pstSrcB->Mat[0][0]) +
			(pstSrcA->Mat[nLoop][1] * pstSrcB->Mat[1][0]) +
			(pstSrcA->Mat[nLoop][2] * pstSrcB->Mat[2][0]) +
			(pstSrcA->Mat[nLoop][3] * pstSrcB->Mat[3][0]) ;

		stTmp.Mat[nLoop][1] = (pstSrcA->Mat[nLoop][0] * pstSrcB->Mat[0][1]) +
			(pstSrcA->Mat[nLoop][1] * pstSrcB->Mat[1][1]) +
			(pstSrcA->Mat[nLoop][2] * pstSrcB->Mat[2][1]) +
			(pstSrcA->Mat[nLoop][3] * pstSrcB->Mat[3][1]) ;

		stTmp.Mat[nLoop][2] = (pstSrcA->Mat[nLoop][0] * pstSrcB->Mat[0][2]) +
			(pstSrcA->Mat[nLoop][1] * pstSrcB->Mat[1][2]) +
			(pstSrcA->Mat[nLoop][2] * pstSrcB->Mat[2][2]) +
			(pstSrcA->Mat[nLoop][3] * pstSrcB->Mat[3][2]) ;

		stTmp.Mat[nLoop][3] = (pstSrcA->Mat[nLoop][0] * pstSrcB->Mat[0][3]) +
			(pstSrcA->Mat[nLoop][1] * pstSrcB->Mat[1][3]) +
			(pstSrcA->Mat[nLoop][2] * pstSrcB->Mat[2][3]) +
			(pstSrcA->Mat[nLoop][3] * pstSrcB->Mat[3][3]) ;
	}
	memcpy(pstResult, &stTmp, sizeof(gl2_matrix_st));
}

/**
* @function		OpenGl2RotationMatrix
* @description	Rotates an Matrix
* @parameter	[IN] gl2_matrix_st *pstResult,
* 				[IN] GLfloat glfAngle,
* 				[IN] GLfloat X,
* 				[IN] GLfloat Y,
* 				[IN] GLfloat Z
* @return		NA
*/
void OpenGl2RotationMatrix(gl2_matrix_st *pstResult, GLfloat glfAngle, GLfloat X, GLfloat Y, GLfloat Z)
{
	GLfloat glfSinAngle = 0.0, glfCosAngle = 0.0;
	GLfloat glfMAG = sqrtf(X * X + Y * Y + Z * Z);

	glfSinAngle = sin ( glfAngle * M_PI / 180.0f );
	glfCosAngle = cos ( glfAngle * M_PI / 180.0f );
	if ( glfMAG > 0.0f )
	{
		GLfloat XX, YY, ZZ, XY, YZ, ZX, XS, YS, ZS;
		GLfloat glfOneMinusCos = 0.0;
		gl2_matrix_st RotMat;

		X /= glfMAG;
		Y /= glfMAG;
		Z /= glfMAG;

		XX = X * X;
		YY = Y * Y;
		ZZ = Z * Z;
		XY = X * Y;
		YZ = Y * Z;
		ZX = Z * X;
		XS = X * glfSinAngle;
		YS = Y * glfSinAngle;
		ZS = Z * glfSinAngle;
		glfOneMinusCos = 1.0f - glfCosAngle;

		RotMat.Mat[0][0] = (glfOneMinusCos * XX) + glfCosAngle;
		RotMat.Mat[0][1] = (glfOneMinusCos * XY) - ZS;
		RotMat.Mat[0][2] = (glfOneMinusCos * ZX) + YS;
		RotMat.Mat[0][3] = 0.0F;

		RotMat.Mat[1][0] = (glfOneMinusCos * XY) + ZS;
		RotMat.Mat[1][1] = (glfOneMinusCos * YY) + glfCosAngle;
		RotMat.Mat[1][2] = (glfOneMinusCos * YZ) - XS;
		RotMat.Mat[1][3] = 0.0F;

		RotMat.Mat[2][0] = (glfOneMinusCos * ZX) - YS;
		RotMat.Mat[2][1] = (glfOneMinusCos * YZ) + XS;
		RotMat.Mat[2][2] = (glfOneMinusCos * ZZ) + glfCosAngle;
		RotMat.Mat[2][3] = 0.0F;

		RotMat.Mat[3][0] = 0.0F;
		RotMat.Mat[3][1] = 0.0F;
		RotMat.Mat[3][2] = 0.0F;
		RotMat.Mat[3][3] = 1.0F;

		OpenGl2MulMatrix( pstResult, &RotMat, pstResult );
	}
}

/**
* @function		OpenGl2LoadShader
* @description	Helper function to load shaders from a shader source
* @parameter	[IN] gl2_renderer_st pstRenderder
* 				[IN] GLenum eType
* 				[IN] const char *pchShaderSrc
* @return		Shader (GLuint)
*/
GLuint OpenGl2LoadShader(gl2_renderer_st *pstRenderder, GLenum eType, const char *pchShaderSrc)
{
	Evas_GL_API *pGL = pstRenderder->pGLApi;
	GLuint glunShader = 0;
	GLint glunCompiled = 0;

	// Create the Shader object
	glunShader = pGL->glCreateShader(eType);
	if ( glunShader == 0 )
	{
		FPRINTF("[Line : %d][%s] glCreateShader has error in creating an empty shader object\\n", __LINE__, API_NAMESPACE);
		return 0;
	}
	// Load/Compile Shader source
	pGL->glShaderSource(glunShader, GL_NO_OF_ELEMENTS_IN_SRC, &pchShaderSrc, NULL);
	pGL->glCompileShader(glunShader);
	pGL->glGetShaderiv(glunShader, GL_COMPILE_STATUS, &glunCompiled);
	
	if ( !glunCompiled )
	{
		GLint glnInfoLen = 0;
		GLsizei glnActualInfoLen = 0;
		pGL->glGetShaderiv(glunShader, GL_INFO_LOG_LENGTH, &glnInfoLen);
		if ( glnInfoLen > 1 )
		{
			GLchar* pchInfoLog = (GLchar*) malloc(sizeof(GLchar) * glnInfoLen);
			pGL->glGetShaderInfoLog(glunShader, glnInfoLen, &glnActualInfoLen, pchInfoLog);
			FPRINTF("[Line : %d][%s] Error compiling Shader:\n%s\n======\n%s\n==\\n", __LINE__, API_NAMESPACE, pchInfoLog, pchShaderSrc );
			free(pchInfoLog);
		}
		
		FPRINTF("[Line : %d][%s] Error compiling Shader:\n%s\n=====\\n", __LINE__, API_NAMESPACE, pchShaderSrc );
		pGL->glDeleteShader(glunShader);
		return 0;
	}
	return glunShader;
}

/**
* @function		OpenGl2InitShader
* @description	Initializes shader code
* @parameter	[IN] gl2_renderer_st pstRenderder
* @return		int (If error occurs returns 0 otherwise 1)
*/
int OpenGl2InitShader(gl2_renderer_st *pstRenderder)
{
	Evas_GL_API *pGL = pstRenderder->pGLApi;

	const char szVertShaderSrc[] =
		"precision mediump float;\n"
		"uniform mat4 Modelview;\n"
		"attribute vec4 vPosition;\n"
		"attribute vec4 color;\n"
		"varying vec4 colorvar;\n"
		"void main()\n"
		"{\n"
		"gl_Position = Modelview*vPosition;\n"
		"colorvar = color;\n"
		"}";
	const char szFragShaderSrc[] =
		"precision mediump float;\n"
		"varying vec4 colorvar;\n"
		"void main()\n"
		"{\n"
		"gl_FragColor = colorvar;\n"
		"}";  

	GLint glnLinked = 0, glnNoOfShaders = 0;

	// Load the vertex/fragment shaders
	pstRenderder->glunVTXShader = OpenGl2LoadShader(pstRenderder, GL_VERTEX_SHADER, (const char*)szVertShaderSrc);
	pstRenderder->glunFGMTShader = OpenGl2LoadShader(pstRenderder, GL_FRAGMENT_SHADER, (const char*)szFragShaderSrc);

	// Create the glunProgram object
	pstRenderder->glunProgram = pGL->glCreateProgram();
	if ( pstRenderder->glunProgram == 0 )
	{
		FPRINTF("[Line : %d][%s] glCreateProgram is failed to create an empty program object\n\\n", __LINE__, API_NAMESPACE);
		return 0;
	}
	pGL->glAttachShader(pstRenderder->glunProgram, pstRenderder->glunVTXShader);
	pGL->glAttachShader(pstRenderder->glunProgram, pstRenderder->glunFGMTShader);
	pGL->glGetProgramiv(pstRenderder->glunProgram, GL_ATTACHED_SHADERS, &glnNoOfShaders);

	pGL->glLinkProgram(pstRenderder->glunProgram);
	pGL->glGetProgramiv(pstRenderder->glunProgram, GL_LINK_STATUS, &glnLinked);
	if ( !glnLinked )
	{
		GLint glnInfoLen = 0;
		GLsizei glnActualInfoLen = 0;
		pGL->glGetProgramiv(pstRenderder->glunProgram, GL_INFO_LOG_LENGTH, &glnInfoLen);
		if ( glnInfoLen > 1 )
		{
			GLchar* pchInfoLog = (GLchar*) malloc(sizeof(GLchar) * glnInfoLen);
			pGL->glGetProgramInfoLog(pstRenderder->glunProgram, glnInfoLen, &glnActualInfoLen, (char *)&pchInfoLog);
			FPRINTF("[Line : %d][%s] Error linking glunProgram, ProgramInfoLog:\n%s\n\\n", __LINE__, API_NAMESPACE, pchInfoLog);
			free(pchInfoLog);
		}
		FPRINTF("[Line : %d][%s] Error linking glunProgram: %d\\n", __LINE__, API_NAMESPACE, glnLinked);
		pGL->glDeleteProgram(pstRenderder->glunProgram);
		return 0;
	}
	return 1;
}

/** @} */ //end of ctc-opengl
