#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include "functions.h"

#define INFO(X) cout << "[INFO] ("<<__FUNCTION__<<":"<<__LINE__<<") " << #X << " = " << X << endl;

using namespace std;

Pixel** createImage(int width, int height) {
  cout << "Start createImage... " << endl;
  
  // Create a one dimensional array on the heap of pointers to Pixels 
  //    that has width elements (i.e. the number of columns)
  Pixel** image = new Pixel*[width];
  
  bool fail = false;
  
  for (int i=0; i < width; ++i) { // loop through each column
    // assign that column to a one dimensional array on the heap of Pixels
    //  that has height elements (i.e. the number of rows)
    image[i] = new Pixel[height];
    
    if (image[i] == nullptr) { // failed to allocate
      fail = true;
    }
  }
  
  if (fail) { // if any allocation fails, clean up and avoid memory leak
    // deallocate any arrays created in for loop
    for (int i=0; i < width; ++i) {
      delete [] image[i]; // deleting nullptr is not a problem
    }
    delete [] image; // dlete array of pointers
    return nullptr;
  }
  
  // initialize cells
  //cout << "Initializing cells..." << endl;
  for (int row=0; row<height; ++row) {
    for (int col=0; col<width; ++col) {
      //cout << "(" << col << ", " << row << ")" << endl;
      image[col][row] = { 0, 0, 0 };
    }
  }
  cout << "End createImage... " << endl;
  return image;
}

void deleteImage(Pixel** image, int width) {
  cout << "Start deleteImage..." << endl;
  // avoid memory leak by deleting the array
  for (int i=0; i<width; ++i) {
    delete [] image[i]; // delete each individual array placed on the heap
  }
  delete [] image;
  image = nullptr;
}

int* createSeam(int length) {
    // TODO(student): create a seam
    //INFO(length);
    int *seam = new int[length];
    for(int i = 0 ; i < length ; i++){
      seam[i] = 0;
    }
  return seam;
}

void deleteSeam(int* seam) {
    // TODO(student): delete a seam
    delete[] seam;
    //INFO(seam);
}

bool loadImage(string filename, Pixel** image, int width, int height) {
    // TODO(student): load an image
    //INFO(filename);
    //INFO(image);
    //INFO(width);
    //INFO(height);
  
ifstream ifs(filename);

  // check if file opened successfully
  if (!ifs.is_open()) {
    cout << "Error: failed to open input file - " << filename;
    return false;
  }

  // get type from preamble
  char type[3];
  ifs >> type;
  if ((toupper(type[0]) != 'P') || (toupper(type[1]) != '3')) {
    cout << "Error: type is " << type[0] << type[1] << " instead of P3";
    return false;
  }

  // get width and height from preamble
  int preamWidth = 0;
  int preamHeight = 0;
  ifs >> preamWidth;
  if (ifs.fail()) {
    cout << "Error: read non-integer value";
    return false;
  }
  ifs >> preamHeight;
  if (ifs.fail()) {
    cout << "Error: read non-integer value";
    return false;
  }
  if (preamWidth != width) {
    cout << "Error: input width (" << width << 
      ") does not match value in file (" << preamWidth << ")";
    return false;
  }
  if (preamHeight != height) {
    cout << "Error: input height (" << height << 
      ") does not match value in file (" << preamHeight << ")";
    return false;
  }

  // get max color value from preamble
  int colorMax = 0;
  ifs >> colorMax;
  if (ifs.fail()) {
    cout << "Error: read non-integer value";
    return false;
  }
  if (colorMax != 255) {
    cout << "Error: file not using RGB color values ";
    return false;
  }

  // get RGB pixel values
  for (int rows = 0; rows < height; ++rows) {
    for (int cols = 0; cols < width; ++cols) {
      int colorVal = 0;

      // check red value
      // condition skips whitespace and sets eof to handle case where
      // whitespace exists before eof in valid file
      if (!(ifs >> std::ws).eof()) {
        ifs >> colorVal;
        if (ifs.fail()) {
          cout << "Error: read non-integer value";
          return false;
        }
        if (colorVal < 0 || colorVal > 255) {
          cout << "Error: invalid color value " << colorVal;
          return false;
        }
        image[cols][rows].r = colorVal;
      } else {
        cout << "Error: not enough color values";
        return false;
      }

      // check green value
      if (!(ifs >> std::ws).eof()) {
        ifs >> colorVal;
        if (ifs.fail()) {
          cout << "Error: read non-integer value";
          return false;
        }
        if (colorVal < 0 || colorVal > 255) {
          cout << "Error: invalid color value " << colorVal;
          return false;
        }
        image[cols][rows].g = colorVal;
      } else {
        cout << "Error: not enough color values";
        return false;
      }

      // check blue value
      if (!(ifs >> std::ws).eof()) {
        ifs >> colorVal;
        if (ifs.fail()) {
          cout << "Error: read non-integer value";
          return false;
        }
        if (colorVal < 0 || colorVal > 255) {
          cout << "Error: invalid color value " << colorVal;
          return false;
        }
        image[cols][rows].b = colorVal;
      } else {
        cout << "Error: not enough color values";
        return false;
      }
    }
  }

  // if eof not set, more values exist in file therefore
  // there are too many values
  if (!(ifs >> std::ws).eof()) {
    cout << "Error: too many color values";
    return false;
  }

  return true;
}

