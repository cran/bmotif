#include <Rcpp.h>
#include <math.h>       /* sqrt */

using namespace Rcpp;

//[[Rcpp::export]]
List np_m2_nw (int NZ, int NP, NumericMatrix W) {
	NumericVector v3(NP);
	NumericVector v4(NZ);
	for (int x = 0; x < NZ; x++) {
		for (int p = 0; p < NP; p++) {
			for (int q = 0; q < NP; q++) {
				if ((W(x,p) * W(x,q) != 0) && (p != q)) {
					v4[x] += 0.5 * (W(x,p) + W(x,q));
					v3[p] += W(x,p);
				}
			}
		}
	}
	v4 = 0.5 * v4;
	List L = List::create(v3, v4);
	return L;
}

//[[Rcpp::export]]
List np_m3_nw (int NZ, int NP, NumericMatrix W) {
	NumericVector v5(NP);
	NumericVector v6(NZ);
	for (int p = 0; p < NP; p++) {
		for (int w = 0; w < NZ; w++) {
			for (int x = 0; x < NZ; x++) {
				if ((W(w,p) * W(x,p) != 0) && (w != x)) {
					v5[p] += 0.5 * (W(w,p) + W(x,p));
					v6[w] += W(w,p);
				}
			}
		}
	}
	v5 = 0.5 * v5;
	List L = List::create(v5, v6);
	return L;
}

//[[Rcpp::export]]
List np_m4_nw (int NZ, int NP, NumericMatrix W) {
	NumericVector v7(NP);
	NumericVector v8(NZ);
	for (int p = 0; p < NP; p++) {
		for (int w = 0; w < NZ; w++) {
			for (int x = 0; x < NZ; x++) {
				if (w == x) {
					continue;
				}
				for (int y = 0; y < NZ; y++) {
					if ((W(w,p) * W(x,p) * W(y,p) != 0) && (w != y) && (x != y)) {
						v7[p] += (W(w,p) + W(x,p) + W(y,p)) / 3.0;
						v8[w] += W(w,p);
					}
				}
			}
		}
	}
	v7 = v7 / 6.0;
	v8 = 0.5 * v8;
	List L = List::create(v7, v8);
	return L;
}

//[[Rcpp::export]]
List np_m5_nw (int NZ, int NP, NumericMatrix W) {
	NumericVector v12(NZ); //this is automatically filled with zeros
	NumericVector v11(NZ);
	NumericVector v9(NP);
	NumericVector v10(NP);
	for (int p = 0; p < NP; p++) {
		for (int q = 0; q < NP; q++) {
			if (p == q) {
				continue;
			}
			for (int x = 0; x < NZ; x++) {
				for (int y = 0; y < NZ; y++) {
					if ((W(x,p) * W(x,q) * W(y,q) != 0) && (W(y,p) == 0) && (x!=y)) {
						//v12[x] += (W(x,p) + W(x,q)) / (W(x,p) + W(x,q) + W(y,q));
						//v11[y] += W(y,q) / (W(x,p) + W(x,q) + W(y,q));
						//v10[q] += (W(x,q) + W(y,q)) / (W(x,p) + W(x,q) + W(y,q));
						//v9[p] += W(x,p) / (W(x,p) + W(x,q) + W(y,q));
						v12[x] += 0.5 * (W(x,p) + W(x,q));
						v11[y] += W(y,q);
						v10[q] += 0.5 * (W(x,q) + W(y,q));
						v9[p] += W(x,p);
					}
				}
			}
		}
	}
	// now want to return a list with all vectors 
	List L = List::create(v9, v10, v11, v12);
	return L;
}

//[[Rcpp::export]]
List np_m6_nw (int NZ, int NP, NumericMatrix W) {
	NumericVector v13(NP);
	NumericVector v14(NZ);
	for (int p = 0; p < NP; p++) {
		for (int q = 0; q < NP; q++) {
			if (p == q) {
				continue;
			}
			for (int x = 0; x < NZ; x++) {
				for (int y = 0; y < NZ; y++) {
					if ((W(x,p) * W(x,q) * W(y,p) * W(y,q) != 0) && (x != y)) {
						v14[x] += 0.5 * (W(x,p) + W(x,q));
						v13[p] += 0.5 * (W(x,p) + W(y,p));
					}
				}
			}
		}
	}
	v13 = 0.5 * v13;
	v14 = 0.5 * v14;
	List L = List::create(v13, v14);
	return L;
}

