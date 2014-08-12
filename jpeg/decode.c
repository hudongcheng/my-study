#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <jpeglib.h>

int decode_file(FILE *input_file, FILE *output_file);

int main()
{
  FILE *input_file;
  FILE *output_file;
  input_file=fopen("lena.jpg","rb");
  output_file=fopen("lena.raw","wb");

  decode_file(input_file, output_file);

  fclose(input_file);
  fclose(output_file);

  return 0;
}

int decode_file(FILE *input_file, FILE *output_file)
{
  struct jpeg_decompress_struct cinfo;
  struct jpeg_error_mgr jerr;
  JSAMPARRAY buffer;
  unsigned char *src_buff;
  unsigned char *point;

  cinfo.err = jpeg_std_error(&jerr);
  jpeg_create_decompress(&cinfo);

  jpeg_stdio_src(&cinfo,input_file);
  jpeg_read_header(&cinfo,TRUE);
  jpeg_start_decompress(&cinfo);

  unsigned long width = cinfo.output_width;
  unsigned long height = cinfo.output_height;
  unsigned short depth = cinfo.output_components;

  src_buff = (unsigned char*)malloc(width*height*depth);
  memset(src_buff,0,sizeof(unsigned char)*width*height*depth);

  buffer = (*cinfo.mem->alloc_sarray)((j_common_ptr)&cinfo, JPOOL_IMAGE, width*depth, 1);

  printf("Nominal Image width: %u, height: %u\n", cinfo.image_width, cinfo.image_height);
  printf("Image width: %lu, height: %lu\n", width, height);
  point = src_buff;
  while (cinfo.output_scanline<height)
  {
    jpeg_read_scanlines(&cinfo,buffer,1);
    memcpy(point,*buffer,width*depth);
    /* fwrite(point, width*depth, 1, output_file);
       printf("width: %d, line length: %d\n",width, depth); */
    point += width*depth;
  }
  fwrite(src_buff, width*height*depth, 1, output_file);
  
  jpeg_finish_decompress(&cinfo);
  jpeg_destroy_decompress(&cinfo);
  free(src_buff);

  return 0;
}


int decode_mem(FILE *input_file, FILE *output_file)
{
  struct jpeg_decompress_struct cinfo;
  struct jpeg_error_mgr jerr;
  JSAMPARRAY buffer;
  unsigned char *src_buff;
  unsigned char *point;

  cinfo.err = jpeg_std_error(&jerr);
  jpeg_create_decompress(&cinfo);

  jpeg_stdio_src(&cinfo,input_file);
  jpeg_read_header(&cinfo,TRUE);
  jpeg_start_decompress(&cinfo);

  unsigned long width = cinfo.output_width;
  unsigned long height = cinfo.output_height;
  unsigned short depth = cinfo.output_components;

  src_buff = (unsigned char*)malloc(width*height*depth);
  memset(src_buff,0,sizeof(unsigned char)*width*height*depth);

  buffer = (*cinfo.mem->alloc_sarray)((j_common_ptr)&cinfo, JPOOL_IMAGE, width*depth, 1);

  printf("Nominal Image width: %u, height: %u\n", cinfo.image_width, cinfo.image_height);
  printf("Image width: %lu, height: %lu\n", width, height);
  point = src_buff;
  while (cinfo.output_scanline<height)
  {
    jpeg_read_scanlines(&cinfo,buffer,1);
    memcpy(point,*buffer,width*depth);
    /* fwrite(point, width*depth, 1, output_file);
       printf("width: %d, line length: %d\n",width, depth); */
    point += width*depth;
  }
  fwrite(src_buff, width*height*depth, 1, output_file);
  
  jpeg_finish_decompress(&cinfo);
  jpeg_destroy_decompress(&cinfo);
  free(src_buff);

  return 0;
}
