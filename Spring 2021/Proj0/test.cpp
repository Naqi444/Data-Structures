#include <iostream>
int main(){
int **dataStructure;
int init = 10;
 int rows = 10;
 int columns = 10;
 for (int i=0;i<rows;i++){
 for (int j=0;j<columns;j++){
 dataStructure[i][j] = init;
 init = init+10;
 }
 }
 std::cout << dataStructure[2][3] << std::endl;
 return 0;
}
 
