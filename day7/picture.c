#include <stdio.h>
#include <stdlib.h>
#define N 15
#define M 13

void transform(int n, int m, int k, int (*buf)[k], int (*matr)[m]);
void make_picture(int n, int m, int (*picture)[m]);
void reset_picture(int n, int m, int (*picture)[m]);
void output(int m, int n,  int (*a)[m]);

void main()
{
   
   int picture[N][M];
   
   make_picture(N, M, picture);
   output(N, M, picture);
}

void make_picture(int n, int m, int (*picture)[m]) { 
   int frame_w[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
   int frame_h[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
   int tree_trunk[] = { 7, 7, 7, 7 };
   int tree_foliage[] = { 3, 3, 3, 3 };
   int sun_data[6][5] = { { 0, 6, 6, 6, 6 }, { 0, 0, 6, 6, 6 }, { 0, 0, 6, 6, 6 },
                          { 0, 6, 0, 0, 6 }, { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 } };
   reset_picture(n, m, picture);
   for (int i = 6; i < 10; i++)
      for (int j = 3; j < 5; j++) 
          picture[i][j] = tree_trunk[0];
   for (int j = 2; j < 6; j++) 
          picture[10][j] = tree_trunk[0];      
   int length_frame_w = sizeof(frame_w) / sizeof(frame_w[0]);   
   for (int i = 0; i < length_frame_w; i++)
   {
      picture[0][i] = frame_w[i];
      picture[(n-1)/2][i] = frame_w[i];
      picture[n-1][i] = frame_w[i];
   }
int length_frame_h = sizeof(frame_h) / sizeof(frame_h[0]);   
   for (int i = 0; i < length_frame_h; i++)
   {
      picture[i][0] = frame_h[i];
      picture[i][(m-1)/2] = frame_h[i];
      picture[i][m-1] = frame_h[i];
   }
   transform(n, m, 5, sun_data, picture);
   for(int i = 2; i < 6; i++)
   {
      for (int j = 2; j < 6; j++)
      {
         if (!((i==2 && (j==2 || j==5)) || (i==5 && (j==2 || j==5))))
          picture[i][j] = tree_foliage[i-2];
   }
}
}


void transform(int n, int m, int k, int (*buf)[k], int (*matr)[m] )
{  
   for(int i = 1; i < (n-1)/2; i++)
   {
      for (int j = (m+1)/2; j < m-1; j++)
      {
         matr[i][j] = buf[i-1][j-(m+1)/2];//+ i * m;
   }
}
}

void reset_picture(int n, int m, int (*picture)[m])
{
   for (int i = 0; i < n; i++)
   {
      for (int j = 0; j < m; j++)
      {
         picture[i][j] = 0;
      }  
   }
}
void output(int n, int m,  int (*a)[m]) {
     for (int p = 0; p < n-1; p++) {
        for (int q = 0; q < m-1; q++)
        printf("%d ", a[p][q]);
        printf("%d\n", a[p][m-1]);
        }    
    for (int q = 0; q < m-1; q++)
        printf("%d ", a[n-1][q]);
    printf("%d", a[n-1][m-1]);
}