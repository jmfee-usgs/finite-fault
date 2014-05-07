C                    PROGRAM TELMOD.F
C
C
C     THIS PROGRAM INTERPOLATES TO A UNIFORM TIME STEP AND BANDPASS
C     BUTTERWORTH FILTERS EITHER OUTPUT FROM CADILLAC OR DIGITIZED
C     TELESEISMIC OBSERVATIONS.  A BINARY OUTPUT FILE AND PLOT ARE
C     CREATED.
C
C     THIS VERSION MODIFIED SO THAT THE ORDER OF PROCESSING
C     IS: 1) REMOVE MEAN,
C     2) FILTER, 3) REMOVE BEGINNING OF RECORD IS DESIRED,
C     4) INTERPOLATE TO OUTPUT TIME STEP, 5) FLIP RECORDS
C     IF DESIRED, 6) PLOT. 
C
c	This is SHartzell's latest TELMOD code, except that
c	plotting has been disabled in this version and responses
c	to yes/no questions have been made consistent...CM/Aug98
c	Dimensions increased to handle max 150 records (was 60)...CM/Feb06)
c
c   This version does not read station/channel info or TSTART value
c   for digital data from GDSN/IRIS (NTYPE=3)...CM/may06
c
c      COMMON/DRAW/SZ(25000)
      COMMON/STA/ STANAM
      COMMON/TERP/TOUT1(25000),TOUT2(25000),TELIN(66000),TELOUT(25000)
      COMMON/DIG/IXDIG(25000),IYDIG(25000),XDIG(25000),YDIG(25000),
     +T(25000),A(25000)
      DIMENSION DTT(150),TFM(150),NFLIP(150),ISKEW(150),ANGLE(150),
     +THETA(150)
      DIMENSION INTYP(150),HIGH(150),XLOW(150)
      INTEGER CODE(4),CHAN(4)
      INTEGER*4 ID(150),RESP
      CHARACTER*40 IFG1,IFG2,IFG3
      CHARACTER*5 STANAM
C
      write(6,*)' **This version of TELMOD does not produce a plot**'
      write(6,*)
      WRITE(6,600)
 600  FORMAT(1X,'NTYPE=1,  PROCESS SYN RECORDS FROM CADILLAC',/,
     +1X,'NTYPE=2,  PROCESS DIGITIZED TRACES FROM PASADENA',/,
     +1X,'NTYPE=3,  PROCESS DIGITAL DATA FROM GDSN/IRIS',/,
     +1X,'NTYPE=4,  PROCESS DIGITIZED TRACES FROM GOLDEN')
      READ(5,*) NTYPE
      WRITE(6,601)
 601  FORMAT(1X,'ENTER INPUT FILE NAME')
      READ(5,602) IFG1
 602  FORMAT(A)
      IF(NTYPE .EQ. 1 .OR. NTYPE .EQ. 3) OPEN(UNIT=9,FILE=IFG1,
     +STATUS='OLD',ACCESS='SEQUENTIAL',FORM='UNFORMATTED')
      IF(NTYPE .EQ. 2 .OR. NTYPE .EQ. 4) OPEN(UNIT=9,FILE=IFG1,
     +STATUS='OLD')
      WRITE(6,603)
 603  FORMAT(1X,'ENTER OUTPUT FILE NAME')
      READ(5,602) IFG2
      OPEN(UNIT=7,FILE=IFG2,STATUS='UNKNOWN',ACCESS='SEQUENTIAL',
     +FORM='UNFORMATTED')      
      IF(NTYPE .GT. 1) GO TO 100
C
C     *********************************
C     PROCESS SYNTHETICS FROM CADILLAC.
C     *********************************
C
      READ(9) NSTA
      WRITE(6,817)
 817  FORMAT(1X,'DO YOU WANT RAMP BANDPASS FILTER (=1), OR',/,
     +1X,'BUTTERWORTH BANDPASS FILTER (=2).')
      READ(5,*) IFILTY
C
      IF(IFILTY .EQ. 1) THEN
      WRITE(6,818)
 818  FORMAT(1X,'ENTER THE FOUR FREQUENCIES DEFINING THE LOW',/,
     +1X,'AND HIGH FREQUENCY RAMPS (FL1, FL2, FH1, FH2), IN',/,
     +1X,'ORDER OF INCREASING FREQUENCY.')
      READ(5,*) FL1,FL2,FH1,FH2
      END IF
C
      IF(IFILTY .EQ. 2) THEN
      WRITE(6,800)
 800  FORMAT(1X,'IS THE HIGHPASS BUTTERWORTH CORNER FREQUENCY',/,
     +1X,'TO BE THE SAME FOR ALL SYNTHETICS, 1=YES 0=NO')
      READ(5,*) RESP
      IF(RESP .EQ. 1) THEN
      WRITE(6,801)
 801  FORMAT(1X,'ENTER THE HIGHPASS BUTTERWORTH CORNER FREQUENCY',/,
     +1X,'ENTER 0. TO SKIP FILTERING.')
      READ(5,*) FIXHIGH      
      DO 1000 I=1,NSTA
 1000 HIGH(I)=FIXHIGH
      ELSE
      WRITE(6,802)
 802  FORMAT(1X,'FOR EACH STATION, ENTER THE CORNER FREQUENCY',/,
     +1X,'OF THE HIGHPASS BUTTERWORTH. ENTER 0. TO SKIP FILTERING')
      READ(5,*) (HIGH(I),I=1,NSTA)
      END IF
      WRITE(6,803)
 803  FORMAT(1X,'IS THE LOWPASS BUTTERWORTH CORNER FREQUENCY',/,
     +1X,'TO BE THE SAME FOR ALL SYNTHETICS, 1=YES 0=NO')
      READ(5,*) RESP
      IF(RESP .EQ. 1) THEN
      WRITE(6,804)
 804  FORMAT(1X,'ENTER THE LOWPASS BUTTERWORTH CORNER FREQUENCY',/,
     +1X,'ENTER 1000. TO SKIP FILTERING.')
      READ(5,*) FIXLOW
      DO 1001 I=1,NSTA
 1001 XLOW(I)=FIXLOW 
      ELSE
      WRITE(6,805)
 805  FORMAT(1X,'FOR EACH STATION, ENTER THE CORNER FREQUENCY',/,
     +1X,'OF THE LOWPASS BUTTERWORTH. ENTER 1000. TO SKIP FILTERING')
      READ(5,*) (XLOW(I),I=1,NSTA)
      END IF
      END IF
