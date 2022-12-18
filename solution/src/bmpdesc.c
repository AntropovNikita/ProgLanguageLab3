#include "bmpdesc.h"

enum read_status from_bmp( FILE* in, struct image* img )
{
    return READ_OK;
}

enum write_status to_bmp( FILE* out, struct image const* img )
{
    return WRITE_OK;
}