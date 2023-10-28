#include "KS.h"
#include "get.h"
#include <fstream>
#include <iostream>

using namespace std;

int KS::Nextid = 2;

KS::KS()
{
	this->id = Nextid++;
}