C
      WRITE(6,819)
 819  FORMAT(1X,'DO YOU WANT TO DIFFERENTIATE THE SYNTHETICS TO',/,
     +1X,'GET VELOCITIES, 1=YES 0=NO')
      READ(5,*) IDIFF
      WRITE(6,806)
 806  FORMAT(1X,'IS THE OUTPUT TIME STEP TO BE THE SAME FOR ALL',/,
     +1X,'SYNTHETICS, 1=YES 0=NO')
      READ(5,*) RESP
      IF(RESP .EQ. 1) THEN
      WRITE(6,807)
 807  FORMAT(1X,'ENTER THE OUTPUT TIME STEP')
      READ(5,*) FIXDTT
      DO 1007 I=1,NSTA
 1007 DTT(I)=FIXDTT
      ELSE
      WRITE(6,608)
 608  FORMAT(1X,'ENTER OUTPUT TIME STEP FOR EACH INPUT RECORD')
      READ(5,*) (DTT(I),I=1,NSTA)
      END IF
      WRITE(6,609)
 609  FORMAT(1X,'ENTER THE FILE NAME WITH THE FIRST ARRIVAL',/,
     +1X,'TIMES FROM CADILLAC')
      READ(5,602) IFG3
      OPEN(UNIT=10,FILE=IFG3,STATUS='OLD')
      READ(10,616) (ID(I),TFM(I),I=1,NSTA)
 616  FORMAT(1X,A4,F10.5)
      CLOSE(10) 
      WRITE(6,610)
 610  FORMAT(1X,'HOW MANY SUBFAULTS ARE THERE')
      READ(5,*) NSUBF
C
C     LOOP OVER THE NUMBER OF STATIONS
C
      DO 2 LOOP=1,NSTA
      DTOUT=DTT(LOOP)
      DO 3 ISB=1,NSUBF
      READ(9) NT,DT,TSTART
      READ(9) (TELIN(IP),IP=1,NT)
      LQ=NT
      TTT=FLOAT(NT-1)*DT
      LL=INT(TTT/DTOUT)
      IF(LL .GT. LQ) LQ=LL
      DO 5 I=1,LQ
      TOUT1(I)=FLOAT(I-1)*DT
  5   TOUT2(I)=FLOAT(I-1)*DTOUT
C
C     DIFFERENTIATE
C
      IF(IDIFF .EQ. 1) THEN
      CALL DFDX(1,NT,TOUT1,TELIN,TELOUT)
      DO 820 I=1,NT
 820  TELIN(I)=TELOUT(I)
      END IF
C
C     BANDPASS FILTER
C
      IF(IFILTY .EQ. 1) CALL RAMPF(TELIN,NT,DT,FL1,FL2,
     +FH1,FH2)
      IF(IFILTY .EQ. 2) THEN
      FHIGHP=HIGH(LOOP)
      FLOWP=XLOW(LOOP)
      IF(FLOWP .EQ. 1000.) GO TO 501
      FNY=2.*DT*FLOWP
      CALL ZPLOP(2,FNY,TELIN,NT)
 501  IF(FHIGHP .EQ. 0.) GO TO 500
      FNY=2.*DT*FHIGHP
      CALL ZPHIP(2,FNY,TELIN,NT)
 500  CONTINUE
      END IF
C     
C     CUT OFF BEGINNING OF RECORD
C
      NTOS=INT(TFM(LOOP)/DT + 0.5)
      NTNEW=NT-NTOS
      DO 26 I=1,NTNEW
  26  TELIN(I)=TELIN(I+NTOS)
      NT=NTNEW
C
C     INTERPOLATE TO OUTPUT TIME STEP
C
      DTDIF=ABS(DT-DTOUT)
      IF(DTDIF .LT. .005) GO TO 4
      TTT=FLOAT(NT-1)*DT
      LL=INT(TTT/DTOUT)
      CALL INTP2(NT,TOUT1,TELIN,LL,TOUT2,TELOUT)
      DO 6 I=1,LL
      TELIN(I)=TELOUT(I)
  6   continue
      NT=LL
      DT=DTOUT
  4   continue
C
C     WRITE OUT TO FILE
C
      IF(LOOP .GT. 1 .OR. ISB .GT. 1) GO TO 8
      WRITE(7) NSTA
  8   WRITE(7) NT,DT,TSTART  
      WRITE(7) (TELIN(IP),IP=1,NT)
  3   CONTINUE
  2   CONTINUE
      GO TO 900
