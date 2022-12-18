#include <stdio.h>

#include "../include/bmpdesc.h"
#include "../include/util.h"
#include "../include/transrot.h"


int main( int argc, char** argv ) {
   
    // Проверка кол-ва аргументов
    if (argc < 2)
        err_output("Ошибка: мало аргументов, требуется 2 - PATH_TO_IMAGE и PATH_TO_NEW_IMAGE");
    else if (argc > 2)
        err_output("Ошибка: много аргументов, требуется 2 - PATH_TO_IMAGE и PATH_TO_NEW_IMAGE");

    // Открытие файла с исходным изображением
    FILE* file = NULL;
    enum open_status open_flag = open_file(argv[1], file, FILE_READ_MODE);
    check_open_status(open_flag);

    // Чтение изображения
    struct image cur_img;
    enum read_status read_flag = from_bmp(file, &cur_img);
    check_read_status(read_flag);

    // Закрытия файла с исходным изображением
    enum close_status close_flag = close_file(file);
    check_close_status(close_flag);

    // Вращение изображения
    struct image new_img = rotate(cur_img, ROTATE_LEFT, ROTATE_GRAD_90);

    // Открытия файла для итогового изображения
    open_flag = open_file(argv[2], file, FILE_WRITE_MODE);
    check_open_status(open_flag);

    // Запись в файл итогового изображения
    enum write_status write_flag = to_bmp(file, &new_img);
    check_write_status(write_flag);

    // Закрытия файла с итоговым изображением
    close_flag = close_file(file);
    check_close_status(close_flag);

    return 0;
}
