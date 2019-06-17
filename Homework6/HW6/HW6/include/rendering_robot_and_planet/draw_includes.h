/*********************************
4104056004 ���a�@ �ĥ|���@�~ 5/1
Includes needed headers and declares some constants.
*********************************/
#include "GL\glew.h"
#include "GL\glut.h"
#include "GL\glm.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <windows.h>
#include "math.h"
#define INITIAL_WIDTH 960
#define INITIAL_HEIGHT 540
static bool draw_box = false;
unsigned char *LoadBitmapFile(char *fileName, BITMAPINFO *bitmapInfo)
{
   FILE            *fp;
   BITMAPFILEHEADER   bitmapFileHeader;   // Bitmap file header
   unsigned char       *bitmapImage;      // Bitmap image data
   unsigned int      lInfoSize;         // Size of information
   unsigned int      lBitSize;         // Size of bitmap
   
   unsigned char change;
    int pixel;
    int p=0;
       
   fp = fopen(fileName, "rb");
   fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, fp);         //Ū�� bitmap header
   
   lInfoSize = bitmapFileHeader.bfOffBits - sizeof(BITMAPFILEHEADER);   //Info��size
   fread(bitmapInfo, lInfoSize, 1, fp);
   
   
   lBitSize = bitmapInfo->bmiHeader.biSizeImage;                  //�t�m�O����
   bitmapImage = new BYTE[lBitSize];
   fread(bitmapImage, 1, lBitSize, fp);                        //Ū���v����
   
   fclose(fp);
   
   //���ɶǦ^bitmapImage���ܡA�C��|�OBGR���ǡA�U���j��|�ﶶ�Ǭ�RGB
   pixel = (bitmapInfo->bmiHeader.biWidth)*(bitmapInfo->bmiHeader.biHeight);

   for( int i=0 ; i<pixel ; i++, p+=3 )
   {
      //�洫bitmapImage[p]�MbitmapImage[p+2]����
      change = bitmapImage[p];
      bitmapImage[p] = bitmapImage[p+2];
      bitmapImage[p+2]  = change;
   }
   
   return bitmapImage;
} 