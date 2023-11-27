PROGRAM Main
  VAR_EXTERNAL
    LT_Low : BOOL;
  END_VAR
  VAR
    LT_Low_f : BOOL;
  END_VAR
  VAR_EXTERNAL
    LT_Middle : BOOL;
  END_VAR
  VAR
    LT_Middle_f : BOOL;
  END_VAR
  VAR_EXTERNAL
    LT_Hight : BOOL;
  END_VAR
  VAR
    LT_Hight_f : BOOL;
  END_VAR
  VAR_EXTERNAL
    HS_Auto : BOOL;
  END_VAR
  VAR
    HS_Auto_f : BOOL;
  END_VAR
  VAR_EXTERNAL
    P_Speed_50 : BOOL;
  END_VAR
  VAR
    P_Speed_50L : BOOL;
  END_VAR
  VAR_EXTERNAL
    P_Speed_100 : BOOL;
  END_VAR
  VAR
    P_Speed_100L : BOOL;
  END_VAR
  VAR_EXTERNAL
    P_Start : BOOL;
  END_VAR
  VAR
    P_StartL : BOOL;
  END_VAR
  VAR_EXTERNAL
    LT_error : BOOL;
  END_VAR
  VAR
    LT_errorL : BOOL;
  END_VAR
  VAR_EXTERNAL
    LT_set : BOOL;
    PLC_state : WORD;
  END_VAR
  VAR
    TON0 : TON;
  END_VAR
  VAR CONSTANT
    TM_5S : TIME := T#5s;
  END_VAR
  VAR
    TON1 : TON;
    TON2 : TON;
    TON3 : TON;
    NOT95_OUT : BOOL;
    OR68_OUT : BOOL;
    OR58_OUT : BOOL;
    OR80_OUT : BOOL;
    WORD_TO_INT93_OUT : INT;
    Inc91_OUT : INT;
    INT_TO_WORD94_OUT : WORD;
  END_VAR

  TON0(IN := HS_Auto, PT := TM_5S);
  HS_Auto_f := TON0.Q;
  TON1(IN := LT_Low, PT := TM_5S);
  LT_Low_f := TON1.Q;
  TON2(IN := LT_Middle, PT := TM_5S);
  LT_Middle_f := TON2.Q;
  TON3(IN := LT_Hight, PT := TM_5S);
  LT_Hight_f := TON3.Q;
  LT_errorL := LT_Hight_f AND (NOT(LT_Middle_f) AND LT_Low_f OR (LT_Middle_f OR NOT(LT_Middle_f)) AND NOT(LT_Low_f)) OR NOT(LT_Hight_f) AND LT_Middle_f AND NOT(LT_Low_f);
  IF LT_errorL THEN
    LT_error := TRUE; (*set*)
  END_IF;
  NOT95_OUT := NOT(LT_errorL);
  IF NOT(HS_Auto_f) AND NOT95_OUT THEN
    LT_error := FALSE; (*reset*)
  END_IF;
  IF NOT(LT_Low_f) THEN
    P_Speed_50L := FALSE; (*reset*)
  END_IF;
  IF NOT(LT_Low_f) THEN
    P_Speed_100L := TRUE; (*set*)
  END_IF;
  OR68_OUT := OR(P_Start AND LT_Middle_f, LT_set AND NOT(P_Start) AND NOT(LT_Middle_f));
  IF OR68_OUT THEN
    P_Speed_50L := TRUE; (*set*)
  END_IF;
  IF OR68_OUT THEN
    P_Speed_100L := FALSE; (*reset*)
  END_IF;
  OR58_OUT := OR(LT_Hight_f, NOT(HS_Auto_f), LT_error);
  IF OR58_OUT THEN
    P_Speed_50L := FALSE; (*reset*)
  END_IF;
  IF OR58_OUT THEN
    P_Speed_100L := FALSE; (*reset*)
  END_IF;
  IF (LT_set AND NOT(LT_Middle_f) OR NOT(LT_Low_f)) AND NOT(LT_error) AND HS_Auto_f THEN
    P_StartL := TRUE; (*set*)
  END_IF;
  OR80_OUT := OR(LT_Hight_f, NOT(HS_Auto_f), LT_error);
  IF OR80_OUT THEN
    P_StartL := FALSE; (*reset*)
  END_IF;
  P_Speed_100 := P_Speed_100L;
  P_Speed_50 := P_Speed_50L;
  P_Start := P_StartL;
  WORD_TO_INT93_OUT := WORD_TO_INT(PLC_state);
  Inc91_OUT := Inc(TRUE, WORD_TO_INT93_OUT);
  INT_TO_WORD94_OUT := INT_TO_WORD(Inc91_OUT);
  PLC_state := INT_TO_WORD94_OUT;
END_PROGRAM


CONFIGURATION config
  VAR_GLOBAL
    LT_Low AT %IX1.0.1.1 : BOOL := FALSE;
    LT_Middle AT %IX1.1.1.1 : BOOL := FALSE;
    LT_Hight AT %IX1.2.1.1 : BOOL := FALSE;
    HS_Auto AT %IX1.3.1.1 : BOOL := FALSE;
    P_Speed_50 AT %QX5.0.1.1 : BOOL := FALSE;
    P_Speed_100 AT %QX5.1.1.1 : BOOL := FALSE;
    P_Start AT %QX5.2.1.1 : BOOL := FALSE;
    LT_error AT %MX8.1.0 : BOOL := FALSE;
    LT_set AT %MX8.1.1 : BOOL := FALSE;
    PLC_state AT %MW8.2.0 : WORD := 0;
  END_VAR

  RESOURCE resource1 ON PLC
    TASK task0(INTERVAL := T#350ms,PRIORITY := 0);
    PROGRAM instance0 WITH task0 : Main;
  END_RESOURCE
END_CONFIGURATION