C
C     **********************************************************
C     PROCESS DATA RECORDS, DIGITAL OR DIGITIZED ANALOG RECORDS.
C     **********************************************************
C
 100  IF(NTYPE .EQ. 2 .OR. NTYPE .EQ. 4) READ(9,27) NSTA
      IF(NTYPE .EQ. 3) READ(9) NSTA
  27  FORMAT(I5)
      WRITE(6,*)' DO YOU WANT TO BUTTERWORTH FILTER DATA RECORDS.'
      WRITE(6,*)' 1=YES, 0=NO'
      READ(5,*) RESP
      IF (RESP .EQ. 0) THEN
      DO 555 II=1,NSTA
      HIGH(II)=0.
 555  XLOW(II)=1000.
      GO TO 666
      ENDIF
      WRITE(6,808)
 808  FORMAT(1X,'IS THE HIGHPASS BUTTERWORTH CORNER FREQUENCY',/,
     +1X,'TO BE THE SAME FOR ALL STATIONS, 1=YES, 0=NO')
      READ(5,*) RESP
      IF(RESP .EQ. 1) THEN
      WRITE(6,611)
 611  FORMAT(1X,'ENTER CORNER FREQUENCY OF HIGHPASS BUTTERWORTH',/,
     +1X,'ENTER 0. IF YOU WANT FILTERING SKIPPED.')
      READ(5,*) FIXHIGH
      DO 1002 I=1,NSTA
 1002 HIGH(I)=FIXHIGH 
      ELSE
      WRITE(6,809)
 809  FORMAT(1X,'FOR EACH STATION, ENTER THE CORNER FREQUENCY',/,
     +1X,'OF THE HIGHPASS BUTTERWORTH. ENTER 0. TO SKIP FILTERING')
      READ(5,*) (HIGH(I),I=1,NSTA)
      END IF 
      WRITE(6,810)
 810  FORMAT(1X,'IS THE LOWPASS BUTTERWORTH CORNER FREQUENCY',/,
     +1X,'TO BE THE SAME FOR ALL STATIONS, 1=YES, 0=NO')
      READ(5,*) RESP
      IF(RESP .EQ. 1) THEN
      WRITE(6,612)
 612  FORMAT(1X,'ENTER CORNER FREQUENCY OF LOWPASS BUTTERWORTH',/,
     +1X,'ENTER 1000. IF YOU WANT FILTERING SKIPPED.')
      READ(5,*) FIXLOW
      DO 1003 I=1,NSTA
 1003 XLOW(I)=FIXLOW 
      ELSE
      WRITE(6,811)
 811  FORMAT(1X,'FOR EACH STATION, ENTER THE CORNER FREQUENCY',/,
     +1X,'OF THE LOWPASS BUTTERWORTH. ENTER 1000. TO SKIP FILTERING')
      READ(5,*) (XLOW(I),I=1,NSTA)
      END IF
 666  CONTINUE
      WRITE(6,630)
 630  FORMAT(1X,'DO YOU WANT TO REMOVE THE MEAN FROM THE DATA',/,
     +1X,'RECORDS, 1=YES  0=NO.')
      READ(5,*) IMEAN
      IF(IMEAN .EQ. 1) THEN
      WRITE(6,631)
 631  FORMAT(1X,'OVER HOW MANY POINTS DO YOU WANT THE MEAN',/,
     +1X,'CALCULATED. IF SET LARGE, IT WILL BE RESET TO RECORD LENGTH') 
      READ(5,*) NMEAN
      END IF
      WRITE(6,620)
 620  FORMAT(1X,'DO YOU WANT TO FLIP ANY OF THE DATA RECORDS',/,
     +1X,'1=YES  0=NO.')
      READ(5,*) IFLIP
      IF(IFLIP .EQ. 1) THEN
      WRITE(6,622)
 622  FORMAT(1X,'HOW MANY RECORDS DO YOU WANT TO FLIP.')
      READ(5,*) NFP
      WRITE(6,621) 
 621  FORMAT(1X,'ENTER THE RECORD NUMBERS IN THE ORDER THAT THEY',/,
     +1X,'ARE READ IN OF THE STATIONS THAT YOU WANT TO FLIP.')
      READ(5,*) (NFLIP(I),I=1,NFP)
      END IF
      IF(NTYPE .EQ. 3) GO TO 200
      WRITE(6,613)
 613  FORMAT(1X,'FOR EACH INPUT RECORD ..... ',/,
     +1X,'ENTER INTYP =1 , USES LINEAR INTERPOLATION',/,
     +1X,'      INTYP =2 , USES PEAK-TROUGH INTERPOLATION')
      READ(5,*) (INTYP(I),I=1,NSTA)
      WRITE(6,635)
 635  FORMAT(1X,'FOR EACH INPUT RECORD, DO YOU WANT TO DESKEW',/,
     +1X,' THE TRACE,  1=YES 0=NO')
      READ(5,*) (ISKEW(I),I=1,NSTA)
      DO 39 I=1,NSTA
  39  IF(ISKEW(I) .EQ. 1) GO TO 40 
      GO TO 200
  40  WRITE(6,636)
 636  FORMAT(1X,'ENTER LENGTH OF PEN ARM. IF RECORD IS TO BE',/,
     +1X,'DESKEWED ONLY SET EQUAL TO ZERO. IF RECORD IS TO BE',/,
     +1X,'DESKEWED AND CORRECTED FOR CURVATURE SET EQUAL TO',/,
     +1X,'ITS ACTUAL VALUE IN THE SAME UNITS AS THE DIGITIZED',/,
     +1X,'TRACE.')
      READ(5,*) PENARM
      WRITE(6,637)
 637  FORMAT(1X,'FOR EACH INPUT RECORD, ENTER SKEW ANGLE IN DEGREES.')
      READ(5,*) (ANGLE(I),I=1,NSTA)
      DO 47 I=1,NSTA
      ANGLE(I)=ANGLE(I)*3.1415926/180.
      RATIO=0.3
      SANG=SIN(ANGLE(I))
      CANG=COS(ANGLE(I))
      THETA(I)=ATAN2(RATIO*SANG,CANG)
  47  CONTINUE
 200  WRITE(6,812)
 812  FORMAT(1X,'IS THE OUTPUT TIME STEP TO BE THE SAME FOR ALL',/,
     +1X,'RECORDS.  1=YES  0=NO.')
      READ(5,*) RESP
      IF(RESP .EQ. 1) THEN
      WRITE(6,614)
 614  FORMAT(1X,'ENTER THE DESIRED OUTPUT TIME STEP.')
      READ(5,*) FIXDTT
      DO 1005 I=1,NSTA
 1005 DTT(I)=FIXDTT 
      ELSE
      WRITE(6,813)
 813  FORMAT(1X,'FOR EACH RECORD, ENTER THE OUTPUT TIME STEP')
      READ(5,*) (DTT(I),I=1,NSTA)
      END IF
      WRITE(6,814)
 814  FORMAT(1X,'IS THE SECTION OF RECORD TO BE REMOVED FROM THE',/,
     +1X,'BEGINNING THE SAME FOR ALL RECORDS,  1=YES  0=NO.')
      READ(5,*) RESP
      IF(RESP .EQ. 1) THEN
      WRITE(6,615)
 615  FORMAT(1X,'ENTER THE LENGTH OF RECORD IN SECONDS',/,
     +1X,'TO BE REMOVED FROM THE BEGINNING OF THE RECORDS,',/,
     +1X,'SAVING THE FOLLOWING SECTION FOR INVERSION.')
      READ(5,*) FIXTFM
      DO 1006 I=1,NSTA
 1006 TFM(I)=FIXTFM 
      ELSE
      WRITE(6,815)
 815  FORMAT(1X,'FOR EACH RECORD, ENTER THE LENGTH OF RECORD IN',/,
     +1X,'SECONDS TO BE REMOVED FROM THE BEGINNING OF THE RECORD,',/,
     +1X,'SAVING THE FOLLOWING SECTION FOR INVERSION.')
      READ(5,*) (TFM(I),I=1,NSTA)
      END IF
C
C     LOOP OVER THE NUMBER OR STATIONS
C
      DO 10 LOOP=1,NSTA
      FHIGHP=HIGH(LOOP)
      FLOWP= XLOW(LOOP)
      DTOUT=DTT(LOOP)
C
C     READ IN RECORDS DIGITIZED IN GOLDEN
C
      IF(NTYPE .EQ. 4) THEN
      CALL GETDIG(LOOP,XDIG,YDIG,ASCALE,L,NSTA)
      GO TO 16
      END IF
      IF(NTYPE .EQ. 3) GO TO 250
C
C     READ IN RECORDS DIGITIZED IN PASADENA
C     IFLAG NOT USED
C     
      READ(9,27) IFLAG
      READ(9,29) GAINF
      READ(9,11) T1,AS
  11  FORMAT(2F10.0)
  29  FORMAT(F10.0)
      TSCALE=60./T1
      ASCALE=1./AS
      ASCALE=ASCALE*GAINF
      JO=1000
      ISTM=1
      IEND=5
      DO 12 J=1,JO
  13  READ(9,14) (IXDIG(I),IYDIG(I),I=1,5)
  14  FORMAT(1X,10I7)
      I=0
      DO 15 IK=ISTM,IEND
      I=I+1
      L=(J-1)*5+IK
      XDIG(L)=FLOAT(IXDIG(I))*TSCALE
      IF(IABS(IYDIG(I)) .EQ. 999999) GO TO 16
      YDIG(L)=FLOAT(IYDIG(I))
  15  CONTINUE
  12  CONTINUE
C
C     DESKEW RECORDS
C
  16  LF=L-1
      L=L-1
      IF(ISKEW(LOOP) .EQ. 1) THEN
      RADIUS=PENARM
      IF(PENARM .EQ. 0.) THEN
      YMAX=-1.E+32
      YMIN=-YMAX
      DO 41 I=1,L
      YMAX=AMAX1(YMAX,YDIG(I))
  41  YMIN=AMIN1(YMIN,YDIG(I))
      RADIUS=1000.*(ABS(YMAX)+ABS(YMIN))
      END IF
      THETA0=THETA(LOOP)
      CALL DESKEW(THETA0,RADIUS,L,XDIG,YDIG,IERR,TOUT1,
     +TOUT2)
      DO 38 I=1,L
      XDIG(I)=TOUT1(I)
  38  YDIG(I)=TOUT2(I)
      WRITE(6,634) IERR
 634  FORMAT(1X,'ERROR FLAG FROM DESKEW= ',I5)
      END IF