//[[Rcpp::export]]
List np_m7_nw (int NZ, int NP, NumericMatrix W) {
	NumericVector v15(NP);
	NumericVector v16(NZ);
	for (int x = 0; x < NZ; x++) {
		for (int p = 0; p < NP; p++) {
			for (int q = 0; q < NP; q++) {
				if (p == q) {
					continue;
				}
				for (int r = 0; r < NP; r++) {
					if ((W(x,p) * W(x,q) * W(x,r) != 0) && (p != r) && (q != r)) {
						v15[p] += W(x,p);
						v16[x] += (W(x,p) + W(x,q) + W(x,r)) / 3.0;
					}
				}
			}
		}
	}
	v16 = v16 / 6.0;
	v15 = 0.5 * v15;
	List L = List::create(v15, v16);
	return L;
}

//[[Rcpp::export]]
List np_m8_nw (int NZ, int NP, NumericMatrix W) {
	NumericVector v17(NP);
	NumericVector v18(NZ);
	for (int p = 0; p < NP; p++) {
		for (int w = 0; w < NZ; w++) {
			for (int x = 0; x < NZ; x++) {
				if (w == x) {
					continue;
				}
				for (int y = 0; y < NZ; y++) {
					if (w == y || x == y) {
						continue;
					}
					for (int z = 0; z < NZ; z++) {
						if ((W(w,p) * W(x,p) * W(y,p) * W(z,p) != 0) && (w != z) && (y != z) && (x != z)) {
							v17[p] += (W(w,p) + W(x,p) + W(y,p) + W(z,p)) / 4.0;
							v18[x] += W(x,p);
						}
					}
				}
			}
		}
	}
	v17 = v17 / 24.0;
	v18 = v18 / 6.0;
	List L = List::create(v17, v18);
	return L;
}

//[[Rcpp::export]]
List np_m9_nw (int NZ, int NP, NumericMatrix W) {
	NumericVector v19(NP);
	NumericVector v20(NP);
	NumericVector v21(NZ);
	NumericVector v22(NZ);
	for (int p = 0; p < NP; p++) {
		for (int q = 0; q < NP; q++) {
				if (p == q) {
					continue;
				}
			for (int x = 0; x < NZ; x++) {
				for (int y = 0; y < NZ; y++) {
					if (x == y) {
						continue;
					}
					for (int z = 0; z < NZ; z++) {
						if ((W(x,p) * W(y,p) * W(z,p) * W(z,q) != 0 && W(x,q) == 0) && (W(y,q) == 0) && (x != z) && (y != z)) {
							v20[p] += (W(x,p) + W(y,p) + W(z,p)) / 3.0;
							v19[q] += W(z,q);
							v21[x] += W(x,p);
							v22[z] += 0.5 * (W(z,p) + W(z,q));
						}
					}
				}
			}
		}
	}
	v19 = 0.5 * v19;
	v20 = 0.5 * v20;
	v22 = 0.5 * v22;
	List L = List::create(v19, v20, v21, v22);
	return L;
}

//[[Rcpp::export]]
List np_m10_nw (int NZ, int NP, NumericMatrix W) {
	NumericVector v23(NP);
	NumericVector v24(NZ);
	NumericVector v25(NZ);
	for (int p = 0; p < NP; p++) {
		for (int q = 0; q < NP; q++) {
				if (p == q) {
					continue;
				}
			for (int x = 0; x < NZ; x++) {
				for (int y = 0; y < NZ; y++) {
					if (x == y) {
						continue;
					}
					for (int z = 0; z < NZ; z++) {
						if ((W(x,p) * W(y,p) * W(y,q) * W(z,q) != 0) && (W(x,q) == 0) && (W(z,p) == 0) && (x != z) && (y != z)) {
							v23[p] += 0.5 * (W(x,p) + W(y,p));
							v24[x] += W(x,p);
							v25[y] += 0.5 * (W(y,p) + W(y,q));
						}
					}
				}
			}
		}
	}
	v25 = 0.5 * v25;	
	List L = List::create(v23, v24, v25);
	return L;
}

