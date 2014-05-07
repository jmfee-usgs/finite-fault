C
C                    ROUTINE SYNPLT
C	PLOTS CADILLAC, SEISRESP, TELMOD SYNTHETICS 
C	AND/OR TELMOD AND MBIN OBSERVED DATA RECORDS
C			C.Mendoza
C
C   OPTIONS:  
C     1) PLOT SUBFAULT SYNTHETICS FOR A SPECIFIED STATION
C     2) PLOT SYNTHETICS AT ALL STATIONS FOR A SPECIFIED SUBFAULT
C     3) PLOT OBSERVED DATA (BINARY MBIN FORMAT) AND SYNTHETICS
C	 AT ALL STATIONS FOR A SPECIFIED SUBFAULT
C     4) PLOT OBSERVED DATA RECORDS (TELMOD FORMAT) ONLY FOR ALL STATIONS
C
c	This version uses CALPAK library (CM/Jan94)	
c	TO COMPILE: f77 synplt.f calpak.f laspac.f -o synplt
c
      COMMON/DRAW/SZ(50000)
      real syn(50000),obs(50000),tt(50000)
      integer code(4),chn(4)
      character*40 filenm
      write(6,*)' ENTER OPTION:'
      write(6,*)'     =1, PLOT SYNTHETICS FOR A SPECIFIED STATION'
      write(6,*)'     =2, PLOT SYNTHETICS FOR A SPECIFIED SUBFAULT'
      write(6,*)'     =3, PLOT SUBFAULT SYNTHETICS AND OBSERVED DATA'
      write(6,*)'         (OBSERVED RECORDS IN MBIN BINARY FORMAT)'
      write(6,*)'     =4, PLOT OBSERVED DATA ONLY (TELMOD FORMAT)'
      read (5,*) iplt
      if (iplt .eq. 4) then
	write(6,*)' ENTER NAME OF TELMOD DATA FILE:'
	read(5,'(a)') filenm
	OPEN(UNIT=7,FILE=filenm,STATUS='OLD',ACCESS='SEQUENTIAL',
     +	FORM='UNFORMATTED')
	nsubf = 1
	go to 10
	endif
      write(6,*)' ENTER NAME OF SYNTHETICS FILE:'
      read(5,'(a)') filenm
      OPEN(UNIT=7,FILE=filenm,STATUS='OLD',ACCESS='SEQUENTIAL',
     +FORM='UNFORMATTED')
      if (iplt .eq. 3) then
        write(6,*)' ENTER OBSERVED BINARY DATA FILE (from MSTART):'
        read(5,'(a)') filenm
        open(unit=11,file=filenm,status='old',access='sequential',
     +  form='unformatted')
        endif
  10  write(6,*)' ENTER NUM OF TRACES TO PLOT PER PLOT FILE'
      read (5,*) ntpf
      xhigh = 14./float(ntpf+1)
      write(6,*)' PLOT HEIGHT (IN) =',xhigh
      write(6,*)
      write(6,*)' ENTER HORIZONTAL SCALE (SEC/INCH)'
      read (5,*) tscale
      top = 27. - xhigh
      xmove = (-2.*xhigh)-0.1
      if (iplt .eq. 4) go to 15
      WRITE(6,*)' HOW MANY SUBFAULTS ARE THERE (TOTAL)'
      READ(5,*) NSUBF
      if (iplt .eq. 1) write(6,*)' ENTER STATION NUMBER TO PLOT:'
      if (iplt .ne. 1) write(6,*)' ENTER SUBFAULT NUMBER TO PLOT:'
      read (5,*) NUM
  15  READ(7) NSTA
      if (iplt .eq. 3) then
	read(11) ista
	if (ista .ne. nsta) then
	  write(6,*)'  ** Number of Stations do not MATCH **'
	  stop
	  endif
	write(6,*)' Same start time and time interval for all records?'
	write(6,*)' (1=yes,0=no)'
	read(5,*) itime
	if (itime .eq. 1) then
	  write(6,*)' Enter start time and time interval'
	  read(5,*) trec,tlen
	  endif
	endif
      if (iplt .eq. 1) then
	nmod=mod(nsubf,ntpf)
	nf=int(nsubf/ntpf)+1
	endif
      if (iplt .gt. 1) then
	nmod=mod(nsta,ntpf)
	nf=int(nsta/ntpf)+1
	endif
      if (nmod.eq.0) nf=nf-1
      ntr=0
      nfc=0
      DO 500 IST=1,NSTA
      if (iplt .gt. 1) then
	ntr=ntr+1
        if (ntr .eq. 1) then
		nfc=nfc+1
        	if (nfc.lt.10) ic1=0
        	if (nfc.ge.10) ic1=1
        	if (nfc.ge.10) ic2=nfc-10
        	if (nfc.lt.10) ic2=nfc
        	if (nfc.ge.20) ic1=2
		if (nfc.ge.20) ic2=nfc-20
		write(filenm,100) ic1,ic2
		call opnpak(filenm)
		call plot(3.,top,-3)
		endif
	endif
      DO 400 ISUBF=1,NSUBF
      READ(7) NT,DT
      READ(7) (SYN(I),I=1,NT)
      if (iplt.eq.1 .and. ist.eq.num) then
        ntr=ntr+1
        if (ntr .eq. 1) then
		nfc=nfc+1
        	if (nfc.lt.10) ic1=0
        	if (nfc.ge.10) ic1=1
        	if (nfc.ge.10) ic2=nfc-10
        	if (nfc.lt.10) ic2=nfc
        	if (nfc.ge.20) ic1=2
        	if (nfc.ge.20) ic2=nfc-20
		write(filenm,100) ic1,ic2
		call opnpak(filenm)
		call plot(3.,top,-3)
		endif
        do 20 i=1,nt
  20    sz(i)=syn(i)
        CALL PICASO(NT,DT,XHIGH,XMOVE,TSCALE)
