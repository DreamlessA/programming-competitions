#include <iostream>
using namespace std;

const int MAX = 1000;

int grid[3][MAX+1];

long table[7][MAX+1];

long max4(long a, long b, long c, long d)
{
	long ans = a;
	if (b > ans)
		ans = b;
	if (c > ans)
		ans = c;
	if (d > ans)
		ans = d;
	return ans;
}

int main()
{
	int n, icase=0;

	cin >> n;
	while(n != 0) {
		icase++;
		for(int i=0; i<3; i++) {
			for(int j=1; j<=n; j++)
				cin >> grid[i][j];
		}

		for(int i=0; i<7; i++)
			table[i][0] = table[i][1] = 0;
		table[4][1] = grid[0][1]*grid[1][1];
		table[6][1] = grid[1][1]*grid[2][1];
		long prev1Max = max4(table[4][1], table[6][1], 0, 0);	// max in previous column
		long prev2Max = 0;										// max in 2 columns back
		for(int j=2; j<=n; j++) {
			long t1 = grid[0][j-1]*grid[0][j];
			long t2 = grid[1][j-1]*grid[1][j];
			long t3 = grid[2][j-1]*grid[2][j];
			long t4 = grid[0][j]*grid[1][j];
			long t5 = grid[1][j]*grid[2][j];
			table[1][j] = max4(prev2Max, table[2][j-1], table[3][j-1], table[6][j-1]) + t1;
			table[2][j] = max4(prev2Max, table[1][j-1], table[3][j-1], table[5][j-1]) + t2;
			table[3][j] = max4(prev2Max, table[1][j-1], table[2][j-1], table[4][j-1]) + t3;
			table[4][j] = max4(prev2Max+t1+t2, table[3][j-1]+t1+t2, prev1Max+t4, 0);
			table[5][j] = max4(prev2Max, table[2][j-1], 0, 0) + t1 + t3;
			table[6][j] = max4(prev2Max+t2+t3, table[1][j-1]+t2+t3, prev1Max+t5, 0);
			table[0][j] = max4(prev2Max+t1+t2+t3, table[1][j]+t5, table[3][j]+t4, 0);

			prev2Max = prev1Max;
			prev1Max = max4(table[0][j], table[1][j], table[2][j], table[3][j]);
			prev1Max = max4(prev1Max, table[4][j], table[5][j], table[6][j]);
		}
		long ans = table[0][n];
		for(int i=1; i<7; i++)
			if (table[i][n] > ans)
				ans = table[i][n];
		cout << "Case " << icase << ": " << ans << endl;

		cin >> n;
	}
}
