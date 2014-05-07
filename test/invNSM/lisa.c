/* lisa.f -- translated by f2c (version 20030320).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include "f2c.h"

/* Common Block Declarations */

struct {
    real a[2660000]	/* was [13300][200] */;
} all_;

#define all_1 all_

struct {
    real b[13300], x[200], w[200], zz[13300];
} rest_;

#define rest_1 rest_

struct {
    integer index[200];
} other_;

#define other_1 other_

/* Table of constant values */

static integer c__3 = 3;
static integer c__1 = 1;
static integer c__13300 = 13300;
static integer c__0 = 0;
static integer c__2 = 2;
static integer c__200 = 200;
static integer c__4 = 4;




/*             PROGRAM LISA ... NONNEGATIVE LEAST SQUARES INVERSION */
/*                                    OR */
/*                              SINGULAR VALUE DECOMPOSITION INVERSE */


/* Main program */ int MAIN__(void)
{
    /* Format strings */
    static char fmt_30[] = "(1x,\002WARNING....THE PARAMETERS MDA,M,N, AND"
	    " N3\002,/,1x,\002MUST BE SET EXACTLY, NOT OVER DIMENSIONED \002)";
    static char fmt_31[] = "(1x,\002IOP=1, NONNEGATIVE LEAST SQUARES INVERS"
	    "E\002,/,1x,\002IOP=2, SINGULAR VALUE DECOMPOSITION INVERSE\002,/"
	    ",1x,\002ENTER VALUE OF IOP \002)";
    static char fmt_32[] = "(1x,\002ENTER NAME OF FILE CONTAINING ARRAY  A"
	    " \002,/,1x,\002(THE SYNTHETICS ARRAY) \002)";
    static char fmt_33[] = "(a)";
    static char fmt_34[] = "(1x,\002ENTER NAME OF FILE CONTAINING ARRAY  B"
	    " \002,/,1x,\002(THE ARRAY OF OBSERVATIONS) \002)";
    static char fmt_35[] = "(1x,\002HOW MANY OBSERVATION RECORDS ARE YOU USI"
	    "NG IN\002,/,1x,\002THE INVERSION \002)";
    static char fmt_36[] = "(1x,\002HOW MANY SUBFAULTS ARE THERE \002)";
    static char fmt_37[] = "(1x,\002HOW MANY DIFFERENT MECHANISMS (GREENS FU"
	    "NCTIONS)\002,/,1x,\002ARE THERE PER SUBFAULT \002)";
    static char fmt_38[] = "(1x,\002HOW MANY TIME WINDOWS ARE THERE\002)";
    static char fmt_39[] = "(1x,\002ENTER THE VALUE OF ISMOTH\002,/,1x,\002I"
	    "SMOTH=0...NO SMOOTHING SUBMATRICES\002,/,1x,\002ISMOTH=1...READ "
	    "IN SMOOTHING SUBMATRICES FROM JULIE DISK\002,/,1x,\002          "
	    " FILES (JULIEA.DAT AND JULIEB.DAT)\002,/,1x,\002ISMOTH=2...GENER"
	    "ATE SMOOTHING SUBMATRICES IN LISA AND APPEND\002,1x,\002        "
	    "   THEM TO THE A AND B MATRICES (AS FROM SEQUEN.F)\002)";
    static char fmt_999[] = "(1x,\002LENGTH OF THIS RECORD IS = \002,i5)";
    static char fmt_2[] = "(\002 EUCLIDEAN NORM OF THE FINAL RESIDUAL VECT"
	    "OR,\r            ((B-AX))= \002,e14.5)";
    static char fmt_3[] = "(\002 MODE= \002,i5)";
    static char fmt_4[] = "(//,\002 SOLUTION VECTOR\002)";
    static char fmt_5[] = "(1x,6e13.5)";
    static char fmt_6[] = "(//,\002 DUAL VECTOR\002)";
    static char fmt_14[] = "(1x,\002NT= \002,i5,\002 IS NOT EQUAL TO NT2="
	    " \002,i5)";

    /* System generated locals */
    integer i__1, i__2, i__3;
    olist o__1;
    cllist cl__1;

    /* Builtin functions */
    integer s_wsfe(cilist *), e_wsfe(void), s_rsle(cilist *), do_lio(integer *
	    , integer *, char *, ftnlen), e_rsle(void), s_rsfe(cilist *), 
	    do_fio(integer *, char *, ftnlen), e_rsfe(void), f_open(olist *), 
	    s_rsue(cilist *), do_uio(integer *, char *, ftnlen), e_rsue(void),
	     f_clos(cllist *);
    /* Subroutine */ int s_stop(char *, ftnlen);

    /* Local variables */
    static integer i__, j, k, l1, l2, ip, nn, jw, nt, nt2, iop;
    extern /* Subroutine */ int sva_(integer *, integer *);
    static integer mup;
    static real syn[5000];
    static integer mode, nrec;
    extern /* Subroutine */ int nnls_(real *, integer *);
    static integer nrow, mdata, nmech, nsubf;
    static real rnorm;
    static char iafile[40], ibfile[40];
    static integer iscale, ismoth;
    extern /* Subroutine */ int constr_(integer *, real *, integer *, integer 
	    *, integer *, integer *, real *);

    /* Fortran I/O blocks */
    static cilist io___1 = { 0, 6, 0, fmt_30, 0 };
    static cilist io___2 = { 0, 6, 0, fmt_31, 0 };
    static cilist io___3 = { 0, 5, 0, 0, 0 };
    static cilist io___5 = { 0, 6, 0, fmt_32, 0 };
    static cilist io___6 = { 0, 5, 0, fmt_33, 0 };
    static cilist io___8 = { 0, 6, 0, fmt_34, 0 };
    static cilist io___9 = { 0, 5, 0, fmt_33, 0 };
    static cilist io___11 = { 0, 6, 0, fmt_35, 0 };
    static cilist io___12 = { 0, 5, 0, 0, 0 };
    static cilist io___14 = { 0, 6, 0, fmt_36, 0 };
    static cilist io___15 = { 0, 5, 0, 0, 0 };
    static cilist io___17 = { 0, 6, 0, fmt_37, 0 };
    static cilist io___18 = { 0, 5, 0, 0, 0 };
    static cilist io___20 = { 0, 6, 0, fmt_38, 0 };
    static cilist io___21 = { 0, 5, 0, 0, 0 };
    static cilist io___24 = { 0, 6, 0, fmt_39, 0 };
    static cilist io___25 = { 0, 5, 0, 0, 0 };
    static cilist io___28 = { 0, 7, 0, 0, 0 };
    static cilist io___30 = { 0, 8, 0, 0, 0 };
    static cilist io___32 = { 0, 6, 0, fmt_999, 0 };
    static cilist io___36 = { 0, 7, 0, 0, 0 };
    static cilist io___40 = { 0, 8, 0, 0, 0 };
    static cilist io___42 = { 0, 8, 0, 0, 0 };
    static cilist io___44 = { 0, 8, 0, 0, 0 };
    static cilist io___45 = { 0, 7, 0, 0, 0 };
    static cilist io___46 = { 0, 7, 0, 0, 0 };
    static cilist io___51 = { 0, 9, 0, fmt_2, 0 };
    static cilist io___52 = { 0, 9, 0, fmt_3, 0 };
    static cilist io___53 = { 0, 9, 0, fmt_4, 0 };
    static cilist io___54 = { 0, 9, 0, fmt_5, 0 };
    static cilist io___55 = { 0, 9, 0, fmt_6, 0 };
    static cilist io___56 = { 0, 9, 0, fmt_5, 0 };
    static cilist io___57 = { 0, 6, 0, fmt_14, 0 };



    s_wsfe(&io___1);
    e_wsfe();
    s_wsfe(&io___2);
    e_wsfe();
    s_rsle(&io___3);
    do_lio(&c__3, &c__1, (char *)&iop, (ftnlen)sizeof(integer));
    e_rsle();
    s_wsfe(&io___5);
    e_wsfe();
    s_rsfe(&io___6);
    do_fio(&c__1, iafile, (ftnlen)40);
    e_rsfe();
    o__1.oerr = 0;
    o__1.ounit = 7;
    o__1.ofnmlen = 40;
    o__1.ofnm = iafile;
    o__1.orl = 0;
    o__1.osta = "OLD";
    o__1.oacc = "SEQUENTIAL";
    o__1.ofm = "UNFORMATTED";
    o__1.oblnk = 0;
    f_open(&o__1);
    s_wsfe(&io___8);
    e_wsfe();
    s_rsfe(&io___9);
    do_fio(&c__1, ibfile, (ftnlen)40);
    e_rsfe();
    o__1.oerr = 0;
    o__1.ounit = 8;
    o__1.ofnmlen = 40;
    o__1.ofnm = ibfile;
    o__1.orl = 0;
    o__1.osta = "OLD";
    o__1.oacc = "SEQUENTIAL";
    o__1.ofm = "UNFORMATTED";
    o__1.oblnk = 0;
    f_open(&o__1);
    s_wsfe(&io___11);
    e_wsfe();
    s_rsle(&io___12);
    do_lio(&c__3, &c__1, (char *)&nrec, (ftnlen)sizeof(integer));
    e_rsle();
    s_wsfe(&io___14);
    e_wsfe();
    s_rsle(&io___15);
    do_lio(&c__3, &c__1, (char *)&nsubf, (ftnlen)sizeof(integer));
    e_rsle();
    s_wsfe(&io___17);
    e_wsfe();
    s_rsle(&io___18);
    do_lio(&c__3, &c__1, (char *)&nmech, (ftnlen)sizeof(integer));
    e_rsle();
    s_wsfe(&io___20);
    e_wsfe();
    s_rsle(&io___21);
    do_lio(&c__3, &c__1, (char *)&jw, (ftnlen)sizeof(integer));
    e_rsle();
    nn = nsubf * nmech * jw;
    s_wsfe(&io___24);
    e_wsfe();
    s_rsle(&io___25);
    do_lio(&c__3, &c__1, (char *)&ismoth, (ftnlen)sizeof(integer));
    e_rsle();
    i__1 = nrec;
    for (j = 1; j <= i__1; ++j) {
	s_rsue(&io___28);
	do_uio(&c__1, (char *)&nt, (ftnlen)sizeof(integer));
	e_rsue();
	s_rsue(&io___30);
	do_uio(&c__1, (char *)&nt2, (ftnlen)sizeof(integer));
	e_rsue();
	if (nt != nt2) {
	    goto L100;
	}
	s_wsfe(&io___32);
	do_fio(&c__1, (char *)&nt, (ftnlen)sizeof(integer));
	e_wsfe();
	if (j == 1) {
	    l2 = nt;
	}
	if (j > 1) {
	    l2 += nt;
	}
	if (j == 1) {
	    l1 = 1;
	}
	if (j > 1) {
	    l1 = l2 - nt + 1;
	}
	i__2 = nn;
	for (k = 1; k <= i__2; ++k) {
	    s_rsue(&io___36);
	    i__3 = nt;
	    for (i__ = 1; i__ <= i__3; ++i__) {
		do_uio(&c__1, (char *)&syn[i__ - 1], (ftnlen)sizeof(real));
	    }
	    e_rsue();
	    i__3 = nt;
	    for (i__ = 1; i__ <= i__3; ++i__) {
/* L444: */
		all_1.a[l1 + i__ - 1 + k * 13300 - 13301] = syn[i__ - 1];
	    }
/* L11: */
	}
	mup = l1 + nt - 1;
	s_rsue(&io___40);
	i__2 = mup;
	for (ip = l1; ip <= i__2; ++ip) {
	    do_uio(&c__1, (char *)&rest_1.b[ip - 1], (ftnlen)sizeof(real));
	}
	e_rsue();
/* L10: */
    }

/*     READ IN SMOOTHING SUBMATRICES. */

    if (ismoth == 0) {
	goto L21;
    }
    if (ismoth == 1) {
	s_rsue(&io___42);
	do_uio(&c__1, (char *)&nrow, (ftnlen)sizeof(integer));
	e_rsue();
	mup = l2 + nrow;
	s_rsue(&io___44);
	i__1 = mup;
	for (ip = l2 + 1; ip <= i__1; ++ip) {
	    do_uio(&c__1, (char *)&rest_1.b[ip - 1], (ftnlen)sizeof(real));
	}
	e_rsue();
	s_rsue(&io___45);
	do_uio(&c__1, (char *)&nrow, (ftnlen)sizeof(integer));
	e_rsue();
	i__1 = nrow;
	for (k = 1; k <= i__1; ++k) {
	    s_rsue(&io___46);
	    i__2 = nn;
	    for (i__ = 1; i__ <= i__2; ++i__) {
		do_uio(&c__1, (char *)&syn[i__ - 1], (ftnlen)sizeof(real));
	    }
	    e_rsue();
	    i__2 = nn;
	    for (i__ = 1; i__ <= i__2; ++i__) {
/* L23: */
		all_1.a[l2 + k + i__ * 13300 - 13301] = syn[i__ - 1];
	    }
/* L22: */
	}
/* L8: */
	goto L21;
    }
    if (ismoth == 2) {
	constr_(&mup, rest_1.b, &nsubf, &jw, &nrec, &nmech, syn);
    }
L21:
    cl__1.cerr = 0;
    cl__1.cunit = 7;
    cl__1.csta = 0;
    f_clos(&cl__1);
    cl__1.cerr = 0;
    cl__1.cunit = 8;
    cl__1.csta = 0;
    f_clos(&cl__1);
    o__1.oerr = 0;
    o__1.ounit = 9;
    o__1.ofnmlen = 11;
    o__1.ofnm = "LISAOUT.DAT";
    o__1.orl = 0;
    o__1.osta = "NEW";
    o__1.oacc = 0;
    o__1.ofm = 0;
    o__1.oblnk = 0;
    f_open(&o__1);
    if (iop == 2) {
	goto L12;
    }
    nnls_(&rnorm, &mode);
    goto L16;
L12:
    mdata = nrec * nt;
    iscale = 1;
    sva_(&mdata, &iscale);
    goto L17;
L16:
    s_wsfe(&io___51);
    do_fio(&c__1, (char *)&rnorm, (ftnlen)sizeof(real));
    e_wsfe();
    s_wsfe(&io___52);
    do_fio(&c__1, (char *)&mode, (ftnlen)sizeof(integer));
    e_wsfe();
    s_wsfe(&io___53);
    e_wsfe();
    s_wsfe(&io___54);
    for (i__ = 1; i__ <= 200; ++i__) {
	do_fio(&c__1, (char *)&rest_1.x[i__ - 1], (ftnlen)sizeof(real));
    }
    e_wsfe();
    s_wsfe(&io___55);
    e_wsfe();
    s_wsfe(&io___56);
    for (i__ = 1; i__ <= 200; ++i__) {
	do_fio(&c__1, (char *)&rest_1.w[i__ - 1], (ftnlen)sizeof(real));
    }
    e_wsfe();
L17:
    cl__1.cerr = 0;
    cl__1.cunit = 9;
    cl__1.csta = 0;
    f_clos(&cl__1);
    goto L50;
L100:
    s_wsfe(&io___57);
    do_fio(&c__1, (char *)&nt, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&nt2, (ftnlen)sizeof(integer));
    e_wsfe();
/* L15: */
L50:
    s_stop("", (ftnlen)0);
    return 0;
} /* MAIN__ */

