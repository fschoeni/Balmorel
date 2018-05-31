* Equation declarations and definitions used in addon combtech




EQUATIONS
   QCOMBFUP(Y,AAA,G,S,T)            "Existing and new combtech, sum of fuel (MW) use any (S,T) limited by rated capacity (MW) on primal (0 for irrelevant, eps for 0) ({eps,(0;1]})"



   QECOMBGUP(Y,AAA,G,S,T)           "Existing and new combtech, sum of production (MW) any (S,T) limited by rated capacity on primal, electricity (0 for irrelevant, eps for 0) (MW)"
   QECOMBGSHARELO(Y,AAA,G,S,T)      "Existing and new combtech in IGKE, minimum share any (S,T) of total generation for this combtech group, electricity (0 for irrelevant, eps for 0) ((0;1])"
   QECOMBGSHAREUP(Y,AAA,G,S,T)      "Existing and new combtech in IGKE, maximum share any (S,T) of total generation for this combtech group, electricity (0 for irrelevant, eps for 0) ([0;1])"
   QECOMBFSHARELO(Y,AAA,G,S,T)      "Existing and new combtech in IGKE, minimum share any (S,T) of total fuel use for this combtech group, electricity (0 for irrelevant, eps for 0) ([0;1])"
   QECOMBFSHAREUP(Y,AAA,G,S,T)      "Existing and new combtech in IGKE, maximum share any (S,T) of total fuel use for this combtech group, electricity (0 for irrelevant, eps for 0) ([0;1])"



   QHCOMBGUP(Y,AAA,G,S,T)           "Existing and new combtech, sum of production any (S,T) limited by rated capacity on primal, (0 for irrelevant, eps for 0) heat (MW)"
   QHCOMBGSHARELO(Y,AAA,G,S,T)      "Existing and new combtech in IGKH, minimum share any (S,T) of total generation for this combtech group, heat (0 for irrelevant, eps for 0) ([0;1])"
   QHCOMBGSHAREUP(Y,AAA,G,S,T)      "Existing and new combtech in IGKH, maximum share any (S,T) of total generation for this combtech group, heat (0 for irrelevant, eps for 0) ([0;1])"
   QHCOMBFSHARELO(Y,AAA,G,S,T)      "Existing and new combtech in IGKH, minimum share any (S,T) of total fuel use for this combtech group, heat (0 for irrelevant, eps for 0) ([0;1])"
   QHCOMBFSHAREUP(Y,AAA,G,S,T)      "Existing and new combtech in IGKH, maximum share any (S,T) of total fuel use for this combtech group, heat (0 for irrelevant, eps for 0) ([0;1])"


   QECOMBGSHAREK1(Y,AAA,G,S,T)      "Primary combtech technology Electricity Production is limited by rated capacity on primal GDCOMBGSHAREK1"
   QECOMBGSHAREK12(Y,AAA,G,G,S,T)   "Secondary combtech technology Electricity Production is limited by GDCOMBGSHAREK1"
   QHCOMBGSHAREK1(Y,AAA,G,S,T)      "Primary combtech technology Heat Production is limited by GDCOMBGSHAREK1"
   QHCOMBGSHAREK12(Y,AAA,G,G,S,T)   "Secondary combtech technology Heat Production is limited by GDCOMBGSHAREK1"
   QCOMBFSHAREK1(Y,AAA,G,S,T)       "Primary combtech technology fuel consumption is limited by GDCOMBGSHAREK1"
   QCOMBFSHAREK12(Y,AAA,G,G,S,T)    "Secondary combtech technology fuel consumption is limited by GDCOMBGSHAREK1"
;

* Existing and new capacity:  ----------------------------------------------------------

* Existing and new combtech, sum of fuel (MW) use any (S,T) limited by rated capacity (MW) on primal (0 for irrelevant, eps for 0) ({eps,(0;1]})
QCOMBFUP(IY411,IA,IGCOMB1,IS3,T)$(IAGK_HASORPOT(IY411,IA,IGCOMB1) AND GDATA(IGCOMB1,'GDCOMBFUP'))..
  (VGKNACCUMNET(IY411,IA,IGCOMB1) + GKFX(IY411,IA,IGCOMB1)) * (1$(NOT IGKRATE(IA,IGCOMB1,IS3,T)) + IGKRATE(IA,IGCOMB1,IS3,T)) * GDATA(IGCOMB1,'GDCOMBFUP')
          =G=
  (VGF_T(IY411,IA,IGCOMB1,IS3,T) + SUM(IGCOMB2$GGCOMB(IGCOMB1,IGCOMB2), VGF_T(IY411,IA,IGCOMB2,IS3,T)));

