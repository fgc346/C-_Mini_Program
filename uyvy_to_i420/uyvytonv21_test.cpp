#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <unistd.h>

#include <iostream>
#include <string>

#define PATH_SIZE 255

//nv21 --> yyyyyy vu vu vu vu
//nv12 --> yyyyyy  uv uv uv uv
int UYVY422ToNv21(unsigned char *src_buffer, int width, int height, unsigned char *des_buffer) {
    int h,j,k;
    int isu=1;
    int uyvySize, nv21Size;
    unsigned char *uyvy, *nv21;
    int nv21_uv;

    uyvy = src_buffer;
    nv21 = des_buffer;

    printf("%s:%d\n", __func__, __LINE__);
    if (uyvy == NULL || nv21 == NULL) {
        printf ("error: input data null!\n");
        return -1;
    }

    uyvySize = width * height * 2;
    nv21Size = width * height * 3 / 2;

    int y = 0, v = width * height, u = v + 1;

    nv21_uv = width * height;
    printf("%s:%d\n", __func__, __LINE__);
    //提取y分量,这里提供了两种方法都可以，方便更深的理解yuv存储
#if 1
    int index = 0;
    for (int i = 0; i < uyvySize; i += 2) {
        //printf("%s:%d i = %d, index = %d\n", __func__, __LINE__, i, index);
        *(nv21 + index) = *(uyvy + i + 1);
        index ++;
    }
#else
    for (int i = 0; i < uyvySize; i += 4) {
        nv21[y++] = uyvy[i + 1];//y^M
        nv21[y++] = uyvy[i + 3];//y^M
    }   
#endif

    printf("%s:%d\n", __func__, __LINE__);
    //提取uv分量,这里也提供了两种方法，都可以
#if 0
    for (int h = 0; h < height; h += 2){
        printf("%s:%d h = %d\n", __func__, __LINE__, h);

        for (int j = h * width * 2 + 1; j < width * 2 * (h + 1); j += 2){
            if (isu == 1) {
                nv21[u]=uyvy[j - 1];
                u+=2;
                isu=0;
            } else {
                nv21[v]=uyvy[j - 1];
                v+=2;
                isu=1;
            }
        }
    }
#else
    int uv_index = 0;
    for(j=0; j< height; j =j+2) {
        for(k = j*width*2+1; k< width*2*(j+1); k=k+4) {//YUYV单行中每四个字节含有一对UV分量
            *(nv21 + v + uv_index) = *(uyvy + k + 1);
            *(nv21 + u + uv_index) = *(uyvy + k - 1);
            uv_index += 2;
        }
    }

#endif
    return 0;
}



//nv12 --> yyyyyy  uv uv uv uv  其中y(width*height), u(1/4*width*height),v(1/4*width*height) 4:2:0
// UYVY -->  uyvy uyvy uyvy 其中y(width*height),u(1/2*width*height),v(1/2*width*heightx), 4:2:2
// 原理YUV4:2:0 ---> YUV4:2:2  Y不变，将U和V信号值的每一行分别拷贝一份形成连续两行数据
int Nv21ToUYVY422(unsigned char *src_buffer, int width, int height, unsigned char *des_buffer) {
    unsigned char *uyvy, *nv12;
    nv12 = src_buffer;
    uyvy = des_buffer;
    int nv12Size = width * height * 3 / 2;

    printf("%s:%d\n", __func__, __LINE__);
    if (uyvy == NULL || nv12 == NULL) {
        printf ("error: input data null!\n");
        return -1;
    }
    printf("%s:%d\n", __func__, __LINE__);
    //提取y分量,方便更深的理解yuv存储
    int index = 1;
    int ySize = width *height;
    // 对 nv12的前 width×height 个y，赋值给uyvy
    for (int i = 0; i < ySize; ++i) {
        //printf("%s:%d i = %d, index = %d\n", __func__, __LINE__, i, index);
        *(uyvy + index) = *(nv12 + i);
        index += 2;
    }

    printf("%s:%d\n", __func__, __LINE__);
    // 提取uv分量,width ,height 均为偶数
    // 将U和V信号值的每一行分别拷贝一份形成连续两行数据
    int uv_index = 0;
    for (int j = width * height; j < nv12Size; j += 2)
    {
        *(uyvy + uv_index) = *(nv12 + j);
        *(uyvy + uv_index + 2) = *(nv12 + j + 1);
        *(uyvy + uv_index + 4) = *(nv12 + j);
        *(uyvy + uv_index + 6) = *(nv12 + j + 1);
        uv_index += 8;
    }
    return 0;
}