C 
C     INTERPOLATE TO UNIFORM TIME STEP
C
      NN=(XDIG(L)-XDIG(1))/DTOUT
      T(1)=XDIG(1)
      DO 17 J=2,NN
  17  T(J)=T(J-1)+DTOUT
      IF(INTYP(LOOP) .EQ. 1) GO TO 18
      CALL METH(XDIG,YDIG,L,DTOUT,NN,A)
      DO 19 J=1,NN
  19  A(J)=A(J)*ASCALE
      GO TO 20
  18  DO 21 J=1,NN
      CALL INTERP(XDIG,YDIG,L,T(J),YI)
  21  A(J)=YI*ASCALE
  20  GO TO 300
C
C     READ IN DIGITAL RECORDS
C
c 250  READ(9) (CODE(I),I=1,4),(CHAN(I),I=1,4)
c      READ(9) NN,DTIN,TSTART
 250  CONTINUE
      READ(9) NN,DTIN
      READ(9) (A(I),I=1,NN)
 300  CONTINUE
C
C     REMOVE MEAN, IF DESIRED
C
      IF(IMEAN .EQ. 1) THEN
      AMP=0.
      NME=NMEAN
      IF(NMEAN .GT. NN) NME=NN
      DO 632 I=1,NME
 632  AMP=AMP+A(I)
      AMP=AMP/FLOAT(NME)
      DO 633 I=1,NN
 633  A(I)=A(I)-AMP
      END IF    
C
C     BANDPASS FILTER
C
      IF(FLOWP .EQ. 1000.) GO TO 301
      IF(NTYPE .EQ. 2 .OR. NTYPE .EQ. 4) FNY=2.*DTOUT*FLOWP
      IF(NTYPE .EQ. 3) FNY=2.*DTIN*FLOWP
      CALL ZPLOP(2,FNY,A,NN)
 301  IF(FHIGHP .EQ. 0.) GO TO 400
      IF(NTYPE .EQ. 2 .OR. NTYPE .EQ. 4) FNY=2.*DTOUT*FHIGHP
      IF(NTYPE .EQ. 3) FNY=2.*DTIN*FHIGHP
      CALL ZPHIP(2,FNY,A,NN)
C
C     REMOVE SECTION FROM BEGINNING OF RECORDS, IF DESIRED
C
 400  IF(NTYPE .EQ. 2 .OR. NTYPE .EQ. 4) 
     +NTOS=INT(TFM(LOOP)/DTOUT + 0.5)
      IF(NTYPE .EQ. 3) NTOS=INT(TFM(LOOP)/DTIN + 0.5)
      NTNEW=NN-NTOS
      DO 25 I=1,NTNEW
  25  A(I)=A(I+NTOS)
      NN=NTNEW
C
C     INTERPOLATE TO OUTPUT TIME STEP
C
      IF(NTYPE .EQ. 2 .OR. NTYPE .EQ. 4) GO TO 350
      DTDIF=ABS(DTOUT-DTIN)
      IF(DTDIF .LT. .005) GO TO 350
      DO 44 I=1,NN
44    TOUT1(I)=DTIN*FLOAT(I-1)
      LL=TOUT1(NN)/DTOUT
      DO 45 I=1,LL
45    TOUT2(I)=DTOUT*FLOAT(I-1)
      CALL INTP2(NN,TOUT1,A,LL,TOUT2,TELOUT)
      DO 46 I=1,LL
46    A(I)=TELOUT(I)
      NN=LL
C
C     FLIP RECORDS, IF DESIRED
C
350   IF(IFLIP .EQ. 1) THEN
      DO 623 I=1,NFP
      IF(LOOP .EQ. NFLIP(I)) GO TO 624
 623  CONTINUE
      GO TO 625
 624  DO 626 I=1,NN
 626  A(I)=-A(I)
 625  END IF
C
      IF(LOOP .LT. 10) WRITE(STANAM(1:1),'(I1)') LOOP
      IF(LOOP .GT.  9) WRITE(STANAM(1:2),'(I2)') LOOP
C
C     WRITE OUT TO FILE
C
      IF(LOOP .GT. 1) GO TO 23
      WRITE(7) NSTA
  23  DTEL=DTOUT
      WRITE(7) NN,DTOUT
      WRITE(7) (A(IP),IP=1,NN)
  10  CONTINUE
      GO TO 900
  30  WRITE(6,31) DTEL,DTOUT
  31  FORMAT(1X,'DTEL= ',F10.4,' IS NOT EQUAL TO DTOUT= ',F10.4)
 900  continue
      CLOSE(9)
      CLOSE(7)
      STOP
      END
      SUBROUTINE GETDIG(LOOP,XDIG,YDIG,ASCALE,L,NSTA)
      DIMENSION TIME(100),XDIG(1),YDIG(1)
      CHARACTER*40 NAME
      CHARACTER*5 STANAM
      COMMON/STA/ STANAM
      IF(LOOP .EQ. 1) THEN
      WRITE(6,600)
 600  FORMAT(1X,'ENTER NAME OF FILE WITH X AXIS TIME SCALE',/,
     +1X,'INFORMATION')
      READ(5,601) NAME
 601  FORMAT(A)
      OPEN(UNIT=10,FILE=NAME,STATUS='OLD')
      END IF
C
C     DETERMINE ENLARGEMENT FACTOR, TIME SCALE, AND GAIN FACTOR
C
      READ(10,606) NPT,GAIN,STANAM,STRCH
 606  FORMAT(2X,I5,16X,F14.5,3X,A,7X,F7.5)
 602  FORMAT(2X,I5)
      READ(10,603) (TIME(I),I=1,NPT)
 603  FORMAT(F10.3)
      TSC=0.
      NPT1=NPT-1
      IC=0
      DO 2 I=1,NPT1
      IF(TIME(I) .EQ. 0. .OR. TIME(I+1) .EQ. 0.) GO TO 2
      TSC=TSC+ABS(TIME(I+1)-TIME(I))
      IC=IC+1
  2   CONTINUE
      TSC=TSC/FLOAT(IC)
      ENLARG=TSC*25.4/15.
      IF(STRCH .NE. 0.) ENLARG=TSC*25.4/30.
      ASCALE=25400./(GAIN*ENLARG)
      TSC=60./TSC
      WRITE(6,604) ENLARG,TSC,ASCALE
 604  FORMAT(1X,'ENLARGEMENT FACTOR= ',F10.4,' SECONDS/INCH= ',
     +F10.4,' GAIN FACTOR= ',F10.4)
C
C     READ IN SEISMOGRAM
C
C     READ(9,602) NP
C     READ(9,605) (XDIG(I),YDIG(I),I=1,NP)
 605  FORMAT(2F10.3)
      READ(9,602) NP
      READ(9,605) (XDIG(I),YDIG(I),I=1,NP)
      XST=XDIG(1)
      DO 3 I=1,NP
  3   XDIG(I)=(XDIG(I)-XST)*TSC
      L=NP+1
      IF(LOOP .EQ. NSTA) CLOSE(10)
      RETURN
      END
      SUBROUTINE LOPAS(M,F2,X,NL,IBACK)