* Bounds on individual units are assigned individually to .UP, however, the sum-of-bounds may exceed 1
QECOMBGUP(IY411,IA,IGCOMB1,IS3,T)$(IAGK_HASORPOT(IY411,IA,IGCOMB1) AND GDATA(IGCOMB1,'GDCOMBGUP') AND IGKE(IGCOMB1))..
  (VGKNACCUMNET(IY411,IA,IGCOMB1) + GKFX(IY411,IA,IGCOMB1)) * (1$(NOT IGKRATE(IA,IGCOMB1,IS3,T)) + IGKRATE(IA,IGCOMB1,IS3,T)) * (GDATA(IGCOMB1,'GDCOMBGUP')$GDATA(IGCOMB1,'GDCOMBGUP')+1$(NOT GDATA(IGCOMB1,'GDCOMBGUP')))
          =G=
  VGE_T(IY411,IA,IGCOMB1,IS3,T) + SUM(IGCOMB2$GGCOMB(IGCOMB1,IGCOMB2), VGE_T(IY411,IA,IGCOMB2,IS3,T));


* Existing and new combtech in IGKE, any combtech minimum share any (S,T) of total generation for this combtech group, electricity (0 for irrelevant, eps for 0) ([0;1])
QECOMBGSHARELO(IY411,IA,IGKE,IS3,T)$(IAGK_HASORPOT(IY411,IA,IGKE) AND GDATA(IGKE,'GDCOMBGSHARELO') AND (IGCOMB1(IGKE) OR IGCOMB2(IGKE)))..
  VGE_T(IY411,IA,IGKE,IS3,T) =G= GDATA(IGKE,'GDCOMBGSHARELO')*(
      (SUM(IGCOMB2$GGCOMB(IGKE,IGCOMB2), VGE_T(IY411,IA,IGCOMB2,IS3,T)) + VGE_T(IY411,IA,IGKE,IS3,T))$IGCOMB1(IGKE)
    + (SUM(IGCOMB1$GGCOMB(IGCOMB1,IGKE), VGE_T(IY411,IA,IGCOMB1,IS3,T)  + SUM(IGCOMB2$GGCOMB(IGCOMB1,IGCOMB2), VGE_T(IY411,IA,IGCOMB2,IS3,T))))$IGCOMB2(IGKE));


* Existing and new combtech in IGKE, maximum share any (S,T) of total generation for this combtech group, electricity (0 for irrelevant, eps for 0) ([0;1])
QECOMBGSHAREUP(IY411,IA,IGKE,IS3,T)$(IAGK_HASORPOT(IY411,IA,IGKE) AND (IGCOMB1(IGKE) OR IGCOMB2(IGKE)) AND GDATA(IGKE,'GDCOMBGSHAREUP'))..
  GDATA(IGKE,'GDCOMBGSHAREUP')*
  (  ( SUM(IGCOMB2$GGCOMB(IGKE,IGCOMB2), VGE_T(IY411,IA,IGCOMB2,IS3,T)) + VGE_T(IY411,IA,IGKE,IS3,T) )$IGCOMB1(IGKE)
   + ( SUM(IGCOMB1$GGCOMB(IGCOMB1,IGKE), VGE_T(IY411,IA,IGCOMB1,IS3,T) + SUM(IGCOMB2$GGCOMB(IGCOMB1,IGCOMB2), VGE_T(IY411,IA,IGCOMB2,IS3,T))) )$IGCOMB2(IGKE)
  )
         =G=
  VGE_T(IY411,IA,IGKE,IS3,T);