/*     SUBROUTINE NNLS  (A,MDA,M,N,B,X,RNORM,W,ZZ,INDEX,MODE) */
/*     C.L.LAWSON AND R.J.HANSON 'SOLVING LEAST SQUARES PROBLEMS', PRENTICE- */
/*     HALL. */
/*     1974. */

/*        ......  NONNEGATIVE LEAST SQUARES  ...... */

/*     GIVEN AN M BY N MATRIX, A, AND AN M-VECTOR, B, COMPUTE AN */
/*     N-VECTOR, X, WHICH SOLVES THE LEAST SQUARES PROBLEM */

/*                A * X = B  SUBJECT TO X .GE. 0 */

/*     A(),MDA,M,N  MDA IS THE FIRST DIMENSIONING PARAMETER FOR */
/*     THE ARRAY, A().  ON ENTRY A() CONTAINS THE M BY N MATRIX A.  ON */
/*     EXIT A() CONTAINS THE PRODUCT MATRIX, Q*A, WHERE Q IS AN M BY M */
/*     ORTHOGONAL MATRIX GENERATED IMPLICITLY BY THIS SUBROUTINE. */
/*     B()     ON ENTRY B() CONTAINS THE M-VECTOR, B.  ON EXIT B() */
/*             CONTAINS Q*B. */
/*     X()     ON ENTRY X() NEED NOT BE INITIALIZED.  ON EXIT X() WILL */
/*             CONTAIN THE SOLUTION VECTOR. */
/*     RNORM   ON EXIT RNORM CONTAINS THE EUCLIDEAN NORM OF THE RESIDUAL */
/*             VECTOR. */
/*     W()     AN N-ARRAY OF WORKING SPACE.  ON EXIT W() WILL CONTAIN */
/*             THE DUAL SOLUTION VECTOR.  W WILL SATISFY W(I) = 0. */
/*             FOR ALL I IN SET P AND W(I) .LE. 0. FOR ALL I IN SET Z. */
/*     ZZ()    AN M-ARRAY OF WORKING SPACE. */
/*     INDEX() AN INTEGER WORKING ARRAY OF LENGTH AT LEAST N. */
/*             ON EXIT THE CONTENTS OF THIS ARRAY DEFINE THE SETS P */
/*             AND Z AS FOLLOWS.. */

/*             INDEX(1)  THRU  INDEX(NSETP) = SET P. */
/*             INDEX(IZ1)  THUR  INDEX(IZ2) = SET Z. */
/*             IZ1 = NSETP + 1 = NPP1 */
/*             IZ2 = N */
/*     MODE    THIS IS A SUCCESS-FAILURE FLAG WITH THE FOLLOWING */
/*             MEANINGS.. */

/*             1    THE SOLUTION HAS BEEN COMPUTED SUCCESSFULLY. */
/*             2    THE DIMENSIONS OF THE PROBLEM ARE BAD. */
/*                  EITHER M .LE. 0 OR N .LE. 0. */
/*             3    ITERATION COUNT EXCEEDED.  MORE THAN 3*N ITERATIONS. */



/* Subroutine */ int nnls_(real *rnorm, integer *mode)
{
    /* Format strings */
    static char fmt_200[] = "";
    static char fmt_440[] = "(1x,\002 NNLS QUITTING ON ITERATION COUNT.\002)";
    static char fmt_320[] = "";

    /* System generated locals */
    integer i__1, i__2;
    real r__1, r__2;

    /* Builtin functions */
    double sqrt(doublereal);
    integer s_wsfe(cilist *), e_wsfe(void);

    /* Local variables */
    static integer i__, j, l;
    static real t;
    extern /* Subroutine */ int g1_(real *, real *, real *, real *, real *), 
	    g2_(real *, real *, real *, real *);
    static real cc;
    extern /* Subroutine */ int h12_(integer *, integer *, integer *, integer 
	    *, real *, integer *, real *, real *, integer *, integer *, 
	    integer *);
    static integer ii, jj, ip;
    static real sm;
    static integer iz, jz;
    static real up, ss;
    static integer iz1, iz2;
    static real one, two;
    static integer npp1;
    extern doublereal diff_(real *, real *);
    static integer iter;
    static real wmax;
    static integer next;
    static real zero, alpha, asave;
    static integer itmax, izmax, nsetp;
    static real dummy, unorm, ztest, factor;

    /* Fortran I/O blocks */
    static cilist io___83 = { 0, 6, 0, fmt_440, 0 };


    /* Assigned format variables */
    static char *next_fmt;

    zero = 0.f;
    one = 1.f;
    two = 2.f;
    factor = .01f;

    *mode = 1;
    if (TRUE_) {
	goto L10;
    }
    *mode = 2;
    return 0;
L10:
    iter = 0;
    itmax = 600;

/*                   INITIALIZE THE ARRAYS INDEX() AND X(). */

    for (i__ = 1; i__ <= 200; ++i__) {
	rest_1.x[i__ - 1] = zero;
/* L20: */
	other_1.index[i__ - 1] = i__;
    }

    iz2 = 200;
    iz1 = 1;
    nsetp = 0;
    npp1 = 1;

/*                  .....  MAIN LOOP BEGINS HERE  ..... */

L30:

/*                  QUIT IF ALL COEFFICIENTS ARE ALREADY IN THE */
/*                  SOLUTION OR IF M COLS OF A HAVE BEEN TRIANGULARIZED. */

    if (iz1 > iz2 || nsetp >= 13300) {
	goto L350;
    }

/*            COMPUTE COMPONENTS OF THE DUAL (NEGATIVE GRADIENT) VECTOR W(). */

    i__1 = iz2;
    for (iz = iz1; iz <= i__1; ++iz) {
	j = other_1.index[iz - 1];
	sm = zero;
	for (l = npp1; l <= 13300; ++l) {
/* L40: */
	    sm += all_1.a[l + j * 13300 - 13301] * rest_1.b[l - 1];
	}
/* L50: */
	rest_1.w[j - 1] = sm;
    }

/*                  FIND LARGEST POSITIVE W(J). */

L60:
    wmax = zero;
    i__1 = iz2;
    for (iz = iz1; iz <= i__1; ++iz) {
	j = other_1.index[iz - 1];
	if (rest_1.w[j - 1] <= wmax) {
	    goto L70;
	}
	wmax = rest_1.w[j - 1];
	izmax = iz;
L70:
	;
    }

/*                  IF WMAX .LE. 0. GO TO TERMINATION. */
/*                  THIS INDICATES SATISFACTION OF THE KUHN-TUCKER CONDITIONS. */

    if (wmax <= 0.f) {
	goto L350;
    } else {
	goto L80;
    }
L80:
    iz = izmax;
    j = other_1.index[iz - 1];

/*          THE SIGN OF W(J) IS OK FOR J TO BE MOVED TO SET P.  BEGIN THE */
/*          TRANSFORMATION AND CHECK NEW DIAGONAL ELEMENT TO AVOID NEAR */
/*          LINEAR DEPENDENCE. */

    asave = all_1.a[npp1 + j * 13300 - 13301];
    i__1 = npp1 + 1;
    h12_(&c__1, &npp1, &i__1, &c__13300, &all_1.a[j * 13300 - 13300], &c__1, &
	    up, &dummy, &c__1, &c__1, &c__0);
    unorm = zero;
    if (nsetp == 0) {
	goto L100;
    }
    i__1 = nsetp;
    for (l = 1; l <= i__1; ++l) {
/* L90: */
/* Computing 2nd power */
	r__1 = all_1.a[l + j * 13300 - 13301];
	unorm += r__1 * r__1;
    }
L100:
    unorm = sqrt(unorm);
    r__2 = unorm + (r__1 = all_1.a[npp1 + j * 13300 - 13301], dabs(r__1)) * 
	    factor;
    if (diff_(&r__2, &unorm) <= 0.f) {
	goto L130;
    } else {
	goto L110;
    }

/*          COL J IS SUFFICIENTLY INDEPENDENT.  COPY B INTO ZZ, UPDATE */
/*          ZZ AND SOLVE FOR ZTEST ( = PROPOSED NEW VALUE FOR X(J) ). */

L110:
    for (l = 1; l <= 13300; ++l) {
/* L120: */
	rest_1.zz[l - 1] = rest_1.b[l - 1];
    }
    i__1 = npp1 + 1;
    h12_(&c__2, &npp1, &i__1, &c__13300, &all_1.a[j * 13300 - 13300], &c__1, &
	    up, rest_1.zz, &c__1, &c__1, &c__1);
    ztest = rest_1.zz[npp1 - 1] / all_1.a[npp1 + j * 13300 - 13301];

/*                    SEE IF ZTEST IS POSITIVE. */

    if (ztest <= 0.f) {
	goto L130;
    } else {
	goto L140;
    }

/*          REJECT J AS A CANDIDATE TO BE MOVED FROM SET Z TO SET P. */
/*          RESTORE A(NPP1,J), SET W(J)=0., AND LOOP BACK TO TEST DUAL */
/*          COEFFS AGAIN. */

L130:
    all_1.a[npp1 + j * 13300 - 13301] = asave;
    rest_1.w[j - 1] = zero;
    goto L60;

/*     THE INDEX J=INDEX(IZ) HAS BEEN SELECTED TO BE MOVED FROM SET */
/*     Z TO SET P.  UPDATE B, UPDATE INDICES, APPLY HOUSEHOLDER */
/*     TRANSFORMATIONS TO COLS IN NEW SET Z, ZERO SUBDIAGONAL ELTS IN */
/*     COL J, SET W(J)=0. */

L140:
    for (l = 1; l <= 13300; ++l) {
/* L150: */
	rest_1.b[l - 1] = rest_1.zz[l - 1];
    }

    other_1.index[iz - 1] = other_1.index[iz1 - 1];
    other_1.index[iz1 - 1] = j;
    ++iz1;
    nsetp = npp1;
    ++npp1;

    if (iz1 > iz2) {
	goto L170;
    }
    i__1 = iz2;
    for (jz = iz1; jz <= i__1; ++jz) {
	jj = other_1.index[jz - 1];
/* L160: */
	h12_(&c__2, &nsetp, &npp1, &c__13300, &all_1.a[j * 13300 - 13300], &
		c__1, &up, &all_1.a[jj * 13300 - 13300], &c__1, &c__13300, &
		c__1);
    }
L170:

    if (nsetp == 13300) {
	goto L190;
    }
    for (l = npp1; l <= 13300; ++l) {
/* L180: */
	all_1.a[l + j * 13300 - 13301] = zero;
    }
L190:

    rest_1.w[j - 1] = zero;

/*                  SOLVE THE TRIANGULAR SYSTEM. STORE THE SOLUTION */
/*                  TEMPORARILY IN ZZ(). */

    next = 0;
    next_fmt = fmt_200;
    goto L400;
L200:

/*                  .....  SECONDARY LOOP BEGINS HERE  ..... */
/*                             ITERATION COUNTER */

L210:
    ++iter;
    if (iter <= itmax) {
	goto L220;
    }
    *mode = 3;
    s_wsfe(&io___83);
    e_wsfe();
    goto L350;
L220:

/*                  SEE IF ALL NEW CONSTRAINED COEFFS ARE FEASIBLE. */
/*                  IF NOT COMPUTE ALPHA. */

    alpha = two;
    i__1 = nsetp;
    for (ip = 1; ip <= i__1; ++ip) {
	l = other_1.index[ip - 1];
	if (rest_1.zz[ip - 1] <= 0.f) {
	    goto L230;
	} else {
	    goto L240;
	}

L230:
	t = -rest_1.x[l - 1] / (rest_1.zz[ip - 1] - rest_1.x[l - 1]);
	if (alpha <= t) {
	    goto L240;
	}
	alpha = t;
	jj = ip;
L240:
	;
    }

/*          IF ALL NEW CONSTRAINED COEFFS ARE FEASIBLE THEN ALPHA WILL */
/*          STILL = 2.  IF SO EXIT FROM SECONDARY LOOP TO MAIN LOOP. */

    if (alpha == two) {
	goto L330;
    }

/*          OTHERWISE USE ALPHA WHICH WILL BE BETWEEN 0. AND 1. TO */
/*          INTERPOLATE BETWEEN THE OLD X AND THE NEW ZZ. */

    i__1 = nsetp;
    for (ip = 1; ip <= i__1; ++ip) {
	l = other_1.index[ip - 1];
/* L250: */
	rest_1.x[l - 1] += alpha * (rest_1.zz[ip - 1] - rest_1.x[l - 1]);
    }

/*             MODIFY A AND B AND THE INDEX ARRAYS TO MOVE COEFFICIENT */
/*             I FROM SET P TO SET Z. */

    i__ = other_1.index[jj - 1];
L260:
    rest_1.x[i__ - 1] = zero;

    if (jj == nsetp) {
	goto L290;
    }
    ++jj;
    i__1 = nsetp;
    for (j = jj; j <= i__1; ++j) {
	ii = other_1.index[j - 1];
	other_1.index[j - 2] = ii;
	g1_(&all_1.a[j - 1 + ii * 13300 - 13301], &all_1.a[j + ii * 13300 - 
		13301], &cc, &ss, &all_1.a[j - 1 + ii * 13300 - 13301]);
	all_1.a[j + ii * 13300 - 13301] = zero;
	for (l = 1; l <= 200; ++l) {
	    if (l != ii) {
		g2_(&cc, &ss, &all_1.a[j - 1 + l * 13300 - 13301], &all_1.a[j 
			+ l * 13300 - 13301]);
	    }
/* L270: */
	}
/* L280: */
	g2_(&cc, &ss, &rest_1.b[j - 2], &rest_1.b[j - 1]);
    }
L290:
    npp1 = nsetp;
    --nsetp;
    --iz1;
    other_1.index[iz1 - 1] = i__;

/*             SEE IF THE REMAINING COEFFS IN SET P ARE FEASIBLE.  THEY */
/*             SHOULD BE BECAUSE OF THE WAY ALPHA WAS DETERMINED.  IF */
/*             ANY ARE INFEASIBLE IT IS DUE TO ROUND-OFF ERROR.  ANY */
/*             THAT ARE NONPOSITIVE WILL BE SET TO ZERO AND MOVED FROM */
/*             SET P TO SET Z. */

    i__1 = nsetp;
    for (jj = 1; jj <= i__1; ++jj) {
	i__ = other_1.index[jj - 1];
	if (rest_1.x[i__ - 1] <= 0.f) {
	    goto L260;
	} else {
	    goto L300;
	}
L300:
	;
    }

/*             COPY B() INTO ZZ().  THEN SOLVE AGAIN AND LOOP BACK. */

    for (i__ = 1; i__ <= 13300; ++i__) {
/* L310: */
	rest_1.zz[i__ - 1] = rest_1.b[i__ - 1];
    }
    next = 1;
    next_fmt = fmt_320;
    goto L400;
L320:
    goto L210;

/*             .....  END OF SECONDARY LOOP  ..... */

L330:
    i__1 = nsetp;
    for (ip = 1; ip <= i__1; ++ip) {
	i__ = other_1.index[ip - 1];
/* L340: */
	rest_1.x[i__ - 1] = rest_1.zz[ip - 1];
    }

/*             ALL NEW COEFFS ARE POSITIVE.  LOOP BACK TO BEGINNING. */

    goto L30;

/*             .....  END OF MAIN LOOP  ..... */
/*             COME TO HERE FOR TERMINATION.  COMPUTE THE NORM */
/*             OF THE FINAL RESIDUAL VECTOR. */

L350:
    sm = zero;
    if (npp1 > 13300) {
	goto L370;
    }
    for (i__ = npp1; i__ <= 13300; ++i__) {
/* L360: */
/* Computing 2nd power */
	r__1 = rest_1.b[i__ - 1];
	sm += r__1 * r__1;
    }
    goto L390;
L370:
    for (j = 1; j <= 200; ++j) {
/* L380: */
	rest_1.w[j - 1] = zero;
    }
L390:
    *rnorm = sqrt(sm);
    return 0;

/*             THE FOLLOWING BLOCK OF CODE IS USED AS AN INTERNAL */
/*             SUBROUTINE TO SOLVE THE TRIANGULAR SYSTEM, PUTTING */
/*             THE SOLUTION IN ZZ(). */

L400:
    i__1 = nsetp;
    for (l = 1; l <= i__1; ++l) {
	ip = nsetp + 1 - l;
	if (l == 1) {
	    goto L420;
	}
	i__2 = ip;
	for (ii = 1; ii <= i__2; ++ii) {
/* L410: */
	    rest_1.zz[ii - 1] -= all_1.a[ii + jj * 13300 - 13301] * rest_1.zz[
		    ip];
	}
L420:
	jj = other_1.index[ip - 1];
/* L430: */
	rest_1.zz[ip - 1] /= all_1.a[ip + jj * 13300 - 13301];
    }
    switch (next) {
	case 0: goto L200;
	case 1: goto L320;
    }
} /* nnls_ */


