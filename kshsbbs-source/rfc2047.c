#include "rfc2047.h"

/* for RFC 2047 */
#define MH_ASCII_PRINTABLE(c) ((c) > '\x1f' && (c) < '\x7f')

/* QP encode */
unsigned char *mh_qp_encode(unsigned char *dst, const int dst_len, unsigned char *src, unsigned char *charset)
{
  static unsigned char symbols[] = "0123456789ABCDEF";
  int i, j;
  
  for(i = j = 0;
      j < dst_len - 1 &&
      src[i] &&
      src[i] != '=' && src[i] != '?' && src[i] != '_' &&
      MH_ASCII_PRINTABLE(src[i]);
      dst[j ++] = src[i ++])
    ;
  dst[j] = '\0';
  if(!src[i])
    return dst;
  strlcat(dst, "=?", dst_len);
  strlcat(dst, charset, dst_len);
  strlcat(dst, "?Q?", dst_len);
  j = strlen(dst);
  for(;
      j < dst_len - 1 &&
      src[i];
      i++)
  {
    if(src[i] == '=' || src[i] == '?' || src[i] == '_' ||
       !MH_ASCII_PRINTABLE(src[i]))
    {
      if(j + 3 >= dst_len - 1)
        break;
      dst[j ++] = '=';
      dst[j ++] = symbols[src[i] >> 4];
      dst[j ++] = symbols[src[i] & 0x0f];
    }
    else if(src[i] == ' ')
      dst[j ++] = '_';
    else
      dst[j ++] = src[i];
  }
  dst[j] = '\0';
  strlcat(dst, "?=", dst_len);
  
  return dst;
}
