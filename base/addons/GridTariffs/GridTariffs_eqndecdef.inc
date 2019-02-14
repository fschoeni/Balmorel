EQUATIONS
QGETOH_CAP1(YYY,AAA,SSS,TTT) 'endogenous limit to electricity consumption under demand charge winter, summer and "2"'
QGETOH_CAP2(YYY,AAA,SSS,TTT) 'endogenous limit to electricity consumption under demand charge TOU'
QGETOH_CAPY(YYY,AAA,SSS,TTT) 'endogenous limit to electricity consumption under demand charge yearly'
QGETOH_CAPBB3(YYY,AAA,SSS,TTT) 'demand charge for BB3'

QDEUSER_CAP1(YYY,RRR,DEUSER,SSS,TTT) 'endogenous limit to electricity consumption under demand charge winter, summer and "2"'
QDEUSER_CAP2(YYY,RRR,DEUSER,SSS,TTT) 'endogenous limit to electricity consumption under demand charge TOU'
QDEUSER_CAPY(YYY,RRR,DEUSER,SSS,TTT) 'endogenous limit to electricity consumption under demand charge yearly'

;

QGETOH_CAP1(IY411,IA,IS3,T)$(SUM(IGETOH, IAGK_HASORPOT(IY411,IA,IGETOH)) AND SUM(IR$RRRAAA(IR,IA), IGR_PRICE_TECH(IY411,IR,'GRDDCW')))..
                         SUM(IGETOH$IAGK_HASORPOT(IY411,IA,IGETOH), VGF_T(IY411,IA,IGETOH,IS3,T))
                         =L=
                         SUM(MMM, VGETOH_CAP1(IY411,IA,MMM)* ISSSTTTMMM(IS3,T,MMM));


QGETOH_CAP2(IY411,IA,IS3,T)$(SUM(IGETOH,IAGK_HASORPOT(IY411,IA,IGETOH)) AND SUM(IR$RRRAAA(IR,IA), IGR_PRICE_TECH(IY411,IR,'GRDDCTOU')))..
                         SUM(IGETOH$IAGK_HASORPOT(IY411,IA,IGETOH), VGF_T(IY411,IA,IGETOH,IS3,T)$SUM(IR$RRRAAA(IR,IA), IGR_TIME('GRDDCTOU',IR,IS3,T)))
                         =L=
                         SUM(MMM, VGETOH_CAP2(IY411,IA,MMM)* ISSSTTTMMM(IS3,T,MMM));

QGETOH_CAPY(IY411,IA,IS3,T)$(SUM(IGETOH,IAGK_HASORPOT(IY411,IA,IGETOH)) AND SUM(IR$RRRAAA(IR,IA), IGR_PRICE_TECH(IY411,IR,'GRDDCY')))..
                         SUM(IGETOH$IAGK_HASORPOT(IY411,IA,IGETOH), VGF_T(IY411,IA,IGETOH,IS3,T)$SUM(IR$RRRAAA(IR,IA),IGR_TIME('GRDDCY',IR,IS3,T)))
                         =L=
                         VGETOH_CAPY(IY411,IA);

QGETOH_CAPBB3(Y,IA,IS3,T)$SUM(IGETOH,IAGK_HASORPOT(Y,IA,IGETOH))..
                         SUM(IGETOH, VGF_T(Y,IA,IGETOH,IS3,T)) =L= IGRGETOHLEVEL(IA,IS3,T);





QDEUSER_CAP1(IY411,IR,DEUSER,IS3,T)$IGR_PRICE_DEUSER(IY411,IR,DEUSER,'GRDDCW')..
                            (((DE(IY411,IR,DEUSER) * DE_VAR_T(IR,DEUSER,IS3,T)) / IDE_SUMST(IR,DEUSER))$(IDE_SUMST(IR,DEUSER) GT 0))             !! classical demand
$ifi %DemandResponse%==yes  + SUM((IA,DR_TECH)$(IADR(IY411,IA,DR_TECH) AND RRRAAA(IR,IA) AND DR_TECH_USER(DR_TECH,DEUSER)),  VDR_UP(IY411,IA,DR_TECH,IS3,T) - VDR_DOWN(IY411,IA,DR_TECH,IS3,T))
$ifi %EV%==yes              + (VEV_VNETCHARGE_BEV(IY411,IR,IS3,T) + VEV_VNETCHARGE_PHEV(IY411,IR,IS3,T) - VEV_VNETDISCHARGE_BEV(IY411,IR,IS3,T) - VEV_VNETDISCHARGE_PHEV(IY411,IR,IS3,T))$IRESE(DEUSER)
                            =L=
                            SUM(MMM, VDEUSER_CAP1(IY411,IR,DEUSER,MMM)* ISSSTTTMMM(IS3,T,MMM));


QDEUSER_CAP2(IY411,IR,DEUSER,IS3,T)$(IGR_PRICE_DEUSER(IY411,IR,DEUSER,'GRDDCTOU') AND IGR_TIME('GRDDCTOU',IR,IS3,T))..
                 (          ((DE(IY411,IR,DEUSER) * DE_VAR_T(IR,DEUSER,IS3,T)) / IDE_SUMST(IR,DEUSER))$(IDE_SUMST(IR,DEUSER) GT 0)          !! classical demand
$ifi %DemandResponse%==yes  + SUM((IA,DR_TECH)$(IADR(IY411,IA,DR_TECH) AND RRRAAA(IR,IA) AND DR_TECH_USER(DR_TECH,DEUSER)),  VDR_UP(IY411,IA,DR_TECH,IS3,T) - VDR_DOWN(IY411,IA,DR_TECH,IS3,T))
$ifi %EV%==yes              + (VEV_VNETCHARGE_BEV(IY411,IR,IS3,T) + VEV_VNETCHARGE_PHEV(IY411,IR,IS3,T) - VEV_VNETDISCHARGE_BEV(IY411,IR,IS3,T) - VEV_VNETDISCHARGE_PHEV(IY411,IR,IS3,T))$IRESE(DEUSER)
                 )$IGR_TIME('GRDDCTOU',IR,IS3,T)
                            =L=
                            SUM(MMM, VDEUSER_CAP2(IY411,IR,DEUSER,MMM)* ISSSTTTMMM(IS3,T,MMM));

QDEUSER_CAPY(IY411,IR,DEUSER,IS3,T)$(IGR_PRICE_DEUSER(IY411,IR,DEUSER,'GRDDCY') AND IGR_TIME('GRDDCY',IR,IS3,T)) ..
                            ((DE(IY411,IR,DEUSER) * DE_VAR_T(IR,DEUSER,IS3,T)) / IDE_SUMST(IR,DEUSER))$(IDE_SUMST(IR,DEUSER) GT 0) +15             !! classical demand
$ifi %DemandResponse%==yes  + SUM((IA,DR_TECH)$(IADR(IY411,IA,DR_TECH) AND RRRAAA(IR,IA) AND DR_TECH_USER(DR_TECH,DEUSER)),  VDR_UP(IY411,IA,DR_TECH,IS3,T) - VDR_DOWN(IY411,IA,DR_TECH,IS3,T))
$ifi %EV%==yes              + (VEV_VNETCHARGE_BEV(IY411,IR,IS3,T) + VEV_VNETCHARGE_PHEV(IY411,IR,IS3,T) - VEV_VNETDISCHARGE_BEV(IY411,IR,IS3,T) - VEV_VNETDISCHARGE_PHEV(IY411,IR,IS3,T))$IRESE(DEUSER)
                            =L=
                            VDEUSER_CAPY(IY411,IR,DEUSER);