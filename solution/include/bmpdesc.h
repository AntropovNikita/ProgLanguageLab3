#ifndef BMP_DESC_H
#define BMP_DESC_H

#include <stdio.h>
#include "imageop.h"
#include "util.h"

/**
 * @defgroup BMP Работа с расширением bmp
*/
/**@{*/

/**
 * @brief Чтение изображения из файла с расширением BMP 
 * @param[in] in Указатель на дескриптор файла
 * @param[out] img Указатель на структуру для представления изображения в программе
 * @return Статус чтения файла из enum read_status
*/
enum read_status from_bmp( FILE* in, struct image* img );

/**
 * @brief Запись изображения в файл с расширением BMP
 * @param[in] out Указатель на дескриптор файла
 * @param[in] img Указатель на структуру для представления изображения в программе
 * @return Статус записи файла из enum write_status
*/
enum write_status to_bmp( FILE* out, struct image const* img );

/**@}*/

#endif // !BMP_DESC_H