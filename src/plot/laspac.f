c     LASPAC
c        Low level plotting routines
c           to support Postcript output
c           using plotpak calls
c-------------------------------------------------------------------
c     Original version  (Sep.   , 1988)
c     Revised by mb     (Apr.  3, 1989)
c     Revised by K2     (Mar. 21, 1990)
c     Revised by S.Hori (Jan.  7, 1991)
c-------------------------------------------------------------------
c
      subroutine NWPAGE(IRO,LPL,ILS)
c
c *** Created by S.Hori ***
c
c     Refreshing page : if ILS=0 - mapped from A4 paper
c                       if ILS=1 - mapped from A3 paper
c
c     Coordinates & magnification are reset
c
      common/P00000/LPLOT,IROT,IL34,A,B,C,D,ASP,THET
      common/p00001/xorig,yorig
      common/L00000/PSCA,xo,yo
c
      A=1.0
      B=0.0
      C=1.0
      D=0.0
      ASP=0.6666
      IL34=ILS
      LPLOT=LPL
      IROT=IRO
c
      if(IROT.eq.1.and.IL34.eq.0) then
      xorig=771.0237
      elseif(IROT.eq.1.and.IL34.eq.1) then
      xorig=545.1960
      else
      xorig=0.
      endif
c
      yorig=0.
c
c     Postscript re-initialisation
c
      write(LPLOT,*) 'stroke'
      write(LPLOT,*) 'showpage'
c
      write(LPLOT,*) 'initmatrix'
      write(LPLOT,*) '/pM {stroke newpath moveto} def'
      write(LPLOT,*) '/pL {lineto} def'
      write(LPLOT,*) '/rM {rmoveto} def'
      write(LPLOT,*) '/rL {rlineto} def'
      write(LPLOT,*) '2 setlinejoin'
      write(LPLOT,*) '/pR {/Palatino-Roman findfont '
      write(LPLOT,*) ' exch scalefont setfont} def'
      write(LPLOT,*) '/pI {/Palatino-Italic findfont '
      write(LPLOT,*) ' exch scalefont setfont} def'
      write(LPLOT,*) '/pB {/Palatino-Bold findfont '
      write(LPLOT,*) ' exch scalefont setfont} def'
      write(LPLOT,*) '/pBI {/Palatino-BoldItalic findfont '
      write(LPLOT,*) ' exch scalefont setfont} def'
      write(LPLOT,*) '/hV {/Helvetica-Bold findfont '
      write(LPLOT,*) ' exch scalefont setfont} def'
      write(LPLOT,*) '590 5 translate '
      write(LPLOT,*) '90 rotate '
      write(LPLOT,*) 'newpath '
c
      if(IL34.eq.0) then
        PSCA=72.0/2.54
      elseif(IL34.eq.1) then
        PSCA=72.0/(sqrt(2.0)*2.54)
      elseif(IL34.eq.2) then
c
c     Initialize plotter to allow convenient screen mapping
c       (1cm=20points)
c
        PSCA=20.0
c
      endif
c
c     Select pen #1
c
      call pen(1,0)
c
      return
c
c *************************
c
      end
c
      subroutine ASPECT(RASP)
c
c     Setting width to height ratio for characters to rasp
c
      common/P00000/LPLOT,IROT,IL34,A,B,C,D,ASP,THET
      common/L00000/PSCA,xo,yo
c
      ASP=RASP
      return
      end
c
      subroutine CIRCLE(RADIUS,NSIDES)
c
c     Drawing circle centred at current pen location, with
c        circumference divided into NSIDES straight segments
c
      common/P00000/LPLOT,IROT,IL34,A,B,C,D,ASP,THET
      common/L00000/PSCA,xo,yo
c
      cx=xo
      cy=yo
      nsid=NSIDES
      if(nsid.EQ.0) nsid=72
      rpa=radius
      ANG=6.283185308/float(nsid)
      xv=rpa+cx
      yv=cy
      call plot(xv,yv,3)
      sta=0.
      do 30 i=1,nsid
        sta=sta+ang
        xv=rpa*cos(sta)+cx
        yv=rpa*sin(sta)+cy
        call plot(xv,yv,2)
 30   continue
      xo=cx
      yo=cy
      return
      end
