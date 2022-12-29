#include "transrot.h"


/**
 * @brief Поворот изображения против часовой стрелки на заданный угол
 * @param[in] source Исходное изображение
 * @param[in] grad Угол поворота изображения
 * @return Копия изображения, повернутая на заданный угол
*/
static struct image rotate_left(struct image const source, enum rotate_grad grad);

/**
 * @brief Поворот изображения против часовой стрелки на 90 градусов
 * @param[in] source Исходное изображение
 * @return Копия изображения, повернутая на заданный угол
*/
static struct image rotate_left_90(struct image const source);

struct image rotate( struct image const source, enum rotate_side side, enum rotate_grad grad)
{
    switch (side)
    {
        case ROTATE_LEFT:
            return rotate_left(source, grad);
        default:
            return source;
    }
}

static struct image rotate_left(struct image const source, enum rotate_grad grad)
{
    switch (grad)
    {
        case ROTATE_GRAD_90:
            return rotate_left_90(source);
        default:
            return source;
    }
}

static struct image rotate_left_90(struct image const source)
{
    struct image rot_img = {
        .height = source.width,
        .width = source.height,
        .data = NULL
    };

    rot_img.data = (struct pixel*) malloc(rot_img.width*rot_img.height*sizeof(struct pixel));
    if (rot_img.data == NULL) // Если не удалось выделить память возвращаем исходное изображение
        return source;

    for(uint32_t i=0; i < rot_img.height; i++)
        for(uint32_t j=0; j < rot_img.width; j++)
            rot_img.data[i * rot_img.width + j] = source.data[(rot_img.width - j - 1)*rot_img.height + i];

    return rot_img;
}
