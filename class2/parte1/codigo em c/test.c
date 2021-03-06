// ************************************************************************
// AC2 – Programa 1
// ************************************************************************
#define N_INT 5
#define TRUE 1
#define FALSE 0
unsigned int sequentialSort(unsigned int, unsigned int *);
void troca(unsigned int *v1, unsigned int *v2);
void main(void)
{
 	static unsigned int lista[N_INT]; // reservado no segmento de dados
 	unsigned int i, n_trocas;
 	unsigned int *ptr;

	 printStr("\nLeitura e ordenacao de inteiros em base 10\n");
 	printStr("Introduza 5 Inteiros: "); // system call
	 for( i = 0; i < N_INT; i++ )
	 {
		 lista[i] = readInt(10); // system call
		 putChar(' '); // system call
	 }


	 n_trocas = sequentialSort( N_INT, lista );

	 printStr("\nNumero de trocas realizado: ");
	 printInt(n_trocas, 10); // system call
	 printStr("\nResultado da ordenacao: ");


	 for( ptr = lista; ptr < lista + N_INT; ptr++ )
	 {
		 printInt(*ptr, 10); // system call
		 putChar(' '); // system call
	 }
}
unsigned int sequentialSort(unsigned int n_val, unsigned int *array)
{
	unsigned int i, j, n_trocas=0;
 	for( i = 0; i < n_val - 1; i++ )
	{
		for( j = i + 1; j < n_val; j++ )
		{
			if( array[i] > array[j] )
			{
			troca(&array[i], &array[j]);
			n_trocas++;
			}
		}
	}
	 return n_trocas;
}
void troca(unsigned int *v1, unsigned int *v2)
{
	unsigned int aux;
	aux = *v1;
 	*v1 = *v2;
 	*v2 = aux;
} 