bool outputImage(string filename, Pixel** image, int width, int height) {
    // TODO(student): output an image
    //INFO(filename);
    //INFO(image);
    //INFO(width);
    //INFO(height);


    ofstream ofs;
    ofs.open(filename);
    if (!ofs.is_open()){
      cout << "Error: failed to open output file - " << filename << endl;
      return false;
    }
    ofs << "P3" << endl;
    ofs << width << " " << height << endl;
    ofs << "255" << endl;
    for(int i = 0 ; i < height ; i++){
      for(int j = 0 ; j < width ; j++){
        ofs << image[j][i].r << " ";
        ofs << image[j][i].g << " ";
        ofs << image[j][i].b << " ";
      }
      ofs << endl;
    }
  

  return true;
}

int energy(Pixel** image, int column, int row, int width, int height) { 
    // TODO(student): compute the energy of a pixel
    //INFO(image);
    //INFO(column);
    //INFO(row);
    //INFO(width);
    //INFO(height);

    int rx = 0;
    int gx = 0;
    int bx = 0;
    int ry = 0;
    int gy = 0; 
    int by = 0;

  if(column != 0 && column != width -1){
    rx = image[column+1][row].r - image[column -1][row].r;
    gx = image[column+1][row].g - image[column -1][row].g;
    bx = image[column+1][row].b - image[column -1][row].b;
  }
  else if(column == 0){
    rx = image[column+1][row].r - image[width -1][row].r;
    gx = image[column+1][row].g - image[width -1][row].g;
    bx = image[column+1][row].b - image[width -1][row].b;
  }
  else if (column == width-1){
    rx = image[column -1][row].r - image[0][row].r;
    gx = image[column -1][row].g - image[0][row].g;
    bx = image[column -1][row].b - image[0][row].b;
  }

  if (row != 0 && row != height -1){
    ry = image[column][row-1].r - image[column][row+1].r;
    gy = image[column][row-1].g - image[column][row+1].g;
    by = image[column][row-1].b - image[column][row+1].b;
  }
  else if (row == 0){
    ry = image[column][row + 1].r - image[column][height -1].r;
    gy = image[column][row + 1].g - image[column][height -1].g;
    by = image[column][row + 1].b - image[column][height -1].b;
  }
  else if (row == height -1){
    ry = image[column][row -1].r - image[column][0].r;
    gy = image[column][row -1].g - image[column][0].g;
    by = image[column][row -1].b - image[column][0].b;
  }

int energy = pow(rx,2) + pow(gx,2) + pow(bx,2) + pow(ry,2) + pow(gy,2) + pow(by,2);
  return energy;
}

