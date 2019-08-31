#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include "product.h"
#include "db_parser.h"
#include "product_parser.h"
#include "util.h"
#include "mydatastore.h"
#include "datastore.h"
#include "msort.h"
#include "review.h"


unsigned long long hashfunction(std::string password)
{
	
	unsigned long long hashcode = 0;
	unsigned long long n = password.size();
	unsigned long long exponent = 1;
	for(unsigned long long  i=0; i<n;i++)
	{
		exponent = 1;
		for(unsigned long long k=0;k<n-i-1;k++)
		{
			exponent *= 128;
		}
		hashcode += exponent*(unsigned long long)password[i];
	}

	unsigned long long w1;
	unsigned long long w2;
	unsigned long long w3;
	unsigned long long w4;

	w4 = hashcode%65521;
	hashcode = hashcode/65521;

	w3 = hashcode%65521;
	hashcode = hashcode/65521;

	w2 = hashcode%65521;
	hashcode = hashcode/65521;

	w1= hashcode%65521;
	hashcode = hashcode/65521;

	
	hashcode = (unsigned int)(45912 * w1 + 35511 * w2 + 65169 * w3 + 4625 * w4) % 65521;
	return hashcode;

}



#endif
