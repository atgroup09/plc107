TYPE
  LOGLEVEL : (CRITICAL, WARNING, INFO, DEBUG) := INFO;
END_TYPE

FUNCTION_BLOCK LOGGER
  VAR_INPUT
    TRIG : BOOL;
    MSG : STRING;
    LEVEL : LOGLEVEL := INFO;
  END_VAR
  VAR
    TRIG0 : BOOL;
  END_VAR

  IF TRIG AND NOT TRIG0 THEN
  {{
   LogMessage(GetFbVar(LEVEL),(char*)GetFbVar(MSG, .body),GetFbVar(MSG, .len));
  }}
  END_IF;
  TRIG0:=TRIG;
END_FUNCTION_BLOCK



FUNCTION ScaleA : REAL
  VAR_INPUT
    Ex : BOOL := FALSE;
    V : REAL := 0.0;
    Ka : REAL := 0.0;
    Kb : REAL := 0.0;
    Y : REAL := 0.0;
  END_VAR

  IF Ex = TRUE THEN
    ScaleA:= (Ka*V)+Kb;
  ELSE  
    ScaleA:= Y;
  END_IF;
END_FUNCTION

FUNCTION ScaleA_Kb : REAL
  VAR_INPUT
    Ex : BOOL := FALSE;
    V1 : REAL := 0.0;
    V2 : REAL := 0.0;
    Y1 : REAL := 0.0;
    Y2 : REAL := 0.0;
    Kb : REAL := 0.0;
  END_VAR

  IF Ex = TRUE THEN
    ScaleA_Kb:= ((Y1*V2)-(Y2*V1))/(V2-V1);
  ELSE  
    ScaleA_Kb:= Kb;
  END_IF;
END_FUNCTION

FUNCTION_BLOCK TONtest
  VAR_INPUT
    IN : BOOL := FALSE;
    MS : DWORD := 0;
  END_VAR
  VAR_OUTPUT
    Q : BOOL := FALSE;
    ET : TIME := T#0ms;
    EDW : DWORD := 0;
    EREA : REAL := 0.0;
  END_VAR
  VAR
    TON1 : TON;
    TON1_IN : BOOL := FALSE;
    TON1_TM : TIME := T#0ms;
  END_VAR

  TON1_IN:= IN;
  TON1_TM:= REAL_TO_TIME(DWORD_TO_REAL(MS)/1000.0);

  TON1(IN:=TON1_IN, PT:=TON1_TM);
  Q   := TON1.Q;
  ET  := TON1.ET;
  EDW := REAL_TO_DWORD(TIME_TO_REAL(TON1.ET)*1000.0);
  EREA:= TIME_TO_REAL(TON1.ET);
END_FUNCTION_BLOCK

FUNCTION ScaleA_Ka : REAL
  VAR_INPUT
    Ex : BOOL := FALSE;
    V1 : REAL := 0.0;
    V2 : REAL := 0.0;
    Y1 : REAL := 0.0;
    Y2 : REAL := 0.0;
    Ka : REAL := 0.0;
  END_VAR

  IF Ex = TRUE THEN
    ScaleA_Ka:= (Y2-Y1)/(V2-V1);
  ELSE  
    ScaleA_Ka:= Ka;
  END_IF;
END_FUNCTION

FUNCTION_BLOCK TONcont
  VAR_INPUT
    IN : BOOL := FALSE;
  END_VAR
  VAR_OUTPUT
    Q : BOOL := FALSE;
    ET : TIME := T#0ms;
  END_VAR
  VAR
    TON1 : TON;
    TON1_IN : BOOL := FALSE;
    TON1_TM : TIME := T#600000ms;
    TON1Inc : TON;
    TON1Inc_IN : BOOL := FALSE;
    TON1Inc_TM : TIME := T#300000ms;
  END_VAR

  TON1_IN   := IN;
  TON1Inc_IN:= IN;

  IF TON1Inc.Q = TRUE THEN
    TON1_TM   := ADD_TIME(IN1:=TON1_TM, IN2:=TON1Inc_TM);
    TON1Inc_IN:= FALSE;
  END_IF;

  TON1(IN:=TON1_IN, PT:=TON1_TM);
  TON1Inc(IN:=TON1Inc_IN, PT:=TON1Inc_TM);

  Q := TON1.Q;
  ET:= TON1.ET;
END_FUNCTION_BLOCK

