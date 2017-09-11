#include <iostream>
#include <stdlib.h>
#include <typeinfo>


class A{
};



void convert_16_to_8_step(int src, int *dst, int *cache, int cache_len){
  int temp = (src<<cache_len) | *cache;
  *dst = 7 & temp;
  *cache = 7 & (temp>>3);
}

int convert_x_to_d(char x){
  if('0'<=x && x<='9'){ return x-'0'; }
  if('a'<=x && x<='f'){ return x-'a'+10; }
  if('A'<=x && x<='F'){ return x-'A'+10; }
  return -1;
}

void convert_16_to_8(const char *src, size_t src_len, char *dst){
  size_t dst_back = (src_len*4)/3;
  int src_num = 0;
  int dst_num = 0;
  int cache = 0;
  int cache_len = 0;
  while(src_len --> 0){
    src_num = convert_x_to_d(src[src_len]);
    convert_16_to_8_step(src_num, &dst_num, &cache, cache_len++);
    dst[dst_back--] = '0' + dst_num;
    if(cache_len >= 3){
      dst[dst_back--] = '0' + cache;
      cache = 0;
      cache_len = 0;
    }
  }
  dst[0] = '0' + cache;
}

int main(int argc, char **argv) {
  char dst[6];
  dst[5] = '\0';
  convert_16_to_8("f000", 4, dst);
  
  std::cout<<dst<<std::endl;
  
  std::cout << "Hello, world! kdevelop" << std::endl;
  
  A a;
  std::cout<<typeid(a).name()<<std::endl;
  
  return 0;
}