c
      subroutine CSYMBL(X,Y,IP,SIZE,INT)
c
c     Writing a centered symbol at location (X,Y). The symbol is
c        is selected from the list below by INT for 1<INT<10
c        and is circle,triangle,square,pentagon,hexagon,heptagon,
c        octagon for 11<INT<17
c
      common/P00000/LPLOT,IROT,IL34,A,B,C,D,ASP,THET
      common/L00000/PSCA,xo,yo
c
      character*1 ISYM
      dimension ISYM(10)
      dimension ICIR(10)
      data ISYM/'O','X','*','+','#','$','@','8','H','Z'/
      data ICIR/20,3,4,5,6,7,8,9,10,11/
c
      if(INT.ge.11) go to 20
c
c     Select character size
c
      call plotu(x,y,ip)
      call symbol(x-0.5*size,y-0.5*size,size,isym(int),0.0,1)
      return
c
c     Move pen to symbol location, symbol is written after move
c
   20 call PLOTU(X,Y,IP)
      call CIRCLE(SIZE*0.75,ICIR(INT-10))
      return
      end
c
      subroutine DASHLN(LDASH,LPAT)
c
c     Defining the style for line drawing
c      ldash < 0   -  reset to solid line C         or = 12
c
c      ldash = 0   -  dots at calling points
c            = 1   -  dots
c            = 2   -  half dash
c            = 3   -  long dash
c            = 4   -  chain dotted
c            = 5   -  long and short
c            = 6   -  long and two short
c            = 7   -  long dash with short space
c
c       lpat - percentage of diagonal of paper used for
c              a pattern
c              if (lpat.eq.0 ) lpat = 2
c
      common/P00000/LPLOT,IROT,IL34,A,B,C,D,ASP,THET
      common/p00001/xorig,yorig
      common/L00000/PSCA,xo,yo
c
      integer*4 ldash,lpat
      write(LPLOT,*) ' stroke' 
      if(ldash.lt.0)  write(LPLOT,*) '[] 0 setdash'
      if(ldash.eq.12) write(LPLOT,*) '[] 0 setdash'
c
      if(ldash.eq.0) write(LPLOT,*) '[2 8] 0 setdash'
      if(ldash.eq.1) write(LPLOT,*) '[2 8] 0 setdash'
      if(ldash.eq.2) write(LPLOT,*) '[4 4] 0 setdash'
      if(ldash.eq.3) write(LPLOT,*) '[8 8] 0 setdash'
      if(ldash.eq.4) write(LPLOT,*) '[6 2 2 2] 0 setdash'
      if(ldash.eq.5) write(LPLOT,*) '[8 4 4 4] 0 setdash'
      if(ldash.eq.6) write(LPLOT,*) '[6 4 4 4 4 4] 0 setdash'
      if(ldash.eq.7) write(LPLOT,*) '[6 2] 0 setdash'
c
c *** Modified by (K2) ***
c
      xv=psca*xo+xorig
      yv=psca*yo+yorig
c
c ************************
c
      write(LPLOT,fmt='(2f9.3,a)') xv,yv,' pM'
c
      return
      end
c
      subroutine NUMBER(X,Y,SIZE,RN,ANGL,NSF)
c
c     Writing a number on the plot: if NSF=klm, format is Fkl.m
c        if NSF=-lm, RN is fixed to an integer and format is Ilm.
c
      common/P00000/LPLOT,IROT,IL34,A,B,C,D,ASP,THET
      common/L00000/PSCA,xo,yo
c
      character*8 IFORM
      character*40 IWORD
c
c     Create the format expression in IFORM
c
      if(NSF.lt.0) go to 20
      ITOT=NSF/10
      IDPL=MOD(NSF,10)
      write(IFORM,55) ITOT,IDPL
   55 format('(F',I2,'.',I1,')')
      write(IWORD,IFORM) RN
      go to 30
c
c     For integer format
c
   20 ITOT=-NSF
      write(IFORM,65) ITOT
   65 format('(I',I2,')   ')
      IR=IFIX(RN)
      write(IWORD,IFORM) IR
