#include "util.h"

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