C
C
C
C Subroutine LOPAS.
C
C    LOPAS is a Butterworth low pass reCursive filter written by
C Keith McCamy at Lamont-Doherty Geological Observatory, N.Y.  It is
C used in place of the Ormsby filter.
C
C    Call LOPAS (m, f2, x, nl, iback)
C
C        m = a flag;
C            if > 0, a filter is designed and new data used
C            if = 0, the last designed filter is used
C            if < 0, the last filter is used with new data
C        f2 = corner frequency in Nyquist units (fny=2*dt*fcps)
C        x = source data array
C        nl = the number of points in x
C        iback = a flag that indicates direction; 0 = forward,
C            1 = backward
C
C
C
      DIMENSION  ALR(5), ALI(5), AO(5), A1(5), B1(5), B2(5), X(1)
      DIMENSION  Z(5), Z1(5), Z2(5)
C
      IF (M) 10, 2, 1
   10 N = -M
      GOTO 20
    1 N = M
      FN = N * 2
      RT = 3.1415926 / FN
      FI = -RT / 2.
      WW = X(1)
      DO 12 I = 1,N
         Z1(I) = 0.
         Z2(I) = 0.
         FI = FI + RT
         ALR(I) = -COS(FI)
   12    ALI(I) = SIN(FI)
      DO 122 K = 1,N
         PR = 0.
         PI = 2. * ALI(K)
         PRK = ALR(K)**2 - ALI(K)**2
         DO 1221 I = 1,N
            IF (I .EQ. K) GOTO 1221
            DR = PRK - ALR(K)*ALR(I)*2. + 1.
            DI = 2.*ALR(K)*ALI(K) - 2.*ALI(K)*ALR(I)
            TPR = PR*DR - PI*DI
            PI = PR*DI + PI*DR
            PR = TPR
 1221       CONTINUE
         DR = PR*PR + PI*PI
         AR = PR / DR
         AI = -PI / DR
         A1(K) = 2. * AR
         AO(K) = 2. * (ALR(K)*AR+ALI(K)*AI)
  122    B1(K) = -2. * ALR(K)
C...  HERE ENDS ALL GENERALIZED FORMS
      POO = F2 * 3.1415926/2.
      WU = 2. * SIN(POO)/COS(POO)
      DO 13 K = 1,N
         DR = 4./WU/WU + B1(K)*2./WU + 1.
         TA = (A1(K)*2./WU-AO(K)) / DR
         A1(K) = -(A1(K)*2./WU+AO(K)) / DR
         AO(K) = TA
         B2(K) = (4./WU/WU-B1(K)*2./WU+1.) / DR
   13    B1(K) = (2.-8./WU/WU) / DR
   20 CONTINUE
      WW = X(1)
      IF (IBACK .EQ. 1) WW = X(NL)
      DO 201 I = 1,N
         Z1(I) = 0.
  201    Z2(I) = 0.
    2 DO 22 II = 1,NL
         I = II
         IF (IBACK .EQ. 1) I = NL - II + 1
         ZZ = X(I) + WW
         XX = 0.
         WW = X(I)
         DO 21 J = 1,N
            Z(J) = ZZ - B1(J)*Z1(J) - B2(J)*Z2(J)
            XX = XX + AO(J)*Z(J) + A1(J)*Z1(J)
            Z2(J) = Z1(J)
   21       Z1(J) = Z(J)
   22    X(I) = XX
      PN = N
      FP = F2
      RETURN
      END
      SUBROUTINE HIPAS (M, F2, X, NL, IBACK)
C
C
C
C Subroutine HIPAS.
C
C    HIPAS uses MCCamy's Butterworth high-pass recursive
C filter.
C
C    Call HIPAS (m, f2, x, nl, iback)
C
C        m = filter flag; if it = 0 then the last
C            designed filter is used; if it > 0 then
C            it designs a filter and starts with new data;
C            if it < 0 then it uses the last filter, but
C            starts on new data
C        f2 = the corner frequency in Nyquist units (fny =
C             2*dt*fcps)
C        x = the source array
C        nl = the number of points in x
C        iback = a flag that indicates direction; 0 = forward,
C            1 = backward
C
C
C
      DIMENSION  ALR(5), ALI(5), AO(5), A1(5), B1(5), B2(5), X(1)
      DIMENSION  Z(5), Z1(5), Z2(5)
C
      IF(M) 10, 2, 1
C...  N = filter order (roll-off=N*12db/octave)
   10 N = -M
      GOTO 20
    1 N = M
      FN = N * 2
      RT = 3.1415926 / FN
      FI = -RT / 2.
      WW = X(1)
      DO 12 I = 1,N
         Z1(I) = 0.
         Z2(I) = 0.
         FI = FI + RT
         ALR(I) = -COS(FI)
   12    ALI(I) = SIN(FI)
      DO 122 K = 1,N
         PR = 0.
         PI = 2. * ALI(K)
         PRK = ALR(K)**2 - ALI(K)**2
         DO 1221 I = 1,N
            IF(I .EQ. K) GOTO 1221
            DR = PRK - 2.*ALR(K)*ALR(I) + 1.
            DI = 2.*ALR(K)*ALI(K) - 2.*ALI(K)*ALR(I)
            TPR = PR*DR - PI*DI
            PI = PR*DI + PI*DR
            PR = TPR
 1221       CONTINUE
         DR = PR*PR + PI*PI
         AR = PR / DR
         AI = -PI / DR
         A1(K) = 2. * AR
         AO(K) = 2. * (ALR(K)*AR+ALI(K)*AI)
  122    B1(K) = -2. * ALR(K)
C
C   HERE ENDS ALL GENERALIZED FORMS
C   BUILD HIGH PASS
      POO = F2 * 3.1415926 / 2.
      WU = 2. * SIN(POO) / COS(POO)
      DO 13 K = 1,N
         DR = WU*WU/4. + B1(K)*WU/2. + 1.
         TA = (A1(K)*WU/2.-AO(K)) / DR
         A1(K) = (A1(K)*WU/2.+AO(K)) / DR
         AO(K) = TA
         B2(K) = (WU*WU/4.-B1(K)*WU/2.+1.) / DR
   13    B1(K) = (WU*WU/2.-2.) / DR
   20 CONTINUE
      WW = X(1)
      IF (IBACK .EQ. 1) WW = X(NL)
      DO 201 I = 1,N
         Z1(I) = 0.
  201    Z2(I) = 0.
    2 DO 22 II = 1,NL
         I = II
         IF (IBACK .EQ. 1) I = NL - II + 1
         ZZ = X(I) - WW
         XX = 0.
         WW = X(I)
         DO 21 J = 1,N
            Z(J) = ZZ - B1(J)*Z1(J) - B2(J)*Z2(J)
            XX = XX + AO(J)*Z(J) + A1(J)*Z1(J)
            Z2(J) = Z1(J)
   21       Z1(J) = Z(J)
   22    X(I) = XX
      PN = N
      FP = F2
      RETURN
      END
      SUBROUTINE ZPLOP (M, FR2, X, NL)