int loadVerticalSeam(Pixel** image, int start_col, int width, int height, int* seam) {
    // TODO(student): load a vertical seam
    //INFO(image);
    //INFO(start_col);
    //INFO(width);
    //INFO(height);
    //INFO(seam);


  int currcol = start_col;
  seam[0] = start_col;
  int left; 
  int foward; 
  int right; 
  int totenergy = energy( image , currcol , 0 , width , height);;
  for(int i = 1 ; i < height ; i++){
    if(currcol == 0){
      left = 390151; // if the current col is at the left edge of the image set left to max value so it doesnt get picked
    }
    else{
      left = energy( image , currcol -1, i , width , height);
    }
    foward = energy(image , currcol, i , width , height);
    if (currcol == width -1){
      right = 390151;
    }
    else{
      right = energy( image , currcol +1, i , width , height);
    }
    // right is least energy value
    if (right <= left && right < foward){
      currcol += 1;
      seam[i] = currcol;
      totenergy += right;
    }
    //left is least
    else if ( left < foward && left < right){
      currcol -=1;
      seam[i] = currcol;
      totenergy += left;
    }

    //forward is least
    else{
      seam[i] = currcol;
      totenergy += foward;
    }
  }


  


  return totenergy;
}

int loadHorizontalSeam(Pixel** image, int start_row, int width, int height, int* seam) {
    // TODO(student): load a horizontal seam
    //INFO(image);
    //INFO(start_row);
    //INFO(width);
    //INFO(height);
    //INFO(seam);


  int currrow = start_row;
  seam[0] = start_row;
  int up; 
  int forward; 
  int down; 
  int totenergy = energy( image , 0 , currrow , width , height);;
  for(int i = 1 ; i < width ; i++){
    if(currrow == 0){
      up = 390151; // if the current col is at the left edge of the image set left to max value so it doesnt get picked
    }
    else{
      up = energy( image , i, currrow -1 , width , height);
    }
    forward = energy(image , i, currrow , width , height);
    if (currrow == height -1){
      down = 390151;
    }
    else{
      up = energy( image , i, currrow +1 , width , height);
    }
    // down is least energy value
    if (down < up && down < forward){
      currrow += 1;
      seam[i] = currrow;
      totenergy += down;
    }
    //foward is least
    else if (forward < up && forward <= down){
      seam[i] = currrow;
      totenergy += forward;
    }

    //up is least
    else{
      currrow -= 1;
      seam[i] = currrow;
      totenergy += up;
    }
  }





  return totenergy;
  return 0;
}

int* findMinVerticalSeam(Pixel** image, int width, int height) {
  int* minSeam = createSeam(height);
  int* tempSeam = createSeam(height);
  int minE = loadVerticalSeam(image, 0, width, height, minSeam);
  //cout << "width" <<  width << endl;
  for (int col = 1; col < width; ++col) {
    //cout << col << endl;
    int tempE = loadVerticalSeam(image, col, width, height, tempSeam);
    if (tempE < minE) {
      minE = tempE;
      for (int i = 0; i < height; ++i) {
        minSeam[i] = tempSeam[i];
      }
    }
  }
  deleteSeam(tempSeam);

  return minSeam;
}


int* findMinHorizontalSeam(Pixel** image, int width, int height) {
    // TODO(student): find min horizontal seam
    //INFO(image);
    //INFO(width);
    //INFO(height);
  int* minSeam = createSeam(width);
  int* tempSeam = createSeam(width);
  int minE = loadHorizontalSeam(image, 0, width, height, minSeam);
  for (int row = 1; row < height; ++row) {
    int tempE = loadHorizontalSeam(image, row, width, height, tempSeam);
    if (tempE < minE) {
      minE = tempE;
      for (int i = 0; i < width; ++i) {
        minSeam[i] = tempSeam[i];
      }
    }
  }

  deleteSeam(tempSeam);

  return minSeam;
  return nullptr;
}

void removeVerticalSeam(Pixel** image, int width, int height, int* verticalSeam) {
    // TODO(student): remove a vertical seam
    int x = 0 ;
    for(int i = 0 ; i < height ; i++){
      x = verticalSeam[i];
      for(int j = x ; j < width -1; j++){
        image[j][i] = image[j+1][i];
      }
    }
    width -=1;
}

void removeHorizontalSeam(Pixel** image, int width, int height, int* horizontalSeam) {
    // TODO(student): remove a horizontal seam
    //INFO(image);
    //INFO(width);
    //INFO(height);
    //INFO(horizontalSeam);
    for (int i = 0; i < width; i++) {
    int row = horizontalSeam[i];
      for (int j = row; j < height - 1; j++) {
        image[i][j] = image[i][1 + j];
      }
    }
}