FUNCTION_BLOCK FLRtun
  VAR_INPUT
    Ex : BOOL := FALSE;
    V : REAL := 0.0;
    Diff : REAL := 0.0;
    Pro : BYTE := 0;
  END_VAR
  VAR_OUTPUT
    Ok : BYTE := 0;
    OY : REAL := 0.0;
    OTm : DWORD := 0;
  END_VAR
  VAR
    TunDone : BOOL := FALSE;
    Tm1 : REAL := 0.0;
    V1Set : BOOL := FALSE;
    V01 : REAL := 0.0;
    TONcont1 : TONcont;
    TONcont1_IN : BOOL := FALSE;
  END_VAR

  (* Pro - process type *)
  (* = 0 - increasing (by default) *)
  (* = 1 - decreasing *)

  (* Ok - result code *)
  (* = 0 - work *)
  (* = 1 - off *)
  (* = 3 - work done success *)

  IF Ex = TRUE THEN
    
    IF TunDone = FALSE THEN
        
      (* work *)
      Ok:= 0;
        
      IF V1Set = FALSE THEN
        V1Set:= TRUE;
        (* calculate setpoint for V(0.1) by type of process *)
        IF Pro = 1 THEN
          (* decreasing *)
          V01 := (V-(0.1*Diff));
        ELSE
          (* increasing *)
          V01 := (V+(0.1*Diff));
        END_IF;
      END_IF;
        
      (* set Tm1 (ms) *)
      IF V < V01 THEN
        Tm1:= TIME_TO_REAL(TONcont1.ET)*1000.0;
      ELSE
        OTm:= REAL_TO_DWORD((Tm1*1.875));
        TunDone:= TRUE;
        (* work done success *)
        Ok:= 3;
      END_IF;
      
    END_IF;
    (* end of TunDone *)
      
  ELSE
    (* off *)
    Ok:= 1;
  END_IF;
  (* end of Ex *)

  (* work *)
  IF Ok = 0 THEN
    OY         := 100.0;
    TONcont1_IN:= TRUE;
  END_IF;

  (* off, error *)
  IF Ok = 1 THEN
    OY         := 0.0;
    TONcont1_IN:= FALSE;
    V1Set      := FALSE;
    TunDone    := FALSE;
    OTm        := 0;
  END_IF;

  (* work is done success *)
  IF TunDone = TRUE THEN
    OY         := 0.0;
    TONcont1_IN:= FALSE;
  END_IF;

  TONcont1(IN:=TONcont1_IN);

  (* DEBUG *)
  (* set Class of debug variables to Output to use its as Outputs of the FB *)
  (* set Class of debug variables to Local to hide its *)
  (* Deb_V1 := V01; *)
  (* Deb_Tm1:= Tm1; *)
  (* end of DEBUG *)
END_FUNCTION_BLOCK

FUNCTION GetBitWo : BOOL
  VAR_INPUT
    Wo : WORD := 0;
    Pos : BYTE := 0;
  END_VAR
  VAR
    Mask : WORD := 0;
  END_VAR

  Mask:= REAL_TO_WORD(EXPT(INT_TO_REAL(2),BYTE_TO_INT(Pos)));
  GetBitWo:= ((Wo AND Mask) > 0);
END_FUNCTION

FUNCTION_BLOCK FiltrD
  VAR_INPUT
    Ex : BOOL := FALSE;
    V : BOOL := FALSE;
    Tm : TIME := T#0ms;
  END_VAR
  VAR_OUTPUT
    Ov : BOOL := FALSE;
  END_VAR
  VAR
    Val : BOOL := FALSE;
    TON0 : TON;
    TON1 : TON;
  END_VAR

  TON0(IN:=AND(Ex, NOT(V)), PT:=Tm);
  TON1(IN:=AND(Ex, V), PT:=Tm);

  IF TON0.Q = TRUE THEN
    Val:= FALSE;
  END_IF;

  IF TON1.Q = TRUE THEN
    Val:= TRUE;
  END_IF;

  Ov:= Val;
END_FUNCTION_BLOCK