C
C
C
C Subroutine ZPLOP.
C
C    ZPLOP Calls McCamys low pass Butterworth routine 2 times,
C once forward and once with the time sequence reversed.
C
C    call ZPLOP (m, fr2, x, nl)
C
C        m  - integer roll-off width for high pass
C        fr2- corner frequency
C        x  - array that will be filtered, equally spaced in time
C        nl - the number of elements in x
C
C
C
C
      DIMENSION  X(NL)
C
      IBACK=0
      CALL LOPAS(M,FR2,X,NL,IBACK)
      IBACK=1
      CALL LOPAS(M,FR2,X,NL,IBACK)
      RETURN
      END
      SUBROUTINE ZPHIP (M, FR2, X, NL)
C
C
C
C Subroutine ZPHIP.
C
C    ZPHIP Calls McCamys high pass Butterworth routine 2 times,
C once forward and once with the time sequence reversed.
C
C    call ZPHIP (m, fr2, x, nl)
C
C        m  - integer roll-off width for high pass
C        fr2- corner frequency
C        x  - array that will be filtered, equally spaced in time
C        nl - the number of elements in x
C
C
C
      DIMENSION  X(NL)
C
      IBACK = 0
      CALL HIPAS(M,FR2,X,NL,IBACK)
      IBACK = 1
      CALL HIPAS(M,FR2,X,NL,IBACK)
      RETURN
      END
      SUBROUTINE INTP2(N,TT3,TA,NP,TT1,TA1)
      DIMENSION TT3(1),TA(1),TT1(1),TA1(1)
      J=1
      I=1
  25  CONTINUE
      IF(TT1(I) .GT. TT3(J)) GO TO 30
      TA1(I)=0.
      IF(TT1(I) .EQ. TT3(J)) TA1(I)=TA(J)
      IF(I .GE. NP) GO TO 20
      I=I+1
      GO TO 25
  30  CONTINUE
  15  CONTINUE
      IF(TT1(I) .GT. TT3(J)) GO TO 10
      SLP=(TA(J)-TA(J-1))/(TT3(J)-TT3(J-1))
      B=-SLP*TT3(J)+TA(J)
      TA1(I)=SLP*TT1(I)+B
      IF(I .GE. NP) GO TO 20
      I=I+1
      GO TO 15
  10  CONTINUE
      IF(J .GE. N) GO TO 20
      J=J+1
      GO TO 15
  20  CONTINUE
      RETURN
      END
c
      SUBROUTINE INTERP(XP,YP,N,X,Y)
      DIMENSION XP(N),YP(N)
      REAL DIF1,DIF2,DIFY,DR
    1 IF (X.GT.XP(N))  GO TO 6
      IF (X .LT. XP(1))  GO TO 6
    2 DO 10  I=1,N
      IF (XP(I)-X) 10,102,3
   10 CONTINUE
    3 K=I-1
      DIF1=XP(I)-XP(K)
      DIF2=XP(I)-X
      RATIO = DIF2/DIF1
      DIFY=ABS(YP(I) - YP(K))
      DR = DIFY*RATIO
      IF (YP(I) .GT. YP(K))  GO TO 4
    5 Y=YP(I) + DR
      RETURN
    4 Y=YP(I)-DR
      RETURN
  102 Y=YP(I)
      RETURN
    6 Y=0.0
      RETURN
      END
c
      SUBROUTINE METH (X,Y,NP,DT,NOUT,Z)
      DIMENSION X(1),Y(1),Z(1)
C
C     PROGRAM METH --- FAST INTERPOLATION ROUTINE
C
C     BOB HART AND DAVE HADLEY
C     SEISMO LAB; SEPT. 17, 1976
C
C     ALGORITHM BASED ON A SUGGESTION BY SHELTON ALEXANDER.
C     RAW SEISMOGRAM IS DIGITIZED WITH ONE POINT AT EACH PEAK AND
C     TROUGH AND THREE POINTS AT INFLECTION POINTS.  DATA THEN FIT WITH
C     HALF COSINES AND CUBICS (AT INFLECTIONS).
C
C     WARNING - LAST POINT IN INPUT ARRAY MUST BE A PEAK OR TROUGH}}}
C
C     INPUT: X,Y - DIGITIZED DATA ARRAYS
C             NP - # DIGITIZED POINTS
C             DT - TIME SPACING OF OUTPUT POINTS
C     OUTPUT : Z - EQUALLY SPACED AMPLITUDES
C             NOUT - # Z POINTS
      PI=3.141593
C
C     FIRST PASS - - - COMPRESS INPUT ARRAYS AND SET UP SLOPE ARRAY
C     SLOPE ARRAY PACKED INTO END OF Z ARRAY
C
      DX=(X(NP)-X(1))/DT
      ID=DX
      NOUT=ID+1
      NOUT1=NOUT+1
      L=NOUT1-NP
      Z(NOUT1)=0.0
      I=1
      K=1
      Z(L)=0.0
      NP1=NP-1
  100 CONTINUE
      JJ=I-NP1
      K=K+1
      L=L+1
      IF(JJ)150,200,400
  150 D=(Y(I+1)-Y(I))*(Y(I+2)-Y(I+1))
      IF(D)200,200,300
  200 I=I+1
      Z(L)=0.0
      Y(K)=Y(I)
      X(K)=X(I)
      GO TO 100
  300 I=I+2
      YS=Y(I-1)
      XS=X(I-1)
      Y(K)=Y(I)
      X(K)=X(I)
      Z(L)=(Y(I+1)-YS)/(X(I+1)-XS)
      I=I+1
      GO TO 100
  400 CONTINUE
      L=L-1
      K=K-1
      NFIX=NOUT-L
      MOUT=L
      DO 450 JI=1,MOUT
      IJ=NOUT1-JI
      Z(IJ)=Z(L)
  450 L=L-1
C
C     SECOND PASS - - - INTERPOLATION ALGORITHM
C
      DX=0.0
      NP1=K-1
      K=1
      L=NOUT1+NFIX-NP
      DO 500 I=1,NP1
      L0=L+I
      L1=L0+1
      AV=ABS(Z(L0)+Z(L1))
C
C     CHECK FOR INFLECTION.  IF INFLECTION, GO TO CUBIC INTERPOLATION.
C
      IF(AV.GT.1.0E-05)GO TO 550
C
C     COSINE INTERPOLATION
C
      T=X(I+1)-X(I)
      PIT=PI/T
      AMP=(Y(I+1)-Y(I))/2.0
      U=X(I)+DX
  510 CONTINUE
      IF(U.GT.X(I+1))GO TO 800
      S=U-X(I)
      U=U+DT
      W=PIT*S
      Z(K)=Y(I)+AMP*(1.0-COS(W))
      K=K+1
      GO TO 510
  550 CONTINUE
