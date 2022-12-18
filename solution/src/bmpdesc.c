#include "bmpdesc.h"

#define BMP_HEADER_SIZE 54
#define BMP_FILE_SIGNATURE 0x4D42

/**
 * Структура заголовка BMP файла
*/
struct __attribute__((packed)) bmp_header
{
        uint16_t bfType;
        uint32_t bfileSize;
        uint32_t bfReserved;
        uint32_t bOffBits;
        uint32_t biSize;
        uint32_t biWidth;
        uint32_t biHeight;
        uint16_t biPlanes;
        uint16_t biBitCount;
        uint32_t biCompression;
        uint32_t biSizeImage;
        uint32_t biXPelsPerMeter;
        uint32_t biYPelsPerMeter;
        uint32_t biClrUsed;
        uint32_t biClrImportant;
};

/**
 * @brief Чтение заголовки BMP
 * @param[in] fd Указатель на дескриптор файла
 * @param[out] header Указатель на структуру заголовка BMP
 * @return Кол-во считанных данных
*/
static uint64_t read_bmp_header(FILE* fd, struct bmp_header* header)
{
    return fread(header, sizeof(struct bmp_header), 1, fd);
}

enum read_status from_bmp( FILE* in, struct image* img )
{
    struct bmp_header header = {0};
    if (read_bmp_header(in, &header) == 0) // Если не удалось прочитать заголовок
        return READ_INVALID_HEADER;

    if (header.bfType != BMP_FILE_SIGNATURE) // Если не совпадает сигнатура с сигнатурой BMP
        return READ_INVALID_SIGNATURE;

    if (header.biBitCount != 24) // Проверка глубины цвета
        return READ_INVALID_BITS;

    if (header.bOffBits != BMP_HEADER_SIZE) // Проверка версии заголовка
        return READ_INVALID_VERSION;

    img->width = header.biWidth;
    img->height = header.biHeight;
    const uint64_t img_size = img->height*img->width;

    img->data = (struct pixel*) malloc(img_size*sizeof(struct pixel)); // Выделение памяти под массив пикселей

    for(uint64_t i=0; i < img->height; i++)
    {
        if (fread(&(img->data[i*img->width]), sizeof(struct pixel), img->width, in) != img->width) // Если не удалось прочитать заданное кол-во байт
        {
            free(img->data); 
            if (feof(in)) // Если обнаружен конец файла
                return READ_UNEXPECTED_EOF;
            return READ_FILE_ERROR;
        }

        if (img->width*3 % 4 != 0) // Пропуск байт padding
            fseek(in, 4 - img->width*3 % 4, SEEK_CUR);
    }
    
    return READ_OK;
}

enum write_status to_bmp( FILE* out, struct image const* img )
{
    return WRITE_OK;
}