//yuv 420p
// n = width * height
//i420 --> yyyyyy(n个) u..u(n/4个) v...v(n/4个)
//yv12 --> yyyyyy(n个)  v...v(n/4个) u...u(n/4个)
int UYVY422ToYUV_I420(unsigned char *src_buffer, int width, int height, unsigned char *des_buffer) {
    int h = 0, j = 0, k = 0;
    int isu=1;
    int uyvySize = 0, i420Size = 0;
    unsigned char *uyvy, *i420;
    int i420_uv = 0;

    uyvy = src_buffer;
    i420 = des_buffer;

    printf("%s:%d\n", __func__, __LINE__);
    if (uyvy == NULL || i420 == NULL) {
        printf ("error: input data null!\n");
        return -1;
    }

    uyvySize = width * height * 2;
    i420Size = width * height * 3 / 2;

    int y = 0, v = width * height, u = v +  width * height / 4;

    i420_uv = width * height;
    printf("%s:%d\n", __func__, __LINE__);
    //提取y分量,这里提供了两种方法都可以，方便更深的理解yuv存储
#if 1
    int index = 0;
    for (int i = 0; i < uyvySize; i += 2) {
        //printf("%s:%d i = %d, index = %d\n", __func__, __LINE__, i, index);
        *(i420 + index) = *(uyvy + i + 1);
        index ++;
    }
#else
    for (int i = 0; i < uyvySize; i += 4) {
        i420[y++] = uyvy[i + 1];//y^M
        i420[y++] = uyvy[i + 3];//y^M
    }   
#endif

    printf("%s:%d\n", __func__, __LINE__);
    //提取uv分量,这里也提供了两种方法，都可以
#if 0
    int u = 0;
    int v = 0;
    for (int h = 0; h < height; h += 2){
        printf("%s:%d h = %d\n", __func__, __LINE__, h);

        for (int j = h * width * 2 + 1; j < width * 2 * (h + 1); j += 2){
            if (isu == 1) {
                i420[u]=uyvy[j - 1];
                ++u;
                isu=0;
            } else {
                i420[v]=uyvy[j - 1];
                ++v;
                isu=1;
            }
        }
    }
#else
    int u_index = 0;
    int v_index = 0;
    for(j = 0; j < height; j = j + 2) {
        for(k = j * width * 2 + 1; k < width * 2 * (j + 1); k = k + 4) {//YUYV单行中每四个字节含有一对UV分量
            *(i420 + v + v_index) = *(uyvy + k + 1);
            ++v_index;
            *(i420 + u + u_index) = *(uyvy + k - 1);
            ++u_index;
        }
    }

#endif
    return 0;
}

int simplest_uyvy_to_nv21(const char *url_in, int w, int h, int num, const char *url_out) {
    FILE *fp = fopen(url_in, "rb+");
    FILE *fp1 = fopen(url_out, "wb+");

    printf("%s:%d\n", __func__, __LINE__);
    unsigned char *pic_nv21420=(unsigned char *)malloc(w * h * 3 / 2);
    unsigned char *pic_uyvy422 = (unsigned char *)malloc(w * h * 2);

    fread(pic_uyvy422, 1, w * h * 2, fp);
    UYVY422ToNv21(pic_uyvy422, w, h, pic_nv21420);
    fwrite(pic_nv21420, 1, w * h * 3 /2, fp1);

    printf("%s:%d\n", __func__, __LINE__);
    free(pic_nv21420);
    free(pic_uyvy422);
    fclose(fp);
    fclose(fp1);

    return 0;
}

int simplest_uyvy_to_i420(const char *url_in, int w, int h, int num, const char *url_out){
    FILE *fp_in = fopen(url_in, "rb+");
    FILE *fp_out = fopen(url_out, "wb+");
    printf("%s:%d\n", __func__, __LINE__);
    unsigned char *pic_i420 = new unsigned char[w * h * 3 / 2];
    unsigned char *pic_uyvy422 = new unsigned char[w * h * 2];

    fread(pic_uyvy422, 1, w * h * 2, fp_in);
    UYVY422ToYUV_I420(pic_uyvy422, w, h, pic_i420);
    fwrite(pic_i420, 1, w * h * 3 / 2, fp_out);
    printf("%s:%d\n", __func__, __LINE__);
    delete []pic_i420;
    delete []pic_uyvy422;
    fclose(fp_in);
    fclose(fp_out);
    return 0;
}


size_t GetCurrentExcutableFilePathName( char* processdir,char* processname, size_t len)
{
        char* path_end;
        if(readlink("/proc/self/exe", processdir,len) <=0)
                return -1;
        path_end = strrchr(processdir,  '/');
        if(path_end == NULL)
                return -1;
        ++path_end;
        strcpy(processname, path_end);
        *path_end = '\0';
        return (size_t)(path_end - processdir);
}

int main(int argc, char* argv[]) {
    //Test
    printf("%s:%d\n", __func__, __LINE__);
    char path[PATH_SIZE];
	if(!getcwd(path,PATH_SIZE)){
		std::cout << "Get path fail!" << std::endl;
		return 0;
	}

    // char *path;
    // char *process_name;
    // // path = get_current_dir_name();
    // size_t num;
    // GetCurrentExcutableFilePathName(path, process_name, num);
    // std::cout << " process_name = " << process_name << std::endl;
    
    std::string src_jpg_path = ((std::string)path + "/pic21.jpg");
    std::cout << "the current path = " << path << std::endl;
    std::cout << "src_jpg_path = " << src_jpg_path << std::endl;
    std::string des_yuv_nv21_path = (std::string)path + "/1280_800.nv21";
    std::string des_yuv_i420_path = (std::string)path + "/1280_800.i420";
    simplest_uyvy_to_nv21(src_jpg_path.data(), 1280, 800, 1, des_yuv_nv21_path.data());
    simplest_uyvy_to_i420(src_jpg_path.data(), 1280, 800, 1, des_yuv_i420_path.data());
    return 0;
}

