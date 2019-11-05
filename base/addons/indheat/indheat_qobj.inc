
* Addon  INDHEAT: contribution to QOBJ:
* Investment cost
+ IOF1000000*(SUM((INDHEAT_IA,INDHEAT_G,INDHEAT_GROUP)$(INDHEAT_IAGK_HASORPOT(Y,INDHEAT_IA,INDHEAT_G,INDHEAT_GROUP) AND INDHEAT_GINGROUP(INDHEAT_G,INDHEAT_GROUP)),
  (INDHEAT_VGKNACCUMNET(Y,INDHEAT_IA,INDHEAT_G,INDHEAT_GROUP)-INDHEAT_GKFX(Y,INDHEAT_IA,INDHEAT_G,INDHEAT_GROUP))*INDHEAT_GDATA(INDHEAT_G,'GDINVCOST0')*SUM(C$ICA(C,INDHEAT_IA),INDHEAT_ANNUITYCG(C,INDHEAT_G))
  )
  )

* Operation and maintainance cost:

   + SUM((INDHEAT_IA,INDHEAT_G,INDHEAT_GROUP)$(INDHEAT_GINGROUP(INDHEAT_G,INDHEAT_GROUP) AND INDHEAT_IAGK_HASORPOT(Y,INDHEAT_IA,INDHEAT_G,INDHEAT_GROUP)),
     INDHEAT_GDATA(INDHEAT_G,'GDOMVCOST0')
   * SUM((INDHEAT_DHUSER,IS3,T), IHOURSINST(IS3,T)* INDHEAT_VGH_T(Y,INDHEAT_IA,INDHEAT_DHUSER,INDHEAT_G,INDHEAT_GROUP,IS3,T)
$ifi not %COMBTECH%==yes $goto endcombtechOMV
         +SUM(INDHEAT_GALIAS$(INDHEAT_GGCOMB(INDHEAT_G,INDHEAT_GALIAS)),
$ifi not %HYDROGEN1%==yes $goto endhydrogenQOBJ1
         (1+INDHEAT_HYDROGEN_H2TOF(INDHEAT_GALIAS)$(INDHEAT_GDATA(INDHEAT_GALIAS,'GDFUEL') EQ THERMGAS_H2 OR INDHEAT_GDATA(INDHEAT_GALIAS,'GDFUEL') EQ BIOGAS_H2))*
$label endhydrogenQOBJ1
         INDHEAT_VGH_T(Y,INDHEAT_IA,INDHEAT_DHUSER,INDHEAT_GALIAS,INDHEAT_GROUP,IS3,T)
         )
$label endcombtechOMV
         ))

    + IOF1000*(SUM((INDHEAT_IA,INDHEAT_G,INDHEAT_GROUP)$(INDHEAT_IAGK_HASORPOT(Y,INDHEAT_IA,INDHEAT_G,INDHEAT_GROUP) AND INDHEAT_GINGROUP(INDHEAT_G,INDHEAT_GROUP)),
         (INDHEAT_VGKNACCUMNET(Y,INDHEAT_IA,INDHEAT_G,INDHEAT_GROUP)$(INDHEAT_IAGK_HASORPOT(Y,INDHEAT_IA,INDHEAT_G,INDHEAT_GROUP) AND INDHEAT_IAGKN(INDHEAT_IA,INDHEAT_G,INDHEAT_GROUP))
                 +INDHEAT_GKFX(Y,INDHEAT_IA,INDHEAT_G,INDHEAT_GROUP))
         *INDHEAT_GDATA(INDHEAT_G,'GDOMFCOST0')
         ))

