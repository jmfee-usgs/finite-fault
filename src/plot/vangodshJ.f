C     PROGRAM VANGO.BIG
C     THIS ROUTINE PLOTS THE COMPARISON OF AX WITH B ( WHERE  A  IS THE
C     SUBFAULT SYNTHETICS, B  IS THE ARRAY OF OBSERVATIONS AND  X  IS THE
C     ARRAY OF WEIGHTS).  USER SPECIFIES THE NUMBER OF RECORD COMPARISONS
C     TO PLOT IN EACH FRAME.
C
C     Original program written by S.Hartzell at USGS-Pasadena;
C     Modified by C.Mendoza to plot using BUPLOT library. User
C     specifies the number of record comparisons to plot in each frame.
C     This version overlaps observations (solid) and synthetics (dashed).
C
C	Feb 94: modified by C.Mendoza to plot at NIED (Tsukuba)
C		using CALPAK library.
C
      COMMON/ALL/A(2000,2620)
      COMMON/REST/B(2000),X(2620),W(2000),yt(2000)
      DIMENSION SYN(2000),DTREC(200),TC(200),XFUL(200)
      CHARACTER*40 RESP,FILENM
      WRITE(6,620)
 620  FORMAT(1X,'ENTER THE NAME OF THE LISA OUTPUT FILE')
      READ(5,*)FILENM
      WRITE(6,621)
 621  FORMAT(1X,'ENTER THE NUMBER OF OBSERVATION RECORDS')
      READ(5,*)NREC
 100  WRITE(6,*)' IS SCALE (SEC/IN) SAME FOR ALL RECORDS (YES/NO)?'
      READ(5,'(A)') RESP
      IF (RESP .EQ. 'YES' .OR. RESP .EQ. 'yes') THEN
        WRITE(6,*)' ENTER SEC/INCH FOR OBSERVATION RECORDS'
        READ(5,*) TC(1)
        DO 150 I=2,NREC
 150    TC(I)=TC(1)
        GO TO 200
        ENDIF
      WRITE(6,622)
 622  FORMAT(1X,'GIVE SEC/INCH TO BE USED FOR EACH COMPARISON PLOT')
      READ(5,*) (TC(I),I=1,NREC)
 200  CONTINUE
      WRITE(6,*)'GIVE NUMBER OF RECORD PAIRS PER PLOT FILE'
      READ(5,*) NPAIR
      HIGH=12./FLOAT(NPAIR)
      XMOVE=2.*HIGH + 0.1
      XSIZ=0.25*HIGH
      OPEN(UNIT=11,FILE='juliea.dat',STATUS='OLD',ACCESS='SEQUENTIAL',
     +FORM='UNFORMATTED')
      OPEN(UNIT=12,FILE='julieb.dat',STATUS='OLD',ACCESS='SEQUENTIAL',
     +FORM='UNFORMATTED')
      OPEN(UNIT=13,FILE=FILENM,STATUS='OLD')
      WRITE(6,628)
 628  FORMAT(1X,'ENTER THE NUMBER OF SUBFAULTS')
      READ(5,*) NSUBF
      WRITE(6,629)
 629  FORMAT(1X,'ENTER THE NUMBER OF DIFF. MECHANISMS PER SUBFAULT')
      READ(5,*) NMECH
      WRITE(6,630)
 630  FORMAT(1X,'HOW MANY TIME WINDOWS ARE THERE')
      READ(5,*) JW
      NN=NSUBF*NMECH*JW
      WRITE(6,631)
 631  FORMAT(1X,'DO YOU WANT OBSERVATIONS AND SYNTHETICS PLOTTED',/,
     +1X,'ON THE SAME SCALE (1=YES, 0=NO)')
      READ(5,*) IMTCH
      ASF = 1.0
      IF(IMTCH .EQ. 0) THEN
	WRITE(6,*)'ENTER AMPLITUDE SCALE FACTOR FOR PLOTS'
	READ(5,*) ASF
	GO TO 20
	ENDIF
      WRITE(6,632)
 632  FORMAT(1X,'HOW MANY RECORDS DO YOU WANT PLOTTED ON THE',/,
     +1X,'SAME SCALE')
      READ(5,*) NPSS
      WRITE(6,633)
 633  FORMAT(1X,'ENTER FULL SCALE AMPLITUDE FOR EACH RECORD')
      READ(5,*) (XFUL(I),I=1,NPSS)
      WRITE(6,634)
 634  FORMAT(1X,'ENTER MOMENT SCALING FACTOR FOR SYNTHETICS')
      READ(5,*) SCM
  20  DO 7 I=1,5
   7  READ(13,8) SPACE
      READ(13,10) (X(I),I=1,NN)
   8  FORMAT(1A2)
  10  FORMAT(1X,6E13.5)
      CLOSE(13)
	  sumrat=0.
	  NMOD=MOD(NREC,NPAIR)
      IFILE=INT(NREC/NPAIR)
      IF (NMOD.GT.0) IFILE=IFILE+1
      NLOOP=NPAIR
	  DO 2 ILP=1,IFILE
      if (ilp.lt.10) ic1=0
      if (ilp.ge.10) ic1=1
      if (ilp.ge.10) ic2=ilp-10
      if (ilp.lt.10) ic2=ilp
      if (ilp.ge.20) ic1=2
      if (ilp.ge.20) ic2=ilp-20
      write(filenm,500) ic1,ic2
      call opnpak(filenm)
      CALL PLOT(2.,25.,-3)
      IF (ILP.EQ.IFILE .and. NMOD.NE.0) NLOOP=NMOD
      DO 3 NLP=1,NLOOP
      IREC=NLP+(NPAIR*(ILP-1))
      READ(11) NT
      DO 4 K=1,NN
      READ(11) (SYN(IP),IP=1,NT)
      DO 444 I=1,NT
 444  A(I,K)=SYN(I)
   4  CONTINUE
      READ(12) NT,DTREC(IREC)
      READ(12) (B(IP),IP=1,NT)
      DO 12 L=1,NT
      Q=0.
      DO 11 K=1,NN
  11  Q=Q+A(L,K)*X(K)
  12  W(L)=Q
      YDT=DTREC(IREC)/TC(IREC)
      A1=0.
      A2=0.
      DO 16 L=1,NT
      IF(ABS(B(L)) .GT. A1) A1=ABS(B(L))
  16  IF(ABS(W(L)) .GT. A2) A2=ABS(W(L))
      H1=HIGH/A1
      H2=HIGH/A2
      IF(IMTCH .EQ. 0) GO TO 24
      IF(IREC .GT. NPSS) GO TO 24
      DO 23 L=1,NT
  23  W(L)=W(L)*SCM
      A2=A2*SCM
      H1=HIGH/XFUL(IREC)
      H2=H1
  24  DO 17 L=1,NT
      B(L)=B(L)*H1
  17  W(L)=W(L)*H2
      Y=0.
      CALL PLOT(Y,B(1),3)
      DO 18 L=1,NT
      CALL PLOT(Y,B(L),2)
      yt(l)=y
  18  Y=Y+YDT
      call pltline(yt,w,nt,-1.)
      ratio=(A2/A1)*ASF
	  sumrat=sumrat+ratio
      ymx=yt(nt)
  26  CALL NUMBER(ymx,0.,xsiz,ratio,0.,52)
  22  Y=0.
      CALL PLOT(Y,-XMOVE,-3)
   3  CONTINUE
      call clspak
   2  CONTINUE
      aasf=nrec/sumrat
	  write(6,*)' AVG AMP SCALE FACTOR:',aasf
 500  format('vango',2i1,'.ps')
      CLOSE(11)
      CLOSE(12)
      STOP
      END