//[[Rcpp::export]]
List np_m11_nw (int NZ, int NP, NumericMatrix W) {
	NumericVector v26(NP);
	NumericVector v27(NP);
	NumericVector v28(NZ);
	NumericVector v29(NZ);
	for (int p = 0; p < NP; p++) {
		for (int q = 0; q < NP; q++) {
				if (p == q) {
					continue;
				}
			for (int x = 0; x < NZ; x++) {
				for (int y = 0; y < NZ; y++) {
					if (x == y) {
						continue;
					}
					for (int z = 0; z < NZ; z++) {
						if ((W(x,p) * W(y,p) * W(y,q) * W(z,p) * W(z,q) != 0) && (W(x,q) == 0) && (x != z) && (y != z)) {
							v28[x] += W(x,p);
							v29[y] += 0.5 * (W(y,p) + W(y,q));
							v27[p] += (W(x,p) + W(y,p) + W(z,p)) / 3.0;
							v26[q] += 0.5 * (W(y,q) + W(z,q));
						}
					}
				}
			}
		}
	}
	v26 = 0.5 * v26;
	v27 = 0.5 * v27;
	v28 = 0.5 * v28;
	List L = List::create(v26, v27, v28, v29);
	return L;
}

//[[Rcpp::export]]
List np_m12_nw (int NZ, int NP, NumericMatrix W) {
	NumericVector v30(NP);
	NumericVector v31(NZ);
	for (int p = 0; p < NP; p++) {
		for (int q = 0; q < NP; q++) {
				if (p == q) {
					continue;
				}
			for (int x = 0; x < NZ; x++) {
				for (int y = 0; y < NZ; y++) {
					if (x == y) {
						continue;
					}
					for (int z = 0; z < NZ; z++) {
						if ((W(x,p) * W(x,q) * W(y,p) * W(y,q) * W(z,p) * W(z,q) != 0) && (x != z) && (y != z)) {
							v30[p] += (W(x,p) + W(y,p) + W(z,p)) / 3.0;
							v31[x] += 0.5 * (W(x,p) + W(x,q));
						}
					}
				}
			}
		}
	}
	v31 = 0.25 * v31;
	v30 = v30 / 6.0;
	List L = List::create(v30, v31);
	return L;
}

//[[Rcpp::export]]
List np_m13_nw (int NZ, int NP, NumericMatrix W) {
	NumericVector v32(NP);
	NumericVector v33(NP);
	NumericVector v34(NZ);
	NumericVector v35(NZ);
	for (int p = 0; p < NP; p++) {
		for (int q = 0; q < NP; q++) {
				if (p == q) {
					continue;
				}
			for (int r = 0; r < NP; r++) {
				if (p == r || q == r) {
					continue;
				}				
				for (int x = 0; x < NZ; x++) {
					for (int y = 0; y < NZ; y++) {
						if ((W(x,p) * W(y,p) * W(y,q) * W(y,r) != 0) && (W(x,q) == 0) & (W(x,r) == 0) && (x != y)) {
							v34[x] += W(x,p);
							v35[y] += (W(y,p) + W(y,q) + W(y,r)) / 3.0;
							v33[p] += 0.5 * (W(x,p) + W(y,p));
							v32[q] += W(y,q);
						}
					}
				}
			}
		}
	}
	v34 = 0.5 * v34;
	v35 = 0.5 * v35;
	v33 = 0.5 * v33;
	List L = List::create(v32, v33, v34, v35);
	return L;
}

