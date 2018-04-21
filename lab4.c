#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int loops = 10;
const int times = 1000000;

typedef struct{
  float v[4];
} vector;

int randFloat(){
  return (float)rand()/(float)RAND_MAX * 10.0;
}

vector generateVector(){
   int i;
   vector vec;
   for(i = 0; i < 4; i++){
     vec.v[i] = randFloat();
   }
   return vec;
}
double add_simd(int number){

  int i,j;
  clock_t start;
  double timer = 0;
  start = clock();
  for(j = 0; j < number; j++){
    vector vec1 = generateVector();
    vector vec2 = generateVector();
    for(i = 0; i < loops; i++){

      __asm(
      "movups %1,%%xmm0 \n"
      "movups %2,%%xmm1 \n"
      "addps %%xmm0, %%xmm1 \n"
      "movups %%xmm0, %0"
      : "=g"(vec1)
      : "g"(vec1), "g"(vec2)
      : "%xmm0", "%xmm1"
      );
    }
  }
  timer += (times*(clock()-start)/CLOCKS_PER_SEC);
  return timer;
}
double sub_simd(int number){

  int i,j;
  clock_t start;
  double timer = 0;
  start = clock();
  for(j = 0; j < number; j++){
    vector vec1 = generateVector();
    vector vec2 = generateVector();
    for(i = 0; i < loops; i++){

      __asm(
      "movups %1,%%xmm0 \n"
      "movups %2,%%xmm1 \n"
      "subps %%xmm0, %%xmm1 \n"
      "movups %%xmm0, %0"
      : "=g"(vec1)
      : "g"(vec1), "g"(vec2)
      : "%xmm0", "%xmm1"
      );
    }
  }
  timer += (times*(clock()-start)/CLOCKS_PER_SEC);
  return timer;
}
double mul_simd(int number){

  int i,j;
  clock_t start;
  double timer = 0;
  start = clock();
  for(j = 0; j < number; j++){
    vector vec1 = generateVector();
    vector vec2 = generateVector();
    for(i = 0; i < loops; i++){

      __asm(
      "movups %1,%%xmm0 \n"
      "movups %2,%%xmm1 \n"
      "mulps %%xmm0, %%xmm1 \n"
      "movups %%xmm0, %0"
      : "=g"(vec1)
      : "g"(vec1), "g"(vec2)
      : "%xmm0", "%xmm1"
      );
    }
  }
  timer += (times*(clock()-start)/CLOCKS_PER_SEC);
  return timer;
}
double div_simd(int number){

  int i,j;
  clock_t start;
  double timer = 0;
  start = clock();
  for(j = 0; j < number; j++){
    vector vec1 = generateVector();
    vector vec2 = generateVector();
    for(i = 0; i < loops; i++){

      __asm(
      "movups %1,%%xmm0 \n"
      "movups %2,%%xmm1 \n"
      "divps %%xmm0, %%xmm1 \n"
      "movups %%xmm0, %0"
      : "=g"(vec1)
      : "g"(vec1), "g"(vec2)
      : "%xmm0", "%xmm1"
      );
    }
  }
  timer += (times*(clock()-start)/CLOCKS_PER_SEC);
  return timer;
}
double add_sisd(int number){

  int i,j,k;
  clock_t start;
  double timer = 0;
  start = clock();
  for(j = 0; j < number; j++){
    vector vec1 = generateVector();
    vector vec2 = generateVector();
    for(i = 0; i < loops; i++){
      for(k = 0; k < 4; k++){
        __asm(
        "fld %1 \n"
        "fld %2 \n"
        "faddp \n"
        "fstp %0 \n"
        : "=m"(vec1.v[k])
        : "m"(vec1.v[k]), "m"(vec2.v[k])
        );
      }
    }
  }
  timer += (times*(clock()-start)/CLOCKS_PER_SEC);
  return timer;
}
double sub_sisd(int number){

  int i,j,k;
  clock_t start;
  double timer = 0;
  start = clock();
  for(j = 0; j < number; j++){
    vector vec1 = generateVector();
    vector vec2 = generateVector();
    for(i = 0; i < loops; i++){
      for(k = 0; k < 4; k++){
        __asm(
        "fld %1 \n"
        "fld %2 \n"
        "fsubp \n"
        "fstp %0 \n"
        : "=m"(vec1.v[k])
        : "m"(vec1.v[k]), "m"(vec2.v[k])
        );
      }
    }
  }
  timer += (times*(clock()-start)/CLOCKS_PER_SEC);
  return timer;
}
double mul_sisd(int number){

  int i,j,k;
  clock_t start;
  double timer = 0;
  start = clock();
  for(j = 0; j < number; j++){
    vector vec1 = generateVector();
    vector vec2 = generateVector();
    for(i = 0; i < loops; i++){
      for(k = 0; k < 4; k++){
        __asm(
        "fld %1 \n"
        "fld %2 \n"
        "fmulp \n"
        "fstp %0 \n"
        : "=m"(vec1.v[k])
        : "m"(vec1.v[k]), "m"(vec2.v[k])
        );
      }
    }
  }
  timer += (times*(clock()-start)/CLOCKS_PER_SEC);
  return timer;
}
double div_sisd(int number){

  int i,j,k;
  clock_t start;
  double timer = 0;
  start = clock();
  for(j = 0; j < number; j++){
    vector vec1 = generateVector();
    vector vec2 = generateVector();
    for(i = 0; i < loops; i++){
      for(k = 0; k < 4; k++){
        __asm(
        "fld %1 \n"
        "fld %2 \n"
        "fdivp \n"
        "fstp %0 \n"
        : "=m"(vec1.v[k])
        : "m"(vec1.v[k]), "m"(vec2.v[k])
        );
      }
    }
  }
  timer += (times*(clock()-start)/CLOCKS_PER_SEC);
  return timer;
}
void saveResults(){

  int num1 = 2048;
  int num2 = 4096;
  int num3 = 8192;

  FILE *f = fopen("results.txt", "w");
  if( f == NULL){
    printf("Error opening file!\n");
    return;
  }
  fprintf(f,"Typ obliczen : SIMD\n");
  fprintf(f,"Ilosc liczb : %d \n", num1);
  fprintf(f,"Sredni czas[s] :\n");
  fprintf(f,"+ %lf\n", add_simd(num1)/times);
  fprintf(f,"- %lf\n", sub_simd(num1)/times);
  fprintf(f,"* %lf\n", mul_simd(num1)/times);
  fprintf(f,"/ %lf\n", div_simd(num1)/times);

  fprintf(f,"Typ obliczen : SISD\n");
  fprintf(f,"Ilosc liczb : %d \n", num1);
  fprintf(f,"Sredni czas[s] :\n");
  fprintf(f,"+ %lf\n", add_sisd(num1)/times);
  fprintf(f,"- %lf\n", sub_sisd(num1)/times);
  fprintf(f,"* %lf\n", mul_sisd(num1)/times);
  fprintf(f,"/ %lf\n", div_sisd(num1)/times);

  fprintf(f,"Typ obliczen : SIMD\n");
  fprintf(f,"Ilosc liczb : %d \n", num2);
  fprintf(f,"Sredni czas[s] :\n");
  fprintf(f,"+ %lf\n", add_simd(num2)/times);
  fprintf(f,"- %lf\n", sub_simd(num2)/times);
  fprintf(f,"* %lf\n", mul_simd(num2)/times);
  fprintf(f,"/ %lf\n", div_simd(num2)/times);

  fprintf(f,"Typ obliczen : SISD\n");
  fprintf(f,"Ilosc liczb : %d \n", num2);
  fprintf(f,"Sredni czas[s] :\n");
  fprintf(f,"+ %lf\n", add_sisd(num2)/times);
  fprintf(f,"- %lf\n", sub_sisd(num2)/times);
  fprintf(f,"* %lf\n", mul_sisd(num2)/times);
  fprintf(f,"/ %lf\n", div_sisd(num2)/times);

  fprintf(f,"Typ obliczen : SIMD\n");
  fprintf(f,"Ilosc liczb : %d \n", num3);
  fprintf(f,"Sredni czas[s] :\n");
  fprintf(f,"+ %lf\n", add_simd(num3)/times);
  fprintf(f,"- %lf\n", sub_simd(num3)/times);
  fprintf(f,"* %lf\n", mul_simd(num3)/times);
  fprintf(f,"/ %lf\n", div_simd(num3)/times);

  fprintf(f,"Typ obliczen : SISD\n");
  fprintf(f,"Ilosc liczb : %d \n", num3);
  fprintf(f,"Sredni czas[s] :\n");
  fprintf(f,"+ %lf\n", add_sisd(num3)/times);
  fprintf(f,"- %lf\n", sub_sisd(num3)/times);
  fprintf(f,"* %lf\n", mul_sisd(num3)/times);
  fprintf(f,"/ %lf\n", div_sisd(num3)/times);

  fclose(f);
}
void printResults(){

  int num1 = 2048;
  int num2 = 4096;
  int num3 = 8192;

  printf("Typ obliczen : SIMD\n");
  printf("Ilosc liczb : %d \n", num1);
  printf("Sredni czas[s] :\n");
  printf("+ %lf\n", add_simd(num1)/times);
  printf("- %lf\n", sub_simd(num1)/times);
  printf("* %lf\n", mul_simd(num1)/times);
  printf("/ %lf\n", div_simd(num1)/times);

  printf("Typ obliczen : SISD\n");
  printf("Ilosc liczb : %d \n", num1);
  printf("Sredni czas[s] :\n");
  printf("+ %lf\n", add_sisd(num1)/times);
  printf("- %lf\n", sub_sisd(num1)/times);
  printf("* %lf\n", mul_sisd(num1)/times);
  printf("/ %lf\n", div_sisd(num1)/times);

  printf("Typ obliczen : SIMD\n");
  printf("Ilosc liczb : %d \n", num2);
  printf("Sredni czas[s] :\n");
  printf("+ %lf\n", add_simd(num2)/times);
  printf("- %lf\n", sub_simd(num2)/times);
  printf("* %lf\n", mul_simd(num2)/times);
  printf("/ %lf\n", div_simd(num2)/times);

  printf("Typ obliczen : SISD\n");
  printf("Ilosc liczb : %d \n", num2);
  printf("Sredni czas[s] :\n");
  printf("+ %lf\n", add_sisd(num2)/times);
  printf("- %lf\n", sub_sisd(num2)/times);
  printf("* %lf\n", mul_sisd(num2)/times);
  printf("/ %lf\n", div_sisd(num2)/times);

  printf("Typ obliczen : SIMD\n");
  printf("Ilosc liczb : %d \n", num3);
  printf("Sredni czas[s] :\n");
  printf("+ %lf\n", add_simd(num3)/times);
  printf("- %lf\n", sub_simd(num3)/times);
  printf("* %lf\n", mul_simd(num3)/times);
  printf("/ %lf\n", div_simd(num3)/times);

  printf("Typ obliczen : SISD\n");
  printf("Ilosc liczb : %d \n", num3);
  printf("Sredni czas[s] :\n");
  printf("+ %lf\n", add_sisd(num3)/times);
  printf("- %lf\n", sub_sisd(num3)/times);
  printf("* %lf\n", mul_sisd(num3)/times);
  printf("/ %lf\n", div_sisd(num3)/times);

}
int main(){

  srand(time(NULL));
  //saveResults();
  printResults();
  return 0;
}
