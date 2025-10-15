#include "box.h"

string Box::getName()
{
    return this->name;
}

void Box::setName(string p_name)
{
    this->name = p_name;
}

void Box::sayHi(){
    cout << "Hi from " << name << endl;
}