FUNCTION_BLOCK FLR1
  VAR_INPUT
    Ex : BOOL := FALSE;
    V : REAL := 0.0;
    Sp : REAL := 0.0;
    Pro : BYTE := 0;
    Sck : BOOL := FALSE;
    Tm : DWORD := 0;
    dV : REAL := 0.0;
    dZ : REAL := 0.0;
    dE : REAL := 0.0;
    dETm : DWORD := 5000;
    Ym : BYTE := 0;
  END_VAR
  VAR_OUTPUT
    Ok : BYTE := 0;
    OY : REAL := 0.0;
  END_VAR
  VAR
    Vprev : REAL := 0.0;
    TmDv : REAL := 0.0;
    UpDown : SINT := 0;
    SckSet : BOOL := FALSE;
    ErrorSet : BOOL := FALSE;
    Er : REAL := 0.0;
    TON_De : TON;
    TON_De_IN : BOOL := FALSE;
    TON_De_TM : TIME := T#0ms;
    DeV : REAL := 0.0;
    DeV1Set : BOOL := FALSE;
    DeV2Set : BOOL := FALSE;
    TON_Dv : TON;
    TON_Dv_IN : BOOL := FALSE;
    TON_Dv_TM : TIME := T#0ms;
  END_VAR

  (* Pro - process type *)
  (* = 0 - increasing (by default) *)
  (* = 1 - decreasing *)

  (* Ym - type of OY *)
  (* = 0 - unipolar    0.0 .. 100.0 % (by default) *)
  (* = 1 - bipolar  -100.0 .. 100.0 % *)

  (* Ok - result code *)
  (* = 0 - work *)
  (* = 1 - off *)
  (* = 2 - dead (d-)zone *)
  (* = 4 - control failure (e-)zone *)

  (* reset Sck *)
  IF Sck = FALSE THEN
    SckSet:= FALSE;
  END_IF;

  (* test execution allow *)
  IF Ex = TRUE THEN
      
    (* test start *)
    IF Sck = TRUE AND SckSet = FALSE AND ErrorSet = FALSE THEN
      
      SckSet:= TRUE;  
            
      (* work *)
      Ok:= 0;
      
      Er:= (Sp-V);
      
      (* test d-zone *)
      IF ABS(IN:=Er) >= dZ THEN
        (* exec *)
        {extern void AppFlr(FLR1*);AppFlr(data__);}
      ELSE
        (* d-zone *)
        Ok:= 2;
      END_IF;
      (* end of test d-zone *)
        
    END_IF;
    (* end of test start *)
    
  ELSE
    (* off *)
    Ok:= 1;
  END_IF;
  (* end of Ex *) 

  (* work *)
  IF Ok = 0 THEN
    
    IF TmDv > 0.0 THEN
      (* msec to real-sec to time *)
      TON_Dv_TM:= REAL_TO_TIME(TmDv/1000.0);
      TON_Dv_IN:= TRUE;
    END_IF;
    
    IF TON_Dv.Q = TRUE THEN
      TON_Dv_IN:= FALSE;
      (* down *)
      IF UpDown = -1 THEN
        OY:= OY-dV;
      END_IF;
      (* up *)
      IF UpDown = 1 THEN
        OY:= OY+dV;
      END_IF;
    END_IF;
    
  ELSE
    TON_Dv_IN:= FALSE;
  END_IF;
  (* end of work *)

  (* test e-zone *)
  IF Ok = 0 AND ABS(IN:=OY) >= 100.0 THEN
    
    IF dETm > 0 THEN
      (* msec to real-sec to time *)
      TON_De_TM:= REAL_TO_TIME(DWORD_TO_REAL(dETm)/1000.0);
      TON_De_IN:= TRUE;
    END_IF;
      
    IF DeV1Set = FALSE THEN
      (* point 1 *)
      DeV:= V;
      DeV1Set:= TRUE;
    END_IF;
      
    IF TON_De.Q = TRUE THEN
      IF DeV2Set = FALSE THEN
        (* point 2 *)
        DeV:= (V-DeV);
        DeV2Set:= TRUE;
      END_IF;
      IF DeV < dE OR DeV < 0.0 THEN
        (* e-zone *)
        Ok:= 4;
        ErrorSet:= TRUE;
      END_IF;
    END_IF;
    
  ELSE
    TON_De_IN:= FALSE;
    DeV1Set  := FALSE;
    DeV2Set  := FALSE;
  END_IF;
  (* end of test e-zone *)

  (* off *)
  IF Ok = 1 THEN
    OY       := 0.0;
    SckSet   := FALSE;
    ErrorSet := FALSE;
    Vprev    := 0.0;
  END_IF;

  (* error *)
  IF ErrorSet = TRUE THEN
    OY       := 0.0;
  END_IF;

  (* scale OY by type of process *)
  IF Pro = 1 THEN
    (* decreasing *)
    OY:= (100.0-OY);
  END_IF;

  (* scale OY by type of output *)
  IF Ym = 1 THEN
    (* bipolar *)
    OY:= LIMIT(MN:=-100.0, IN:=OY, MX:=100.0);
  ELSE
    (* unipolar *)
    OY:= LIMIT(MN:=0.0, IN:=OY, MX:=100.0);
  END_IF;

  TON_De(IN:=TON_De_IN, PT:=TON_De_TM);
  TON_Dv(IN:=TON_Dv_IN, PT:=TON_Dv_TM);

  (* DEBUG *)
  (* set Class of debug variables to Output to use its as Outputs of the FB *)
  (* set Class of debug variables to Local to hide its *)
  (* Deb_UpDown:= UpDown; *)
  (* Deb_dVTm  := REAL_TO_DWORD(TmDv); *)
  (* Deb_dVEt  := REAL_TO_DWORD(TIME_TO_REAL(TON_Dv.ET)*1000.0); *)
  (* Deb_dEEt  := REAL_TO_DWORD(TIME_TO_REAL(TON_De.ET)*1000.0); *)
  (* end of DEBUG *)
END_FUNCTION_BLOCK

