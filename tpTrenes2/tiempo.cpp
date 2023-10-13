#include "tiempo.h"

tiempo::tiempo()
{

}

tiempo::tiempo(int segundos)
{
    this->seg=segundos;
    this->tiempo_inicial=segundos;
}

void tiempo::decrementar()
{
    this->seg-=1;
}

int tiempo::get_seg()
{
    return this->seg;
}

void tiempo::reiniciar()
{
    this->seg=this->tiempo_inicial;
}
