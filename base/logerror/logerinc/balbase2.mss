* File balbase2.mss
*-------------------------------------------------------------------------------

* This file is part of the BALMOREL model.
* File last time modified 13-05-2003 (hr), 20080414(hr), 20120914(hr), 20150304(hr)


* This file will print the model and solver status, the objective value, etc.,
* for the model BALBASE2 for each year solved


* This file will print the solver status, the objective value, etc.,
* for each year solved.


Put logfile


* Note: The below text: "Some Balmorel errors" is a keyword for communication with the BUI. Do not change.
IF((ORD(Y) EQ 1),
IF ((ERRCOUNT2 EQ 0),
PUT "No obvious Balmorel errors detected in the input data before simulation."
ELSE
PUT "Some Balmorel errors were detected in the input data before simulation." " See the file errors.out." //;
));



IF((ORD(Y) EQ 1),
  PUT "Solver status of the BALBASE2 model each year in the simulation" //;
     PUT CARD(Y):4:0 " years to be simulated."  //;

  PUT "Year    Model status returned     " ;
  PUT "Solver status returned          " ;
  PUT "Obj. fct. value  " ;
  PUT "Iter. used " " No of infeas" " No of nonopt"PUT /;
);

IF((ORD(Y) EQ 1),
  IF((CARD(Y) GE 1),
  PUT "       (now to first SOLVE statement)" /;
));


* Note: The below text: "Some Balmorel errors" is a keyword for communication with the BUI. Do not change.
IF((ERRCOUNT3 GT 0),
PUT "       Some Balmorel errors were detected before optimisation of year " Y.TL:4". See the file errors.out." /;
);


PUT Y.TL:5 "  " ;
PUT$(BALBASE2.MODELSTAT EQ 1)  " Optimal                     ";
PUT$(BALBASE2.MODELSTAT EQ 2)  " Locally optimal             ";
PUT$(BALBASE2.MODELSTAT EQ 3)  " Unbounded                   ";
PUT$(BALBASE2.MODELSTAT EQ 4)  " Infeasible                  ";
PUT$(BALBASE2.MODELSTAT EQ 5)  " Locally infeasible          ";
PUT$(BALBASE2.MODELSTAT EQ 6)  " Intermediate infeasible     ";
PUT$(BALBASE2.MODELSTAT EQ 7)  " Intermediate nonoptimal     ";
PUT$(BALBASE2.MODELSTAT EQ 8)  " Integer solution            ";
PUT$(BALBASE2.MODELSTAT EQ 9)  " Intermediate non-integer    ";
PUT$(BALBASE2.MODELSTAT EQ 10) " Integer infeasible          ";
PUT$(BALBASE2.MODELSTAT EQ 12) " Error unknown               ";
PUT$(BALBASE2.MODELSTAT EQ 13) " Error no solution           ";
PUT$(BALBASE2.MODELSTAT EQ 14) " No solution returned        ";
PUT$(BALBASE2.MODELSTAT EQ 15) " Solved unique               ";
PUT$(BALBASE2.MODELSTAT EQ 16) " Solved                      ";
PUT$(BALBASE2.MODELSTAT EQ 17) " Solved singular             ";
PUT$(BALBASE2.MODELSTAT EQ 18) " Unbounded no solution       ";
PUT$(BALBASE2.MODELSTAT EQ 19) " Infeasible no solution      ";
PUT$(BALBASE2.MODELSTAT GE 20) " Error no. " BALBASE2.MODELSTAT:3:0 ", consult GAMS documentation for details about MODELSTAT." /;

PUT$(BALBASE2.SOLVESTAT EQ 1)  " Normal completion           ";
PUT$(BALBASE2.SOLVESTAT EQ 2)  " Max iterations reached      ";
PUT$(BALBASE2.SOLVESTAT EQ 3)  " Resource limit reached      ";
PUT$(BALBASE2.SOLVESTAT GE 4)  " Solver quit or terminated - error no.  " BALBASE2.SOLVESTAT:3:0 ", consult GAMS documentation for details about SOLVESTAT." /;
;

PUT VOBJ.L:16:2 " ";
PUT BALBASE2.ITERUSD:11:0 " " ;
PUT BALBASE2.NUMINFES:12:0 " " ;
PUT BALBASE2.NUMNOPT:13:0 /;



* Note: The below text: "Some Balmorel errors" is a keyword for communication with the BUI. Do not change.
IF((ERRCOUNT4 GT 0),
PUT "       Some Balmorel errors were detected after optimisation of year " Y.TL:4". See the file errors.out." /;
);

IF((ORD(Y) LT CARD(Y)),
  PUT "       (now to next SOLVE statement)" /;
);
