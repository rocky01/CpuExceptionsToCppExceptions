#include <iostream>
#include <stdexcept>

#include "sigSeg.h"


void handle_segv()
{
    throw SigSeg();
}

int main()
{
    init_segv(&handle_segv);
    
    try
    {
        *(int*) 0 = 0;
    }
    catch (...)
    {
        std::cerr << "Exception catched" << std::endl;
    }

    std::cout << "We are living yet!" << std::endl;

    return 0;
}
