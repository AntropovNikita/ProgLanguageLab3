#ifndef UTIL_H
#define UTIL_H

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
    READ_INVALID_SIGNATURE,  /**< Неизвестная сигнатура */
    READ_INVALID_BITS,       /**< Неизвестные биты */
    READ_INVALID_HEADER,     /**< Неверный заголовок */
    READ_INVALID_VERSION,    /**< Неверная версия */
    READ_UNEXPECTED_EOF,     /**< Неожиданный конец файла */
    READ_FILE_ERROR          /**< Ошибка чтения файла */
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
    OPEN_WRITE_ERROR /**< Ошибка отркытия файла для записи */
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

/**@}*/

#endif //!UTIL_H