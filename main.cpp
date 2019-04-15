#include <iostream>
#include <stdexcept>

#include "sigSeg.h"


void handle_segv()
{
    throw SigSeg();
}

int main()
{
    init_segv(&handle_segv, false);
    
    try
    {
        std::cout << "In try." << std::endl;
        *(int*) 0 = 0;
    }
    catch (SigSeg e)
    {
        std::cerr << "Exception catched" << std::endl;
    }

    try
    {
        std::cout << "In try 2." << std::endl;
        *(int*) 0 = 0;
    }
    catch (SigSeg e)
    {
        std::cerr << "Exception catched 2" << std::endl;
    }

    std::cout << "We are living yet!" << std::endl;

    return 0;
}
