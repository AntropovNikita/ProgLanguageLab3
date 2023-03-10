#ifndef UTIL_H
#define UTIL_H

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>


/**
 * @defgroup UTIL Дополнительные функции
*/
/**@{*/

/**
 * Перечисление для кодов ошибок чтения из файла
*/
enum read_status  
{
    READ_OK = 0,             /**< Нет ошибки */
    READ_INVALID_SIGNATURE,  /**< Неизвестная сигнатура файла*/
    READ_INVALID_BITS,       /**< Неверная глубина цвета файла*/
    READ_INVALID_HEADER,     /**< Неверный заголовок файла*/
    READ_INVALID_VERSION,    /**< Неверная версия заголовка*/
    READ_UNEXPECTED_EOF,     /**< Неожиданный конец файла */
    READ_FILE_ERROR,         /**< Ошибка чтения файла */
    READ_FILE_TOO_BIG        /**< Ошибка нехватки памяти */
    /* коды других ошибок  */
};
    
/**
 * Перечисление для кодов ошибок записи в файл
*/
enum  write_status  
{
    WRITE_OK = 0, /**< Нет ошибки */
    WRITE_ERROR   /**< Ошибка записи в файл */
    /* коды других ошибок  */
};

/**
 * Перечисление для кодов ошибок открытия файла
*/
enum  open_status  
{
    OPEN_OK = 0,     /**< Нет ошибки */
    OPEN_READ_ERROR, /**< Ошибка открытия файла для чтения */
    OPEN_WRITE_ERROR /**< Ошибка открытия файла для записи */
    /* коды других ошибок  */
};

/**
 * Перечисление для кодов ошибок закрытия файлов
*/
enum  close_status  
{
    CLOSE_OK = 0, /**< Нет ошибки */
    CLOSE_ERROR   /**< Ошибка закрытия файла */
    /* коды других ошибок  */
};

/** 
 * Перечисление режимов открытия файлов
*/
enum file_mode
{
    FILE_READ_MODE, /**< Режим чтения */
    FILE_WRITE_MODE /**< Режим записи */
};

/**
 * Перечисление для проверки наличия ошибки
*/
enum check_status
{
    ERROR_STATUS,   /**< Ошибка есть */
    NO_ERROR_STATUS /**< Ошибки нет */
};

/**
 * @brief Открытие файла в заданном режиме
 * @param[in] path Путь до файла
 * @param[out] fd Указатель на дескриптор файла
 * @param[in] mode Режим открытия файла
 * @return Код ошибки открытия файла
*/
enum open_status open_file(const char* path, FILE** fd, enum file_mode mode);

/**
 * @brief Закрытия файла
 * @param[in] fd Указатель на дескриптор файла
 * @return Код ошибки закрытия файла
*/
enum close_status close_file(FILE** fd);

/**
 * @brief Проверка статуса открытия файла
 * @param[in] status Статус открытия файла
 * @return Перечисление с индикатром наличия/отсутствия ошибки
*/
enum check_status check_open_status(enum open_status status);

/**
 * @brief Проверка статуса закрытия файла
 * @param[in] status Статус закрытия файла
 * @return Перечисление с индикатром наличия/отсутствия ошибки
*/
enum check_status check_close_status(enum close_status status);

/**
 * @brief Проверка статуса записи файла
 * @param[in] status Статус записи в файл
 * @return Перечисление с индикатром наличия/отсутствия ошибки
*/
enum check_status check_write_status(enum write_status status);

/**
 * @brief Проверка статуса чтения файла
 * @param[in] status Статус чтения файла
 * @return Перечисление с индикатром наличия/отсутствия ошибки
*/
enum check_status check_read_status(enum read_status status);

/**@}*/

#endif //!UTIL_H
