// Input:  X == two dimensional array matrix
//         n == order
// Output: X
void inv(float *X, int n)
{
	int i, j, k;
	static float a[100][200], t;

	if (n > 100) return;

    for(i = 0; i < n; i++)
		memcpy(a[i], &X[i * n], sizeof(float) * n);
   
	for(i = 0; i < n; i++)
	{
		for(j = n ; j < 2 * n ; j++)
		{
			if(i == j - n)
				a[i][j] = 1;
			else
				a[i][j] = 0;
		}
	}

	for(i = 0; i < n; i++)
	{
		t = a[i][i];
		for(j = i; j < 2 * n; j++)
			a[i][j] = a[i][j] / t;
		for(j = 0; j < n; j++)
		{
			if(i != j)
			{
				t = a[j][i];
				for(k = 0; k < 2 * n; k++)
					a[j][k] = a[j][k] - t * a[i][k];
			}
		}
	}

    for(i = 0; i < n; i++)
		memcpy(&X[i * n], &a[i][n], sizeof(float) * n);
}