* Existing combtech in IGKE, minimum share any (S,T) of total fuel use for this combtech group, electricity (0 for irrelevant, eps for 0) ([0;1])
QECOMBFSHARELO(IY411,IA,IGKE,IS3,T)$(IAGK_HASORPOT(IY411,IA,IGKE) AND GDATA(IGKE,'GDCOMBFSHARELO') AND (IGCOMB1(IGKE) OR IGCOMB2(IGKE)))..
  VGF_T(IY411,IA,IGKE,IS3,T) =G=
  GDATA(IGKE,'GDCOMBFSHARELO')*
  (  ( SUM(IGCOMB2$GGCOMB(IGKE,IGCOMB2), VGF_T(IY411,IA,IGCOMB2,IS3,T)) + VGF_T(IY411,IA,IGKE,IS3,T) )$IGCOMB1(IGKE)
   + ( SUM(IGCOMB1$GGCOMB(IGCOMB1,IGKE), VGF_T(IY411,IA,IGCOMB1,IS3,T)  + SUM(IGCOMB2$GGCOMB(IGCOMB1,IGCOMB2), VGF_T(IY411,IA,IGCOMB2,IS3,T))) )$IGCOMB2(IGKE)     !! HOV:
  );


* Existing combtech in IGKE, maximum share any (S,T) of total fuel use for this combtech group, electricity (0 for irrelevant, eps for 0) ([0;1])
QECOMBFSHAREUP(IY411,IA,IGKE,IS3,T)$(IAGK_HASORPOT(IY411,IA,IGKE) AND (IGCOMB1(IGKE) OR IGCOMB2(IGKE)) AND GDATA(IGKE,'GDCOMBFSHAREUP'))..
  GDATA(IGKE,'GDCOMBFSHAREUP')*
  (  ( SUM(IGCOMB2$GGCOMB(IGKE,IGCOMB2), VGF_T(IY411,IA,IGCOMB2,IS3,T)) + VGF_T(IY411,IA,IGKE,IS3,T) )$IGCOMB1(IGKE)
   + ( SUM(IGCOMB1$GGCOMB(IGCOMB1,IGKE), VGF_T(IY411,IA,IGCOMB1,IS3,T) + SUM(IGCOMB2$GGCOMB(IGCOMB1,IGCOMB2), VGF_T(IY411,IA,IGCOMB2,IS3,T))) )$IGCOMB2(IGKE)
  )
         =G=
  VGF_T(IY411,IA,IGKE,IS3,T);


* Bounds on individual units are assigned individually to .UP, however, the sum-of-bounds may exceed 1
QHCOMBGUP(IY411,IA,IGCOMB1,IS3,T)$(IAGK_HASORPOT(IY411,IA,IGCOMB1) AND GDATA(IGCOMB1,'GDCOMBGUP') AND IGKH(IGCOMB1))..
  (VGKNACCUMNET(IY411,IA,IGCOMB1) + GKFX(IY411,IA,IGCOMB1))*(1$(NOT IGKRATE(IA,IGCOMB1,IS3,T)) + IGKRATE(IA,IGCOMB1,IS3,T)) * (GDATA(IGCOMB1,'GDCOMBGUP')$GDATA(IGCOMB1,'GDCOMBGUP')+1$(NOT GDATA(IGCOMB1,'GDCOMBGUP')))
        =G=
  VGH_T(IY411,IA,IGCOMB1,IS3,T) + SUM(IGCOMB2$GGCOMB(IGCOMB1,IGCOMB2), VGH_T(IY411,IA,IGCOMB2,IS3,T))
;


QHCOMBGSHARELO(IY411,IA,IGKH,IS3,T)$(IAGK_HASORPOT(IY411,IA,IGKH) AND (IGCOMB1(IGKH) OR IGCOMB2(IGKH)) AND GDATA(IGKH,'GDCOMBGSHARELO'))..
  VGH_T(IY411,IA,IGKH,IS3,T)  =G=  GDATA(IGKH,'GDCOMBGSHARELO')*
  (
    ( SUM(IGCOMB2$GGCOMB(IGKH,IGCOMB2), VGH_T(IY411,IA,IGCOMB2,IS3,T)) + VGH_T(IY411,IA,IGKH,IS3,T))$IGCOMB1(IGKH)
  + ( SUM(IGCOMB1$GGCOMB(IGCOMB1,IGKH), VGH_T(IY411,IA,IGCOMB1,IS3,T) + SUM(IGCOMB2$GGCOMB(IGCOMB1,IGCOMB2), VGH_T(IY411,IA,IGCOMB2,IS3,T))) )$IGCOMB2(IGKH)
  )
