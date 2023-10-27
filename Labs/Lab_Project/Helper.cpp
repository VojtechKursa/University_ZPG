#include "Helper.h"

#include <stdlib.h>



int Helper::random(int min, int max)
{
    return (rand() % (max - min) + min);
}