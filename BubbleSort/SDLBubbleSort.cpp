#include <SDL.h>
#include <ctime>
#include <iostream>

#define Black 0x00
#define White 0xFF

// Limit loop rate for visibility
#define LIMIT_RATE 0
// Tick-rate in milliseconds (if LIMIT_RATE == 1)
#define TICK_RATE 50

// Standard Library
using namespace std;

// Width and height (in pixels) of a Dot
unsigned int UnitySize = 10;

// System dimensions (the dimension of the objects relatively to the each other)
unsigned int SystemWidth = 1280 / UnitySize;
unsigned int SystemHeight = 720 / UnitySize;

// Graphics
SDL_Window *window = NULL;
SDL_Surface *surface = NULL;
unsigned int WindowWidth = SystemWidth * UnitySize;
unsigned int WindowHeight = SystemHeight * UnitySize;

void DrawSort(unsigned int x, unsigned int y, unsigned int colour){
	
	Uint8* pixel_ptr = (Uint8*)surface->pixels + (y * UnitySize * WindowWidth + x * UnitySize) * 4;

	for (unsigned int i = 0; i < UnitySize; i++){
		for (unsigned int j = 0; j < UnitySize; j++){
			*(pixel_ptr + j * 4) = colour;		// b
			*(pixel_ptr + j * 4 + 1) = colour;	// g
			*(pixel_ptr + j * 4 + 2) = colour;	// r
		}
		pixel_ptr += WindowWidth * 4;
	}
		
}

unsigned int n = SystemWidth;

int main(int argc, char* argv[]){
	
	srand(time(NULL));
	
	// SDL boilerplate
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("BubbleSort", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WindowWidth, WindowHeight, SDL_WINDOW_SHOWN);
	surface = SDL_GetWindowSurface(window);

	int vet[n];
	
	for(int i = 0; i < n; i++){
			vet[i] = rand() % SystemHeight;
			cout << vet[i] << " ";
			if(i % 10 == 0 && i != 0)
				cout << "\n";
	}
	cout << "\n";
	
	// SDL Event handler
	SDL_Event e;
	
	cout<<"\nProcessing...\n";

	//The array elements are represented by white bars, but it hasn't much importance for the visualization 
	for(int x = 0; x < n; x++){
		for(int y = 0; y < vet[x]; y++){
			DrawSort(x, y, White);
		}
	}
					
	int i = 0, j = 0;
	
	bool quit = false;
	while (!quit){
		while (SDL_PollEvent(&e) != 0)
			if (e.type == SDL_QUIT) quit = true;
			
		SDL_UpdateWindowSurface(window);
		
		int temp;
		if(i != n){
			if(vet[i] < vet[j]){
				temp = vet[i];
				vet[i] = vet[j];
				vet[j] = temp;
			}
			for(int y = temp; y < vet[i]; y++){
				DrawSort(i, y, White);
			}			
			for(int y = vet[i]; y < SystemHeight; y++){
				DrawSort(i, y, Black);
			}
			for(int y = temp; y < vet[j]; y++){
				DrawSort(j, y, White);
			}			
			for(int y = vet[j]; y < SystemHeight; y++){
				DrawSort(j, y, Black);
			}
			j++;
			if(j == n - 1){
				i++;
				j = 0;
			}
		}
		
		#if LIMIT_RATE
			SDL_Delay(TICK_RATE);
		#endif
		
	}
	
	// Destroy window 
	SDL_DestroyWindow(window); 
		
	// Quit SDL subsystems 
	SDL_Quit();
	
//	system("cls");
	cout << "\n";
	for(int i = 0; i < n; i++){
		cout << vet[i] << " ";
		if(i % 10 == 0 && i != 0)
			cout << "\n";
	}
	cout << "\n";
	system("pause");
	
	return 0;
	
}


