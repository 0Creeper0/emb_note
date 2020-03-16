#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	for (int a = 1; a <= 1; a++) {
		for (int b = 1; b <= 2; b++) {
			for (int c = 3; c <= 4; c++) {
				for (int d = 5; d <= 8; d++) {
					for (int e = 9; e <= 16; e++) {
						for (int f = 17; f <= 32; f++) {
							for (int g = 33; g <= 64; g++) {
								for (int h = 65; h <= 128; h++) {
									for (int i = 129; i <= 256; i++) {
										for (int j = 257; j <= 512; j++) {
											if (a+b+c+d+e+f+g+h+i+j == 1000)
												printf("%d %d %d %d %d %d %d %d %d %d\n", a, b, c, d, e, f, g, h, i, j);
										}

									}

								}

							}

						}

					}

				}

			}
		}
	}

	exit(0);
}