c
c     Encode number and send to plotter
c
   30 call SYMBOL(X,Y,SIZE,IWORD,ANGL,ITOT)
c
      return
      end
c
      subroutine xNUMBER(X,Y,SIZE,RN,ANGL,NSF,ifont)
c
c     Modified by (K2)
c
c     Writing a number on the plot: if NSF=klm, format is Fkl.m
c        if NSF=-lm, RN is fixed to an integer and format is Ilm.
c
      common/P00000/LPLOT,IROT,IL34,A,B,C,D,ASP,THET
      common/L00000/PSCA,xo,yo
c
      character*8 IFORM
      character*40 IWORD
c
c     Create the format expression in IFORM
c
      if(NSF.lt.0) go to 20
      ITOT=NSF/10
      IDPL=MOD(NSF,10)
      write(IFORM,55) ITOT,IDPL
   55 format('(F',I2,'.',I1,')')
      write(IWORD,IFORM) RN
      go to 30
c
c     For integer format
c
   20 ITOT=-NSF
      write(IFORM,65) ITOT
   65 format('(I',I2,')   ')
      IR=IFIX(RN)
      write(IWORD,IFORM) IR
c
c     Encode number and send to plotter
c
   30 call xSYMBOL(X,Y,SIZE,IWORD,ANGL,ITOT,ifont)
c
      return
      end
c
      subroutine PEN(IPEN,IVEL)
c
c     Allowing user to change pen, plotting velocity of pen
c     Pens are coded in colours of gray
c     Pen 1 is double width
c
      common/P00000/LPLOT,IROT,IL34,A,B,C,D,ASP,THET
      common/p00001/xorig,yorig
      common/L00000/PSCA,xo,yo
c
c *** Modified by (K2) ***
c
c     ipen=g*10+w
c         w : line width / 0.2
c         g : gray scale
      if(ipen .lt. 0)  return
      write(LPLOT,*) ' stroke '
      iwidth=mod(ipen,10)
      igray=ipen/10
      width=iwidth*0.2+0.1
      if(il34.ge.1) width=width*0.667
      if(igray.eq.0) gray=0.
      if(igray.eq.1) gray=0.2
      if(igray.eq.2) gray=0.4
      if(igray.eq.3) gray=0.6
      if(igray.eq.4) gray=0.75
      if(igray.ge.5) gray=0.8
      write(LPLOT,71) width, ' setlinewidth', gray, ' setgray'
71    format(1x,f5.2,a,f5.2,a)
      xv=psca*xo+xorig
      yv=psca*yo+yorig
c
c ************************
c
      write(LPLOT,fmt='(2f9.3,a)') xv,yv,' pM'
C
      return
      end
c
      subroutine xPLOT(X,Y,I)
c
c     Raising (I=3) or lowers (I=2) pen and moves to coordinates
c        (X,Y) if I>0 or to current position plus (X,Y) if I<0
c
      common/P00000/LPLOT,IROT,IL34,A,B,C,D,ASP,THET
      common/p00001/xorig,yorig
      common/L00000/PSCA,xo,yo
c
      data IUP/1/
c
      II=iabs(I)
c
c     Rotate plot by 90 degrees if necessary
c
      if(IROT.eq.0) then
        xv=PSCA*x+xorig
        yv=PSCA*y+yorig
      else
	xv=-PSCA*y+xorig
	yv=PSCA*x+yorig
      endif
c
c     Plot
c
      if(I.eq.2)  write(LPLOT,fmt='(2f9.3,a)') xv,yv,' pL'
      if(I.eq.3)  write(LPLOT,fmt='(2f9.3,a)') xv,yv,' pM'
      if(I.eq.-2) write(LPLOT,fmt='(2f9.3,a)') xv,yv,' rL'
      if(I.eq.-3) write(LPLOT,fmt='(2f9.3,a)') xv,yv,' rM'
c 
c     if(I.gt.0) then
      xo=x   
      yo=y
c     endif
c 
      return
      end
c
       subroutine ORIGIN(x,y,iorig)
