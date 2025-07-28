#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

// splict yuv file
int simplest_yuv420_split(const char *url, int w ,int h, int num){
    // open yuv file
    FILE *fp = fopen(url, "rb");
    if(!fp){
        fprintf(stderr, "Error: Open failed (errno:%d): %s\n",
                errno, strerror(errno));
        fclose(fp);
        exit(EXIT_FAILURE);
    }

    // touch y、u、v files
    FILE *fp1 = fopen("C:\\Users\\ASUS\\Videos\\output_420_y.y", "wb+");
    FILE *fp2 = fopen("C:\\Users\\ASUS\\Videos\\output_420_u.y", "wb+");
    FILE *fp3 = fopen("C:\\Users\\ASUS\\Videos\\output_420_v.y", "wb+");

    // check file open
    if(!fp1 || !fp2 || !fp3){
        fprintf(stderr, "Error: Open file failed (errno:%d): %s\n",
                errno,strerror(errno));
        fclose(fp);
        if(fp1) fclose(fp1);
        if(fp2) fclose(fp2);
        if(fp3) fclose(fp3);
        exit(EXIT_FAILURE);
    }

    // alloc memory
    size_t frame_size = w * h * 3 / 2;
    unsigned char *pic = (unsigned char*)malloc(frame_size);

    // check memory allocation
    if(!pic){
        fprintf(stderr, "Error: Memory allocation failed\n");
        fclose(fp); fclose(fp1); fclose(fp2); fclose(fp3);
        return -1;
    }

    // handler
    for(int i = 0; i < num; ++i){
        size_t read_size = fread(pic, 1, frame_size, fp);
        if(read_size != frame_size){
            fprintf(stderr, "Warning: Incomplete read\n");
            break;
        }

        fwrite(pic, 1, w * h, fp1);
        fwrite(pic + w * h, 1, w * h / 4, fp2);
        fwrite(pic + w * h * 5 / 4, 1, w * h / 4, fp3);
    }

    // free resource
    free(pic);
    fclose(fp);
    fclose(fp1);
    fclose(fp2);
    fclose(fp3);

    return 0;
}

int main(){
    const char *file_path = "C:\\Users\\ASUS\\Videos\\yuv420p_320x240.yuv";
    int width = 320;
    int height = 240;
    int frame_size = 10;
    int result = simplest_yuv420_split(file_path, width, height, frame_size);

    if(result != 0){
        fprintf(stderr, "Error: YUV split failed\n");
    }

    return 0;
}