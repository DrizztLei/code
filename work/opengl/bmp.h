/************************************************************************/
/*	bmp.h											Vincent Hsu, Aug. 2005
/*	-----											----------------------
/*
/*	A simplified version of the bmp.h in VIP library.
/*	It's used for I/O with 24-bit bmp file.
/************************************************************************/
#ifndef _BMP_H
#define _BMP_H

typedef unsigned char PIXEL_TYPE;


/* per pixel structure */
typedef struct RGB{
	PIXEL_TYPE	r;
	PIXEL_TYPE	g;
	PIXEL_TYPE	b;
	//PIXEL_TYPE  a;
	void operator = (RGB &oResID2)
	{
		//iStuID表示调用"="操作符时，"="左边的那个结构体对象的iStuID，其他同
		r = oResID2.r;
		g = oResID2.g;
		b = oResID2.b;
	};
} RGB;


/* per pixel structure */
typedef struct RGBf{
	float	r;
	float	g;
	float	b;
	//PIXEL_TYPE  a;
	void operator = (RGBf &oResID2)
	{
		//iStuID表示调用"="操作符时，"="左边的那个结构体对象的iStuID，其他同
		r = oResID2.r;
		g = oResID2.g;
		b = oResID2.b;
	};
} RGBf;

typedef struct {
	PIXEL_TYPE	r;
	PIXEL_TYPE	g;
	PIXEL_TYPE	b;
	//PIXEL_TYPE  a;
} RGBA;


/* per image structure */
typedef struct {
	int		width;
	int		height;
	RGB**	pixel;
	//RGBA**	pixel;
} rgb_image_struct;


/* per image structure */
typedef struct {
	int		width;
	int		height;
	RGBf**	pixel;
	//RGBA**	pixel;
} rgbf_image_struct;
/* read in a 24-bit bmp */
rgb_image_struct* read_bmp_image(char *filename);
/* allocate a 24-bit RGB image */
rgb_image_struct* allocate_image(int width, int height);
/* write out an image as a 24-bit bmp */
void write_bmp_image(const char *filename, rgb_image_struct *image);
/* release allocated memory */
void free_image(rgb_image_struct *image);
/* reverse image rows */
void reverse_image_row(rgb_image_struct *image);

/* allocate a 24-bit RGB image */
rgbf_image_struct* allocate_fimage(int width, int height);
void reverse_fimage_row(rgbf_image_struct *image);
void free_fimage(rgbf_image_struct *image);
void clear_image(rgbf_image_struct *image);
void clear_image(rgb_image_struct *image);
void write_rgb_bmp_image(rgb_image_struct *image);
#endif