FUNCTION_BLOCK FLR2
  VAR_INPUT
    Ex : BOOL := FALSE;
    V : REAL := 0.0;
    Sp : REAL := 0.0;
    Pro : BYTE := 0;
    Tm : DWORD := 0;
    dV : REAL := 0.0;
    dZ : REAL := 0.0;
    dE : REAL := 0.0;
    dETm : DWORD := 5000;
    Ym : BYTE := 0;
  END_VAR
  VAR_OUTPUT
    Ok : BYTE := 0;
    OY : REAL := 0.0;
  END_VAR
  VAR
    TON_Work : TON;
    TON_Work_IN : BOOL := FALSE;
    TON_Work_TM : TIME := T#0ms;
    FLR1_1 : FLR1;
  END_VAR

  FLR1_1(Ex:=Ex, V:=V, Sp:=Sp, Pro:=Pro, Sck:=TON_Work.Q, Tm:=Tm, dV:=dV, dZ:=dZ, dE:=dE, dETm:=dETm, Ym:=Ym);

  Ok:= FLR1_1.Ok;
  OY:= FLR1_1.OY;

  IF Ex = TRUE AND Tm > 0 THEN
    (* msec to real-sec to time *)
    TON_Work_TM:= REAL_TO_TIME(DWORD_TO_REAL(Tm)/1000.0);
    TON_Work_IN:= TRUE;
  ELSE
    TON_Work_IN:= FALSE;
  END_IF;

  IF TON_Work.Q = TRUE THEN
    TON_Work_IN:= FALSE;
  END_IF;

  TON_Work(IN:=TON_Work_IN, PT:=TON_Work_TM);

  (* DEBUG *)
  (* set Class of debug variables to Output to use its as Outputs of the FB *)
  (* set Class of debug variables to Local to hide its *)
  (* Deb_Speed := FLR1_1.Deb_Speed; *)
  (* Deb_UpDown:= FLR1_1.Deb_UpDown; *)
  (* Deb_dVTm  := FLR1_1.Deb_dVTm; *)
  (* Deb_dVEt  := FLR1_1.Deb_dVEt; *)
  (* Deb_dEEt  := FLR1_1.Deb_dEEt; *)
  (* Deb_Et    := REAL_TO_DWORD(TIME_TO_REAL(TON_Work.ET)*1000.0); *)
  (* Deb_Y0    := FLR1_1.Deb_Y0; *)
  (* Deb_Er    := FLR1_1.Deb_Er; *)
  (* Deb_Cm    := FLR1_1.Deb_Cm; *)
  (* Deb_m     := FLR1_1.Deb_m; *)
  (* end of DEBUG *)
END_FUNCTION_BLOCK

FUNCTION_BLOCK PIDtun
  VAR_INPUT
    Ex : BOOL := FALSE;
    V : REAL := 0.0;
    Diff : REAL := 0.0;
    Ty : BYTE := 0;
    Pro : BYTE := 0;
  END_VAR
  VAR_OUTPUT
    Ok : BYTE := 0;
    OY : REAL := 0.0;
    OKp : REAL := 0.0;
    OKi : REAL := 0.0;
    OKd : REAL := 0.0;
    OTm : DWORD := 0;
  END_VAR
  VAR
    TunDone : BOOL := FALSE;
    Tm1 : REAL := 0.0;
    Tm2 : REAL := 0.0;
    TmSum : REAL := 0.0;
    V1Set : BOOL := FALSE;
    V01 : REAL := 0.0;
    V063 : REAL := 0.0;
    Rr : REAL := 0.0;
    Tm1sec : REAL := 0.0;
    TONcont1 : TONcont;
    TONcont1_IN : BOOL := FALSE;
  END_VAR

  (* Ty - regulator type *)
  (* = 0 - PID *)
  (* = 1 - PI *)
  (* = 2 - PD *)
  (* = 3 - P *)

  (* Pro - process type *)
  (* = 0 - increasing (by default) *)
  (* = 1 - decreasing *)

  (* Ok - result code *)
  (* = 0 - work *)
  (* = 1 - off *)
  (* = 2 - incorrect regulator type *)
  (* = 3 - work done success *)

  IF Ex = TRUE THEN
    
    IF Ty <= 3 THEN
        
      IF TunDone = FALSE THEN
        
        (* work *)
        Ok:= 0;
        
        IF V1Set = FALSE THEN
          V1Set:= TRUE;
          (* calculate setpoint for V(0.1) by type of process *)
          IF Pro = 1 THEN
            (* decreasing *)
            V01 := (V-(0.1*Diff));
            V063:= (V-(0.63*Diff));
          ELSE
            (* increasing *)
            V01 := (V+(0.1*Diff));
            V063:= (V+(0.63*Diff));
          END_IF;
        END_IF;
        
        (* set Tm1 (ms) *)
        IF V < V01 THEN
          Tm1:= TIME_TO_REAL(TONcont1.ET)*1000.0;
        END_IF;
        
        (* set Tm2 (ms) *)
        IF V >= V063 THEN
          
          TONcont1_IN:= FALSE;
          TunDone    := TRUE;
          
          Tm2   := TIME_TO_REAL(TONcont1.ET)*1000.0;
          TmSum := (Tm1+Tm2);
          OTm   := REAL_TO_DWORD((Tm1*1.875));
          Rr    := (Diff/((TmSum-Tm1)/1000.0));
          Tm1sec:= (Tm1/1000.0);
          (* 1000 - divider to convert msec to sec *)
            
          (* calculate factors by type of regulator *)
          CASE BYTE_TO_INT(Ty) OF
            0:
              (* PID *)
              OKp:= (1.2/(Rr*Tm1sec));
              OKi:= (2.0*Tm1sec);
              OKd:= (0.4*Tm1sec);
            1:
              (* PI *)
              OKp:= (0.8/(Rr*Tm1sec));
              OKi:= (2.0*Tm1sec);
            2:
              (*PD*)
              OKp:= (1.0/(Rr*Tm1sec));
              OKd:= (0.25*Tm1sec);
            3:
              (*P*)
              OKp:= (1.0/(Rr*Tm1sec));
          END_CASE;
          
        END_IF;
        (* end of Tm2 *)
      ELSE
        (* work done success *)
        Ok:= 3;
      END_IF;
      (* end of TunDone *)
    ELSE
      (* incorrect regulator type *)
      Ok:= 2;
    END_IF;
    (* end of Ty *)
  ELSE
    (* off *)
    Ok:= 1;
  END_IF;
  (* end of Ex *)

  (* work *)
  IF Ok = 0 THEN
    OY         := 100.0;
    TONcont1_IN:= TRUE;
  END_IF;

  (* off, error *)
  IF Ok = 1 OR Ok = 2 THEN
    OY         := 0.0;
    TONcont1_IN:= FALSE;
    V1Set      := FALSE;
    TunDone    := FALSE;
    OKp        := 0.0;
    OKi        := 0.0;
    OKd        := 0.0;
    OTm        := 0;
  END_IF;

  (* work is done success *)
  IF TunDone = TRUE THEN
    OY         := 0.0;
  END_IF;

  TONcont1(IN:=TONcont1_IN);

  (* DEBUG *)
  (* set Class of debug variables to Output to use its as Outputs of the FB *)
  (* set Class of debug variables to Local to hide its *)
  (* Deb_V1 := V01; *)
  (* Deb_Tm1:= Tm1; *)
  (* Deb_V2 := V063; *)
  (* Deb_Tm2:= Tm2; *)
  (* end of DEBUG *)
