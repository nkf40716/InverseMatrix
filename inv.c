#include <stdlib.h> 
#include <stdio.h>

// calculate the cofactor
static void GetMinor(float *src, float *dst, int row, int col, int n)
{
    int nCol=0, nRow=0;
 
    for(int i = 0; i < n; i++) 
	{
        if(i != row) 
		{
            nCol = 0;
            for(int j = 0; j < n; j++) 
			{           
                if( j != col ) 
				{
                    dst[nRow * n + nCol] = src[i * n + j];
                    nCol++;
                }
            }
            nRow++;
        }
    }
}
 
// Calculate the determinant, n >= 0
static float determinant(float *x, int n)
{
    // stop the recursion
    if(n == 1) return x[0];
 
    double d = 0; 
    float *m = (float *)malloc(sizeof(float) * (n-1) * (n-1));
 
    for(int i = 0; i < n; i++ )
    {
        // get minor of element (0,i)
        GetMinor(x, m, 0, i , n);
		//d += pow(-1.0, i) * x[i] * determinant(minor, n-1);
        d += (i % 2 == 1 ? -1.0 : 1.0) * x[i] * determinant(m, n-1);
        
    }

    free(m);
    return (float)d;
}

// Input:  X == two dimensional array matrix
//         n == order
// Output: Y
void inv(float *X, int n, float *Y)
{
    // calculate the determinant
    double d = 1.0 / determinant(X, n);
 
    float *minor = (float *)malloc(sizeof(float) * (n-1) * (n-1));
 
    for(int j = 0; j < n; j++)
    {
        for(int i = 0; i < n; i++)
        {
            // get the co-factor (matrix) of A(j,i)
            GetMinor(X, minor, j, i, n);
            Y[i * n + j] = (float)(d * determinant(minor, n-1));
            if((i+j) % 2 == 1)
                Y[i * n + j] = -Y[i * n + j];
        }
    }
    free(minor);
}

int main(void)
{
	int i;
	float a[9];
	float b[9];
	
	// initialize for 3 x 3 matrix
	for (i = 0; i < 9; i++)
		a[i] = i + 1;
	
	inv(a, 3, b);
	
	printf("Original matrix:\n");
	for (i = 0; i < 9; i++) {
		printf("%.3f ", a[i]);
		if ((i + 1) % 3 == 0) printf("\n");
	}
	printf("\n");

	printf("Output matrix:\n");
	for (i = 0; i < 9; i++) {
		printf("%.3f ", b[i]);
		if ((i + 1) % 3 == 0) printf("\n");
	}	
	printf("\n");
}