C
C     CUBIC INTERPOLATION
C
      X2=X(I+1)-X(I)
      WRITE (6,700) I,X(I),X(I+1),X2
 700  FORMAT ('I,X(I),X(I+1),X2=',I4,3E14.4)
      A=Y(I)
      B=Z(L0)
      E=X2*X2
      S=Z(L1)
      D=(S+B)/E+2.0*(A-Y(I+1))/(X2*E)
      C=(S-B)/(2.0*X2)-1.5*D*X2
      U=DX
  560 CONTINUE
      IF(U.GT.X2)GO TO 600
      Z(K)=A+B*U+C*U*U+D*(U**3)
      K=K+1
      U=U+DT
      GO TO 560
  600 DX=U-X2
      GO TO 500
  800 DX=U-X(I+1)
  500 CONTINUE
      Z(NOUT)=Y(NP)
      RETURN
      END
      SUBROUTINE DESKEW(THETA0,RADIUS,NPTS,X,Y,IERR,T,AMP)
C
C   SUBROUTINE TO DESKEW AND DECURVE A SEISMOGRAM
C   INPUTS : THETA0,RADIUS,NPTS,X,Y
C   OUTPUT : T,AMP,IERR
C
C   THE INPUT CURVE IS AN ORDERED SET OF PAIRS
C   OF NUMBERS X(I),Y(I) WHERE X IS IN THE TIME DIRECTION
C   AND Y IS IN THE AMPLITUDE DIRECTION.
C   THE INDEX I RUNS FROM 1 TO NPTS.
C
C   THE CURVE S ASSUMED TO BE DESCRIBED BY:
C
C   X(I)=V*(T-T0)+RADIUS*(COS(THETA0)-COS(THETA+THETA0))
C   Y(I)=RADIUS*(SIN(THETA+THETA0)-SIN(THETA0))
C
C   THE PAPER TRANSLATION SPEED IS V (NOT NEEDED HERE).
C   THE PEN ARM LENGTH IS RADIUS. RADIUS IS POSITIVE.
C   IF THE TRACE CURVATURE IS TOO SMALL TO DETECT,
C   SET RADIUS TO A NUMBER GREATER THAN 100. TIMES THE
C   MAXIMUM TRACE AMPLITUDE.
C   RADIUS, X AND Y SHOULD BE IN THE SAME UNITS.
C   THE OFFSET ANGLE IS THETA0.
C   THETA0 IS MEASURED FROM THE SEISMOGRAM AS THE ANGLE
C   WHICH THE TRACE MAKES WITH THE POSITIVE AMPLITUDE DIRECTION,
C   MEASURED CLOCKWISE FROM POSITIVE AMPLITUDE AND WHEN
C   D(THETA)/DT >> V/RADIUS
C   IF THE ARC IS CONVEX TOWARD INCREASING TIME,
C      -PI/2. < THETA0 < PI/2.
C   IF THE ARC IS CONVEX TOWARD DECREASING TIME,
C       PI/2. < THETA0 < 3.*PI/2.
C   THE INPUT VOLTAGE TO THE PEN DEFLECTING MECHANISM
C   IS ASSUMED TO BE PROPORTIONAL TO THETA. THE DESIRED
C   RESPONSE IS THETA*RADIUS, AS A FUNCTION OF TIME, T.
C   THIS ROUTINE ASSUMES THAT THETA LIES IN THE
C   SAME INTERVAL  (-PI/2.,PI/2.) OR (PI/2.,3.*PI/2.)
C   AS THETA0.
C
C   THE RELATIONSHIP BETWEEN TIME AND THE INDEX I IS UNKNOWN,
C   EXCEPT THAT I INCREASES MONOTONICALLY WITH TIME.
C
C   FROM THE ABOVE EQUATIONS ONE MAY ELIMINATE TTHETA TO
C   OBTAIN TIME, T, AS A FUNCTION OF X(I) AND Y(I).
C   V*(T-T0) = X(I)-R*COS(THETA0)+{R**2-(Y(I)+R*SIN(THETA0))**2}**1/2
C
C   THE QUANTITIES RETURNED ARE IERR, T(I) AND AMP(I),
C   WHERE AMP(I) IS RADIUS*THETA(I) A T(I) IS THE VALUE OF
C   V*(T-T0) CORRESPONDING TO INDEX I.
C   IERR IS THE ERROR RETURN FLAG.
C   IERR=0  : NO ERROR
C   IERR=1  : RADIUS TOO SMALL
C   IERR=2  : CALCULATED TIME IS MULTIVALUED AS A FUNCTION OF I.
C
      DIMENSION X(1),Y(1),T(1),AMP(1)

      COSTH0=COS(THETA0)
      SINTH0=SIN(THETA0)
      IERR=0
C
C   CHECK FOR CURVATURE.
C   CHECK FOR RADIUS TOO SMALL.
C
      YMAX=0.
      DO 01 I=1,NPTS
      YMAX=AMAX1(YMAX,ABS(Y(I)))
   01 CONTINUE

      TEST=100.*YMAX/RADIUS
      IF(TEST.LT.1.) GOTO 50
      IF(TEST.GT.100.) GOTO 1000
C
C   LOOP FOR CURVATURE AND SKEW
C
      X0=RADIUS*COSTH0
      Y0=-RADIUS*SINTH0
      R2=RADIUS*RADIUS
      DO 11 I=1,NPTS
      YDIF=Y(I)-Y0
      ARG=R2-YDIF*YDIF
      IF(ARG.LE.0.) GOTO 1000
   11 T(I)=X(I)-X0+SQRT(ARG)

      A0=RADIUS*ARCSIN(THETA0)

      DO 13 I=1,NPTS
   13 AMP(I)=RADIUS*ARCSIN(Y(I)/RADIUS+SINTH0)-A0

      DO 12 I=2,NPTS
   12 IF(T(I).LE.T(I-1)) GOTO 1001
      RETURN

   50 CONTINUE
C
C   DESKEW ONLY
C
      DO 51 I=1,NPTS
      AMP(I)=Y(I)/COSTH0
   51 T(I)=X(I)-AMP(I)*SINTH0

      DO 52 I=2,NPTS
   52 IF(T(I).LE.T(I-1)) GOTO 1001

      RETURN

 1000 IERR=1
      RETURN
 1001 IERR=2
      RETURN
      END
c
      FUNCTION ARCSIN(X)
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
C    ARCSIN FUNCTION CODED JULY 30 1978 BY J.B. MINSTER
C    BASED ON CHEBYSHEV APPROXIMATION DEGREE 11
C    REF ABRAMOWITZ & STEGUN AND IBM SCIENTIFIC PACKAGE
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
      IS=1
      IF(X.LT.0.)IS=-1
      Z=ABS(X)
      IFLAG=0
      IF(X.LT.0.5) GO TO 10
      IFLAG=1
      Z=SQRT(0.5*(1.-Z))
10    CONTINUE
      Y=4.*Z*Z-1.
      Y2=Y*Y
      Y3=Y2*Y
      Y4=Y3*Y
      Y5=Y4*Y
      ARCSIN=1.047198313+0.053752222*Y+0.007785382*Y2
      ARCSIN=ARCSIN+0.001619798*Y3+0.00037588*Y4+0.0000941*Y5
      ARCSIN=ARCSIN*Z
      IF(IFLAG.EQ.1)ARCSIN=1.570796327-2.*ARCSIN
      ARCSIN=ARCSIN*IS
      RETURN
      END