c
c *** Modified by S.Hori ***
c
      common/P00000/LPLOT,IROT,IL34,A,B,C,D,ASP,THET
      common/p00001/xorig,yorig
      common/L00000/PSCA,xo,yo
c
      data zero/1.e-16/
c
	xx=x
	yy=y
c
      if(irot.eq.0) then
        if(iorig.eq.0) then
          xorig=xx*psca
          yorig=yy*psca
        elseif(iorig.gt.0) then
          xorig=xorig+xx*psca
          yorig=yorig+yy*psca
        elseif(iorig.lt.0) then
          if(abs(psca).lt.zero) stop 'ORIGIN error: zero scale'
          x=xorig/psca
          y=yorig/psca
        endif
      elseif(il34.eq.0) then
	if(iorig.eq.0) then
	  xorig=771.0237-yy*psca
	  yorig=xx*psca
        elseif(iorig.gt.0) then
	  xorig=xorig-yy*psca
	  yorig=yorig+xx*psca
        elseif(iorig.lt.0) then
          if(abs(psca).lt.zero) stop 'ORIGIN error: zero scale'
          x=(771.0237-yorig)/psca
          y=xorig/psca
        endif
      elseif(il34.eq.1) then
	if(iorig.eq.0) then
	  xorig=545.1960-yy*psca
	  yorig=xx*psca
        elseif(iorig.gt.0) then
	  xorig=xorig-yy*psca
	  yorig=yorig+xx*psca
        elseif(iorig.lt.0) then
          if(abs(psca).lt.zero) stop 'ORIGIN error: zero scale'
          x=(545.1960-yorig)/psca
          y=xorig/psca
        endif
      else
	if(iorig.eq.0) then
	  xorig=-yy*psca
	  yorig=xx*psca
        elseif(iorig.gt.0) then
	  xorig=xorig-yy*psca
	  yorig=yorig+xx*psca
        elseif(iorig.lt.0) then
          if(abs(psca).lt.zero) stop 'ORIGIN error: zero scale'
          x=-yorig/psca
          y=xorig/psca
        endif
      endif
c
      return
      end
c
c
      subroutine WHERE(x,y,rfact)
c
c     Returning current cursor location in cm
c        and the current plot sizing factor 
c
      common/p00001/xorig,yorig
      common/L00000/PSCA,xo,yo
c
c     integer*2 ix,iy
c
      x=xo
      y=yo
      rfact=-1.
      call factor(rfact)
      return
      end
c
c
      subroutine FACTOR(fact)
c
c     If fact>0  the plot scale is changed to the original
c                scale multiplied by 'fact'
c     If fact<=0 the latest factor is returned
c
      common/p00001/xorig,yorig
      common/L00000/PSCA,xo,yo
c
      logical first
      data first/.true./,factl/1./
c
      if(first) then 
         osca=psca
         first=.false.
      endif
      if(fact.gt.0) then
         psca=osca*fact
         factl=fact
      else
         fact=factl
      endif
      return
      end
c

      subroutine HPLOTS(ION,IRO,LPL,ILS)
c
c     Initializing plotter : if ILS=0 - mapped from A4 paper
c                            if ILS=1 - mapped from A3 paper
c     Establishing handshaking characteristics (ION=1).
c     Terminating plot file if ION<>1
c
      common/P00000/LPLOT,IROT,IL34,A,B,C,D,ASP,THET
      common/p00001/xorig,yorig
      common/L00000/PSCA,xo,yo
c
      if(ION.eq.0) go to 80
c
      A=1.0
      B=0.0
      C=1.0
      D=0.0
      ASP=0.6666
      IL34=ILS
      LPLOT=LPL
      IROT=IRO
c
c *** Modified by S.Hori ***
c
      if(IROT.eq.1.and.IL34.eq.0) then
      xorig=771.0237
      elseif(IROT.eq.1.and.IL34.eq.1) then
      xorig=545.1960
      else
      xorig=0.
      endif
c
c **************************
c
      yorig=0.