c	if (isubf.lt.nsubf .and. ntr.eq.ntpf) then
	if (ntr .eq. ntpf) then
		call clspak
		ntr=0
		endif
        endif
      if (iplt.eq.2 .and. isubf.eq.num) then
        do 30 i=1,nt
  30    sz(i)=syn(i)
        CALL PICASO(NT,DT,XHIGH,XMOVE,TSCALE)
        endif
      if (iplt .eq. 3 .and. isubf .eq. num) then
        read(11) (code(i),i=1,4),(chn(i),i=1,4)
        read(11) nn,dtt,tstart
        read(11) (obs(i),i=1,nn)
        write(6,'(/,2(1x,4a1))') code,chn
	if (itime .eq. 0) then
          write(6,*)'  Observed Record Sampling Interval (sec):',dtt
          write(6,*)'  Enter the start time (sec) w.r.t. the beginning'
          write(6,*)'  and time interval (sec) desired for this record'
          read(5,*) trec,tlen
	  endif
        ns=int(trec/dtt)
	np=int(tlen/dtt)
        write(6,*)'  Start Time:',dtt*float(ns),' SEC'
        write(6,*)'  Time Window:',dtt*float(np),' SEC'
c        np=nn-ns
        do 40 i=1,np
  40    sz(i)=obs(ns+i)
        write(6,*)'PICASO: plot observed record'
        call picaso(np,dtt,xhigh,xmove,tscale)
	call plot(0.,-xmove,-3)
c        call plot(0.,-3.,-3)
c        do 50 i=1,nt
c  50    sz(i)=syn(i)
c        call picaso(nt,dt,xhigh,xmove,tscale)
	amx=0.
        do 50 i=1,nt
  50	if (abs(syn(i)) .gt. amx) amx=abs(syn(i))
	y=0.
	ydt=dt/tscale
	do 60 i=1,nt
	syn(i)=syn(i)*xhigh/amx
	tt(i)=y
  60	y=y+ydt
	yplt=y/2.
        write(6,*)'PLTLINE: plot synthetic'
	call pltline(tt,syn,nt,-1.)
	write(6,'(1x,e14.7)') amx
	nform=155
	if (amp.lt.1.) nform=109
	call number(yplt,0.,.2,amx,0.,nform)
	call plot(0.,xmove,-3)
        endif
      if (iplt.eq.4) then
        do 70 i=1,nt
  70    sz(i)=syn(i)
        CALL PICASO(NT,DT,XHIGH,XMOVE,TSCALE)
        endif
 400  CONTINUE
c      if (iplt.ne.1 .and. ist.lt.nsta .and. ntr.eq.ntpf) then
      if (iplt.gt.1 .and. ntr.eq.ntpf) then
		call clspak
		ntr=0
		endif
 500  CONTINUE
      CLOSE(7)
      if (iplt .eq. 3) close(11)
c      call endplt
      if (nmod .gt. 0) call clspak
 100  format('plt',2i1,'.ps')
      STOP
      END
      SUBROUTINE PICASO(NT,DT,HEI,XMOVE,TSCAL)
      COMMON/DRAW/SZ(50000)
      AMP=0.
      NS=1
      DO 2 I=NS,NT
  2   IF(ABS(SZ(I)) .GT. AMP) AMP=ABS(SZ(I))
      nform=155
      if (amp.lt.1.) nform=109
      ZP=HEI/AMP
      X1=SZ(NS)*ZP
      Y1=0.
      CALL PLOT(Y1,X1,3)
      DO 3 I=NS,NT
      X1=SZ(I)*ZP
      CALL PLOT(Y1,X1,2)
  3   Y1=Y1 + (DT/TSCAL)
      WRITE(6,5) AMP
  5   FORMAT(1X,E14.7)
      CALL NUMBER(-1.,-1.,.2,AMP,0.,nform)
      CALL PLOT(0.,XMOVE,-3)
      RETURN
      END
c
      subroutine pltline(x, y, np, u)
      dimension x(1), y(1), xt(50000), yt(50000)
c
c       draw solid or dashed line  wds 9/87
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

