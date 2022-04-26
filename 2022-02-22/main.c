#include "matrix.h"

int main(int argc, char* argv[])
{
	float a[3][3] = {
        { 2.0f, -1.0f,  4.0f},
        { 4.0f, -4.0f,  1.0f},
        {-3.0f,  2.0f, -5.0f}
    };

    float b[3][3] = {
        { 1.0f, -2.0f,  3.0f},
        { 5.0f, -3.0f,  2.0f},
        { 3.0f, -2.0f, -3.0f}
    };
	
	float c[3][3];

	printf("A matrix:\n");
    print_matrix(a);
	
	printf("\nB matrix:\n");
    print_matrix(b);
    
	printf("\nAdded matrix:\n");
    add_matrices(a, b, c);
    print_matrix(c);

	printf("\nIdentity matrix:\n");
	init_identity_matrix(c);
    print_matrix(c);

	printf("\nMultiply matrix:\n");
    multiply_matrices(a, b, c);
    print_matrix(c);
	
	printf("\nScalar:\n");
	mult_scalar_matrix(b, 100);
	print_matrix(b);



	return 0;
}