/*     SUBROUTINE H12(MODE,LPIVOT,L1,M,U,IUE,UP,C,ICE,ICV,NCV) */
/*     C.L.LAWSON AND R.J.HANSON, 'SOLVING LEAST SQUARES PROBLEMS', */
/*     PRENTICE-HALL, 1974. */

/*     CONSTRUCTION AND/OR APPLICATION OF A SINGLE HOUSEHOLDER */
/*     TRANSFORMATION..    Q = I + U*(U**T)/B */

/*     MODE    = 1 OR 2 TO SELECT ALGORITHM H1 OR H2. */
/*     LPIVOT  IS THE INDEX OF THE PIVOT ELEMENT. */
/*     L1,M    IF L1 .LE. M THE TRANSFORMATION WILL BE CONSTRUCTED */
/*             TO ZERO ELEMENTS INDEXED FROM L1 THROUGH M.  IF L1 */
/*             .GT. M THE SUBROUTINE DOES AN IDENTITY TRANSFORMATION. */
/*     U(),IUE,UP */
/*             ON ENTRY TO H1 U() CONTAINS THE PIVOT VECTOR. IUE IS */
/*             THE STORAGE INCREMENT BETWEEN ELEMENTS.  ON EXIT FROM */
/*             H1 U() AND UP CONTAIN QUANTITES DEFINING THE VECTOR U */
/*             OF THE HOUSEHOLDER TRANSFORMATION.  ON ENTRY TO H2 U() */
/*             AND UP SHOULD CONTAIN QUANTITIES PREVIOUSLY COMPUTED */
/*             BY H1.  THESE WILL NOT BE MODIFIED BY H2. */
/*     C()     ON ENTRY TO H1 OR H2 C() CONTAINS A MATRIX WHICH WILL */
/*             BE REGARDED AS A SET OF VECTORS TO WHICH THE HOUSEHOLDER */
/*             TRANSFORMATION IS TO BE APPLIED.  ON EXIT C() CONTAINS */
/*             THE SET OF TRANSFORMED VECTORS. */
/*     ICE     STORAGE INCREMENT BETWEEN ELEMENTS OF VECTORS IN C(). */
/*     ICV     STORAGE INCREMENT BETWEEN VECTORS IN C(). */
/*     NCV     NUMBER OF VECTORS IN C() TO BE TRANSFORMED.  IF NCV */
/*             .LE. 0 NO OPERATIONS WILL BE DONE ON C(). */

/* Subroutine */ int h12_(integer *mode, integer *lpivot, integer *l1, 
	integer *m, real *u, integer *iue, real *up, real *c__, integer *ice, 
	integer *icv, integer *ncv)
{
    /* System generated locals */
    integer u_dim1, u_offset, i__1, i__2;
    real r__1, r__2;
    doublereal d__1;

    /* Builtin functions */
    double sqrt(doublereal);

    /* Local variables */
    static doublereal b;
    static integer i__, j, i2, i3, i4;
    static real cl;
    static doublereal sm;
    static real sm1, one;
    static integer incr;
    static real clinv;

    /* Parameter adjustments */
    u_dim1 = *iue;
    u_offset = 1 + u_dim1;
    u -= u_offset;
    --c__;

    /* Function Body */
    one = 1.f;

    if (0 >= *lpivot || *lpivot >= *l1 || *l1 > *m) {
	return 0;
    }
    cl = (r__1 = u[*lpivot * u_dim1 + 1], dabs(r__1));
    if (*mode == 2) {
	goto L60;
    }

/*               .....  CONSTRUCT THE TRANSFORMATION  ..... */

    i__1 = *m;
    for (j = *l1; j <= i__1; ++j) {
/* L10: */
/* Computing MAX */
	r__2 = (r__1 = u[j * u_dim1 + 1], dabs(r__1));
	cl = dmax(r__2,cl);
    }
    if (cl <= 0.f) {
	goto L130;
    } else {
	goto L20;
    }
L20:
    clinv = one / cl;
/* Computing 2nd power */
    d__1 = (doublereal) u[*lpivot * u_dim1 + 1] * clinv;
    sm = d__1 * d__1;
    i__1 = *m;
    for (j = *l1; j <= i__1; ++j) {
/* L30: */
/* Computing 2nd power */
	d__1 = (doublereal) u[j * u_dim1 + 1] * clinv;
	sm += d__1 * d__1;
    }

/*               CONVERT DBLE PREC SM TO SNGL PREC SM1. */

    sm1 = sm;
    cl *= sqrt(sm1);
    if (u[*lpivot * u_dim1 + 1] <= 0.f) {
	goto L50;
    } else {
	goto L40;
    }
L40:
    cl = -cl;
L50:
    *up = u[*lpivot * u_dim1 + 1] - cl;
    u[*lpivot * u_dim1 + 1] = cl;
    goto L70;

/*               .....  APPLY THE TRANSFORMATION I+U*(U**T)/B  TO C  ..... */

L60:
    if (cl <= 0.f) {
	goto L130;
    } else {
	goto L70;
    }
L70:
    if (*ncv <= 0) {
	return 0;
    }
    b = (doublereal) (*up) * u[*lpivot * u_dim1 + 1];

/*               B MUST BE NONPOSITIVE HERE.  IF B = 0., RETURN */

    if (b >= 0.) {
	goto L130;
    } else {
	goto L80;
    }
L80:
    b = one / b;
    i2 = 1 - *icv + *ice * (*lpivot - 1);
    incr = *ice * (*l1 - *lpivot);
    i__1 = *ncv;
    for (j = 1; j <= i__1; ++j) {
	i2 += *icv;
	i3 = i2 + incr;
	i4 = i3;
	sm = c__[i2] * (doublereal) (*up);
	i__2 = *m;
	for (i__ = *l1; i__ <= i__2; ++i__) {
	    sm += c__[i3] * (doublereal) u[i__ * u_dim1 + 1];
/* L90: */
	    i3 += *ice;
	}
	if (sm != 0.) {
	    goto L100;
	} else {
	    goto L120;
	}
L100:
	sm *= b;
	c__[i2] += sm * (doublereal) (*up);
	i__2 = *m;
	for (i__ = *l1; i__ <= i__2; ++i__) {
	    c__[i4] += sm * (doublereal) u[i__ * u_dim1 + 1];
/* L110: */
	    i4 += *ice;
	}
L120:
	;
    }
L130:
    return 0;
} /* h12_ */


/* Subroutine */ int g1_(real *a, real *b, real *cos__, real *sin__, real *
	sig)
{
    /* System generated locals */
    real r__1;

    /* Builtin functions */
    double sqrt(doublereal), r_sign(real *, real *);

    /* Local variables */
    static real xr, yr, one, zero;


/*     C.L.LAWSON AND R.J.HANSON, 'SOLVING LEAST SQUARES PROBLEMS', */
/*     PRENTICE-HALL, 1974. */

/*     COMPUTE ORTHOGONAL ROTATION MATRIX. */
/*     COMPUTE..  MATRIX  (C, S) SO THAT (C, S)(A) = (SQRT(A**2+B**2)) */
/*                        (-S,C)         (-S,C)(B)   (   0          ) */
/*     COMPUTE SIG = SQRT(A**2+B**2) */
/*     SIG IS COMPUTED LAST TO ALLOW FOR THE POSSIBILITY THAT SIG */
/*     MAY BE IN THE SAME LOCATION AS A OR B. */

    zero = 0.f;
    one = 1.f;
    if (dabs(*a) <= dabs(*b)) {
	goto L10;
    }
    xr = *b / *a;
/* Computing 2nd power */
    r__1 = xr;
    yr = sqrt(one + r__1 * r__1);
    r__1 = one / yr;
    *cos__ = r_sign(&r__1, a);
    *sin__ = *cos__ * xr;
    *sig = dabs(*a) * yr;
    return 0;
L10:
    if (*b != 0.f) {
	goto L20;
    } else {
	goto L30;
    }
L20:
    xr = *a / *b;
/* Computing 2nd power */
    r__1 = xr;
    yr = sqrt(one + r__1 * r__1);
    r__1 = one / yr;
    *sin__ = r_sign(&r__1, b);
    *cos__ = *sin__ * xr;
    *sig = dabs(*b) * yr;
    return 0;
L30:
    *sig = zero;
    *cos__ = zero;
    *sin__ = one;
    return 0;
} /* g1_ */


/* Subroutine */ int g2_(real *cos__, real *sin__, real *x, real *y)
{
    static real xr;


/*     C.L.LAWSON AND R.J.HANSON, 'SOLVING LEAST SQUARES PROBLEMS', */
/*     PRENTICE-HALL, 1974. */
/*     APPLY THE ROTATION COMPUTED BY G1 TO (X, Y). */

    xr = *cos__ * *x + *sin__ * *y;
    *y = -(*sin__) * *x + *cos__ * *y;
    *x = xr;
    return 0;
} /* g2_ */


doublereal diff_(real *x, real *y)
{
    /* System generated locals */
    real ret_val;

/*     C.L.LAWSON AND R.J.HANSON, 'SOLVING LEAST SQUARES PROBLEMS', */
/*     PRENTICE-HALL, 1974. */
    ret_val = *x - *y;
    return ret_val;
} /* diff_ */