END_FUNCTION_BLOCK

FUNCTION SetBitWo : WORD
  VAR_INPUT
    Wo : WORD := 0;
    Pos : BYTE := 0;
    Val : BOOL := FALSE;
  END_VAR
  VAR
    Mask : WORD := 0;
  END_VAR

  Mask:= REAL_TO_WORD(EXPT(INT_TO_REAL(2),BYTE_TO_INT(Pos)));
  IF Val = FALSE THEN
    SetBitWo:= (Wo AND NOT(Mask));
  ELSE
    SetBitWo:= (Wo OR Mask);
  END_IF;
END_FUNCTION

FUNCTION_BLOCK FiltrA
  VAR_INPUT
    Ex : BOOL := FALSE;
    V : REAL := 0.0;
    K : REAL := 0.0;
  END_VAR
  VAR_OUTPUT
    Ov : REAL := 0.0;
  END_VAR
  VAR
    Val : REAL := 0.0;
    Klim : REAL := 0.0;
  END_VAR

  IF Ex = TRUE THEN
    Klim:= LIMIT(MN:=0.0, IN:=K, MX:=1.0);
    Val := (Klim*V)+(1.0-Klim)*Ov;
  ELSE
    Val:= V;
  END_IF;

  Ov:= Val;
END_FUNCTION_BLOCK

