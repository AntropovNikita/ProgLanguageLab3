#include "bmpdesc.h"
#include "transrot.h"

#include <stdio.h>

int main( int argc, char** argv ) 
{
    // Проверка кол-ва аргументов
    if (argc < 3)
    {
        fprintf(stderr, "Ошибка: мало аргументов, использование: ./image_transform <source_img> <output_img>\n");
        abort();
    }
    else if (argc > 3)
    {
        fprintf(stderr, "Ошибка: много аргументов, использование: ./image_transform <source_img> <output_img>\n");
        abort();
    }

    // Открытие файла с исходным изображением
    FILE* file = NULL;
    enum open_status open_flag = open_file(argv[1], &file, FILE_READ_MODE);
    if (check_open_status(open_flag) == ERROR_STATUS) // Ошибка открытия файла для чтения
        abort();

    // Чтение изображения
    struct image cur_img = {
        .width = 0,
        .height = 0,
        .data = NULL
    };

    enum read_status read_flag = from_bmp(file, &cur_img);
    if (check_read_status(read_flag) == ERROR_STATUS) // Ошибка чтения файла BMP
    {
        free(cur_img.data);
        close_file(&file);
        abort();
    }

    // Закрытия файла с исходным изображением
    enum close_status close_flag = close_file(&file);
    check_close_status(close_flag);

    // Вращение изображения
    struct image new_img = rotate(cur_img, ROTATE_LEFT, ROTATE_GRAD_90);
    if (new_img.data == cur_img.data) // Ошибка поворота изображения
    {
        fprintf(stderr, "Ошибка: Не удалось повернуть изображение\n");
        free(new_img.data);
        free(cur_img.data);
        abort();
    }

    // Открытия файла для итогового изображения
    open_flag = open_file(argv[2], &file, FILE_WRITE_MODE);
    if (check_open_status(open_flag) == ERROR_STATUS) // Ошибка открытия файла для записи
    {
        free(cur_img.data);
        free(new_img.data);
        abort();
    }

    // Запись в файл итогового изображения
    enum write_status write_flag = to_bmp(file, &new_img);
    if (check_write_status(write_flag) == ERROR_STATUS) // Ошибка записи в файл BMP
    {
        free(cur_img.data);
        free(new_img.data);
        close_file(&file);
        abort();
    }

    // Закрытия файла с итоговым изображением
    close_flag = close_file(&file);
    check_close_status(close_flag);

    free(cur_img.data);
    free(new_img.data);

    return 0;
}
