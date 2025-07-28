#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

int adjust_yuv420_brightness(const char *url, int w, int h, int num, int brightness){
    FILE *fp = fopen(url, "rb");
    if(!fp){
        fprintf(stderr, "Error: Open file failed\n"
                "errno:%d\n"
                "%s\n", errno, strerror(errno));
        exit(EXIT_FAILURE);
    }

    FILE *fp1 = fopen("C:\\Users\\ASUS\\Videos\\output_adjust_brightniess.yuv", "wb+");
    if(!fp1){
        fprintf(stderr, "Error: Open file failed\n"
                "errno:%d\n"
                "%s\n", errno, strerror(errno));
        fclose(fp);
        exit(EXIT_FAILURE);
    }

    size_t frame_size = w * h * 3 / 2;
    unsigned char *pic = (unsigned char*)malloc(frame_size);

    // check memory allocation
    if(!pic){
        fprintf(stderr, "Error: malloc failed\n");
        fclose(fp);
        fclose(fp1);
        exit(-1);
    }

    for(int i = 0; i < num; ++i){
        if (fread(pic, 1, frame_size, fp) != frame_size){
            fprintf(stderr, "Warning: could not read full frame at index %d\n", i);
            break;
        }

        for(int j = 0; j < w * h; ++j){
            int val = pic[j] + brightness;
            if(val < 0) val = 0;
            if(val > 255) val = 255;
            pic[j] = (unsigned char)val;
        }
        fwrite(pic, 1, frame_size, fp1);
    }

    // free resource
    free(pic);
    fclose(fp);
    fclose(fp1);
    return 0;
}

int main(){
    const char *file_path = "C:\\Users\\ASUS\\Videos\\yuv420p_320x240.yuv";
    int width = 320;
    int height = 240;
    int frame = 1;
    int result = adjust_yuv420_brightness(file_path, width, height, frame, 100);

    if(result != 0){
        printf("Waring: Incomplete split\n");
    }
    return 0;
}