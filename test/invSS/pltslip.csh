#  gmt shaded grid shell script
#  to run: csh pltslip.csh FILE
#	where FILE is the file of x,y,z slip values made with PLISAXYZ
#	(e.g., contr01.dat, contr02.dat, etc)
#
psbasemap -R-50/150/-50/50 -Jx0.1 -Ba20g10:." COLIMA 1995": -K > grdplt.ps
psxy $1 -H -Jx0.1 -R-50/150/-50/50 -V -Ss1.33 -Cgray.cpt -O -K >> grdplt.ps  
psxy -Jx0.1 -R-50/150/-50/50 -V -Sa0.5 -Cgray.cpt  -O -K <<eoi >> grdplt.ps
0. 0. 100.
eoi
psscale -D22/5/10/1 -Cgray.cpt -O >> grdplt.ps
exit
