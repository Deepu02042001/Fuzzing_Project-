#include <stdio.h>
#include <string.h>
#include <png.h>

int main(int argc,char **argv){
  if(argc!=2)return 1;
  FILE *fp=fopen(argv[1],"rb");
  if(!fp)return 2;
  unsigned char hdr[8];
  fread(hdr,1,8,fp);
  if(png_sig_cmp(hdr,0,8)){ fclose(fp); return 0; }
  fseek(fp,16,SEEK_SET);
  unsigned char w[4]; fread(w,1,4,fp);
  if(!memcmp(w,"ABCD",4)){
    char *boom=NULL; *boom=1;
  }
  fclose(fp);
  return 0;
}

