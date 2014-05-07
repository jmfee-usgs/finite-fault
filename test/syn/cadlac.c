/* cadlac.f -- translated by f2c (version 20030320).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include "f2c.h"

/* Common Block Declarations */

struct {
    integer ibug;
} bug_;

#define bug_1 bug_

struct {
    integer iprnt;
} ipr_;

#define ipr_1 ipr_

struct {
    integer ipap;
} paper_;

#define paper_1 paper_

struct {
    integer itest;
    real xlng, ylng;
    integer ierror;
} complo_;

#define complo_1 complo_

struct {
    real dip[1], rake[1], strk[1], fmnt[1], tlag[1], xc[1], yc[1], hs[1];
    integer lis[1];
} faul1_;

#define faul1_1 faul1_

struct {
    real xss[8192]	/* was [1][8192] */;
} floose_;

#define floose_1 floose_

struct rinv_1_ {
    real ri[16], dis[16];
};

#define rinv_1 (*(struct rinv_1_ *) &rinv_)

struct {
    real pp[4096];
    integer ncomp, mode;
} sconv_;

#define sconv_1 sconv_

struct {
    real del[50], az[50], p[50], cre[50], sre[50];
} stat_;

#define stat_1 stat_

struct {
    real xs[16384]	/* was [4][4096] */;
} stim_;

#define stim_1 stim_

struct {
    doublereal c__[10], s[10], d__[10], th[10], rcsq[10], rssq[10];
    real dpth[10];
} stuff_;

#define stuff_1 stuff_

union {
    struct {
	integer lp[10], ls[10], jo;
    } _1;
    struct {
	integer lp[10], ls[10], ll;
    } _2;
} travel_;

#define travel_1 (travel_._1)
#define travel_2 (travel_._2)

struct {
    real far__[105600]	/* was [220][120][4] */, weight[26400]	/* was [220][
	    120][1] */, tmlag[26400]	/* was [220][120] */;
} rat_;

#define rat_1 rat_

struct {
    integer nx[1], ny[1], ndx[1], ndy[1], ih[1], jh[1];
    real rv[1], dsx[1], dsy[1], dtd[1];
} tail_;

#define tail_1 tail_

struct {
    integer nsub[1], ibx1[300]	/* was [300][1] */, iex1[300]	/* was [300][
	    1] */;
    real by1[300]	/* was [300][1] */, ey1[300]	/* was [300][1] */;
    integer jby1[600]	/* was [300][2][1] */, jey1[600]	/* was [300][
	    2][1] */, msub1[1], ib[300]	/* was [300][1] */, ie[300]	/* 
	    was [300][1] */;
} subf_;

#define subf_1 subf_

struct {
    integer icon;
} point_;

#define point_1 point_

struct {
    integer ngdrx, ngdry;
    real xmin, xmax, ymin, ymax, zmin, zmax, clat, clon;
} junk_;

#define junk_1 junk_

struct {
    real tf[16384]	/* was [4096][4] */, xzk[4096];
} timefn_;

#define timefn_1 timefn_

struct {
    integer mpoin;
    real deltm, tzero;
} bin_;

#define bin_1 bin_

struct {
    real x1[8192], xs1[8192], xs2[4096]	/* was [1][4096] */, x[4096], xs3[
	    4096];
} big_;

#define big_1 big_

union {
    struct {
	real po[1000], to[1000], am[1000];
	integer lfinal, ntype[250];
    } _1;
    struct {
	real po[1000], to[1000], am[1000];
	integer l, ntype[250];
    } _2;
} ans_;

#define ans_1 (ans_._1)
#define ans_2 (ans_._2)

union {
    struct {
	real c1[10], s1[10], d1[10];
    } _1;
    struct {
	real c__[10], s[10], d__[10];
    } _2;
} orst_;

#define orst_1 (orst_._1)
#define orst_2 (orst_._2)

struct {
    integer na[12500]	/* was [250][50] */, nray[12500]	/* was [250][
	    50] */, ndr[250], ncount[250], love;
} rays_;

#define rays_1 rays_

struct {
    integer iidt;
} fixup_;

#define fixup_1 fixup_

/* Initialized data */

struct {
    real e_1[32];
    } rinv_ = { 8.4e-5f, 7.95e-5f, 7.65e-5f, 7.4e-5f, 7.15e-5f, 6.9e-5f, 
	    6.7e-5f, 6.35e-5f, 5.95e-5f, 5.6e-5f, 5.3e-5f, 5e-5f, 4.7e-5f, 
	    4.4e-5f, 4.1e-5f, 3.85e-5f, 30.f, 32.5f, 35.f, 37.5f, 40.f, 42.5f,
	     45.f, 50.f, 55.f, 60.f, 65.f, 70.f, 75.f, 80.f, 85.f, 90.f };


/* Table of constant values */

static integer c__3 = 3;
static integer c__1 = 1;
static integer c__10 = 10;
static real c_b115 = -1.f;
static integer c__4 = 4;
static real c_b259 = 1.f;
static integer c_n1 = -1;
static doublereal c_b581 = .5;
static integer c__2 = 2;
static integer c__9 = 9;

/*  CADILLAC - FAR-FIELD TELESEISMIC BODY WAVE CODE FOR COMPUTING THE RESPONSE */
/*  OF FINITE FAULTS LOCATED WITHIN LAYERED SPACES.  THIS CODE IS A MODIFICATION */
/*  OF DISCONH WHICH WAS MODIFIED BY HEATON FROM THE CODE DISCON WHICH WAS */
/*  MODIFIED BY CIPAR FROM A CODE WHICH WAS ORIGINALLY WRITTEN BY LANGSTON. */
/*  THEREFORE ANY COMPLAINTS SHOULD BE DIRECTED TO GOD. */

/*     TQ=RATIO T/Q USED IN FUTTERMAN'S Q OPERATOR */
/*     NCOMP=1,VERTICAL ;=2, RADIAL; =3,TANGENTIAL. */
/*     MODE=1,P;=2,SV;=3,SH. */
/*     SCALE IS IN SEC/MM CONTROLS PLOT SCALE. */
/*     IPRPL CONTROLS THE PLOTTER TO PLOT EXTRA PLOTS. NORMALLY EQUAL TO 0. */
/*     IF IPRPL=0, ONLY S*Q*I*RAYS (FINAL ANSWER) IS PLOTTED. */
/*     IF IPRPL=1, INST, AND S*Q*I*RAYS FOR EACH SOURCE AND */
/*       FINAL ANSWER ARE PLOTTED. */
/*     IBUG=1, PLOTS INTERMEDIATE STEPS FOR DEBUGGING PURPOSES.  NORMALLY */
/*             IBUG=0. */
/*     DT=TIME POINT SEPARATION. */
/*     NP=# OF POINTS...NPL=LOG2(NP),USED FOR COOLB */
/*     REMEMBER THE NUMBER OF REAL PLUS IMAG. POINTS IS 2*NP. */
/*     FOR LONG-PERIOD BODY WAVES, NP=512, NPL=9, DT=0.2 */
/*     CURRENTLY (DEC. 20, 1989) THE ARRAYS ARE SET UP FOR NP=4096. */
/*     XIN CONTAINS THE INSTRUMENT IN THE TIME DOMAIN. */
/*     FQW CONTAINS THE Q-OPERATOR IN THE FREQUENCY DOMAIN. */
/*     AMPLITUDE SCALING OF DISCONH HAS BEEN CHECKED AND CORRECTED */
/*          ON FEBRUARY 27, 1980. */
/*     SCALING IS IN UNITS OF MICRONS, ZERO-TO-PEAK, FOR AN INSTRUMENT */
/*          OF UNIT MAGNIFICATION. */


/*                INTERACTIVE INPUT */


/*     ISAVEH=1, WRITES DISPLACEMENTS FOR EACH FAULT SEGMENT (NSORCE */
/*               OF THEM) TO DISK FILE DISPL. */
/*           =0, DISPLACEMENTS NOT SAVED. */
/*     INSTRH=1, LONG PERIOD WWSSN INSTRUMENT RESPONSE IS USED. READ */
/*               FROM FILE INSTRYLONG. */
/*           =2, SHORT PERIOD WWSSN INSTRUMENT RESPONSE IS USED. READ */
/*               FROM FILE INSTRYSHORT. */
/*     ITIMEH=1, PROGRAM COMPUTES AND PLOTS ONLY THE SMOOTHED FAR */
/*               FIELD TIME FUNCTIONS. ALL OTHER INPUT IS THE SAME. */
/*           =0, NORMAL OPERATION MODE OF THE PROGRAM. */
/*     TQ= VALUE OF T* */
/*     NCOMP=1, VERTICAL */
/*          =2, RADIAL */
/*          =3, TRANSVERSE */
/*     MODE=1, P-WAVE */
/*         =2, SV-WAVE */
/*         =3, SH-WAVE. */
/*     NSORCE= NUMBER OF DIFFERENT FAULTS TO BE CONSIDERED. */
/*              MAXIMUM IS MSOR. NSORCE=0 TERMINATES THE */
/*             PROGRAM. */
/*     EPI= EVENT ID. */
/*     MODL= MODEL ID. */
/*     STRIKE, DIP, RAKE= STRIKE, DIP, AND RAKE OF EACH FAULT. */
/*     MOMENT= MOMENT OF EACH SOURCE (X10**26 DYNE-CM) */
/*     TLAG= TIME DELAY OF EACH SOURCE. */
/*     XC= NORTH COMPONENT OF RELATIVE LOCATION OF TOP CENTER OF FAULT. */
/*     YC= EAST COMPONENT OF RELATIVE LOCATION OF TOP CENTER OF FAULT. */
/*     DT1, DT2, DT3= RISE, TOP, AND FALL OF TRAPEZOID DESCRIBING */
/*                    SOURCE RUPTURE CHARACTER AT A GIVEN POINT ON */
/*                    EACH FAULT. */
/*     NSORCE SETS OF THE FOLLOWING INPUT DATA. */
/*     NUMBER OF WEIGHTS ALONG STRIKE FOR A GIVEN FAULT SEGMENT. */
/*     NUMBER OF WEIGHTS DOWN DIP FOR A GIVEN FAULT SEGMENT. */
/*     NUMBER OF POINT SOURCES TO INTERPOLATE TO BETWEEN EACH INPUT */
/*          WEIGHT ALONG THE STRIKE OF THE FAULT. */
/*     NUMBER OF POINT SOURCES TO INTERPOLATE TO BETWEEN EACH INPUT */
/*          WEIGHT DOWN THE DIP OF THE FAULT. */
/*          HORIZONTAL NUMBERING OF POINT SOURCES INCREASES IN THE */
/*          DIRECTION OF THE STRIKE OF THE FAULT. VERTICAL NUMBERING */
/*          OF POINT SOURCES INCREASES DOWN DIP. FOR A FAULT SEGMENT */
/*          ABOVE THE HYPOCENTER, THE VERTICAL NUMBER */
/*          IS THE TOTAL NUMBER OF SOURCES VERTICALLY DOWN THE FAULT */
/*          SEGMENT IN QUESTION PLUS THE NUMBER TO REACH THE FIRST */
/*          POINT OF THE FAULT SEGMENT TO RUPTURE FROM THE HYPOCENTER. */
/*          THE ORIGIN OF COORDINATES FOR NUMBERING IS ALWAYS IN */
/*          THE UPPER LEFT HAND CORNER OF EACH FAULT SEGMENT. IF THE */
/*          HYPOCENTER IS ABOVE THE UPPER LEFT HAND CORNER OF THE */
/*          FAULT, THE VERTICAL INDEX IS NEGATIVE. HORIZONTAL INDEX */
/*          IS ALWAYS POSITIVE. */
/*     RUPTURE VELOCITY */
/*     ZERO TERMINATES PROGRAM. */




/*       THIS VERSION OF THE PROGRAM AUTOMATICALLY HANDLES FINITE FAULTS */
/*       WHICH EXTEND BETWEEN SEVERAL LAYERS.  THE FINITENESS AND THE */
/*       LAYERING ARE HANDLED IN A WAY WHICH IS TRANSPARENT TO THE USER. */
/*       THIS VERSION WAS DEVELOPED IN FEBRUARY 1982 BY HEATON. */


/*       THE WEIGHT FILE IS INPUTTED IN TERMS OF RELATIVE AMPLITUDE OF */
/*       SLIP AS A FUNCTION OF LOCATION ON THE FAULT.  THIS WEIGHTING */
/*       IS THEN TURNED INTO ABSOLUTE SLIP WHICH IS DETERMINED BY THE */
/*       INPUT MOMENT AND THE FAULT DIMENSIONS.  CONTOUR MAPS CAN BE */
/*       MADE OF THE ABSOLUTE SLIP FILE BY USING MINSTER'S CONTOUR PROGRAM */
/*       ON THE FILES CONTOUR01, CONTOUR02, ETC.  THE SLIP VALUES ARE GIVEN */
/*       IN CENTIMETERS. */


