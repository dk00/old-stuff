/************************************************************************/
/*  Author: NadOo (nadoo@21cn.com)
    Blog:
            http://nadoo.cnblogs.com
    Reference: 
            http://blog.csdn.net/lovekatherine/archive/2007/08/30/1765903.aspx
    Testing Tool: 
            http://www.hanzify.org/?Go=Show::List&ID=9627
*/
/************************************************************************/
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <malloc.h>
#include <memory.h>


int utf8_to_unicode(uint8_t *in, uint16_t **out, int *outsize)
{
    uint8_t *p = in;
    uint16_t *result = NULL;
    int resultsize = 0;
    uint8_t *tmp = NULL;

    result = (uint16_t *)malloc(strlen(in) * 2 + 2); /* should be enough */
    memset(result, 0, strlen(in) * 2 + 2);
    tmp = (uint8_t *)result;

    while(*p)
    {
        if (*p >= 0x00 && *p <= 0x7f)
        {
            *tmp = *p;
            tmp++;
            *tmp = '\0';
            resultsize += 2;
        }
        else if ((*p & (0xff << 5))== 0xc0)
        {
            uint16_t t = 0;
            uint8_t t1 = 0;
            uint8_t t2 = 0;

            t1 = *p & (0xff >> 3);
            p++;
            t2 = *p & (0xff >> 2);

            *tmp = t2 | ((t1 & (0xff >> 6)) << 6);//t1 >> 2;
            tmp++;

            *tmp = t1 >> 2;//t2 | ((t1 & (0xff >> 6)) << 6);
            tmp++;

            resultsize += 2;
        }
        else if ((*p & (0xff << 4))== 0xe0)
        {
            uint16_t t = 0;
            uint8_t t1 = 0;
            uint8_t t2 = 0;
            uint8_t t3 = 0;

            t1 = *p & (0xff >> 3);
            p++;
            t2 = *p & (0xff >> 2);
            p++;
            t3 = *p & (0xff >> 2);

            //Little Endian
            *tmp = ((t2 & (0xff >> 6)) << 6) | t3;//(t1 << 4) | (t2 >> 2);
            tmp++;

            *tmp = (t1 << 4) | (t2 >> 2);//((t2 & (0xff >> 6)) << 6) | t3;
            tmp++;
            resultsize += 2;
        }

        p++;
    }

    *tmp = '\0';
    tmp++;
    *tmp = '\0';
    resultsize += 2;

    *out = result;
    *outsize = resultsize; 
    return 0;
}


void dump_utf8(uint8_t *utf8)
{
    uint8_t *p = utf8;

    while(*p)
    {
        printf("%02X", *p);
        p++;
    }
    putchar('\n');
}

void dump_unicode(uint16_t *utf16, int size)
{
    uint8_t *p = (uint8_t *)utf16;
    int i = 0;

    
    for (i = 0; i < size; i++)
    {
        printf("%02X", *p);
        p++;
    }
    putchar('\n');
}

int main()
{
    uint8_t utf8[1000];

    int unisize = 0;
    uint16_t *uni = NULL;
    scanf("%s", utf8);
    utf8_to_unicode(utf8, &uni, &unisize);
    FILE* fw = fopen("xd.out", "w");
    fwrite(uni, sizeof(uint16_t), unisize/sizeof(uint16_t)-1, fw);
    free(uni);

    return 0;
}