c
c     Postscript initialisation
c
      write(LPLOT,'(a2)') '%!'
      write(LPLOT,*) 'initmatrix'
      write(LPLOT,*) '/pM {stroke newpath moveto} def'
      write(LPLOT,*) '/pL {lineto} def'
      write(LPLOT,*) '/rM {rmoveto} def'
      write(LPLOT,*) '/rL {rlineto} def'
      write(LPLOT,*) '2 setlinejoin'
      write(LPLOT,*) '/pR {/Palatino-Roman findfont '
      write(LPLOT,*) ' exch scalefont setfont} def'
      write(LPLOT,*) '/pI {/Palatino-Italic findfont '
      write(LPLOT,*) ' exch scalefont setfont} def'
      write(LPLOT,*) '/pB {/Palatino-Bold findfont '
      write(LPLOT,*) ' exch scalefont setfont} def'
      write(LPLOT,*) '/pBI {/Palatino-BoldItalic findfont '
      write(LPLOT,*) ' exch scalefont setfont} def'
      write(LPLOT,*) '/hV {/Helvetica-Bold findfont '
      write(LPLOT,*) ' exch scalefont setfont} def'
      write(LPLOT,*) '590 5 translate '
      write(LPLOT,*) '90 rotate '
      write(LPLOT,*) 'newpath '
c
      if(IL34.eq.0) then
        PSCA=72.0/2.54
      elseif(IL34.eq.1) then
        PSCA=72.0/(sqrt(2.0)*2.54)
      elseif(IL34.eq.2) then
c
c     Initialize plotter to allow convenient screen mapping
c       (1cm=20points)
c
        PSCA=20.0
c
      endif
c
c     Select pen #1
c
      call pen(1,0)
c
      return
c
c     Postscript close
c
 80   continue
      write(LPLOT,*) 'stroke'
      write(LPLOT,*) 'showpage'
c
c *** Modified by S.Hori ***
c
c     write(LPLOT,*) 'quit'
c
c **************************
c
      close(LPLOT)
c
      return
      end
c
      subroutine PLOTU(X,Y,II)
c
c     Scaling user coordinates to plotter coordinates
c
      common/P00000/LPLOT,IROT,IL34,A,B,C,D,ASP,THET
      common/L00000/PSCA,xo,yo
c
      XP=A*X
      YP=C*Y
      if(II.lt.0) go to 10
      XP=XP+B
      YP=YP+D
   10 call PLOT(XP,YP,II)
c
      return
      end
c
      subroutine xSCALE(XMIN,XMAX,PX1,PX2,YMIN,YMAX,PY1,PY2)
c
c     Setting up scale factors used in PLOTU and other routines
c
      common/P00000/LPLOT,IROT,IL34,A,B,C,D,ASP,THET
      common/L00000/PSCA,xo,yo
      common/p00002/a1,a2,b1,b2,c1,c2,d1,d2
c
      A=(PX2-PX1)/(XMAX-XMIN)
      B=PX1-A*XMIN
      C=(PY2-PY1)/(YMAX-YMIN)
      D=PY1-C*YMIN
c
      a1=xmin
      a2=xmax
      b1=px1
      b2=px2
      c1=ymin
      c2=ymax
      d1=py1
      d2=py2
c
      return
      end
c
      subroutine xSYMBOL(X,Y,SIZE,IWORD,ANGL,NCHAR,ifont)
c
c     Writing a Hollerith string on the plot--plotter unit
c        ifont=1(Palatino Roman), 2(Bold), 3(Italic), 4(BoldItalic)
c
      common/P00000/LPLOT,IROT,IL34,A,B,C,D,ASP,THET
      common/L00000/PSCA,xo,yo
c
      character*80 IWORD
      character*80 CWORD
c
      nch=nchar
      if(NCHAR.gt.80) NCH=80
c
c     Select character orientation
c
      ab=0.0
      if(irot.ne.0) ab=90.0
c
c     Select character size
c
   40 SZ=abs(SIZE)*PSCA*1.5
c
      do 50 k=1,80
        cword(k:k)=iword(k:k)
   50 continue
c
      do 51 k=nch+1,80
        cword(k:k)=' '
   51 continue
