
#include "bloom.h"

void set_bit(bloom_filter_t *B, index_t i){
  // i = 64*a+b
  uint64_t a = i>>6;
  uint64_t b = i%64;
  B->table[a] = (B->table[a] | ((uint64_t)1<<b));
}
index_t get_bit(bloom_filter_t *B, index_t i){
  // i = 64*a+b
  uint64_t a = i>>6;
  uint64_t b = i%64;
  return (B->table[a] & ((uint64_t)1<<b))>>b;
}

index_t hash1(bloom_filter_t *B, key_t k){
  //Knuth's multiplicative method
  return (k*2654435761)%4294967296;
}

index_t hash2(bloom_filter_t *B, key_t k){
  // From http://stackoverflow.com/questions/664014/what-integer-hash-function-are-good-that-accepts-an-integer-hash-key
  uint64_t x = k;
  x = ((x >> 16) ^ x) * 0x45d9f3b;
  x = ((x >> 16) ^ x) * 0x45d9f3b;
  x = ((x >> 16) ^ x);
  return x;
}


void bloom_init(bloom_filter_t *B, index_t size_in_bits){
  B->size = size_in_bits;
  B->count = 0;
  B->table = calloc(size_in_bits/64+1, sizeof(uint64_t));
}

void bloom_destroy(bloom_filter_t *B){
  free(B);
}

int bloom_check(bloom_filter_t *B, key_t k){
  int i;
  for(i=0;i<N_HASHES;i++){
    index_t idx = (hash1(B, k) + i*hash2(B, k))%(B->size);
    if(!get_bit(B, idx))
      return 0;
  }
  return 1;
}

void bloom_add(bloom_filter_t *B, key_t k){
  int i;
  for(i=0;i<N_HASHES;i++){
    index_t idx = (hash1(B, k) + i*hash2(B, k))%(B->size);
    set_bit(B, idx);
    B->count ++;  //ignore setting 1 if already 1.
  }
}

void tradeofftest(index_t *array1, index_t *array2){
  bloom_filter_t *B = (bloom_filter_t *) malloc(sizeof(bloom_filter_t));

  bloom_init(B, 1000);
  int i;
  for(i=0;i<100;i++){
    bloom_add(B, array1[i]);
  }

  int count=0;
  for(i=0;i<1000;i++){
    if(get_bit(B, i))
      count++;
  }
  printf("tradeoff test, count of 1's: %d\n", count);

  int checkcount = 0;
  for(i=0;i<100;i++){
    if(bloom_check(B, array2[i]))
      checkcount ++;
  }

  printf("tradeoff test, array2 in filter: %d\n", checkcount);

}

int main(){
  bloom_filter_t *BF;

  // Part 1

  printf("%llu,",hash1(BF,0));
  printf("%llu,",hash1(BF,1));
  printf("%llu,",hash1(BF,2));
  printf("%llu,",hash1(BF,3));
  printf("%llu,",hash1(BF,13));
  printf("%llu\n",hash1(BF,97));

  printf("%llu,",hash2(BF,0));
  printf("%llu,",hash2(BF,1));
  printf("%llu,",hash2(BF,2));
  printf("%llu,",hash2(BF,3));
  printf("%llu,",hash2(BF,13));
  printf("%llu\n",hash2(BF,97));

  // //Smoke test
  // bloom_init(BF, 1000);
  // int i;
  // for(i=1;i<71;i++){
  //   bloom_add(BF, i);
  // }
  //
  // //Check number of 1s
  // int count=0;
  // for(i=0;i<1000;i++){
  //   if(get_bit(BF, i))
  //     count++;
  // }
  // printf("count of 1's: %d\n", count);


  //Trade off
  index_t array1[100];
  index_t array2[100];

  int j=0;
  for(j=0; j<100; j++) {
    array1[j] = rand()%1000000;
    array2[j] = rand()%1000000;
  }

  tradeofftest(array1, array2);


}
