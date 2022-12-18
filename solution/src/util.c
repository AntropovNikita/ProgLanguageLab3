#include <stdarg.h>
#include "util.h"

_Noreturn static void err(const char* msg, ...);

enum open_status open_file(const char* path, FILE* fd, enum file_mode mode)
{
    if (mode == FILE_READ_MODE) // Открытие в режиме чтения
    {
        fd = fopen(path, 'rb');
        if (fd == NULL)
            return OPEN_READ_ERROR;
    }
    else if (mode == FILE_WRITE_MODE) // Открытие в режиме записи
    {
        fd = fopen(path, 'wb');
        if (fd == NULL)
            return OPEN_WRITE_ERROR;
    }

    return OPEN_OK; 
}

enum close_status close_file(FILE* fd)
{
    if (fclose(fd) == EOF)
        return CLOSE_ERROR;
    return CLOSE_OK;
}

void check_open_status(enum open_status status)
{
    static char const* const messages[] = {
	    [OPEN_READ_ERROR] = "Не получилось открыть файл в режиме чтения",
	    [OPEN_WRITE_ERROR] = "Не получилось открыть файл в режиме записи",
	    [OPEN_OK] = "Файл упешно открыт"
    };
    
    if(status != OPEN_OK)
	    err("Ошибка: %s\n",messages[status]);

    fprintf(stdout, "Вывод: %s\n", messages[status]);
}

void check_close_status(enum close_status status)
{
    static char const* const messages[] = {
	    [CLOSE_ERROR] = "Не получилось закрыть файл",
	    [CLOSE_OK] = "Файл упешно закрыт"
    };
    
    if(status != CLOSE_OK)
	    err("Ошибка: %s\n",messages[status]);

    fprintf(stdout, "Вывод: %s\n", messages[status]);
}

void check_write_status(enum write_status status)
{
    static char const* const messages[] = {
	    [WRITE_ERROR] = "Не получилось записать данные в файл",
	    [WRITE_OK] = "Данные успешно записаны в файл"
    };
    
    if(status != WRITE_OK)
	    err("Ошибка: %s\n",messages[status]);

    fprintf(stdout, "Вывод: %s\n", messages[status]);
}

void check_read_status(enum read_status status)
{
    static char const* const messages[] = {
	    [READ_INVALID_BITS] = "Требуется глубина цвета - 24 бита",
	    [READ_INVALID_HEADER] = "Файл слишком короткий",
	    [READ_INVALID_SIGNATURE] = "Не совпадает сигнатура файла",
	    [READ_INVALID_VERSION] = "Неподдерживаемая версия файла",
	    [READ_UNEXPECTED_EOF] = "Неожиданный конец файла",
	    [READ_FILE_ERROR] = "Не получилось прочесть данные из файла",
	    [READ_OK] = "Данные успешно прочитанны из файла"
    };
    
    if(status != READ_OK)
	    err("Ошибка: %s\n",messages[status]);

    fprintf(stdout, "Вывод: %s\n", messages[status]);
}

_Noreturn static void err(const char* msg, ...)
{
      va_list args;
      va_start (args, msg);
      vfprintf(stderr, msg, args);
      va_end (args);
      exit(1);
}