/* Subroutine */ int sva_(integer *mdata, integer *iscale)
{
    /* Format strings */
    static char fmt_11[] = "(1x,\002ENTER THE FILE NAME OF THE (OUPUT) V MAT"
	    "RIX\002)";
    static char fmt_12[] = "(a)";
    static char fmt_270[] = "(\002 SINGULAR VALUE ANALYSIS OF THE LEAST SQUA"
	    "RES\002,\002 PROBLEM,  A*X=B,  SCALED AS  (A*D)*Y=B  .\002)";
    static char fmt_260[] = "(\002 M = \002,i6,\002,   N = \002,i4,\002,   M"
	    "DATA = \002,i8)";
    static char fmt_280[] = "(\002 SCALING OPTION NO.\002,i2,\002.  D IS A D"
	    "IAGONAL\002,\002 MATRIX WITH THE FOLLOWING DIAGONAL ELEMENTS."
	    ".\002/(5x,10e12.4))";
    static char fmt_290[] = "(\002 SCALING OPTION NO. 1.   D IS THE IDENTITY"
	    " MATRIX.\002/1x)";
    static char fmt_220[] = "(\002  INDEX  SING. VALUE       P COEF        "
	    " \002,\002RECIP. S.V.            G COEF            G**2  \002"
	    ",\002        C.S.S.      N.S.R.C.S.S.\002)";
    static char fmt_230[] = "(\002 \002,4x,\0020\002,84x,1pe14.4,2x,1pe14.4)";
    static char fmt_240[] = "(\002 \002,i5,e12.4,1p(e14.4,4x,e14.4,4x,e14.4,"
	    "4x,e14.4,4x,e14.4,2x,e14.4))";
    static char fmt_250[] = "(\002 \002,i5,f12.4,1p(e14.4,4x,e14.4,4x,e14.4,"
	    "4x,e14.4,4x,e14.4,2x,e14.4))";
    static char fmt_300[] = "(\002 INDEX\002,13x,\002         YNORM         "
	    "RNORM\002,14x,\002  LOG10(YNORM)  LOG10(RNORM)\002/1x)";
    static char fmt_310[] = "(\002 \002,i4,14x,2e14.5,14x,2f14.5)";
    static char fmt_320[] = "(\002 NORMS OF SOLUTION AND RESIDUAL VECTORS FO"
	    "R A RANGE OF\002,\002 VALUES OF THE LEVENBERG-MARQUARDT PARAMETER"
	    "\002,\002, LAMBDA.\002)";
    static char fmt_321[] = "(/\002 \002,4x,\002        LAMBDA         TNORM"
	    "         RNORM\002,\002 LOG10(LAMBDA)  LOG10(YNORM)  LOG10(RNORM)"
	    "\002)";
    static char fmt_330[] = "(5x,3e14.5,3f14.5)";

    /* System generated locals */
    integer i__1, i__2, i__3;
    real r__1, r__2;
    doublereal d__1;
    olist o__1;
    cllist cl__1;

    /* Builtin functions */
    integer s_wsfe(cilist *), e_wsfe(void), s_rsfe(cilist *), do_fio(integer *
	    , char *, ftnlen), e_rsfe(void), f_open(olist *);
    double sqrt(doublereal);
    integer f_clos(cllist *);
    double r_lg10(real *), log(doublereal), exp(doublereal);

    /* Local variables */
    static real d__[200];
    static integer i__, j, k;
    static real a1, a2, a3, a4;
    static integer ie;
    static real el;
    static integer jj;
    static doublereal sb;
    static real pi;
    static integer js;
    static real rl, sl, yl, rs, ys, el2;
    static integer np1, mx1, nx1;
    static real del, one, ten, ysq, aln10, sing[327];
    static integer nsol;
    static logical test;
    static real zero, alamb;
    static integer names[200], minmn;
    static doublereal dzero;
    static real rnorm;
    extern /* Subroutine */ int svdrs_(real *, integer *, integer *, integer *
	    , real *, integer *, integer *, real *);
    static real ynorm;
    static integer minmn1;
    static char ivfile[40];
    extern /* Subroutine */ int funnel_(real *, integer *, integer *), 
	    mfeout_(real *, integer *, integer *, integer *, integer *, 
	    integer *);

    /* Fortran I/O blocks */
    static cilist io___107 = { 0, 6, 0, fmt_11, 0 };
    static cilist io___108 = { 0, 5, 0, fmt_12, 0 };
    static cilist io___116 = { 0, 9, 0, fmt_270, 0 };
    static cilist io___117 = { 0, 9, 0, fmt_260, 0 };
    static cilist io___123 = { 0, 9, 0, fmt_280, 0 };
    static cilist io___124 = { 0, 9, 0, fmt_290, 0 };
    static cilist io___127 = { 0, 9, 0, fmt_220, 0 };
    static cilist io___134 = { 0, 9, 0, fmt_230, 0 };
    static cilist io___140 = { 0, 9, 0, fmt_240, 0 };
    static cilist io___141 = { 0, 9, 0, fmt_250, 0 };
    static cilist io___142 = { 0, 9, 0, fmt_240, 0 };
    static cilist io___143 = { 0, 9, 0, fmt_300, 0 };
    static cilist io___149 = { 0, 9, 0, fmt_310, 0 };
    static cilist io___155 = { 0, 9, 0, fmt_320, 0 };
    static cilist io___156 = { 0, 9, 0, fmt_321, 0 };
    static cilist io___162 = { 0, 9, 0, fmt_330, 0 };


/*     C.L.LAWSON AND R.J.HANSON, SOLVING LEAST SQUARES PROBLEMS, */
/*     PRENTICE-HALL, 1974. */
/*     SINGULAR VALUE ANALYSIS PRINTOUT. */

/*     ISCALE   SET BY USER TO 1, 2, OR 3 TO SELECT COLUMN SCALING OPTION. */
/*              1   SUBR. WILL USE IDENTITY SCALING AND IGNORE THE D() ARRAY. */
/*              2   SUBR. WILL SCALE NONZERO COLS TO HAVE UNIT EUCLIDEAN */
/*                  LENGTH AND WILL STORE RECIPROCAL LENGTHS OF ORIGINAL */
/*                  NONZERO COLS IN D(). */
/*              3   USER SUPPLIES COL SCALE FACTORS IN D(). SUBR WILL */
/*                  MULT COL J BY D(J) AND REMOVE THE SCALING FROM THE */
/*                  SOLUTION AT THE END. */
/*     SING(3*N) */
    s_wsfe(&io___107);
    e_wsfe();
    s_rsfe(&io___108);
    do_fio(&c__1, ivfile, (ftnlen)40);
    e_rsfe();
    o__1.oerr = 0;
    o__1.ounit = 10;
    o__1.ofnmlen = 40;
    o__1.ofnm = ivfile;
    o__1.orl = 0;
    o__1.osta = "NEW";
    o__1.oacc = "SEQUENTIAL";
    o__1.ofm = "UNFORMATTED";
    o__1.oblnk = 0;
    f_open(&o__1);
    dzero = 0.;
    one = 1.f;
    zero = 0.f;
    if (FALSE_) {
	return 0;
    }
    np1 = 201;
    mx1 = 13300;
    nx1 = 200;
    s_wsfe(&io___116);
    e_wsfe();
    s_wsfe(&io___117);
    do_fio(&c__1, (char *)&mx1, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&nx1, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&(*mdata), (ftnlen)sizeof(integer));
    e_wsfe();
    switch (*iscale) {
	case 1:  goto L60;
	case 2:  goto L10;
	case 3:  goto L10;
    }

/*     APPLY COLUMN SCALING TO A */

L10:
    for (j = 1; j <= 200; ++j) {
	a1 = d__[j - 1];
	switch (*iscale) {
	    case 1:  goto L20;
	    case 2:  goto L20;
	    case 3:  goto L40;
	}
L20:
	sb = dzero;
	for (i__ = 1; i__ <= 13300; ++i__) {
/* L30: */
/* Computing 2nd power */
	    d__1 = (doublereal) all_1.a[i__ + j * 13300 - 13301];
	    sb += d__1 * d__1;
	}
	a1 = sqrt(sb);
	if (a1 == zero) {
	    a1 = one;
	}
	a1 = one / a1;
	d__[j - 1] = a1;
L40:
	for (i__ = 1; i__ <= 13300; ++i__) {
/* L50: */
	    all_1.a[i__ + j * 13300 - 13301] *= a1;
	}
    }
    s_wsfe(&io___123);
    do_fio(&c__1, (char *)&(*iscale), (ftnlen)sizeof(integer));
    for (j = 1; j <= 200; ++j) {
	do_fio(&c__1, (char *)&d__[j - 1], (ftnlen)sizeof(real));
    }
    e_wsfe();
    goto L70;
L60:
    s_wsfe(&io___124);
    e_wsfe();
L70:

/*     OBTAIN SING. VALUE DECOMP. OF SCALED MATRIX */

    svdrs_(all_1.a, &c__13300, &c__13300, &c__200, rest_1.b, &c__1, &c__1, 
	    sing);
    funnel_(all_1.a, &c__13300, &c__200);
    cl__1.cerr = 0;
    cl__1.cunit = 10;
    cl__1.csta = 0;
    f_clos(&cl__1);


/*     PRINT THE V MATRIX. */

    mfeout_(all_1.a, &c__13300, &c__200, &c__200, names, &c__1);
    if (*iscale == 1) {
	goto L90;
    }

/*     REPLACE V BY D*V IN THE ARRAY A() */

    for (i__ = 1; i__ <= 200; ++i__) {
	for (j = 1; j <= 200; ++j) {
/* L80: */
	    all_1.a[i__ + j * 13300 - 13301] = d__[i__ - 1] * all_1.a[i__ + j 
		    * 13300 - 13301];
	}
    }

/*     G NOW IN B ARRAY. V NOW IN A ARRAY. */

/*     OBTAIN SUMMARY OUTPUT. */

L90:
    s_wsfe(&io___127);
    e_wsfe();

/*     COMPUTE CUMULATIVE SUMS OF SQUARES OF COMPONENTS OF */
/*     G AND STORE THEM IN SING(I), I=MINMN+1,....,2*MINMN+1 */

    sb = dzero;
    minmn = 200;
    minmn1 = minmn + 1;
    if (13300 == minmn) {
	goto L110;
    }
    for (i__ = minmn1; i__ <= 13300; ++i__) {
/* L100: */
/* Computing 2nd power */
	d__1 = (doublereal) rest_1.b[i__ - 1];
	sb += d__1 * d__1;
    }
L110:
    sing[minmn * 2] = sb;
    i__1 = minmn;
    for (jj = 1; jj <= i__1; ++jj) {
	j = minmn + 1 - jj;
/* Computing 2nd power */
	d__1 = (doublereal) rest_1.b[j - 1];
	sb += d__1 * d__1;
	js = minmn + j;
/* L120: */
	sing[js - 1] = sb;
    }
    a3 = sing[minmn];
    a4 = sqrt(a3 / (real) max(1,*mdata));
    s_wsfe(&io___134);
    do_fio(&c__1, (char *)&a3, (ftnlen)sizeof(real));
    do_fio(&c__1, (char *)&a4, (ftnlen)sizeof(real));
    e_wsfe();

    nsol = 0;



    i__1 = minmn;
    for (k = 1; k <= i__1; ++k) {
	if (sing[k - 1] == zero) {
	    goto L130;
	}
	nsol = k;
	pi = rest_1.b[k - 1] / sing[k - 1];
	a1 = one / sing[k - 1];
/* Computing 2nd power */
	r__1 = rest_1.b[k - 1];
	a2 = r__1 * r__1;
	a3 = sing[minmn1 + k - 1];
/* Computing MAX */
	i__2 = 1, i__3 = *mdata - k;
	a4 = sqrt(a3 / (real) max(i__2,i__3));
	test = sing[k - 1] >= 100.f || sing[k - 1] < .001f;
	if (test) {
	    s_wsfe(&io___140);
	    do_fio(&c__1, (char *)&k, (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&sing[k - 1], (ftnlen)sizeof(real));
	    do_fio(&c__1, (char *)&pi, (ftnlen)sizeof(real));
	    do_fio(&c__1, (char *)&a1, (ftnlen)sizeof(real));
	    do_fio(&c__1, (char *)&rest_1.b[k - 1], (ftnlen)sizeof(real));
	    do_fio(&c__1, (char *)&a2, (ftnlen)sizeof(real));
	    do_fio(&c__1, (char *)&a3, (ftnlen)sizeof(real));
	    do_fio(&c__1, (char *)&a4, (ftnlen)sizeof(real));
	    e_wsfe();
	}
	if (! test) {
	    s_wsfe(&io___141);
	    do_fio(&c__1, (char *)&k, (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&sing[k - 1], (ftnlen)sizeof(real));
	    do_fio(&c__1, (char *)&pi, (ftnlen)sizeof(real));
	    do_fio(&c__1, (char *)&a1, (ftnlen)sizeof(real));
	    do_fio(&c__1, (char *)&rest_1.b[k - 1], (ftnlen)sizeof(real));
	    do_fio(&c__1, (char *)&a2, (ftnlen)sizeof(real));
	    do_fio(&c__1, (char *)&a3, (ftnlen)sizeof(real));
	    do_fio(&c__1, (char *)&a4, (ftnlen)sizeof(real));
	    e_wsfe();
	}
	goto L140;
L130:
	s_wsfe(&io___142);
	do_fio(&c__1, (char *)&k, (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&sing[k - 1], (ftnlen)sizeof(real));
	e_wsfe();
	pi = zero;
L140:
	for (i__ = 1; i__ <= 200; ++i__) {
	    all_1.a[i__ + k * 13300 - 13301] *= pi;
/* L150: */
	    if (k > 1) {
		all_1.a[i__ + k * 13300 - 13301] += all_1.a[i__ + (k - 1) * 
			13300 - 13301];
	    }
	}
/* L160: */
    }

/*     COMPUTE AND PRINT VALUES OF YNORM AND RNORM. */

    s_wsfe(&io___143);
    e_wsfe();
    j = 0;
    ysq = zero;
    goto L180;
L170:
    ++j;
/* Computing 2nd power */
    r__1 = rest_1.b[j - 1] / sing[j - 1];
    ysq += r__1 * r__1;
L180:
    ynorm = sqrt(ysq);
    js = minmn1 + j;
    rnorm = sqrt(sing[js - 1]);
    yl = -1e3f;
    if (ynorm > 0.f) {
	yl = r_lg10(&ynorm);
    }
    rl = -1e3f;
    if (rnorm > 0.f) {
	rl = r_lg10(&rnorm);
    }
    s_wsfe(&io___149);
    do_fio(&c__1, (char *)&j, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&ynorm, (ftnlen)sizeof(real));
    do_fio(&c__1, (char *)&rnorm, (ftnlen)sizeof(real));
    do_fio(&c__1, (char *)&yl, (ftnlen)sizeof(real));
    do_fio(&c__1, (char *)&rl, (ftnlen)sizeof(real));
    e_wsfe();
    if (j < nsol) {
	goto L170;
    }

/*     COMPUTE VALUES OF XNORM AND RNORM FOR A SEQUENCE OF VALUES OF */
/*     THE LEVENBERG-MARQUARDT PARAMETER. */

    if (sing[0] == zero) {
	goto L210;
    }
    el = r_lg10(sing) + one;
    el2 = r_lg10(&sing[nsol - 1]) - one;
    del = (el2 - el) / 20.f;
    ten = 10.f;
    aln10 = log(ten);
    s_wsfe(&io___155);
    e_wsfe();
    s_wsfe(&io___156);
    e_wsfe();
    for (ie = 1; ie <= 21; ++ie) {
/*     COMPUTE ALAMB=10.**EL */
	alamb = exp(aln10 * el);
	ys = 0.f;
	js = minmn1 + nsol;
	rs = sing[js - 1];
	i__1 = minmn;
	for (i__ = 1; i__ <= i__1; ++i__) {
/* Computing 2nd power */
	    r__1 = sing[i__ - 1];
/* Computing 2nd power */
	    r__2 = alamb;
	    sl = r__1 * r__1 + r__2 * r__2;
/* Computing 2nd power */
	    r__1 = rest_1.b[i__ - 1] * sing[i__ - 1] / sl;
	    ys += r__1 * r__1;
/* Computing 2nd power */
	    r__2 = alamb;
/* Computing 2nd power */
	    r__1 = rest_1.b[i__ - 1] * (r__2 * r__2) / sl;
	    rs += r__1 * r__1;
/* L190: */
	}
	ynorm = sqrt(ys);
	rnorm = sqrt(rs);
	rl = -1e3f;
	if (rnorm > zero) {
	    rl = r_lg10(&rnorm);
	}
	yl = -1e3f;
	if (ynorm > zero) {
	    yl = r_lg10(&ynorm);
	}
	s_wsfe(&io___162);
	do_fio(&c__1, (char *)&alamb, (ftnlen)sizeof(real));
	do_fio(&c__1, (char *)&ynorm, (ftnlen)sizeof(real));
	do_fio(&c__1, (char *)&rnorm, (ftnlen)sizeof(real));
	do_fio(&c__1, (char *)&el, (ftnlen)sizeof(real));
	do_fio(&c__1, (char *)&yl, (ftnlen)sizeof(real));
	do_fio(&c__1, (char *)&rl, (ftnlen)sizeof(real));
	e_wsfe();
	el += del;
/* L200: */
    }

/*     PRINT CANDIDATE SOLUTIONS. */

L210:
    if (nsol >= 1) {
	mfeout_(all_1.a, &c__13300, &c__200, &nsol, names, &c__2);
    }
    return 0;
} /* sva_ */


/*     SUBROUTINE SVDRS(A,MDA,MM,NN,B,MDB,NB,S) */
/*     C.L.LAWSON AND R.J.HANSON, SOLVING LEAST SQUARES PROBLEMS, */
/*     PRENTICE-HALL,1974. */
/*     SINGULAR VALUE DECOMPOSITION ALSO TREATING RIGHT SIDE VECTOR. */

/*     THE ARRAY S OCCUPIES 3*N CELLS. */
/*     A OCCUPIES M*N CELLS */
/*     B OCCUPIES M*NB CELLS */

/*     SPECIAL SINGULAR VALUE DECOMPOSITION SUBROUTINE */
/*     WE HAVE THE M X N MATRIX A AND THE SYSTEM A*X=B TO SOLVE. */
/*     EITHER M .GE. N OR M .LT. N IS PERMITTED. */
/*                      THE SINGULAR VALUE DECOMPOSITION */
/*     A = U*S*V**(T) IS MADE IN SUCH A WAY THAT ONE GETS */
/*        (1) THE MATRIX V IN THE FIRST N ROWS AND COLUMNS OF A. */
/*         (2) THE DIAGONAL MATRIX OF ORDERED SINGULAR VALUES IN */
/*            THE FIRST N CELLS OF THE ARRAY S(IP), IP .GE. 3*N. */
/*        (3) THE MATRIX PRODUCT U**(T)*B=G GETS PLACED BACK IN B. */
/*        (4) THE USER MUST COMPLETE THE SOLUTION AND DO HIS OWN */
/*            SINGULAR VALUE ANALYSIS. */

/*     GIVE SPECIAL */
/*     TREATMENT TO ROWS AND COLUMNS WHICH ARE ENTIRELY ZERO. THIS */
/*     CAUSES CERTAIN ZERO SING. VALS. TO APPEAR AS EXACT ZEROS RATHER */
/*     THAN AS ABOUT ETA TIMES THE LARGEST SING. VAL.  IT SIMILARLY */
/*     CLEANS UP THE ASSOCIATED COLUMNS OF U AND V. */
/*     METHOD... */
/*      1. EXCHANGE COLS OF A TO PACK NONZERO COLS TO THE LEFT. */
/*         SET N = NO. OF NONZERO COLS. */
/*         USE LOCATIONS A(1,NN),A(1,NN-1),...,A(1,N+1) TO RECORD THE */
/*         COL PERMUTATIONS. */
/*      2. EXCHANGE ROWS OF A TO PACK NONZERO ROWS TO THE TOP. */
/*         QUIT PACKING IF FIND N NONZERO ROWS.  MAKE SAME ROW EXCHANGES */
/*         IN B.  SET M SO THAT ALL NONZERO ROWS OF THE PERMUTED A */
/*         ARE IN FIRST M ROWS.  IF M .LE. N THEN ALL M ROWS ARE */
/*         NONZERO.  IF M .GT. N THEN THE FIRST N ROWS ARE KNOWN */
/*         TO BE NONZERO, AND ROWS N+1 THRU M MAY BE ZERO OR NONZERO. */
/*      3. APPLY ORIGINAL ALGORITHM TO THE M BY N PROBLEM. */
/*      4. MOVE PERMUTATION RECORD FROM A(,) TO S(I),I=N+1,...,NN. */
/*      5. BUILD V UP FROM N BY N TO NN BY NN BY PLACING ONES ON */
/*         THE DIAGONAL AND ZEROS ELSEWHERE.  THIS IS ONLY PARTLY DONE */
/*         EXPLICITLY.  IT IS COMPLETED DURING STEP 6. */
/*      6. EXCHANGE ROWS OF V TO COMPENSATE FOR COL EXCHANGES OF STEP 2. */
/*      7. PLACE ZEROS IN S(I),I=N+1,NN TO REPRESENT ZERO SING VALS. */

/* Subroutine */ int svdrs_(real *a, integer *mda, integer *mm, integer *nn, 
	real *b, integer *mdb, integer *nb, real *s)
{
    /* Format strings */
    static char fmt_320[] = "(\002 CONVERGENCE FAILURE IN QR BIDIAGONAL SVD "
	    "ROUTINE\002)";

    /* System generated locals */
    integer a_dim1, a_offset, b_dim1, b_offset, s_dim1, s_offset, i__1, i__2, 
	    i__3, i__4;

    /* Builtin functions */
    integer s_wsfe(cilist *), e_wsfe(void);
    /* Subroutine */ int s_stop(char *, ftnlen);

    /* Local variables */
    static integer i__, j, k, l, m, n;
    static real t;
    extern /* Subroutine */ int h12_(integer *, integer *, integer *, integer 
	    *, real *, integer *, real *, real *, integer *, integer *, 
	    integer *);
    static integer ns, np1;
    static real one;
    static integer nsp1;
    extern /* Subroutine */ int qrbd_(integer *, real *, real *, integer *, 
	    real *, integer *, integer *, real *, integer *, integer *);
    static real zero;
    static integer ipass;

    /* Fortran I/O blocks */
    static cilist io___176 = { 0, 9, 0, fmt_320, 0 };


    /* Parameter adjustments */
    s_dim1 = *nn;
    s_offset = 1 + s_dim1;
    s -= s_offset;
    a_dim1 = *mda;
    a_offset = 1 + a_dim1;
    a -= a_offset;
    b_dim1 = *mdb;
    b_offset = 1 + b_dim1;
    b -= b_offset;

    /* Function Body */
    zero = 0.f;
    one = 1.f;

/*                     BEGIN...SPECIAL FOR ZERO ROWS AND COLS. */
/*                     PACK THE NONZERO COLS TO THE LEFT */

    n = *nn;
    if (n <= 0 || *mm <= 0) {
	return 0;
    }
    j = n;
L10:
    i__1 = *mm;
    for (i__ = 1; i__ <= i__1; ++i__) {
	if (a[i__ + j * a_dim1] != 0.f) {
	    goto L50;
	} else {
	    goto L20;
	}
L20:
	;
    }

/*     COL J IS ZERO. EXCHANGE IT WITH COL N. */

    if (j == n) {
	goto L40;
    }
    i__1 = *mm;
    for (i__ = 1; i__ <= i__1; ++i__) {
/* L30: */
	a[i__ + j * a_dim1] = a[i__ + n * a_dim1];
    }
L40:
    a[n * a_dim1 + 1] = (real) j;
    --n;
L50:
    --j;
    if (j >= 1) {
	goto L10;
    }
/*                            IF N=0 THEN A IS ENTIRELY ZERO AND SVD */
/*                            COMPUTATION CAN BE SKIPPED. */
    ns = 0;
    if (n == 0) {
	goto L240;
    }
/*                            PACK NONZERO ROWS TO THE TOP */
/*                            QUIT PACKING IF FIND N NONZERO ROWS. */
    i__ = 1;
    m = *mm;
L60:
    if (i__ > n || i__ >= m) {
	goto L150;
    }
    if (a[i__ + i__ * a_dim1] != 0.f) {
	goto L90;
    } else {
	goto L70;
    }
L70:
    i__1 = n;
    for (j = 1; j <= i__1; ++j) {
	if (a[i__ + j * a_dim1] != 0.f) {
	    goto L90;
	} else {
	    goto L80;
	}
L80:
	;
    }
    goto L100;
L90:
    ++i__;
    goto L60;
/*                            ROW I IS ZERO */
/*                            EXCHANGE ROWS I AND M */
L100:
    if (*nb <= 0) {
	goto L115;
    }
    i__1 = *nb;
    for (j = 1; j <= i__1; ++j) {
	t = b[i__ + j * b_dim1];
	b[i__ + j * b_dim1] = b[m + j * b_dim1];
/* L110: */
	b[m + j * b_dim1] = t;
    }
L115:
    i__1 = n;
    for (j = 1; j <= i__1; ++j) {
/* L120: */
	a[i__ + j * a_dim1] = a[m + j * a_dim1];
    }
    if (m > n) {
	goto L140;
    }
    i__1 = n;
    for (j = 1; j <= i__1; ++j) {
/* L130: */
	a[m + j * a_dim1] = zero;
    }
L140:
/*                             EXCHANGE IS FINISHED. */
    --m;
    goto L60;

L150:
/*                             END.. SPECIAL FOR ZERO ROWS AND COLUMNS */
/*                             BEGIN.. SVD ALGORITHM. */
/*     METHOD.. */
/*     (1)     REDUCE THE MATRIX TO UPPER BIDIAGONAL FORM WITH */
/*     HOUSEHOLDER TRANSFORMATIONS. */
/*          H(N)...H(1)AQ(1)...Q(N-2) = (D**T,0)**T */
/*     WHERE D IS UPPER BIDIAGONAL. */

/*     (2)     APPLY H(N)...H(1) TO B.  HERE H(N)...H(1)*B REPLACES B */
/*     IN STORAGE. */

/*     (3)     THE MATRIX PRODUCT W= Q(1)...Q(N-2) OVERWRITES THE FIRST */
/*     N ROWS OF A IN STORAGE. */

/*     (4)     AN SVD FOR D IS COMPUTED.  HERE K ROTATIONS RI AND PI ARE */
/*     COMPUTED SO THAT */
/*          RK...R1*D*P1**(T)...PK**(T) = DIAG(S1,...,SM) */
/*     TO WORKING ACCURACY.  THE SI ARE NONNEGATIVE AND NONINCREASING. */
/*     HERE RK...R1*B OVERWRITES B IN STORAGE WHILE */
/*     A*P1**(T)...PK**(T) OVERWRITES A IN STORAGE. */

/*     (5)     IT FOLLOWS THAT, WITH THE PROPER DEFINITIONS, */
/*     U**(T)*B OVERWRITES B, WHILE V OVERWRITES THE FIRST N ROW AND */
/*     COLUMNS OF A. */

    l = min(m,n);
/*             THE FOLLOWING LOOP REDUCES A TO UPPER BIDIAGONAL AND */
/*             ALSO APPLIES THE PREMULTIPLYING TRANSFORMATIONS TO B. */

    i__1 = l;
    for (j = 1; j <= i__1; ++j) {
	if (j >= m) {
	    goto L160;
	}
	i__2 = j + 1;
	i__3 = n - j;
	h12_(&c__1, &j, &i__2, &m, &a[j * a_dim1 + 1], &c__1, &t, &a[(j + 1) *
		 a_dim1 + 1], &c__1, mda, &i__3);
	i__2 = j + 1;
	h12_(&c__2, &j, &i__2, &m, &a[j * a_dim1 + 1], &c__1, &t, &b[b_offset]
		, &c__1, mdb, nb);
L160:
	if (j >= n - 1) {
	    goto L170;
	}
	i__2 = j + 1;
	i__3 = j + 2;
	i__4 = m - j;
	h12_(&c__1, &i__2, &i__3, &n, &a[j + a_dim1], mda, &s[j + s_dim1 * 3],
		 &a[j + 1 + a_dim1], mda, &c__1, &i__4);
L170:
	;
    }

/*     COPY THE BIDIAGONAL MATRIX INTO THE ARRAY S() FOR QRBD. */

    if (n == 1) {
	goto L190;
    }
    i__1 = n;
    for (j = 2; j <= i__1; ++j) {
	s[j + s_dim1] = a[j + j * a_dim1];
/* L180: */
	s[j + (s_dim1 << 1)] = a[j - 1 + j * a_dim1];
    }
L190:
    s[s_dim1 + 1] = a[a_dim1 + 1];

    ns = n;
    if (m >= n) {
	goto L200;
    }
    ns = m + 1;
    s[ns + s_dim1] = zero;
    s[ns + (s_dim1 << 1)] = a[m + (m + 1) * a_dim1];
L200:

/*     CONSTRUCT THE EXPLICIT N BY N PRODUCT MATRIX, W=Q1*Q2*...*QL*I */
/*     IN THE ARRAY A(). */

    i__1 = n;
    for (k = 1; k <= i__1; ++k) {
	i__ = n + 1 - k;
	if (i__ >= n - 1) {
	    goto L210;
	}
	i__2 = i__ + 1;
	i__3 = i__ + 2;
	i__4 = n - i__;
	h12_(&c__2, &i__2, &i__3, &n, &a[i__ + a_dim1], mda, &s[i__ + s_dim1 *
		 3], &a[(i__ + 1) * a_dim1 + 1], &c__1, mda, &i__4);
L210:
	i__2 = n;
	for (j = 1; j <= i__2; ++j) {
/* L220: */
	    a[i__ + j * a_dim1] = zero;
	}
/* L230: */
	a[i__ + i__ * a_dim1] = one;
    }

/*     COMPUTE THE SVD OF THE BIDIAGONAL MATRIX. */

    qrbd_(&ipass, &s[s_dim1 + 1], &s[(s_dim1 << 1) + 1], &ns, &a[a_offset], 
	    mda, &n, &b[b_offset], mdb, nb);

    switch (ipass) {
	case 1:  goto L240;
	case 2:  goto L310;
    }
L240:
    if (ns >= n) {
	goto L260;
    }
    nsp1 = ns + 1;
    i__1 = n;
    for (j = nsp1; j <= i__1; ++j) {
/* L250: */
	s[j + s_dim1] = zero;
    }
L260:
    if (n == *nn) {
	return 0;
    }
    np1 = n + 1;
/*                    MOVE RECORD OF PERMUTATIONS AND STORE ZEROS. */
    i__1 = *nn;
    for (j = np1; j <= i__1; ++j) {
	s[j + s_dim1] = a[j * a_dim1 + 1];
	i__2 = n;
	for (i__ = 1; i__ <= i__2; ++i__) {
/* L270: */
	    a[i__ + j * a_dim1] = zero;
	}
/* L280: */
    }
/*                  PERMUTE ROWS AND SET ZERO SINGULAR VALUES. */
    i__1 = *nn;
    for (k = np1; k <= i__1; ++k) {
	i__ = s[k + s_dim1];
	s[k + s_dim1] = zero;
	i__2 = *nn;
	for (j = 1; j <= i__2; ++j) {
	    a[k + j * a_dim1] = a[i__ + j * a_dim1];
/* L290: */
	    a[i__ + j * a_dim1] = zero;
	}
	a[i__ + k * a_dim1] = one;
/* L300: */
    }
/*                  END.. SPECIAL FOR ZERO ROWS AND COLUMNS. */
    return 0;
L310:
    s_wsfe(&io___176);
    e_wsfe();
    s_stop("", (ftnlen)0);
    return 0;
} /* svdrs_ */


/*     SUBROUTINE QRBD(IPASS,Q,E,NN,V,MDV,NRV,C,MDC,NCC) */
/*     C.L.LAWSON AND R.J.HANSON, SOLVING LEAST SQUARES PROBLEMS, */
/*     PRENTICE-HALL, 1974. */
/*         QR ALGORITHM FOR SINGULAR VALUES OF A BIDIAGONAL MATRIX. */

/*     THE BIDIAGONAL MATRIX */

/*                       (Q1,E2,0...    ) */
/*                       (   Q2,E3,0... ) */
/*               D=      (       .      ) */
/*                       (         .   0) */
/*                       (           .EN) */
/*                       (          0,QN) */

/*     IS PRE AND POST MULTIPLIED BY ELEMENTARY ROTATION MATRICES */
/*     RI AND PI SO THAT */

/*         RK...R1*D*P1**(T)...PK**(T) = DIAG(S1,...,SN) */

/*     TO WITHIN WORKING ACCURACY. */

/*     1. EI AND QI OCCUPY E(I) AND Q(I) AS INPUT. */
/*     2. RM...R11*C REPLACES 'C' IN STORAGE AS OUTPUT. */
/*     3. V*P1**(T)...PM**(T) REPLACES 'V' IN STORAGE AS OUTPUT. */
/*     4. SI OCCUPIES Q(I) AS OUTPUT. */
/*     5. THE SI'S ARE NONINCREASING AND NONNEGATIVE. */

/*     THIS CODE IS BASED ON THE PAPER AND 'ALGOL' CODE.. */
/*     REF.. */
/*     REINSCH,C.H. AND GOLUB,G.H. 'SINGULAR VALUE DECOMPOSITION */
/*     AND LEAST SQUARES SOLUTIONS' (NUMER. MATH.) VOL. 14, 1970. */

/* Subroutine */ int qrbd_(integer *ipass, real *q, real *e, integer *nn, 
	real *v, integer *mdv, integer *nrv, real *c__, integer *mdc, integer 
	*ncc)
{
    /* System generated locals */
    integer v_dim1, v_offset, c_dim1, c_offset, i__1, i__2, i__3;
    real r__1, r__2, r__3;

    /* Builtin functions */
    double sqrt(doublereal);

    /* Local variables */
    static real f, g, h__;
    static integer i__, j, k, l, n;
    static real t, x, y, z__;
    extern /* Subroutine */ int g1_(real *, real *, real *, real *, real *), 
	    g2_(real *, real *, real *, real *);
    static integer n10, ii, kk;
    static real cs;
    static integer ll;
    static real sn;
    static integer lp1;
    static real one, two;
    extern doublereal diff_(real *, real *);
    static logical fail;
    static real zero;
    static integer nqrs;
    static logical wntv;
    static real dnorm;
    static logical havers;

    /* Parameter adjustments */
    --e;
    --q;
    v_dim1 = *mdv;
    v_offset = 1 + v_dim1;
    v -= v_offset;
    c_dim1 = *mdc;
    c_offset = 1 + c_dim1;
    c__ -= c_offset;

    /* Function Body */
    zero = 0.f;
    one = 1.f;
    two = 2.f;

    n = *nn;
    *ipass = 1;
    if (n <= 0) {
	return 0;
    }
    n10 = n * 10;
    wntv = *nrv > 0;
    havers = *ncc > 0;
    fail = FALSE_;
    nqrs = 0;
    e[1] = zero;
    dnorm = zero;
    i__1 = n;
    for (j = 1; j <= i__1; ++j) {
/* L10: */
/* Computing MAX */
	r__3 = (r__1 = q[j], dabs(r__1)) + (r__2 = e[j], dabs(r__2));
	dnorm = dmax(r__3,dnorm);
    }
    i__1 = n;
    for (kk = 1; kk <= i__1; ++kk) {
	k = n + 1 - kk;

/*     TEST FOR SPLITTING OR RANK DEFICIENCIES.. */
/*     FIRST MAKE TEST FOR LAST DIAGONAL TERM, Q(K), BEING SMALL. */
L20:
	if (k == 1) {
	    goto L50;
	}
	r__1 = dnorm + q[k];
	if (diff_(&r__1, &dnorm) != 0.f) {
	    goto L50;
	} else {
	    goto L25;
	}

/*     SINCE Q(K) IS SMALL WE WILL MAKE A SPECIAL PASS TO */
/*     TRANSFORM E(K) TO ZERO. */

L25:
	cs = zero;
	sn = -one;
	i__2 = k;
	for (ii = 2; ii <= i__2; ++ii) {
	    i__ = k + 1 - ii;
	    f = -sn * e[i__ + 1];
	    e[i__ + 1] = cs * e[i__ + 1];
	    g1_(&q[i__], &f, &cs, &sn, &q[i__]);
/*     TRANSFORMATION CONSTRUCTED TO ZERO POSITION (I,K). */

	    if (! wntv) {
		goto L40;
	    }
	    i__3 = *nrv;
	    for (j = 1; j <= i__3; ++j) {
/* L30: */
		g2_(&cs, &sn, &v[j + i__ * v_dim1], &v[j + k * v_dim1]);
	    }
/*     ACCUMULATE RT. TRANSFORMATIONS IN V. */

L40:
	    ;
	}

/*     THE MATRIX IS NOW BIDIAGONAL, AND OF LOWER ORDER */
/*     SINCE E(K) .EQ. ZERO.. */

L50:
	i__2 = k;
	for (ll = 1; ll <= i__2; ++ll) {
	    l = k + 1 - ll;
	    r__1 = dnorm + e[l];
	    if (diff_(&r__1, &dnorm) != 0.f) {
		goto L55;
	    } else {
		goto L100;
	    }
L55:
	    r__1 = dnorm + q[l - 1];
	    if (diff_(&r__1, &dnorm) != 0.f) {
		goto L60;
	    } else {
		goto L70;
	    }
L60:
	    ;
	}
/*     THIS LOOP CAN'T COMPLETE SINCE E(1) = ZERO. */

	goto L100;

/*     CANCELLATION OF E(L), L .GT. 1. */
L70:
	cs = zero;
	sn = -one;
	i__2 = k;
	for (i__ = l; i__ <= i__2; ++i__) {
	    f = -sn * e[i__];
	    e[i__] = cs * e[i__];
	    r__1 = dnorm + f;
	    if (diff_(&r__1, &dnorm) != 0.f) {
		goto L75;
	    } else {
		goto L100;
	    }
L75:
	    g1_(&q[i__], &f, &cs, &sn, &q[i__]);
	    if (! havers) {
		goto L90;
	    }
	    i__3 = *ncc;
	    for (j = 1; j <= i__3; ++j) {
/* L80: */
		g2_(&cs, &sn, &c__[i__ + j * c_dim1], &c__[l - 1 + j * c_dim1]
			);
	    }
L90:
	    ;
	}

/*     TEST FOR CONVERGENCE.. */
L100:
	z__ = q[k];
	if (l == k) {
	    goto L170;
	}

/*     SHIFT FROM BOTTOM 2 BY 2 MINOR OF B**(T)*B. */
	x = q[l];
	y = q[k - 1];
	g = e[k - 1];
	h__ = e[k];
	f = ((y - z__) * (y + z__) + (g - h__) * (g + h__)) / (two * h__ * y);
/* Computing 2nd power */
	r__1 = f;
	g = sqrt(one + r__1 * r__1);
	if (f < zero) {
	    goto L110;
	}
	t = f + g;
	goto L120;
L110:
	t = f - g;
L120:
	f = ((x - z__) * (x + z__) + h__ * (y / t - h__)) / x;

/*     NEXT QR SWEEP.. */
	cs = one;
	sn = one;
	lp1 = l + 1;
	i__2 = k;
	for (i__ = lp1; i__ <= i__2; ++i__) {
	    g = e[i__];
	    y = q[i__];
	    h__ = sn * g;
	    g = cs * g;
	    g1_(&f, &h__, &cs, &sn, &e[i__ - 1]);
	    f = x * cs + g * sn;
	    g = -x * sn + g * cs;
	    h__ = y * sn;
	    y *= cs;
	    if (! wntv) {
		goto L140;
	    }

/*     ACCUMULATE ROTATIONS (FROM THE RIGHT) IN 'V' */
	    i__3 = *nrv;
	    for (j = 1; j <= i__3; ++j) {
/* L130: */
		g2_(&cs, &sn, &v[j + (i__ - 1) * v_dim1], &v[j + i__ * v_dim1]
			);
	    }
L140:
	    g1_(&f, &h__, &cs, &sn, &q[i__ - 1]);
	    f = cs * g + sn * y;
	    x = -sn * g + cs * y;
	    if (! havers) {
		goto L160;
	    }
	    i__3 = *ncc;
	    for (j = 1; j <= i__3; ++j) {
/* L150: */
		g2_(&cs, &sn, &c__[i__ - 1 + j * c_dim1], &c__[i__ + j * 
			c_dim1]);
	    }
/*     APPLY ROTATIONS FROM THE LEFT TO */
/*     RIGHT HAND SIDES IN 'C'.. */

L160:
	    ;
	}
	e[l] = zero;
	e[k] = f;
	q[k] = x;
	++nqrs;
	if (nqrs <= n10) {
	    goto L20;
	}
/*     RETURN TO 'TEST FOR SPLITTING'. */

	fail = TRUE_;

/*     CUTOFF FOR CONVERGENCE FAILURE. 'NQRS' WILL BE 2*N USUALLY. */
L170:
	if (z__ >= zero) {
	    goto L190;
	}
	q[k] = -z__;
	if (! wntv) {
	    goto L190;
	}
	i__2 = *nrv;
	for (j = 1; j <= i__2; ++j) {
/* L180: */
	    v[j + k * v_dim1] = -v[j + k * v_dim1];
	}
L190:
/*     CONVERGENCE. Q(K) IS MADE NONNEGATIVE.. */

/* L200: */
	;
    }
    if (n == 1) {
	return 0;
    }
    i__1 = n;
    for (i__ = 2; i__ <= i__1; ++i__) {
	if (q[i__] > q[i__ - 1]) {
	    goto L220;
	}
/* L210: */
    }
    if (fail) {
	*ipass = 2;
    }
    return 0;

/*     EVERY SINGULAR VALUE IS IN ORDER.. */
L220:
    i__1 = n;
    for (i__ = 2; i__ <= i__1; ++i__) {
	t = q[i__ - 1];
	k = i__ - 1;
	i__2 = n;
	for (j = i__; j <= i__2; ++j) {
	    if (t >= q[j]) {
		goto L230;
	    }
	    t = q[j];
	    k = j;
L230:
	    ;
	}
	if (k == i__ - 1) {
	    goto L270;
	}
	q[k] = q[i__ - 1];
	q[i__ - 1] = t;
	if (! havers) {
	    goto L250;
	}
	i__2 = *ncc;
	for (j = 1; j <= i__2; ++j) {
	    t = c__[i__ - 1 + j * c_dim1];
	    c__[i__ - 1 + j * c_dim1] = c__[k + j * c_dim1];
/* L240: */
	    c__[k + j * c_dim1] = t;
	}
L250:
	if (! wntv) {
	    goto L270;
	}
	i__2 = *nrv;
	for (j = 1; j <= i__2; ++j) {
	    t = v[j + (i__ - 1) * v_dim1];
	    v[j + (i__ - 1) * v_dim1] = v[j + k * v_dim1];
/* L260: */
	    v[j + k * v_dim1] = t;
	}
L270:
	;
    }
/*     END OF ORDERING ALGORITHM. */

    if (fail) {
	*ipass = 2;
    }
    return 0;
} /* qrbd_ */


/* Subroutine */ int mfeout_(real *a, integer *mda, integer *m, integer *n, 
	integer *names, integer *mode)
{
    /* Initialized data */

    static integer maxcol = 7;
    static struct {
	char e_1[4];
	integer e_2;
	} equiv_221 = { "    ", 0 };

#define iblank (*(integer *)&equiv_221)

    static struct {
	char e_1[8];
	integer e_2;
	} equiv_222 = { " COLSOLN", 0 };

#define ihead ((integer *)&equiv_222)


    /* Format strings */
    static char fmt_70[] = "(\002 V-MATRIX OF THE SINGULAR VALUE DECOMPOSITI"
	    "ON\002,\002 OF A*D.\002/\002 (ELEMENTS OF V SCALED UP BY A FACTO"
	    "R OF 10**4)\002)";
    static char fmt_80[] = "(\002 SEQUENCE OF CANDIDATE SOLUTIONS, X\002)";
    static char fmt_90[] = "(\002 \002,11x,8(6x,a4,i4,1x)/1x)";
    static char fmt_100[] = "(1x,i3,6x,4p8f15.4)";
    static char fmt_110[] = "(1x,i3,8x,8e15.6)";

    /* System generated locals */
    integer a_dim1, a_offset, i__1, i__2;

    /* Builtin functions */
    integer s_wsfe(cilist *), e_wsfe(void), do_fio(integer *, char *, ftnlen);

    /* Local variables */
    static integer i__, j, j1, j2, name__, ncol, last, nblock;
    static logical notblk;

    /* Fortran I/O blocks */
    static cilist io___208 = { 0, 9, 0, fmt_70, 0 };
    static cilist io___209 = { 0, 9, 0, fmt_80, 0 };
    static cilist io___215 = { 0, 9, 0, fmt_90, 0 };
    static cilist io___219 = { 0, 9, 0, fmt_100, 0 };
    static cilist io___220 = { 0, 9, 0, fmt_110, 0 };


/*     C.L.LAWSON AND R.J.HANSON, SOLVING LEAST SQUARES PROBLEMS, */
/*     PRENTICE-HALL, 1974. */
/*         SUBROUTINE FOR MATRIX OUTPUT WITH LABELING. */

/*     A( )     MATRIX TO BE OUTPUT */
/*              MDA   FIRST DIMENSION OF A ARRAY */
/*              M     NO. OF ROWS IN A MATRIX */
/*              N     NO. OF COLS IN A MATRIX */
/*     NAMES()  ARRAY OF NAMES.  IF NAMES(1) = 1H , THE REST */
/*              OF THE NAMES() ARRAY WILL BE IGNORED. */
/*     MODE     =1 FOR 4P8F15.0 FORMAT FOR V MATRIX. */
/*              =2 FOR 8E15.8   FORMAT FOR CANDIDATE SOLUTIONS. */

    /* Parameter adjustments */
    --names;
    a_dim1 = *mda;
    a_offset = 1 + a_dim1;
    a -= a_offset;

    /* Function Body */

    if (*m <= 0 || *n <= 0) {
	return 0;
    }
    notblk = names[1] != iblank;

    if (*mode == 2) {
	goto L10;
    }
    s_wsfe(&io___208);
    e_wsfe();
    goto L20;
L10:
    s_wsfe(&io___209);
    e_wsfe();
L20:

    nblock = *n / maxcol;
    last = *n - nblock * maxcol;
    ncol = maxcol;
    j1 = 1;

/*                           MAIN LOOP STARTS HERE */

L30:
    if (nblock > 0) {
	goto L40;
    }
    if (last <= 0) {
	return 0;
    }
    ncol = last;
    last = 0;

L40:
    j2 = j1 + ncol - 1;
    s_wsfe(&io___215);
    i__1 = j2;
    for (j = j1; j <= i__1; ++j) {
	do_fio(&c__1, (char *)&ihead[*mode - 1], (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&j, (ftnlen)sizeof(integer));
    }
    e_wsfe();

    i__1 = *m;
    for (i__ = 1; i__ <= i__1; ++i__) {
	name__ = iblank;
	if (notblk) {
	    name__ = names[i__];
	}

	if (*mode == 2) {
	    goto L50;
	}
	s_wsfe(&io___219);
	do_fio(&c__1, (char *)&i__, (ftnlen)sizeof(integer));
	i__2 = j2;
	for (j = j1; j <= i__2; ++j) {
	    do_fio(&c__1, (char *)&a[i__ + j * a_dim1], (ftnlen)sizeof(real));
	}
	e_wsfe();
	goto L60;
L50:
	s_wsfe(&io___220);
	do_fio(&c__1, (char *)&i__, (ftnlen)sizeof(integer));
	i__2 = j2;
	for (j = j1; j <= i__2; ++j) {
	    do_fio(&c__1, (char *)&a[i__ + j * a_dim1], (ftnlen)sizeof(real));
	}
	e_wsfe();
L60:
	;
    }

    j1 += maxcol;
    --nblock;
    goto L30;

} /* mfeout_ */

#undef ihead
#undef iblank


/* Subroutine */ int funnel_(real *a, integer *mda, integer *n)
{
    /* System generated locals */
    integer a_dim1, a_offset, i__1, i__2;

    /* Builtin functions */
    integer s_wsue(cilist *), do_uio(integer *, char *, ftnlen), e_wsue(void);

    /* Local variables */
    static integer i__, j, k;
    static real v[900];

    /* Fortran I/O blocks */
    static cilist io___226 = { 0, 10, 0, 0, 0 };


    /* Parameter adjustments */
    a_dim1 = *mda;
    a_offset = 1 + a_dim1;
    a -= a_offset;

    /* Function Body */
    i__1 = *n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	i__2 = *n;
	for (j = 1; j <= i__2; ++j) {
/* L20: */
	    v[j - 1] = a[i__ + j * a_dim1];
	}
	s_wsue(&io___226);
	i__2 = *n;
	for (k = 1; k <= i__2; ++k) {
	    do_uio(&c__1, (char *)&v[k - 1], (ftnlen)sizeof(real));
	}
	e_wsue();
/* L10: */
    }
    return 0;
} /* funnel_ */

/* Subroutine */ int constr_(integer *mstart, real *b, integer *nsubf, 
	integer *jw, integer *nrec, integer *nmech, real *syn)
{
    /* Format strings */
    static char fmt_612[] = "(1x,\002DO YOU WANT TO ADD ON SMOOTHING OR MINI"
	    "MIZATION\002,/,1x,\002CONSTRAINTS TO THE DISLOCATION AMPLITUDE, "
	    "1=YES 0=NO\002)";
    static char fmt_613[] = "(\002FIRST ORDER DIFFERENCE SMOOTHING OF DISLOC"
	    "ATION\002,/,1x,\002AMPLITUDES, 1=YES 0=NO\002)";
    static char fmt_614[] = "(1x,\002HOW MANY SUBFAULTS ARE THERE DOWN THE D"
	    "IP AND\002,/,1x,\002ALONG THE FAULT STRIKE\002)";
    static char fmt_616[] = "(1x,\002ENTER FIRST ORDER DIFFERENCE SMOOTHING "
	    "WEIGHT\002)";
    static char fmt_619[] = "(1x,\002MINIMIZATION OF DISLOCATION AMPLITUDE"
	    "S\002,/,1x,\0021=YES, 0=NO\002)";
    static char fmt_620[] = "(1x,\002ENTER DISLOCATION MINIMIZATION WEIGH"
	    "T\002)";
    static char fmt_6[] = "(1x,\002DO YOU WANT RUPTURE TIME CONSTRAINT EQUAT"
	    "IONS\002,/,1x,\002ADDED, 1=YES 0=NO\002)";
    static char fmt_8[] = "(1x,\002FIRST ORDER DIFFERENCE CONSTRAINT ON RUPT"
	    "URE\002,/,1x,\002TIMES, 1=YES 0=NO\002)";
    static char fmt_12[] = "(1x,\002HOW MANY SUBFAULTS ARE THERE DOWN THE DI"
	    "P AND\002,/,1x,\002ALONG THE FAULT STRIKE\002)";
    static char fmt_42[] = "(1x,\002WRONG NUMBER OF SUBFAULTS\002)";
    static char fmt_10[] = "(1x,\002ENTER FIRST ORDER DIFFERENCE WEIGHT\002)";
    static char fmt_11[] = "(1x,\002MINIMIZATION CONSTRAINT ON RUPTURE TIME"
	    "S\002,/,1x,\0021=YES 0=NO\002)";
    static char fmt_13[] = "(1x,\002ENTER MINIMIZATION WEIGHT\002)";
    static char fmt_14[] = "(1x,\002DO YOU WANT TRIGGER TIME CONSTRAINT EQUA"
	    "TIONS\002,/,1x,\002ADDED, 1=YES 0=NO\002)";
    static char fmt_16[] = "(1x,\002CONSTRAINT WILL BE ADDED TO HAVE EQUAL T"
	    "RIGGER\002,/,1x,\002TIMES FOR ALL COMPONENTS OF A GIVEN STATION."
	    " ENTER\002,/,1x,\002WEIGHT AND NUMBER OF COMPONENTS (OR RECORDS)"
	    " PER STATION\002)";
    static char fmt_17[] = "(1x,\002MINIMIZATION CONSTRAINT ON TRIGGER TIMES"
	    ", 1=YES\002,/,1x,\0020=NO\002)";
    static char fmt_18[] = "(1x,\002ENTER MINIMIZATION WEIGHT\002)";
    static char fmt_40[] = "(1x,\002THE NUMBER OF ROWS ADDED TO THE A MATRIX"
	    " IN\002,/,1x,\002SUBROUTINE CONSTR IS \002,i6)";
    static char fmt_37[] = "(1x,\002THE TOTAL NUMBER OF ROWS IN THE A MATRIX"
	    " IS \002,i6)";
    static char fmt_38[] = "(1x,\002THE DIMENSION OF THE A MATRIX, \002,i6"
	    ",\002 ,IS NOT\002,/,1x,\002EQUAL TO THE TOTAL NUMBER OF ROWS...."
	    "STOP\002)";

    /* System generated locals */
    integer i__1;

    /* Builtin functions */
    integer s_wsfe(cilist *), e_wsfe(void), s_rsle(cilist *), do_lio(integer *
	    , integer *, char *, ftnlen), e_rsle(void);
    /* Subroutine */ int s_stop(char *, ftnlen);
    integer do_fio(integer *, char *, ftnlen);

    /* Local variables */
    static integer i__, k, ic, mm, nn, ifod, mend, idls, imin, numc;
    static real trgw;
    static integer iloc1, iloc2, ident, ncomp, nsubh, istep, nsubv;
    static real wtmin, wtsmh;
    static integer nsubff, irupdf, nrowad, itrgeq, itrgmn, icount, irupeq;
    static real rupdfw;
    static integer irupmn;
    static real trgmnw;
    static integer numzer;
    static real rupmnw;

    /* Fortran I/O blocks */
    static cilist io___229 = { 0, 6, 0, fmt_612, 0 };
    static cilist io___230 = { 0, 5, 0, 0, 0 };
    static cilist io___232 = { 0, 6, 0, fmt_613, 0 };
    static cilist io___233 = { 0, 5, 0, 0, 0 };
    static cilist io___235 = { 0, 6, 0, fmt_614, 0 };
    static cilist io___236 = { 0, 5, 0, 0, 0 };
    static cilist io___239 = { 0, 6, 0, fmt_616, 0 };
    static cilist io___240 = { 0, 5, 0, 0, 0 };
    static cilist io___242 = { 0, 6, 0, fmt_619, 0 };
    static cilist io___243 = { 0, 5, 0, 0, 0 };
    static cilist io___245 = { 0, 6, 0, fmt_620, 0 };
    static cilist io___246 = { 0, 5, 0, 0, 0 };
    static cilist io___248 = { 0, 6, 0, fmt_6, 0 };
    static cilist io___249 = { 0, 5, 0, 0, 0 };
    static cilist io___251 = { 0, 6, 0, fmt_8, 0 };
    static cilist io___252 = { 0, 5, 0, 0, 0 };
    static cilist io___254 = { 0, 6, 0, fmt_12, 0 };
    static cilist io___255 = { 0, 5, 0, 0, 0 };
    static cilist io___257 = { 0, 6, 0, fmt_42, 0 };
    static cilist io___258 = { 0, 6, 0, fmt_10, 0 };
    static cilist io___259 = { 0, 5, 0, 0, 0 };
    static cilist io___261 = { 0, 6, 0, fmt_11, 0 };
    static cilist io___262 = { 0, 5, 0, 0, 0 };
    static cilist io___264 = { 0, 6, 0, fmt_13, 0 };
    static cilist io___265 = { 0, 5, 0, 0, 0 };
    static cilist io___267 = { 0, 6, 0, fmt_14, 0 };
    static cilist io___268 = { 0, 5, 0, 0, 0 };
    static cilist io___270 = { 0, 6, 0, fmt_16, 0 };
    static cilist io___271 = { 0, 5, 0, 0, 0 };
    static cilist io___274 = { 0, 6, 0, fmt_17, 0 };
    static cilist io___275 = { 0, 5, 0, 0, 0 };
    static cilist io___277 = { 0, 6, 0, fmt_18, 0 };
    static cilist io___278 = { 0, 5, 0, 0, 0 };
    static cilist io___293 = { 0, 6, 0, fmt_40, 0 };
    static cilist io___294 = { 0, 6, 0, fmt_37, 0 };
    static cilist io___295 = { 0, 6, 0, fmt_38, 0 };



/*     NMECH...NUMBER OF DIFFERENT MECHANISMS PER SUBFAULT (1 OR 2) */
/*     NREC....TOTAL NUMBER OF RECORDS IN INVERSION */
/*     NSUBF...TOTAL NUMBER OF SUBFAULTS */
/*     MSTART..NUMBER OF ROWS IN 'A' MATRIX UPON ENTERING SUBROUTINE */
/*     JW......NUMBER OF TIME WINDOWS */
/*     M.......NUMBER OF ROWS IN 'A' MATRIX UPON EXITING SUBROUTINE */
/*     N.......NUMBER OF COLUMNS IN 'A' MATRIX */

    /* Parameter adjustments */
    --syn;
    --b;

    /* Function Body */
    ic = *mstart + 1;
    s_wsfe(&io___229);
    e_wsfe();
    s_rsle(&io___230);
    do_lio(&c__3, &c__1, (char *)&idls, (ftnlen)sizeof(integer));
    e_rsle();
    if (idls == 0) {
	goto L46;
    }
    s_wsfe(&io___232);
    e_wsfe();
    s_rsle(&io___233);
    do_lio(&c__3, &c__1, (char *)&ifod, (ftnlen)sizeof(integer));
    e_rsle();
    if (ifod == 0) {
	goto L47;
    }
    s_wsfe(&io___235);
    e_wsfe();
    s_rsle(&io___236);
    do_lio(&c__3, &c__1, (char *)&nsubv, (ftnlen)sizeof(integer));
    do_lio(&c__3, &c__1, (char *)&nsubh, (ftnlen)sizeof(integer));
    e_rsle();
    s_wsfe(&io___239);
    e_wsfe();
    s_rsle(&io___240);
    do_lio(&c__4, &c__1, (char *)&wtsmh, (ftnlen)sizeof(real));
    e_rsle();
L47:
    s_wsfe(&io___242);
    e_wsfe();
    s_rsle(&io___243);
    do_lio(&c__3, &c__1, (char *)&imin, (ftnlen)sizeof(integer));
    e_rsle();
    if (imin == 0) {
	goto L46;
    }
    s_wsfe(&io___245);
    e_wsfe();
    s_rsle(&io___246);
    do_lio(&c__4, &c__1, (char *)&wtmin, (ftnlen)sizeof(real));
    e_rsle();
L46:
    s_wsfe(&io___248);
    e_wsfe();
    s_rsle(&io___249);
    do_lio(&c__3, &c__1, (char *)&irupeq, (ftnlen)sizeof(integer));
    e_rsle();
    if (irupeq == 0) {
	goto L7;
    }
    s_wsfe(&io___251);
    e_wsfe();
    s_rsle(&io___252);
    do_lio(&c__3, &c__1, (char *)&irupdf, (ftnlen)sizeof(integer));
    e_rsle();
    if (irupdf == 0) {
	goto L9;
    }
    s_wsfe(&io___254);
    e_wsfe();
    s_rsle(&io___255);
    do_lio(&c__3, &c__1, (char *)&nsubv, (ftnlen)sizeof(integer));
    do_lio(&c__3, &c__1, (char *)&nsubh, (ftnlen)sizeof(integer));
    e_rsle();
    nsubff = nsubv * nsubh;
    if (nsubff != *nsubf) {
	s_wsfe(&io___257);
	e_wsfe();
	s_stop("", (ftnlen)0);
    }
    s_wsfe(&io___258);
    e_wsfe();
    s_rsle(&io___259);
    do_lio(&c__4, &c__1, (char *)&rupdfw, (ftnlen)sizeof(real));
    e_rsle();
L9:
    s_wsfe(&io___261);
    e_wsfe();
    s_rsle(&io___262);
    do_lio(&c__3, &c__1, (char *)&irupmn, (ftnlen)sizeof(integer));
    e_rsle();
    if (irupmn == 0) {
	goto L7;
    }
    s_wsfe(&io___264);
    e_wsfe();
    s_rsle(&io___265);
    do_lio(&c__4, &c__1, (char *)&rupmnw, (ftnlen)sizeof(real));
    e_rsle();
L7:
    s_wsfe(&io___267);
    e_wsfe();
    s_rsle(&io___268);
    do_lio(&c__3, &c__1, (char *)&itrgeq, (ftnlen)sizeof(integer));
    e_rsle();
    if (itrgeq == 0) {
	goto L15;
    }
    s_wsfe(&io___270);
    e_wsfe();
    s_rsle(&io___271);
    do_lio(&c__4, &c__1, (char *)&trgw, (ftnlen)sizeof(real));
    do_lio(&c__3, &c__1, (char *)&ncomp, (ftnlen)sizeof(integer));
    e_rsle();
    s_wsfe(&io___274);
    e_wsfe();
    s_rsle(&io___275);
    do_lio(&c__3, &c__1, (char *)&itrgmn, (ftnlen)sizeof(integer));
    e_rsle();
    if (itrgmn == 0) {
	goto L15;
    }
    s_wsfe(&io___277);
    e_wsfe();
    s_rsle(&io___278);
    do_lio(&c__4, &c__1, (char *)&trgmnw, (ftnlen)sizeof(real));
    e_rsle();
L15:
    nn = *nsubf * *nmech;
    if (idls == 0) {
	goto L121;
    }
    if (imin == 0) {
	goto L72;
    }
    nn = *nsubf * *nmech * *jw;
    ident = 1;
    i__1 = nn;
    for (k = 1; k <= i__1; ++k) {
	for (i__ = 1; i__ <= 200; ++i__) {
	    syn[i__] = 0.f;
/* L74: */
	    if (i__ == ident) {
		syn[i__] = wtmin;
	    }
	}
	for (i__ = 1; i__ <= 200; ++i__) {
/* L84: */
	    all_1.a[ic + i__ * 13300 - 13301] = syn[i__];
	}
	++ic;
	++ident;
/* L73: */
    }
L72:
    if (ifod == 0) {
	goto L121;
    }
    mm = (*nsubf - nsubv) * *nmech * *jw;
    if (mm == 0) {
	goto L75;
    }
    numzer = nsubv * *nmech * *jw - 1;
    iloc1 = 1;
    iloc2 = iloc1 + numzer + 1;
    i__1 = mm;
    for (k = 1; k <= i__1; ++k) {
	for (i__ = 1; i__ <= 200; ++i__) {
	    syn[i__] = 0.f;
	    if (i__ == iloc1) {
		syn[i__] = wtsmh;
	    }
/* L77: */
	    if (i__ == iloc2) {
		syn[i__] = -wtsmh;
	    }
	}
	for (i__ = 1; i__ <= 200; ++i__) {
/* L85: */
	    all_1.a[ic + i__ * 13300 - 13301] = syn[i__];
	}
	++ic;
	++iloc1;
	++iloc2;
/* L76: */
    }
L75:
    mm = (*nsubf - nsubh) * *nmech * *jw;
    if (mm == 0) {
	goto L121;
    }
    numzer = *nmech * *jw - 1;
    iloc1 = 1;
    iloc2 = iloc1 + numzer + 1;
    icount = 0;
    istep = *nmech * *jw * nsubv - *nmech * *jw;
    i__1 = mm;
    for (k = 1; k <= i__1; ++k) {
	++icount;
	for (i__ = 1; i__ <= 200; ++i__) {
	    syn[i__] = 0.f;
	    if (i__ == iloc1) {
		syn[i__] = wtsmh;
	    }
/* L81: */
	    if (i__ == iloc2) {
		syn[i__] = -wtsmh;
	    }
	}
	for (i__ = 1; i__ <= 200; ++i__) {
/* L86: */
	    all_1.a[ic + i__ * 13300 - 13301] = syn[i__];
	}
	++ic;
	++iloc1;
	++iloc2;
	if (icount == istep) {
	    goto L82;
	}
	goto L83;
L82:
	iloc1 += *nmech * *jw;
	iloc2 += *nmech * *jw;
	icount = 0;
L83:
/* L79: */
	;
    }
L121:
    if (irupeq == 0) {
	goto L20;
    }
    if (irupdf == 0) {
	goto L21;
    }
    mm = *nsubf - nsubv;
    if (mm == 0) {
	goto L55;
    }
    numzer = nsubv - 1;
    iloc1 = nn + 1;
    iloc2 = iloc1 + numzer + 1;
    i__1 = mm;
    for (k = 1; k <= i__1; ++k) {
	for (i__ = 1; i__ <= 200; ++i__) {
	    syn[i__] = 0.f;
	    if (i__ == iloc1) {
		syn[i__] = rupdfw;
	    }
/* L57: */
	    if (i__ == iloc2) {
		syn[i__] = -rupdfw;
	    }
	}
	for (i__ = 1; i__ <= 200; ++i__) {
/* L19: */
	    all_1.a[ic + i__ * 13300 - 13301] = syn[i__];
	}
	++iloc1;
	++iloc2;
/* L56: */
	++ic;
    }
L55:
    mm = *nsubf - nsubh;
    if (mm == 0) {
	goto L21;
    }
    numzer = 0;
    iloc1 = nn + 1;
    iloc2 = iloc1 + numzer + 1;
    icount = 0;
    istep = nsubv - 1;
    i__1 = mm;
    for (k = 1; k <= i__1; ++k) {
	++icount;
	for (i__ = 1; i__ <= 200; ++i__) {
	    syn[i__] = 0.f;
	    if (i__ == iloc1) {
		syn[i__] = rupdfw;
	    }
/* L61: */
	    if (i__ == iloc2) {
		syn[i__] = -rupdfw;
	    }
	}
	for (i__ = 1; i__ <= 200; ++i__) {
/* L22: */
	    all_1.a[ic + i__ * 13300 - 13301] = syn[i__];
	}
	++iloc1;
	++iloc2;
	if (icount == istep) {
	    goto L62;
	}
	goto L63;
L62:
	++iloc1;
	++iloc2;
	icount = 0;
L63:
/* L59: */
	++ic;
    }
L21:
    if (irupmn == 0) {
	goto L20;
    }
    ident = nn + 1;
    i__1 = *nsubf;
    for (k = 1; k <= i__1; ++k) {
	for (i__ = 1; i__ <= 200; ++i__) {
	    syn[i__] = 0.f;
/* L54: */
	    if (i__ == ident) {
		syn[i__] = rupmnw;
	    }
	}
	for (i__ = 1; i__ <= 200; ++i__) {
/* L23: */
	    all_1.a[ic + i__ * 13300 - 13301] = syn[i__];
	}
	++ident;
/* L53: */
	++ic;
    }
L20:
    if (itrgeq == 0) {
	goto L25;
    }
    iloc1 = nn + *nsubf + 1;
    iloc2 = iloc1 + 1;
    if (ncomp == 1) {
	goto L26;
    }
    if (ncomp == 3) {
	goto L27;
    }
    numc = *nrec / 2;
    i__1 = numc;
    for (k = 1; k <= i__1; ++k) {
	for (i__ = 1; i__ <= 200; ++i__) {
	    syn[i__] = 0.f;
	    if (i__ == iloc1) {
		syn[i__] = trgw;
	    }
/* L29: */
	    if (i__ == iloc2) {
		syn[i__] = -trgw;
	    }
	}
	for (i__ = 1; i__ <= 200; ++i__) {
/* L30: */
	    all_1.a[ic + i__ * 13300 - 13301] = syn[i__];
	}
	iloc1 += 2;
	iloc2 += 2;
/* L28: */
	++ic;
    }
    goto L26;
L27:
    numc = *nrec;
    icount = 0;
    i__1 = numc;
    for (k = 1; k <= i__1; ++k) {
	for (i__ = 1; i__ <= 200; ++i__) {
	    syn[i__] = 0.f;
	    if (i__ == iloc1) {
		syn[i__] = trgw;
	    }
/* L32: */
	    if (i__ == iloc2) {
		syn[i__] = -trgw;
	    }
	}
	for (i__ = 1; i__ <= 200; ++i__) {
/* L33: */
	    all_1.a[ic + i__ * 13300 - 13301] = syn[i__];
	}
	++icount;
	++ic;
	if (icount == 1) {
	    ++iloc2;
	}
	if (icount == 2) {
	    ++iloc1;
	}
	if (icount == 3) {
	    iloc1 += 2;
	    iloc2 += 2;
	    icount = 0;
	}
/* L31: */
    }
L26:
    if (itrgmn == 0) {
	goto L25;
    }
    ident = nn + *nsubf + 1;
    i__1 = *nrec;
    for (k = 1; k <= i__1; ++k) {
	for (i__ = 1; i__ <= 200; ++i__) {
	    syn[i__] = 0.f;
/* L35: */
	    if (i__ == ident) {
		syn[i__] = trgmnw;
	    }
	}
	for (i__ = 1; i__ <= 200; ++i__) {
/* L36: */
	    all_1.a[ic + i__ * 13300 - 13301] = syn[i__];
	}
	++ident;
/* L34: */
	++ic;
    }
L25:
    mend = ic - 1;
    nrowad = mend - *mstart;
    s_wsfe(&io___293);
    do_fio(&c__1, (char *)&nrowad, (ftnlen)sizeof(integer));
    e_wsfe();
    s_wsfe(&io___294);
    do_fio(&c__1, (char *)&mend, (ftnlen)sizeof(integer));
    e_wsfe();
    if (mend != 13300) {
	s_wsfe(&io___295);
	do_fio(&c__1, (char *)&c__13300, (ftnlen)sizeof(integer));
	e_wsfe();
	s_stop("", (ftnlen)0);
    }
    ic = *mstart + 1;
    i__1 = mend;
    for (i__ = ic; i__ <= i__1; ++i__) {
/* L39: */
	b[i__] = 0.f;
    }
    return 0;
} /* constr_ */

