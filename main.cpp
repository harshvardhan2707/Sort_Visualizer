#include <SDL2/SDL.h>
#include <iostream>
#include <random>
#include <ranges>
#include <algorithm>
class Button{
    public:
    SDL_Texture *text;
    SDL_Rect srect,drect;
    bool isSelected=false;
    
};
void draw_state(std::vector<int> &v,SDL_Renderer* renderer,int red,int blue){
    int index=0;
    for(auto i:v){
        if(index==red)SDL_SetRenderDrawColor(renderer,255,0,0,255);
        else if(index==blue)SDL_SetRenderDrawColor(renderer,0,0,255,255);
        else SDL_SetRenderDrawColor(renderer,255,255,255,255);
        SDL_RenderDrawLine(renderer,index,99,index,i);
        index++;
    }
}
void InsertionSort(std::vector<int> &v,SDL_Renderer* renderer){
    for(int i=0;i<v.size();i++){
        for(int j=i;j<v.size();j++){
            if(v[j]<v[i]){
                std::swap(v[j],v[i]);
            }
            SDL_SetRenderDrawColor(renderer,0,0,0,255);
            SDL_RenderClear(renderer);

            draw_state(v,renderer,i,j);
            SDL_RenderPresent(renderer);
            SDL_Delay(10);
        }
    }
}
void SelectionSort(std::vector<int> &v,SDL_Renderer* renderer){
    for(int i=0;i<v.size()-1;i++){
        int minIndex=i;
        for(int j=i+1;j<v.size();j++){
            if(v[j]<v[minIndex]){
                minIndex=j;
            }
            SDL_SetRenderDrawColor(renderer,0,0,0,255);
            SDL_RenderClear(renderer);

            draw_state(v,renderer,i,j);
            SDL_RenderPresent(renderer);
            SDL_Delay(10);
            }
            if(i!=minIndex)std::swap(v[minIndex],v[i]);

    }
}
int partition(std::vector<int> &array, int low, int high,SDL_Renderer* renderer) {
  int pivot = array[high];
  int i = (low - 1);
  for (int j = low; j < high; j++) {
    if (array[j] <= pivot) {
      i++;
      std::swap(array[i], array[j]);
    }
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    SDL_RenderClear(renderer);

    draw_state(array,renderer,i,j);
    SDL_RenderPresent(renderer);
    SDL_Delay(10);
  }
  std::swap(array[i + 1], array[high]);
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    SDL_RenderClear(renderer);

    draw_state(array,renderer,i+1,high);
    SDL_RenderPresent(renderer);
    SDL_Delay(10);
  return (i + 1);
}

void quickSort(std::vector<int> &array, int low, int high,SDL_Renderer* renderer) {
  if (low < high) {
    int pi = partition(array, low, high,renderer);
    quickSort(array, low, pi - 1,renderer);
    quickSort(array, pi + 1, high,renderer);
  }
}
void MergeSort(std::vector<int> &v,int s,int e,SDL_Renderer* renderer){
    if(s>=e)return;
    int mid=(s+e)/2;
    MergeSort(v,s,mid,renderer);
    MergeSort(v,mid+1,e,renderer);
    std::vector<int> F(e-s+1);
    int i=s,j=mid+1,k=0;
    while(i<=mid && j<=e){
        if(v[i]<=v[j])F[k++]=v[i++];
        else F[k++]=v[j++];
    }
    while(i<=mid)F[k++]=v[i++];
    while(j<=e)F[k++]=v[j++];
    for(auto i:F){
        v[s++]=i;
            SDL_SetRenderDrawColor(renderer,0,0,0,255);
    SDL_RenderClear(renderer);

    draw_state(v,renderer,-1,-1);
    SDL_RenderPresent(renderer);
    SDL_Delay(10);}
}
int main( int argc, char *argv[] )
{
    std::random_device rd;
    std::uniform_int_distribution d(1,99);
    std::vector<int> v;
    for(int i=0;i<100;i++){
        v.push_back(d(rd)); 
        // v.push_back(100-i); 
    }
    SDL_Window *window=nullptr;
    SDL_Renderer* renderer=nullptr; 
    SDL_CreateWindowAndRenderer(100*5,100*5,0,&window,&renderer);
    SDL_RenderSetScale(renderer,5,5);
    // InsertionSort(v,renderer);
    // SelectionSort(v,renderer);
    // MergeSort(v,0,v.size()-1,renderer);
    quickSort(v,0,v.size()-1,renderer);
    
    return 0;
}