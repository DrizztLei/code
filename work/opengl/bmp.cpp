/************************************************************************/
/*	bmp.c											Vincent Hsu, Aug. 2005
/*	-----											----------------------
/*
/*	Implementation of bmp.h
/************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

#pragma pack(1)

typedef struct {
    short	Type;
    int		FileSize;
    short	Reserved1;
    short	Reserved2;
    int		Offset;
} BMPHEADER;

typedef struct {
    int		InfoSize;
    int		Width;
    int		Height;
    short	Plane;
    short	BitCount;
    int		Compression;
    int		ImageSize;
    int		XDPM;
    int		YDPM;
    int		ClrUsed;
    int		ClrImportant;
} BMPINFOHEADER;

rgb_image_struct* read_bmp_image(char *filename)
{
    int					i, j;
    FILE				*fp;
    BMPHEADER			header;
    BMPINFOHEADER		info;
    RGB					*pixel;
    char				pack;
    rgb_image_struct	*result;

    fp = fopen(filename, "rb");
    fread(&header, sizeof(BMPHEADER), 1, fp);
    fread(&info, sizeof(BMPINFOHEADER), 1, fp);

    pixel = (RGB *)malloc(info.Width * sizeof(RGB));

    result = allocate_image(info.Width, info.Height);

    for (i = info.Height - 1; i >= 0; i--)
    {
        fread(pixel, sizeof(RGB), info.Width, fp);
        for (j = 0; j < info.Width; j++)
        {
            result->pixel[i][j].r = pixel[j].r;
            result->pixel[i][j].g = pixel[j].g;
            result->pixel[i][j].b = pixel[j].b;
        }

        j = j * info.BitCount >> 3;

        while (j++ % 4 != 0)
        fread(&pack, sizeof(char), 1, fp);
    }

    free(pixel);
    fclose(fp);

    return result;
}

void write_bmp_image(const char *filename, rgb_image_struct *image)
{
    BMPHEADER		header;
    BMPINFOHEADER	info;
    int				i, j;
    char			pack = 0;
    FILE			*fp;
    RGBA				pixel;
    int				width;
    int				height;

    fp = fopen(filename, "wb");

    width = image->width;
    height = image->height;

    header.Type = 19778;
    header.FileSize = height * ((((width *3) >> 2) + 1) << 2) + 54;
    header.Reserved1 = 0;
    header.Reserved2 = 0;
    header.Offset = 54;

    fwrite(&header, sizeof(BMPHEADER), 1, fp);

    info.InfoSize = 40;
    info.Width = width;
    info.Height = height;
    info.Plane = 1;
    info.BitCount = 24;//32 RGBA
    info.Compression = 0;
    info.ImageSize = header.FileSize - 54;
    info.XDPM = 2873;
    info.YDPM = 2873;
    info.ClrUsed = 0;
    info.ClrImportant = 0;

    fwrite(&info, sizeof(BMPINFOHEADER), 1, fp);

    for (i = info.Height - 1; i >= 0; i--)
    {
        for (j = 0; j < info.Width; j++)
        {
            pixel.r = image->pixel[i][j].b;
            pixel.g = image->pixel[i][j].g;
            pixel.b = image->pixel[i][j].r;
            //	pixel.a = image->pixel[i][j].a;
            fwrite(&pixel, sizeof(RGB), 1, fp);
        }

        j = j * info.BitCount >> 3;

        while (j++ % 4 != 0)
        fwrite(&pack, sizeof(char), 1, fp);
    }

    fclose(fp);
    }
    void write_rgb_bmp_image(rgb_image_struct *image)
    {
        BMPHEADER		header;
        BMPINFOHEADER	info;
        int				i, j;
        char			pack = 0;
        FILE			*fp;
        RGBA				pixel;
        int				width;
        int				height;

        fp = fopen("r.bmp", "wb");

        width = image->width;
        height = image->height;

        header.Type = 19778;
        header.FileSize = height * ((((width *3) >> 2) + 1) << 2) + 54;
        header.Reserved1 = 0;
        header.Reserved2 = 0;
        header.Offset = 54;

        fwrite(&header, sizeof(BMPHEADER), 1, fp);

        info.InfoSize = 40;
        info.Width = width;
        info.Height = height;
        info.Plane = 1;
        info.BitCount = 24;//32 RGBA
        info.Compression = 0;
        info.ImageSize = header.FileSize - 54;
        info.XDPM = 2873;
        info.YDPM = 2873;
        info.ClrUsed = 0;
        info.ClrImportant = 0;

        fwrite(&info, sizeof(BMPINFOHEADER), 1, fp);

        for (i = info.Height - 1; i >= 0; i--)
        {
            for (j = 0; j < info.Width; j++)
            {
                pixel.r = image->pixel[i][j].r;
                pixel.g = image->pixel[i][j].r;
                pixel.b = image->pixel[i][j].r;
                //	pixel.a = image->pixel[i][j].a;
                fwrite(&pixel, sizeof(RGB), 1, fp);
            }

            j = j * info.BitCount >> 3;

            while (j++ % 4 != 0)
            fwrite(&pack, sizeof(char), 1, fp);
        }

    fclose(fp);

    fp = fopen("g.bmp", "wb");

    fwrite(&header, sizeof(BMPHEADER), 1, fp);

    fwrite(&info, sizeof(BMPINFOHEADER), 1, fp);

    for (i = info.Height - 1; i >= 0; i--)
    {
        for (j = 0; j < info.Width; j++)
        {
            pixel.r = image->pixel[i][j].g;
            pixel.g = image->pixel[i][j].g;
            pixel.b = image->pixel[i][j].g;
            //	pixel.a = image->pixel[i][j].a;
            fwrite(&pixel, sizeof(RGB), 1, fp);
        }

        j = j * info.BitCount >> 3;

        while (j++ % 4 != 0)
        fwrite(&pack, sizeof(char), 1, fp);
    }

    fclose(fp);


    fp = fopen("b.bmp", "wb");

    fwrite(&header, sizeof(BMPHEADER), 1, fp);

    fwrite(&info, sizeof(BMPINFOHEADER), 1, fp);

    for (i = info.Height - 1; i >= 0; i--)
    {
        for (j = 0; j < info.Width; j++)
        {
            pixel.r = image->pixel[i][j].b;
            pixel.g = image->pixel[i][j].b;
            pixel.b = image->pixel[i][j].b;
            //	pixel.a = image->pixel[i][j].a;
            fwrite(&pixel, sizeof(RGB), 1, fp);
        }

        j = j * info.BitCount >> 3;

        while (j++ % 4 != 0)
        fwrite(&pack, sizeof(char), 1, fp);
    }

    fclose(fp);
    }

rgb_image_struct* allocate_image(int width, int height)
{
    int					i, j, y_index;
    int					half_height;
    int					total_width;
    RGB					*pixel_buffer;
    RGB					default_color;
    /*RGBA					*pixel_buffer;
    RGBA					default_color;*/
    rgb_image_struct	*result;

    default_color.r = 0;
    default_color.g = 0;
    default_color.b = 0;
    //default_color.a = 0;

    result = (rgb_image_struct *)malloc(sizeof(rgb_image_struct));

    result->width = width;
    result->height = height;
    result->pixel = (RGB **)malloc(height * sizeof(RGB *));
    pixel_buffer = (RGB *)malloc(height * width * sizeof(RGB));
    y_index = 0;
    half_height = height / 2;
    total_width = (height - 1) * width;

    for (i = 0; i <= half_height; i++, y_index = y_index + width)
    {
        result->pixel[i] = &pixel_buffer[y_index];
        result->pixel[height - i - 1] = &pixel_buffer[total_width - y_index];

        for (j = width - 1; j >= 0; j--)
        {
            result->pixel[i][j] = default_color;
            result->pixel[height - i - 1][j] = default_color;
        }
    }

    return result;
}

