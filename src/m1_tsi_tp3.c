#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#include "def.h"
#include "nrio.h"
#include "nrarith.h"
#include "nralloc.h"

int main(int argc, char** argv) {
	long nrh, nrl, nch, ncl;
	byte** I;
	byte** binary;
	byte** droits;

	int theta, roMax, ro;
	int** tableRT;

	I = LoadPGM_bmatrix("route0.pgm", &nrl, &nrh, &ncl, &nch);

	binary = bmatrix(nrl, nrh, ncl, nch);
	roMax = sqrt(nrh * nrh + nch * nch);
	tableRT = imatrix(0, 179, 0, roMax);
	droits = bmatrix(0, 179, 0, roMax);

	int i, j;
	for (i = nrl; i < nrh; i++) {
		for (j = ncl; j < nch; j++) {
			if (I[i][j] >= 180)
				binary[i][j] = 255;
			else
				binary[i][j] = 0;
		}
	}

	for (theta = 0; theta < 180; theta++) {
		for (ro = 0; ro < roMax; ro++) {
			tableRT[theta][ro] = 0;
		}
	}

	for (theta = 0; theta < 180; theta++) {
		for (i = nrl; i < nrh; i++) {
			for (j = ncl; j < nch; j++) {
				if (I[i][j] >= 180) {
					ro = i * cos(rad(theta)) + j * sin(rad(theta));
					tableRT[theta][abs(ro)]++;
				}

			}
		}
	}
	int max = 0;
	for (theta = 0; theta < 180; theta++) {
		for (ro = 0; ro < roMax; ro++) {
			if (tableRT[theta][ro] > max) {
				max = tableRT[theta][ro];
			}
		}
	}

	SavePGM_bmatrix(binary, nrl, nrh, ncl, nch, "route_binary.pgm");

	free_bmatrix(I, nrl, nrh, ncl, nch);
	free_bmatrix(binary, nrl, nrh, ncl, nch);
	return 0;
}
