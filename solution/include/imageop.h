#ifndef IMAGE_OP_H
#define IMAGE_OP_H

#include <stdint.h>


/**
 * @defgroup IMAGE Внутренний формат изображения
*/
/**@{*/

/**
 * Струкура пикселя RGB изображения
*/
struct __attribute__((packed)) pixel
{
    uint8_t b; /**< Синий канал */
    uint8_t g; /**< Зеленый канал */
    uint8_t r; /**< Красный канал */
};

/**
 * Структура изображения
*/
struct image
{
    uint32_t width;     /**< Ширина изображения */
    uint32_t height;    /**< Высота изображения */
    struct pixel* data; /**< Массив пикселей */
};

/**@}*/

#endif // !IMAGE_OP_H
