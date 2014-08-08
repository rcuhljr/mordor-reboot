#ifndef MDATA_TOOLS_H
#define MDATA_TOOLS_H

#include <iostream>
#include <fstream>
using namespace std;

extern const int MDATA1;
extern const int MDATA2;
extern const int MDATA3;
extern const int MDATA5;
extern const int MDATA11;

extern const char* MDATA1_NAME;
extern const char* MDATA2_NAME;
extern const char* MDATA3_NAME;
extern const char* MDATA5_NAME;
extern const char* MDATA11_NAME;

extern const int MDATA1_SIZE;  // size of MDATA1.MDR in bytes
extern const int MDATA2_SIZE;  // size of MDATA2.MDR in bytes
extern const int MDATA3_SIZE;  // size of MDATA3.MDR in bytes
extern const int MDATA5_SIZE;  // size of MDATA5.MDR in bytes
extern const int MDATA11_SIZE; // size of MDATA11.MDR in bytes

bool validPath(char* path, const char* FNAME);
bool checkLength(ifstream *mdata_input, const int SIZE);
bool possiblyValidFile(char* path, int target);

#endif