FUNCTION_BLOCK PID1
  VAR_INPUT
    Ex : BOOL := FALSE;
    V : REAL := 0.0;
    Sp : REAL := 0.0;
    Ty : BYTE := 0;
    Pro : BYTE := 0;
    Kp : REAL := 0.0;
    Ki : REAL := 0.0;
    Kd : REAL := 0.0;
    Sck : BOOL := FALSE;
    dI : REAL := 0.0;
    dZ : REAL := 0.0;
    dE : REAL := 0.0;
    dETm : DWORD := 5000;
    Ym : BYTE := 0;
  END_VAR
  VAR_OUTPUT
    Ok : BYTE := 0;
    OY : REAL := 0.0;
  END_VAR
  VAR
    Er : REAL := 0.0;
    ErAbs : REAL := 0.0;
    ErPrev : REAL := 0.0;
    ErDiff : REAL := 0.0;
    Ppart : REAL := 0.0;
    Ipart : REAL := 0.0;
    Dpart : REAL := 0.0;
    DeV : REAL := 0.0;
    DeV1Set : BOOL := FALSE;
    DeV2Set : BOOL := FALSE;
    SckSet : BOOL := FALSE;
    ErrorSet : BOOL := FALSE;
    TON_De : TON;
    TON_De_IN : BOOL := FALSE;
    TON_De_TM : TIME := T#0ms;
  END_VAR

  (* Ty - regulator type *)
  (* = 0 - PID *)
  (* = 1 - PI *)
  (* = 2 - PD *)
  (* = 3 - P *)

  (* Pro - process type *)
  (* = 0 - increasing (by default) *)
  (* = 1 - decreasing *)

  (* Ym - type of OY *)
  (* = 0 - unipolar    0.0 .. 100.0 % (by default) *)
  (* = 1 - bipolar  -100.0 .. 100.0 % *)

  (* Ok - result code *)
  (* = 0 - work *)
  (* = 1 - off *)
  (* = 2 - dead (d-)zone *)
  (* = 3 - integral (i-)zone *)
  (* = 4 - control failure (e-)zone *)
  (* = 5 - incorrect regulator type *)

  (* reset Sck *)
  IF Sck = FALSE THEN
    SckSet:= FALSE;
  END_IF;

  (* test execution allow *)
  IF Ex = TRUE THEN
    
    (* test regulator type *)
    IF Ty <= 3 THEN
      
      (* test start *)
      IF Sck = TRUE AND SckSet = FALSE AND ErrorSet = FALSE THEN
        
        SckSet:= TRUE;
        
        (* work *)
        Ok:= 0;
       
        Er    := (Sp-V);
        ErDiff:= (Er-ErPrev);
        ErPrev:= Er;
        ErAbs := ABS(IN:=Er);
        
        (* test d-zone *)
        IF ErAbs >= dZ THEN
          
          (* Ty: 0-PID, 1-PI, 2-PD, 3-P *)
          Ppart:= (Kp*Er);
          
          (* Ty: 0-PID, 1-PI *)
          IF (Ty = 0 OR Ty = 1) AND (ErAbs < dI OR dI = 0.0) AND Ki > 0.0 THEN
            (* i-zone *)
            Ok:= 3;
            Ipart:= (Ipart+Er);
            IF Ipart >= Ki THEN
              Ipart:= Ki;
            END_IF;
            Ipart:= ((1.0/Ki)*Ipart);
          ELSE
            Ipart:= 0.0;
          END_IF;
          
          (*0-PID, 2-PD*)
          IF (Ty = 0 OR Ty = 2) THEN
            Dpart:= (Kd*ErDiff);
          ELSE
            Dpart:= 0.0;
          END_IF;
          
          OY:= (Ppart+Ipart+Dpart)*100.0;
          
        ELSE
          (* d-zone *)
          Ok:= 2;
        END_IF;
        (* end of test d-zone *)
        
      END_IF;
      (* end of test start *)
    
    ELSE
      (* incorrect regulator type *)
      Ok:= 5;
      ErrorSet:= TRUE;
    END_IF;
    (* end of test regulator type *)
    
  ELSE
    (* off *)
    Ok:= 1;
  END_IF;
  (* end of Ex *) 

  (* work, i-zone *)
  IF (Ok = 0 OR Ok = 3) AND ABS(IN:=OY) >= 100.0 THEN
      
    IF dETm > 0 THEN
      TON_De_TM:= REAL_TO_TIME(DWORD_TO_REAL(dETm)/1000.0);
      TON_De_IN:= TRUE;
    END_IF;
      
    IF DeV1Set = FALSE THEN
      (* point 1 *)
      DeV:= V;
      DeV1Set:= TRUE;
    END_IF;
      
    IF TON_De.Q = TRUE THEN
      IF DeV2Set = FALSE THEN
        (* point 2 *)
        DeV:= (V-DeV);
        DeV2Set:= TRUE;
      END_IF;
      IF DeV < dE OR DeV < 0.0 THEN
        (* e-zone *)
        Ok:= 4;
        ErrorSet:= TRUE;
      END_IF;
    END_IF;
    
  ELSE
    TON_De_IN:= FALSE;
    DeV1Set  := FALSE;
    DeV2Set  := FALSE;
  END_IF;

  (* off *)
  IF Ok = 1 THEN
    OY       := 0.0;
    SckSet   := FALSE;
    ErrorSet := FALSE;
    Ppart    := 0.0;
    Ipart    := 0.0;
    Dpart    := 0.0;
  END_IF;

  (* e-zone, error of regulator type *)
  IF ErrorSet = TRUE THEN
    OY       := 0.0;
  END_IF;

  (* scale OY by type of process *)
  IF Pro = 1 THEN
    (* decreasing *)
    OY:= (100.0-OY);
  END_IF;

  (* scale OY by type of output *)
  IF Ym = 1 THEN
    (* bipolar *)
    OY:= LIMIT(MN:=-100.0, IN:=OY, MX:=100.0);
  ELSE
    (* unipolar *)
    OY:= LIMIT(MN:=0.0, IN:=OY, MX:=100.0);
  END_IF;

  TON_De(IN:=TON_De_IN, PT:=TON_De_TM);

  (* DEBUG *)
  (* set Class of debug variables to Output to use its as Outputs of the FB *)
  (* set Class of debug variables to Local to hide its *)
  (* Deb_P   := Ppart; *)
  (* Deb_I   := Ipart; *)
  (* Deb_D   := Dpart; *)
  (* Deb_dEEt:= REAL_TO_DWORD(TIME_TO_REAL(TON_De.ET)*1000.0); *)
  (* end of DEBUG *)
END_FUNCTION_BLOCK

