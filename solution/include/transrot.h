#ifndef TRANS_ROT_H
#define TRANS_ROT_H

#include "imageop.h"


/**
 * @defgroup TRANSROT Вращение изображения
*/
/**@{*/

/**
 * Перечисление стороны поворота изображения
*/
enum rotate_side
{
    ROTATE_LEFT /**< Поворот против часовой стрелки */
};

/**
 * Перечисление углов поворота изображения
*/
enum rotate_grad
{
    ROTATE_GRAD_90 /**< Поворот на 90 градусов */
};

/**
 * @brief Вращение копии изображения на 90 градусов
 * @param[in] source Исходное изображение
 * @param[in] side Сторона поворота изображения
 * @param[in] grad Угол поворота изображения
 * @return Копия изображения, повернутая на заданный градус
*/
struct image rotate( struct image const source, enum rotate_side side, enum rotate_grad grad);

/**@}*/

#endif // !TRANS_ROT_H