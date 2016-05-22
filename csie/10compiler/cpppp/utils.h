#ifndef _unicode_h
#define _unicode_h
#include<cstdint>
int utf8_to_utf16(uint8_t to[], const string& from);
void HashFile(FILE *fp, const char id_hex[]);
void MakeDB(const DB& db, FILE *fp);
#endif