FUNCTION_BLOCK PID2
  VAR_INPUT
    Ex : BOOL := FALSE;
    V : REAL := 0.0;
    Sp : REAL := 0.0;
    Ty : BYTE := 0;
    Pro : BYTE := 0;
    Kp : REAL := 0.0;
    Ki : REAL := 0.0;
    Kd : REAL := 0.0;
    Tm : DWORD := 1000;
    dI : REAL := 0.0;
    dZ : REAL := 0.0;
    dE : REAL := 0.0;
    dETm : DWORD := 5000;
    Ym : BYTE := 0;
  END_VAR
  VAR_OUTPUT
    Ok : BYTE := 0;
    OY : REAL := 0.0;
  END_VAR
  VAR
    TON_Work : TON;
    TON_Work_IN : BOOL := FALSE;
    TON_Work_TM : TIME := T#0ms;
    PID1_1 : PID1;
  END_VAR

  PID1_1(Ex:=Ex, V:=V, Sp:=Sp, Ty:=Ty, Pro:=Pro, Kp:=Kp, Ki:=Ki, Kd:=Kd, Sck:=TON_Work.Q, dI:=dI, dZ:=dZ, dE:=dE, dETm:=dETm, Ym:=Ym);

  Ok:= PID1_1.Ok;
  OY:= PID1_1.OY;

  IF Ex = TRUE AND Tm > 0 THEN
    TON_Work_TM:= REAL_TO_TIME(DWORD_TO_REAL(Tm)/1000.0);
    TON_Work_IN:= TRUE;
  ELSE
    TON_Work_IN:= FALSE;
  END_IF;

  IF TON_Work.Q = TRUE THEN
    TON_Work_IN:= FALSE;
  END_IF;

  TON_Work(IN:=TON_Work_IN, PT:=TON_Work_TM);

  (* DEBUG *)
  (* set Class of debug variables to Output to use its as Outputs of the FB *)
  (* set Class of debug variables to Local to hide its *)
  (* Deb_P   := PID1_1.Deb_P; *)
  (* Deb_I   := PID1_1.Deb_I; *)
  (* Deb_D   := PID1_1.Deb_D; *)
  (* Deb_Et  := REAL_TO_DWORD(TIME_TO_REAL(TON_Work.ET)*1000.0); *)
  (* Deb_dEEt:= PID1_1.Deb_dEEt; *)
  (* end of DEBUG *)
END_FUNCTION_BLOCK

FUNCTION Dec : INT
  VAR_INPUT
    Ex : BOOL;
    V : INT;
  END_VAR
  VAR
    Val : INT;
  END_VAR

  Val:= V;

  IF Ex = True AND Val > 0 THEN
    Val:= V-1;
  END_IF;

  Dec:= Val;

END_FUNCTION

FUNCTION Inc : INT
  VAR_INPUT
    Ex : BOOL;
    V : INT;
  END_VAR
  VAR
    Val : INT;
  END_VAR

  Val:= V;

  IF Ex = True THEN
    Val:= V+1;
  END_IF;

  Inc:= Val;

END_FUNCTION



FUNCTION SoftReset : BOOL
  VAR_INPUT
    Ex : BOOL := FALSE;
  END_VAR

  {extern void AppSys_SoftReset(BOOL);AppSys_SoftReset(EX);}
  SoftReset:= TRUE;
END_FUNCTION



FUNCTION_BLOCK DICntT
  VAR_INPUT
    Ex : BOOL := FALSE;
    DIn : BYTE := 0;
    Ref : WORD := 0;
    RefEn : BOOL := FALSE;
  END_VAR
  VAR_OUTPUT
    Ov : WORD := 0;
    Oref : BOOL := FALSE;
    Ok : BYTE := 0;
  END_VAR

  {extern void App_DICntT(DICNTT*);App_DICntT(data__);}
END_FUNCTION_BLOCK

FUNCTION_BLOCK DICnt
  VAR_INPUT
    Ex : BOOL := FALSE;
    DIn : BYTE := 0;
    Ref : DWORD := 0;
    RefEn : BOOL := FALSE;
  END_VAR
  VAR_OUTPUT
    Ov : DWORD := 0;
    Oref : BOOL := FALSE;
    Ok : BYTE := 0;
  END_VAR

  {extern void App_DICnt(DICNT*);App_DICnt(data__);}
END_FUNCTION_BLOCK

FUNCTION_BLOCK DIEnc
  VAR_INPUT
    Ex : BOOL := FALSE;
    DIn : BYTE := 0;
    RefA : DWORD := 0;
    RefAEn : BOOL := FALSE;
    RefB : DWORD := 0;
    RefBEn : BOOL := FALSE;
    RefT : WORD := 0;
    RefTEn : BOOL := FALSE;
  END_VAR
  VAR_OUTPUT
    OA : DWORD := 0;
    OAref : BOOL := FALSE;
    OB : DWORD := 0;
    OBref : BOOL := FALSE;
    OT : WORD := 0;
    OTref : BOOL := FALSE;
    Ok : BYTE := 0;
  END_VAR

  {extern void App_DIEnc(DIENC*);App_DIEnc(data__);}
END_FUNCTION_BLOCK

FUNCTION_BLOCK DIVal
  VAR_INPUT
    Ex : BOOL := FALSE;
    DIn : BYTE := 0;
  END_VAR
  VAR_OUTPUT
    Ov : BOOL := FALSE;
    Ok : BYTE := 0;
  END_VAR

  {extern void App_DIVal(DIVAL*);App_DIVal(data__);}
END_FUNCTION_BLOCK

FUNCTION_BLOCK DICntRst
  VAR_INPUT
    Ex : BOOL := FALSE;
    DIn : BYTE := 0;
    Rst : BOOL := FALSE;
  END_VAR
  VAR_OUTPUT
    Ok : BYTE := 0;
  END_VAR

  {extern void App_DICntRst(DICNTRST*);App_DICntRst(data__);}
END_FUNCTION_BLOCK

FUNCTION_BLOCK DIMode
  VAR_INPUT
    Ex : BOOL := FALSE;
    DIn : BYTE := 0;
    M : BYTE := 0;
  END_VAR
  VAR_OUTPUT
    Om : BYTE := 0;
    Ok : BYTE := 0;
  END_VAR

  {extern void App_DIMode(DIMODE*);App_DIMode(data__);}
