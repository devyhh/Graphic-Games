// glMaterial.cpp: implementation of the CglMaterial class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "example.h"
#include "glMaterial.h"
#include "glPicLoad.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CglMaterial::CglMaterial()
{

}

CglMaterial::~CglMaterial()
{

}
GLuint CglMaterial::LoadGLTransparentTextures(char *filename)
{
	GLuint texture[1]={0};
	CglImageData* TextureImage=0;					// Create Storage Space For The Texture
	CglPicLoad pic;
	unsigned char *newData;
	if ((TextureImage=pic.ReadBMP(filename))!=NULL)
	{
		newData = new unsigned char [TextureImage->m_width*TextureImage->m_height*4];
		for(int i=0;i<TextureImage->m_width*TextureImage->m_height;i++)
		{
			newData[i*4]=TextureImage->m_pData[i*3];
			newData[i*4+1]=TextureImage->m_pData[i*3+1];
			newData[i*4+2]=TextureImage->m_pData[i*3+2];
			int tra=TextureImage->m_pData[i*3]+TextureImage->m_pData[i*3+1]+TextureImage->m_pData[i*3+2];
			if(tra>255)newData[i*4+3]=255;
			else newData[i*4+3]=tra;
		}
		glGenTextures(1, &texture[0]);					// Create The Texture
		glBindTexture(GL_TEXTURE_2D, texture[0]);
		// Generate The Texture
		gluBuild2DMipmaps(GL_TEXTURE_2D,4,TextureImage->m_width, TextureImage->m_height,GL_BGRA_EXT, GL_UNSIGNED_BYTE, newData);
		//filter 参数
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR_MIPMAP_LINEAR);	// Linear Filtering
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);	// Linear Filteringd
		
		//wrap参数
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);		
		//	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
		//	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP );		
		//	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_MODULATE);	//颜色直接相乘
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_MODULATE);	//
		//	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_BLEND);
		delete TextureImage;
		delete newData;
	}
	return texture[0];
}
GLuint CglMaterial::LoadGLTextures(char *filename)
{
	GLuint texture[1]={0};
	CglImageData* TextureImage=0;					// Create Storage Space For The Texture
	CglPicLoad pic;
	if ((TextureImage=pic.ReadBMP(filename))!=NULL)
	{
		glGenTextures(1, &texture[0]);					// Create The Texture
		glBindTexture(GL_TEXTURE_2D, texture[0]);
		// Generate The Texture
		gluBuild2DMipmaps(GL_TEXTURE_2D,(TextureImage->m_bits>>3),TextureImage->m_width, TextureImage->m_height,GL_BGR_EXT, GL_UNSIGNED_BYTE, TextureImage->m_pData);
		//filter 参数
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR_MIPMAP_LINEAR);	// Linear Filtering
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);	// Linear Filteringd
		
		//wrap参数
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);		
	//	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
	//	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP );		
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_MODULATE);	//颜色直接相乘
		//	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_REPLACE);	//
	//	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_BLEND);
		delete TextureImage;
	}
	return texture[0];
}