* Cost of fuel consumption during the year:
   + SUM((INDHEAT_IA,INDHEAT_G,INDHEAT_GROUP,FFF)$(INDHEAT_GDATA(INDHEAT_G,'GDFUEL') EQ FDATA(FFF,'FDACRONYM') AND ( INDHEAT_GINGROUP(INDHEAT_G,INDHEAT_GROUP)
$ifi not %COMBTECH%==yes $goto endcombtechFUEL1
         OR SUM(INDHEAT_GALIAS,INDHEAT_GGCOMB(INDHEAT_GALIAS,INDHEAT_G))
$label endcombtechFUEL1
         ) AND FUELPRICE(Y,INDHEAT_IA,FFF) <> 0
         AND (INDHEAT_IAGK_HASORPOT(Y,INDHEAT_IA,INDHEAT_G,INDHEAT_GROUP)
$ifi not %COMBTECH%==yes $goto endcombtechFUEL2
         OR SUM(INDHEAT_GALIAS$INDHEAT_GGCOMB(INDHEAT_GALIAS,INDHEAT_G), INDHEAT_IAGK_HASORPOT(Y,INDHEAT_IA,INDHEAT_GALIAS,INDHEAT_GROUP))
$label endcombtechFUEL2
         )
         ),
$ifi %VGF%==ST               FUELPRICE(Y,INDHEAT_IA,FFF) * IOF3P6 * SUM((IS3,T), IHOURSINST(IS3,T) * INDHEAT_VGF_T(Y,INDHEAT_IA,INDHEAT_G,INDHEAT_GROUP,IS3,T)))
$ifi %VGF%==Y               FUELPRICE(Y,INDHEAT_IA,FFF) * IOF3P6 * INDHEAT_VGF_T(Y,INDHEAT_IA,INDHEAT_G,INDHEAT_GROUP))