void free_image(rgb_image_struct *image)
{
    free(*image->pixel);
    free(image->pixel);
    free(image);
}

void reverse_image_row(rgb_image_struct *image)
{
    int					i, j;
    rgb_image_struct	*tmp;

    tmp = allocate_image(image->width, image->height);

    for (i = 0; i < image->height; i++)
    {
        for (j = 0; j < image->width; j++)
        {
            tmp->pixel[image->height - 1 - i][j] = image->pixel[i][j];
        }
    }

    for (i = 0; i < image->height; i++)
    {
        for (j = 0; j < image->width; j++)
        {
            image->pixel[i][j] = tmp->pixel[i][j];
        }
    }

    free_image(tmp);
}

rgbf_image_struct* allocate_fimage(int width, int height)
{
    int					i, j, y_index;
    int					half_height;
    int					total_width;
    RGBf					*pixel_buffer;
    RGBf					default_color;
    /*RGBA					*pixel_buffer;
    RGBA					default_color;*/
    rgbf_image_struct	*result;

    default_color.r = 0;
    default_color.g = 0;
    default_color.b = 0;
    //default_color.a = 0;

    result = (rgbf_image_struct *)malloc(sizeof(rgbf_image_struct));

    result->width = width;
    result->height = height;
    result->pixel = (RGBf **)malloc(height * sizeof(RGBf *));
    pixel_buffer = (RGBf *)malloc(height * width * sizeof(RGBf));
    y_index = 0;
    half_height = height / 2;
    total_width = (height - 1) * width;

    for (i = 0; i <= half_height; i++, y_index = y_index + width)
    {
        result->pixel[i] = &pixel_buffer[y_index];
        result->pixel[height - i - 1] = &pixel_buffer[total_width - y_index];

        for (j = width - 1; j >= 0; j--)
        {
            result->pixel[i][j] = default_color;
            result->pixel[height - i - 1][j] = default_color;
        }
    }

    return result;
}
void free_fimage(rgbf_image_struct *image)
{
    free(*image->pixel);
    free(image->pixel);
    free(image);
}

void reverse_fimage_row(rgbf_image_struct *image)
{
    int					i, j;
    rgbf_image_struct	*tmp;

    tmp = allocate_fimage(image->width, image->height);

    for (i = 0; i < image->height; i++)
    {
        for (j = 0; j < image->width; j++)
        {
            tmp->pixel[image->height - 1 - i][j] = image->pixel[i][j];
        }
    }

    for (i = 0; i < image->height; i++)
    {
        for (j = 0; j < image->width; j++)
        {
            image->pixel[i][j] = tmp->pixel[i][j];
        }
    }

    free_fimage(tmp);
}

void clear_image(rgbf_image_struct *image)
{
    for (int i = 0; i < image->height; i++)
    {
        for (int j = 0; j < image->width; j++)
        {
            image->pixel[i][j].r = 0.0;
            image->pixel[i][j].g = 0.0;
            image->pixel[i][j].b = 0.0;
        }
    }
}

void clear_image(rgb_image_struct *image)
{
    for (int i = 0; i < image->height; i++)
    {
        for (int j = 0; j < image->width; j++)
        {
            image->pixel[i][j].r = 0.0;
            image->pixel[i][j].g = 0.0;
            image->pixel[i][j].b = 0.0;
        }
    }
}