CC
CC
c       draw solid or dashed line  wds 9/87
      subroutine pltline(x, y, np, u)
      dimension x(1), y(1), xt(5000), yt(5000)
c
c ++    smooth line
      parameter (dash = 0.05)
      nnp = np - 1
      do 80 i = 2, nnp
      xt(i) = ((.2 * x(i - 1)) + (.6 * x(i))) + (.2 * x(i + 1))
      yt(i) = ((.2 * y(i - 1)) + (.6 * y(i))) + (.2 * y(i + 1))
c
   80 continue
      do 82 i = 2, nnp
      x(i) = xt(i)
      y(i) = yt(i)
c
c ++
c       solid line if u >= 0.
   82 continue
      if (u .lt. 0.) goto 20
c pen up                          
      call plot(x(1), y(1), 3)
      do 10 n = 2, np
c dwn                             
      call plot(x(n), y(n), 2)
   10 continue
c
c       dashed line if u < 0., uniform around corners
      return 
c -1 start gap   +1 start dash    
   20 idsh = -1
      n = 1
c gap or dash length left to draw 
      drw = dash
      xp = x(1)
      yp = y(1)
      ipen = 3
c
c up                              
      call plot(xp, yp, ipen)
c current seg                     
   30 n = n + 1
      if (n .gt. np) return 
      dx = x(n) - x(n - 1)
      dy = y(n) - y(n - 1)
      seglen = sqrt((dx * dx) + (dy * dy))
c ++ evade bug in subr procs      
      if (seglen .eq. 0.) goto 30
c
c       draw rest of last or entire new gap or dash on this seg
c length left on this seg         
      slft = seglen
   40 if (drw .gt. slft) goto 50
      xp = xp + ((drw * dx) / seglen)
      yp = yp + ((drw * dy) / seglen)
      call plot(xp, yp, ipen)
      idsh = - (1 * idsh)
      ipen = 2
c 2 dwn, 3 up                     
      if (idsh .eq. (-1)) ipen = 3
      slft = slft - drw
      drw = dash
      if (slft .eq. 0.) goto 30
c
c       draw gap or dash to end of this seg, cont on next
      goto 40
   50 xp = x(n)
      yp = y(n)
      call plot(xp, yp, ipen)
      drw = drw - slft
      goto 30
c
c ----------------------------------------------------------------------
c
      end
c
c
	subroutine opnpak(filenm)
c
c	initiate plotting w/CALPAK library
c	cmendoza 1/94
c
	character*32 filenm
	open(8,file=filenm)
  	call hplots(1,1,8,0)
	return
	end
c
c
	subroutine clspak
c	cmendoza 1/94
c
c	terminate plotting w/CALPAK library
c
  	call hplots(0,0,8,0)
	close(8)
	return
	end

