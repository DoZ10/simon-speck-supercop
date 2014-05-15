#include "api.h"
#include "randombytes.h"
#include "gls254.h"
#include "tables.h"

#include "curves.incl"
#include "low.incl"
#include "ec.incl"
#include "scmul.incl"

int crypto_dh_gls254_prot_keypair(unsigned char *pk, unsigned char *sk) {
	Curve curve;
	curves_domParam(&curve, GLS254);
	
	//EBATS GENERATOR
	randombytes(sk, 32);
	sk[31] = sk[31] & 0x1F;

	//generate public-key
	scmul_rand_wreg((ui64*) &pk[0], (ui64*) &pk[32], curve.Gx, curve.Gy, (ui64*) sk, 5, &curve);

	return 0;
}

int crypto_dh_gls254_prot(unsigned char *out, const unsigned char *pk, const unsigned char *sk) {
	Curve curve;
	curves_domParam(&curve, GLS254);
	elt254 tmp;
	
	scmul_rand_wreg((ui64*) out, tmp, (ui64*) &pk[0], (ui64*) &pk[32], (ui64*) sk, 5, &curve);

	return 0;
}
