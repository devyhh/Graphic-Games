// glPicLoad.cpp: implementation of the CglPicLoad class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "example.h"
#include "glPicLoad.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CglPicLoad::CglPicLoad()
{

}

CglPicLoad::~CglPicLoad()
{

}

CglImageData* CglPicLoad::ReadBMP(char *filename)
{
	BITMAPFILEHEADER bfh;
	BITMAPINFOHEADER bih;
	FILE *fp=fopen(filename,"rb");
	if(!fp)
		return 0;
	CglImageData* image = new CglImageData;
	fread(&bfh,sizeof(bfh),1,fp);
	fread(&bih,sizeof(bih),1,fp);
	image->m_width=bih.biWidth;
	image->m_height=bih.biHeight;
	image->m_bits=bih.biBitCount;
	int cx = (bih.biWidth * bih.biBitCount)>>3;
	image->m_pData = new unsigned char[bih.biHeight*cx];
	int resizecx = ((bih.biWidth * bih.biBitCount + 15) & ~15) >> 3;
	unsigned char *buffer = new unsigned char[resizecx*bih.biHeight];
	fseek(fp,bfh.bfOffBits,SEEK_SET);
	fread(buffer,1,resizecx*bih.biHeight,fp);
	fclose(fp);
	int curpos=0;
	for(int h=image->m_height-1;h>=0;h--)
	{
		int index = h*resizecx;
		memcpy(&image->m_pData[curpos],&buffer[index],cx);
		curpos+=cx;
	}
	delete buffer;
	return image;
}