;


QHCOMBGSHAREUP(IY411,IA,IGKH,IS3,T)$(IAGK_HASORPOT(IY411,IA,IGKH) AND (IGCOMB1(IGKH) OR IGCOMB2(IGKH)) AND GDATA(IGKH,'GDCOMBGSHAREUP'))..
  GDATA(IGKH,'GDCOMBGSHAREUP')*
  (  ( SUM(IGCOMB2$GGCOMB(IGKH,IGCOMB2), VGH_T(IY411,IA,IGCOMB2,IS3,T)) + VGH_T(IY411,IA,IGKH,IS3,T) )$IGCOMB1(IGKH)
   + ( SUM(IGCOMB1$GGCOMB(IGCOMB1,IGKH), VGH_T(IY411,IA,IGCOMB1,IS3,T) + SUM(IGCOMB2$GGCOMB(IGCOMB1,IGCOMB2), VGH_T(IY411,IA,IGCOMB2,IS3,T))) )$IGCOMB2(IGKH)
  )
         =G=
  VGH_T(IY411,IA,IGKH,IS3,T)
;



* Existing combtech in IGKH, minimum share any (S,T) of total fuel use for this combtech group, electricity (0 for irrelevant, eps for 0) ([0;1])
QHCOMBFSHARELO(IY411,IA,IGKH,IS3,T)$(IAGK_HASORPOT(IY411,IA,IGKH) AND GDATA(IGKH,'GDCOMBFSHARELO') AND (IGCOMB1(IGKH) OR IGCOMB2(IGKH)))..
  VGF_T(IY411,IA,IGKH,IS3,T) =G=
  GDATA(IGKH,'GDCOMBFSHARELO')*
  (  ( SUM(IGCOMB2$GGCOMB(IGKH,IGCOMB2), VGF_T(IY411,IA,IGCOMB2,IS3,T)) + VGF_T(IY411,IA,IGKH,IS3,T) )$IGCOMB1(IGKH)
   + ( SUM(IGCOMB1$GGCOMB(IGCOMB1,IGKH), VGF_T(IY411,IA,IGCOMB1,IS3,T)  + SUM(IGCOMB2$GGCOMB(IGCOMB1,IGCOMB2), VGF_T(IY411,IA,IGCOMB2,IS3,T))) )$IGCOMB2(IGKH)     !! HOV:
  );


* Existing combtech in IGKH, maximum share any (S,T) of total fuel use for this combtech group, electricity (0 for irrelevant, eps for 0) ([0;1])
QHCOMBFSHAREUP(IY411,IA,IGKH,IS3,T)$(IAGK_HASORPOT(IY411,IA,IGKH) AND (IGCOMB1(IGKH) OR IGCOMB2(IGKH)) AND GDATA(IGKH,'GDCOMBFSHAREUP'))..
  GDATA(IGKH,'GDCOMBFSHAREUP')*
  (  ( SUM(IGCOMB2$GGCOMB(IGKH,IGCOMB2), VGF_T(IY411,IA,IGCOMB2,IS3,T)) + VGF_T(IY411,IA,IGKH,IS3,T) )$IGCOMB1(IGKH)
   + ( SUM(IGCOMB1$GGCOMB(IGCOMB1,IGKH), VGF_T(IY411,IA,IGCOMB1,IS3,T) + SUM(IGCOMB2$GGCOMB(IGCOMB1,IGCOMB2), VGF_T(IY411,IA,IGCOMB2,IS3,T))) )$IGCOMB2(IGKH)
  )
         =G=
  VGF_T(IY411,IA,IGKH,IS3,T);


*"Primary combtech technology Electricity Production is limited by GDCOMBGSHAREK1"
QECOMBGSHAREK1(IY411,IA,IGCOMB1,S,T)$(IGKE(IGCOMB1) AND GDATA(IGCOMB1,'GDCOMBGSHAREK1'))..
  (VGKNACCUMNET(IY411,IA,IGCOMB1) + GKFX(IY411,IA,IGCOMB1))* (1$(NOT IGKRATE(IA,IGCOMB1,S,T)) + IGKRATE(IA,IGCOMB1,S,T))*GDATA(IGCOMB1,'GDCOMBGSHAREK1')
   =G=
   VGE_T(IY411,IA,IGCOMB1,S,T)
