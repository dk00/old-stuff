#include <stdio.h>

typedef unsigned __int64 uint64_t;

extern "C" unsigned int crc32(const char* data, size_t len);

// this function read a file into an array, and set len to its size.
char* read_file(const char* filename, size_t &len){
    FILE* fin = fopen(filename, "rb");
    if(!fin){
        fprintf(stderr, "Unable to open file %s\n", filename);
        return NULL;
    }

    // get file length
    fseek(fin, 0, SEEK_END);
    len = ftell(fin);
    rewind(fin);

    char* data = new char[len+1];
    if(data == NULL){
        fprintf(stderr, "Unable to allocate memory\n");
        return NULL;
    }
    if(fread(data, len, 1, fin) != 1){
	fprintf(stderr, "Error reading file %s\n", filename);
	delete [] data;
	return NULL;
    }
    data[len] = 0;
    fclose(fin);
    return data;
}

// this function is used for timing. It will return CPU cycles
// used during previous call.
uint64_t rdtsc(){
    static uint64_t prev_cycle = 0;
    uint64_t prev = prev_cycle;
    __asm{
        rdtsc
        mov DWORD PTR [prev_cycle], eax
        mov DWORD PTR [prev_cycle+4], edx
    }
    return prev_cycle - prev;
}

int main(int argc, char** argv){
    if(argc != 2){
        perror("Usage: crc32 FILENAME\n");
        return 1;
    }

    size_t len;
    char* data = read_file(argv[1], len);

    if(data == NULL)
        return 1;

    rdtsc();
    unsigned int sum = crc32(data, len);
    uint64_t cycles = rdtsc();
    
    printf("CRC32 checksum: %X\n", sum);
    printf("%I64u CPU cycles used.\n", cycles);
    
    delete [] data;
    return 0;
}