c
c     Move pen to symbol location
c
      IP=3
      if(SIZE.lt.0.0) IP=-3
      call plot(X,Y,IP)
      ang=angl+ab
      write(LPLOT,fmt='(f9.3,a)') ang,' rotate'
c
c     Write character string
c
      if(ifont.eq.1) then
         write(LPLOT,fmt='(f9.3,x,a)') sz,' pR'
      elseif(ifont.eq.2) then
         write(LPLOT,fmt='(f9.3,x,a)') sz,' pB'
      elseif(ifont.eq.3) then
         write(LPLOT,fmt='(f9.3,x,a)') sz,' pI'
      elseif(ifont.eq.4) then
         write(LPLOT,fmt='(f9.3,x,a)') sz,' pBI'
      else
         write(LPLOT,fmt='(f9.3,x,a)') sz,' hV'
      endif
      write(LPLOT,fmt='(x,a,a,a,/,a)') '(',cword,')',' show'
c
c     Reset character orientation if necessary
c
      bng=-ang 
      write(LPLOT,fmt='(f9.3,a)') bng,' rotate'
10    return
      end
c
      subroutine SYMBU(X,Y,SIZE,IWORD,ANGL,NCHAR)
c
c     Writingt a Hollerith string on the plot--user units
c
      common/P00000/LPLOT,IROT,IL34,A,B,C,D,ASP,THET
      common/L00000/PSCA,xo,yo
c
      character*80 IWORD
      character*80 CWORD
c
      nch=nchar
      if(NCHAR.gt.80) NCH=80
c
c     Select character orientation
c
      if(ANGL.eq.0.0) GO TO 40
c
c     Select character size
c
   40 SZ=abs(SIZE)*PSCA*1.5
c
      do 50 k=1,80
        cword(k:k)=iword(k:k)
   50 continue
c
      do 51 k=nch+1,80
        cword(k:k)=' '
   51 continue
c
c     Move pen to symbol location
c
      IP=3
      if(SIZE.lt.0.0) IP=-3
      call PLOTU(X,Y,IP)
      write(LPLOT,fmt='(f9.3,a)') angl,' rotate'
c
c     Write character string
c
      write(LPLOT,fmt='(f9.3,x,a)') sz,' hV'
      write(LPLOT,fmt='(x,a,a,a,/,a)') '(',cword,')',' show'
c
c     Reset character orientation if necessary
c
      if(ANGL.eq.0.0) return
      bngl=-angl 
      write(LPLOT,fmt='(f9.3,a)') bngl,' rotate'
c
      return
      end
c
	subroutine FILLUP
c
c *** Modified by (K2) ***
c
      common/P00000/LPLOT,IROT,IL34,A,B,C,D,ASP,THET
      write(LPLOT,*) 'fill'
c
c ************************
c
      return
      end
c
      subroutine FILLTYP(it,spac,ian)
c
c     Specifying fill type for shading
c
c     it    - 
c     spac  - line spacing in cm converted to gray tone
c     ian   - 
c
      common/P00000/LPLOT,IROT,IL34,A,B,C,D,ASP,THET
      common/L00000/PSCA,xo,yo
c
      spec=spac
      write(LPLOT,fmt='(f9.3,a)') spec,' setgray'
      return
      end
c
      subroutine SHADRT(XI,YI)
c
c     Shading rectangle defined by coordinate increments xinc,yinc
c
      common/P00000/LPLOT,IROT,IL34,A,B,C,D,ASP,THET
      common/L00000/PSCA,xo,yo
c
c *** Modified by (K2) ***
c
c     xin=a*xi
c     yin=c*yi
c
c ************************
c
      call edgert(xi,yi)
      write(LPLOT,*) 'fill'
c
      return
      end
c
      subroutine EDGERT(XI,YI)
c
c     Edging rectangle defined by coordinate increments xi,yi
c
      common/P00000/LPLOT,IROT,IL34,A,B,C,D,ASP,THET
      common/L00000/PSCA,xo,yo
c
      call where(x,y,rf)
      call plot(x+xi,y,2)
      call plot(x+xi,y+yi,2)
      call plot(x,y+yi,2)
      call plot(x,y,2)
      write(LPLOT,*) 'closepath'
c
      return
      end
