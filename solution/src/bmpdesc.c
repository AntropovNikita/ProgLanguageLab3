#include "bmpdesc.h"

#define BMP_INFOHEADER_SIZE 40     // Размер заголовка с информацией
#define BMP_FILE_SIGNATURE  0x4D42 // Сигнатура BMP файла
#define BMP_BIT_COUNT       24     // Глубина цвета
#define BMP_COLOR_COUNT     3      // Кол-во канало цвета
#define PADDING_COUNT       4      // Кратность для мусорных битов

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
static uint64_t read_bmp_header(FILE* fd, struct bmp_header* header);

/**
 * @brief Генерация заголовка BMP
 * @param[in] heigth Высота изображения
 * @param[in] width Ширина изображения
 * @return Заголовок BMP файла
*/
static struct bmp_header gen_bmp_header(uint32_t height, uint32_t width);

enum read_status from_bmp( FILE* in, struct image* img )
{
    struct bmp_header header = {0};
    if (read_bmp_header(in, &header) == 0) // Если не удалось прочитать заголовок
        return READ_INVALID_HEADER;

    if (header.bfType != BMP_FILE_SIGNATURE) // Если не совпадает сигнатура с сигнатурой BMP
        return READ_INVALID_SIGNATURE;

    if (header.biBitCount != BMP_BIT_COUNT) // Проверка глубины цвета
        return READ_INVALID_BITS;

    if (header.bOffBits != sizeof(struct bmp_header)) // Проверка версии заголовка
        return READ_INVALID_VERSION;

    img->width = header.biWidth;
    img->height = header.biHeight;
    const uint64_t img_size = img->height*img->width;

    img->data = (struct pixel*) malloc(img_size*sizeof(struct pixel)); // Выделение памяти под массив пикселей

    for(uint32_t i=0; i < img->height; i++)
    {
        if (fread(&(img->data[i*img->width]), sizeof(struct pixel), img->width, in) != img->width) // Если не удалось прочитать заданное кол-во байт
        {
            free(img->data); 
            if (feof(in)) // Если обнаружен конец файла
                return READ_UNEXPECTED_EOF;
            return READ_FILE_ERROR;
        }

        if (img->width*BMP_COLOR_COUNT % PADDING_COUNT != 0) // Пропуск байт padding
            fseek(in, PADDING_COUNT - img->width*BMP_COLOR_COUNT % PADDING_COUNT, SEEK_CUR);
    }
    
    return READ_OK;
}

enum write_status to_bmp( FILE* out, struct image const* img )
{
    const uint8_t padding_byte = 0;

    struct bmp_header header = gen_bmp_header(img->height, img->width);

    if (fwrite(&header, sizeof(struct bmp_header), 1, out) == 0)
        return WRITE_ERROR;

    for(uint32_t i = 0; i < img->height; i++)
    {
        if (fwrite(&(img->data[i*img->width]), sizeof(struct pixel), img->width, out) != img->width)
            return WRITE_ERROR;

        if (img->width*BMP_COLOR_COUNT % PADDING_COUNT != 0) // Добавление байт padding
            if (fwrite(&padding_byte, 1, 4 - img->width*BMP_COLOR_COUNT % PADDING_COUNT, out))
                return WRITE_ERROR;
    }

    return WRITE_OK;
}

static uint64_t read_bmp_header(FILE* fd, struct bmp_header* header)
{
    return fread(header, sizeof(struct bmp_header), 1, fd);
}

static struct bmp_header gen_bmp_header(uint32_t height, uint32_t width)
{
    const uint32_t padding = PADDING_COUNT - width*BMP_COLOR_COUNT % PADDING_COUNT;

    struct bmp_header header = {0};
    header.bfType = BMP_FILE_SIGNATURE;
    header.bfileSize = sizeof(struct bmp_header) + height*(width*BMP_COLOR_COUNT + padding);
    header.bOffBits = sizeof(struct bmp_header);
    header.biSize = BMP_INFOHEADER_SIZE;
    header.biWidth = width;
    header.biHeight = height;
    header.biPlanes = 1;
    header.biBitCount = BMP_BIT_COUNT;
    header.biCompression = 0;
    header.biSizeImage = height*(width*BMP_COLOR_COUNT + padding);

    return header;
}