//[[Rcpp::export]]
List np_m14_nw (int NZ, int NP, NumericMatrix W) {
	NumericVector v36(NP);
	NumericVector v37(NP);
	NumericVector v38(NZ);
	for (int p = 0; p < NP; p++) {
		for (int q = 0; q < NP; q++) {
				if (p == q) {
					continue;
				}
			for (int r = 0; r < NP; r++) {
				if (p == r || q == r) {
					continue;
				}				
				for (int x = 0; x < NZ; x++) {
					for (int y = 0; y < NZ; y++) {
						if ((W(x,p) * W(x,q) * W(y,q) * W(y,r) != 0) && (W(x,r) == 0) && (W(y,p) == 0) && (x != y)) {
							v38[x] += 0.5 * (W(x,p) + W(x,q));
							v36[p] += W(x,p);
							v37[q] += 0.5 * (W(x,q) + W(y,q));
						}
					}
				}
			}
		}
	}
	v37 = 0.5 * v37;
	List L = List::create(v36, v37, v38);
	return L;
}

//[[Rcpp::export]]
List np_m15_nw (int NZ, int NP, NumericMatrix W) {
	NumericVector v39(NP);
	NumericVector v40(NP);
	NumericVector v41(NZ);
	NumericVector v42(NZ);
	for (int p = 0; p < NP; p++) {
		for (int q = 0; q < NP; q++) {
				if (p == q) {
					continue;
				}
			for (int r = 0; r < NP; r++) {
				if (p == r || q == r) {
					continue;
				}				
				for (int x = 0; x < NZ; x++) {
					for (int y = 0; y < NZ; y++) {
						if ((W(x,p) * W(x,q) * W(y,p) * W(y,q) * W(y,r) != 0) && (W(x,r) == 0) && (x != y)) {
							v39[r] += W(y,r);
							v40[p] += 0.5 * (W(x,p) + W(y,p));
							v41[x] += 0.5 * (W(x,p) + W(x,q));
							v42[y] += (W(y,p) + W(y,q) + W(y,r)) / 3.0;
						}
					}
				}
			}
		}
	}
	v39 = 0.5 * v39;
	v41 = 0.5 * v41;
	v42 = 0.5 * v42;
	List L = List::create(v39, v40, v41, v42);
	return L;
}

//[[Rcpp::export]]
List np_m16_nw (int NZ, int NP, NumericMatrix W) {
	NumericVector v43(NP);
	NumericVector v44(NZ);
	for (int p = 0; p < NP; p++) {
		for (int q = 0; q < NP; q++) {
				if (p == q) {
					continue;
				}
			for (int r = 0; r < NP; r++) {
				if (p == r || q == r) {
					continue;
				}				
				for (int x = 0; x < NZ; x++) {
					for (int y = 0; y < NZ; y++) {
						if ((W(x,p) * W(x,q) * W(x,r) * W(y,p) * W(y,q) * W(y,r) != 0) && (x != y)) {
							v43[p] += 0.5 * (W(x,p) + W(y,p));
							v44[x] += (W(x,p) + W(x,q) + W(x,r)) / 3.0;
						}
					}
				}
			}
		}
	}
	v43 = 0.25 * v43;
	v44 = v44 / 6.0;
	List L = List::create(v43, v44);
	return L;
}


//[[Rcpp::export]]
List np_m17_nw (int NZ, int NP, NumericMatrix W) {
	NumericVector v45(NP);
	NumericVector v46(NZ);
	for (int x = 0; x < NZ; x++) {
		for (int p = 0; p < NP; p++) {
			for (int q = 0; q < NP; q++) {
				if (p == q) {
					continue;
				}
				for (int r = 0; r < NP; r++) {
					if (p == r || q == r) {
						continue;
					}
					for (int s = 0; s < NP; s++) {
						if ((W(x,p) * W(x,q) * W(x,r) * W(x,s) != 0) && (p != s) && (q != s) && (r != s)) {
							v46[x] += 0.25 * (W(x,p) + W(x,q) + W(x,r) + W(x,s));
							v45[p] += W(x,p);
						}
					}
				}
			}
		}
	}
	v46 = v46 / 24.0;
	v45 = v45 / 6.0;
	List L = List::create(v45, v46);
	return L;
}