c
      SUBROUTINE DFDX(N1,N2,X,F,DF)
      DIMENSION X(1),F(1),DF(1)
      I2=N1-1
  8   I1=I2+1
      I2=I1+1
      H1=X(I1)
      DO 9 I=I2,N2
      H2=X(I)
      IF(H1-H2)9,10,9
  9   H1=H2
      I2=N2
      GO TO 11
  10  I2=I-1
  11  I=I2-I1
      IF(I)3,5,4
  4   IF(I-1)5,6,7
  5   DF(I1)=0.
      GO TO 3
  6   DF(I1)=(F(I2)-F(I1))/(X(I2)-X(I1))
      DF(I2)=DF(I1)
      GO TO 3
  7   I=I2-1
      N=I1
      L=I1+1
      K=I1+2
  1   H1=X(K)-X(N)
      H2=X(L)-X(N)
      HH=H1*H2*(H1-H2)
      H1=H1*H1
      H2=-H2*H2
      DF(N)=(H2*F(K)-(H2+H1)*F(N)+H1*F(L))/HH
      K=N
      N=L
      L=L+1
      IF(K-I)1,2,3
  2   L=K-1
      GO TO 1
  3   IF(I2-N2)8,13,13
  13  RETURN
      END
c
      SUBROUTINE RAMPF(A,NT,DT,FL1,FL2,FH1,FH2)
C     CMENDOZA (JULY 1995)
C
C     THIS ROUTINE BANDPASS FILTERS AN INPUT RECORD USING SIMPLE RAMPS
C     WITHIN A SPECIFIED FREQUENCY RANGE AS SHOWN BELOW:
C
C		       FL2	       FH1
C			*****************
C		       *		  *
C		      *			    *
C		     *			      *
C		   FL1			      FH2
C
C	A  =  INPUT RECORD ARRAY
C	NT =  NUMBER OF POINTS IN A ARRAY
C	DT =  SAMPLING INTERVAL OF INPUT RECORD (SEC)

      DIMENSION A(1),TEMP(66000)
C   PAD, TAPER, AND TRANSFORM RECORD
      DO 1 J=1,5
      N=10+J
      NN=2**N
 1    IF (NN .GT. NT) GO TO 100
      WRITE(6,650)
 650  FORMAT(1X,'DIMENSION EXCEEDED IN RAMPF...STOP')
      STOP
 100  CONTINUE
      NIN=(NN-NT)/2
      DO 2 J=1,NN
 2    TEMP(J)=0.0
      DO 3 J=1,NT
 3    TEMP(NIN+J)=A(J)
      NB1=NIN-18
      NB2=NIN+18
      NE1=NIN+NT-18
      NE2=NIN+NT+18
      IF (NB1.LT.1) NB1=1
      IF (NE2.GT.NN) NE2=NN
      DO 200 J=NB1,NB2
      XCOS=COS(3.1415927*FLOAT(NB2-J)/(2.*FLOAT(NB2-NB1)))
 200  TEMP(J)=TEMP(J)*XCOS
      DO 250 J=NE1,NE2
      XCOS=COS(3.1415927*FLOAT(J-NE1)/(2.*FLOAT(NE2-NE1)))
 250  TEMP(J)=TEMP(J)*XCOS
      DO 300 J=1,2*NN
 300  A(J)=0.0
      DO 400 J=1,NN
 400  A(J*2-1)=TEMP(J)
      CALL FOUR2(A,NN,1,-1)
C   BANDPASS FILTER USING SIMPLE RAMPS
      DF = 1./(DT*FLOAT(NN))
      F=-DF
      DO 500 J=1,NN,2
      F=F+DF
      IF (F.LE.FL1 .OR. F.GE.FH2) THEN
	A(J)=0.
	A(J+1)=0.
	ENDIF
      IF (F.GT.FL1 .AND. F.LT.FL2) THEN
	RAMP=(F-FL1)/(FL2-FL1)
	A(J)=A(J)*RAMP
	A(J+1)=A(J+1)*RAMP
	ENDIF
      IF (F.GT.FH1 .AND. F.LT.FH2) THEN
	RAMP=(FH2-F)/(FH2-FH1)
	A(J)=A(J)*RAMP
	A(J+1)=A(J+1)*RAMP
	ENDIF
 500  CONTINUE
C   INVERSE TRANSFORM TO FORM TIME SERIES
      DO 600 J=1,NN
      TEMP(J)=A(J)
 600  TEMP(NN+J)=0.0
      DO 700 J=1,NN,2
      JJ=NN+2-J
      A(NN+J)=TEMP(JJ)
 700  A(NN+J+1)=-TEMP(JJ+1)
      CALL FOUR2(A,NN,1,1)
      DO 800 J=1,NN
 800  TEMP(J)=A(J*2-1)
      DO 900 J=1,NT
 900  A(J)=TEMP(NIN+J)     
      RETURN
      END
c
      subroutine four2(dat,nn,idum,isign)
c     the cooley-tookey fast fourier transform in usasi basic fortran
c     transform(j) = sum(dat(i)*w**((i-1)(j-1)), where i and j run
c     from 1 to nn and w = exp(isign*2*pi*sqrt(-1)/nn).  DAT is a one-
c     dimensional complex array (i.e., the real and imaginary parts of
c     data are located immediately adjacent in storage, such as
c     fortran iv places them) whose length nn is a power of two.  isign
c     is +1 or -1, giving the sign of the transform.  transform values
c     are returned in array DAT, replacing the input data.  the time is
c     proportional to n*log2(n), rather than the usual n**2
c     rms resolution error being bounded by 6*sqrt(i)*log2(nn)*i**(-b),
c     where b is the number of bits in the floating point fraction.
c     program automatically divides transform by nn for inverse
c     transform
      dimension dat(*)
      n = 2 * nn
      if(isign.eq.-1) go to 1002
      do 1001 iiii = 1,n
 1001 dat(iiii) = dat(iiii)/nn
 1002 continue
      j = 1
      do 5 i=1,n,2
      if(i-j)1,2,2
    1 tempr = dat(j)
      tempi = dat(j+1)
      dat(j) = dat(i)
      dat(j+1)=dat(i+1)
      dat(i) = tempr
      dat(i+1) = tempi
    2 m = n/2
    3 if(j-m) 5,5,4
    4 j = j-m
      m = m/2
      if(m-2)5,3,3
    5 j=j+m
      mmax = 2
    6 if(mmax-n)7,10,10
    7 istep= 2 *mmax
      theta = 6.283185307/float(isign*mmax)
      sinth=sin(theta/2.)
      wstpr=-2.*sinth*sinth
      wstpi=sin(theta)
      wr=1.0
      wi=0.0
      do 9 m=1,mmax,2
      do 8 i=m,n,istep
      j=i+mmax
      tempr=wr*dat(j)-wi*dat(j+1)
      tempi=wr*dat(j+1)+wi*dat(j)
      dat(j)=dat(i)-tempr
      dat(j+1)=dat(i+1)-tempi
      dat(i)=dat(i)+tempr
    8 dat(i+1) = dat(i+1)+tempi
      tempr = wr
      wr = wr*wstpr-wi*wstpi + wr
    9 wi = wi*wstpr+tempr*wstpi + wi
      mmax = istep
      go to 6
   10 return
      end