;

*"Secondary combtech technology Electricity Production is limited by GDCOMBGSHAREK1"
QECOMBGSHAREK12(IY411,IA,IGCOMB1,IGCOMB2,IS3,T)$(IAGK_HASORPOT(IY411,IA,IGCOMB2) AND IGKE(IGCOMB2) AND GGCOMB(IGCOMB1,IGCOMB2) AND GDATA(IGCOMB2,'GDCOMBGSHAREK1'))..

  (VGKNACCUMNET(IY411,IA,IGCOMB1) + GKFX(IY411,IA,IGCOMB1)) * (1$(NOT IGKRATE(IA,IGCOMB1,IS3,T)) + IGKRATE(IA,IGCOMB1,IS3,T)) * GDATA(IGCOMB2,'GDCOMBGSHAREK1')
   =G=
   VGE_T(IY411,IA,IGCOMB2,IS3,T)

;



*"Primary combtech technology Heat Production is limited by GDCOMBGSHAREK1"
QHCOMBGSHAREK1(IY411,IA,IGCOMB1,S,T)$(IGKH(IGCOMB1)AND GDATA(IGCOMB1,'GDCOMBGSHAREK1'))..
  (VGKNACCUMNET(IY411,IA,IGCOMB1) + GKFX(IY411,IA,IGCOMB1))* (1$(NOT IGKRATE(IA,IGCOMB1,S,T)) + IGKRATE(IA,IGCOMB1,S,T))*GDATA(IGCOMB1,'GDCOMBGSHAREK1')
   =G=
   VGH_T(IY411,IA,IGCOMB1,S,T)
;

*"Secondary combtech technology Heat Production is limited by GDCOMBGSHAREK1"
QHCOMBGSHAREK12(IY411,IA,IGCOMB1,IGCOMB2,IS3,T)$(IAGK_HASORPOT(IY411,IA,IGCOMB2) AND IGKH(IGCOMB2) AND GGCOMB(IGCOMB1,IGCOMB2) AND GDATA(IGCOMB2,'GDCOMBGSHAREK1'))..

  (VGKNACCUMNET(IY411,IA,IGCOMB1) + GKFX(IY411,IA,IGCOMB1)) * (1$(NOT IGKRATE(IA,IGCOMB1,IS3,T)) + IGKRATE(IA,IGCOMB1,IS3,T)) * GDATA(IGCOMB2,'GDCOMBGSHAREK1')
   =G=
   VGH_T(IY411,IA,IGCOMB2,IS3,T)

;


*"Primary combtech technology fuel consumption is limited by GDCOMBGSHAREK1"
QCOMBFSHAREK1(IY411,IA,IGCOMB1,S,T)$(IAGK_HASORPOT(IY411,IA,IGCOMB1) AND GDATA(IGCOMB1,'GDCOMBFSHAREK1'))..
  (VGKNACCUMNET(IY411,IA,IGCOMB1) + GKFX(IY411,IA,IGCOMB1))* (1$(NOT IGKRATE(IA,IGCOMB1,S,T)) + IGKRATE(IA,IGCOMB1,S,T))*GDATA(IGCOMB1,'GDCOMBFSHAREK1')
   =G=
   VGF_T(IY411,IA,IGCOMB1,S,T)
;

*"Secondary combtech technology fuel Production is limited by GDCOMBGSHAREK1"
QCOMBFSHAREK12(IY411,IA,IGCOMB1,IGCOMB2,IS3,T)$(IAGK_HASORPOT(IY411,IA,IGCOMB2) AND IGKH(IGCOMB2) AND GGCOMB(IGCOMB1,IGCOMB2) AND GDATA(IGCOMB2,'GDCOMBFSHAREK1'))..

  (VGKNACCUMNET(IY411,IA,IGCOMB1) + GKFX(IY411,IA,IGCOMB1)) * (1$(NOT IGKRATE(IA,IGCOMB1,IS3,T)) + IGKRATE(IA,IGCOMB1,IS3,T)) * GDATA(IGCOMB2,'GDCOMBFSHAREK1')
   =G=
   VGF_T(IY411,IA,IGCOMB2,IS3,T)

;