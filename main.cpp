#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

#define KEY_LEN 2048 // dlinna klyuchya
bool key[KEY_LEN]; //nevidomiy klyuch

#define POP_SIZE 20 // rozmir polulyaciyi
#define ELITE 5 // rozmir eliti
struct gen_struct { // structura person
 bool gen[KEY_LEN];
 int fitness;
 gen_struct(){ //randomizaciya parametrov
  for(int i=0;i<KEY_LEN;++i)
   gen[i]=(rand()%2==0);
 }
 bool operator<(const gen_struct & g)const{
  return (g.fitness>fitness);
 }
 gen_struct(const gen_struct& g){
  for(int i=0;i<KEY_LEN;++i) gen[i]=g.gen[i];
  fitness=g.fitness;
 }
 void Mutate(){ //Mutaciya
  gen[rand()%KEY_LEN]=rand()%2;
 }
 void Crossingover(gen_struct & g){ //Zreshuvannya
  for(int i=0;i<KEY_LEN;++i){
   if(rand()%2){
    gen[i]=g.gen[i];
   }
  }
 }
};

int Fitness(bool gen[]){ //HP
 int ret=0;
 for(int i=0;i<KEY_LEN;i++){
  ret+=(key[i]!=gen[i]);
 }
 return ret;
}


void GA(gen_struct &ret){
 vector<gen_struct> pop;
 pop.resize(POP_SIZE);
 while(1){
  for(int i=0;i<POP_SIZE;++i)
   if((pop[i].fitness=Fitness(pop[i].gen))==0){
      ret=pop[i];
      return;
     }
  sort(pop.begin(), pop.end());
  for(int i=ELITE;i<POP_SIZE;++i){// Elita bez zmin
   pop[i].Crossingover(pop[rand()%(ELITE)]);
   pop[i].Mutate();
  }
 }
}


int main()
{
  for(int i=0;i<KEY_LEN;i++){
    key[i]=(rand()%2==0);
  }
  gen_struct ret;
  GA(ret);
  cout << "key="<<endl;
  for(int i=0;i<KEY_LEN; i++){
    cout << ret.gen[i];
  }
  cout << endl;
}