END_FUNCTION_BLOCK



FUNCTION_BLOCK DOPwm
  VAR_INPUT
    Ex : BOOL := FALSE;
    Enx : BOOL := FALSE;
    DOn : BYTE := 0;
    Tm : DWORD := 0;
    Du : REAL := 0.0;
  END_VAR
  VAR_OUTPUT
    Ow : BOOL := FALSE;
    Ok : BYTE := 0;
  END_VAR

  {extern void App_DOPwm(DOPWM*);App_DOPwm(data__);}
END_FUNCTION_BLOCK

FUNCTION_BLOCK DOSafe
  VAR_INPUT
    Ex : BOOL := FALSE;
    Enx : BOOL := FALSE;
    DOn : BYTE := 0;
    V : BOOL := FALSE;
  END_VAR
  VAR_OUTPUT
    Ov : BOOL := FALSE;
    Ow : BOOL := FALSE;
    Ok : BYTE := 0;
  END_VAR

  {extern void App_DOSafe(DOSAFE*);App_DOSafe(data__);}
END_FUNCTION_BLOCK

FUNCTION_BLOCK DOMode
  VAR_INPUT
    Ex : BOOL := FALSE;
    DOn : BYTE := 0;
    M : BYTE := 0;
  END_VAR
  VAR_OUTPUT
    Om : BYTE := 0;
    Ok : BYTE := 0;
  END_VAR

  {extern void App_DOMode(DOMODE*);App_DOMode(data__);}
END_FUNCTION_BLOCK

FUNCTION_BLOCK DOVal
  VAR_INPUT
    Ex : BOOL := FALSE;
    DOn : BYTE := 0;
    V : BOOL := FALSE;
  END_VAR
  VAR_OUTPUT
    Ov : BOOL := FALSE;
    Ok : BYTE := 0;
  END_VAR

  {extern void App_DOVal(DOVAL*);App_DOVal(data__);}
END_FUNCTION_BLOCK

FUNCTION_BLOCK DOFast
  VAR_INPUT
    Ex : BOOL := FALSE;
    DOn : BYTE := 0;
    V : BOOL := FALSE;
  END_VAR
  VAR_OUTPUT
    Ov : BOOL := FALSE;
    Ok : BYTE := 0;
  END_VAR

  {extern void App_DOFast(DOFAST*);App_DOFast(data__);}
END_FUNCTION_BLOCK



FUNCTION_BLOCK AIMode
  VAR_INPUT
    Ex : BOOL := FALSE;
    AIn : BYTE := 0;
    M : BYTE := 0;
  END_VAR
  VAR_OUTPUT
    Om : BYTE := 0;
    Os : BYTE := 0;
    Ok : BYTE := 0;
  END_VAR

  {extern void App_AIMode(AIMODE*);App_AIMode(data__);}
END_FUNCTION_BLOCK

FUNCTION_BLOCK AIVal
  VAR_INPUT
    Ex : BOOL := FALSE;
    AIn : BYTE := 0;
  END_VAR
  VAR_OUTPUT
    Ov : REAL := 0.0;
    Os : BYTE := 0;
    Ok : BYTE := 0;
  END_VAR

  {extern void App_AIVal(AIVAL*);App_AIVal(data__);}
END_FUNCTION_BLOCK



FUNCTION_BLOCK AOFast
  VAR_INPUT
    Ex : BOOL := FALSE;
    AOn : BYTE := 0;
    V : REAL := 0.0;
  END_VAR
  VAR_OUTPUT
    Ov : REAL := 0.0;
    Ok : BYTE := 0;
  END_VAR

  {extern void App_AOFast(AOFAST*);App_AOFast(data__);}
END_FUNCTION_BLOCK

FUNCTION_BLOCK AOMode
  VAR_INPUT
    Ex : BOOL := FALSE;
    AOn : BYTE := 0;
    M : BYTE := 0;
  END_VAR
  VAR_OUTPUT
    Om : BYTE := 0;
    Ok : BYTE := 0;
  END_VAR

  {extern void App_AOMode(AOMODE*);App_AOMode(data__);}
END_FUNCTION_BLOCK

FUNCTION_BLOCK AOVal
  VAR_INPUT
    Ex : BOOL := FALSE;
    AOn : BYTE := 0;
    V : REAL := 0.0;
  END_VAR
  VAR_OUTPUT
    Ov : REAL := 0.0;
    Ok : BYTE := 0;
  END_VAR

  {extern void App_AOVal(AOVAL*);App_AOVal(data__);}
END_FUNCTION_BLOCK

FUNCTION_BLOCK AOSafe
  VAR_INPUT
    Ex : BOOL := FALSE;
    Enx : BOOL := FALSE;
    AOn : BYTE := 0;
    V : REAL := 0.0;
  END_VAR
  VAR_OUTPUT
    Ov : REAL := 0.0;
    Ow : BOOL := FALSE;
    Ok : BYTE := 0;
  END_VAR

  {extern void App_AOSafe(AOSAFE*);App_AOSafe(data__);}
END_FUNCTION_BLOCK


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
