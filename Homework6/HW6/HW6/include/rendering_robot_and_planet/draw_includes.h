/*********************************
4104056004 李家駿 第四次作業 5/1
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
   fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, fp);         //讀取 bitmap header
   
   lInfoSize = bitmapFileHeader.bfOffBits - sizeof(BITMAPFILEHEADER);   //Info的size
   fread(bitmapInfo, lInfoSize, 1, fp);
   
   
   lBitSize = bitmapInfo->bmiHeader.biSizeImage;                  //配置記憶體
   bitmapImage = new BYTE[lBitSize];
   fread(bitmapImage, 1, lBitSize, fp);                        //讀取影像檔
   
   fclose(fp);
   
   //此時傳回bitmapImage的話，顏色會是BGR順序，下面迴圈會改順序為RGB
   pixel = (bitmapInfo->bmiHeader.biWidth)*(bitmapInfo->bmiHeader.biHeight);

   for( int i=0 ; i<pixel ; i++, p+=3 )
   {
      //交換bitmapImage[p]和bitmapImage[p+2]的值
      change = bitmapImage[p];
      bitmapImage[p] = bitmapImage[p+2];
      bitmapImage[p+2]  = change;
   }
   
   return bitmapImage;
} 