*Emission taxes:
   + SUM( (C,SECTOR), SUM((INDHEAT_IA,INDHEAT_G,INDHEAT_GROUP,FFF)$(ICA(C,INDHEAT_IA) AND INDHEAT_GDATA(INDHEAT_G,'GDFUEL') EQ FDATA(FFF,'FDACRONYM') AND ( INDHEAT_GINGROUP(INDHEAT_G,INDHEAT_GROUP)
$ifi not %COMBTECH%==yes $goto endcombtechCO21
         OR SUM(INDHEAT_GALIAS,INDHEAT_GGCOMB(INDHEAT_GALIAS,INDHEAT_G))
$label endcombtechCO21
         ) AND M_POL(Y,"TAX_CO2",C) <> 0
         AND (INDHEAT_IAGK_HASORPOT(Y,INDHEAT_IA,INDHEAT_G,INDHEAT_GROUP) AND INDHEAT_AAAINSECTOR(INDHEAT_IA,SECTOR)
$ifi not %COMBTECH%==yes $goto endcombtechCO22
         OR SUM(INDHEAT_GALIAS$INDHEAT_GGCOMB(INDHEAT_GALIAS,INDHEAT_G), INDHEAT_IAGK_HASORPOT(Y,INDHEAT_IA,INDHEAT_GALIAS,INDHEAT_GROUP))
$label endcombtechCO22
         )
         ),
$ifi %VGF%==ST          SUM((IS3,T), IHOURSINST(IS3,T) * (FDATA(FFF,'FDCO2')*IOF0001) * IOF3P6 * INDHEAT_VGF_T(Y,INDHEAT_IA,INDHEAT_G,INDHEAT_GROUP,IS3,T)) * INDHEAT_M_POL(Y,'TAX_CO2',SECTOR,C))
$ifi %VGF%==Y           FDATA(FFF,'FDCO2')*IOF0001 * IOF3P6 * INDHEAT_VGF_T(Y,INDHEAT_IA,INDHEAT_G,INDHEAT_GROUP) * INDHEAT_M_POL(Y,'TAX_CO2',SECTOR,C))
         )

   + SUM( (C,SECTOR), SUM((INDHEAT_IA,INDHEAT_G,INDHEAT_GROUP,FFF)$(ICA(C,INDHEAT_IA) AND INDHEAT_GDATA(INDHEAT_G,'GDFUEL') EQ FDATA(FFF,'FDACRONYM') AND ( INDHEAT_GINGROUP(INDHEAT_G,INDHEAT_GROUP)
$ifi not %COMBTECH%==yes $goto endcombtechSO21
         OR SUM(INDHEAT_GALIAS,INDHEAT_GGCOMB(INDHEAT_GALIAS,INDHEAT_G))
$label endcombtechSO21
         ) AND M_POL(Y,"TAX_SO2",C) <> 0
         AND (INDHEAT_IAGK_HASORPOT(Y,INDHEAT_IA,INDHEAT_G,INDHEAT_GROUP) AND INDHEAT_AAAINSECTOR(INDHEAT_IA,SECTOR)
$ifi not %COMBTECH%==yes $goto endcombtechSO22
         OR SUM(INDHEAT_GALIAS$INDHEAT_GGCOMB(INDHEAT_GALIAS,INDHEAT_G), INDHEAT_IAGK_HASORPOT(Y,INDHEAT_IA,INDHEAT_GALIAS,INDHEAT_GROUP))
$label endcombtechSO22
         )
         ),
$ifi %VGF%==ST          SUM((IS3,T), IHOURSINST(IS3,T) * (FDATA(FFF,'FDSO2')*IOF0001) * IOF3P6 * INDHEAT_VGF_T(Y,INDHEAT_IA,INDHEAT_G,INDHEAT_GROUP,IS3,T)) * INDHEAT_M_POL(Y,'TAX_SO2',SECTOR,C))
$ifi %VGF%==Y           FDATA(FFF,'FDCO2')*IOF0001 * IOF3P6 * INDHEAT_VGF_T(Y,INDHEAT_IA,INDHEAT_G,INDHEAT_GROUP) * INDHEAT_M_POL(Y,'TAX_SO2',SECTOR,C))
         )

   + SUM( (C,SECTOR), SUM((INDHEAT_IA,INDHEAT_G,INDHEAT_GROUP)$(ICA(C,INDHEAT_IA) AND ( INDHEAT_GINGROUP(INDHEAT_G,INDHEAT_GROUP)
$ifi not %COMBTECH%==yes $goto endcombtechNOX1
         OR SUM(INDHEAT_GALIAS,INDHEAT_GGCOMB(INDHEAT_GALIAS,INDHEAT_G))
$label endcombtechNOX1
         ) AND M_POL(Y,"TAX_NOX",C) <> 0
         AND (INDHEAT_IAGK_HASORPOT(Y,INDHEAT_IA,INDHEAT_G,INDHEAT_GROUP) AND INDHEAT_AAAINSECTOR(INDHEAT_IA,SECTOR)
$ifi not %COMBTECH%==yes $goto endcombtechNOX2
         OR SUM(INDHEAT_GALIAS$INDHEAT_GGCOMB(INDHEAT_GALIAS,INDHEAT_G), INDHEAT_IAGK_HASORPOT(Y,INDHEAT_IA,INDHEAT_GALIAS,INDHEAT_GROUP))
$label endcombtechNOX2
         )
         ),
$ifi %VGF%==ST          SUM((IS3,T), IHOURSINST(IS3,T) * (INDHEAT_GDATA(INDHEAT_G,'GDNOX')*IOF0000001) * IOF3P6 * INDHEAT_VGF_T(Y,INDHEAT_IA,INDHEAT_G,INDHEAT_GROUP,IS3,T)) * INDHEAT_M_POL(Y,'TAX_NOX',SECTOR,C))
$ifi %VGF%==Y           INDHEAT_GDATA(INDHEAT_G,'GDNOX')*IOF0000001 * IOF3P6 * INDHEAT_VGF_T(Y,INDHEAT_IA,INDHEAT_G,INDHEAT_GROUP) * INDHEAT_M_POL(Y,'TAX_NOX',SECTOR,C))
         )

*Retrofitting TEST!!!!!
   +0.001*IOF1000*SUM((INDHEAT_IA,INDHEAT_G,INDHEAT_GROUP)$(SUM(INDHEAT_GROUPFROM,INDHEAT_IAGK_HASORPOT(Y,INDHEAT_IA,INDHEAT_G,INDHEAT_GROUPFROM)) AND INDHEAT_GINGROUP(INDHEAT_G,INDHEAT_GROUP) and SUM(INDHEAT_GROUPFROM, INDHEAT_GMOVE(INDHEAT_G,INDHEAT_GROUPFROM,INDHEAT_GROUP))),
                 INDHEAT_VGKNMOVETO(Y,INDHEAT_IA,INDHEAT_G,INDHEAT_GROUP)*INDHEAT_GDATA(INDHEAT_G,'GDINVCOST0')*SUM(C$ICA(C,INDHEAT_IA),INDHEAT_ANNUITYCG(C,INDHEAT_G))
         )