/*       IN THIS VERSION, THE RAYS ARE NOT READ FROM THE INSTRY FILE. */
/*       THE RAYS ARE READ FROM RAYUFD WHICH SHOULD BE A SUBUFD OF */
/*       THE UFD WHICH IS RUNNING THIS PROGRAM.  THE RAYS ARE CONTAINED */
/*       IN FILES WHICH ARE NAMED, RAY.M.N.L, WHERE M=MODE, N=NUMBER OF */
/*       LAYERS IN THE SOURCE REGION, AND L=THE LAYER WITH THE SOURCE. */
/* Main program */ int MAIN__(void)
{
    /* Initialized data */

    static struct {
	char e_1[16];
	integer e_2;
	} equiv_228 = { "INST S*Q SQI   Q", 0 };

#define inst ((integer *)&equiv_228)


    /* Format strings */
    static char fmt_600[] = "(1x,\002CADILLAC - TELESEISMIC DISLOCATION SOUR"
	    "CE PROGRAM \002)";
    static char fmt_111[] = "(1x,//)";
    static char fmt_690[] = "(3x,\002ISAVEH, =1, SAVE DISPL., =0, DON'T SAVE"
	    " DISPL. \002)";
    static char fmt_691[] = "(3x,\002INSTRH, =1, LP RESP., =2, SP RESP.\002)";
    static char fmt_692[] = "(3x,\002ITIMEH, =1, COMPUTE TIME FUNC. ONLY, =0"
	    ", NORM. OPER.\002)";
    static char fmt_526[] = "(3x,\002IGDSN=1,  INSTRUMENT ADDED BY SEISRESP2"
	    ". CADILLAC\002,/,1x,\002            INSTRUMENT RESPONSE VALUES N"
	    "OT USED\002,/,1x,\002       =0,  INSTRUMENT RESPONSE TAKEN FROM "
	    "CADILLAC\002,/,1x,\002            INSTRUMENT FILE.\002)";
    static char fmt_528[] = "(3x,\002ITFEX=1,  AN EXTERNAL TIME FUNCTION IS "
	    "READ IN TO\002,/,1x,\002            REPLACE THE TIME FUNCTIONS C"
	    "ALCULATED BY DIANE\002,/,1x,\002       =0,  NORMAL OPERATION OF "
	    "PROGRAM\002)";
    static char fmt_6931[] = "(1x,\002GIVE VALUES OF ISAVEH, INSTRH, ITIMEH,"
	    " IGDSN, ITFEX\002)";
    static char fmt_693[] = "(3x,\002ISAVEH= \002,i2,\002  INSTRH= \002,i2"
	    ",\002 ITIMEH= \002,i2,\002  IGDSN= \002,i2,\002  ITFEX= \002,i2)";
    static char fmt_4009[] = "(1x,\002DO YOU WANT BINARY OUTPUT FILE (1 OR"
	    " 0)\002)";
    static char fmt_102[] = "(f5.0,2i5,2f10.0,3i5)";
    static char fmt_103[] = "(3x,\002DT =\002,f10.3,4x,\002NP =\002,i5,3x"
	    ",\002SCALE=\002f10.3,\002  RINC=\002f10.5,\002  NPL=\002i3,\002 "
	    " IPRPL=\0023i3)";
    static char fmt_110[] = "(1x,10e10.3)";
    static char fmt_100[] = "(12a4,2x,10a2,f5.0,i5)";
    static char fmt_101[] = "(3x,12a4,2x,10a2,\002  DTI=\002f7.3,\002  NPI"
	    "=\002i4)";
    static char fmt_773[] = "(\002 NOW READ INSTRUMENT RESPONSE \002)";
    static char fmt_620[] = "(2x,\002GEOMETRICAL SPREADING FACTOR \002)";
    static char fmt_105[] = "(16(1x,f6.2))";
    static char fmt_255[] = "(i10)";
    static char fmt_109[] = "(1x,i5,1x,\002STATIONS\002)";
    static char fmt_200[] = "(1x,2x,\002ID\002,11x,\002DEL\002,7x,\002AZ\002"
	    ",7x,\002P\002,8x,\002CRE\002,6x,\002SRE\002)";
    static char fmt_107[] = "(a4,6x,5f10.0)";
    static char fmt_108[] = "(1x,a4,6x,5f10.3)";
    static char fmt_256[] = "(4f10.0)";
    static char fmt_257[] = "(1x,5x,\002LAYERED EARTH MODEL\002//)";
    static char fmt_258[] = "(1x,5x,\002C\002,13x,\002S\002,13x,\002D\002,13"
	    "x,\002TH\002)";
    static char fmt_259[] = "(1x,4(f10.3,4x))";
    static char fmt_529[] = "(1x,\002ENTER 0...IF YOU WANT A CONSTANT T STAR"
	    " MODEL\002,/,1x,\002ENTER 1...IF YOU WANT MINSTER ATTENUATION OP"
	    "ERATOR\002,/,1x,\002ENTER 2...IF YOU WANT CHOYS VARIABLE T STAR "
	    "MODEL\002)";
    static char fmt_530[] = "(1x,\002ENTER THE VALUE OF T STAR (T/Q)\002)";
    static char fmt_531[] = "(1x,\002ENTER VALUES OF T STAR, TAUBM, TAULM, T"
	    "RAVEL TIME.\002,/,1x,\002ENTER ZERO FOR DEFAULT VALUES OF 1.0, 1"
	    "000., .01, AND 600.\002)";
    static char fmt_532[] = "(1x,\002ENTER 1 FOR LOW ATTENUATION CHOY MODE"
	    "L\002,/,1x,\002ENTER 2 FOR HIGH ATTENUATION CHOY MODEL\002)";
    static char fmt_300[] = "(a)";
    static char fmt_301[] = "(i5,f5.0)";
    static char fmt_302[] = "(5e15.7)";
    static char fmt_740[] = "(1x,\002AREA UNDER Q OPERATOR= \002,f12.4)";
    static char fmt_614[] = "(2x,\002NCOMP  =1, VERTICAL, =2, RADIAL, =3, TR"
	    "ANSVERSE \002)";
    static char fmt_615[] = "(2x,\002MODE  =1, P-WAVE, =2, SV-WAVE, =3, SH-W"
	    "AVE \002)";
    static char fmt_601[] = "(1x,\002NCOMP,MODE\002)";
    static char fmt_602[] = "(5x,\002T/Q= \002f10.4,\002  NCOMP= \002i3,\002"
	    "  MODE= \002i3)";
    static char fmt_603[] = "(1x,\002HOW MANY SOURCES?\002)";
    static char fmt_6031[] = "(1x,\002NSORCE=\002)";
    static char fmt_513[] = "(1x,\002EVNT MODL\002)";
    static char fmt_514[] = "(a4,1x,a4)";
    static char fmt_5141[] = "(1x,\002CHANGE FAULT PARAMETERS?\002)";
    static char fmt_604[] = "(1x,\002STRIKE    DIP       RAKE\002)";
    static char fmt_6041[] = "(1x,\002THE DIP CANT BE NEGATIVE, BUT MAY BE G"
	    "REATER THAN 90.\002)";
    static char fmt_6042[] = "(1x,\002IF DIP>90, THEN RAKE=+90 IS STILL THRU"
	    "ST FAULT.\002)";
    static char fmt_5011[] = "(1x,\002CHANGE MOMENT?\002)";
    static char fmt_605[] = "(1x,\002  MOMENT (*E+26)\002)";
    static char fmt_5051[] = "(1x,\002CHANGE TLAG, XC, YC?\002)";
    static char fmt_606[] = "(1x,\002TLAG      XC        YC\002)";
    static char fmt_5081[] = "(1x,\002CHANGE TIME FUNCTION?\002)";
    static char fmt_700[] = "(1x,\002 Enter 1 for TRAPEZOID, 2 for DIGITIZED"
	    " TIME FUNCTION\002)";
    static char fmt_609[] = "(1x,\002DT1  DT2  DT3\002)";
    static char fmt_515[] = "(4x,\002EVENT= \002a4,\002  MODEL= \002a4)";
    static char fmt_607[] = "(1x,\002SOURCE  STRIKE   DIP    RAKE     MOMENT"
	    "   TLAG    \002,\002XC     YC    DT1    DT2    DT3\002)";
    static char fmt_608[] = "(5x,i2,2x,3f7.2,e12.5,6f6.2)";
    static char fmt_5211[] = "(1x,\002ARE YOU READY?\002)";
    static char fmt_9000[] = "(1x,10e12.4)";
    static char fmt_611[] = "(1x,\002THINKING\002)";
    static char fmt_616[] = "(3x,\002STATION\002i3,1x,a4,\002  P=\002f7.4)";
    static char fmt_4761[] = "(1x,\002STRK,DIP,AZ\002,3f12.6)";
    static char fmt_984[] = "(1x,\002ENTER FILE NAME WITH EXTERNAL TIME FUNC"
	    "TION\002)";
    static char fmt_985[] = "(a)";
    static char fmt_979[] = "(i10,f10.5)";
    static char fmt_980[] = "(8f10.0)";
    static char fmt_983[] = "(1x,\002DTEX= \002,f10.5,\002 DT= \002,f10.5"
	    ",\002 STOP \002)";
    static char fmt_132[] = "(i5,f10.5,a4)";
    static char fmt_131[] = "(10e12.4)";
    static char fmt_4013[] = "(1x,\002THE EARLIEST ARRIVAL AT\002,a4,\002 CO"
	    "MES \002,f10.5,\002 SECONDS AFTER THE BEGINNING OF THE RECORD"
	    "\002)";
    static char fmt_4014[] = "(1x,a4,f10.5)";
    static char fmt_112[] = "(1x,\002TOTAL RESPONSE, WITH INSTRUMENT, FOR ST"
	    "ATION\002,a4)";
    static char fmt_612[] = "(1x,\002GOOD BYE \002)";

    /* System generated locals */
    integer i__1, i__2, i__3, i__4;
    real r__1, r__2;
    olist o__1;
    cllist cl__1;

    /* Builtin functions */
    integer f_open(olist *), s_wsfe(cilist *), e_wsfe(void), s_rsle(cilist *),
	     do_lio(integer *, integer *, char *, ftnlen), e_rsle(void), 
	    do_fio(integer *, char *, ftnlen), s_rsfe(cilist *), e_rsfe(void),
	     s_wsue(cilist *), do_uio(integer *, char *, ftnlen), e_wsue(void)
	    , f_clos(cllist *);
    /* Subroutine */ int s_stop(char *, ftnlen);

    /* Local variables */
    static integer i__, j, k, l, m, n;
    static real q, d1, d2, d3, t1;
    static integer id[50];
    static real fl[1], pc;
    static integer kj, i45;
    static real dt;
    static integer np;
    static real tq;
    static integer nq;
    static real xr, xi, yr, yi;
    static integer ns;
    static real sn, se;
    static integer kp;
    static real dt1[1], dt2[1], dt3[1];
    static integer np2;
    static real xs4[4096];
    static integer nch, epi;
    static real ddt, dti, aaz;
    static integer ijk, npi;
    static real sdp;
    static integer npl;
    static real fqw[8200], xin[8192], tau;
    static integer los, nex, nsu;
    static real vpx, vsx;
    static char ifg1[80];
    static integer nch1, npi1;
    static real area, ddip;
    static integer kbin, modl;
    static real rinc, dtch, pamp, conr, coni, hypd[1];
    static integer xinm[20];
    static shortint frmt[10];
    static real xhyp[1];
    static integer lwrt;
    static char type__[80];
    static real xamp, yamp;
    extern /* Subroutine */ int trap_(real *, real *, integer *, integer *, 
	    real *, integer *), fttq_(integer *, real *, real *, real *, 
	    integer *, real *, real *, real *);
    static integer icip;
    extern /* Subroutine */ int scon_(real *, real *, integer *, integer *, 
	    real *, real *, real *), jill_(integer *, real *, real *, real *, 
	    real *, integer *);
    static integer list;
    static real dtex, smax;
    extern /* Subroutine */ int diane_(real *, real *, real *, real *, real *,
	     integer *, real *, real *, integer *, integer *, real *);
    static real scale, qarea, difdt, picam;
    extern /* Subroutine */ int coolb_(integer *, real *, real *);
    static integer igdsn;
    static real xname, yname, taubm;
    static integer ichoy;
    extern /* Subroutine */ int contf_(real *, real *, real *, real *, real *,
	     real *, real *, integer *, integer *, integer *, real *, real *, 
	    integer *, integer *, real *), slave_(integer *, real *, real *, 
	    integer *, real *, real *, real *, real *, real *, real *);
    static integer itfex;
    extern /* Subroutine */ int convf_(real *, integer *, integer *, real *, 
	    integer *, integer *), ttlag_(integer *, integer *, real *, 
	    integer *, real *, real *);
    static real taulm;
    static integer iprpl, npnew, nstat;
    extern /* Subroutine */ int recev_(integer *, integer *, integer *, 
	    integer *);
    static real xsamp;
    static integer itmty;
    static real sstrk;
    static integer isaveh, itimeh;
    static real xspace;
    static integer iatten;
    extern /* Subroutine */ int filter_(real *, real *, integer *, integer *);
    static real dtsave;
    static integer nsorce;
    static real moment;
    extern /* Subroutine */ int subflt_(integer *, real *), interp_(integer *,
	     real *, real *, integer *, real *, real *, integer *), diswht_(
	    integer *, integer *, integer *, real *, integer *, real *);
    static integer instrh;
    static real tfirst, tstart;

    /* Fortran I/O blocks */
    static cilist io___12 = { 0, 6, 0, fmt_600, 0 };
    static cilist io___13 = { 0, 3, 0, fmt_600, 0 };
    static cilist io___14 = { 0, 3, 0, fmt_111, 0 };
    static cilist io___15 = { 0, 6, 0, fmt_690, 0 };
    static cilist io___16 = { 0, 6, 0, fmt_691, 0 };
    static cilist io___17 = { 0, 6, 0, fmt_692, 0 };
    static cilist io___18 = { 0, 6, 0, fmt_526, 0 };
    static cilist io___19 = { 0, 6, 0, fmt_528, 0 };
    static cilist io___20 = { 0, 3, 0, fmt_690, 0 };
    static cilist io___21 = { 0, 3, 0, fmt_691, 0 };
    static cilist io___22 = { 0, 3, 0, fmt_692, 0 };
    static cilist io___23 = { 0, 3, 0, fmt_526, 0 };
    static cilist io___24 = { 0, 3, 0, fmt_528, 0 };
    static cilist io___25 = { 0, 6, 0, fmt_6931, 0 };
    static cilist io___26 = { 0, 5, 0, 0, 0 };
    static cilist io___32 = { 0, 3, 0, fmt_693, 0 };
    static cilist io___33 = { 0, 6, 0, fmt_4009, 0 };
    static cilist io___34 = { 0, 5, 0, 0, 0 };
    static cilist io___36 = { 0, 2, 0, fmt_102, 0 };
    static cilist io___43 = { 0, 3, 0, fmt_103, 0 };
    static cilist io___44 = { 0, 6, 0, fmt_103, 0 };
    static cilist io___47 = { 0, 2, 0, fmt_100, 0 };
    static cilist io___52 = { 0, 3, 0, fmt_101, 0 };
    static cilist io___53 = { 0, 6, 0, fmt_101, 0 };
    static cilist io___54 = { 0, 6, 0, fmt_773, 0 };
    static cilist io___55 = { 0, 2, 0, (char *)frmt, 0 };
    static cilist io___57 = { 0, 3, 0, fmt_110, 0 };
    static cilist io___62 = { 0, 3, 0, fmt_111, 0 };
    static cilist io___63 = { 0, 3, 0, fmt_620, 0 };
    static cilist io___64 = { 0, 3, 0, fmt_105, 0 };
    static cilist io___65 = { 0, 3, 0, fmt_110, 0 };
    static cilist io___66 = { 0, 2, 0, fmt_255, 0 };
    static cilist io___68 = { 0, 3, 0, fmt_109, 0 };
    static cilist io___69 = { 0, 6, 0, fmt_109, 0 };
    static cilist io___70 = { 0, 12, 0, 0, 0 };
    static cilist io___71 = { 0, 3, 0, fmt_200, 0 };
    static cilist io___72 = { 0, 6, 0, fmt_200, 0 };
    static cilist io___73 = { 0, 2, 0, fmt_107, 0 };
    static cilist io___75 = { 0, 3, 0, fmt_108, 0 };
    static cilist io___76 = { 0, 6, 0, fmt_108, 0 };
    static cilist io___77 = { 0, 2, 0, fmt_255, 0 };
    static cilist io___78 = { 0, 2, 0, fmt_256, 0 };
    static cilist io___79 = { 0, 3, 0, fmt_111, 0 };
    static cilist io___80 = { 0, 3, 0, fmt_257, 0 };
    static cilist io___81 = { 0, 6, 0, fmt_257, 0 };
    static cilist io___82 = { 0, 3, 0, fmt_258, 0 };
    static cilist io___83 = { 0, 6, 0, fmt_258, 0 };
    static cilist io___84 = { 0, 6, 0, fmt_259, 0 };
    static cilist io___85 = { 0, 3, 0, fmt_259, 0 };
    static cilist io___86 = { 0, 6, 0, fmt_529, 0 };
    static cilist io___87 = { 0, 5, 0, 0, 0 };
    static cilist io___89 = { 0, 6, 0, fmt_530, 0 };
    static cilist io___90 = { 0, 5, 0, 0, 0 };
    static cilist io___92 = { 0, 6, 0, fmt_531, 0 };
    static cilist io___93 = { 0, 5, 0, 0, 0 };
    static cilist io___97 = { 0, 6, 0, fmt_532, 0 };
    static cilist io___98 = { 0, 5, 0, 0, 0 };
    static cilist io___100 = { 0, 14, 0, fmt_300, 0 };
    static cilist io___102 = { 0, 3, 0, fmt_300, 0 };
    static cilist io___103 = { 0, 14, 0, fmt_301, 0 };
    static cilist io___106 = { 0, 14, 0, fmt_302, 0 };
    static cilist io___108 = { 0, 14, 0, fmt_302, 0 };
    static cilist io___114 = { 0, 3, 0, fmt_740, 0 };
    static cilist io___116 = { 0, 3, 0, fmt_111, 0 };
    static cilist io___117 = { 0, 3, 0, fmt_614, 0 };
    static cilist io___118 = { 0, 6, 0, fmt_614, 0 };
    static cilist io___119 = { 0, 3, 0, fmt_615, 0 };
    static cilist io___120 = { 0, 6, 0, fmt_615, 0 };
    static cilist io___121 = { 0, 6, 0, fmt_601, 0 };
    static cilist io___122 = { 0, 5, 0, 0, 0 };
    static cilist io___123 = { 0, 3, 0, fmt_602, 0 };
    static cilist io___133 = { 0, 6, 0, fmt_603, 0 };
    static cilist io___134 = { 0, 6, 0, fmt_6031, 0 };
    static cilist io___135 = { 0, 5, 0, 0, 0 };
    static cilist io___137 = { 0, 6, 0, fmt_513, 0 };
    static cilist io___138 = { 0, 5, 0, fmt_514, 0 };
    static cilist io___139 = { 0, 6, 0, fmt_5141, 0 };
    static cilist io___140 = { 0, 5, 0, 0, 0 };
    static cilist io___142 = { 0, 6, 0, fmt_604, 0 };
    static cilist io___143 = { 0, 6, 0, fmt_6041, 0 };
    static cilist io___144 = { 0, 6, 0, fmt_6042, 0 };
    static cilist io___145 = { 0, 5, 0, 0, 0 };
    static cilist io___146 = { 0, 6, 0, fmt_5011, 0 };
    static cilist io___147 = { 0, 5, 0, 0, 0 };
    static cilist io___148 = { 0, 6, 0, fmt_605, 0 };
    static cilist io___149 = { 0, 5, 0, 0, 0 };
    static cilist io___150 = { 0, 6, 0, fmt_5051, 0 };
    static cilist io___151 = { 0, 5, 0, 0, 0 };
    static cilist io___152 = { 0, 6, 0, fmt_606, 0 };
    static cilist io___153 = { 0, 5, 0, 0, 0 };
    static cilist io___154 = { 0, 6, 0, fmt_5081, 0 };
    static cilist io___155 = { 0, 5, 0, 0, 0 };
    static cilist io___156 = { 0, 6, 0, fmt_700, 0 };
    static cilist io___157 = { 0, 5, 0, 0, 0 };
    static cilist io___159 = { 0, 6, 0, fmt_609, 0 };
    static cilist io___160 = { 0, 5, 0, 0, 0 };
    static cilist io___165 = { 0, 6, 0, fmt_515, 0 };
    static cilist io___166 = { 0, 6, 0, fmt_607, 0 };
    static cilist io___167 = { 0, 6, 0, fmt_608, 0 };
    static cilist io___168 = { 0, 6, 0, fmt_5211, 0 };
    static cilist io___169 = { 0, 5, 0, 0, 0 };
    static cilist io___170 = { 0, 3, 0, fmt_111, 0 };
    static cilist io___171 = { 0, 3, 0, fmt_515, 0 };
    static cilist io___172 = { 0, 3, 0, fmt_607, 0 };
    static cilist io___173 = { 0, 3, 0, fmt_608, 0 };
    static cilist io___174 = { 0, 3, 0, fmt_111, 0 };
    static cilist io___178 = { 0, 6, 0, fmt_611, 0 };
    static cilist io___181 = { 0, 3, 0, fmt_616, 0 };
    static cilist io___182 = { 0, 6, 0, fmt_616, 0 };
    static cilist io___187 = { 0, 6, 0, fmt_4761, 0 };
    static cilist io___200 = { 0, 6, 0, fmt_984, 0 };
    static cilist io___201 = { 0, 5, 0, fmt_985, 0 };
    static cilist io___203 = { 0, 15, 0, fmt_979, 0 };
    static cilist io___206 = { 0, 15, 0, fmt_980, 0 };
    static cilist io___208 = { 0, 6, 0, fmt_983, 0 };
    static cilist io___211 = { 0, 3, 0, fmt_9000, 0 };
    static cilist io___213 = { 0, 7, 0, fmt_132, 0 };
    static cilist io___214 = { 0, 7, 0, fmt_131, 0 };
    static cilist io___220 = { 0, 12, 0, 0, 0 };
    static cilist io___221 = { 0, 12, 0, 0, 0 };
    static cilist io___223 = { 0, 3, 0, fmt_4013, 0 };
    static cilist io___224 = { 0, 13, 0, fmt_4014, 0 };
    static cilist io___225 = { 0, 3, 0, fmt_112, 0 };
    static cilist io___226 = { 0, 3, 0, fmt_110, 0 };
    static cilist io___227 = { 0, 6, 0, fmt_612, 0 };


/*     COMMON/PLOTD/IFIRST,EPI,MODL,XNAME,YNAME,XAMP,YAMP,XSPACE */
/*    2 ,YSPACE */
    moment = 1e26f;
/*     L IS PLOTTER CONTROL. */
    l = 1;
    paper_1.ipap = 0;
    epi = inst[0];
    modl = inst[0];
/*     OPEN UNIT 3 FOR WRITING TO FILE 'OUTPUT'. */
    o__1.oerr = 0;
    o__1.ounit = 3;
    o__1.ofnmlen = 10;
    o__1.ofnm = "CADOUT.DAT";
    o__1.orl = 0;
    o__1.osta = "NEW";
    o__1.oacc = 0;
    o__1.ofm = 0;
    o__1.oblnk = 0;
    f_open(&o__1);
/*     OPEN UNIT 8 FOR PLOT FILE 'PLOT'. */
/*     OPEN(UNIT=8,FILE='PLOT.DAT',STATUS='NEW',CARRIAGECONTROL='LIST') */
/*     CALL PLOTS(53,0,8) */
/*     CALL SPEED(20) */
    point_1.icon = 0;
    xname = 0.f;
    yname = 0.f;
    xamp = 0.f;
    yamp = 0.f;
    xspace = 0.f;
    lwrt = 0;
    bin_1.tzero = 0.f;

    s_wsfe(&io___12);
    e_wsfe();
    s_wsfe(&io___13);
    e_wsfe();
    s_wsfe(&io___14);
    e_wsfe();
    s_wsfe(&io___15);
    e_wsfe();
    s_wsfe(&io___16);
    e_wsfe();
    s_wsfe(&io___17);
    e_wsfe();
    s_wsfe(&io___18);
    e_wsfe();
    s_wsfe(&io___19);
    e_wsfe();
    s_wsfe(&io___20);
    e_wsfe();
    s_wsfe(&io___21);
    e_wsfe();
    s_wsfe(&io___22);
    e_wsfe();
    s_wsfe(&io___23);
    e_wsfe();
    s_wsfe(&io___24);
    e_wsfe();
    s_wsfe(&io___25);
    e_wsfe();
    s_rsle(&io___26);
    do_lio(&c__3, &c__1, (char *)&isaveh, (ftnlen)sizeof(integer));
    do_lio(&c__3, &c__1, (char *)&instrh, (ftnlen)sizeof(integer));
    do_lio(&c__3, &c__1, (char *)&itimeh, (ftnlen)sizeof(integer));
    do_lio(&c__3, &c__1, (char *)&igdsn, (ftnlen)sizeof(integer));
    do_lio(&c__3, &c__1, (char *)&itfex, (ftnlen)sizeof(integer));
    e_rsle();
    s_wsfe(&io___32);
    do_fio(&c__1, (char *)&isaveh, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&instrh, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&itimeh, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&igdsn, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&itfex, (ftnlen)sizeof(integer));
    e_wsfe();
    s_wsfe(&io___33);
    e_wsfe();
    s_rsle(&io___34);
    do_lio(&c__3, &c__1, (char *)&kbin, (ftnlen)sizeof(integer));
    e_rsle();
    o__1.oerr = 0;
    o__1.ounit = 13;
    o__1.ofnmlen = 10;
    o__1.ofnm = "CADARR.DAT";
    o__1.orl = 0;
    o__1.osta = "UNKNOWN";
    o__1.oacc = 0;
    o__1.ofm = 0;
    o__1.oblnk = 0;
    f_open(&o__1);
    if (kbin == 1) {
	o__1.oerr = 0;
	o__1.ounit = 12;
	o__1.ofnmlen = 10;
	o__1.ofnm = "CADBIN.DAT";
	o__1.orl = 0;
	o__1.osta = "NEW";
	o__1.oacc = "SEQUENTIAL";
	o__1.ofm = "UNFORMATTED";
	o__1.oblnk = 0;
	f_open(&o__1);
    }
    if (instrh == 1) {
	o__1.oerr = 0;
	o__1.ounit = 2;
	o__1.ofnmlen = 10;
	o__1.ofnm = "INLONG.DAT";
	o__1.orl = 0;
	o__1.osta = "OLD";
	o__1.oacc = 0;
	o__1.ofm = 0;
	o__1.oblnk = 0;
	f_open(&o__1);
    }
    if (instrh == 2) {
	o__1.oerr = 0;
	o__1.ounit = 2;
	o__1.ofnmlen = 11;
	o__1.ofnm = "INSHORT.DAT";
	o__1.orl = 0;
	o__1.osta = "OLD";
	o__1.oacc = 0;
	o__1.ofm = 0;
	o__1.oblnk = 0;
	f_open(&o__1);
    }
    if (isaveh == 1) {
	o__1.oerr = 0;
	o__1.ounit = 7;
	o__1.ofnmlen = 9;
	o__1.ofnm = "DISPL.DAT";
	o__1.orl = 0;
	o__1.osta = "NEW";
	o__1.oacc = 0;
	o__1.ofm = 0;
	o__1.oblnk = 0;
	f_open(&o__1);
    }
    s_rsfe(&io___36);
    do_fio(&c__1, (char *)&dt, (ftnlen)sizeof(real));
    do_fio(&c__1, (char *)&np, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&npl, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&scale, (ftnlen)sizeof(real));
    do_fio(&c__1, (char *)&rinc, (ftnlen)sizeof(real));
    do_fio(&c__1, (char *)&iprpl, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&bug_1.ibug, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&ipr_1.iprnt, (ftnlen)sizeof(integer));
    e_rsfe();
    s_wsfe(&io___43);
    do_fio(&c__1, (char *)&dt, (ftnlen)sizeof(real));
    do_fio(&c__1, (char *)&np, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&scale, (ftnlen)sizeof(real));
    do_fio(&c__1, (char *)&rinc, (ftnlen)sizeof(real));
    do_fio(&c__1, (char *)&npl, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&iprpl, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&bug_1.ibug, (ftnlen)sizeof(integer));
    e_wsfe();
/* L110: */
    s_wsfe(&io___44);
    do_fio(&c__1, (char *)&dt, (ftnlen)sizeof(real));
    do_fio(&c__1, (char *)&np, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&scale, (ftnlen)sizeof(real));
    do_fio(&c__1, (char *)&rinc, (ftnlen)sizeof(real));
    do_fio(&c__1, (char *)&npl, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&iprpl, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&bug_1.ibug, (ftnlen)sizeof(integer));
    e_wsfe();
/*     X IS THE EQUAL INTERVAL ABSCISSA FOR GIVEN DT. */
    if (instrh == 2) {
	dt = .01f;
    }
    np2 = np << 1;
    i__1 = np;
    for (i__ = 1; i__ <= i__1; ++i__) {
/* L5: */
	big_1.x[i__ - 1] = dt * (i__ - 1);
    }

/*        READING IN INSTRUMENT */

    if (igdsn == 1) {
	goto L525;
    }
    s_rsfe(&io___47);
    for (i__ = 1; i__ <= 12; ++i__) {
	do_fio(&c__1, (char *)&xinm[i__ - 1], (ftnlen)sizeof(integer));
    }
    do_fio(&c__10, (char *)&frmt[0], (ftnlen)sizeof(shortint));
    do_fio(&c__1, (char *)&dti, (ftnlen)sizeof(real));
    do_fio(&c__1, (char *)&npi, (ftnlen)sizeof(integer));
    e_rsfe();
    s_wsfe(&io___52);
    for (i__ = 1; i__ <= 12; ++i__) {
	do_fio(&c__1, (char *)&xinm[i__ - 1], (ftnlen)sizeof(integer));
    }
    do_fio(&c__10, (char *)&frmt[0], (ftnlen)sizeof(shortint));
    do_fio(&c__1, (char *)&dti, (ftnlen)sizeof(real));
    do_fio(&c__1, (char *)&npi, (ftnlen)sizeof(integer));
    e_wsfe();
    s_wsfe(&io___53);
    for (i__ = 1; i__ <= 12; ++i__) {
	do_fio(&c__1, (char *)&xinm[i__ - 1], (ftnlen)sizeof(integer));
    }
    do_fio(&c__10, (char *)&frmt[0], (ftnlen)sizeof(shortint));
    do_fio(&c__1, (char *)&dti, (ftnlen)sizeof(real));
    do_fio(&c__1, (char *)&npi, (ftnlen)sizeof(integer));
    e_wsfe();
    s_wsfe(&io___54);
    e_wsfe();
    s_rsfe(&io___55);
    i__1 = npi;
    for (i__ = 1; i__ <= i__1; ++i__) {
	do_fio(&c__1, (char *)&xin[i__ - 1], (ftnlen)sizeof(real));
    }
    e_rsfe();
    s_wsfe(&io___57);
    for (i__ = 1; i__ <= 200; ++i__) {
	do_fio(&c__1, (char *)&xin[i__ - 1], (ftnlen)sizeof(real));
    }
    e_wsfe();
    if (itimeh == 1) {
	goto L133;
    }

/*        INTERPOLATING INSTRUMENT IF NEEDED */
/*        NOTE...TIME STEP FOR WWSSN LONG PERIOD INSTRUMENT IS 0.1 SEC, */
/*        TIME STEP FOR WWSSN SHORT PERIOD INSTRUMENT IS 0.01 SEC, BEST */
/*        NOT TO USE A TIME STEP FOR THE SYNTHETICS MUCH LARGER THAN */
/*        THESE VALUES. */

    t1 = 1e-5f;
    ddt = (r__1 = dt - dti, dabs(r__1));
    if (ddt <= t1) {
	goto L11;
    }
    i__1 = npi;
    for (i__ = 1; i__ <= i__1; ++i__) {
/* L12: */
	big_1.x1[i__ - 1] = dti * (i__ - 1);
    }
    interp_(&npi, big_1.x1, xin, &np, big_1.x, big_1.xs1, &npnew);
    npi = npnew;
    i__1 = npi;
    for (i__ = 1; i__ <= i__1; ++i__) {
/* L13: */
	xin[i__ - 1] = big_1.xs1[i__ - 1];
    }
L11:
    if (npi >= np) {
	goto L25;
    }
    npi1 = npi + 1;
    i__1 = np;
    for (i__ = npi1; i__ <= i__1; ++i__) {
/* L17: */
	xin[i__ - 1] = xin[npi - 1];
    }
    npi = np;
L25:
/*     IF(IPRPL .EQ. +1) CALL SEPLOT(L,NPI,X,XIN,SCALE,INST(1)) */
/*     TRANSFORM INSTRUMENT TO FREQUENCY DOMAIN. */
    np2 = np << 1;
    i__1 = np2;
    for (i__ = 1; i__ <= i__1; ++i__) {
/* L18: */
	big_1.xs1[i__ - 1] = 0.f;
    }
    i__1 = np;
    for (i__ = 1; i__ <= i__1; ++i__) {
/* L19: */
	big_1.xs1[(i__ << 1) - 2] = xin[i__ - 1];
    }
    coolb_(&npl, big_1.xs1, &c_b115);
/*     SCALE FREQUENCY DOMAIN INSTRUMENT RESPONSE. */
    i__1 = np2;
    for (i__ = 1; i__ <= i__1; ++i__) {
/* L23: */
	xin[i__ - 1] = big_1.xs1[i__ - 1] * dt;
    }
L525:
    s_wsfe(&io___62);
    e_wsfe();
/*     CORRECT GEOMETRICAL SPREADING FACTOR FOR SOURCE DEPTH */
    for (i__ = 1; i__ <= 16; ++i__) {
/* L14: */
	rinv_1.ri[i__ - 1] = rinc * rinv_1.ri[i__ - 1];
    }
    s_wsfe(&io___63);
    e_wsfe();
    s_wsfe(&io___64);
    for (i__ = 1; i__ <= 16; ++i__) {
	do_fio(&c__1, (char *)&rinv_1.dis[i__ - 1], (ftnlen)sizeof(real));
    }
    e_wsfe();
    s_wsfe(&io___65);
    for (i__ = 1; i__ <= 16; ++i__) {
	do_fio(&c__1, (char *)&rinv_1.ri[i__ - 1], (ftnlen)sizeof(real));
    }
    e_wsfe();
L133:

/*        READING IN STATION INFORMATION */

    s_rsfe(&io___66);
    do_fio(&c__1, (char *)&nstat, (ftnlen)sizeof(integer));
    e_rsfe();
    s_wsfe(&io___68);
    do_fio(&c__1, (char *)&nstat, (ftnlen)sizeof(integer));
    e_wsfe();
    s_wsfe(&io___69);
    do_fio(&c__1, (char *)&nstat, (ftnlen)sizeof(integer));
    e_wsfe();
    if (kbin == 1) {
	s_wsue(&io___70);
	do_uio(&c__1, (char *)&nstat, (ftnlen)sizeof(integer));
	e_wsue();
    }
    s_wsfe(&io___71);
    e_wsfe();
    s_wsfe(&io___72);
    e_wsfe();
    i__1 = nstat;
    for (i__ = 1; i__ <= i__1; ++i__) {
	s_rsfe(&io___73);
	do_fio(&c__1, (char *)&id[i__ - 1], (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&stat_1.del[i__ - 1], (ftnlen)sizeof(real));
	do_fio(&c__1, (char *)&stat_1.az[i__ - 1], (ftnlen)sizeof(real));
	do_fio(&c__1, (char *)&stat_1.p[i__ - 1], (ftnlen)sizeof(real));
	do_fio(&c__1, (char *)&stat_1.cre[i__ - 1], (ftnlen)sizeof(real));
	do_fio(&c__1, (char *)&stat_1.sre[i__ - 1], (ftnlen)sizeof(real));
	e_rsfe();
	if (stat_1.p[i__ - 1] > 1.f) {
	    stat_1.p[i__ - 1] /= 111.19f;
	}
	s_wsfe(&io___75);
	do_fio(&c__1, (char *)&id[i__ - 1], (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&stat_1.del[i__ - 1], (ftnlen)sizeof(real));
	do_fio(&c__1, (char *)&stat_1.az[i__ - 1], (ftnlen)sizeof(real));
	do_fio(&c__1, (char *)&stat_1.p[i__ - 1], (ftnlen)sizeof(real));
	do_fio(&c__1, (char *)&stat_1.cre[i__ - 1], (ftnlen)sizeof(real));
	do_fio(&c__1, (char *)&stat_1.sre[i__ - 1], (ftnlen)sizeof(real));
	e_wsfe();
	s_wsfe(&io___76);
	do_fio(&c__1, (char *)&id[i__ - 1], (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&stat_1.del[i__ - 1], (ftnlen)sizeof(real));
	do_fio(&c__1, (char *)&stat_1.az[i__ - 1], (ftnlen)sizeof(real));
	do_fio(&c__1, (char *)&stat_1.p[i__ - 1], (ftnlen)sizeof(real));
	do_fio(&c__1, (char *)&stat_1.cre[i__ - 1], (ftnlen)sizeof(real));
	do_fio(&c__1, (char *)&stat_1.sre[i__ - 1], (ftnlen)sizeof(real));
	e_wsfe();
/* L15: */
    }

/*     READ IN EARTH STRUCTURE */

    s_rsfe(&io___77);
    do_fio(&c__1, (char *)&travel_1.jo, (ftnlen)sizeof(integer));
    e_rsfe();
    i__1 = travel_1.jo;
    for (i__ = 1; i__ <= i__1; ++i__) {
/* L31: */
	s_rsfe(&io___78);
	do_fio(&c__1, (char *)&stuff_1.c__[i__ - 1], (ftnlen)sizeof(
		doublereal));
	do_fio(&c__1, (char *)&stuff_1.s[i__ - 1], (ftnlen)sizeof(doublereal))
		;
	do_fio(&c__1, (char *)&stuff_1.d__[i__ - 1], (ftnlen)sizeof(
		doublereal));
	do_fio(&c__1, (char *)&stuff_1.th[i__ - 1], (ftnlen)sizeof(doublereal)
		);
	e_rsfe();
    }
    s_wsfe(&io___79);
    e_wsfe();
    s_wsfe(&io___80);
    e_wsfe();
    s_wsfe(&io___81);
    e_wsfe();
    s_wsfe(&io___82);
    e_wsfe();
    s_wsfe(&io___83);
    e_wsfe();
    i__1 = travel_1.jo;
    for (i__ = 1; i__ <= i__1; ++i__) {
	s_wsfe(&io___84);
	do_fio(&c__1, (char *)&stuff_1.c__[i__ - 1], (ftnlen)sizeof(
		doublereal));
	do_fio(&c__1, (char *)&stuff_1.s[i__ - 1], (ftnlen)sizeof(doublereal))
		;
	do_fio(&c__1, (char *)&stuff_1.d__[i__ - 1], (ftnlen)sizeof(
		doublereal));
	do_fio(&c__1, (char *)&stuff_1.th[i__ - 1], (ftnlen)sizeof(doublereal)
		);
	e_wsfe();
/* L34: */
	s_wsfe(&io___85);
	do_fio(&c__1, (char *)&stuff_1.c__[i__ - 1], (ftnlen)sizeof(
		doublereal));
	do_fio(&c__1, (char *)&stuff_1.s[i__ - 1], (ftnlen)sizeof(doublereal))
		;
	do_fio(&c__1, (char *)&stuff_1.d__[i__ - 1], (ftnlen)sizeof(
		doublereal));
	do_fio(&c__1, (char *)&stuff_1.th[i__ - 1], (ftnlen)sizeof(doublereal)
		);
	e_wsfe();
    }

/*        Q OPERATOR */

    s_wsfe(&io___86);
    e_wsfe();
    s_rsle(&io___87);
    do_lio(&c__3, &c__1, (char *)&iatten, (ftnlen)sizeof(integer));
    e_rsle();
    if (iatten == 0) {
	s_wsfe(&io___89);
	e_wsfe();
	s_rsle(&io___90);
	do_lio(&c__4, &c__1, (char *)&tq, (ftnlen)sizeof(real));
	e_rsle();
    }
    if (iatten == 1) {
	s_wsfe(&io___92);
	e_wsfe();
	s_rsle(&io___93);
	do_lio(&c__4, &c__1, (char *)&tq, (ftnlen)sizeof(real));
	do_lio(&c__4, &c__1, (char *)&taubm, (ftnlen)sizeof(real));
	do_lio(&c__4, &c__1, (char *)&taulm, (ftnlen)sizeof(real));
	do_lio(&c__4, &c__1, (char *)&tau, (ftnlen)sizeof(real));
	e_rsle();
	if (tq == 0.f) {
	    tq = 1.f;
	}
	if (taubm == 0.f) {
	    taubm = 1e3f;
	}
	if (taulm == 0.f) {
	    taulm = .01f;
	}
	if (tau == 0.f) {
	    tau = 600.f;
	}
    }

/*     READ IN CHOY ATTENUATION OPERATOR, INTERPOLATE TO THE SAME TIME */
/*     STEP AS THE SYNTHETICS, AND TRANSFORM INTO THE FREQUENCY DOMAIN. */
/*     NOTE...TIME STEP OF CHOY OPERATOR IS 0.1 SEC, BEST TO NOT USE A */
/*     TIME STEP IN THE SYNTHETICS MUCH LARGER THAN THIS. */

    if (iatten == 2) {
	s_wsfe(&io___97);
	e_wsfe();
	s_rsle(&io___98);
	do_lio(&c__3, &c__1, (char *)&ichoy, (ftnlen)sizeof(integer));
	e_rsle();
	if (ichoy == 1) {
	    o__1.oerr = 0;
	    o__1.ounit = 14;
	    o__1.ofnmlen = 10;
	    o__1.ofnm = "CHOYLO.DAT";
	    o__1.orl = 0;
	    o__1.osta = "OLD";
	    o__1.oacc = 0;
	    o__1.ofm = 0;
	    o__1.oblnk = 0;
	    f_open(&o__1);
	}
	if (ichoy == 2) {
	    o__1.oerr = 0;
	    o__1.ounit = 14;
	    o__1.ofnmlen = 10;
	    o__1.ofnm = "CHOYHI.DAT";
	    o__1.orl = 0;
	    o__1.osta = "OLD";
	    o__1.oacc = 0;
	    o__1.ofm = 0;
	    o__1.oblnk = 0;
	    f_open(&o__1);
	}
	s_rsfe(&io___100);
	do_fio(&c__1, type__, (ftnlen)80);
	e_rsfe();
	s_wsfe(&io___102);
	do_fio(&c__1, type__, (ftnlen)80);
	e_wsfe();
	s_rsfe(&io___103);
	do_fio(&c__1, (char *)&nch, (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&dtch, (ftnlen)sizeof(real));
	e_rsfe();
	s_rsfe(&io___106);
	do_fio(&c__1, (char *)&pamp, (ftnlen)sizeof(real));
	e_rsfe();
	s_rsfe(&io___108);
	i__1 = nch;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    do_fio(&c__1, (char *)&xs4[i__ - 1], (ftnlen)sizeof(real));
	}
	e_rsfe();
	cl__1.cerr = 0;
	cl__1.cunit = 14;
	cl__1.csta = 0;
	f_clos(&cl__1);
	difdt = (r__1 = dtch - dt, dabs(r__1));
	if (difdt < 1e-4f) {
	    goto L310;
	}
	i__1 = np;
	for (i__ = 1; i__ <= i__1; ++i__) {
/* L307: */
	    big_1.x[i__ - 1] = dt * (i__ - 1);
	}
	i__1 = nch;
	for (i__ = 1; i__ <= i__1; ++i__) {
/* L303: */
	    big_1.xs3[i__ - 1] = dtch * (i__ - 1);
	}
	interp_(&nch, big_1.xs3, xs4, &np, big_1.x, big_1.x1, &npnew);
	nch = npnew;
	goto L314;
L310:
	i__1 = nch;
	for (i__ = 1; i__ <= i__1; ++i__) {
/* L312: */
	    big_1.x1[i__ - 1] = xs4[i__ - 1];
	}
L314:
	if (nch >= np) {
	    goto L311;
	}
	nch1 = nch + 1;
	i__1 = np;
	for (i__ = nch1; i__ <= i__1; ++i__) {
/* L313: */
	    big_1.x1[i__ - 1] = big_1.x1[nch - 1];
	}
L311:
	trap_(big_1.x1, big_1.x, &c__1, &nch, xs4, &nq);
	qarea = xs4[nq - 1];
	i__1 = np;
	for (i__ = 1; i__ <= i__1; ++i__) {
/* L739: */
	    big_1.x1[i__ - 1] /= qarea;
	}
	s_wsfe(&io___114);
	do_fio(&c__1, (char *)&qarea, (ftnlen)sizeof(real));
	e_wsfe();
	i__1 = np;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    fqw[(i__ << 1) - 1] = 0.f;
/* L304: */
	    fqw[(i__ << 1) - 2] = big_1.x1[i__ - 1];
	}
	coolb_(&npl, fqw, &c_b115);
	i__1 = np2;
	for (i__ = 1; i__ <= i__1; ++i__) {
/* L306: */
	    fqw[i__ - 1] *= dt;
	}
/*     IF(IPRPL .EQ. 1) CALL SEPLOT(L,NP,X,X1,SCALE,INST(4)) */
	i__1 = nch;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    big_1.xs3[i__ - 1] = 0.f;
/* L308: */
	    xs4[i__ - 1] = 0.f;
	}
	i__1 = np;
	for (i__ = 1; i__ <= i__1; ++i__) {
/* L309: */
	    big_1.x1[i__ - 1] = 0.f;
	}
	goto L134;
    }


    if (itimeh == 1) {
	goto L134;
    }
    s_wsfe(&io___116);
    e_wsfe();
    fttq_(&npl, &dt, &tq, fqw, &iatten, &taubm, &taulm, &tau);
/*     FQW IS FREQUENCY DOMAIN Q-OPERATOR. */
L134:
    s_wsfe(&io___117);
    e_wsfe();
    s_wsfe(&io___118);
    e_wsfe();
    s_wsfe(&io___119);
    e_wsfe();
    s_wsfe(&io___120);
    e_wsfe();
    s_wsfe(&io___121);
    e_wsfe();
    s_rsle(&io___122);
    do_lio(&c__3, &c__1, (char *)&sconv_1.ncomp, (ftnlen)sizeof(integer));
    do_lio(&c__3, &c__1, (char *)&sconv_1.mode, (ftnlen)sizeof(integer));
    e_rsle();
    s_wsfe(&io___123);
    do_fio(&c__1, (char *)&tq, (ftnlen)sizeof(real));
    do_fio(&c__1, (char *)&sconv_1.ncomp, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&sconv_1.mode, (ftnlen)sizeof(integer));
    e_wsfe();
    if (itimeh == 1) {
	goto L135;
    }

/*     CONVOLVE Q-OPERATOR WITH INSTRUMENT */

    if (igdsn == 1) {
	goto L527;
    }
    i__1 = np;
    for (i__ = 1; i__ <= i__1; ++i__) {
	xr = fqw[(i__ << 1) - 2];
	xi = fqw[(i__ << 1) - 1];
	yr = xin[(i__ << 1) - 2];
	yi = xin[(i__ << 1) - 1];
	conr = xr * yr - xi * yi;
	coni = xi * yr + xr * yi;
	fqw[(i__ << 1) - 2] = conr;
	fqw[(i__ << 1) - 1] = coni;
/* L37: */
    }
L527:
/*     FQW IS NOW I*Q IN THE FREQUENCY DOMAIN. */
/*     INTERPOLATE FQW TO DT=0.02 SEC, FOR SHORT-PERIOD RECORDS ONLY. */
    if (instrh == 1) {
	goto L444;
    }
/*     10/10/85 ERROR IN FFT NORMALIZATION CORRECTED FOR SHORT-PERIOD */
/*     SYNTHETICS.  BEFORE THIS DATE SYNTHETICS WERE TOO SMALL BY A */
/*     FACTOR OF 2. */
    dtsave = dt;
    dt = .02f;
    i__1 = np;
    for (i__ = 1; i__ <= i__1; ++i__) {
/* L445: */
	big_1.x[i__ - 1] = dt * (i__ - 1);
    }
    coolb_(&npl, fqw, &c_b259);
    j = 1;
    q = (real) np;
    i__1 = np;
    for (i__ = 1; i__ <= i__1; i__ += 4) {
	fqw[j - 1] = fqw[i__ - 1] / (q * dtsave);
	fqw[j] = 0.f;
/* L446: */
	j += 2;
    }
    i__1 = np2;
    for (i__ = j; i__ <= i__1; ++i__) {
/* L447: */
	fqw[i__ - 1] = 0.f;
    }
    coolb_(&npl, fqw, &c_b115);
    i__1 = np2;
    for (i__ = 1; i__ <= i__1; ++i__) {
/* L657: */
	fqw[i__ - 1] *= dt;
    }
L444:
/*     FQW IS I*Q IN FREQUENCY DOMAIN. */
L135:

/*        READING IN FAULT-PLANE PARAMETERS */
/*        READING IN SOURCE TIME FUNCTIONS */

L77:
    s_wsfe(&io___133);
    e_wsfe();
    o__1.oerr = 0;
    o__1.ounit = 9;
    o__1.ofnmlen = 10;
    o__1.ofnm = "WEIGHT.DAT";
    o__1.orl = 0;
    o__1.osta = "OLD";
    o__1.oacc = 0;
    o__1.ofm = 0;
    o__1.oblnk = 0;
    f_open(&o__1);
    s_wsfe(&io___134);
    e_wsfe();
    s_rsle(&io___135);
    do_lio(&c__3, &c__1, (char *)&nsorce, (ftnlen)sizeof(integer));
    e_rsle();
    if (nsorce == 0) {
	goto L76;
    }
    s_wsfe(&io___137);
    e_wsfe();
    s_rsfe(&io___138);
    do_fio(&c__1, (char *)&modl, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&epi, (ftnlen)sizeof(integer));
    e_rsfe();
    s_wsfe(&io___139);
    e_wsfe();
    s_rsle(&io___140);
    do_lio(&c__3, &c__1, (char *)&icip, (ftnlen)sizeof(integer));
    e_rsle();
    if (icip == 0) {
	goto L501;
    }
    i__1 = nsorce;
    for (i__ = 1; i__ <= i__1; ++i__) {
	s_wsfe(&io___142);
	e_wsfe();
	s_wsfe(&io___143);
	e_wsfe();
	s_wsfe(&io___144);
	e_wsfe();
/* L502: */
	s_rsle(&io___145);
	do_lio(&c__4, &c__1, (char *)&faul1_1.strk[i__ - 1], (ftnlen)sizeof(
		real));
	do_lio(&c__4, &c__1, (char *)&faul1_1.dip[i__ - 1], (ftnlen)sizeof(
		real));
	do_lio(&c__4, &c__1, (char *)&faul1_1.rake[i__ - 1], (ftnlen)sizeof(
		real));
	e_rsle();
    }
L501:
    s_wsfe(&io___146);
    e_wsfe();
    s_rsle(&io___147);
    do_lio(&c__3, &c__1, (char *)&icip, (ftnlen)sizeof(integer));
    e_rsle();
    if (icip == 0) {
	goto L505;
    }
    i__1 = nsorce;
    for (i__ = 1; i__ <= i__1; ++i__) {
	s_wsfe(&io___148);
	e_wsfe();
	s_rsle(&io___149);
	do_lio(&c__4, &c__1, (char *)&faul1_1.fmnt[i__ - 1], (ftnlen)sizeof(
		real));
	e_rsle();
/* L506: */
	faul1_1.fmnt[i__ - 1] *= moment;
    }
L505:
    s_wsfe(&io___150);
    e_wsfe();
    s_rsle(&io___151);
    do_lio(&c__3, &c__1, (char *)&icip, (ftnlen)sizeof(integer));
    e_rsle();
    if (icip == 0) {
	goto L508;
    }
    i__1 = nsorce;
    for (i__ = 1; i__ <= i__1; ++i__) {
	s_wsfe(&io___152);
	e_wsfe();
/* L509: */
	s_rsle(&io___153);
	do_lio(&c__4, &c__1, (char *)&faul1_1.tlag[i__ - 1], (ftnlen)sizeof(
		real));
	do_lio(&c__4, &c__1, (char *)&faul1_1.xc[i__ - 1], (ftnlen)sizeof(
		real));
	do_lio(&c__4, &c__1, (char *)&faul1_1.yc[i__ - 1], (ftnlen)sizeof(
		real));
	e_rsle();
    }
L508:
    s_wsfe(&io___154);
    e_wsfe();
    s_rsle(&io___155);
    do_lio(&c__3, &c__1, (char *)&icip, (ftnlen)sizeof(integer));
    e_rsle();
    if (icip == 0) {
	goto L510;
    }
    s_wsfe(&io___156);
    e_wsfe();
    s_rsle(&io___157);
    do_lio(&c__3, &c__1, (char *)&itmty, (ftnlen)sizeof(integer));
    e_rsle();
    if (itmty == 2) {
	goto L701;
    }
    i__1 = nsorce;
    for (i__ = 1; i__ <= i__1; ++i__) {
	s_wsfe(&io___159);
	e_wsfe();
/* L511: */
	s_rsle(&io___160);
	do_lio(&c__4, &c__1, (char *)&dt1[i__ - 1], (ftnlen)sizeof(real));
	do_lio(&c__4, &c__1, (char *)&dt2[i__ - 1], (ftnlen)sizeof(real));
	do_lio(&c__4, &c__1, (char *)&dt3[i__ - 1], (ftnlen)sizeof(real));
	e_rsle();
    }
    goto L702;
L701:
    contf_(floose_1.xss, xs4, big_1.xs3, big_1.x, fqw, big_1.x1, big_1.xs1, &
	    np, &np2, &npl, &dt, &area, &nsorce, &bug_1.ibug, &scale);
L702:
L510:
    s_wsfe(&io___165);
    do_fio(&c__1, (char *)&epi, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&modl, (ftnlen)sizeof(integer));
    e_wsfe();
    s_wsfe(&io___166);
    e_wsfe();
    s_wsfe(&io___167);
    i__1 = nsorce;
    for (i__ = 1; i__ <= i__1; ++i__) {
	do_fio(&c__1, (char *)&i__, (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&faul1_1.strk[i__ - 1], (ftnlen)sizeof(real));
	do_fio(&c__1, (char *)&faul1_1.dip[i__ - 1], (ftnlen)sizeof(real));
	do_fio(&c__1, (char *)&faul1_1.rake[i__ - 1], (ftnlen)sizeof(real));
	do_fio(&c__1, (char *)&faul1_1.fmnt[i__ - 1], (ftnlen)sizeof(real));
	do_fio(&c__1, (char *)&faul1_1.tlag[i__ - 1], (ftnlen)sizeof(real));
	do_fio(&c__1, (char *)&faul1_1.xc[i__ - 1], (ftnlen)sizeof(real));
	do_fio(&c__1, (char *)&faul1_1.yc[i__ - 1], (ftnlen)sizeof(real));
	do_fio(&c__1, (char *)&dt1[i__ - 1], (ftnlen)sizeof(real));
	do_fio(&c__1, (char *)&dt2[i__ - 1], (ftnlen)sizeof(real));
	do_fio(&c__1, (char *)&dt3[i__ - 1], (ftnlen)sizeof(real));
    }
    e_wsfe();
    s_wsfe(&io___168);
    e_wsfe();
    s_rsle(&io___169);
    do_lio(&c__3, &c__1, (char *)&icip, (ftnlen)sizeof(integer));
    e_rsle();
    if (icip == 0) {
	goto L77;
    }
    s_wsfe(&io___170);
    e_wsfe();
    s_wsfe(&io___171);
    do_fio(&c__1, (char *)&epi, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&modl, (ftnlen)sizeof(integer));
    e_wsfe();
/* L522: */
    s_wsfe(&io___172);
    e_wsfe();
    s_wsfe(&io___173);
    i__1 = nsorce;
    for (i__ = 1; i__ <= i__1; ++i__) {
	do_fio(&c__1, (char *)&i__, (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&faul1_1.strk[i__ - 1], (ftnlen)sizeof(real));
	do_fio(&c__1, (char *)&faul1_1.dip[i__ - 1], (ftnlen)sizeof(real));
	do_fio(&c__1, (char *)&faul1_1.rake[i__ - 1], (ftnlen)sizeof(real));
	do_fio(&c__1, (char *)&faul1_1.fmnt[i__ - 1], (ftnlen)sizeof(real));
	do_fio(&c__1, (char *)&faul1_1.tlag[i__ - 1], (ftnlen)sizeof(real));
	do_fio(&c__1, (char *)&faul1_1.xc[i__ - 1], (ftnlen)sizeof(real));
	do_fio(&c__1, (char *)&faul1_1.yc[i__ - 1], (ftnlen)sizeof(real));
	do_fio(&c__1, (char *)&dt1[i__ - 1], (ftnlen)sizeof(real));
	do_fio(&c__1, (char *)&dt2[i__ - 1], (ftnlen)sizeof(real));
	do_fio(&c__1, (char *)&dt3[i__ - 1], (ftnlen)sizeof(real));
    }
    e_wsfe();
    s_wsfe(&io___174);
    e_wsfe();
/* L9000: */
    if (itimeh == 1) {
	goto L136;
    }

/*        CONVOLVING SOURCE*Q FOR EACH SOURCE */

    if (itmty == 2) {
	goto L730;
    }
    i__1 = nsorce;
    for (i__ = 1; i__ <= i__1; ++i__) {
	i__2 = np;
	for (j = 1; j <= i__2; ++j) {
/* L30: */
	    floose_1.xss[i__ + j - 2] = 0.f;
	}
    }
    i__2 = nsorce;
    for (i__ = 1; i__ <= i__2; ++i__) {
/*        MODIFIED BOXCAR SOURCE TIME FUNCTION */
	d1 = dt1[i__ - 1];
	d2 = dt2[i__ - 1];
	d3 = dt3[i__ - 1];
	scon_(big_1.xs1, &dt, &np, &npl, &d1, &d2, &d3);
/*        CONVOLVING */
	i__1 = np;
	for (j = 1; j <= i__1; ++j) {
	    xr = big_1.xs1[(j << 1) - 2];
	    xi = big_1.xs1[(j << 1) - 1];
	    yr = fqw[(j << 1) - 2];
	    yi = fqw[(j << 1) - 1];
	    conr = xr * yr - xi * yi;
	    coni = xi * yr + xr * yi;
	    big_1.xs1[(j << 1) - 2] = conr;
	    big_1.xs1[(j << 1) - 1] = coni;
	    floose_1.xss[i__ + ((j << 1) - 1) - 2] = conr;
	    floose_1.xss[i__ + (j << 1) - 2] = coni;
/* L32: */
	}
	if (bug_1.ibug == 0) {
	    goto L22;
	}
	coolb_(&npl, big_1.xs1, &c_b259);
	big_1.xs1[0] /= dt * np;
	i__1 = np;
	for (j = 2; j <= i__1; ++j) {
/* L33: */
	    big_1.xs1[j - 1] = big_1.xs1[(j << 1) - 2] / (dt * np);
	}
/*     XSS(I,J) IS Q*I CONVOLVED WITH SOURCE FOR SOURCE I. */
/*         CALL SEPLOT(L,NP,X,XS1,SCALE,INST(3)) */
L22:
	;
    }
L730:
    s_wsfe(&io___178);
    e_wsfe();
L136:
/*     RESET PLOTTING CONTROL PARAMETER, L, FOR NEW MODEL. */
    l = 1;

/*        COMPUTING THE TOTAL RESPONSE AT EACH STATION */

    i__2 = nstat;
    for (j = 1; j <= i__2; ++j) {
	tfirst = 100.f;
	pc = stat_1.p[j - 1];
	s_wsfe(&io___181);
	do_fio(&c__1, (char *)&j, (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&id[j - 1], (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&pc, (ftnlen)sizeof(real));
	e_wsfe();
	s_wsfe(&io___182);
	do_fio(&c__1, (char *)&j, (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&id[j - 1], (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&pc, (ftnlen)sizeof(real));
	e_wsfe();
	i__1 = nsorce;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    if (j > 1) {
		goto L5375;
	    }
	    ddip = faul1_1.dip[i__ - 1] * 3.14159f / 180.f;

/*   READ IN FINITE FAULT PARAMETERS AND MASSAGE WEIGHT FILES. */

	    jill_(&i__, &ddip, &hypd[i__ - 1], &fl[i__ - 1], &xhyp[i__ - 1], &
		    travel_1.jo);
/*   SET UP SUBFAULT PARAMETERS SO THAT FINITE FAULT IS DIVIDED INTO MANY */
/*   SUBFAULTS.  TWO TYPES OF SUBFAULT BOUNDARIES ARE SET UP.  REGULAR */
/*   SUBFAULT BOUNDARIES WHICH WERE SPECIFIED IN JILL HAVE TOP AND BOTTOM */
/*   INDICES WHICH ARE GIVEN BY JBY1(NS,1,I) AND JEY1(NS,1,I) AND WHERE */
/*   JBY1(NS,2,I) IS POSITVE.  ANY VELOCITY DISCONTINUITIES ALSO FORM */
/*   SUBFAULT BOUNDARIES.  THESE BOUNDARIES ARE NEEDED FOR THE CALCULATION */
/*   AND ARE LATER REMOVED.  THEY ARE TREATED IN THE SAME FASHION AS NORMAL */
/*   SUBFAULT BOUNDARIES EXCEPT THAT JBY1(NS,2,I) IS NEGATIVE. */
	    subflt_(&i__, &ddip);
L5375:
	    s_wsfe(&io___187);
	    do_fio(&c__1, (char *)&faul1_1.strk[i__ - 1], (ftnlen)sizeof(real)
		    );
	    do_fio(&c__1, (char *)&faul1_1.dip[i__ - 1], (ftnlen)sizeof(real))
		    ;
	    do_fio(&c__1, (char *)&stat_1.az[j - 1], (ftnlen)sizeof(real));
	    e_wsfe();
	    sstrk = faul1_1.strk[i__ - 1] * 3.14159f / 180.f;
	    ddip = faul1_1.dip[i__ - 1] * 3.14159f / 180.f;
	    aaz = stat_1.az[j - 1] * 3.14159f / 180.f;
	    i__3 = np;
	    for (m = 1; m <= i__3; ++m) {
		big_1.xs3[m - 1] = 0.f;
/* L3001: */
		big_1.xs2[i__ + m - 2] = 0.f;
	    }
/*        CYCLE THROUGH THE SUBFAULTS */
	    nsu = subf_1.msub1[i__ - 1];
	    list = (i__3 = subf_1.jby1[((i__ << 1) + 2) * 300 - 900], abs(
		    i__3));
	    i__3 = nsu;
	    for (ns = 1; ns <= i__3; ++ns) {
		faul1_1.lis[i__ - 1] = (i__4 = subf_1.jby1[ns + ((i__ << 1) + 
			2) * 300 - 901], abs(i__4));
/*        LIS IS THE LAYER WITH THE SOURCE. */
		los = faul1_1.lis[i__ - 1];
		if (faul1_1.lis[i__ - 1] == list && ns != 1) {
		    goto L3002;
		}

/*    WILL NOW DETERMINE THE GEOMETRY OF SUBFAULTS WITH RESPECT TO THE */
/*    HYPOCENTER.  THESE NUMBERS GO INTO THE SUBROUTINE TTLAG.  THIS */
/*    STEP REMOVES THE CALCULATION OF STTM WHICH USED TO BE DONE IN DIANE. */

		slave_(&i__, &hypd[i__ - 1], &sdp, &los, &sstrk, &ddip, &sn, &
			se, &fl[i__ - 1], &xhyp[i__ - 1]);
		vpx = stuff_1.c__[los - 1];
		vsx = stuff_1.s[los - 1];

/*     WILL NOW CALCULATE POINT SOURCE RESPONSES */
/*     SDP REPRESENTS THE SOURCE DEPTH. */

		diswht_(&j, &i__, &sconv_1.mode, &pc, &los, &sdp);
L3002:
		list = faul1_1.lis[i__ - 1];
/* L7301: */

/*     WILL NOW CALCUALTE FAR-FIELD TIME FUNCTIONS FOR EACH FINITE SUBFAULT. */

		diane_(&dt, &sstrk, &ddip, &aaz, &pc, &i__, &vpx, &vsx, &ns, &
			los, &hypd[i__ - 1]);
		if (itfex != 1) {
		    goto L978;
		}
		s_wsfe(&io___200);
		e_wsfe();
		s_rsfe(&io___201);
		do_fio(&c__1, ifg1, (ftnlen)80);
		e_rsfe();
		o__1.oerr = 0;
		o__1.ounit = 15;
		o__1.ofnmlen = 80;
		o__1.ofnm = ifg1;
		o__1.orl = 0;
		o__1.osta = "OLD";
		o__1.oacc = 0;
		o__1.ofm = 0;
		o__1.oblnk = 0;
		f_open(&o__1);
		s_rsfe(&io___203);
		do_fio(&c__1, (char *)&nex, (ftnlen)sizeof(integer));
		do_fio(&c__1, (char *)&dtex, (ftnlen)sizeof(real));
		e_rsfe();
		s_rsfe(&io___206);
		i__4 = np;
		for (k = 1; k <= i__4; ++k) {
		    do_fio(&c__1, (char *)&timefn_1.xzk[k - 1], (ftnlen)
			    sizeof(real));
		}
		e_rsfe();
		cl__1.cerr = 0;
		cl__1.cunit = 15;
		cl__1.csta = 0;
		f_clos(&cl__1);
/* L983: */
		if (dtex != dt) {
		    s_wsfe(&io___208);
		    do_fio(&c__1, (char *)&dtex, (ftnlen)sizeof(real));
		    do_fio(&c__1, (char *)&dt, (ftnlen)sizeof(real));
		    e_wsfe();
		}
		if (dtex != dt) {
		    s_stop("", (ftnlen)0);
		}
		for (m = 1; m <= 4; ++m) {
		    i__4 = np;
		    for (k = 1; k <= i__4; ++k) {
/* L982: */
			timefn_1.tf[k + (m << 12) - 4097] = timefn_1.xzk[k - 
				1];
		    }
/* L981: */
		}
L978:
		for (m = 1; m <= 4; ++m) {
		    i__4 = np;
		    for (k = 1; k <= i__4; ++k) {
/* L1417: */
			timefn_1.xzk[k - 1] = timefn_1.tf[k + (m << 12) - 
				4097];
		    }
		    if (itimeh == 0) {
			goto L137;
		    }
		    filter_(timefn_1.xzk, big_1.xs1, &c__3, &np);
		    i__4 = np;
		    for (kj = 1; kj <= i__4; ++kj) {
/* L139: */
			timefn_1.xzk[kj - 1] = big_1.xs1[kj - 1];
		    }
/*     CALL SEPLOT(L,NP,X,XZK,SCALE,ID(J)) */
L137:
/*     IF(IBUG .EQ. 1) CALL SEPLOT(L,NP,X,XZK,SCALE,ID(J)) */
/* L1418: */
		    ;
		}
		if (itimeh == 1) {
		    goto L3000;
		}
/*       CONVOLVE EACH RAY WITH S*Q*I. */
		for (m = 1; m <= 4; ++m) {
/*       M =1, DOWN-GOING P, =2, UP-GOING P, =3, DOWN-GOING S, =4, UP-GOING S. */
		    i__4 = np;
		    for (k = 1; k <= i__4; ++k) {
			ijk = (k << 1) - 1;
			big_1.xs1[ijk] = 0.f;
/* L27: */
			big_1.xs1[ijk - 1] = timefn_1.tf[k + (m << 12) - 4097]
				 * dt;
		    }
		    if (bug_1.ibug == 1) {
			s_wsfe(&io___211);
			i__4 = np;
			for (ijk = 1; ijk <= i__4; ++ijk) {
			    do_fio(&c__1, (char *)&big_1.xs1[ijk - 1], (
				    ftnlen)sizeof(real));
			}
			e_wsfe();
		    }
		    coolb_(&npl, big_1.xs1, &c_b115);
/*       CONVOLVE PROPAGATION WITH I*Q. */
		    i__4 = np;
		    for (n = 1; n <= i__4; ++n) {
			xr = big_1.xs1[(n << 1) - 2];
			xi = big_1.xs1[(n << 1) - 1];
			yr = floose_1.xss[i__ + ((n << 1) - 1) - 2];
			yi = floose_1.xss[i__ + (n << 1) - 2];
			conr = xr * yr - xi * yi;
			coni = xi * yr + xr * yi;
			big_1.xs1[(n << 1) - 2] = conr;
			big_1.xs1[(n << 1) - 1] = coni;
/* L38: */
		    }
		    coolb_(&npl, big_1.xs1, &c_b259);
/*       XS1 IS NOW THE TIME DOMAIN S*I*Q FOR A PARTICULAR RAY, SOURCE & STATION. */
		    i__4 = np;
		    for (n = 1; n <= i__4; ++n) {
/* L10: */
			big_1.xs1[n - 1] = big_1.xs1[(n << 1) - 2] / (dt * np)
				;
		    }
		    i__4 = np;
		    for (n = 1; n <= i__4; ++n) {
/* L950: */
			stim_1.xs[m + (n << 2) - 5] = big_1.xs1[n - 1];
		    }
/*     IF(IBUG .EQ. 1) CALL SEPLOT(L,NP,X,XS1,SCALE,ID(J)) */
/* L28: */
		}
/*       CONVF CONVOLVES IN THE SOURCE USING A SIMPLE DELAY-LAG SUM. */
		convf_(&scale, &l, &i__, &dt, &np, &c__1);
		if (bug_1.ibug == 1) {
		    l = 1;
		}
/*        TTLAG LAGS EACH SOURCE THE APPROPRIATE TIME */
		ttlag_(&j, &i__, &dt, &np, &sn, &se);

/*        RECEV COMPUTES THE RECIEVER FUNCTION,TAKES CARE OF THE 1/R */
/*        DEPENDENCE AND MULTIPLIES IN THE FAULT MOMENT AND 1/4*PI*RHO */
/*        SCALING TO MICRONS. */

		recev_(&j, &i__, &np, &los);
		i__4 = np;
		for (m = 1; m <= i__4; ++m) {
/* L3007: */
		    big_1.xs3[m - 1] += sconv_1.pp[m - 1];
		}

/*     PHANTOM SUBFAULTS WHICH WERE CREATED TO HANDLE LAYERING ARE */
/*     SUMMED AND THUS ELIMINATED AT THIS POINT.  REAL SUBFAULT RESULTS */
/*     ARE PLOTTED AND OUTPUT AT THIS POINT. */

		if (subf_1.jey1[ns + ((i__ << 1) + 2) * 300 - 901] < 0) {
		    goto L9001;
		}
		if (isaveh == 1) {
		    s_wsfe(&io___213);
		    do_fio(&c__1, (char *)&np, (ftnlen)sizeof(integer));
		    do_fio(&c__1, (char *)&scale, (ftnlen)sizeof(real));
		    do_fio(&c__1, (char *)&id[j - 1], (ftnlen)sizeof(integer))
			    ;
		    e_wsfe();
		}
		if (isaveh == 1) {
		    s_wsfe(&io___214);
		    i__4 = np;
		    for (kp = 1; kp <= i__4; ++kp) {
			do_fio(&c__1, (char *)&big_1.xs3[kp - 1], (ftnlen)
				sizeof(real));
		    }
		    e_wsfe();
		}

/*     WRITING TO BINARY OUTPUT FILE (CADBIN) FOR EACH REAL SUBFAULT. */

		if (kbin != 1) {
		    goto L4005;
		}
		smax = 0.f;
		i__4 = np;
		for (m = 1; m <= i__4; ++m) {
/* L4006: */
/* Computing MAX */
		    r__1 = big_1.xs3[m - 1], r__2 = -big_1.xs3[m - 1], r__1 = 
			    max(r__1,r__2);
		    smax = dmax(r__1,smax);
		}
		picam = smax / 100.f;
		i__4 = np;
		for (m = 1; m <= i__4; ++m) {
		    xsamp = (r__1 = big_1.xs3[m - 1], dabs(r__1));
/* L4007: */
		    if (xsamp >= picam) {
			goto L4008;
		    }
		}
L4008:
		tstart = m * dt;
		if (tstart < tfirst) {
		    tfirst = tstart;
		}
		bin_1.mpoin = np;
		bin_1.deltm = dt;
/* L4010: */
		s_wsue(&io___220);
		do_uio(&c__1, (char *)&bin_1.mpoin, (ftnlen)sizeof(integer));
		do_uio(&c__1, (char *)&bin_1.deltm, (ftnlen)sizeof(real));
		do_uio(&c__1, (char *)&bin_1.tzero, (ftnlen)sizeof(real));
		e_wsue();
		m = np << 1;

/*     THE FOLLOWING CORRECTION IS NOT NECESSARY FOR MOMENT E20 */
/*     AND HAS BEEN OMITTED ....................... APR 30 1993 */
/*     TO GET MOMENT E20, SIMPLY MAKE INPUT MOMENT = 1.e-6 */

/*      DO 7999 I45=1,NP */
/* 7999 XS4(I45)=XS3(I45)/1.E6 */
/*      WRITE(12) (XS4(I45),I45=1,NP) */

		s_wsue(&io___221);
		i__4 = np;
		for (i45 = 1; i45 <= i__4; ++i45) {
		    do_uio(&c__1, (char *)&big_1.xs3[i45 - 1], (ftnlen)sizeof(
			    real));
		}
		e_wsue();
L4005:

/*     PLOT FIRST AND LAST REAL SUBFAULTS.  IF FIRST 2 SUBFAULTS */
/*     ARE NOT PHANTOMS, MORE THAN TWO WILL BE PLOTTED. */

/*     IF(NS .EQ. 1 .OR. NS .EQ. 2) CALL SEPLOT(L,NP,X,XS3,SCALE,ID(J)) */
/*     IF(NS .EQ. NSU) CALL SEPLOT(L,NP,X,XS3,SCALE,ID(J)) */
		i__4 = np;
		for (m = 1; m <= i__4; ++m) {
/* L40: */
		    big_1.xs2[i__ + m - 2] = big_1.xs3[m - 1] + big_1.xs2[i__ 
			    + m - 2];
		}
		i__4 = np;
		for (m = 1; m <= i__4; ++m) {
/* L9002: */
		    big_1.xs3[m - 1] = 0.f;
		}
L9001:
/*     BOTTOM OF SUBFAULT LOOP INCLUDING PHANTOMS. DO 3000 NS=1,NSU */
L3000:
		;
	    }
/*     BOTTOM OF SOURCE LOOP (IE. MULTIPLE FAULTS). DO 21 I=1,NSORCE */
/* L21: */
	}
	s_wsfe(&io___223);
	do_fio(&c__1, (char *)&id[j - 1], (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&tfirst, (ftnlen)sizeof(real));
	e_wsfe();
	s_wsfe(&io___224);
	do_fio(&c__1, (char *)&id[j - 1], (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&tfirst, (ftnlen)sizeof(real));
	e_wsfe();
	if (itimeh == 1) {
	    goto L20;
	}
/*     ADDING ALL THE SOURCES */
	i__1 = np;
	for (m = 1; m <= i__1; ++m) {
	    sconv_1.pp[m - 1] = 0.f;
	    i__3 = nsorce;
	    for (i__ = 1; i__ <= i__3; ++i__) {
		sconv_1.pp[m - 1] += big_1.xs2[i__ + m - 2];
/* L41: */
	    }
	}
	if (ipr_1.iprnt == 0) {
	    goto L47;
	}
	s_wsfe(&io___225);
	do_fio(&c__1, (char *)&id[j - 1], (ftnlen)sizeof(integer));
	e_wsfe();
	s_wsfe(&io___226);
	for (i__ = 1; i__ <= 200; ++i__) {
	    do_fio(&c__1, (char *)&sconv_1.pp[i__ - 1], (ftnlen)sizeof(real));
	}
	e_wsfe();
/*  47 CALL SEPLOT(L,NP,X,PP,SCALE,ID(J)) */
L47:
/*     BOTTOM OF STATION LOOP. DO 20 J=1,NSTAT */
L20:
	;
    }
    cl__1.cerr = 0;
    cl__1.cunit = 9;
    cl__1.csta = 0;
    f_clos(&cl__1);
    goto L77;
L76:
    cl__1.cerr = 0;
    cl__1.cunit = 2;
    cl__1.csta = 0;
    f_clos(&cl__1);
    s_wsfe(&io___227);
    e_wsfe();
/*     WRITE(6,613) */
/* 613 FORMAT(1X, 72HYOU'LL FIND PRINT OUTPUT IN FILE 'OUTPUT' AND PLOT OUTP */
/*    2UTPUT IN FILE 'PLOT'      ) */
    cl__1.cerr = 0;
    cl__1.cunit = 3;
    cl__1.csta = 0;
    f_clos(&cl__1);
/*     CALL PLOT(17.0,0.0,999) */
    if (isaveh == 1) {
	cl__1.cerr = 0;
	cl__1.cunit = 7;
	cl__1.csta = 0;
	f_clos(&cl__1);
    }
/*     CLOSE(8) */
    cl__1.cerr = 0;
    cl__1.cunit = 9;
    cl__1.csta = 0;
    f_clos(&cl__1);
    cl__1.cerr = 0;
    cl__1.cunit = 13;
    cl__1.csta = 0;
    f_clos(&cl__1);
    if (kbin == 1) {
	cl__1.cerr = 0;
	cl__1.cunit = 12;
	cl__1.csta = 0;
	f_clos(&cl__1);
    }
    s_stop("", (ftnlen)0);
    return 0;
} /* MAIN__ */

#undef inst


/* Subroutine */ int diswht_(integer *jsta, integer *isrc, integer *mode, 
	real *pc, integer *los, real *hs1)
{
    /* Format strings */
    static char fmt_20[] = "(1x,\002HS1=\002,e12.4,\002 PC=\002,e12.4,\002"
	    " I=\002,i5,\002 JSTA=\002,i5,\002 ISRC=\002,i5)";
    static char fmt_201[] = "(1x,\002CRUSTAL RESPONSE FOR SOURCE\002,i5,1x"
	    ",\002AT STATION\002,i5)";
    static char fmt_200[] = "(i3,2e18.5,i5)";

    /* System generated locals */
    integer i__1;

    /* Builtin functions */
    integer s_wsfe(cilist *), do_fio(integer *, char *, ftnlen), e_wsfe(void);

    /* Local variables */
    static integer i__, j, jm;
    extern /* Subroutine */ int trav_(real *, real *, integer *, integer *, 
	    integer *), raygun_(integer *, integer *, integer *, integer *);

    /* Fortran I/O blocks */
    static cilist io___231 = { 0, 3, 0, fmt_20, 0 };
    static cilist io___232 = { 0, 3, 0, fmt_201, 0 };
    static cilist io___233 = { 0, 3, 0, fmt_200, 0 };


/*  DISWHIT - FIRST MOTIONS FOR ALL DISLOCATION SOURCES IMBEDED IN A LAYERED */
/*        MEDIUM 6/15/74 */
/*     USES FIRST MOTION APPROX FOR DISLOCATIONS AS USED BY LANGSTON */
/*     CALCULATES LAYERED MEDIUM RESPONSE FOR P,SV,SH SOURCES */
/*     NORMALIZATION CONSTANTS FOR THE POTENTIALS ARE ALL SET TO 1.0 */
/*        ALSO, NO FACTORS FOR THE SPATIAL DERIVATIVES ARE INCLUDED */
/*     HS=DEPTH OF THE SOURCE IN THE MEDIUM */
/*     NRAY=5,P WAVE; =3,S WAVE */
/*     NCOUNT(I)=DEGENERACY OF A PARTICULAR RAY */
/*     COMMON/ANS/ CONTAINS RAY ARRIVAL TIMES (TO) AND AMPLITUDES (AM) */
/*     NTYPE =+5, UP GOING P, =-5, DOWN-GOING P, =+3, UP-GOING S, =-3, DOWN GOING */
    rays_1.love = 0;
    if (*mode == 3) {
	rays_1.love = 2;
    }

/*        READING IN MODEL AND RAYS */

    if (*isrc > 1 || *jsta > 1) {
	goto L38;
    }
    i__1 = travel_1.jo;
    for (i__ = 1; i__ <= i__1; ++i__) {
	stuff_1.rcsq[i__ - 1] = 1.f / (stuff_1.c__[i__ - 1] * stuff_1.c__[i__ 
		- 1]);
	stuff_1.rssq[i__ - 1] = 1.f / (stuff_1.s[i__ - 1] * stuff_1.s[i__ - 1]
		);
	orst_1.c1[i__ - 1] = (real) stuff_1.c__[i__ - 1];
	orst_1.s1[i__ - 1] = (real) stuff_1.s[i__ - 1];
	orst_1.d1[i__ - 1] = (real) stuff_1.d__[i__ - 1];
/* L36: */
    }
L38:
    raygun_(los, &travel_1.jo, mode, &jm);
    ans_1.lfinal = 1;
    i__1 = jm;
    for (i__ = 1; i__ <= i__1; ++i__) {
	if (ipr_1.iprnt == 1) {
	    s_wsfe(&io___231);
	    do_fio(&c__1, (char *)&(*hs1), (ftnlen)sizeof(real));
	    do_fio(&c__1, (char *)&(*pc), (ftnlen)sizeof(real));
	    do_fio(&c__1, (char *)&i__, (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&(*jsta), (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&(*isrc), (ftnlen)sizeof(integer));
	    e_wsfe();
	}
/* L77: */
	trav_(hs1, pc, &i__, jsta, isrc);
    }
    --ans_1.lfinal;
/* L310: */
    s_wsfe(&io___232);
    do_fio(&c__1, (char *)&(*isrc), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&(*jsta), (ftnlen)sizeof(integer));
    e_wsfe();
    if (ipr_1.iprnt == 1) {
	s_wsfe(&io___233);
	i__1 = ans_1.lfinal;
	for (j = 1; j <= i__1; ++j) {
	    do_fio(&c__1, (char *)&j, (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&ans_1.to[j - 1], (ftnlen)sizeof(real));
	    do_fio(&c__1, (char *)&ans_1.am[j - 1], (ftnlen)sizeof(real));
	    do_fio(&c__1, (char *)&ans_1.ntype[j - 1], (ftnlen)sizeof(integer)
		    );
	}
	e_wsfe();
    }
/* L100: */
/* L101: */
    return 0;
} /* diswht_ */

/* Subroutine */ int tranm_(real *p, real *v1, real *s1, real *d1, real *v2, 
	real *s2, real *d2, real *tpp, real *tps, real *tsp, real *tss)
{
    /* System generated locals */
    real r__1, r__2, r__3;

    /* Local variables */
    static real t, b1, b2, e1, e2, c1, c2, c3, k1, k2, k3, k4, c4, c5, c6, r1,
	     r2, ap, bp;
    extern doublereal cr_(real *, real *);
    static real bs, ts, e1p, e2p, rho1, rho2;

    rho1 = *d1;
    rho2 = *d2;
/* Computing 2nd power */
    r__1 = *s2;
/* Computing 2nd power */
    r__2 = *s1;
    k4 = rho2 * (r__1 * r__1) / (rho1 * (r__2 * r__2));
    b1 = .5f / (1 - k4);
    b2 = k4 * .5f / (k4 - 1);
/* Computing 2nd power */
    r__1 = *s1;
    k1 = b1 / (r__1 * r__1);
/* Computing 2nd power */
    r__1 = *s2;
    k2 = b2 / (r__1 * r__1);
    k3 = k1 + k2;
    e1 = cr_(p, v1);
    e2 = cr_(p, v2);
    e2p = cr_(p, s2);
    e1p = cr_(p, s1);
    if (rays_1.love > 0) {
	goto L10;
    }
/* Computing 2nd power */
    r__1 = *p;
/* Computing 2nd power */
    r__3 = *p;
/* Computing 2nd power */
    r__2 = k3 - r__3 * r__3;
    c1 = r__1 * r__1 * (r__2 * r__2);
/* Computing 2nd power */
    r__1 = *p;
    c2 = r__1 * r__1 * e1 * e1p * e2p;
/* Computing 2nd power */
    r__2 = *p;
/* Computing 2nd power */
    r__1 = k2 - r__2 * r__2;
    c3 = e1 * e1p * (r__1 * r__1);
/* Computing 2nd power */
    r__1 = k1 - *p * *p;
    c4 = e2p * (r__1 * r__1);
    c5 = k1 * k2 * e1 * e2p;
    c6 = k1 * k2 * e1p;
    ap = c1 + c3 - c5;
    bp = c2 + c4 - c6;
    bs = ap + e2 * bp;
/* Computing 2nd power */
    r__1 = *p;
/* Computing 2nd power */
    r__2 = *p;
    t = k1 * 2.f * e1 * (e2p * (k1 - r__1 * r__1) - e1p * (k2 - r__2 * r__2));
    *tpp = t / bs;
/* Computing 2nd power */
    r__1 = *p;
    t = k1 * 2.f * *p * e1 * (e1p * e2 - (k3 - r__1 * r__1));
    *tps = t / bs;
/* Computing 2nd power */
    r__1 = *p;
    ts = k1 * 2.f * *p * e1p * (k3 - r__1 * r__1 - e1 * e2p);
    *tsp = ts / bs;
/* Computing 2nd power */
    r__1 = *p;
    ts = k1 * -2.f * e1p * (e1 * (k2 - r__1 * r__1) - e2 * (k1 - *p * *p));
    *tss = ts / bs;
    return 0;
L10:
/* Computing 2nd power */
    r__1 = *s1;
    r1 = *d1 * (r__1 * r__1);
/* Computing 2nd power */
    r__1 = *s2;
    r2 = *d2 * (r__1 * r__1);
    *tss = r1 * 2.f * e1p / (r1 * e1p + r2 * e2p);
    return 0;
} /* tranm_ */

/* Subroutine */ int refft_(real *p, real *v1, real *s1, real *d1, real *v2, 
	real *s2, real *d2, real *rpp, real *rps, real *rsp, real *rss)
{
    /* System generated locals */
    real r__1, r__2, r__3;

    /* Local variables */
    static real a, b, b1, b2, e1, e2, c1, c2, c3, k1, k2, k3, k4, c4, c5, c6, 
	    r1, r2, ap, bp;
    extern doublereal cr_(real *, real *);
    static real bt, e1p, e2p, aps, bps, asp, bsp;

/* Computing 2nd power */
    r__1 = *s2;
/* Computing 2nd power */
    r__2 = *s1;
    k4 = r__1 * r__1 * *d2 / (r__2 * r__2 * *d1);
    b1 = .5f / (1 - k4);
    b2 = k4 * .5f / (k4 - 1);
/* Computing 2nd power */
    r__1 = *s1;
    k1 = b1 / (r__1 * r__1);
/* Computing 2nd power */
    r__1 = *s2;
    k2 = b2 / (r__1 * r__1);
    k3 = k1 + k2;
    e1 = cr_(p, v1);
    e2 = cr_(p, v2);
    e1p = cr_(p, s1);
    e2p = cr_(p, s2);
    if (rays_1.love > 0) {
	goto L10;
    }
/* Computing 2nd power */
    r__1 = *p;
/* Computing 2nd power */
    r__3 = *p;
/* Computing 2nd power */
    r__2 = k3 - r__3 * r__3;
    c1 = r__1 * r__1 * (r__2 * r__2);
/* Computing 2nd power */
    r__1 = *p;
    c2 = r__1 * r__1 * e1 * e1p * e2p;
/* Computing 2nd power */
    r__2 = *p;
/* Computing 2nd power */
    r__1 = k2 - r__2 * r__2;
    c3 = e1 * e1p * (r__1 * r__1);
/* Computing 2nd power */
    r__1 = k1 - *p * *p;
    c4 = e2p * (r__1 * r__1);
    c5 = k1 * k2 * e1 * e2p;
    c6 = k1 * k2 * e1p;
    ap = c1 + c3 - c5;
    bp = c2 + c4 - c6;
    a = -c1 + c3 - c5;
    b = -c2 + c4 - c6;
    bt = ap + bp * e2;
    *rpp = (a - b * e2) / bt;
    aps = *p * 2.f * e1 * (k2 - *p * *p) * (k3 - *p * *p);
    bps = *p * 2.f * e1 * (k1 - *p * *p) * e2p;
    *rps = (aps - bps * e2) / bt;
    a = -c1 + c3 + c5;
    b = -c2 + c4 + c6;
    *rss = (a - b * e2) / bt;
    asp = *p * 2.f * e1p * (k2 - *p * *p) * (k3 - *p * *p);
    bsp = *p * 2.f * e1p * (k1 - *p * *p) * e2p;
    *rsp = -(asp - bsp * e2) / bt;
    return 0;
L10:
/* Computing 2nd power */
    r__1 = *s1;
    r1 = *d1 * (r__1 * r__1);
/* Computing 2nd power */
    r__1 = *s2;
    r2 = *d2 * (r__1 * r__1);
    *rss = (r1 * e1p - r2 * e2p) / (r1 * e1p + r2 * e2p);
    return 0;
} /* refft_ */

/* Subroutine */ int convf_(real *scale, integer *l, integer *is, real *dt, 
	integer *np, integer *line)
{
    /* Format strings */
    static char fmt_600[] = "(3x,\002CONVF, IS=\002i5,f10.4,2i5)";
    static char fmt_601[] = "(5x,2f10.6,i5)";
    static char fmt_602[] = "(2x,5i5,3e11.4)";

    /* System generated locals */
    integer i__1, i__2;

    /* Builtin functions */
    integer s_wsfe(cilist *), do_fio(integer *, char *, ftnlen), e_wsfe(void);

    /* Local variables */
    static integer i__, j, k;
    static real x[4096];
    static integer im;
    static real pt[4096], amp, ppt[4096];
    static integer nlag;

    /* Fortran I/O blocks */
    static cilist io___290 = { 0, 3, 0, fmt_600, 0 };
    static cilist io___291 = { 0, 3, 0, fmt_601, 0 };
    static cilist io___297 = { 0, 3, 0, fmt_602, 0 };


/*     M=1, DOWN-GOING P, NTYPE=-5 */
/*     M=2, UP-GOING P, NTYPE=+5 */
/*     M=3, DOWN-GOING S, NTYPE=-3 */
/*     M=4, UP-GOING S, NTYPE=+3 */
    for (k = 1; k <= 4; ++k) {
	amp = stim_1.xs[k - 1];
	i__1 = *np;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    if (stim_1.xs[k + (i__ << 2) - 5] == 0.f) {
		goto L51;
	    }
	    stim_1.xs[k + (i__ << 2) - 5] -= amp;
L51:
	    ;
	}
/* L50: */
    }
    if (bug_1.ibug == 0) {
	goto L30;
    }
    s_wsfe(&io___290);
    do_fio(&c__1, (char *)&(*is), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&(*dt), (ftnlen)sizeof(real));
    do_fio(&c__1, (char *)&(*np), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&ans_1.lfinal, (ftnlen)sizeof(integer));
    e_wsfe();
    s_wsfe(&io___291);
    i__1 = ans_1.lfinal;
    for (i__ = 1; i__ <= i__1; ++i__) {
	do_fio(&c__1, (char *)&ans_1.to[i__ - 1], (ftnlen)sizeof(real));
	do_fio(&c__1, (char *)&ans_1.am[i__ - 1], (ftnlen)sizeof(real));
	do_fio(&c__1, (char *)&ans_1.ntype[i__ - 1], (ftnlen)sizeof(integer));
    }
    e_wsfe();
    i__1 = *np;
    for (i__ = 1; i__ <= i__1; ++i__) {
	x[i__ - 1] = *dt * (i__ - 1);
/* L901: */
	pt[i__ - 1] = stim_1.xs[*is + (i__ << 2) - 5];
    }
/*      CALL SEPLOT(L,NP,X,PT,SCALE,4H XS ) */
/* L950: */
L30:
    i__1 = *np;
    for (i__ = 1; i__ <= i__1; ++i__) {
	pt[i__ - 1] = 0.f;
/* L10: */
	sconv_1.pp[i__ - 1] = 0.f;
    }
    i__1 = ans_1.lfinal;
    for (j = 1; j <= i__1; ++j) {
	if (*line == 0) {
	    goto L17;
	}
	if (ans_1.ntype[j - 1] == -5) {
	    goto L1;
	}
	if (ans_1.ntype[j - 1] == 5) {
	    goto L2;
	}
	if (ans_1.ntype[j - 1] == -3) {
	    goto L3;
	}
	im = 4;
	goto L16;
L1:
	im = 1;
	goto L16;
L2:
	im = 2;
	goto L16;
L3:
	im = 3;
	goto L16;
L17:
	im = *is;
L16:
	i__2 = *np;
	for (i__ = 1; i__ <= i__2; ++i__) {
/* L15: */
	    pt[i__ - 1] = stim_1.xs[im + (i__ << 2) - 5] * ans_1.am[j - 1];
	}
	nlag = (integer) (ans_1.to[j - 1] / *dt) + 1;
	if (bug_1.ibug == 1) {
	    s_wsfe(&io___297);
	    do_fio(&c__1, (char *)&j, (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&ans_1.ntype[j - 1], (ftnlen)sizeof(integer)
		    );
	    do_fio(&c__1, (char *)&im, (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&nlag, (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&(*np), (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&ans_1.to[j - 1], (ftnlen)sizeof(real));
	    do_fio(&c__1, (char *)&ans_1.am[j - 1], (ftnlen)sizeof(real));
	    do_fio(&c__1, (char *)&(*dt), (ftnlen)sizeof(real));
	    e_wsfe();
	}
	if (nlag > *np) {
	    goto L20;
	}
	i__2 = *np;
	for (i__ = 1; i__ <= i__2; ++i__) {
/* L35: */
	    ppt[i__ - 1] = 0.f;
	}
	i__2 = *np;
	for (i__ = nlag; i__ <= i__2; ++i__) {
	    ppt[i__ - 1] = -pt[i__ - nlag] * 1000;
/* L25: */
	    sconv_1.pp[i__ - 1] += pt[i__ - nlag];
	}
	if (bug_1.ibug == 0) {
	    goto L20;
	}
/*     CALL SEPLOT(L,NP,X,PPT,SCALE,4HCONV) */
L20:
	;
    }
    return 0;
} /* convf_ */

/* Subroutine */ int trav_(real *hs, real *pc, integer *ir, integer *jsta, 
	integer *isrc)
{
    /* Format strings */
    static char fmt_400[] = "(1x,\002LIS=\002,i5,\002   NUP=\002i3,\002   NR"
	    "AY=\002i3,5x,\002NTYPE=\002,i5)";
    static char fmt_401[] = "(1x,\002HSL=\002,f10.3)";
    static char fmt_100[] = "(1x,\002GC1=\002,e13.6,4x,\002GC=\002,e13.6,4x"
	    ",\002RT=\002,e13.6)";
    static char fmt_41[] = "(1x,\002GC=\002,e12.4,\002 SR=\002,e12.4,\002 "
	    "RR=\002,e12.4,\002 EA=\002,e12.4,\002 EB=\002,e12.4,\002 DET="
	    "\002,e12.4)";
    static char fmt_42[] = "(1x,\002NCOUNT(IR)=\002,i5,\002 IR=\002,i5,\002 "
	    "AM(L)=\002,e12.4,\002 L=\002,i5,\002 PC=\002,e12.4)";

    /* System generated locals */
    integer i__1, i__2, i__3;
    doublereal d__1;

    /* Builtin functions */
    integer pow_ii(integer *, integer *), s_wsfe(cilist *), do_fio(integer *, 
	    char *, ftnlen), e_wsfe(void);
    double pow_dd(doublereal *, doublereal *), sqrt(doublereal);

    /* Local variables */
    static real h__;
    static integer i__, j;
    static real ea, eb, gc, cn[5];
    static integer nd, nl, nm, mr;
    static real rr;
    static integer nx;
    static real sr;
    static integer nr;
    static real rt, ea1, eb1, gc1, sr1, sr2, sr3, det, gct, hsl;
    static integer lis, nup;
    static real srp;
    static doublereal rsq;
    static real srs;
    static integer lis1, nend;
    extern /* Subroutine */ int fcon_(integer *, integer *, real *, integer *)
	    ;
    static integer ncip, lmax;
    static real thtot;
    extern doublereal gencof_(integer *, real *, integer *, integer *);

    /* Fortran I/O blocks */
    static cilist io___306 = { 0, 3, 0, fmt_400, 0 };
    static cilist io___311 = { 0, 3, 0, fmt_401, 0 };
    static cilist io___327 = { 0, 3, 0, fmt_100, 0 };
    static cilist io___337 = { 0, 3, 0, fmt_41, 0 };
    static cilist io___338 = { 0, 3, 0, fmt_42, 0 };


/*     IR - INDEX OF RAY BEING CONSIDERED, GOES FROM 1 TO JM */
/*     NDR(I) - NUMBER OPF SEGMENTS IN I-TH RAY. */
/*     NA(RAY,SEGMENT) - DEFINES RAY PATH. */
/*     NDR(IR) = ND - NUMBER OF SEGMENTS IN RAY IR. */
/*     NRAY(RAY,SEGMENT) - DEFINES RAY TYPE (P OR S). */
/*     FCON FINDS THE FAULT ORIENTATION CONSTANTS */
/*     NCOUNT(I)=NUMBER OF RAYS WITH THE SAME RESPONSE */
/*     NEND IS THE NUMBER OF LAYERS TRAVERSED -1. */
/*     NRAY CODE: P=5,S=3 */
/*     GC IS PRODUCT OF ALL THE TRANSMISSION AND REFLECTION COEFF. */
/*     TESTING NA AND NRAY FOR LP AND LS INFORMATION. */

    nend = rays_1.ndr[*ir - 1] - 1;
    nd = rays_1.ndr[*ir - 1];
    i__1 = travel_2.ll;
    for (j = 1; j <= i__1; ++j) {
	travel_2.lp[j - 1] = 0;
/* L1: */
	travel_2.ls[j - 1] = 0;
    }
    i__1 = nd;
    for (j = 1; j <= i__1; ++j) {
	ncip = rays_1.na[*ir + j * 250 - 251];
	if (rays_1.nray[*ir + j * 250 - 251] == 5) {
	    ++travel_2.lp[ncip - 1];
	}
	if (rays_1.nray[*ir + j * 250 - 251] == 3) {
	    ++travel_2.ls[ncip - 1];
	}
/* L5: */
    }

/*        DETERMINING WHICH DIRECTION THE RAY TRAVELS */
/*                 (UP OR DOWN) */
/*        NUP=1, RAY GOING UP; =-1, RAY GOING DOWN. */
/*        LIS=LAYER SOURCE IS IN */

    lis = rays_1.na[*ir - 1];
    nl = 0;
    i__1 = nd;
    for (j = 1; j <= i__1; ++j) {
/* L20: */
	if (rays_1.na[*ir + j * 250 - 251] == lis) {
	    ++nl;
	}
    }
    nup = pow_ii(&c_n1, &nl);
    ans_2.ntype[*ir - 1] = nup * rays_1.nray[*ir - 1];
    if (ipr_1.iprnt == 1) {
	s_wsfe(&io___306);
	do_fio(&c__1, (char *)&lis, (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&nup, (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&rays_1.nray[*ir - 1], (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&ans_2.ntype[*ir - 1], (ftnlen)sizeof(integer));
	e_wsfe();
    }


/*        NOW FINDING THE POSITION OF THE SOURCE IN THE LIS LAYER */

    lis1 = lis - 1;
    thtot = 0.f;
    i__1 = lis1;
    for (i__ = 1; i__ <= i__1; ++i__) {
/* L21: */
	thtot = stuff_1.th[i__ - 1] + thtot;
    }
    hsl = *hs - thtot;
    if (ipr_1.iprnt == 1) {
	s_wsfe(&io___311);
	do_fio(&c__1, (char *)&hsl, (ftnlen)sizeof(real));
	e_wsfe();
    }
    nx = 1;
    i__1 = nd;
    for (nm = 1; nm <= i__1; ++nm) {
/* L17: */
/* Computing MAX */
	i__2 = nx, i__3 = rays_1.na[*ir + nm * 250 - 251];
	nx = max(i__2,i__3);
    }
    lmax = nx;


/* L30: */
    d__1 = stuff_1.rcsq[lis - 1] - *pc * *pc;
    ea = pow_dd(&d__1, &c_b581);
    d__1 = stuff_1.rssq[lis - 1] - *pc * *pc;
    eb = pow_dd(&d__1, &c_b581);
    sr = 1.f;
    rr = 1.f;
    mr = rays_1.nray[*ir - 1];
    ea1 = ea;
    eb1 = eb;
    nr = rays_1.nray[*ir + nd * 250 - 251];
    if (nd == 1) {
	goto L24;
    }
    gc = 1.f;
    i__2 = nend;
    for (i__ = 1; i__ <= i__2; ++i__) {
	gct = gencof_(&i__, pc, &nup, ir);
	gc *= gct;
/* L10: */
    }
/*        THIS SECTION CORRECTS AMPLITUDES FOR A SHALLOW SOURCE */
    rt = 1.f;
    if (mr == 3 && nr == 5) {
	rt = ea1 / eb;
    }
    if (mr == 5 && nr == 3) {
	rt = eb1 / ea;
    }
    gc1 = gc;
    gc *= rt;
    if (ipr_1.iprnt == 1) {
	s_wsfe(&io___327);
	do_fio(&c__1, (char *)&gc1, (ftnlen)sizeof(real));
	do_fio(&c__1, (char *)&gc, (ftnlen)sizeof(real));
	do_fio(&c__1, (char *)&rt, (ftnlen)sizeof(real));
	e_wsfe();
    }

    goto L25;
L24:
    gc = 1.f;
L25:

/*        FINDING THE TIME LAG (FAR-FIELD) ASSOCIATED WITH THE RAY */

    if (nup < 0) {
	goto L22;
    }
/*        UP */
    h__ = stuff_1.th[lis - 1] - hsl;
    goto L23;
/*        DOWN */
L22:
    h__ = hsl;
L23:
    det = 0.f;
    i__2 = travel_2.ll;
    for (j = 1; j <= i__2; ++j) {
/* L31: */
	det += travel_2.lp[j - 1] * stuff_1.th[j - 1] * sqrt(stuff_1.rcsq[j - 
		1] - *pc * *pc);
	det += travel_2.ls[j - 1] * stuff_1.th[j - 1] * sqrt(stuff_1.rssq[j - 
		1] - *pc * *pc);
/* L35: */
    }
/*        ADJUSTING TIMES FOR SOURCE DEPTH */
    if (rays_1.nray[*ir - 1] == 5) {
	rsq = stuff_1.rcsq[lis - 1];
    }
    if (rays_1.nray[*ir - 1] == 3) {
	rsq = stuff_1.rssq[lis - 1];
    }
/* L32: */
    det -= h__ * sqrt(rsq - *pc * *pc);

    fcon_(jsta, isrc, cn, ir);
    if (rays_1.love == 2) {
	goto L26;
    }

/*        P AND SV POTENTIALS FOR DISLOCATIONS */


/*        THE FOLLOWING SECTION FINDS THE SOURCE RESPONSE TO THE RAY */
/*        PARAMETER USED. */


/*        SS CASE */

    srp = -(*pc * *pc);
    srs = -(*pc * eb);
/*        DOWN-GOING AND/OR UP-GOING P WAVES */
    if (mr == 5) {
	sr1 = srp;
    }
/*        DOWN-GOING SV */
    if (nup == -1 && mr == 3) {
	sr1 = srs;
    }
/*        UP-GOING SV */
    if (nup == 1 && mr == 3) {
	sr1 = -srs;
    }

/*        DS CASE */

    srp = *pc * 2.f * ea;
    srs = -(*pc * *pc - eb * eb);
/*        DOWN-GOING P */
    if (nup == -1 && mr == 5) {
	sr2 = srp;
    }
/*        UP-GOING P */
    if (nup == 1 && mr == 5) {
	sr2 = -srp;
    }
/*        DOWN-GOING AND UP-GOING SV */
    if (mr == 3) {
	sr2 = srs;
    }

/*        45 DS CASE */

    srp = -(ea * 2.f * ea - *pc * *pc);
    srs = *pc * 3.f * eb;
/*        DOWN-GOING AND UP-GOING P */
    if (mr == 5) {
	sr3 = srp;
    }
/*        DOWN-GOING SV */
    if (nup == -1 && mr == 3) {
	sr3 = srs;
    }
/*        UP-GOING SV */
    if (nup == 1 && mr == 3) {
	sr3 = -srs;
    }
    sr = sr1 * cn[0] + sr2 * cn[1] + sr3 * cn[2];
    goto L27;
L26:

/*        SH DISLOCATION POTENTIALS */


/*        SS CASE */

/*        DOWN-GOING AND UP-GOING SH */
    sr1 = stuff_1.rssq[lis - 1];

/*        DS CASE */

    srs = -stuff_1.rssq[lis - 1] * eb / *pc;
/*        DOWN-GOING SH */
    if (nup == -1) {
	sr2 = srs;
    }
/*        UP-GOING SH */
    if (nup == 1) {
	sr2 = -srs;
    }
    sr = sr1 * cn[3] + sr2 * cn[4];
L27:
/*        RR CONTAINED EA OR EB BEFORE TO TAKE CARE OF THE SCALING */
/*        FOR THE DERIVATIVE WITH RESPECT TO Z.  IT IS DELEDED HERE. */
    ans_2.am[ans_2.l - 1] = sr * rr * gc * rays_1.ncount[*ir - 1];
    ans_2.to[ans_2.l - 1] = det;
    if (ipr_1.iprnt == 0) {
	goto L40;
    }
    s_wsfe(&io___337);
    do_fio(&c__1, (char *)&gc, (ftnlen)sizeof(real));
    do_fio(&c__1, (char *)&sr, (ftnlen)sizeof(real));
    do_fio(&c__1, (char *)&rr, (ftnlen)sizeof(real));
    do_fio(&c__1, (char *)&ea, (ftnlen)sizeof(real));
    do_fio(&c__1, (char *)&eb, (ftnlen)sizeof(real));
    do_fio(&c__1, (char *)&det, (ftnlen)sizeof(real));
    e_wsfe();
    s_wsfe(&io___338);
    do_fio(&c__1, (char *)&rays_1.ncount[*ir - 1], (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&(*ir), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&ans_2.am[ans_2.l - 1], (ftnlen)sizeof(real));
    do_fio(&c__1, (char *)&ans_2.l, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&(*pc), (ftnlen)sizeof(real));
    e_wsfe();
L40:
    ++ans_2.l;
    return 0;
} /* trav_ */

doublereal gencof_(integer *i__, real *p, integer *nup, integer *ir)
{
    /* Format strings */
    static char fmt_112[] = "(1x,18x,\002STUFF(K) AND (M)\002,/(6e12.4))";
    static char fmt_110[] = "(1x,15x,\002TPP\002,15x,\002TPS\002,15x,\002TS"
	    "P\002,15x,\002TSS\002,/(8e12.4))";
    static char fmt_111[] = "(1x,15x,\002RPP\002,15x,\002RPS\002,15x,\002RS"
	    "P\002,15x,\002RSS\002,/(8e12.4))";

    /* System generated locals */
    integer i__1;
    real ret_val;

    /* Builtin functions */
    integer pow_ii(integer *, integer *), s_wsfe(cilist *), do_fio(integer *, 
	    char *, ftnlen), e_wsfe(void);

    /* Local variables */
    static integer j, k, m;
    static real q;
    static integer ij, kr, mr;
    static real rpp, tpp, rps, rsp, tps, tsp, tss, rss;
    static integer nfix;
    extern /* Subroutine */ int refft_(real *, real *, real *, real *, real *,
	     real *, real *, real *, real *, real *, real *), tranm_(real *, 
	    real *, real *, real *, real *, real *, real *, real *, real *, 
	    real *, real *);

    /* Fortran I/O blocks */
    static cilist io___355 = { 0, 3, 0, fmt_112, 0 };
    static cilist io___356 = { 0, 3, 0, fmt_110, 0 };
    static cilist io___357 = { 0, 3, 0, fmt_111, 0 };


/*     NDR(I)= NUMBER OF LEGS IN EITHER MODE */
/*     LL IS NUMBER OF LAYERS */
/*     I IS THE INDEX BEFORE INTERACTION */
/*     (I+1) IS THE INDEX AFTER INTERACTION */
/*     NUP=1, RAY GOING UP; =-1,RAY GOING DOWN */
    q = *p;
    m = rays_1.na[*ir + (*i__ + 1) * 250 - 251];
    k = rays_1.na[*ir + *i__ * 250 - 251];
    mr = rays_1.nray[*ir + (*i__ + 1) * 250 - 251];
    kr = rays_1.nray[*ir + *i__ * 250 - 251];
    if (m == k) {
	goto L14;
    }

/*        TRANSMISSION BUSINESS */

    tranm_(&q, &orst_2.c__[k - 1], &orst_2.s[k - 1], &orst_2.d__[k - 1], &
	    orst_2.c__[m - 1], &orst_2.s[m - 1], &orst_2.d__[m - 1], &tpp, &
	    tps, &tsp, &tss);
    if (m > k) {
	goto L11;
    }
    tps = -tps;
    tsp = -tsp;
L11:
    if (kr == mr) {
	goto L12;
    }
    if (kr == 5) {
	ret_val = tps;
    }
    if (kr == 3) {
	ret_val = tsp;
    }
    goto L20;
L12:
    if (kr == 3) {
	ret_val = tss;
    }
    if (kr == 5) {
	ret_val = tpp;
    }
    goto L20;

/*        REFLECTION BUSINESS */

L14:
/*        TESTING FOR THE REFLECTION NUMBER */
    ij = 0;
    i__1 = *i__;
    for (j = 1; j <= i__1; ++j) {
/* L40: */
	if (rays_1.na[*ir + j * 250 - 251] == rays_1.na[*ir + (j + 1) * 250 - 
		251]) {
	    ++ij;
	}
    }
    nfix = pow_ii(&c_n1, &ij);
    k = rays_1.na[*ir + *i__ * 250 - 251];
    if (*nup <= 0) {
	goto L41;
    } else {
	goto L42;
    }
L41:
    if (nfix < 0) {
	goto L43;
    }
/*        IJ=EVEN NUMBER AND SOURCE RAY IS DOWN-GOING */
    m = k - 1;
    goto L50;
L43:
/*        IJ=ODD NUMBER AND SOURCE RAY IS DOWN-GOING */
    m = k + 1;
    goto L50;
L42:
    if (nfix < 0) {
	goto L44;
    }
/*        IJ=EVEN NUMBER AND SOURCE RAY IS UP-GOING */
    m = k + 1;
    goto L50;
L44:
/*        IJ=ODD NUMBER AND SOURCE RAY IS UP GOING */
    m = k - 1;
L50:
    refft_(&q, &orst_2.c__[k - 1], &orst_2.s[k - 1], &orst_2.d__[k - 1], &
	    orst_2.c__[m - 1], &orst_2.s[m - 1], &orst_2.d__[m - 1], &rpp, &
	    rps, &rsp, &rss);
    if (m > k) {
	goto L21;
    }
    rps = -rps;
    rsp = -rsp;
L21:

    if (kr == mr) {
	goto L22;
    }
    if (kr == 5) {
	ret_val = rps;
    }
    if (kr == 3) {
	ret_val = rsp;
    }
    goto L20;
L22:
    if (kr == 3) {
	ret_val = rss;
    }
    if (kr == 5) {
	ret_val = rpp;
    }
L20:
    if (ipr_1.iprnt == 0) {
	return ret_val;
    }
    s_wsfe(&io___355);
    do_fio(&c__1, (char *)&orst_2.c__[k - 1], (ftnlen)sizeof(real));
    do_fio(&c__1, (char *)&orst_2.s[k - 1], (ftnlen)sizeof(real));
    do_fio(&c__1, (char *)&orst_2.d__[k - 1], (ftnlen)sizeof(real));
    do_fio(&c__1, (char *)&orst_2.c__[m - 1], (ftnlen)sizeof(real));
    do_fio(&c__1, (char *)&orst_2.s[m - 1], (ftnlen)sizeof(real));
    do_fio(&c__1, (char *)&orst_2.d__[m - 1], (ftnlen)sizeof(real));
    e_wsfe();
    s_wsfe(&io___356);
    do_fio(&c__1, (char *)&tpp, (ftnlen)sizeof(real));
    do_fio(&c__1, (char *)&tps, (ftnlen)sizeof(real));
    do_fio(&c__1, (char *)&tsp, (ftnlen)sizeof(real));
    do_fio(&c__1, (char *)&tss, (ftnlen)sizeof(real));
    e_wsfe();
    s_wsfe(&io___357);
    do_fio(&c__1, (char *)&rpp, (ftnlen)sizeof(real));
    do_fio(&c__1, (char *)&rps, (ftnlen)sizeof(real));
    do_fio(&c__1, (char *)&rsp, (ftnlen)sizeof(real));
    do_fio(&c__1, (char *)&rss, (ftnlen)sizeof(real));
    e_wsfe();
    return ret_val;
} /* gencof_ */

/* Subroutine */ int filter_(real *x, real *y, integer *m, integer *nt)
{
    /* System generated locals */
    integer i__1;

    /* Local variables */
    static integer i__, k, l, n;
    static real t;
    static integer jj, nm, nn, iflag;

    /* Parameter adjustments */
    --y;
    --x;

    /* Function Body */
    jj = (*m << 1) + 1;
    t = (real) jj;
    n = *m + 1;
    nn = *nt - n;
    nm = nn + 1;
    iflag = 0;
L4:
    ++iflag;
    i__1 = n;
    for (i__ = 1; i__ <= i__1; ++i__) {
/* L2: */
	y[i__] = 0.f;
    }
    i__1 = nn;
    for (i__ = n; i__ <= i__1; ++i__) {
	k = i__ + *m + 1;
	l = i__ - *m;
/* L10: */
	y[i__ + 1] = y[i__] + 1.f / t * (x[k] - x[l]);
    }
    i__1 = *nt;
    for (i__ = nm; i__ <= i__1; ++i__) {
/* L12: */
	y[i__] = 0.f;
    }
    if (iflag == 2) {
	goto L16;
    }
    i__1 = *nt;
    for (i__ = 1; i__ <= i__1; ++i__) {
/* L15: */
	x[i__] = y[i__];
    }
    goto L4;
L16:
    return 0;
} /* filter_ */

/* Subroutine */ int convlv_(integer *lx, real *xx, integer *ly, real *yy, 
	real *cc)
{
    /* System generated locals */
    integer i__1, i__2;

    /* Local variables */
    static integer i__, j, k;
    static real x;
    static integer ib, lc, ix;

    /* Parameter adjustments */
    --cc;
    --yy;
    --xx;

    /* Function Body */
    lc = *lx + *ly - 1;
    ib = *lx + 1;
    i__1 = lc;
    for (i__ = ib; i__ <= i__1; ++i__) {
/* L10: */
	cc[i__] = 0.f;
    }
    ix = *lx;
    i__1 = *lx;
    for (i__ = 1; i__ <= i__1; ++i__) {
	x = xx[ix];
	cc[ix] = 0.f;
	i__2 = *ly;
	for (j = 1; j <= i__2; ++j) {
	    k = ix + j;
	    cc[k - 1] += x * yy[j];
/* L20: */
	}
/* L30: */
	--ix;
    }
    return 0;
} /* convlv_ */

/* Subroutine */ int convs_(real *ts1, real *ts2, real *con, integer *lg2, 
	real *dt)
{
    /* System generated locals */
    integer i__1;
    real r__1, r__2;

    /* Builtin functions */
    integer pow_ii(integer *, integer *);
    double sqrt(doublereal);

    /* Local variables */
    static real a, b, c__;
    static integer j;
    static real f1, f2, f3, df;
    static integer np;
    static real aaa, bbb, ccc, amp, bmp;
    static integer ncp;
    static real cmp, scl, scal;
    extern /* Subroutine */ int coolb_(integer *, real *, real *);

    /* Parameter adjustments */
    --con;
    --ts2;
    --ts1;

    /* Function Body */
    ncp = pow_ii(&c__2, lg2);
    np = ncp << 1;
    coolb_(lg2, &ts1[1], &c_b115);
    coolb_(lg2, &ts2[1], &c_b115);
    i__1 = np;
    for (j = 1; j <= i__1; j += 2) {
	con[j] = ts1[j] * ts2[j] - ts1[j + 1] * ts2[j + 1];
/* L1: */
	con[j + 1] = ts1[j + 1] * ts2[j] + ts1[j] * ts2[j + 1];
    }
    df = 1.f / (*dt * ncp);
    a = 0.f;
    b = 0.f;
    c__ = 0.f;
    i__1 = ncp;
    for (j = 1; j <= i__1; j += 2) {
/* Computing 2nd power */
	r__1 = ts1[j];
/* Computing 2nd power */
	r__2 = ts1[j + 1];
	aaa = r__1 * r__1 + r__2 * r__2;
/* Computing 2nd power */
	r__1 = ts2[j];
/* Computing 2nd power */
	r__2 = ts2[j + 1];
	bbb = r__1 * r__1 + r__2 * r__2;
/* Computing 2nd power */
	r__1 = con[j];
/* Computing 2nd power */
	r__2 = con[j + 1];
	ccc = r__1 * r__1 + r__2 * r__2;
	amp = sqrt(aaa) * *dt;
	bmp = sqrt(bbb) * *dt;
	cmp = sqrt(ccc) * *dt * *dt;
	if (amp > a) {
	    f1 = df * (real) ((j - 1) / 2);
	}
	if (bmp > b) {
	    f2 = df * (real) ((j - 1) / 2);
	}
	if (cmp > c__) {
	    f3 = df * (real) ((j - 1) / 2);
	}
	a = dmax(a,amp);
	c__ = dmax(c__,cmp);
/* L3: */
	b = dmax(b,bmp);
    }
/*      WRITE(3,1111) A,F1 */
/*      WRITE(3,1113) B,F2 */
/*      WRITE(3,1115) C,F3 */
/* L1111: */
/* L1113: */
/* L1115: */
    coolb_(lg2, &con[1], &c_b259);
    coolb_(lg2, &ts1[1], &c_b259);
    coolb_(lg2, &ts2[1], &c_b259);
    scl = (real) ncp / *dt;
    scal = (real) ncp;
    i__1 = np;
    for (j = 1; j <= i__1; ++j) {
	con[j] /= scl;
	ts1[j] /= scal;
	ts2[j] /= scal;
	if (j <= ncp) {
	    con[j * 2] = 0.f;
	}
/* L2: */
	if (j > ncp) {
	    con[j] = 0.f;
	}
    }
    return 0;
} /* convs_ */

/* Subroutine */ int coolb_(integer *nn, real *deta, real *signi)
{
    /* System generated locals */
    integer i__1, i__2, i__3;

    /* Builtin functions */
    integer pow_ii(integer *, integer *);
    double sin(doublereal);

    /* Local variables */
    static integer i__, j, m, n;
    static real wi, wr;
    static integer mmax;
    static real theta, tempi;
    static integer istep;
    static real sinth, tempr, wstpi, wstpr;

/*     SCALING THE OUTPUT OF COOLB. */
/*     THE SPECTRUM OF A TIME DOMAIN SIGNAL COMPUTED BY COOLB (-1 CASE) CAN BE */
/*     TERMED THE "SPECTRA".  TO SCALE THIS "SPECTRA" TO THE SPECTRAL DENSITY, */
/*     THE RESULT OF AN ANALYTICAL COMPUTATION OF THE FOURIER TRANSFORM OF A FUNC */
/*     TIME INTERVAL, DT.  IN GOING FROM THE FREQUENCY DOMAIN TO THE TIME DOMAIN */
/*     (+1 CASE OF COOLB), THE OUTPUT MUST BE DIVIDED BY THE NUMBER OF POINTS, */
/*     N, IF THE TRANSFORM IS PERFORMED ON THE "SPECTRA" OR MUST BE DIVIDED BY */
/*     N*DT IF THE TRANSFORM IS PERFORMED ON THE SPECTRAL DENSITY.  THIS ACHIEVES */
    /* Parameter adjustments */
    --deta;

    /* Function Body */
    i__1 = *nn + 1;
    n = pow_ii(&c__2, &i__1);
    j = 1;
    i__1 = n;
    for (i__ = 1; i__ <= i__1; i__ += 2) {
	if (i__ - j >= 0) {
	    goto L2;
	} else {
	    goto L1;
	}
L1:
	tempr = deta[j];
	tempi = deta[j + 1];
	deta[j] = deta[i__];
	deta[j + 1] = deta[i__ + 1];
	deta[i__] = tempr;
	deta[i__ + 1] = tempi;
L2:
	m = n / 2;
L3:
	if (j - m <= 0) {
	    goto L5;
	} else {
	    goto L4;
	}
L4:
	j -= m;
	m /= 2;
	if (m - 2 >= 0) {
	    goto L3;
	} else {
	    goto L5;
	}
L5:
	j += m;
    }
    mmax = 2;
L6:
    if (mmax - n >= 0) {
	goto L10;
    } else {
	goto L7;
    }
L7:
    istep = mmax << 1;
    theta = *signi * 6.28318531f / (real) mmax;
    sinth = sin(theta / 2.f);
    wstpr = sinth * -2.f * sinth;
    wstpi = sin(theta);
    wr = 1.f;
    wi = 0.f;
    i__1 = mmax;
    for (m = 1; m <= i__1; m += 2) {
	i__2 = n;
	i__3 = istep;
	for (i__ = m; i__3 < 0 ? i__ >= i__2 : i__ <= i__2; i__ += i__3) {
	    j = i__ + mmax;
	    tempr = wr * deta[j] - wi * deta[j + 1];
	    tempi = wr * deta[j + 1] + wi * deta[j];
	    deta[j] = deta[i__] - tempr;
	    deta[j + 1] = deta[i__ + 1] - tempi;
	    deta[i__] += tempr;
/* L8: */
	    deta[i__ + 1] += tempi;
	}
	tempr = wr;
	wr = wr * wstpr - wi * wstpi + wr;
/* L9: */
	wi = wi * wstpr + tempr * wstpi + wi;
    }
    mmax = istep;
    goto L6;
L10:
    return 0;
} /* coolb_ */

/* Subroutine */ int fcon_(integer *jsta, integer *isrc, real *c__, integer *
	ir)
{
    /* Builtin functions */
    double sin(doublereal), cos(doublereal);

    /* Local variables */
    static real d__, r__, t;
    static integer ii;
    static real pi2;

/*    COORDINATE SYSTEMS USED SAME AS FOR DISSYN2.  X1 AXIS IS NORTH, */
/*        STRK MEASURED CLOCKWISE FROM IT. */
    /* Parameter adjustments */
    --c__;

    /* Function Body */
    if (*ir > 1) {
	return 0;
    }
    pi2 = .017453291666666666f;
    d__ = faul1_1.dip[*isrc - 1] * pi2;
    r__ = faul1_1.rake[*isrc - 1] * pi2;
    if (faul1_1.dip[*isrc - 1] > 90.f) {
	r__ = -r__;
    }
    t = (stat_1.az[*jsta - 1] - faul1_1.strk[*isrc - 1]) * pi2;
    c__[1] = sin(t * 2.f) * cos(r__) * sin(d__) + cos(t * 2.f) * sin(r__) * 
	    cos(d__) * sin(d__);
    c__[2] = cos(t) * cos(r__) * cos(d__) - sin(t) * sin(r__) * cos(d__ * 2.f)
	    ;
    c__[3] = sin(r__) * cos(d__) * sin(d__);
    c__[4] = cos(t * 2.f) * cos(r__) * sin(d__) - sin(t * 2.f) * sin(r__) * 
	    cos(d__) * sin(d__);
    c__[5] = -sin(t) * cos(r__) * cos(d__) - cos(t) * sin(r__) * cos(d__ * 
	    2.f);

/*  IF THE DIP>90,  THEN FOR RAKE=0 TO BE LEFT LATERAL, */
/*  AND FOR RAKE=+ TO BE A TRUE THRUST FAULT, THEN WE MUST CHANGE */
/*  THE POLARITY OF THE RAKE ANGLE. */

    if (d__ >= 0.f) {
	goto L1;
    }
    for (ii = 1; ii <= 5; ++ii) {
/* L2: */
	c__[ii] = -c__[ii];
    }
L1:
/*     WRITE(3,100) JSTA,ISRC */
/* L100: */
/*     WRITE(3,101) (C(I),I=1,5) */
/* L101: */
    return 0;
} /* fcon_ */

/* Subroutine */ int fttq_(integer *nt, real *dt, real *rq, real *fqw, 
	integer *iatten, real *taubm, real *taulm, real *tau)
{
    /* Format strings */
    static char fmt_120[] = "(1x,\002PARTIAL Q OPERATOR (FREQUENCY DOMAIN) F"
	    "OR # POINTS= \002,i10,1x,\002DT= \002,f10.3,1x,\002T/Q RATIO="
	    " \002,f10.3)";
    static char fmt_121[] = "(1x,\002MINSTER ATTENUATION OPERATOR WITH RQ="
	    " \002,f10.3,\002 TAUBM= \002,f10.3,\002 TAULM= \002,f10.4,\002 T"
	    "AU= \002,f10.1)";

    /* System generated locals */
    integer i__1, i__2;

    /* Builtin functions */
    integer pow_ii(integer *, integer *);
    double r_imag(complex *), exp(doublereal), log(doublereal), cos(
	    doublereal), sin(doublereal);
    integer s_wsfe(cilist *), do_fio(integer *, char *, ftnlen), e_wsfe(void);

    /* Local variables */
    static real a, b;
    static integer i__;
    static real w0, ck;
    static integer nc, nd, nf;
    static real ep, cr, si, fdf;
    static complex array[1025];
    extern /* Subroutine */ int mnstrq_(integer *, real *, real *, real *, 
	    real *, real *, complex *);

    /* Fortran I/O blocks */
    static cilist io___424 = { 0, 3, 0, fmt_120, 0 };
    static cilist io___425 = { 0, 3, 0, fmt_121, 0 };


/*     FUTTERMAN'S Q OPERATOR MODIFIED.  CONTAINS NONE OF THE PHASE */
/*     SHIFTS AND MADE TO USE THE RATIO T/Q. */
/*     NT=EXPONENT OF 2 (2**NT IS NUMBER OF POINTS) */
/*     DT=TIME SEPARATION IN THE TIME DOMAIN */
/*     RQ=RATIO T/Q */
/*     THIS VERSION OF FTTQ HAS BEEN CHECKED AND CORRECTED ON OCT. 19, 1978. */

/*     IF IATTEN IS EQUAL TO 0, A CONSTANT T STAR MODEL IS USED. */

/*     IF IATTEN IS EQUAL TO 1, PROGRAM USES MINSTER ATTENUATION OPERATOR. */
/*     MINSTER(1978)G.J.R. ASTR. SOC.,V52,507,EQUATION(2.2). */

/*     IF IATTEN IS EQUAL TO 2, PROGRAM CONSTRUCTS THE FRQUENCY DEPENDENT */
/*     T STAR OPERATOR OF CHOY AND CORMIER(1986)J.G.R.,V91,7326-7342, */
/*     EQUATION(6) FOR A SURFACE SOURCE. */

/*     NUMBER OF POINTS */
    /* Parameter adjustments */
    --fqw;

    /* Function Body */
    nd = pow_ii(&c__2, nt);
/*     FUNDEMENTAL FREQUENCY */
    fdf = 1.f / (nd * *dt);
/*     SAMPLING FREQUENCY */
    w0 = fdf * 6.283185f;
    fqw[1] = 1.f;
    fqw[2] = 0.f;
    nf = nd / 2;
    if (*iatten == 0) {
	goto L20;
    }
    if (*iatten == 1) {
	mnstrq_(nt, dt, rq, taubm, taulm, tau, array);
	fqw[1] = array[0].r;
	fqw[2] = -r_imag(array);
	i__1 = nf;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    i__2 = i__;
	    fqw[(i__ << 1) + 1] = array[i__2].r;
	    fqw[(i__ << 1) + 2] = -r_imag(&array[i__]);
	    nc = nd - i__;
	    fqw[(nc << 1) + 1] = fqw[(i__ << 1) + 1];
	    fqw[(nc << 1) + 2] = -fqw[(i__ << 1) + 2];
/* L21: */
	}
	goto L40;
    }

/*     THE REAL PART OF FQW IS CONTAINED IN THE ODD NUMBERED LOCATIONS */
/*     AND THE IMAGINARY PART IS IN THE EVEN LOCATIONS. */

/*     FOLDING FREQUENCY POINT */
L20:
    nf = nd / 2;
    i__1 = nf;
    for (i__ = 1; i__ <= i__1; ++i__) {
	ck = w0 * i__ * .5f * *rq;
	if (ck >= 60.f) {
	    ep = 0.f;
	    goto L30;
	}
	ep = exp(-w0 * i__ * .5f * *rq);
L30:
	a = w0 * i__ * *rq * .31830989f * log(w0 * i__);
/*     B IS AN ARBITRARY PHASE SHIFT. */
	b = w0 * i__ * 2.f;
	cr = cos(a) * cos(b) + sin(a) * sin(b);
	si = sin(b) * cos(a) - sin(a) * cos(b);
	fqw[(i__ << 1) + 1] = ep * cr;
	fqw[(i__ << 1) + 2] = ep * si;
	nc = nd - i__;
	fqw[(nc << 1) + 1] = fqw[(i__ << 1) + 1];
	fqw[(nc << 1) + 2] = -fqw[(i__ << 1) + 2];
/* L15: */
    }
L40:
    fqw[nd + 2] = 0.f;
/*     MAKING CORRECTION FOR CHANGE IN DEFN'S FOR FOURIER TRANSFORMS. */
    i__1 = nd;
    for (i__ = 1; i__ <= i__1; ++i__) {
/* L16: */
	fqw[i__ * 2] = -fqw[i__ * 2];
    }

/*     FREQ. DOMAIN Q-OPERATOR IS CORRECTLY SCALED. */
    if (*iatten == 0) {
	s_wsfe(&io___424);
	do_fio(&c__1, (char *)&nd, (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&(*dt), (ftnlen)sizeof(real));
	do_fio(&c__1, (char *)&(*rq), (ftnlen)sizeof(real));
	e_wsfe();
    }
    if (*iatten == 1) {
	s_wsfe(&io___425);
	do_fio(&c__1, (char *)&(*rq), (ftnlen)sizeof(real));
	do_fio(&c__1, (char *)&(*taubm), (ftnlen)sizeof(real));
	do_fio(&c__1, (char *)&(*taulm), (ftnlen)sizeof(real));
	do_fio(&c__1, (char *)&(*tau), (ftnlen)sizeof(real));
	e_wsfe();
    }
/* L10: */
    return 0;
} /* fttq_ */

/* Subroutine */ int mnstrq_(integer *nt, real *dt, real *tq, real *taubm, 
	real *taulm, real *tu, complex *array)
{
    /* System generated locals */
    integer i__1, i__2;
    real r__1;
    complex q__1, q__2, q__3, q__4, q__5, q__6, q__7, q__8, q__9, q__10, 
	    q__11, q__12, q__13, q__14, q__15, q__16;

    /* Builtin functions */
    integer pow_ii(integer *, integer *);
    void c_div(complex *, complex *, complex *), c_log(complex *, complex *), 
	    c_sqrt(complex *, complex *);
    double c_abs(complex *);
    void c_exp(complex *, complex *);

    /* Local variables */
    static complex a, i__;
    static integer j;
    static complex w, c1, c2;
    static real df, pi, qm;
    static integer np, np1;
    static complex cdf;
    static real cdt, cpi;
    static complex cqm, ctu, ctbm, ctlm, zero;
    static real wzero;
    static complex tstart;


/*     STANDARD LINEAR SOLID Q OPERATOR, COMPATIBLE WITH PREVIOUS */
/*     FUTTERMAN Q OPERATOR SUBROUTINE FORMAT. */
/*     NT...  LOG2 # OF TIME POINTS */
/*     DT...  TIME SEPARATION */
/*     TQ...  T STAR */
/*     ARRAY..FREQUENCY DOMAIN Q OPERATOR */
/*     QM...  TRAVEL TIME DIVIDED BY T STAR */
/*     TU...  TRAVEL TIME OF RAY */
/*     TAUBM..TAU BIG M */
/*     TAULM..TAU LITTLE M */
/*     SEE MINSTER(1978)G.J.R. ASTR. SOC.,V52,479-524,AND */
/*         BURGER(1987)BSSA,V77,1274. */

/*     DEFAULT VALUE */
    /* Parameter adjustments */
    --array;

    /* Function Body */
    tstart.r = 1.f, tstart.i = 0.f;
    qm = *tu / *tq;
    np = pow_ii(&c__2, nt);
    np1 = np / 2 + 1;
    df = 1.f / *dt / (real) np;
    pi = 3.1415926f;
    wzero = pi * 2.f * df;
    i__.r = 0.f, i__.i = 1.f;
    zero.r = 0.f, zero.i = 0.f;
    q__1.r = *dt, q__1.i = 0.f;
    cdt = q__1.r;
    c1.r = 1.f, c1.i = 0.f;
    c2.r = 2.f, c2.i = 0.f;
    q__1.r = df, q__1.i = 0.f;
    cdf.r = q__1.r, cdf.i = q__1.i;
    q__1.r = pi, q__1.i = 0.f;
    cpi = q__1.r;
    q__1.r = qm, q__1.i = 0.f;
    cqm.r = q__1.r, cqm.i = q__1.i;
    q__1.r = *tu, q__1.i = 0.f;
    ctu.r = q__1.r, ctu.i = q__1.i;
    r__1 = 1.f / *taubm;
    q__1.r = r__1, q__1.i = 0.f;
    ctbm.r = q__1.r, ctbm.i = q__1.i;
    r__1 = 1.f / *taulm;
    q__1.r = r__1, q__1.i = 0.f;
    ctlm.r = q__1.r, ctlm.i = q__1.i;
    i__1 = np1;
    for (j = 1; j <= i__1; ++j) {
	r__1 = wzero * (real) (j - 1);
	q__1.r = r__1, q__1.i = 0.f;
	w.r = q__1.r, w.i = q__1.i;
	q__3.r = i__.r * w.r - i__.i * w.i, q__3.i = i__.r * w.i + i__.i * 
		w.r;
	q__2.r = q__3.r * ctu.r - q__3.i * ctu.i, q__2.i = q__3.r * ctu.i + 
		q__3.i * ctu.r;
	q__14.r = i__.r * w.r - i__.i * w.i, q__14.i = i__.r * w.i + i__.i * 
		w.r;
	q__13.r = q__14.r + ctbm.r, q__13.i = q__14.i + ctbm.i;
	q__16.r = i__.r * w.r - i__.i * w.i, q__16.i = i__.r * w.i + i__.i * 
		w.r;
	q__15.r = q__16.r + ctlm.r, q__15.i = q__16.i + ctlm.i;
	c_div(&q__12, &q__13, &q__15);
	c_log(&q__11, &q__12);
	q__10.r = q__11.r * c2.r - q__11.i * c2.i, q__10.i = q__11.r * c2.i + 
		q__11.i * c2.r;
	q__9.r = q__10.r / cpi, q__9.i = q__10.i / cpi;
	c_div(&q__8, &q__9, &cqm);
	q__7.r = c1.r + q__8.r, q__7.i = c1.i + q__8.i;
	c_sqrt(&q__6, &q__7);
	c_div(&q__5, &c1, &q__6);
	q__4.r = c1.r - q__5.r, q__4.i = c1.i - q__5.i;
	q__1.r = q__2.r * q__4.r - q__2.i * q__4.i, q__1.i = q__2.r * q__4.i 
		+ q__2.i * q__4.r;
	a.r = q__1.r, a.i = q__1.i;
	if (c_abs(&a) + 174.673f >= 0.f) {
	    goto L11;
	} else {
	    goto L10;
	}
L10:
	i__2 = j;
	array[i__2].r = zero.r, array[i__2].i = zero.i;
	goto L1;
L11:
	i__2 = j;
	c_exp(&q__2, &a);
	q__6.r = -w.r, q__6.i = -w.i;
	q__5.r = q__6.r * i__.r - q__6.i * i__.i, q__5.i = q__6.r * i__.i + 
		q__6.i * i__.r;
	q__4.r = q__5.r * tstart.r - q__5.i * tstart.i, q__4.i = q__5.r * 
		tstart.i + q__5.i * tstart.r;
	c_exp(&q__3, &q__4);
	q__1.r = q__2.r * q__3.r - q__2.i * q__3.i, q__1.i = q__2.r * q__3.i 
		+ q__2.i * q__3.r;
	array[i__2].r = q__1.r, array[i__2].i = q__1.i;
L1:
	;
    }
    return 0;
} /* mnstrq_ */

/* Subroutine */ int interp_(integer *n, real *x, real *y, integer *np, real *
	xf, real *yf, integer *i__)
{
    static real b;
    static integer j;
    static real slp;

/*     LINEAR INTERPOLATION PROGRAM */
/*     N - NUMBER OF POINTS IN ARRAYS X AND Y. */
/*     X - UNEQUAL ABSCISSA VALUES. */
/*     Y - UNEQUAL INTERVAL DATA. */
/*     NP - NUMBER OF POINTS DESIRED. */
/*     XF - EQUAL INTERVAL ABSCISSA. */
/*     YF - EQUAL INTERVAL DATA. */
    /* Parameter adjustments */
    --yf;
    --xf;
    --y;
    --x;

    /* Function Body */
    j = 1;
    *i__ = 1;
L25:
    if (xf[*i__] > x[j]) {
	goto L30;
    }
    yf[*i__] = 0.f;
    if (*i__ >= *np) {
	goto L20;
    }
    ++(*i__);
    goto L25;
L30:
L15:
    if (xf[*i__] > x[j]) {
	goto L10;
    }
    slp = (y[j] - y[j - 1]) / (x[j] - x[j - 1]);
    b = -slp * x[j] + y[j];
    yf[*i__] = slp * xf[*i__] + b;
    if (*i__ >= *np) {
	goto L20;
    }
    ++(*i__);
    goto L15;
L10:
    if (j >= *n) {
	goto L20;
    }
    ++j;
    goto L15;
L20:
    --(*i__);
    return 0;
} /* interp_ */

/* Subroutine */ int recev_(integer *jsta, integer *isrc, integer *npts, 
	integer *los)
{
    /* System generated locals */
    integer i__1;
    real r__1;

    /* Local variables */
    static integer i__, j;
    static real r1, t2, ea, eb, dn, pc, cp;
    extern doublereal cr_(real *, real *);
    static real rp, sp, sr, rec, rpb, cons, ratio;

/*     RI - GEOMETRICAL SPREADING FACTOR. */
/*     DIS - DISTANCE IN DEGREES. */
/*        CALCULATING THE APPROPRIATE RECEIVER FUNCTION */
    pc = stat_1.p[*jsta - 1];
    cp = stat_1.cre[*jsta - 1];
    sp = stat_1.sre[*jsta - 1];
    ea = cr_(&pc, &cp);
    eb = cr_(&pc, &sp);
/* Computing 2nd power */
    r__1 = eb * eb - pc * pc;
    rp = r__1 * r__1 + pc * 4.f * pc * ea * eb;
    rpb = rp * sp * sp;
/*        VERTICAL P WAVES */
    if (sconv_1.ncomp == 1 && sconv_1.mode == 1) {
	sr = ea * 2.f * (eb * eb - pc * pc);
    }
/*        RADIAL P WAVES */
    if (sconv_1.ncomp == 2 && sconv_1.mode == 1) {
	sr = ea * -4.f * eb * pc;
    }
/*        VERTICAL SV WAVES */
    if (sconv_1.ncomp == 1 && sconv_1.mode == 2) {
	sr = pc * 4.f * ea * eb;
    }
/*        RADIAL SV WAVES */
    if (sconv_1.ncomp == 2 && sconv_1.mode == 2) {
	sr = eb * 2.f * (eb * eb - pc * pc);
    }
/*        NOTE THAT SIGN CHANGE IS FOR VERTICAL COMP SO THAT UP IS +VE. */
    if (sconv_1.ncomp == 1) {
	sr = -sr;
    }
    rec = sr / rpb;
    if (sconv_1.mode == 3) {
	rec = pc * 2.f;
    }
/*     WRITE(3,100) REC */
/* L100: */
/*        INTERPOLATING TO FIND THE CORRECT 1/R FACTOR */
    if (stat_1.del[*jsta - 1] < rinv_1.dis[0]) {
	r1 = rinv_1.ri[0];
	goto L200;
    }
    if (stat_1.del[*jsta - 1] > rinv_1.dis[15]) {
	r1 = rinv_1.ri[15];
	goto L200;
    }
    for (i__ = 1; i__ <= 15; ++i__) {
	j = i__;
	if (stat_1.del[*jsta - 1] >= rinv_1.dis[i__ - 1] && stat_1.del[*jsta 
		- 1] <= rinv_1.dis[i__]) {
	    goto L16;
	}
/* L10: */
    }
L16:
    dn = stat_1.del[*jsta - 1] - rinv_1.dis[j - 1];
    ratio = dn / (rinv_1.dis[j] - rinv_1.dis[j - 1]);
    r1 = ratio * (rinv_1.ri[j] - rinv_1.ri[j - 1]) + rinv_1.ri[j - 1];
/*     WRITE(3,101) R1 */
/* L101: */
/*        FINAL SCALING CONSTANT FOR MICRONS SCALING */
L200:
    t2 = 1e-16f;
    cons = t2 * rec * r1 * faul1_1.fmnt[*isrc - 1] / (orst_2.d__[*los - 1] * 
	    12.56636f);
/*     WRITE(3,102) CONS,ISRC */
/* L102: */
    i__1 = *npts;
    for (i__ = 1; i__ <= i__1; ++i__) {
/* L20: */
	sconv_1.pp[i__ - 1] *= cons;
    }
    return 0;
} /* recev_ */

doublereal cr_(real *p, real *v)
{
    /* System generated locals */
    real ret_val;

    /* Builtin functions */
    double sqrt(doublereal);

    ret_val = sqrt(1.f / (*v * *v) - *p * *p);
    return ret_val;
} /* cr_ */

/* Subroutine */ int scon_(real *f, real *dt, integer *npts, integer *npl, 
	real *dt1, real *dt2, real *dt3)
{
    /* System generated locals */
    integer i__1;

    /* Builtin functions */
    double cos(doublereal), sin(doublereal);

    /* Local variables */
    static real a;
    static integer i__, n;
    static real w, c1, d1, d2, d3, c2, c3;
    static integer i1, i2;
    static real m1, m3, s1, s2, s3, w0, w1;
    static integer nf, in1, in2;

/*     THIS VERSION OF SCON HAS BEEN CHECKED AND CORRECTED ON OCT. 19, 1978. */
    /* Parameter adjustments */
    --f;

    /* Function Body */
    n = *npts << 1;
/*        CONSTRUCTING F'S.  ZERO FREQ AMP IS SET TO ZERO. */
/*        SAMPLING FREQUENCY */
    w0 = 6.283185f / (*npts * *dt);
/*        FOLDING FREQUENCY POINT */
    nf = *npts / 2;
    i__1 = n;
    for (i__ = 1; i__ <= i__1; ++i__) {
/* L10: */
	f[i__] = 0.f;
    }
    d1 = *dt1;
    d2 = *dt1 + *dt2;
    d3 = d2 + *dt3;
    m1 = 1.f / d1;
    m3 = 1.f / *dt3;
/*     A IS THE AREA UNDER THE TRAPEZOID. */
    a = 1.f / (*dt1 * .5f + *dt2 + *dt3 * .5f);
    f[1] = 1.f / a;
    f[2] = 0.f;
    i__1 = nf;
    for (i__ = 1; i__ <= i__1; ++i__) {
	w = w0 * i__;
	w1 = w * w;
	c1 = cos(w * d1);
	c2 = cos(w * d2);
	c3 = cos(w * d3);
	s1 = sin(w * d1);
	s2 = sin(w * d2);
	s3 = sin(w * d3);
	i1 = (i__ << 1) + 1;
	i2 = (i__ << 1) + 2;
	f[i1] = -(m1 * (1.f - c1) + m3 * (c3 - c2)) / w1;
	f[i2] = -(m1 * s1 + m3 * (-s3 + s2)) / w1;
	in1 = (*npts - i__ << 1) + 1;
	in2 = (*npts - i__ << 1) + 2;
	f[in1] = f[i1];
/* L15: */
	f[in2] = -f[i2];
    }
/*     THIS STEP IS INSERTED TO CONFORM TO THE THEOREM PROVED IN THE FT NOTES. */
    f[*npts + 2] = 0.f;
    i__1 = n;
    for (i__ = 1; i__ <= i__1; ++i__) {
/* L16: */
	f[i__] = a * f[i__];
    }
/*     FREQ. DOMAIN TIME FUNCTION IS CORRECTLY SCALED. */
    return 0;
} /* scon_ */

/* Subroutine */ int ttlag_(integer *js, integer *is, real *dt, integer *np, 
	real *sn, real *se)
{
    /* System generated locals */
    integer i__1;

    /* Builtin functions */
    double cos(doublereal), sin(doublereal);

    /* Local variables */
    static real a, d__;
    static integer i__;
    static real pt[4096];
    static integer np1;
    static real dlag;
    static integer nlag;

/*    THIS SUBROUTINE LAGS THE RESPONSE IN TIME DUE TO RUPTURE (TLAG) AND */
/*        SPATIAL DISRIBUTION OF THE POINT SOURCES. THE LAG DUE TO DEPTH */
/*        HAS BEEN TAKEN CARE OF WHEN DISWHIT WAS CALLED. */
/*     JS - INDEX OF STATION. */
/*     IS - INDEX OF SOURCE. */
    a = stat_1.az[*js - 1] * 6.283185f / 360.f;
    d__ = (faul1_1.xc[*is - 1] + *sn) * cos(a) + (faul1_1.yc[*is - 1] + *se) *
	     sin(a);
    d__ = -d__ * stat_1.p[*js - 1];
    dlag = d__ + faul1_1.tlag[*is - 1];
/*     WRITE(3,100) DLAG,IS,JS */
/* L100: */
/*     WRITE(3,101) XC(IS),YC(IS),SN,SE */
/* L101: */
    i__1 = *np;
    for (i__ = 1; i__ <= i__1; ++i__) {
/* L5: */
	pt[i__ - 1] = 0.f;
    }
    nlag = (integer) (dlag / *dt);
    if (nlag >= *np) {
	goto L10;
    }
    if (nlag == 0) {
	return 0;
    }
    if (nlag < 0) {
	goto L18;
    }
    np1 = *np - nlag;
    i__1 = np1;
    for (i__ = 1; i__ <= i__1; ++i__) {
/* L15: */
	pt[i__ + nlag - 1] = sconv_1.pp[i__ - 1];
    }
    i__1 = *np;
    for (i__ = 1; i__ <= i__1; ++i__) {
/* L16: */
	sconv_1.pp[i__ - 1] = pt[i__ - 1];
    }
    return 0;
L10:
    i__1 = *np;
    for (i__ = 1; i__ <= i__1; ++i__) {
/* L17: */
	sconv_1.pp[i__ - 1] = 0.f;
    }
    return 0;
L18:
    np1 = *np + nlag;
    i__1 = np1;
    for (i__ = 1; i__ <= i__1; ++i__) {
/* L19: */
	pt[i__ - 1] = sconv_1.pp[i__ - nlag - 1];
    }
    i__1 = *np;
    for (i__ = 1; i__ <= i__1; ++i__) {
/* L20: */
	sconv_1.pp[i__ - 1] = pt[i__ - 1];
    }
    return 0;
} /* ttlag_ */

/* Subroutine */ int vector_(real *p, real *v, real *az, real *strk, real *
	dip, real *frake, real *ang, real *ang1, integer *m, integer *line)
{
    /* Format strings */
    static char fmt_600[] = "(3x,\002VECTOR \002,9f11.5)";

    /* System generated locals */
    real r__1, r__2, r__3;

    /* Builtin functions */
    double asin(doublereal), sin(doublereal), cos(doublereal);
    integer s_wsfe(cilist *), do_fio(integer *, char *, ftnlen), e_wsfe(void);
    double acos(doublereal);

    /* Local variables */
    static real a, d__, x, y, z__, x1, y1, z1, ai, aih, rad, caih, saih, dist;

    /* Fortran I/O blocks */
    static cilist io___500 = { 0, 3, 0, fmt_600, 0 };
    static cilist io___506 = { 0, 3, 0, fmt_600, 0 };
    static cilist io___511 = { 0, 3, 0, fmt_600, 0 };


    rad = .017453f;
/*     COMPUTE TAKE-OFF ANGLE. */
/*     MEASURE DIP OF FAULT FROM DOWNWARD VERTICAL. */
    *dip = 90.f - *dip;
    aih = *p * *v;
    ai = asin(aih);
    if (*m == 2 || *m == 4) {
	ai = 3.1415926f - ai;
    }
    saih = sin(ai);
    caih = cos(ai);
    ai /= rad;
    if (bug_1.ibug == 1) {
	s_wsfe(&io___500);
	do_fio(&c__1, (char *)&(*p), (ftnlen)sizeof(real));
	do_fio(&c__1, (char *)&(*v), (ftnlen)sizeof(real));
	do_fio(&c__1, (char *)&(*az), (ftnlen)sizeof(real));
	do_fio(&c__1, (char *)&aih, (ftnlen)sizeof(real));
	do_fio(&c__1, (char *)&ai, (ftnlen)sizeof(real));
	do_fio(&c__1, (char *)&saih, (ftnlen)sizeof(real));
	do_fio(&c__1, (char *)&caih, (ftnlen)sizeof(real));
	e_wsfe();
    }
    *az *= rad;
    x = cos(*az) * saih;
    y = sin(*az) * saih;
    z__ = caih;
    if (*line == 1) {
	goto L14;
    }
/*     COMPUTE POLE TO FAULT PLANE. */
    a = *strk + 270.f;
    d__ = 90.f - *dip;
    goto L13;
/*     COMPUTE AZIMUTH AND DIP OF FAULT PROPAGATION VECTOR. */
L14:
    if (*frake == 0.f) {
	goto L10;
    }
    if (*frake == 270.f) {
	goto L11;
    }
    if (*frake == 180.f) {
	goto L12;
    }
    a = *strk + 270.f;
    d__ = 180.f - *dip;
    goto L13;
L10:
    a = *strk;
    d__ = 90.f;
    goto L13;
L11:
    a = *strk + 90.f;
    d__ = *dip;
    goto L13;
L12:
    a = *strk + 180.f;
    d__ = 90.f;
L13:
    if (a > 360.f) {
	a += -360.f;
    }
    if (bug_1.ibug == 1) {
	s_wsfe(&io___506);
	do_fio(&c__1, (char *)&(*strk), (ftnlen)sizeof(real));
	do_fio(&c__1, (char *)&(*dip), (ftnlen)sizeof(real));
	do_fio(&c__1, (char *)&(*frake), (ftnlen)sizeof(real));
	do_fio(&c__1, (char *)&a, (ftnlen)sizeof(real));
	do_fio(&c__1, (char *)&d__, (ftnlen)sizeof(real));
	e_wsfe();
    }
    a *= rad;
    d__ *= rad;
    x1 = cos(a) * sin(d__);
    y1 = sin(a) * sin(d__);
    z1 = cos(d__);
/* Computing 2nd power */
    r__1 = x - x1;
/* Computing 2nd power */
    r__2 = y - y1;
/* Computing 2nd power */
    r__3 = z__ - z1;
    dist = r__1 * r__1 + r__2 * r__2 + r__3 * r__3;
    *ang = (2.f - dist) / 2.f;
    *ang1 = acos(*ang);
    *ang1 /= rad;
    *az /= rad;
    *dip = 90.f - *dip;
    if (bug_1.ibug == 1) {
	s_wsfe(&io___511);
	do_fio(&c__1, (char *)&(*ang), (ftnlen)sizeof(real));
	do_fio(&c__1, (char *)&(*ang1), (ftnlen)sizeof(real));
	do_fio(&c__1, (char *)&dist, (ftnlen)sizeof(real));
	do_fio(&c__1, (char *)&x, (ftnlen)sizeof(real));
	do_fio(&c__1, (char *)&x1, (ftnlen)sizeof(real));
	do_fio(&c__1, (char *)&y, (ftnlen)sizeof(real));
	do_fio(&c__1, (char *)&y1, (ftnlen)sizeof(real));
	do_fio(&c__1, (char *)&z__, (ftnlen)sizeof(real));
	do_fio(&c__1, (char *)&z1, (ftnlen)sizeof(real));
	e_wsfe();
    }
    return 0;
} /* vector_ */

/* Subroutine */ int haskel_(real *f, real *dt, integer *np, real *c__, real *
	l, real *vr, real *t, real *ang)
{
    /* Format strings */
    static char fmt_601[] = "(3x,i5,8f11.5)";
    static char fmt_600[] = "(3x,10e12.5)";

    /* System generated locals */
    integer i__1;
    real r__1;

    /* Builtin functions */
    integer s_wsfe(cilist *), do_fio(integer *, char *, ftnlen), e_wsfe(void);
    double cos(doublereal), sin(doublereal);

    /* Local variables */
    static real a;
    static integer i__;
    static real q, r__, w;
    static integer i1, i2, nf;
    static real cq, sq, ws;
    static integer in1, in2, np2;
    static real rad, tau, denom;

    /* Fortran I/O blocks */
    static cilist io___516 = { 0, 3, 0, fmt_601, 0 };
    static cilist io___530 = { 0, 3, 0, fmt_600, 0 };


/*     C - WAVE VELOCITY IN SOURCE REGION. */
/*     L - FAULT LENGTH. */
/*     VR - RUPTURE VELOCITY. */
/*     T - TIME CONSTANT OF THE DISLOCATION MODEL. */
/*     ANG - ANGLE BETWEEN RAY TAKE-OFF ANGLE AND FAULT PRPAGATION VECTOR. */
    /* Parameter adjustments */
    --f;

    /* Function Body */
    rad = .017453f;
/*     ANG=ANG*RAD */
    tau = *l / *c__ * (*c__ / *vr - *ang);
    np2 = *np << 1;
/*     SAMPLING FREQUENCY. */
    ws = 6.283185f / (*np * *dt);
    if (bug_1.ibug == 1) {
	s_wsfe(&io___516);
	do_fio(&c__1, (char *)&(*np), (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&(*dt), (ftnlen)sizeof(real));
	do_fio(&c__1, (char *)&(*c__), (ftnlen)sizeof(real));
	do_fio(&c__1, (char *)&(*l), (ftnlen)sizeof(real));
	do_fio(&c__1, (char *)&(*vr), (ftnlen)sizeof(real));
	do_fio(&c__1, (char *)&(*t), (ftnlen)sizeof(real));
	do_fio(&c__1, (char *)&(*ang), (ftnlen)sizeof(real));
	do_fio(&c__1, (char *)&tau, (ftnlen)sizeof(real));
	do_fio(&c__1, (char *)&ws, (ftnlen)sizeof(real));
	e_wsfe();
    }
/*     FOLDING FREQUENCY POINT. */
    nf = *np / 2;
    i__1 = np2;
    for (i__ = 1; i__ <= i__1; ++i__) {
/* L10: */
	f[i__] = 0.f;
    }
    f[1] = 1.f;
    f[2] = 0.f;
    i__1 = nf;
    for (i__ = 1; i__ <= i__1; ++i__) {
	w = ws * i__;
	i1 = (i__ << 1) + 1;
	i2 = (i__ << 1) + 2;
	q = w * tau / 2.f;
	cq = cos(q);
	sq = sin(q);
	r__ = sq / q;
/* Computing 2nd power */
	r__1 = *t * w;
	denom = r__1 * r__1 + 1.f;
/*     A REPRESENTS AN ARBITRARY TIME SHIFT IN SECONDS. */
	a = 5.f;
	a = w * a;
	f[i1] = r__ * cos(a) * (-sq * w * *t / denom + cq / denom);
	f[i2] = -r__ * sin(a) * (cq * *t * w / denom - sq / denom);
	in1 = (*np - i__ << 1) + 1;
	in2 = (*np - i__ << 1) + 2;
	f[in1] = f[i1];
/* L15: */
	f[in2] = -f[i2];
    }
    f[*np + 2] = 0.f;
    if (bug_1.ibug == 1) {
	s_wsfe(&io___530);
	for (i__ = 1; i__ <= 200; ++i__) {
	    do_fio(&c__1, (char *)&f[i__], (ftnlen)sizeof(real));
	}
	e_wsfe();
    }
    return 0;
} /* haskel_ */

/* Subroutine */ int jill_(integer *is, real *dip, real *hypd, real *xl, real 
	*lend, integer *jo)
{
    /* Format strings */
    static char fmt_1100[] = "(1x,\002WHAT IS THE FAULT LENGTH?\002)";
    static char fmt_102[] = "(1x,\002ENTER THE NUMBER OF WEIGHTS TO BE ENTER"
	    "ED ALONG STRIKE\002)";
    static char fmt_1101[] = "(1x,\002HOW MANY INTERMEDIATE POINTS ALONG STR"
	    "IKE?\002)";
    static char fmt_1102[] = "(1x,\002WHAT ARE THE TOP AND BOTTOM DEPTHS OF "
	    "THE FAULT?\002)";
    static char fmt_1103[] = "(1x,\002HOW MANY POINT SOURCES DOWN THE DIP"
	    "?\002)";
    static char fmt_1104[] = "(1x,\002HOW MANY INTERMEDIATE POINT SOURCES DO"
	    "WN THE DIP?\002)";
    static char fmt_344[] = "(30f3.0)";
    static char fmt_1105[] = "(1x,\002WHAT IS THE HYPOCENTRAL DEPTH?\002)";
    static char fmt_1106[] = "(1x,\002WHAT IS THE DISTANCE ALONG STRIKE OF T"
	    "HE HYPOCENTER?\002)";
    static char fmt_108[] = "(1x,\002ENTER THE RUPTURE VELOCITY\002)";
    static char fmt_1107[] = "(1x,\002HOW MANY SUBFAULTS?\002)";
    static char fmt_1108[] = "(1x,\002THE SUBFAULT RUNS FROM WHERE TO WHERE "
	    "ALONG THE STRIKE;  GIVE THE FINE GRID SPACING\002)";
    static char fmt_1109[] = "(1x,\002THE SUBFAULT RUNS BETWEEN WHICH TWO DE"
	    "PTHS?\002)";
    static char fmt_3004[] = "(1x,20f5.2)";
    static char fmt_200[] = "(\002         FAULT #\002,i1)";
    static char fmt_201[] = "(1x,\002FAULT LENGTH IS \002,f6.3,\002KM\002)";
    static char fmt_202[] = "(1x,\002NUMBER OF COARSE GRID POINTS ALONG STRI"
	    "KE =\002,i2)";
    static char fmt_203[] = "(1x,\002NUMBER OF INTERMEDIATE GRID POINTS ALON"
	    "G STRIKE=\002,i2)";
    static char fmt_204[] = "(1x,\002TOTAL NUMBER GRID POINTS ALONG STRIKE"
	    "=\002,i3,\002 ;DSX=\002,f6.4)";
    static char fmt_205[] = "(\002 TOP AND BOTTOM DEPTHS OF FAULT ARE \002,f"
	    "6.3,\002 AND \002,f6.3)";
    static char fmt_206[] = "(\002 FAULT WIDTH IS \002,f6.3,\002KM\002)";
    static char fmt_207[] = "(\002 NUMBER OF COARSE GRID POINTS DOWN DIP IS"
	    " \002,i2)";
    static char fmt_208[] = "(\002 NUMBER OF INTERMEDIATE GRID POINTS DOWN D"
	    "IP IS \002,i2)";
    static char fmt_209[] = "(\002 NUMBER OF TOTAL GRID POINTS DOWN DIP ="
	    "\002,i3,\002 ;DSY=\002,f6.4)";
    static char fmt_210[] = "(\002 HYPOCENTER IS \002,f6.3,\002 ALONG STRIKE"
	    " AND \002,f6.3,\002 DOWN DIP\002)";
    static char fmt_211[] = "(\002 CLOSEST GRID POINT IS \002,i3,\002 ACCROS"
	    "S BY \002,i3,\002 DOWN\002)";
    static char fmt_212[] = "(\002 THE RUPTURE VELOCITY IS \002,f6.3,\002KM/"
	    "SEC\002)";
    static char fmt_213[] = "(\002 THERE ARE \002,i3,\002 SUBFAULTS\002)";
    static char fmt_214[] = "(\002 SUBFAULT NUMBER \002,i3,\002 IS BETWEEN T"
	    "HE DEPTHS OF \002,f7.3,\002 AND \002,f7.3,\002 AND RUNS BETWEEN "
	    "THE STRIKE INDICES OF \002,i3,\002 AND \002,i3)";

    /* System generated locals */
    integer i__1, i__2, i__3;

    /* Builtin functions */
    integer s_wsfe(cilist *), e_wsfe(void), s_rsle(cilist *), do_lio(integer *
	    , integer *, char *, ftnlen), e_rsle(void), s_rsfe(cilist *), 
	    do_fio(integer *, char *, ftnlen), e_rsfe(void);
    double sin(doublereal);

    /* Local variables */
    static integer i__, j, i2, j2, j3, j4, i3, i4;
    static real bd, yl;
    static integer nnx, nny, nsu, ntx, nty, nxx, nyy, nddx, nddy, jsub, nttx, 
	    ntty;
    static real bweigh[231]	/* was [21][11] */;
    extern /* Subroutine */ int moment_(integer *, real *, integer *);

    /* Fortran I/O blocks */
    static cilist io___531 = { 0, 6, 0, fmt_1100, 0 };
    static cilist io___532 = { 0, 5, 0, 0, 0 };
    static cilist io___533 = { 0, 6, 0, fmt_102, 0 };
    static cilist io___534 = { 0, 5, 0, 0, 0 };
    static cilist io___535 = { 0, 6, 0, fmt_1101, 0 };
    static cilist io___536 = { 0, 5, 0, 0, 0 };
    static cilist io___537 = { 0, 6, 0, fmt_1102, 0 };
    static cilist io___538 = { 0, 5, 0, 0, 0 };
    static cilist io___540 = { 0, 6, 0, fmt_1103, 0 };
    static cilist io___541 = { 0, 5, 0, 0, 0 };
    static cilist io___542 = { 0, 6, 0, fmt_1104, 0 };
    static cilist io___543 = { 0, 5, 0, 0, 0 };
    static cilist io___547 = { 0, 9, 0, fmt_344, 0 };
    static cilist io___550 = { 0, 6, 0, fmt_1105, 0 };
    static cilist io___551 = { 0, 5, 0, 0, 0 };
    static cilist io___552 = { 0, 6, 0, fmt_1106, 0 };
    static cilist io___553 = { 0, 5, 0, 0, 0 };
    static cilist io___554 = { 0, 6, 0, fmt_108, 0 };
    static cilist io___555 = { 0, 5, 0, 0, 0 };
    static cilist io___556 = { 0, 6, 0, fmt_1107, 0 };
    static cilist io___557 = { 0, 5, 0, 0, 0 };
    static cilist io___560 = { 0, 6, 0, fmt_1108, 0 };
    static cilist io___561 = { 0, 5, 0, 0, 0 };
    static cilist io___562 = { 0, 6, 0, fmt_1109, 0 };
    static cilist io___563 = { 0, 5, 0, 0, 0 };
    static cilist io___572 = { 0, 3, 0, fmt_3004, 0 };
    static cilist io___580 = { 0, 3, 0, fmt_200, 0 };
    static cilist io___581 = { 0, 3, 0, fmt_201, 0 };
    static cilist io___582 = { 0, 3, 0, fmt_202, 0 };
    static cilist io___583 = { 0, 3, 0, fmt_203, 0 };
    static cilist io___584 = { 0, 3, 0, fmt_204, 0 };
    static cilist io___585 = { 0, 3, 0, fmt_205, 0 };
    static cilist io___586 = { 0, 3, 0, fmt_206, 0 };
    static cilist io___587 = { 0, 3, 0, fmt_207, 0 };
    static cilist io___588 = { 0, 3, 0, fmt_208, 0 };
    static cilist io___589 = { 0, 3, 0, fmt_209, 0 };
    static cilist io___590 = { 0, 3, 0, fmt_210, 0 };
    static cilist io___591 = { 0, 3, 0, fmt_211, 0 };
    static cilist io___592 = { 0, 3, 0, fmt_212, 0 };
    static cilist io___593 = { 0, 3, 0, fmt_213, 0 };
    static cilist io___594 = { 0, 3, 0, fmt_214, 0 };


/*  JILL READS IN THE INFORMATION FOR A FINITE FAULT. */
/*       DATA BWEIGH/300*1./ */
    s_wsfe(&io___531);
    e_wsfe();
    s_rsle(&io___532);
    do_lio(&c__4, &c__1, (char *)&(*xl), (ftnlen)sizeof(real));
    e_rsle();
    s_wsfe(&io___533);
    e_wsfe();
    s_rsle(&io___534);
    do_lio(&c__3, &c__1, (char *)&tail_1.nx[*is - 1], (ftnlen)sizeof(integer))
	    ;
    e_rsle();
    s_wsfe(&io___535);
    e_wsfe();
    s_rsle(&io___536);
    do_lio(&c__3, &c__1, (char *)&tail_1.ndx[*is - 1], (ftnlen)sizeof(integer)
	    );
    e_rsle();
    s_wsfe(&io___537);
    e_wsfe();
    s_rsle(&io___538);
    do_lio(&c__4, &c__1, (char *)&tail_1.dtd[*is - 1], (ftnlen)sizeof(real));
    do_lio(&c__4, &c__1, (char *)&bd, (ftnlen)sizeof(real));
    e_rsle();
    s_wsfe(&io___540);
    e_wsfe();
    s_rsle(&io___541);
    do_lio(&c__3, &c__1, (char *)&tail_1.ny[*is - 1], (ftnlen)sizeof(integer))
	    ;
    e_rsle();
    s_wsfe(&io___542);
    e_wsfe();
    s_rsle(&io___543);
    do_lio(&c__3, &c__1, (char *)&tail_1.ndy[*is - 1], (ftnlen)sizeof(integer)
	    );
    e_rsle();
    nyy = tail_1.ny[*is - 1];
    nxx = tail_1.nx[*is - 1];
    i__1 = nyy;
    for (j = 1; j <= i__1; ++j) {
	s_rsfe(&io___547);
	i__2 = nxx;
	for (i__ = 1; i__ <= i__2; ++i__) {
	    do_fio(&c__1, (char *)&bweigh[i__ + j * 21 - 22], (ftnlen)sizeof(
		    real));
	}
	e_rsfe();
/* L343: */
    }
    s_wsfe(&io___550);
    e_wsfe();
    s_rsle(&io___551);
    do_lio(&c__4, &c__1, (char *)&(*hypd), (ftnlen)sizeof(real));
    e_rsle();
    s_wsfe(&io___552);
    e_wsfe();
    s_rsle(&io___553);
    do_lio(&c__4, &c__1, (char *)&(*lend), (ftnlen)sizeof(real));
    e_rsle();
    s_wsfe(&io___554);
    e_wsfe();
    s_rsle(&io___555);
    do_lio(&c__4, &c__1, (char *)&tail_1.rv[*is - 1], (ftnlen)sizeof(real));
    e_rsle();
    s_wsfe(&io___556);
    e_wsfe();
    s_rsle(&io___557);
    do_lio(&c__3, &c__1, (char *)&subf_1.nsub[*is - 1], (ftnlen)sizeof(
	    integer));
    e_rsle();
    jsub = subf_1.nsub[*is - 1];
    i__1 = jsub;
    for (nsu = 1; nsu <= i__1; ++nsu) {
	s_wsfe(&io___560);
	e_wsfe();
	s_rsle(&io___561);
	do_lio(&c__3, &c__1, (char *)&subf_1.ibx1[nsu + *is * 300 - 301], (
		ftnlen)sizeof(integer));
	do_lio(&c__3, &c__1, (char *)&subf_1.iex1[nsu + *is * 300 - 301], (
		ftnlen)sizeof(integer));
	e_rsle();
	s_wsfe(&io___562);
	e_wsfe();
	s_rsle(&io___563);
	do_lio(&c__4, &c__1, (char *)&subf_1.by1[nsu + *is * 300 - 301], (
		ftnlen)sizeof(real));
	do_lio(&c__4, &c__1, (char *)&subf_1.ey1[nsu + *is * 300 - 301], (
		ftnlen)sizeof(real));
	e_rsle();
	if (subf_1.ibx1[nsu + *is * 300 - 301] < 1) {
	    subf_1.ibx1[nsu + *is * 300 - 301] = 1;
	}
	if (subf_1.by1[nsu + *is * 300 - 301] < .001f) {
	    subf_1.by1[nsu + *is * 300 - 301] = .001f;
	}
	ntx = (tail_1.ndx[*is - 1] + 1) * (tail_1.nx[*is - 1] - 1) + 1;
	if (subf_1.iex1[nsu + *is * 300 - 301] > ntx) {
	    subf_1.iex1[nsu + *is * 300 - 301] = ntx;
	}
	if (subf_1.by1[nsu + *is * 300 - 301] < tail_1.dtd[*is - 1]) {
	    subf_1.by1[nsu + *is * 300 - 301] = tail_1.dtd[*is - 1];
	}
	if (subf_1.ey1[nsu + *is * 300 - 301] > bd) {
	    subf_1.ey1[nsu + *is * 300 - 301] = bd;
	}
/* L1979: */
    }
    ntx = (tail_1.ndx[*is - 1] + 1) * (tail_1.nx[*is - 1] - 1) + 1;
    nty = (tail_1.ndy[*is - 1] + 1) * (tail_1.ny[*is - 1] - 1) + 1;
    nddx = tail_1.ndx[*is - 1] + 1;
    nddy = tail_1.ndy[*is - 1] + 1;
    ntty = nty - 1;
    nttx = ntx - 1;
    i__1 = nyy;
    for (j = 1; j <= i__1; ++j) {
	i__2 = nxx;
	for (i__ = 1; i__ <= i__2; ++i__) {
	    nnx = (i__ - 1) * (tail_1.ndx[*is - 1] + 1) + 1;
	    nny = (j - 1) * (tail_1.ndy[*is - 1] + 1) + 1;
	    rat_1.weight[nnx + (nny + *is * 120) * 220 - 26621] = bweigh[i__ 
		    + j * 21 - 22];
/* L3003: */
	}
	s_wsfe(&io___572);
	i__2 = nxx;
	for (i__ = 1; i__ <= i__2; ++i__) {
	    do_fio(&c__1, (char *)&bweigh[i__ + j * 21 - 22], (ftnlen)sizeof(
		    real));
	}
	e_wsfe();
/* L3002: */
    }
    i__1 = nxx;
    for (i__ = 1; i__ <= i__1; ++i__) {
	i__2 = ntty;
	i__3 = nddy;
	for (j = 1; i__3 < 0 ? j >= i__2 : j <= i__2; j += i__3) {
	    j2 = 0;
L31:
	    ++j2;
	    j3 = j + j2;
	    j4 = j + tail_1.ndy[*is - 1] + 1;
	    if (j2 >= nddy) {
		goto L32;
	    }
	    nnx = (i__ - 1) * nddx + 1;
	    rat_1.weight[nnx + (j3 + *is * 120) * 220 - 26621] = (
		    rat_1.weight[nnx + (j + *is * 120) * 220 - 26621] * (
		    tail_1.ndy[*is - 1] + 1 - j2) + rat_1.weight[nnx + (j4 + *
		    is * 120) * 220 - 26621] * j2) / (tail_1.ndy[*is - 1] + 1)
		    ;
	    goto L31;
L32:
/* L30: */
	    ;
	}
/* L29: */
    }
/*  WILL NOW INTERPOLATE TO FIND WEIGHTS FOR INTERMEDIATE COLUMN. */
    i__1 = nty;
    for (j = 1; j <= i__1; ++j) {
	i__3 = nttx;
	i__2 = nddx;
	for (i__ = 1; i__2 < 0 ? i__ >= i__3 : i__ <= i__3; i__ += i__2) {
	    i2 = 0;
L37:
	    ++i2;
	    i3 = i__ + i2;
	    i4 = i__ + tail_1.ndx[*is - 1] + 1;
	    if (i2 == nddx) {
		goto L38;
	    }
	    rat_1.weight[i3 + (j + *is * 120) * 220 - 26621] = (rat_1.weight[
		    i__ + (j + *is * 120) * 220 - 26621] * (tail_1.ndx[*is - 
		    1] + 1 - i2) + rat_1.weight[i4 + (j + *is * 120) * 220 - 
		    26621] * i2) / (tail_1.ndx[*is - 1] + 1);
	    goto L37;
L38:
/* L36: */
	    ;
	}
/* L35: */
    }
    tail_1.dsx[*is - 1] = *xl / (ntx - 1);
    yl = (bd - tail_1.dtd[*is - 1]) / sin(*dip);
    tail_1.dsy[*is - 1] = yl / (nty - 1);
    tail_1.ih[*is - 1] = *lend / tail_1.dsx[*is - 1] + 1.5f;
    tail_1.jh[*is - 1] = (*hypd - tail_1.dtd[*is - 1]) / sin(*dip) / 
	    tail_1.dsy[*is - 1] + 1.5f;
    moment_(is, dip, jo);
    s_wsfe(&io___580);
    do_fio(&c__1, (char *)&(*is), (ftnlen)sizeof(integer));
    e_wsfe();
    s_wsfe(&io___581);
    do_fio(&c__1, (char *)&(*xl), (ftnlen)sizeof(real));
    e_wsfe();
    s_wsfe(&io___582);
    do_fio(&c__1, (char *)&tail_1.nx[*is - 1], (ftnlen)sizeof(integer));
    e_wsfe();
    s_wsfe(&io___583);
    do_fio(&c__1, (char *)&tail_1.ndx[*is - 1], (ftnlen)sizeof(integer));
    e_wsfe();
    s_wsfe(&io___584);
    do_fio(&c__1, (char *)&ntx, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&tail_1.dsx[*is - 1], (ftnlen)sizeof(real));
    e_wsfe();
    s_wsfe(&io___585);
    do_fio(&c__1, (char *)&tail_1.dtd[*is - 1], (ftnlen)sizeof(real));
    do_fio(&c__1, (char *)&bd, (ftnlen)sizeof(real));
    e_wsfe();
    s_wsfe(&io___586);
    do_fio(&c__1, (char *)&yl, (ftnlen)sizeof(real));
    e_wsfe();
    s_wsfe(&io___587);
    do_fio(&c__1, (char *)&tail_1.ny[*is - 1], (ftnlen)sizeof(integer));
    e_wsfe();
    s_wsfe(&io___588);
    do_fio(&c__1, (char *)&tail_1.ndy[*is - 1], (ftnlen)sizeof(integer));
    e_wsfe();
    s_wsfe(&io___589);
    do_fio(&c__1, (char *)&nty, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&tail_1.dsy[*is - 1], (ftnlen)sizeof(real));
    e_wsfe();
    s_wsfe(&io___590);
    do_fio(&c__1, (char *)&(*lend), (ftnlen)sizeof(real));
    do_fio(&c__1, (char *)&(*hypd), (ftnlen)sizeof(real));
    e_wsfe();
    s_wsfe(&io___591);
    do_fio(&c__1, (char *)&tail_1.ih[*is - 1], (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&tail_1.jh[*is - 1], (ftnlen)sizeof(integer));
    e_wsfe();
    s_wsfe(&io___592);
    do_fio(&c__1, (char *)&tail_1.rv[*is - 1], (ftnlen)sizeof(real));
    e_wsfe();
    jsub = subf_1.nsub[*is - 1];
    s_wsfe(&io___593);
    do_fio(&c__1, (char *)&jsub, (ftnlen)sizeof(integer));
    e_wsfe();
    i__1 = jsub;
    for (nsu = 1; nsu <= i__1; ++nsu) {
	s_wsfe(&io___594);
	do_fio(&c__1, (char *)&nsu, (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&subf_1.by1[nsu + *is * 300 - 301], (ftnlen)
		sizeof(real));
	do_fio(&c__1, (char *)&subf_1.ey1[nsu + *is * 300 - 301], (ftnlen)
		sizeof(real));
	do_fio(&c__1, (char *)&subf_1.ibx1[nsu + *is * 300 - 301], (ftnlen)
		sizeof(integer));
	do_fio(&c__1, (char *)&subf_1.iex1[nsu + *is * 300 - 301], (ftnlen)
		sizeof(integer));
	e_wsfe();
/* L1982: */
    }
    return 0;
} /* jill_ */

/* Subroutine */ int diane_(real *dt, real *strk, real *dip, real *az, real *
	p, integer *is, real *vp, real *vs, integer *nsu, integer *los, real *
	hypd)
{
    /* Format strings */
    static char fmt_241[] = "(\002 SUBFAULT HAS DIMENSIONS FROM\002,i3,"
	    "\002TO\002,i3,\002DOWN AND FROM\002,i3,\002TO\002,i3,\002ACROS"
	    "S\002)";
    static char fmt_1957[] = "(1x,\002SCALE=\002,e12.4,\002      DT=\002,e12"
	    ".4)";

    /* System generated locals */
    integer i__1, i__2;
    real r__1, r__2;

    /* Builtin functions */
    double cos(doublereal), sin(doublereal), sqrt(doublereal);
    integer s_wsfe(cilist *), do_fio(integer *, char *, ftnlen), e_wsfe(void);

    /* Local variables */
    static integer i__, j, k, l;
    static real y[4096], dd[3], cv, yt, ed1, ed2, ed3, es1, es2, es3, gar[4];
    static integer ihp, jhp;
    static real alt;
    static integer ibx, jby, itp, jtp, isx, jsy, ntx, nty, ntx1, nty1;
    static real edes, crap;
    static integer nddx, nddy;
    static real bull, rihp, rjhp, ritp, rjtp;
    static integer nttx, ntty;
    static real scale;

    /* Fortran I/O blocks */
    static cilist io___618 = { 0, 3, 0, fmt_241, 0 };
    static cilist io___632 = { 0, 6, 0, fmt_1957, 0 };


/*  DIANE COMPUTES THE TELESEISMIC TIME FUNTION FOR A FINITE FAULT OF THE */
/*  TYPE USED IN NORMA (HEATON).  THE FINITE FAULT (OR SUBFAULT) MUST LIE */
/*  WITHIN A HOMOGENOUS LAYER (LOS). */
/*  TF(J,I) IS THE TIME FUNCTION FOR THE RAYS P,pP,S,sS */
    for (i__ = 1; i__ <= 4; ++i__) {
	for (j = 1; j <= 4096; ++j) {
/* L1146: */
	    timefn_1.tf[j + (i__ << 12) - 4097] = 0.f;
	}
/* L1145: */
    }
/*     CALL FIRSTP */
    dd[0] = 0.f;
    dd[1] = 0.f;
    dd[2] = 0.f;
/*  NTX,NTY ARE TOTAL NUMBER OF GRID POINTS ON THE FINITE FAULT */
    ntx = (tail_1.ndx[*is - 1] + 1) * (tail_1.nx[*is - 1] - 1) + 1;
    nty = (tail_1.ndy[*is - 1] + 1) * (tail_1.ny[*is - 1] - 1) + 1;
    nddx = tail_1.ndx[*is - 1] + 1;
    nddy = tail_1.ndy[*is - 1] + 1;
    ntty = nty - 1;
    nttx = ntx - 1;
/*  IH,JH ARE THE HORIZONTAL AND VERTICAL FINE GRID POINTS FOR THE */
/*  HYPOCENTER */
/*  LOS IS THE LAYER WITH THE VIRTUAL SOURCE IN IT. */

/*     WRITE(6,3469) IH(IS),JH(IS) */
/* 3469 FORMAT(1X,'IH,JH',2I5) */

/*  WILL NOW COMPUTE THE ARRIVAL TIMES OF THE PHASES P,PP,S,SP. */
    for (l = 1; l <= 4; ++l) {
	rat_1.far__[(l * 120 + 1) * 220 - 26620] = 0.f;
	rat_1.far__[ntx + (l * 120 + 1) * 220 - 26621] = rat_1.far__[(l * 120 
		+ 1) * 220 - 26620] - *p * (ntx - 1) * tail_1.dsx[*is - 1] * 
		cos(*strk - *az);
/*  ED IS THE UNIT VECTOR IN THE DOWN-DIP DIRECTION */
	ed1 = -sin(*strk) * cos(*dip);
	ed2 = cos(*dip) * cos(*strk);
	ed3 = sin(*dip);
/*  CV IS THE INTRINSIC VELOCITY AT THE VIRTUAL SOURCE (NOT */
/*  NECESSARILY THE HYPOCENTER) OF THE RAY OF INTEREST */
/*  ALT IS POSITIVE FOR DOWN-GOING AND NEGATIVE FOR UPGOING */
	cv = *vp;
	if (l >= 3) {
	    cv = *vs;
	}
	alt = 1.f;
	if (l == 2) {
	    alt = -1.f;
	}
	if (l == 4) {
	    alt = -1.f;
	}
/*  ES IS THE UNIT VECTOR ALONG THE RAY PATH */
	es1 = cos(*az) * *p * cv;
	es2 = sin(*az) * *p * cv;
/* Computing 2nd power */
	r__1 = *p * cv;
	es3 = alt * sqrt(1 - r__1 * r__1);
/*     WRITE(6,87) ES3 */
/*     WRITE(3,88) ES1,ES2,ES3 */
/*  88 FORMAT (1X,'ES1,ES2,ES3',3F12.6) */
/*  87 FORMAT (F10.5) */

/*  EDES IS THE DOT PRODUCT OF ED AND ES */
	edes = ed1 * es1 + ed2 * es2 + ed3 * es3;
/*     WRITE(3,897)ED1,ED2,ED3,EDES */
/* 897 FORMAT (1X,'ED1,ED2,ED3,EDES',4F12.6) */
/*     WRITE(6,899) P,CV */
/* 899 FORMAT (1X,'P,C',2F12.6) */
	rat_1.far__[(nty + l * 120) * 220 - 26620] = rat_1.far__[(l * 120 + 1)
		 * 220 - 26620] - edes * (nty - 1) * tail_1.dsy[*is - 1] / cv;
	rat_1.far__[ntx + (nty + l * 120) * 220 - 26621] = rat_1.far__[(nty + 
		l * 120) * 220 - 26620] - *p * (ntx - 1) * tail_1.dsx[*is - 1]
		 * cos(*strk - *az);
/* L89: */
	ibx = subf_1.ib[*nsu + *is * 300 - 301];
	isx = subf_1.ie[*nsu + *is * 300 - 301];
	jby = subf_1.jby1[*nsu + ((*is << 1) + 1) * 300 - 901];
	jsy = subf_1.jey1[*nsu + ((*is << 1) + 1) * 300 - 901];
	if (l == 1) {
	    s_wsfe(&io___618);
	    do_fio(&c__1, (char *)&jby, (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&jsy, (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&ibx, (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&isx, (ftnlen)sizeof(integer));
	    e_wsfe();
	}
/*     WRITE(3,89) FAR(1,1,L),FAR(NTX,1,L),FAR(1,NTY,L),FAR(NTX,NTY,L) */
/*  COMPUTE THE ARRIVAL TIMES RELATIVE TO THE UPPER LEFT CORNER */
/*  IF THE FAULT SPANS VELOCITY LAYERS, THEN THE ARRIVAL TIMES FOR THESE */
/*  CORNERS MAY NOT BE THE ACTUAL VALUES.  THESE CORNERS ARE USED TO */
/*  INTERPOLATE TO THE ARRVIVAL TIMES OF ELEMENTS WITHIN THE SUBFAULT. */
	i__1 = jsy;
	for (j = jby; j <= i__1; ++j) {
	    rat_1.far__[(j + l * 120) * 220 - 26620] = rat_1.far__[(l * 120 + 
		    1) * 220 - 26620] + (rat_1.far__[(nty + l * 120) * 220 - 
		    26620] - rat_1.far__[(l * 120 + 1) * 220 - 26620]) * (j - 
		    1) / (nty - 1);
	    rat_1.far__[ntx + (j + l * 120) * 220 - 26621] = rat_1.far__[ntx 
		    + (l * 120 + 1) * 220 - 26621] + (rat_1.far__[ntx + (nty 
		    + l * 120) * 220 - 26621] - rat_1.far__[ntx + (l * 120 + 
		    1) * 220 - 26621]) * (j - 1) / (nty - 1);
	    i__2 = isx;
	    for (i__ = ibx; i__ <= i__2; ++i__) {
		rat_1.far__[i__ + (j + l * 120) * 220 - 26621] = rat_1.far__[(
			j + l * 120) * 220 - 26620] + (rat_1.far__[ntx + (j + 
			l * 120) * 220 - 26621] - rat_1.far__[(j + l * 120) * 
			220 - 26620]) * (i__ - 1) / (ntx - 1);
/*     IF (L.NE.1) GO TO 90 */
/*     WRITE(3,91) FAR(I,J,L) */
/*  91 FORMAT (1X,'FAR',F12.6) */
/* L90: */
/* L52: */
	    }
/* L51: */
	}
/* L50: */
    }
/*  WILL NOW COMPUTE THE LAG TIME DUE TO RUPTURE. */
/*  ITP AND JTP ARE THE LOCATIONS OF THE VIRTUAL POINT SOURCES WHICH */
/*  REPRESENT THE FINITE FAULT WITHIN A LAYER. */
    ihp = tail_1.ih[*is - 1];
    jhp = tail_1.jh[*is - 1];
    itp = ihp;
    jtp = jhp;
    if (ihp < 1) {
	itp = 1;
    }
    if (ihp > ntx) {
	itp = ntx;
    }
/*  DPTH(LOS) IS DEPTH OF LAYER WITH THE SOURCE (NOT NECESSARILY THE HYPOCENTER) */
/*  DTD IS THE DEPTH OF THE TOP OF THE FAULT */
    yt = (stuff_1.dpth[*los - 1] - tail_1.dtd[*is - 1]) / (tail_1.dsy[*is - 1]
	     * sin(*dip));
    if (*hypd > stuff_1.dpth[*los - 1]) {
	jtp = (integer) yt + 1;
    }
    yt = (stuff_1.dpth[*los - 2] - tail_1.dtd[*is - 1]) / (tail_1.dsy[*is - 1]
	     * sin(*dip));
    if (*hypd < stuff_1.dpth[*los - 2]) {
	jtp = (integer) yt + 1;
    }
    for (l = 1; l <= 4; ++l) {
	rat_1.far__[(jtp + l * 120) * 220 - 26620] = rat_1.far__[(l * 120 + 1)
		 * 220 - 26620] + (rat_1.far__[(nty + l * 120) * 220 - 26620] 
		- rat_1.far__[(l * 120 + 1) * 220 - 26620]) * (jtp - 1) / (
		nty - 1);
	rat_1.far__[ntx + (jtp + l * 120) * 220 - 26621] = rat_1.far__[ntx + (
		l * 120 + 1) * 220 - 26621] + (rat_1.far__[ntx + (nty + l * 
		120) * 220 - 26621] - rat_1.far__[ntx + (l * 120 + 1) * 220 - 
		26621]) * (jtp - 1) / (nty - 1);
	rat_1.far__[itp + (jtp + l * 120) * 220 - 26621] = rat_1.far__[(jtp + 
		l * 120) * 220 - 26620] + (rat_1.far__[ntx + (jtp + l * 120) *
		 220 - 26621] - rat_1.far__[(jtp + l * 120) * 220 - 26620]) * 
		(itp - 1) / (ntx - 1);
	gar[l - 1] = rat_1.far__[itp + (jtp + l * 120) * 220 - 26621];
	i__1 = isx;
	for (i__ = ibx; i__ <= i__1; ++i__) {
	    i__2 = jsy;
	    for (j = jby; j <= i__2; ++j) {
/* L163: */
		rat_1.far__[i__ + (j + l * 120) * 220 - 26621] -= gar[l - 1];
	    }
/* L162: */
	}
/* L164: */
    }
/*  IN THIS VERSION THE NEED FOR STTM HAS BEEN ELIMINATED BY THE USE */
/*  OF THE VARIABLE CRAP AND ALSO THE SUBROUTINES SLAVE AND TTLAG. */
/*     DO 60 L=1,4 */
/*  60 STTM(L) = FAR(ITP,JTP,L) */
    scale = 0.f;
/* BULL IS A RUPTURE TIME THAT IS SUBTRACTED OUT OF EVERYTHING TO REDUCE */
/* THE TIME OF THE LEADER.  BULL IS THE SAME FOR ALL SUBFAULTS */
    ritp = (real) itp;
    rjtp = (real) jtp;
    rihp = (real) ihp;
    rjhp = (real) jhp;
/*  THE FOLLOWING CODE LOOKS TO BE INCORRECT IF THE HYPOCENTER IS ABOVE */
/*  OR BELOW THE LIMITS OF THE FAULT AND HAS BEEN REPLACED OCTOBER 1988 */
/*      CRAP=((ITP-IHP)*DSX(IS))**2+((JTP-JHP)*DSY(IS))**2 */
/*      IF((JTP.GE.1).AND.(JTP.LE.NTX)) CRAP=((ITP-IHP)*DSX(IS))**2 */

/* Computing 2nd power */
    r__1 = (itp - ihp) * tail_1.dsx[*is - 1];
    crap = r__1 * r__1;
    if (jhp < 1) {
/* Computing 2nd power */
	r__1 = (itp - ihp) * tail_1.dsx[*is - 1];
/* Computing 2nd power */
	r__2 = jhp * tail_1.dsy[*is - 1];
	crap = r__1 * r__1 + r__2 * r__2;
    }
    if (jhp > nty) {
/* Computing 2nd power */
	r__1 = (itp - ihp) * tail_1.dsx[*is - 1];
/* Computing 2nd power */
	r__2 = (jhp - nty) * tail_1.dsy[*is - 1];
	crap = r__1 * r__1 + r__2 * r__2;
    }
    bull = sqrt(crap) / tail_1.rv[*is - 1];
/*     WRITE(6,5623) DS(IS),RV(IS) */
/* 5623 FORMAT(1X,'DS,RV',2F12.5) */
/*     WRITE(6,1387)IHP,JHP,ITP,JTP */
/* 1387 FORMAT (1X,'IHP,JHP,ITP,JTP',4I5) */
/*     WRITE(6,1206) BULL */
/* 1206 FORMAT(1X,'BULL=',F12.5) */
/*  WILL NOW COMPUTE THE TIME FOR THE RUPTURE TO MEET A GRID POINT */
    i__1 = isx;
    for (i__ = ibx; i__ <= i__1; ++i__) {
	i__2 = jsy;
	for (j = jby; j <= i__2; ++j) {
/* Computing 2nd power */
	    r__1 = (i__ - ihp) * tail_1.dsx[*is - 1];
/* Computing 2nd power */
	    r__2 = (j - jhp) * tail_1.dsy[*is - 1];
	    crap = r__1 * r__1 + r__2 * r__2;
	    rat_1.tmlag[i__ + j * 220 - 221] = sqrt(crap) / tail_1.rv[*is - 1]
		    ;
/*     WRITE(3,1958)WEIGHT(I,J,IS),SCALE */
/* 1958 FORMAT(1X,'WEIGHT,SCALE',2F12.6) */
	    for (l = 1; l <= 4; ++l) {
/* L56: */
		rat_1.far__[i__ + (j + l * 120) * 220 - 26621] = rat_1.far__[
			i__ + (j + l * 120) * 220 - 26621] + rat_1.tmlag[i__ 
			+ j * 220 - 221] - bull;
	    }
/* L55: */
	}
/* L54: */
    }
    i__1 = ntx;
    for (i__ = 1; i__ <= i__1; ++i__) {
	i__2 = nty;
	for (j = 1; j <= i__2; ++j) {
/* L755: */
	    scale += rat_1.weight[i__ + (j + *is * 120) * 220 - 26621];
	}
/* L754: */
    }
/*  WILL NOW COMPUTE THE TIME FUNCTION. */
    s_wsfe(&io___632);
    do_fio(&c__1, (char *)&scale, (ftnlen)sizeof(real));
    do_fio(&c__1, (char *)&(*dt), (ftnlen)sizeof(real));
    e_wsfe();

/*  NTY1 DELETES BOTTOM ROW OF SOURCES ON EACH FAULT SEGMENT SO */
/*  THAT FAULT SEGMENTS MATCH TOGETHER PROPERLY WITH NO OVERLAP. */

    nty1 = jsy - 1;
    ntx1 = isx - 1;
    if (isx == ntx) {
	ntx1 = ntx;
    }
    if (jsy == nty) {
	nty1 = nty;
    }
    for (l = 1; l <= 4; ++l) {
	i__1 = ntx1;
	for (i__ = ibx; i__ <= i__1; ++i__) {
	    i__2 = nty1;
	    for (j = jby; j <= i__2; ++j) {
		k = rat_1.far__[i__ + (j + l * 120) * 220 - 26621] / *dt + 20;
		timefn_1.tf[k + (l << 12) - 4097] += rat_1.weight[i__ + (j + *
			is * 120) * 220 - 26621] / (scale * *dt);
/*     IF (L.NE.1) GO TO 92 */
/*     WRITE(3,5789) I,J,L,K,FAR(I,J,L),TMLAG(I,J),TF(K,L) */
/*  92 CONTINUE */
/* 5789 FORMAT (1X,'I,J,L,K,FAR,TMLAG,TF',4I5,3F12.6) */
/* L63: */
	    }
/* L62: */
	}
/*     WRITE(3,243) (TF(K,L),K=1,501) */
/* L243: */
/* L61: */
    }
    for (l = 1; l <= 4; ++l) {
	for (k = 1; k <= 500; ++k) {
/* L71: */
	    y[k - 1] = timefn_1.tf[k + (l << 12) - 4097];
	}
/*     CALL CPLOT (Y,500,500,DD,1.,0.,1) */
/* L70: */
    }
/*     CALL LASTP */
    return 0;
} /* diane_ */

/* Subroutine */ int contor_(real *zgr, integer *ndx, integer *ndy, real *dx, 
	real *dy)
{
    /* Format strings */
    static char fmt_300[] = "(\002CNTR\002,2i1,\002.DAT\002)";
    static char fmt_200[] = "(\002 SUBROUTINE CONTOUR IS WRITING FILE TO "
	    "\002,a)";

    /* System generated locals */
    integer i__1, i__2;
    real r__1, r__2;
    olist o__1;
    cllist cl__1;

    /* Builtin functions */
    integer s_wsfi(icilist *), do_fio(integer *, char *, ftnlen), e_wsfi(void)
	    , f_open(olist *), s_wsfe(cilist *), e_wsfe(void), s_wsue(cilist *
	    ), do_uio(integer *, char *, ftnlen), e_wsue(void), f_clos(cllist 
	    *);

    /* Local variables */
    static integer i__, j, ii, ic1, ic2;
    static real xgr[220], ygr[120];
    static char name__[10];
    static integer lwrt, ngrdx, ngrdy;

    /* Fortran I/O blocks */
    static icilist io___640 = { 0, name__, 0, fmt_300, 10, 1 };
    static cilist io___641 = { 0, 3, 0, fmt_200, 0 };
    static cilist io___649 = { 0, 11, 0, 0, 0 };
    static cilist io___650 = { 0, 11, 0, 0, 0 };
    static cilist io___651 = { 0, 11, 0, 0, 0 };
    static cilist io___653 = { 0, 11, 0, 0, 0 };
    static cilist io___654 = { 0, 11, 0, 0, 0 };


/*  THIS SUBROUTINE CREATES FILES CONTOUR(ICON) WHICH ARE IN A FORMAT SUITABLE */
/*  FOR CONTOURING WITH BERNARD MINSTER'S CONTOUR PROGRAM.  THE PARAMETER ICON */
/*  STEPS EACH TIME THE PROGRAM IS CALLED.  THIS PROGRAM IS MODIFIED EXTENSIVE */
/*  LY FROM ONE WRITTEN BY MINSTER AND THUS HAS AN UNUSUAL STYLE. */
    /* Parameter adjustments */
    zgr -= 221;

    /* Function Body */
    junk_1.clat = 0.f;
    junk_1.clon = 0.f;
    ++point_1.icon;
    if (point_1.icon < 10) {
	ic1 = 0;
    }
    if (point_1.icon >= 10) {
	ic1 = 1;
    }
    if (point_1.icon >= 10) {
	ic2 = point_1.icon - 10;
    }
    if (point_1.icon < 10) {
	ic2 = point_1.icon;
    }
    if (point_1.icon >= 20) {
	ic1 = 2;
    }
    if (point_1.icon >= 20) {
	ic2 = point_1.icon - 20;
    }
    s_wsfi(&io___640);
    do_fio(&c__1, (char *)&ic1, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&ic2, (ftnlen)sizeof(integer));
    e_wsfi();
    o__1.oerr = 0;
    o__1.ounit = 11;
    o__1.ofnmlen = 10;
    o__1.ofnm = name__;
    o__1.orl = 0;
    o__1.osta = "NEW";
    o__1.oacc = "SEQUENTIAL";
    o__1.ofm = "UNFORMATTED";
    o__1.oblnk = 0;
    f_open(&o__1);
    s_wsfe(&io___641);
    do_fio(&c__1, name__, (ftnlen)10);
    e_wsfe();
    ngrdx = *ndx;
    ngrdy = *ndy;
    i__1 = *ndx;
    for (i__ = 1; i__ <= i__1; ++i__) {
/* L1: */
	xgr[i__ - 1] = (i__ - 1) * *dx;
    }
/*  FLIP Y AXIS UPSIDE DOWN SO DOWN DIP IS DOWN AND ALONG STRIKE IS RIGHT. */
    i__1 = *ndy;
    for (i__ = 1; i__ <= i__1; ++i__) {
/* L2: */
	ygr[i__ - 1] = -(*ndy - i__) * *dy;
    }
    junk_1.xmin = 0.f;
    junk_1.xmax = xgr[*ndx - 1];
    junk_1.ymin = ygr[0];
    junk_1.ymax = ygr[*ndy - 1];
    junk_1.zmax = -1e10f;
    junk_1.zmin = 1e10f;
    i__1 = *ndx;
    for (i__ = 1; i__ <= i__1; ++i__) {
	i__2 = *ndy;
	for (j = 1; j <= i__2; ++j) {
/* Computing MAX */
	    r__1 = junk_1.zmax, r__2 = zgr[i__ + j * 220];
	    junk_1.zmax = dmax(r__1,r__2);
/* Computing MIN */
	    r__1 = junk_1.zmin, r__2 = zgr[i__ + j * 220];
	    junk_1.zmin = dmin(r__1,r__2);
/* L5: */
	}
/* L4: */
    }
    lwrt = 0;
/*     CALL WRDSK(11,LWRT,NGRDX,4,ICODE) */
/*     IF (ICODE.NE.0) GO TO 2300 */
/*     LWRT = LWRT+4 */
    s_wsue(&io___649);
    do_uio(&c__1, (char *)&ngrdx, (ftnlen)sizeof(integer));
    do_uio(&c__1, (char *)&ngrdy, (ftnlen)sizeof(integer));
    e_wsue();
/*     NWD = NGRDX+NGRDX */
/*     CALL WRDSK(11,LWRT,XGR(1),NWD,ICODE) */
    s_wsue(&io___650);
    i__1 = ngrdx;
    for (i__ = 1; i__ <= i__1; ++i__) {
	do_uio(&c__1, (char *)&xgr[i__ - 1], (ftnlen)sizeof(real));
    }
    e_wsue();
/*     IF (ICODE.NE.0) GO TO 2300 */
/*     LWRT = LWRT+NWD */
/*     NWD = NGRDY + NGRDY */
/*     CALL WRDSK(11,LWRT,YGR(1),NWD,ICODE) */
    s_wsue(&io___651);
    i__1 = ngrdy;
    for (i__ = 1; i__ <= i__1; ++i__) {
	do_uio(&c__1, (char *)&ygr[i__ - 1], (ftnlen)sizeof(real));
    }
    e_wsue();
/*     IF (ICODE.NE.0) GO TO 2300 */
/*     LWRT = LWRT+NWD */
/*     NWD = NGRDX+NGRDX */
    i__1 = ngrdy;
    for (i__ = 1; i__ <= i__1; ++i__) {
	ii = ngrdy - i__ + 1;
/*     CALL WRDSK(11,LWRT,ZGR(1,II),NWD,ICODE) */
/* L2100: */
	s_wsue(&io___653);
	i__2 = ngrdx;
	for (j = 1; j <= i__2; ++j) {
	    do_uio(&c__1, (char *)&zgr[j + ii * 220], (ftnlen)sizeof(real));
	}
	e_wsue();
    }
/*     IF (ICODE.NE.0) GO TO 2300 */
/* 2100 LWRT = LWRT + NWD */
/*     CALL WRDSK(11,LWRT,XMIN,16,ICODE) */
    s_wsue(&io___654);
    do_uio(&c__1, (char *)&junk_1.xmin, (ftnlen)sizeof(real));
    do_uio(&c__1, (char *)&junk_1.xmax, (ftnlen)sizeof(real));
    do_uio(&c__1, (char *)&junk_1.ymin, (ftnlen)sizeof(real));
    do_uio(&c__1, (char *)&junk_1.ymax, (ftnlen)sizeof(real));
    do_uio(&c__1, (char *)&junk_1.zmin, (ftnlen)sizeof(real));
    do_uio(&c__1, (char *)&junk_1.zmax, (ftnlen)sizeof(real));
    do_uio(&c__1, (char *)&junk_1.clat, (ftnlen)sizeof(real));
    do_uio(&c__1, (char *)&junk_1.clon, (ftnlen)sizeof(real));
    e_wsue();
/*     IF (ICODE.NE.0) GO TO 2300 */
    cl__1.cerr = 0;
    cl__1.cunit = 11;
    cl__1.csta = 0;
    f_clos(&cl__1);
    return 0;
/* 2300 WRITE(6,2350) ICODE */
/*     WRITE(3,2350) ICODE */
/* 2350 FORMAT(' ERROR IN WRDSK, ICODE=',I4) */
/*     CLOSE (11) */
/*     RETURN */
} /* contor_ */

/* Subroutine */ int moment_(integer *is, real *dipp, integer *jo)
{
    /* Format strings */
    static char fmt_101[] = "(1x,\002WGHT(I,J)= \002,e12.4)";

    /* System generated locals */
    integer i__1, i__2;

    /* Builtin functions */
    double sin(doublereal);
    integer s_wsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_wsle(void), s_wsfe(cilist *), do_fio(integer *, char *, ftnlen),
	     e_wsfe(void);

    /* Local variables */
    static real h__;
    static integer i__, j, l, ntx, nty;
    static real area, slip, wght[26400]	/* was [220][120] */, scale, factor[
	    120];

    /* Fortran I/O blocks */
    static cilist io___664 = { 0, 3, 0, 0, 0 };
    static cilist io___667 = { 0, 3, 0, 0, 0 };
    static cilist io___668 = { 0, 3, 0, fmt_101, 0 };


/*  SUBROUTINE MOMENT CHANGES THE WEIGHTS WHICH ARE GIVEN IN TERMS */
/*  OF RELATIVE DISLOCATION TO ABSOLUTE DISLOCATION AND THEN HAS THESE */
/*  WEIGHTS CONTOURED.  IT THEN CONVERTS ALL MOMENTS OVER TO RELATIVE */
/*  MOMENTS FOR USE IN THE REST OF THE PROGRAM. */
    stuff_1.dpth[0] = 0.f;
    ntx = (tail_1.nx[*is - 1] - 1) * (tail_1.ndx[*is - 1] + 1) + 1;
    nty = (tail_1.ny[*is - 1] - 1) * (tail_1.ndy[*is - 1] + 1) + 1;
    i__1 = *jo;
    for (j = 2; j <= i__1; ++j) {
/* L1: */
	stuff_1.dpth[j - 1] = stuff_1.dpth[j - 2] + stuff_1.th[j - 1];
    }
    scale = 0.f;
    i__1 = nty;
    for (j = 1; j <= i__1; ++j) {
	h__ = tail_1.dtd[*is - 1] + (j - 1) * tail_1.dsy[*is - 1] * sin(*dipp)
		;
	l = 0;
L3:
	++l;
	if (h__ > stuff_1.dpth[l - 1]) {
	    goto L3;
	}
	factor[j - 1] = stuff_1.d__[l - 1] * stuff_1.s[l - 1] * stuff_1.s[l - 
		1];
/*  TURN WEIGHTS FROM RELATIVE SLIP TO RELATIVE MOMENT */
	i__2 = ntx;
	for (i__ = 1; i__ <= i__2; ++i__) {
	    rat_1.weight[i__ + (j + *is * 120) * 220 - 26621] *= factor[j - 1]
		    ;
/* L4: */
	    scale += rat_1.weight[i__ + (j + *is * 120) * 220 - 26621];
	}
/* L2: */
    }
    area = tail_1.dsx[*is - 1] * tail_1.dsy[*is - 1] * 1e10f;
    s_wsle(&io___664);
    do_lio(&c__9, &c__1, " AREA AND SCALE:", (ftnlen)16);
    do_lio(&c__4, &c__1, (char *)&area, (ftnlen)sizeof(real));
    do_lio(&c__4, &c__1, (char *)&scale, (ftnlen)sizeof(real));
    e_wsle();
    i__1 = nty;
    for (j = 1; j <= i__1; ++j) {
	slip = faul1_1.fmnt[*is - 1] / (area * scale * factor[j - 1] * 1e10f);
	i__2 = ntx;
	for (i__ = 1; i__ <= i__2; ++i__) {
/*  TURN WEIGHTS INTO ACTUAL SLIPS IN CM. */
	    rat_1.weight[i__ + (j + *is * 120) * 220 - 26621] *= slip;
/* L6: */
	    wght[i__ + j * 220 - 221] = rat_1.weight[i__ + (j + *is * 120) * 
		    220 - 26621];
	}
/*     WRITE(3,100) (WGHT(I,J),I=1,NTX) */
/* 100 FORMAT(20(F4.0,1X)) */
/* L5: */
    }
    s_wsle(&io___667);
    do_lio(&c__9, &c__1, " DISLOCATION SCALING FACTOR FOR INPUT MOMENT", (
	    ftnlen)44);
    e_wsle();
    for (j = 1; j <= 2; ++j) {
/* L103: */
	s_wsfe(&io___668);
	for (i__ = 1; i__ <= 2; ++i__) {
	    do_fio(&c__1, (char *)&wght[i__ + j * 220 - 221], (ftnlen)sizeof(
		    real));
	}
	e_wsfe();
    }
/*     CALL CONTOR(WGHT,NTX,NTY,DSX(IS),DSY(IS)) */
    i__1 = nty;
    for (j = 1; j <= i__1; ++j) {
	i__2 = ntx;
	for (i__ = 1; i__ <= i__2; ++i__) {
/*  TURN WEIGHTS BACK INTO RELATIVE MOMENTS */
/* L8: */
	    rat_1.weight[i__ + (j + *is * 120) * 220 - 26621] = rat_1.weight[
		    i__ + (j + *is * 120) * 220 - 26621] * factor[j - 1] / 
		    factor[nty - 1];
	}
/* L7: */
    }
    return 0;
} /* moment_ */

/* Subroutine */ int slave_(integer *is, real *hypd, real *sdp, integer *los, 
	real *strk, real *dip, real *sn, real *se, real *fl, real *xhyp)
{
    /* Builtin functions */
    double sin(doublereal), sqrt(doublereal), atan2(doublereal, doublereal), 
	    cos(doublereal);

    /* Local variables */
    static real h__, d1, s1, xh, yh, gama, beta;
    static integer lsor;

/*  SLAVE SETS UP PROPER GEOMETRY FOR EACH SUBFAULT.  ALL DISTANCES ARE */
/*  MEASURED FROM THE TOP CENTER OF EACH FINITE FAULT. */
/* FIND LAYER WITH THE SOURCE */
    lsor = 0;
L1:
    ++lsor;
    if (stuff_1.dpth[lsor - 1] < *hypd) {
	goto L1;
    }
    if (*los == lsor) {
	*sdp = *hypd;
    }
    if (*los < lsor) {
	*sdp = stuff_1.dpth[*los - 1];
    }
    if (*los > lsor) {
	*sdp = stuff_1.dpth[*los - 2];
    }
    h__ = *sdp - tail_1.dtd[*is - 1];
    xh = *xhyp - *fl / 2.f;
    yh = h__ / sin(*dip);
    d1 = sqrt(xh * xh + yh * yh);
    s1 = sqrt(d1 * d1 - h__ * h__);
    beta = atan2(xh, yh);
    gama = *strk + 1.570796f - beta;
    *sn = s1 * cos(gama);
    *se = s1 * sin(gama);
    return 0;
} /* slave_ */

/* Subroutine */ int subflt_(integer *is, real *dip)
{
    /* System generated locals */
    integer i__1, i__2;

    /* Builtin functions */
    double sin(doublereal);

    /* Local variables */
    static integer j, l, n;
    static real y, bd, dj, td;
    static integer nl, nsu, nty, limn;

/*  SUBFAULT SETS UP THE DIMENSIONS OF SUBFAULTS, ASSUMING THAT VELOCITY */
/*  CONTRASTS ALSO PRODUCE SUBFAULT BOUNDARIES. */
/*  NL IS THE NEW SUBFAULT INDEX.  L IS THE LAYERING INDEX. */
/*  LIMN IS A FLAG TO DECIDE WHETHER OR NOT A SUBFAULT CONTAINS AN */
/*  ACTUAL ROW OF SOURCES. */
    limn = 0;
    nty = (tail_1.nx[*is - 1] - 1) * (tail_1.ndx[*is - 1] + 1) + 1;
    nl = 0;
    nsu = subf_1.nsub[*is - 1];
    i__1 = nsu;
    for (n = 1; n <= i__1; ++n) {
/*  FIND THE LAYER WITH THE TOP OF THE SUBFAULT. */
	l = 0;
L3:
	++l;
	if (subf_1.by1[n + *is * 300 - 301] < stuff_1.dpth[l] && subf_1.by1[n 
		+ *is * 300 - 301] >= stuff_1.dpth[l - 1]) {
	    goto L7;
	}
	goto L3;
L7:
	++l;
/*  IF LIMN=-1, THEN ELIMINATE THE LAST SUBFAULT SINCE IT CONTAINED NO SOURCES. */
	nl = nl + 1 + limn;
	y = (subf_1.by1[n + *is * 300 - 301] - tail_1.dtd[*is - 1]) / (sin(*
		dip) * tail_1.dsy[*is - 1]);
	subf_1.jby1[nl + ((*is << 1) + 1) * 300 - 901] = (integer) y + 1;
	subf_1.jby1[nl + ((*is << 1) + 2) * 300 - 901] = l;
	td = subf_1.by1[n + *is * 300 - 301];
	subf_1.ib[nl + *is * 300 - 301] = subf_1.ibx1[n + *is * 300 - 301];
	subf_1.ie[nl + *is * 300 - 301] = subf_1.iex1[n + *is * 300 - 301];
L5:
	if (subf_1.ey1[n + *is * 300 - 301] <= stuff_1.dpth[l - 1]) {
	    goto L4;
	}
/*  IF A LAYER BOUNDARY OCCURS BEFORE BOTTOMOF SUBFAULT, THEN CREATE TWO */
/*  SUBFAULTS WHICH WILL LATER BE SUMMED IF JEY1(NL,2,IS) IS NEGATIVE. */
	y = (stuff_1.dpth[l - 1] - tail_1.dtd[*is - 1]) / (sin(*dip) * 
		tail_1.dsy[*is - 1]);
	subf_1.jey1[nl + ((*is << 1) + 1) * 300 - 901] = (integer) y + 1;
	subf_1.jey1[nl + ((*is << 1) + 2) * 300 - 901] = -l;
/*  ELIMINATE THIS SUBFAULT IF THERE ARE NO SOURCES WITHIN. */
	limn = -1;
	bd = stuff_1.dpth[l - 1];
	i__2 = nty;
	for (j = 1; j <= i__2; ++j) {
	    dj = tail_1.dtd[*is - 1] + (j - 1) * tail_1.dsy[*is - 1] * sin(*
		    dip);
/* L9: */
	    if (dj >= td && dj <= bd) {
		limn = 0;
	    }
	}
	nl = nl + 1 + limn;
/*  CREATE TOP TO NEW SUBFAULT. */
	++l;
	y = (stuff_1.dpth[l - 2] - tail_1.dtd[*is - 1]) / (sin(*dip) * 
		tail_1.dsy[*is - 1]);
	subf_1.jby1[nl + ((*is << 1) + 1) * 300 - 901] = (integer) y + 1;
	subf_1.jby1[nl + ((*is << 1) + 2) * 300 - 901] = -l;
/*  IF THE LAST SUBFAULT WAS ELIMINATED, THEN THIS SUBFAULT BOUNDARY IS */
/*  NO LONGER VIRTUAL. */
	if (limn == -1) {
	    subf_1.jby1[nl + ((*is << 1) + 2) * 300 - 901] = l;
	}
	td = stuff_1.dpth[l - 2];
	subf_1.ib[nl + *is * 300 - 301] = subf_1.ibx1[n + *is * 300 - 301];
	subf_1.ie[nl + *is * 300 - 301] = subf_1.iex1[n + *is * 300 - 301];
	goto L5;
L4:
/*  PUT BOTTOM ON SUBFAULT AND CHECK TO SEE IF ANY SOURCES ARE LOCATED */
/*  WITHIN THE SUBFAULT.  IF NOT, THEN ELIMINATE THE SUBFAULT. */
	limn = -1;
	bd = subf_1.ey1[n + *is * 300 - 301];
	i__2 = nty;
	for (j = 1; j <= i__2; ++j) {
	    dj = tail_1.dtd[*is - 1] + (j - 1) * tail_1.dsy[*is - 1] * sin(*
		    dip);
/* L8: */
	    if (dj >= td && dj <= bd) {
		limn = 0;
	    }
	}
/*  IF LAST SUBFAULT WAS ELIMINATED, THEN THE BOUDARY IS NO LONGER VIRTUAL. */
	if (limn == -1) {
	    subf_1.jey1[nl - 1 + ((*is << 1) + 2) * 300 - 901] = (i__2 = 
		    subf_1.jey1[nl - 1 + ((*is << 1) + 2) * 300 - 901], abs(
		    i__2));
	}
	y = (subf_1.ey1[n + *is * 300 - 301] - tail_1.dtd[*is - 1]) / (sin(*
		dip) * tail_1.dsy[*is - 1]);
	subf_1.jey1[nl + ((*is << 1) + 1) * 300 - 901] = (integer) y + 1;
	subf_1.jey1[nl + ((*is << 1) + 2) * 300 - 901] = l;
	if (subf_1.jby1[nl + ((*is << 1) + 1) * 300 - 901] <= 0) {
	    subf_1.jby1[nl + ((*is << 1) + 1) * 300 - 901] = 1;
	}
	nty = (tail_1.ny[*is - 1] - 1) * (tail_1.ndy[*is - 1] + 1) + 1;
/* L2: */
	if (subf_1.jey1[nl + ((*is << 1) + 1) * 300 - 901] > nty) {
	    subf_1.jey1[nl + ((*is << 1) + 1) * 300 - 901] = nty;
	}
    }
    subf_1.msub1[*is - 1] = nl + limn;
    return 0;
} /* subflt_ */

/* Subroutine */ int raygun_(integer *los, integer *nlay, integer *mode, 
	integer *jm)
{
    /* Format strings */
    static char fmt_1000[] = "(\002/users/cmendoza/pgms/ff/rays/rx\002,i1"
	    ",\002x\002,i1,\002x\002,i1,\002.dat\002)";
    static char fmt_1001[] = "(\002/users/cmendoza/pgms/ff/rays/rx\002,i1"
	    ",\002x\002,i2,\002x\002,i1,\002.dat\002)";
    static char fmt_1002[] = "(\002/users/cmendoza/pgms/ff/rays/rx\002,i1"
	    ",\002x\002,i2,\002x\002,i2,\002.dat\002)";
    static char fmt_255[] = "(i10)";
    static char fmt_400[] = "(40i2)";
    static char fmt_401[] = "(1x,40i2)";

    /* System generated locals */
    integer i__1, i__2;
    olist o__1;
    cllist cl__1;

    /* Builtin functions */
    integer s_wsfi(icilist *), do_fio(integer *, char *, ftnlen), e_wsfi(void)
	    , f_open(olist *), s_rsfe(cilist *), e_rsfe(void), s_wsfe(cilist *
	    ), e_wsfe(void), f_clos(cllist *);

    /* Local variables */
    static integer i__, j, nd;
    static char name__[40];

    /* Fortran I/O blocks */
    static icilist io___689 = { 0, name__, 0, fmt_1000, 40, 1 };
    static icilist io___690 = { 0, name__, 0, fmt_1001, 40, 1 };
    static icilist io___691 = { 0, name__, 0, fmt_1002, 40, 1 };
    static cilist io___692 = { 0, 4, 0, fmt_255, 0 };
    static cilist io___694 = { 0, 4, 0, fmt_400, 0 };
    static cilist io___697 = { 0, 3, 0, fmt_401, 0 };
    static cilist io___698 = { 0, 4, 0, fmt_400, 0 };
    static cilist io___699 = { 0, 3, 0, fmt_401, 0 };


/*  RAYGUN DECIDES WHICH RAYFILE SHOULD BE READ.  THE FIRST RAY IS NOT */
/*  IGNORED.  THIS IS DIFFERENT FROM THE RAYGUN IN THREAD.  ALL OF THE */
/*  RAYFILES SHOULD BE IN A SUBUFD TO THE RUNNING UFD.  THE NAME OF THIS */
/*  UFD SHOULD BE RAYUFD.  INDIVIDUAL RAY SETS ARE IN FILES NAMED */
/*  RAY.I.J.K     WHERE  I=1,2,3 FOR P,SV,SH WAVES */
/*    J=NUMBER OF LAYERS */
/*    K=LAYER WITH THE SOURCE */
    if (*nlay >= 10) {
	goto L1;
    }
    s_wsfi(&io___689);
    do_fio(&c__1, (char *)&(*mode), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&(*nlay), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&(*los), (ftnlen)sizeof(integer));
    e_wsfi();
    goto L2;
L1:
    if (*los >= 10) {
	goto L3;
    }
    s_wsfi(&io___690);
    do_fio(&c__1, (char *)&(*mode), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&(*nlay), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&(*los), (ftnlen)sizeof(integer));
    e_wsfi();
    goto L2;
L3:
    s_wsfi(&io___691);
    do_fio(&c__1, (char *)&(*mode), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&(*nlay), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&(*los), (ftnlen)sizeof(integer));
    e_wsfi();
L2:
    o__1.oerr = 0;
    o__1.ounit = 4;
    o__1.ofnmlen = 40;
    o__1.ofnm = name__;
    o__1.orl = 0;
    o__1.osta = "OLD";
    o__1.oacc = 0;
    o__1.ofm = 0;
    o__1.oblnk = 0;
    f_open(&o__1);
    s_rsfe(&io___692);
    do_fio(&c__1, (char *)&(*jm), (ftnlen)sizeof(integer));
    e_rsfe();
    i__1 = *jm;
    for (i__ = 1; i__ <= i__1; ++i__) {
	s_rsfe(&io___694);
	do_fio(&c__1, (char *)&nd, (ftnlen)sizeof(integer));
	i__2 = nd;
	for (j = 1; j <= i__2; ++j) {
	    do_fio(&c__1, (char *)&rays_1.na[i__ + j * 250 - 251], (ftnlen)
		    sizeof(integer));
	}
	e_rsfe();
	if (ipr_1.iprnt == 1) {
	    s_wsfe(&io___697);
	    do_fio(&c__1, (char *)&nd, (ftnlen)sizeof(integer));
	    i__2 = nd;
	    for (j = 1; j <= i__2; ++j) {
		do_fio(&c__1, (char *)&rays_1.na[i__ + j * 250 - 251], (
			ftnlen)sizeof(integer));
	    }
	    e_wsfe();
	}
	s_rsfe(&io___698);
	do_fio(&c__1, (char *)&rays_1.ncount[i__ - 1], (ftnlen)sizeof(integer)
		);
	i__2 = nd;
	for (j = 1; j <= i__2; ++j) {
	    do_fio(&c__1, (char *)&rays_1.nray[i__ + j * 250 - 251], (ftnlen)
		    sizeof(integer));
	}
	e_rsfe();
	if (ipr_1.iprnt == 1) {
	    s_wsfe(&io___699);
	    do_fio(&c__1, (char *)&rays_1.ncount[i__ - 1], (ftnlen)sizeof(
		    integer));
	    i__2 = nd;
	    for (j = 1; j <= i__2; ++j) {
		do_fio(&c__1, (char *)&rays_1.nray[i__ + j * 250 - 251], (
			ftnlen)sizeof(integer));
	    }
	    e_wsfe();
	}
	rays_1.ndr[i__ - 1] = nd;
/* L42: */
    }
/* 402 FORMAT(' RAYFILE IS ',20A2) */
    cl__1.cerr = 0;
    cl__1.cunit = 4;
    cl__1.csta = 0;
    f_clos(&cl__1);
    return 0;
} /* raygun_ */

/* Subroutine */ int contf_(real *xss, real *xs4, real *xs3, real *x, real *
	fqw, real *x1, real *xs1, integer *np, integer *np2, integer *npl, 
	real *dt, real *area, integer *nsorce, integer *ibug, real *scale)
{
    /* Format strings */
    static char fmt_703[] = "(1x,\002ENTER NAME OF FILE WITH DIGITIZED TIME "
	    "FUNCTION\002)";
    static char fmt_704[] = "(a)";
    static char fmt_705[] = "(i10,f10.5)";
    static char fmt_706[] = "(1x,9e12.4)";
    static char fmt_717[] = "(1x,\002AREA UNDER TIME FUNCTION= \002,f12.4)";

    /* System generated locals */
    integer i__1, i__2;
    real r__1;
    olist o__1;
    cllist cl__1;

    /* Builtin functions */
    integer s_wsfe(cilist *), e_wsfe(void), s_rsfe(cilist *), do_fio(integer *
	    , char *, ftnlen), e_rsfe(void), f_open(olist *), f_clos(cllist *)
	    ;

    /* Local variables */
    static integer i__, j;
    static real xi, yi;
    static integer kz;
    static real xr, yr, coni, conr;
    extern /* Subroutine */ int trap_(real *, real *, integer *, integer *, 
	    real *, integer *);
    static integer itot;
    static real difdt;
    static char digtf[80];
    extern /* Subroutine */ int coolb_(integer *, real *, real *);
    static real dtkos;
    static integer npnew, npnew1;
    extern /* Subroutine */ int interp_(integer *, real *, real *, integer *, 
	    real *, real *, integer *);

    /* Fortran I/O blocks */
    static cilist io___700 = { 0, 6, 0, fmt_703, 0 };
    static cilist io___701 = { 0, 5, 0, fmt_704, 0 };
    static cilist io___703 = { 0, 14, 0, fmt_705, 0 };
    static cilist io___706 = { 0, 14, 0, fmt_706, 0 };
    static cilist io___709 = { 0, 6, 0, fmt_717, 0 };



/*     THIS ROUTINE READS IN AN EXTERNALLY GENERATED TIME FUNCTION */
/*     INTO CADILLAC. THE FORMAT OF THE TIME FUNCTION FILE MUST BE */
/*     THE SAME AS THAT GENERATED BY THE PROGRAM KOSTROV. LINEAR */
/*     INTERPOLATION IS DONE TO PRODUCE A COMMON TIME STEP FOR BOTH */
/*     THE TIME FUNCTION AND THE PREVIOUSLY CONVOLVED INSTRUMENT */
/*     RESPONSE AND Q OPERATOR. THE RESAMPLING TIME STEP IS CHOSEN */
/*     TO BE THE FINER OF THE TWO TIME STEPS. THE CONVOLUTION IS DONE */
/*     AND THE RESULT IS RESAMPLED, IF NECESSARY AT THE ORIGINAL DT. */

/* 	call opnplt(2,8.,0) */
/* 	call plot(2.,6.5,-3) */
    /* Parameter adjustments */
    --xs1;
    --x1;
    --fqw;
    --x;
    --xs3;
    --xs4;
    xss -= 2;

    /* Function Body */
    s_wsfe(&io___700);
    e_wsfe();
    s_rsfe(&io___701);
    do_fio(&c__1, digtf, (ftnlen)80);
    e_rsfe();
    o__1.oerr = 0;
    o__1.ounit = 14;
    o__1.ofnmlen = 80;
    o__1.ofnm = digtf;
    o__1.orl = 0;
    o__1.osta = "OLD";
    o__1.oacc = 0;
    o__1.ofm = 0;
    o__1.oblnk = 0;
    f_open(&o__1);
    s_rsfe(&io___703);
    do_fio(&c__1, (char *)&itot, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&dtkos, (ftnlen)sizeof(real));
    e_rsfe();
    s_rsfe(&io___706);
    i__1 = itot;
    for (i__ = 1; i__ <= i__1; ++i__) {
	do_fio(&c__1, (char *)&xs4[i__], (ftnlen)sizeof(real));
    }
    e_rsfe();
    cl__1.cerr = 0;
    cl__1.cunit = 14;
    cl__1.csta = 0;
    f_clos(&cl__1);
    if (itot < *np) {
	i__1 = *np;
	for (i__ = itot + 1; i__ <= i__1; ++i__) {
/* L714: */
	    xs4[i__] = 0.f;
	}
    }
    i__1 = *np;
    for (i__ = 1; i__ <= i__1; ++i__) {
	x[i__] = *dt * (i__ - 1);
/* L708: */
	xs3[i__] = dtkos * (i__ - 1);
    }
/* 	if (ibug .eq. 1) call draw(xs4,np,dtkos,scale) */
    trap_(&xs4[1], &xs3[1], &c__1, &itot, &x1[1], &kz);
    *area = x1[kz];
    s_wsfe(&io___709);
    do_fio(&c__1, (char *)&(*area), (ftnlen)sizeof(real));
    e_wsfe();
    difdt = (r__1 = dtkos - *dt, dabs(r__1));
    if (difdt < 1e-4f) {
	goto L730;
    }
    if (dtkos < *dt) {
	coolb_(npl, &fqw[1], &c_b259);
	i__1 = *np;
	for (i__ = 1; i__ <= i__1; ++i__) {
/* L713: */
	    fqw[i__] = fqw[(i__ << 1) - 1] / (*dt * *np);
	}
	interp_(np, &x[1], &fqw[1], np, &xs3[1], &x1[1], &npnew);
	if (npnew >= *np) {
	    goto L718;
	}
	npnew1 = npnew + 1;
	i__1 = *np;
	for (i__ = npnew1; i__ <= i__1; ++i__) {
/* L719: */
	    x1[i__] = 0.f;
	}
L718:
/* 718 IF(IBUG .EQ. 1) CALL DRAW(X1,NP,DTKOS,SCALE) */
	i__1 = *np;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    fqw[i__ * 2] = 0.f;
	    fqw[(i__ << 1) - 1] = x1[i__];
	    xs1[i__ * 2] = 0.f;
/* L715: */
	    xs1[(i__ << 1) - 1] = xs4[i__];
	}
	coolb_(npl, &fqw[1], &c_b115);
	coolb_(npl, &xs1[1], &c_b115);
	i__1 = *np2;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    fqw[i__] *= dtkos;
/* L716: */
	    xs1[i__] *= dtkos;
	}
	goto L720;
    }
    if (*dt < dtkos) {
	interp_(np, &xs3[1], &xs4[1], np, &x[1], &x1[1], &npnew);
	if (npnew >= *np) {
	    goto L709;
	}
	npnew1 = npnew + 1;
	i__1 = *np;
	for (i__ = npnew1; i__ <= i__1; ++i__) {
/* L710: */
	    x1[i__] = 0.f;
	}
L709:
/* 709 IF(IBUG .EQ. 1) CALL DRAW(X1,NP,DT,SCALE) */
	i__1 = *np;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    xs1[i__ * 2] = 0.f;
/* L711: */
	    xs1[(i__ << 1) - 1] = x1[i__];
	}
	coolb_(npl, &xs1[1], &c_b115);
	i__1 = *np2;
	for (i__ = 1; i__ <= i__1; ++i__) {
/* L712: */
	    xs1[i__] *= *dt;
	}
    }
    goto L720;
L730:
    i__1 = *np;
    for (i__ = 1; i__ <= i__1; ++i__) {
	xs1[i__ * 2] = 0.f;
/* L721: */
	xs1[(i__ << 1) - 1] = xs4[i__];
    }
    coolb_(npl, &xs1[1], &c_b115);
    i__1 = *np2;
    for (i__ = 1; i__ <= i__1; ++i__) {
/* L722: */
	xs1[i__] *= *dt;
    }
L720:
    i__1 = *np;
    for (j = 1; j <= i__1; ++j) {
	xr = xs1[(j << 1) - 1];
	xi = xs1[j * 2];
	yr = fqw[(j << 1) - 1];
	yi = fqw[j * 2];
	conr = (xr * yr - xi * yi) / *area;
	coni = (xi * yr + xr * yi) / *area;
	xs1[(j << 1) - 1] = conr;
	xs1[j * 2] = coni;
/* L723: */
    }
    if (dtkos < *dt) {
	coolb_(npl, &xs1[1], &c_b259);
	i__1 = *np;
	for (i__ = 1; i__ <= i__1; ++i__) {
/* L724: */
	    xs1[i__] = xs1[(i__ << 1) - 1] / (dtkos * *np);
	}
	interp_(np, &xs3[1], &xs1[1], np, &x[1], &x1[1], &npnew);
	if (npnew >= *np) {
	    goto L725;
	}
	npnew1 = npnew + 1;
	i__1 = *np;
	for (i__ = npnew1; i__ <= i__1; ++i__) {
/* L726: */
	    x1[i__] = 0.f;
	}
L725:
/* 725 IF(IBUG .EQ. 1) CALL DRAW(X1,NP,DT,SCALE) */
	i__1 = *np;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    xs1[i__ * 2] = 0.f;
/* L727: */
	    xs1[(i__ << 1) - 1] = x1[i__];
	}
	coolb_(npl, &xs1[1], &c_b115);
	i__1 = *np2;
	for (i__ = 1; i__ <= i__1; ++i__) {
/* L728: */
	    xs1[i__] *= *dt;
	}
    }
    i__1 = *nsorce;
    for (i__ = 1; i__ <= i__1; ++i__) {
	i__2 = *np;
	for (j = 1; j <= i__2; ++j) {
/* L729: */
	    xss[i__ + j] = xs1[j];
	}
    }
/* 	call endplt */
    return 0;
} /* contf_ */

/* Subroutine */ int trap_(real *y, real *t, integer *n1, integer *n2, real *
	z__, integer *np)
{
    /* System generated locals */
    integer i__1;
    real r__1;

    /* Local variables */
    static real a, h__;
    static integer i__, j, k, m;
    static real h1, h2, q1, q2, tm;
    static integer iy, iy1;
    static real area;

/*     INTEGRATES THE CURVE Y(I) SAMPLED AT TIME POINTS T(I) BETWEEN */
/*     THE POINTS N1 AND N2.  OUTPUT IS IN ARRAY Z(I) SAMPLED AT THE */
/*     NP TIME POINTS. */
    /* Parameter adjustments */
    --z__;
    --t;
    --y;

    /* Function Body */
    j = 1;
    z__[j] = 0.f;
    m = *n1 + 1;
    i__1 = *n2;
    for (i__ = m; i__ <= i__1; ++i__) {
	++j;
	h__ = (r__1 = t[i__] - t[i__ - 1], dabs(r__1));
	a = y[i__] - y[i__ - 1];
	if (y[i__] >= 0.f) {
	    iy = 1;
	}
	if (y[i__] < 0.f) {
	    iy = 0;
	}
	if (y[i__ - 1] >= 0.f) {
	    iy1 = 1;
	}
	if (y[i__ - 1] < 0.f) {
	    iy1 = 0;
	}
	if (iy != iy1) {
	    goto L4;
	}
	q1 = (r__1 = y[i__ - 1], dabs(r__1));
	q2 = (r__1 = y[i__], dabs(r__1));
	if (q2 < q1) {
	    goto L5;
	}
	area = h__ * y[i__ - 1] + h__ * a / 2.f;
	goto L9;
L5:
	a = y[i__ - 1] - y[i__];
	area = h__ * y[i__] + h__ * a / 2.f;
	goto L9;
L4:
	tm = t[i__ - 1] - y[i__ - 1] * h__ / a;
	h1 = (r__1 = tm - t[i__ - 1], dabs(r__1));
	h2 = (r__1 = t[i__] - tm, dabs(r__1));
	area = (h1 * y[i__ - 1] + h2 * y[i__]) / 2.f;
L9:
	z__[j] = z__[j - 1] + area;
/* L10: */
    }
    *np = j;
    k = *n1;
    i__1 = *np;
    for (i__ = 1; i__ <= i__1; ++i__) {
	t[i__] = t[k] - t[*n1];
/* L12: */
	++k;
    }
    return 0;
} /* trap_ */

