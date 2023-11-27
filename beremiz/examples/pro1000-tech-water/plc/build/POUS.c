void LOGGER_init__(LOGGER *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->TRIG,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->MSG,__STRING_LITERAL(0,""),retain)
  __INIT_VAR(data__->LEVEL,LOGLEVEL__INFO,retain)
  __INIT_VAR(data__->TRIG0,__BOOL_LITERAL(FALSE),retain)
}

// Code part
void LOGGER_body__(LOGGER *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }
  // Initialise TEMP variables

  if ((__GET_VAR(data__->TRIG,) && !(__GET_VAR(data__->TRIG0,)))) {
    #define GetFbVar(var,...) __GET_VAR(data__->var,__VA_ARGS__)
    #define SetFbVar(var,val,...) __SET_VAR(data__->,var,__VA_ARGS__,val)

   LogMessage(GetFbVar(LEVEL),(char*)GetFbVar(MSG, .body),GetFbVar(MSG, .len));
  
    #undef GetFbVar
    #undef SetFbVar
;
  };
  __SET_VAR(data__->,TRIG0,,__GET_VAR(data__->TRIG,));

  goto __end;

__end:
  return;
} // LOGGER_body__() 





// FUNCTION
REAL SCALEA(
  BOOL EN, 
  BOOL *__ENO, 
  BOOL EX, 
  REAL V, 
  REAL KA, 
  REAL KB, 
  REAL Y)
{
  BOOL ENO = __BOOL_LITERAL(TRUE);
  REAL SCALEA = 0;

  // Control execution
  if (!EN) {
    if (__ENO != NULL) {
      *__ENO = __BOOL_LITERAL(FALSE);
    }
    return SCALEA;
  }
  if ((EX == __BOOL_LITERAL(TRUE))) {
    SCALEA = ((KA * V) + KB);
  } else {
    SCALEA = Y;
  };

  goto __end;

__end:
  if (__ENO != NULL) {
    *__ENO = ENO;
  }
  return SCALEA;
}


// FUNCTION
REAL SCALEA_KB(
  BOOL EN, 
  BOOL *__ENO, 
  BOOL EX, 
  REAL V1, 
  REAL V2, 
  REAL Y1, 
  REAL Y2, 
  REAL KB)
{
  BOOL ENO = __BOOL_LITERAL(TRUE);
  REAL SCALEA_KB = 0;

  // Control execution
  if (!EN) {
    if (__ENO != NULL) {
      *__ENO = __BOOL_LITERAL(FALSE);
    }
    return SCALEA_KB;
  }
  if ((EX == __BOOL_LITERAL(TRUE))) {
    SCALEA_KB = (((Y1 * V2) - (Y2 * V1)) / (V2 - V1));
  } else {
    SCALEA_KB = KB;
  };

  goto __end;

__end:
  if (__ENO != NULL) {
    *__ENO = ENO;
  }
  return SCALEA_KB;
}


void TONTEST_init__(TONTEST *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->IN,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->MS,0,retain)
  __INIT_VAR(data__->Q,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->ET,__time_to_timespec(1, 0, 0, 0, 0, 0),retain)
  __INIT_VAR(data__->EDW,0,retain)
  __INIT_VAR(data__->EREA,0.0,retain)
  TON_init__(&data__->TON1,retain);
  __INIT_VAR(data__->TON1_IN,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->TON1_TM,__time_to_timespec(1, 0, 0, 0, 0, 0),retain)
}

// Code part
void TONTEST_body__(TONTEST *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }
  // Initialise TEMP variables

  __SET_VAR(data__->,TON1_IN,,__GET_VAR(data__->IN,));
  __SET_VAR(data__->,TON1_TM,,REAL_TO_TIME(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (REAL)(DWORD_TO_REAL(
      (BOOL)__BOOL_LITERAL(TRUE),
      NULL,
      (DWORD)__GET_VAR(data__->MS,)) / 1000.0)));
  __SET_VAR(data__->TON1.,IN,,__GET_VAR(data__->TON1_IN,));
  __SET_VAR(data__->TON1.,PT,,__GET_VAR(data__->TON1_TM,));
  TON_body__(&data__->TON1);
  __SET_VAR(data__->,Q,,__GET_VAR(data__->TON1.Q,));
  __SET_VAR(data__->,ET,,__GET_VAR(data__->TON1.ET,));
  __SET_VAR(data__->,EDW,,REAL_TO_DWORD(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (REAL)(TIME_TO_REAL(
      (BOOL)__BOOL_LITERAL(TRUE),
      NULL,
      (TIME)__GET_VAR(data__->TON1.ET,)) * 1000.0)));
  __SET_VAR(data__->,EREA,,TIME_TO_REAL(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (TIME)__GET_VAR(data__->TON1.ET,)));

  goto __end;

__end:
  return;
} // TONTEST_body__() 





// FUNCTION
REAL SCALEA_KA(
  BOOL EN, 
  BOOL *__ENO, 
  BOOL EX, 
  REAL V1, 
  REAL V2, 
  REAL Y1, 
  REAL Y2, 
  REAL KA)
{
  BOOL ENO = __BOOL_LITERAL(TRUE);
  REAL SCALEA_KA = 0;

  // Control execution
  if (!EN) {
    if (__ENO != NULL) {
      *__ENO = __BOOL_LITERAL(FALSE);
    }
    return SCALEA_KA;
  }
  if ((EX == __BOOL_LITERAL(TRUE))) {
    SCALEA_KA = ((Y2 - Y1) / (V2 - V1));
  } else {
    SCALEA_KA = KA;
  };

  goto __end;

__end:
  if (__ENO != NULL) {
    *__ENO = ENO;
  }
  return SCALEA_KA;
}


void TONCONT_init__(TONCONT *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->IN,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->Q,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->ET,__time_to_timespec(1, 0, 0, 0, 0, 0),retain)
  TON_init__(&data__->TON1,retain);
  __INIT_VAR(data__->TON1_IN,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->TON1_TM,__time_to_timespec(1, 600000, 0, 0, 0, 0),retain)
  TON_init__(&data__->TON1INC,retain);
  __INIT_VAR(data__->TON1INC_IN,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->TON1INC_TM,__time_to_timespec(1, 300000, 0, 0, 0, 0),retain)
}

// Code part
void TONCONT_body__(TONCONT *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }
  // Initialise TEMP variables

  __SET_VAR(data__->,TON1_IN,,__GET_VAR(data__->IN,));
  __SET_VAR(data__->,TON1INC_IN,,__GET_VAR(data__->IN,));
  if ((__GET_VAR(data__->TON1INC.Q,) == __BOOL_LITERAL(TRUE))) {
    __SET_VAR(data__->,TON1_TM,,ADD_TIME(
      (BOOL)__BOOL_LITERAL(TRUE),
      NULL,
      (TIME)__GET_VAR(data__->TON1_TM,),
      (TIME)__GET_VAR(data__->TON1INC_TM,)));
    __SET_VAR(data__->,TON1INC_IN,,__BOOL_LITERAL(FALSE));
  };
  __SET_VAR(data__->TON1.,IN,,__GET_VAR(data__->TON1_IN,));
  __SET_VAR(data__->TON1.,PT,,__GET_VAR(data__->TON1_TM,));
  TON_body__(&data__->TON1);
  __SET_VAR(data__->TON1INC.,IN,,__GET_VAR(data__->TON1INC_IN,));
  __SET_VAR(data__->TON1INC.,PT,,__GET_VAR(data__->TON1INC_TM,));
  TON_body__(&data__->TON1INC);
  __SET_VAR(data__->,Q,,__GET_VAR(data__->TON1.Q,));
  __SET_VAR(data__->,ET,,__GET_VAR(data__->TON1.ET,));

  goto __end;

__end:
  return;
} // TONCONT_body__() 





void FLRTUN_init__(FLRTUN *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->EX,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->V,0.0,retain)
  __INIT_VAR(data__->DIFF,0.0,retain)
  __INIT_VAR(data__->PRO,0,retain)
  __INIT_VAR(data__->OK,0,retain)
  __INIT_VAR(data__->OY,0.0,retain)
  __INIT_VAR(data__->OTM,0,retain)
  __INIT_VAR(data__->TUNDONE,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->TM1,0.0,retain)
  __INIT_VAR(data__->V1SET,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->V01,0.0,retain)
  TONCONT_init__(&data__->TONCONT1,retain);
  __INIT_VAR(data__->TONCONT1_IN,__BOOL_LITERAL(FALSE),retain)
}

// Code part
void FLRTUN_body__(FLRTUN *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }
  // Initialise TEMP variables

  if ((__GET_VAR(data__->EX,) == __BOOL_LITERAL(TRUE))) {
    if ((__GET_VAR(data__->TUNDONE,) == __BOOL_LITERAL(FALSE))) {
      __SET_VAR(data__->,OK,,0);
      if ((__GET_VAR(data__->V1SET,) == __BOOL_LITERAL(FALSE))) {
        __SET_VAR(data__->,V1SET,,__BOOL_LITERAL(TRUE));
        if ((__GET_VAR(data__->PRO,) == 1)) {
          __SET_VAR(data__->,V01,,(__GET_VAR(data__->V,) - (0.1 * __GET_VAR(data__->DIFF,))));
        } else {
          __SET_VAR(data__->,V01,,(__GET_VAR(data__->V,) + (0.1 * __GET_VAR(data__->DIFF,))));
        };
      };
      if ((__GET_VAR(data__->V,) < __GET_VAR(data__->V01,))) {
        __SET_VAR(data__->,TM1,,(TIME_TO_REAL(
          (BOOL)__BOOL_LITERAL(TRUE),
          NULL,
          (TIME)__GET_VAR(data__->TONCONT1.ET,)) * 1000.0));
      } else {
        __SET_VAR(data__->,OTM,,REAL_TO_DWORD(
          (BOOL)__BOOL_LITERAL(TRUE),
          NULL,
          (REAL)(__GET_VAR(data__->TM1,) * 1.875)));
        __SET_VAR(data__->,TUNDONE,,__BOOL_LITERAL(TRUE));
        __SET_VAR(data__->,OK,,3);
      };
    };
  } else {
    __SET_VAR(data__->,OK,,1);
  };
  if ((__GET_VAR(data__->OK,) == 0)) {
    __SET_VAR(data__->,OY,,100.0);
    __SET_VAR(data__->,TONCONT1_IN,,__BOOL_LITERAL(TRUE));
  };
  if ((__GET_VAR(data__->OK,) == 1)) {
    __SET_VAR(data__->,OY,,0.0);
    __SET_VAR(data__->,TONCONT1_IN,,__BOOL_LITERAL(FALSE));
    __SET_VAR(data__->,V1SET,,__BOOL_LITERAL(FALSE));
    __SET_VAR(data__->,TUNDONE,,__BOOL_LITERAL(FALSE));
    __SET_VAR(data__->,OTM,,0);
  };
  if ((__GET_VAR(data__->TUNDONE,) == __BOOL_LITERAL(TRUE))) {
    __SET_VAR(data__->,OY,,0.0);
    __SET_VAR(data__->,TONCONT1_IN,,__BOOL_LITERAL(FALSE));
  };
  __SET_VAR(data__->TONCONT1.,IN,,__GET_VAR(data__->TONCONT1_IN,));
  TONCONT_body__(&data__->TONCONT1);

  goto __end;

__end:
  return;
} // FLRTUN_body__() 





// FUNCTION
BOOL GETBITWO(
  BOOL EN, 
  BOOL *__ENO, 
  WORD WO, 
  BYTE POS)
{
  BOOL ENO = __BOOL_LITERAL(TRUE);
  WORD MASK = 0;
  BOOL GETBITWO = __BOOL_LITERAL(FALSE);

  // Control execution
  if (!EN) {
    if (__ENO != NULL) {
      *__ENO = __BOOL_LITERAL(FALSE);
    }
    return GETBITWO;
  }
  MASK = REAL_TO_WORD(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (REAL)EXPT__REAL__REAL__INT(
      (BOOL)__BOOL_LITERAL(TRUE),
      NULL,
      (REAL)INT_TO_REAL(
        (BOOL)__BOOL_LITERAL(TRUE),
        NULL,
        (INT)2),
      (INT)BYTE_TO_INT(
        (BOOL)__BOOL_LITERAL(TRUE),
        NULL,
        (BYTE)POS)));
  GETBITWO = ((WO & MASK) > 0);

  goto __end;

__end:
  if (__ENO != NULL) {
    *__ENO = ENO;
  }
  return GETBITWO;
}


void FILTRD_init__(FILTRD *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->EX,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->V,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->TM,__time_to_timespec(1, 0, 0, 0, 0, 0),retain)
  __INIT_VAR(data__->OV,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->VAL,__BOOL_LITERAL(FALSE),retain)
  TON_init__(&data__->TON0,retain);
  TON_init__(&data__->TON1,retain);
}

// Code part
void FILTRD_body__(FILTRD *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }
  // Initialise TEMP variables

  __SET_VAR(data__->TON0.,IN,,AND__BOOL__BOOL(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (UINT)2,
    (BOOL)__GET_VAR(data__->EX,),
    (BOOL)!(__GET_VAR(data__->V,))));
  __SET_VAR(data__->TON0.,PT,,__GET_VAR(data__->TM,));
  TON_body__(&data__->TON0);
  __SET_VAR(data__->TON1.,IN,,AND__BOOL__BOOL(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (UINT)2,
    (BOOL)__GET_VAR(data__->EX,),
    (BOOL)__GET_VAR(data__->V,)));
  __SET_VAR(data__->TON1.,PT,,__GET_VAR(data__->TM,));
  TON_body__(&data__->TON1);
  if ((__GET_VAR(data__->TON0.Q,) == __BOOL_LITERAL(TRUE))) {
    __SET_VAR(data__->,VAL,,__BOOL_LITERAL(FALSE));
  };
  if ((__GET_VAR(data__->TON1.Q,) == __BOOL_LITERAL(TRUE))) {
    __SET_VAR(data__->,VAL,,__BOOL_LITERAL(TRUE));
  };
  __SET_VAR(data__->,OV,,__GET_VAR(data__->VAL,));

  goto __end;

__end:
  return;
} // FILTRD_body__() 





void FLR1_init__(FLR1 *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->EX,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->V,0.0,retain)
  __INIT_VAR(data__->SP,0.0,retain)
  __INIT_VAR(data__->PRO,0,retain)
  __INIT_VAR(data__->SCK,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->TM,0,retain)
  __INIT_VAR(data__->DV,0.0,retain)
  __INIT_VAR(data__->DZ,0.0,retain)
  __INIT_VAR(data__->DE,0.0,retain)
  __INIT_VAR(data__->DETM,5000,retain)
  __INIT_VAR(data__->YM,0,retain)
  __INIT_VAR(data__->OK,0,retain)
  __INIT_VAR(data__->OY,0.0,retain)
  __INIT_VAR(data__->VPREV,0.0,retain)
  __INIT_VAR(data__->TMDV,0.0,retain)
  __INIT_VAR(data__->UPDOWN,0,retain)
  __INIT_VAR(data__->SCKSET,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->ERRORSET,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->ER,0.0,retain)
  TON_init__(&data__->TON_DE,retain);
  __INIT_VAR(data__->TON_DE_IN,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->TON_DE_TM,__time_to_timespec(1, 0, 0, 0, 0, 0),retain)
  __INIT_VAR(data__->DEV,0.0,retain)
  __INIT_VAR(data__->DEV1SET,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->DEV2SET,__BOOL_LITERAL(FALSE),retain)
  TON_init__(&data__->TON_DV,retain);
  __INIT_VAR(data__->TON_DV_IN,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->TON_DV_TM,__time_to_timespec(1, 0, 0, 0, 0, 0),retain)
}

// Code part
void FLR1_body__(FLR1 *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }
  // Initialise TEMP variables

  if ((__GET_VAR(data__->SCK,) == __BOOL_LITERAL(FALSE))) {
    __SET_VAR(data__->,SCKSET,,__BOOL_LITERAL(FALSE));
  };
  if ((__GET_VAR(data__->EX,) == __BOOL_LITERAL(TRUE))) {
    if ((((__GET_VAR(data__->SCK,) == __BOOL_LITERAL(TRUE)) && (__GET_VAR(data__->SCKSET,) == __BOOL_LITERAL(FALSE))) && (__GET_VAR(data__->ERRORSET,) == __BOOL_LITERAL(FALSE)))) {
      __SET_VAR(data__->,SCKSET,,__BOOL_LITERAL(TRUE));
      __SET_VAR(data__->,OK,,0);
      __SET_VAR(data__->,ER,,(__GET_VAR(data__->SP,) - __GET_VAR(data__->V,)));
      if ((ABS__REAL__REAL(
        (BOOL)__BOOL_LITERAL(TRUE),
        NULL,
        (REAL)__GET_VAR(data__->ER,)) >= __GET_VAR(data__->DZ,))) {
        #define GetFbVar(var,...) __GET_VAR(data__->var,__VA_ARGS__)
        #define SetFbVar(var,val,...) __SET_VAR(data__->,var,__VA_ARGS__,val)
extern void AppFlr(FLR1*);AppFlr(data__);
        #undef GetFbVar
        #undef SetFbVar
;
      } else {
        __SET_VAR(data__->,OK,,2);
      };
    };
  } else {
    __SET_VAR(data__->,OK,,1);
  };
  if ((__GET_VAR(data__->OK,) == 0)) {
    if ((__GET_VAR(data__->TMDV,) > 0.0)) {
      __SET_VAR(data__->,TON_DV_TM,,REAL_TO_TIME(
        (BOOL)__BOOL_LITERAL(TRUE),
        NULL,
        (REAL)(__GET_VAR(data__->TMDV,) / 1000.0)));
      __SET_VAR(data__->,TON_DV_IN,,__BOOL_LITERAL(TRUE));
    };
    if ((__GET_VAR(data__->TON_DV.Q,) == __BOOL_LITERAL(TRUE))) {
      __SET_VAR(data__->,TON_DV_IN,,__BOOL_LITERAL(FALSE));
      if ((__GET_VAR(data__->UPDOWN,) == -1)) {
        __SET_VAR(data__->,OY,,(__GET_VAR(data__->OY,) - __GET_VAR(data__->DV,)));
      };
      if ((__GET_VAR(data__->UPDOWN,) == 1)) {
        __SET_VAR(data__->,OY,,(__GET_VAR(data__->OY,) + __GET_VAR(data__->DV,)));
      };
    };
  } else {
    __SET_VAR(data__->,TON_DV_IN,,__BOOL_LITERAL(FALSE));
  };
  if (((__GET_VAR(data__->OK,) == 0) && (ABS__REAL__REAL(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (REAL)__GET_VAR(data__->OY,)) >= 100.0))) {
    if ((__GET_VAR(data__->DETM,) > 0)) {
      __SET_VAR(data__->,TON_DE_TM,,REAL_TO_TIME(
        (BOOL)__BOOL_LITERAL(TRUE),
        NULL,
        (REAL)(DWORD_TO_REAL(
          (BOOL)__BOOL_LITERAL(TRUE),
          NULL,
          (DWORD)__GET_VAR(data__->DETM,)) / 1000.0)));
      __SET_VAR(data__->,TON_DE_IN,,__BOOL_LITERAL(TRUE));
    };
    if ((__GET_VAR(data__->DEV1SET,) == __BOOL_LITERAL(FALSE))) {
      __SET_VAR(data__->,DEV,,__GET_VAR(data__->V,));
      __SET_VAR(data__->,DEV1SET,,__BOOL_LITERAL(TRUE));
    };
    if ((__GET_VAR(data__->TON_DE.Q,) == __BOOL_LITERAL(TRUE))) {
      if ((__GET_VAR(data__->DEV2SET,) == __BOOL_LITERAL(FALSE))) {
        __SET_VAR(data__->,DEV,,(__GET_VAR(data__->V,) - __GET_VAR(data__->DEV,)));
        __SET_VAR(data__->,DEV2SET,,__BOOL_LITERAL(TRUE));
      };
      if (((__GET_VAR(data__->DEV,) < __GET_VAR(data__->DE,)) || (__GET_VAR(data__->DEV,) < 0.0))) {
        __SET_VAR(data__->,OK,,4);
        __SET_VAR(data__->,ERRORSET,,__BOOL_LITERAL(TRUE));
      };
    };
  } else {
    __SET_VAR(data__->,TON_DE_IN,,__BOOL_LITERAL(FALSE));
    __SET_VAR(data__->,DEV1SET,,__BOOL_LITERAL(FALSE));
    __SET_VAR(data__->,DEV2SET,,__BOOL_LITERAL(FALSE));
  };
  if ((__GET_VAR(data__->OK,) == 1)) {
    __SET_VAR(data__->,OY,,0.0);
    __SET_VAR(data__->,SCKSET,,__BOOL_LITERAL(FALSE));
    __SET_VAR(data__->,ERRORSET,,__BOOL_LITERAL(FALSE));
    __SET_VAR(data__->,VPREV,,0.0);
  };
  if ((__GET_VAR(data__->ERRORSET,) == __BOOL_LITERAL(TRUE))) {
    __SET_VAR(data__->,OY,,0.0);
  };
  if ((__GET_VAR(data__->PRO,) == 1)) {
    __SET_VAR(data__->,OY,,(100.0 - __GET_VAR(data__->OY,)));
  };
  if ((__GET_VAR(data__->YM,) == 1)) {
    __SET_VAR(data__->,OY,,LIMIT__REAL__REAL__REAL__REAL(
      (BOOL)__BOOL_LITERAL(TRUE),
      NULL,
      (REAL)-100.0,
      (REAL)__GET_VAR(data__->OY,),
      (REAL)100.0));
  } else {
    __SET_VAR(data__->,OY,,LIMIT__REAL__REAL__REAL__REAL(
      (BOOL)__BOOL_LITERAL(TRUE),
      NULL,
      (REAL)0.0,
      (REAL)__GET_VAR(data__->OY,),
      (REAL)100.0));
  };
  __SET_VAR(data__->TON_DE.,IN,,__GET_VAR(data__->TON_DE_IN,));
  __SET_VAR(data__->TON_DE.,PT,,__GET_VAR(data__->TON_DE_TM,));
  TON_body__(&data__->TON_DE);
  __SET_VAR(data__->TON_DV.,IN,,__GET_VAR(data__->TON_DV_IN,));
  __SET_VAR(data__->TON_DV.,PT,,__GET_VAR(data__->TON_DV_TM,));
  TON_body__(&data__->TON_DV);

  goto __end;

__end:
  return;
} // FLR1_body__() 





void FLR2_init__(FLR2 *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->EX,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->V,0.0,retain)
  __INIT_VAR(data__->SP,0.0,retain)
  __INIT_VAR(data__->PRO,0,retain)
  __INIT_VAR(data__->TM,0,retain)
  __INIT_VAR(data__->DV,0.0,retain)
  __INIT_VAR(data__->DZ,0.0,retain)
  __INIT_VAR(data__->DE,0.0,retain)
  __INIT_VAR(data__->DETM,5000,retain)
  __INIT_VAR(data__->YM,0,retain)
  __INIT_VAR(data__->OK,0,retain)
  __INIT_VAR(data__->OY,0.0,retain)
  TON_init__(&data__->TON_WORK,retain);
  __INIT_VAR(data__->TON_WORK_IN,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->TON_WORK_TM,__time_to_timespec(1, 0, 0, 0, 0, 0),retain)
  FLR1_init__(&data__->FLR1_1,retain);
}

// Code part
void FLR2_body__(FLR2 *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }
  // Initialise TEMP variables

  __SET_VAR(data__->FLR1_1.,EX,,__GET_VAR(data__->EX,));
  __SET_VAR(data__->FLR1_1.,V,,__GET_VAR(data__->V,));
  __SET_VAR(data__->FLR1_1.,SP,,__GET_VAR(data__->SP,));
  __SET_VAR(data__->FLR1_1.,PRO,,__GET_VAR(data__->PRO,));
  __SET_VAR(data__->FLR1_1.,SCK,,__GET_VAR(data__->TON_WORK.Q,));
  __SET_VAR(data__->FLR1_1.,TM,,__GET_VAR(data__->TM,));
  __SET_VAR(data__->FLR1_1.,DV,,__GET_VAR(data__->DV,));
  __SET_VAR(data__->FLR1_1.,DZ,,__GET_VAR(data__->DZ,));
  __SET_VAR(data__->FLR1_1.,DE,,__GET_VAR(data__->DE,));
  __SET_VAR(data__->FLR1_1.,DETM,,__GET_VAR(data__->DETM,));
  __SET_VAR(data__->FLR1_1.,YM,,__GET_VAR(data__->YM,));
  FLR1_body__(&data__->FLR1_1);
  __SET_VAR(data__->,OK,,__GET_VAR(data__->FLR1_1.OK,));
  __SET_VAR(data__->,OY,,__GET_VAR(data__->FLR1_1.OY,));
  if (((__GET_VAR(data__->EX,) == __BOOL_LITERAL(TRUE)) && (__GET_VAR(data__->TM,) > 0))) {
    __SET_VAR(data__->,TON_WORK_TM,,REAL_TO_TIME(
      (BOOL)__BOOL_LITERAL(TRUE),
      NULL,
      (REAL)(DWORD_TO_REAL(
        (BOOL)__BOOL_LITERAL(TRUE),
        NULL,
        (DWORD)__GET_VAR(data__->TM,)) / 1000.0)));
    __SET_VAR(data__->,TON_WORK_IN,,__BOOL_LITERAL(TRUE));
  } else {
    __SET_VAR(data__->,TON_WORK_IN,,__BOOL_LITERAL(FALSE));
  };
  if ((__GET_VAR(data__->TON_WORK.Q,) == __BOOL_LITERAL(TRUE))) {
    __SET_VAR(data__->,TON_WORK_IN,,__BOOL_LITERAL(FALSE));
  };
  __SET_VAR(data__->TON_WORK.,IN,,__GET_VAR(data__->TON_WORK_IN,));
  __SET_VAR(data__->TON_WORK.,PT,,__GET_VAR(data__->TON_WORK_TM,));
  TON_body__(&data__->TON_WORK);

  goto __end;

__end:
  return;
} // FLR2_body__() 





void PIDTUN_init__(PIDTUN *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->EX,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->V,0.0,retain)
  __INIT_VAR(data__->DIFF,0.0,retain)
  __INIT_VAR(data__->TY,0,retain)
  __INIT_VAR(data__->PRO,0,retain)
  __INIT_VAR(data__->OK,0,retain)
  __INIT_VAR(data__->OY,0.0,retain)
  __INIT_VAR(data__->OKP,0.0,retain)
  __INIT_VAR(data__->OKI,0.0,retain)
  __INIT_VAR(data__->OKD,0.0,retain)
  __INIT_VAR(data__->OTM,0,retain)
  __INIT_VAR(data__->TUNDONE,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->TM1,0.0,retain)
  __INIT_VAR(data__->TM2,0.0,retain)
  __INIT_VAR(data__->TMSUM,0.0,retain)
  __INIT_VAR(data__->V1SET,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->V01,0.0,retain)
  __INIT_VAR(data__->V063,0.0,retain)
  __INIT_VAR(data__->RR,0.0,retain)
  __INIT_VAR(data__->TM1SEC,0.0,retain)
  TONCONT_init__(&data__->TONCONT1,retain);
  __INIT_VAR(data__->TONCONT1_IN,__BOOL_LITERAL(FALSE),retain)
}

// Code part
void PIDTUN_body__(PIDTUN *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }
  // Initialise TEMP variables

  if ((__GET_VAR(data__->EX,) == __BOOL_LITERAL(TRUE))) {
    if ((__GET_VAR(data__->TY,) <= 3)) {
      if ((__GET_VAR(data__->TUNDONE,) == __BOOL_LITERAL(FALSE))) {
        __SET_VAR(data__->,OK,,0);
        if ((__GET_VAR(data__->V1SET,) == __BOOL_LITERAL(FALSE))) {
          __SET_VAR(data__->,V1SET,,__BOOL_LITERAL(TRUE));
          if ((__GET_VAR(data__->PRO,) == 1)) {
            __SET_VAR(data__->,V01,,(__GET_VAR(data__->V,) - (0.1 * __GET_VAR(data__->DIFF,))));
            __SET_VAR(data__->,V063,,(__GET_VAR(data__->V,) - (0.63 * __GET_VAR(data__->DIFF,))));
          } else {
            __SET_VAR(data__->,V01,,(__GET_VAR(data__->V,) + (0.1 * __GET_VAR(data__->DIFF,))));
            __SET_VAR(data__->,V063,,(__GET_VAR(data__->V,) + (0.63 * __GET_VAR(data__->DIFF,))));
          };
        };
        if ((__GET_VAR(data__->V,) < __GET_VAR(data__->V01,))) {
          __SET_VAR(data__->,TM1,,(TIME_TO_REAL(
            (BOOL)__BOOL_LITERAL(TRUE),
            NULL,
            (TIME)__GET_VAR(data__->TONCONT1.ET,)) * 1000.0));
        };
        if ((__GET_VAR(data__->V,) >= __GET_VAR(data__->V063,))) {
          __SET_VAR(data__->,TONCONT1_IN,,__BOOL_LITERAL(FALSE));
          __SET_VAR(data__->,TUNDONE,,__BOOL_LITERAL(TRUE));
          __SET_VAR(data__->,TM2,,(TIME_TO_REAL(
            (BOOL)__BOOL_LITERAL(TRUE),
            NULL,
            (TIME)__GET_VAR(data__->TONCONT1.ET,)) * 1000.0));
          __SET_VAR(data__->,TMSUM,,(__GET_VAR(data__->TM1,) + __GET_VAR(data__->TM2,)));
          __SET_VAR(data__->,OTM,,REAL_TO_DWORD(
            (BOOL)__BOOL_LITERAL(TRUE),
            NULL,
            (REAL)(__GET_VAR(data__->TM1,) * 1.875)));
          __SET_VAR(data__->,RR,,(__GET_VAR(data__->DIFF,) / ((__GET_VAR(data__->TMSUM,) - __GET_VAR(data__->TM1,)) / 1000.0)));
          __SET_VAR(data__->,TM1SEC,,(__GET_VAR(data__->TM1,) / 1000.0));
          {
            INT __case_expression = BYTE_TO_INT(
              (BOOL)__BOOL_LITERAL(TRUE),
              NULL,
              (BYTE)__GET_VAR(data__->TY,));
            if ((__case_expression == 0)) {
              __SET_VAR(data__->,OKP,,(1.2 / (__GET_VAR(data__->RR,) * __GET_VAR(data__->TM1SEC,))));
              __SET_VAR(data__->,OKI,,(2.0 * __GET_VAR(data__->TM1SEC,)));
              __SET_VAR(data__->,OKD,,(0.4 * __GET_VAR(data__->TM1SEC,)));
            }
            else if ((__case_expression == 1)) {
              __SET_VAR(data__->,OKP,,(0.8 / (__GET_VAR(data__->RR,) * __GET_VAR(data__->TM1SEC,))));
              __SET_VAR(data__->,OKI,,(2.0 * __GET_VAR(data__->TM1SEC,)));
            }
            else if ((__case_expression == 2)) {
              __SET_VAR(data__->,OKP,,(1.0 / (__GET_VAR(data__->RR,) * __GET_VAR(data__->TM1SEC,))));
              __SET_VAR(data__->,OKD,,(0.25 * __GET_VAR(data__->TM1SEC,)));
            }
            else if ((__case_expression == 3)) {
              __SET_VAR(data__->,OKP,,(1.0 / (__GET_VAR(data__->RR,) * __GET_VAR(data__->TM1SEC,))));
            }
          };
        };
      } else {
        __SET_VAR(data__->,OK,,3);
      };
    } else {
      __SET_VAR(data__->,OK,,2);
    };
  } else {
    __SET_VAR(data__->,OK,,1);
  };
  if ((__GET_VAR(data__->OK,) == 0)) {
    __SET_VAR(data__->,OY,,100.0);
    __SET_VAR(data__->,TONCONT1_IN,,__BOOL_LITERAL(TRUE));
  };
  if (((__GET_VAR(data__->OK,) == 1) || (__GET_VAR(data__->OK,) == 2))) {
    __SET_VAR(data__->,OY,,0.0);
    __SET_VAR(data__->,TONCONT1_IN,,__BOOL_LITERAL(FALSE));
    __SET_VAR(data__->,V1SET,,__BOOL_LITERAL(FALSE));
    __SET_VAR(data__->,TUNDONE,,__BOOL_LITERAL(FALSE));
    __SET_VAR(data__->,OKP,,0.0);
    __SET_VAR(data__->,OKI,,0.0);
    __SET_VAR(data__->,OKD,,0.0);
    __SET_VAR(data__->,OTM,,0);
  };
  if ((__GET_VAR(data__->TUNDONE,) == __BOOL_LITERAL(TRUE))) {
    __SET_VAR(data__->,OY,,0.0);
  };
  __SET_VAR(data__->TONCONT1.,IN,,__GET_VAR(data__->TONCONT1_IN,));
  TONCONT_body__(&data__->TONCONT1);

  goto __end;

__end:
  return;
} // PIDTUN_body__() 





// FUNCTION
WORD SETBITWO(
  BOOL EN, 
  BOOL *__ENO, 
  WORD WO, 
  BYTE POS, 
  BOOL VAL)
{
  BOOL ENO = __BOOL_LITERAL(TRUE);
  WORD MASK = 0;
  WORD SETBITWO = 0;

  // Control execution
  if (!EN) {
    if (__ENO != NULL) {
      *__ENO = __BOOL_LITERAL(FALSE);
    }
    return SETBITWO;
  }
  MASK = REAL_TO_WORD(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (REAL)EXPT__REAL__REAL__INT(
      (BOOL)__BOOL_LITERAL(TRUE),
      NULL,
      (REAL)INT_TO_REAL(
        (BOOL)__BOOL_LITERAL(TRUE),
        NULL,
        (INT)2),
      (INT)BYTE_TO_INT(
        (BOOL)__BOOL_LITERAL(TRUE),
        NULL,
        (BYTE)POS)));
  if ((VAL == __BOOL_LITERAL(FALSE))) {
    SETBITWO = (WO & ~(MASK));
  } else {
    SETBITWO = (WO | MASK);
  };

  goto __end;

__end:
  if (__ENO != NULL) {
    *__ENO = ENO;
  }
  return SETBITWO;
}


void FILTRA_init__(FILTRA *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->EX,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->V,0.0,retain)
  __INIT_VAR(data__->K,0.0,retain)
  __INIT_VAR(data__->OV,0.0,retain)
  __INIT_VAR(data__->VAL,0.0,retain)
  __INIT_VAR(data__->KLIM,0.0,retain)
}

// Code part
void FILTRA_body__(FILTRA *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }
  // Initialise TEMP variables

  if ((__GET_VAR(data__->EX,) == __BOOL_LITERAL(TRUE))) {
    __SET_VAR(data__->,KLIM,,LIMIT__REAL__REAL__REAL__REAL(
      (BOOL)__BOOL_LITERAL(TRUE),
      NULL,
      (REAL)0.0,
      (REAL)__GET_VAR(data__->K,),
      (REAL)1.0));
    __SET_VAR(data__->,VAL,,((__GET_VAR(data__->KLIM,) * __GET_VAR(data__->V,)) + ((1.0 - __GET_VAR(data__->KLIM,)) * __GET_VAR(data__->OV,))));
  } else {
    __SET_VAR(data__->,VAL,,__GET_VAR(data__->V,));
  };
  __SET_VAR(data__->,OV,,__GET_VAR(data__->VAL,));

  goto __end;

__end:
  return;
} // FILTRA_body__() 





void PID1_init__(PID1 *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->EX,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->V,0.0,retain)
  __INIT_VAR(data__->SP,0.0,retain)
  __INIT_VAR(data__->TY,0,retain)
  __INIT_VAR(data__->PRO,0,retain)
  __INIT_VAR(data__->KP,0.0,retain)
  __INIT_VAR(data__->KI,0.0,retain)
  __INIT_VAR(data__->KD,0.0,retain)
  __INIT_VAR(data__->SCK,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->DI,0.0,retain)
  __INIT_VAR(data__->DZ,0.0,retain)
  __INIT_VAR(data__->DE,0.0,retain)
  __INIT_VAR(data__->DETM,5000,retain)
  __INIT_VAR(data__->YM,0,retain)
  __INIT_VAR(data__->OK,0,retain)
  __INIT_VAR(data__->OY,0.0,retain)
  __INIT_VAR(data__->ER,0.0,retain)
  __INIT_VAR(data__->ERABS,0.0,retain)
  __INIT_VAR(data__->ERPREV,0.0,retain)
  __INIT_VAR(data__->ERDIFF,0.0,retain)
  __INIT_VAR(data__->PPART,0.0,retain)
  __INIT_VAR(data__->IPART,0.0,retain)
  __INIT_VAR(data__->DPART,0.0,retain)
  __INIT_VAR(data__->DEV,0.0,retain)
  __INIT_VAR(data__->DEV1SET,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->DEV2SET,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->SCKSET,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->ERRORSET,__BOOL_LITERAL(FALSE),retain)
  TON_init__(&data__->TON_DE,retain);
  __INIT_VAR(data__->TON_DE_IN,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->TON_DE_TM,__time_to_timespec(1, 0, 0, 0, 0, 0),retain)
}

// Code part
void PID1_body__(PID1 *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }
  // Initialise TEMP variables

  if ((__GET_VAR(data__->SCK,) == __BOOL_LITERAL(FALSE))) {
    __SET_VAR(data__->,SCKSET,,__BOOL_LITERAL(FALSE));
  };
  if ((__GET_VAR(data__->EX,) == __BOOL_LITERAL(TRUE))) {
    if ((__GET_VAR(data__->TY,) <= 3)) {
      if ((((__GET_VAR(data__->SCK,) == __BOOL_LITERAL(TRUE)) && (__GET_VAR(data__->SCKSET,) == __BOOL_LITERAL(FALSE))) && (__GET_VAR(data__->ERRORSET,) == __BOOL_LITERAL(FALSE)))) {
        __SET_VAR(data__->,SCKSET,,__BOOL_LITERAL(TRUE));
        __SET_VAR(data__->,OK,,0);
        __SET_VAR(data__->,ER,,(__GET_VAR(data__->SP,) - __GET_VAR(data__->V,)));
        __SET_VAR(data__->,ERDIFF,,(__GET_VAR(data__->ER,) - __GET_VAR(data__->ERPREV,)));
        __SET_VAR(data__->,ERPREV,,__GET_VAR(data__->ER,));
        __SET_VAR(data__->,ERABS,,ABS__REAL__REAL(
          (BOOL)__BOOL_LITERAL(TRUE),
          NULL,
          (REAL)__GET_VAR(data__->ER,)));
        if ((__GET_VAR(data__->ERABS,) >= __GET_VAR(data__->DZ,))) {
          __SET_VAR(data__->,PPART,,(__GET_VAR(data__->KP,) * __GET_VAR(data__->ER,)));
          if (((((__GET_VAR(data__->TY,) == 0) || (__GET_VAR(data__->TY,) == 1)) && ((__GET_VAR(data__->ERABS,) < __GET_VAR(data__->DI,)) || (__GET_VAR(data__->DI,) == 0.0))) && (__GET_VAR(data__->KI,) > 0.0))) {
            __SET_VAR(data__->,OK,,3);
            __SET_VAR(data__->,IPART,,(__GET_VAR(data__->IPART,) + __GET_VAR(data__->ER,)));
            if ((__GET_VAR(data__->IPART,) >= __GET_VAR(data__->KI,))) {
              __SET_VAR(data__->,IPART,,__GET_VAR(data__->KI,));
            };
            __SET_VAR(data__->,IPART,,((1.0 / __GET_VAR(data__->KI,)) * __GET_VAR(data__->IPART,)));
          } else {
            __SET_VAR(data__->,IPART,,0.0);
          };
          if (((__GET_VAR(data__->TY,) == 0) || (__GET_VAR(data__->TY,) == 2))) {
            __SET_VAR(data__->,DPART,,(__GET_VAR(data__->KD,) * __GET_VAR(data__->ERDIFF,)));
          } else {
            __SET_VAR(data__->,DPART,,0.0);
          };
          __SET_VAR(data__->,OY,,(((__GET_VAR(data__->PPART,) + __GET_VAR(data__->IPART,)) + __GET_VAR(data__->DPART,)) * 100.0));
        } else {
          __SET_VAR(data__->,OK,,2);
        };
      };
    } else {
      __SET_VAR(data__->,OK,,5);
      __SET_VAR(data__->,ERRORSET,,__BOOL_LITERAL(TRUE));
    };
  } else {
    __SET_VAR(data__->,OK,,1);
  };
  if ((((__GET_VAR(data__->OK,) == 0) || (__GET_VAR(data__->OK,) == 3)) && (ABS__REAL__REAL(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (REAL)__GET_VAR(data__->OY,)) >= 100.0))) {
    if ((__GET_VAR(data__->DETM,) > 0)) {
      __SET_VAR(data__->,TON_DE_TM,,REAL_TO_TIME(
        (BOOL)__BOOL_LITERAL(TRUE),
        NULL,
        (REAL)(DWORD_TO_REAL(
          (BOOL)__BOOL_LITERAL(TRUE),
          NULL,
          (DWORD)__GET_VAR(data__->DETM,)) / 1000.0)));
      __SET_VAR(data__->,TON_DE_IN,,__BOOL_LITERAL(TRUE));
    };
    if ((__GET_VAR(data__->DEV1SET,) == __BOOL_LITERAL(FALSE))) {
      __SET_VAR(data__->,DEV,,__GET_VAR(data__->V,));
      __SET_VAR(data__->,DEV1SET,,__BOOL_LITERAL(TRUE));
    };
    if ((__GET_VAR(data__->TON_DE.Q,) == __BOOL_LITERAL(TRUE))) {
      if ((__GET_VAR(data__->DEV2SET,) == __BOOL_LITERAL(FALSE))) {
        __SET_VAR(data__->,DEV,,(__GET_VAR(data__->V,) - __GET_VAR(data__->DEV,)));
        __SET_VAR(data__->,DEV2SET,,__BOOL_LITERAL(TRUE));
      };
      if (((__GET_VAR(data__->DEV,) < __GET_VAR(data__->DE,)) || (__GET_VAR(data__->DEV,) < 0.0))) {
        __SET_VAR(data__->,OK,,4);
        __SET_VAR(data__->,ERRORSET,,__BOOL_LITERAL(TRUE));
      };
    };
  } else {
    __SET_VAR(data__->,TON_DE_IN,,__BOOL_LITERAL(FALSE));
    __SET_VAR(data__->,DEV1SET,,__BOOL_LITERAL(FALSE));
    __SET_VAR(data__->,DEV2SET,,__BOOL_LITERAL(FALSE));
  };
  if ((__GET_VAR(data__->OK,) == 1)) {
    __SET_VAR(data__->,OY,,0.0);
    __SET_VAR(data__->,SCKSET,,__BOOL_LITERAL(FALSE));
    __SET_VAR(data__->,ERRORSET,,__BOOL_LITERAL(FALSE));
    __SET_VAR(data__->,PPART,,0.0);
    __SET_VAR(data__->,IPART,,0.0);
    __SET_VAR(data__->,DPART,,0.0);
  };
  if ((__GET_VAR(data__->ERRORSET,) == __BOOL_LITERAL(TRUE))) {
    __SET_VAR(data__->,OY,,0.0);
  };
  if ((__GET_VAR(data__->PRO,) == 1)) {
    __SET_VAR(data__->,OY,,(100.0 - __GET_VAR(data__->OY,)));
  };
  if ((__GET_VAR(data__->YM,) == 1)) {
    __SET_VAR(data__->,OY,,LIMIT__REAL__REAL__REAL__REAL(
      (BOOL)__BOOL_LITERAL(TRUE),
      NULL,
      (REAL)-100.0,
      (REAL)__GET_VAR(data__->OY,),
      (REAL)100.0));
  } else {
    __SET_VAR(data__->,OY,,LIMIT__REAL__REAL__REAL__REAL(
      (BOOL)__BOOL_LITERAL(TRUE),
      NULL,
      (REAL)0.0,
      (REAL)__GET_VAR(data__->OY,),
      (REAL)100.0));
  };
  __SET_VAR(data__->TON_DE.,IN,,__GET_VAR(data__->TON_DE_IN,));
  __SET_VAR(data__->TON_DE.,PT,,__GET_VAR(data__->TON_DE_TM,));
  TON_body__(&data__->TON_DE);

  goto __end;

__end:
  return;
} // PID1_body__() 





void PID2_init__(PID2 *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->EX,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->V,0.0,retain)
  __INIT_VAR(data__->SP,0.0,retain)
  __INIT_VAR(data__->TY,0,retain)
  __INIT_VAR(data__->PRO,0,retain)
  __INIT_VAR(data__->KP,0.0,retain)
  __INIT_VAR(data__->KI,0.0,retain)
  __INIT_VAR(data__->KD,0.0,retain)
  __INIT_VAR(data__->TM,1000,retain)
  __INIT_VAR(data__->DI,0.0,retain)
  __INIT_VAR(data__->DZ,0.0,retain)
  __INIT_VAR(data__->DE,0.0,retain)
  __INIT_VAR(data__->DETM,5000,retain)
  __INIT_VAR(data__->YM,0,retain)
  __INIT_VAR(data__->OK,0,retain)
  __INIT_VAR(data__->OY,0.0,retain)
  TON_init__(&data__->TON_WORK,retain);
  __INIT_VAR(data__->TON_WORK_IN,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->TON_WORK_TM,__time_to_timespec(1, 0, 0, 0, 0, 0),retain)
  PID1_init__(&data__->PID1_1,retain);
}

// Code part
void PID2_body__(PID2 *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }
  // Initialise TEMP variables

  __SET_VAR(data__->PID1_1.,EX,,__GET_VAR(data__->EX,));
  __SET_VAR(data__->PID1_1.,V,,__GET_VAR(data__->V,));
  __SET_VAR(data__->PID1_1.,SP,,__GET_VAR(data__->SP,));
  __SET_VAR(data__->PID1_1.,TY,,__GET_VAR(data__->TY,));
  __SET_VAR(data__->PID1_1.,PRO,,__GET_VAR(data__->PRO,));
  __SET_VAR(data__->PID1_1.,KP,,__GET_VAR(data__->KP,));
  __SET_VAR(data__->PID1_1.,KI,,__GET_VAR(data__->KI,));
  __SET_VAR(data__->PID1_1.,KD,,__GET_VAR(data__->KD,));
  __SET_VAR(data__->PID1_1.,SCK,,__GET_VAR(data__->TON_WORK.Q,));
  __SET_VAR(data__->PID1_1.,DI,,__GET_VAR(data__->DI,));
  __SET_VAR(data__->PID1_1.,DZ,,__GET_VAR(data__->DZ,));
  __SET_VAR(data__->PID1_1.,DE,,__GET_VAR(data__->DE,));
  __SET_VAR(data__->PID1_1.,DETM,,__GET_VAR(data__->DETM,));
  __SET_VAR(data__->PID1_1.,YM,,__GET_VAR(data__->YM,));
  PID1_body__(&data__->PID1_1);
  __SET_VAR(data__->,OK,,__GET_VAR(data__->PID1_1.OK,));
  __SET_VAR(data__->,OY,,__GET_VAR(data__->PID1_1.OY,));
  if (((__GET_VAR(data__->EX,) == __BOOL_LITERAL(TRUE)) && (__GET_VAR(data__->TM,) > 0))) {
    __SET_VAR(data__->,TON_WORK_TM,,REAL_TO_TIME(
      (BOOL)__BOOL_LITERAL(TRUE),
      NULL,
      (REAL)(DWORD_TO_REAL(
        (BOOL)__BOOL_LITERAL(TRUE),
        NULL,
        (DWORD)__GET_VAR(data__->TM,)) / 1000.0)));
    __SET_VAR(data__->,TON_WORK_IN,,__BOOL_LITERAL(TRUE));
  } else {
    __SET_VAR(data__->,TON_WORK_IN,,__BOOL_LITERAL(FALSE));
  };
  if ((__GET_VAR(data__->TON_WORK.Q,) == __BOOL_LITERAL(TRUE))) {
    __SET_VAR(data__->,TON_WORK_IN,,__BOOL_LITERAL(FALSE));
  };
  __SET_VAR(data__->TON_WORK.,IN,,__GET_VAR(data__->TON_WORK_IN,));
  __SET_VAR(data__->TON_WORK.,PT,,__GET_VAR(data__->TON_WORK_TM,));
  TON_body__(&data__->TON_WORK);

  goto __end;

__end:
  return;
} // PID2_body__() 





// FUNCTION
INT DEC(
  BOOL EN, 
  BOOL *__ENO, 
  BOOL EX, 
  INT V)
{
  BOOL ENO = __BOOL_LITERAL(TRUE);
  INT VAL = 0;
  INT DEC = 0;

  // Control execution
  if (!EN) {
    if (__ENO != NULL) {
      *__ENO = __BOOL_LITERAL(FALSE);
    }
    return DEC;
  }
  VAL = V;
  if (((EX == __BOOL_LITERAL(TRUE)) && (VAL > 0))) {
    VAL = (V - 1);
  };
  DEC = VAL;

  goto __end;

__end:
  if (__ENO != NULL) {
    *__ENO = ENO;
  }
  return DEC;
}


// FUNCTION
INT INC(
  BOOL EN, 
  BOOL *__ENO, 
  BOOL EX, 
  INT V)
{
  BOOL ENO = __BOOL_LITERAL(TRUE);
  INT VAL = 0;
  INT INC = 0;

  // Control execution
  if (!EN) {
    if (__ENO != NULL) {
      *__ENO = __BOOL_LITERAL(FALSE);
    }
    return INC;
  }
  VAL = V;
  if ((EX == __BOOL_LITERAL(TRUE))) {
    VAL = (V + 1);
  };
  INC = VAL;

  goto __end;

__end:
  if (__ENO != NULL) {
    *__ENO = ENO;
  }
  return INC;
}


// FUNCTION
BOOL SOFTRESET(
  BOOL EN, 
  BOOL *__ENO, 
  BOOL EX)
{
  BOOL ENO = __BOOL_LITERAL(TRUE);
  BOOL SOFTRESET = __BOOL_LITERAL(FALSE);

  // Control execution
  if (!EN) {
    if (__ENO != NULL) {
      *__ENO = __BOOL_LITERAL(FALSE);
    }
    return SOFTRESET;
  }
  #define GetFbVar(var,...) __GET_VAR(data__->var,__VA_ARGS__)
  #define SetFbVar(var,val,...) __SET_VAR(data__->,var,__VA_ARGS__,val)
extern void AppSys_SoftReset(BOOL);AppSys_SoftReset(EX);
  #undef GetFbVar
  #undef SetFbVar
;
  SOFTRESET = __BOOL_LITERAL(TRUE);

  goto __end;

__end:
  if (__ENO != NULL) {
    *__ENO = ENO;
  }
  return SOFTRESET;
}


void DICNTT_init__(DICNTT *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->EX,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->DIN,0,retain)
  __INIT_VAR(data__->REF,0,retain)
  __INIT_VAR(data__->REFEN,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->OV,0,retain)
  __INIT_VAR(data__->OREF,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->OK,0,retain)
}

// Code part
void DICNTT_body__(DICNTT *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }
  // Initialise TEMP variables

  __IL_DEFVAR_T __IL_DEFVAR;
  __IL_DEFVAR_T __IL_DEFVAR_BACK;
  #define GetFbVar(var,...) __GET_VAR(data__->var,__VA_ARGS__)
  #define SetFbVar(var,val,...) __SET_VAR(data__->,var,__VA_ARGS__,val)
extern void App_DICntT(DICNTT*);App_DICntT(data__);
  #undef GetFbVar
  #undef SetFbVar
;

  goto __end;

__end:
  return;
} // DICNTT_body__() 





void DICNT_init__(DICNT *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->EX,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->DIN,0,retain)
  __INIT_VAR(data__->REF,0,retain)
  __INIT_VAR(data__->REFEN,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->OV,0,retain)
  __INIT_VAR(data__->OREF,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->OK,0,retain)
}

// Code part
void DICNT_body__(DICNT *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }
  // Initialise TEMP variables

  __IL_DEFVAR_T __IL_DEFVAR;
  __IL_DEFVAR_T __IL_DEFVAR_BACK;
  #define GetFbVar(var,...) __GET_VAR(data__->var,__VA_ARGS__)
  #define SetFbVar(var,val,...) __SET_VAR(data__->,var,__VA_ARGS__,val)
extern void App_DICnt(DICNT*);App_DICnt(data__);
  #undef GetFbVar
  #undef SetFbVar
;

  goto __end;

__end:
  return;
} // DICNT_body__() 





void DIENC_init__(DIENC *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->EX,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->DIN,0,retain)
  __INIT_VAR(data__->REFA,0,retain)
  __INIT_VAR(data__->REFAEN,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->REFB,0,retain)
  __INIT_VAR(data__->REFBEN,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->REFT,0,retain)
  __INIT_VAR(data__->REFTEN,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->OA,0,retain)
  __INIT_VAR(data__->OAREF,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->OB,0,retain)
  __INIT_VAR(data__->OBREF,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->OT,0,retain)
  __INIT_VAR(data__->OTREF,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->OK,0,retain)
}

// Code part
void DIENC_body__(DIENC *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }
  // Initialise TEMP variables

  __IL_DEFVAR_T __IL_DEFVAR;
  __IL_DEFVAR_T __IL_DEFVAR_BACK;
  #define GetFbVar(var,...) __GET_VAR(data__->var,__VA_ARGS__)
  #define SetFbVar(var,val,...) __SET_VAR(data__->,var,__VA_ARGS__,val)
extern void App_DIEnc(DIENC*);App_DIEnc(data__);
  #undef GetFbVar
  #undef SetFbVar
;

  goto __end;

__end:
  return;
} // DIENC_body__() 





void DIVAL_init__(DIVAL *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->EX,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->DIN,0,retain)
  __INIT_VAR(data__->OV,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->OK,0,retain)
}

// Code part
void DIVAL_body__(DIVAL *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }
  // Initialise TEMP variables

  __IL_DEFVAR_T __IL_DEFVAR;
  __IL_DEFVAR_T __IL_DEFVAR_BACK;
  #define GetFbVar(var,...) __GET_VAR(data__->var,__VA_ARGS__)
  #define SetFbVar(var,val,...) __SET_VAR(data__->,var,__VA_ARGS__,val)
extern void App_DIVal(DIVAL*);App_DIVal(data__);
  #undef GetFbVar
  #undef SetFbVar
;

  goto __end;

__end:
  return;
} // DIVAL_body__() 





void DICNTRST_init__(DICNTRST *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->EX,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->DIN,0,retain)
  __INIT_VAR(data__->RST,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->OK,0,retain)
}

// Code part
void DICNTRST_body__(DICNTRST *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }
  // Initialise TEMP variables

  __IL_DEFVAR_T __IL_DEFVAR;
  __IL_DEFVAR_T __IL_DEFVAR_BACK;
  #define GetFbVar(var,...) __GET_VAR(data__->var,__VA_ARGS__)
  #define SetFbVar(var,val,...) __SET_VAR(data__->,var,__VA_ARGS__,val)
extern void App_DICntRst(DICNTRST*);App_DICntRst(data__);
  #undef GetFbVar
  #undef SetFbVar
;

  goto __end;

__end:
  return;
} // DICNTRST_body__() 





void DIMODE_init__(DIMODE *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->EX,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->DIN,0,retain)
  __INIT_VAR(data__->M,0,retain)
  __INIT_VAR(data__->OM,0,retain)
  __INIT_VAR(data__->OK,0,retain)
}

// Code part
void DIMODE_body__(DIMODE *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }
  // Initialise TEMP variables

  __IL_DEFVAR_T __IL_DEFVAR;
  __IL_DEFVAR_T __IL_DEFVAR_BACK;
  #define GetFbVar(var,...) __GET_VAR(data__->var,__VA_ARGS__)
  #define SetFbVar(var,val,...) __SET_VAR(data__->,var,__VA_ARGS__,val)
extern void App_DIMode(DIMODE*);App_DIMode(data__);
  #undef GetFbVar
  #undef SetFbVar
;

  goto __end;

__end:
  return;
} // DIMODE_body__() 





void DOPWM_init__(DOPWM *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->EX,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->ENX,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->DON,0,retain)
  __INIT_VAR(data__->TM,0,retain)
  __INIT_VAR(data__->DU,0.0,retain)
  __INIT_VAR(data__->OW,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->OK,0,retain)
}

// Code part
void DOPWM_body__(DOPWM *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }
  // Initialise TEMP variables

  __IL_DEFVAR_T __IL_DEFVAR;
  __IL_DEFVAR_T __IL_DEFVAR_BACK;
  #define GetFbVar(var,...) __GET_VAR(data__->var,__VA_ARGS__)
  #define SetFbVar(var,val,...) __SET_VAR(data__->,var,__VA_ARGS__,val)
extern void App_DOPwm(DOPWM*);App_DOPwm(data__);
  #undef GetFbVar
  #undef SetFbVar
;

  goto __end;

__end:
  return;
} // DOPWM_body__() 





void DOSAFE_init__(DOSAFE *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->EX,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->ENX,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->DON,0,retain)
  __INIT_VAR(data__->V,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->OV,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->OW,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->OK,0,retain)
}

// Code part
void DOSAFE_body__(DOSAFE *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }
  // Initialise TEMP variables

  __IL_DEFVAR_T __IL_DEFVAR;
  __IL_DEFVAR_T __IL_DEFVAR_BACK;
  #define GetFbVar(var,...) __GET_VAR(data__->var,__VA_ARGS__)
  #define SetFbVar(var,val,...) __SET_VAR(data__->,var,__VA_ARGS__,val)
extern void App_DOSafe(DOSAFE*);App_DOSafe(data__);
  #undef GetFbVar
  #undef SetFbVar
;

  goto __end;

__end:
  return;
} // DOSAFE_body__() 





void DOMODE_init__(DOMODE *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->EX,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->DON,0,retain)
  __INIT_VAR(data__->M,0,retain)
  __INIT_VAR(data__->OM,0,retain)
  __INIT_VAR(data__->OK,0,retain)
}

// Code part
void DOMODE_body__(DOMODE *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }
  // Initialise TEMP variables

  __IL_DEFVAR_T __IL_DEFVAR;
  __IL_DEFVAR_T __IL_DEFVAR_BACK;
  #define GetFbVar(var,...) __GET_VAR(data__->var,__VA_ARGS__)
  #define SetFbVar(var,val,...) __SET_VAR(data__->,var,__VA_ARGS__,val)
extern void App_DOMode(DOMODE*);App_DOMode(data__);
  #undef GetFbVar
  #undef SetFbVar
;

  goto __end;

__end:
  return;
} // DOMODE_body__() 





void DOVAL_init__(DOVAL *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->EX,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->DON,0,retain)
  __INIT_VAR(data__->V,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->OV,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->OK,0,retain)
}

// Code part
void DOVAL_body__(DOVAL *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }
  // Initialise TEMP variables

  __IL_DEFVAR_T __IL_DEFVAR;
  __IL_DEFVAR_T __IL_DEFVAR_BACK;
  #define GetFbVar(var,...) __GET_VAR(data__->var,__VA_ARGS__)
  #define SetFbVar(var,val,...) __SET_VAR(data__->,var,__VA_ARGS__,val)
extern void App_DOVal(DOVAL*);App_DOVal(data__);
  #undef GetFbVar
  #undef SetFbVar
;

  goto __end;

__end:
  return;
} // DOVAL_body__() 





void DOFAST_init__(DOFAST *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->EX,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->DON,0,retain)
  __INIT_VAR(data__->V,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->OV,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->OK,0,retain)
}

// Code part
void DOFAST_body__(DOFAST *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }
  // Initialise TEMP variables

  __IL_DEFVAR_T __IL_DEFVAR;
  __IL_DEFVAR_T __IL_DEFVAR_BACK;
  #define GetFbVar(var,...) __GET_VAR(data__->var,__VA_ARGS__)
  #define SetFbVar(var,val,...) __SET_VAR(data__->,var,__VA_ARGS__,val)
extern void App_DOFast(DOFAST*);App_DOFast(data__);
  #undef GetFbVar
  #undef SetFbVar
;

  goto __end;

__end:
  return;
} // DOFAST_body__() 





void AIMODE_init__(AIMODE *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->EX,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->AIN,0,retain)
  __INIT_VAR(data__->M,0,retain)
  __INIT_VAR(data__->OM,0,retain)
  __INIT_VAR(data__->OS,0,retain)
  __INIT_VAR(data__->OK,0,retain)
}

// Code part
void AIMODE_body__(AIMODE *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }
  // Initialise TEMP variables

  __IL_DEFVAR_T __IL_DEFVAR;
  __IL_DEFVAR_T __IL_DEFVAR_BACK;
  #define GetFbVar(var,...) __GET_VAR(data__->var,__VA_ARGS__)
  #define SetFbVar(var,val,...) __SET_VAR(data__->,var,__VA_ARGS__,val)
extern void App_AIMode(AIMODE*);App_AIMode(data__);
  #undef GetFbVar
  #undef SetFbVar
;

  goto __end;

__end:
  return;
} // AIMODE_body__() 





void AIVAL_init__(AIVAL *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->EX,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->AIN,0,retain)
  __INIT_VAR(data__->OV,0.0,retain)
  __INIT_VAR(data__->OS,0,retain)
  __INIT_VAR(data__->OK,0,retain)
}

// Code part
void AIVAL_body__(AIVAL *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }
  // Initialise TEMP variables

  __IL_DEFVAR_T __IL_DEFVAR;
  __IL_DEFVAR_T __IL_DEFVAR_BACK;
  #define GetFbVar(var,...) __GET_VAR(data__->var,__VA_ARGS__)
  #define SetFbVar(var,val,...) __SET_VAR(data__->,var,__VA_ARGS__,val)
extern void App_AIVal(AIVAL*);App_AIVal(data__);
  #undef GetFbVar
  #undef SetFbVar
;

  goto __end;

__end:
  return;
} // AIVAL_body__() 





void AOFAST_init__(AOFAST *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->EX,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->AON,0,retain)
  __INIT_VAR(data__->V,0.0,retain)
  __INIT_VAR(data__->OV,0.0,retain)
  __INIT_VAR(data__->OK,0,retain)
}

// Code part
void AOFAST_body__(AOFAST *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }
  // Initialise TEMP variables

  __IL_DEFVAR_T __IL_DEFVAR;
  __IL_DEFVAR_T __IL_DEFVAR_BACK;
  #define GetFbVar(var,...) __GET_VAR(data__->var,__VA_ARGS__)
  #define SetFbVar(var,val,...) __SET_VAR(data__->,var,__VA_ARGS__,val)
extern void App_AOFast(AOFAST*);App_AOFast(data__);
  #undef GetFbVar
  #undef SetFbVar
;

  goto __end;

__end:
  return;
} // AOFAST_body__() 





void AOMODE_init__(AOMODE *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->EX,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->AON,0,retain)
  __INIT_VAR(data__->M,0,retain)
  __INIT_VAR(data__->OM,0,retain)
  __INIT_VAR(data__->OK,0,retain)
}

// Code part
void AOMODE_body__(AOMODE *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }
  // Initialise TEMP variables

  __IL_DEFVAR_T __IL_DEFVAR;
  __IL_DEFVAR_T __IL_DEFVAR_BACK;
  #define GetFbVar(var,...) __GET_VAR(data__->var,__VA_ARGS__)
  #define SetFbVar(var,val,...) __SET_VAR(data__->,var,__VA_ARGS__,val)
extern void App_AOMode(AOMODE*);App_AOMode(data__);
  #undef GetFbVar
  #undef SetFbVar
;

  goto __end;

__end:
  return;
} // AOMODE_body__() 





void AOVAL_init__(AOVAL *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->EX,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->AON,0,retain)
  __INIT_VAR(data__->V,0.0,retain)
  __INIT_VAR(data__->OV,0.0,retain)
  __INIT_VAR(data__->OK,0,retain)
}

// Code part
void AOVAL_body__(AOVAL *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }
  // Initialise TEMP variables

  __IL_DEFVAR_T __IL_DEFVAR;
  __IL_DEFVAR_T __IL_DEFVAR_BACK;
  #define GetFbVar(var,...) __GET_VAR(data__->var,__VA_ARGS__)
  #define SetFbVar(var,val,...) __SET_VAR(data__->,var,__VA_ARGS__,val)
extern void App_AOVal(AOVAL*);App_AOVal(data__);
  #undef GetFbVar
  #undef SetFbVar
;

  goto __end;

__end:
  return;
} // AOVAL_body__() 





void AOSAFE_init__(AOSAFE *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->EX,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->ENX,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->AON,0,retain)
  __INIT_VAR(data__->V,0.0,retain)
  __INIT_VAR(data__->OV,0.0,retain)
  __INIT_VAR(data__->OW,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->OK,0,retain)
}

// Code part
void AOSAFE_body__(AOSAFE *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }
  // Initialise TEMP variables

  __IL_DEFVAR_T __IL_DEFVAR;
  __IL_DEFVAR_T __IL_DEFVAR_BACK;
  #define GetFbVar(var,...) __GET_VAR(data__->var,__VA_ARGS__)
  #define SetFbVar(var,val,...) __SET_VAR(data__->,var,__VA_ARGS__,val)
extern void App_AOSafe(AOSAFE*);App_AOSafe(data__);
  #undef GetFbVar
  #undef SetFbVar
;

  goto __end;

__end:
  return;
} // AOSAFE_body__() 





void MAIN_init__(MAIN *data__, BOOL retain) {
  __INIT_EXTERNAL(BOOL,LT_LOW,data__->LT_LOW,retain)
  __INIT_VAR(data__->LT_LOW_F,__BOOL_LITERAL(FALSE),retain)
  __INIT_EXTERNAL(BOOL,LT_MIDDLE,data__->LT_MIDDLE,retain)
  __INIT_VAR(data__->LT_MIDDLE_F,__BOOL_LITERAL(FALSE),retain)
  __INIT_EXTERNAL(BOOL,LT_HIGHT,data__->LT_HIGHT,retain)
  __INIT_VAR(data__->LT_HIGHT_F,__BOOL_LITERAL(FALSE),retain)
  __INIT_EXTERNAL(BOOL,HS_AUTO,data__->HS_AUTO,retain)
  __INIT_VAR(data__->HS_AUTO_F,__BOOL_LITERAL(FALSE),retain)
  __INIT_EXTERNAL(BOOL,P_SPEED_50,data__->P_SPEED_50,retain)
  __INIT_VAR(data__->P_SPEED_50L,__BOOL_LITERAL(FALSE),retain)
  __INIT_EXTERNAL(BOOL,P_SPEED_100,data__->P_SPEED_100,retain)
  __INIT_VAR(data__->P_SPEED_100L,__BOOL_LITERAL(FALSE),retain)
  __INIT_EXTERNAL(BOOL,P_START,data__->P_START,retain)
  __INIT_VAR(data__->P_STARTL,__BOOL_LITERAL(FALSE),retain)
  __INIT_EXTERNAL(BOOL,LT_ERROR,data__->LT_ERROR,retain)
  __INIT_VAR(data__->LT_ERRORL,__BOOL_LITERAL(FALSE),retain)
  __INIT_EXTERNAL(BOOL,LT_SET,data__->LT_SET,retain)
  __INIT_EXTERNAL(WORD,PLC_STATE,data__->PLC_STATE,retain)
  TON_init__(&data__->TON0,retain);
  __INIT_VAR(data__->TM_5S,__time_to_timespec(1, 0, 5, 0, 0, 0),retain)
  TON_init__(&data__->TON1,retain);
  TON_init__(&data__->TON2,retain);
  TON_init__(&data__->TON3,retain);
  __INIT_VAR(data__->NOT95_OUT,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->OR68_OUT,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->OR58_OUT,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->OR80_OUT,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->WORD_TO_INT93_OUT,0,retain)
  __INIT_VAR(data__->INC91_OUT,0,retain)
  __INIT_VAR(data__->INT_TO_WORD94_OUT,0,retain)
}

// Code part
void MAIN_body__(MAIN *data__) {
  // Initialise TEMP variables

  __SET_VAR(data__->TON0.,IN,,__GET_EXTERNAL(data__->HS_AUTO,));
  __SET_VAR(data__->TON0.,PT,,__GET_VAR(data__->TM_5S,));
  TON_body__(&data__->TON0);
  __SET_VAR(data__->,HS_AUTO_F,,__GET_VAR(data__->TON0.Q,));
  __SET_VAR(data__->TON1.,IN,,__GET_EXTERNAL(data__->LT_LOW,));
  __SET_VAR(data__->TON1.,PT,,__GET_VAR(data__->TM_5S,));
  TON_body__(&data__->TON1);
  __SET_VAR(data__->,LT_LOW_F,,__GET_VAR(data__->TON1.Q,));
  __SET_VAR(data__->TON2.,IN,,__GET_EXTERNAL(data__->LT_MIDDLE,));
  __SET_VAR(data__->TON2.,PT,,__GET_VAR(data__->TM_5S,));
  TON_body__(&data__->TON2);
  __SET_VAR(data__->,LT_MIDDLE_F,,__GET_VAR(data__->TON2.Q,));
  __SET_VAR(data__->TON3.,IN,,__GET_EXTERNAL(data__->LT_HIGHT,));
  __SET_VAR(data__->TON3.,PT,,__GET_VAR(data__->TM_5S,));
  TON_body__(&data__->TON3);
  __SET_VAR(data__->,LT_HIGHT_F,,__GET_VAR(data__->TON3.Q,));
  __SET_VAR(data__->,LT_ERRORL,,((__GET_VAR(data__->LT_HIGHT_F,) && ((!(__GET_VAR(data__->LT_MIDDLE_F,)) && __GET_VAR(data__->LT_LOW_F,)) || ((__GET_VAR(data__->LT_MIDDLE_F,) || !(__GET_VAR(data__->LT_MIDDLE_F,))) && !(__GET_VAR(data__->LT_LOW_F,))))) || ((!(__GET_VAR(data__->LT_HIGHT_F,)) && __GET_VAR(data__->LT_MIDDLE_F,)) && !(__GET_VAR(data__->LT_LOW_F,)))));
  if (__GET_VAR(data__->LT_ERRORL,)) {
    __SET_EXTERNAL(data__->,LT_ERROR,,__BOOL_LITERAL(TRUE));
  };
  __SET_VAR(data__->,NOT95_OUT,,!(__GET_VAR(data__->LT_ERRORL,)));
  if ((!(__GET_VAR(data__->HS_AUTO_F,)) && __GET_VAR(data__->NOT95_OUT,))) {
    __SET_EXTERNAL(data__->,LT_ERROR,,__BOOL_LITERAL(FALSE));
  };
  if (!(__GET_VAR(data__->LT_LOW_F,))) {
    __SET_VAR(data__->,P_SPEED_50L,,__BOOL_LITERAL(FALSE));
  };
  if (!(__GET_VAR(data__->LT_LOW_F,))) {
    __SET_VAR(data__->,P_SPEED_100L,,__BOOL_LITERAL(TRUE));
  };
  __SET_VAR(data__->,OR68_OUT,,OR__BOOL__BOOL(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (UINT)2,
    (BOOL)(__GET_EXTERNAL(data__->P_START,) && __GET_VAR(data__->LT_MIDDLE_F,)),
    (BOOL)((__GET_EXTERNAL(data__->LT_SET,) && !(__GET_EXTERNAL(data__->P_START,))) && !(__GET_VAR(data__->LT_MIDDLE_F,)))));
  if (__GET_VAR(data__->OR68_OUT,)) {
    __SET_VAR(data__->,P_SPEED_50L,,__BOOL_LITERAL(TRUE));
  };
  if (__GET_VAR(data__->OR68_OUT,)) {
    __SET_VAR(data__->,P_SPEED_100L,,__BOOL_LITERAL(FALSE));
  };
  __SET_VAR(data__->,OR58_OUT,,OR__BOOL__BOOL(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (UINT)3,
    (BOOL)__GET_VAR(data__->LT_HIGHT_F,),
    (BOOL)!(__GET_VAR(data__->HS_AUTO_F,)),
    (BOOL)__GET_EXTERNAL(data__->LT_ERROR,)));
  if (__GET_VAR(data__->OR58_OUT,)) {
    __SET_VAR(data__->,P_SPEED_50L,,__BOOL_LITERAL(FALSE));
  };
  if (__GET_VAR(data__->OR58_OUT,)) {
    __SET_VAR(data__->,P_SPEED_100L,,__BOOL_LITERAL(FALSE));
  };
  if (((((__GET_EXTERNAL(data__->LT_SET,) && !(__GET_VAR(data__->LT_MIDDLE_F,))) || !(__GET_VAR(data__->LT_LOW_F,))) && !(__GET_EXTERNAL(data__->LT_ERROR,))) && __GET_VAR(data__->HS_AUTO_F,))) {
    __SET_VAR(data__->,P_STARTL,,__BOOL_LITERAL(TRUE));
  };
  __SET_VAR(data__->,OR80_OUT,,OR__BOOL__BOOL(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (UINT)3,
    (BOOL)__GET_VAR(data__->LT_HIGHT_F,),
    (BOOL)!(__GET_VAR(data__->HS_AUTO_F,)),
    (BOOL)__GET_EXTERNAL(data__->LT_ERROR,)));
  if (__GET_VAR(data__->OR80_OUT,)) {
    __SET_VAR(data__->,P_STARTL,,__BOOL_LITERAL(FALSE));
  };
  __SET_EXTERNAL(data__->,P_SPEED_100,,__GET_VAR(data__->P_SPEED_100L,));
  __SET_EXTERNAL(data__->,P_SPEED_50,,__GET_VAR(data__->P_SPEED_50L,));
  __SET_EXTERNAL(data__->,P_START,,__GET_VAR(data__->P_STARTL,));
  __SET_VAR(data__->,WORD_TO_INT93_OUT,,WORD_TO_INT(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (WORD)__GET_EXTERNAL(data__->PLC_STATE,)));
  __SET_VAR(data__->,INC91_OUT,,INC(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (BOOL)__BOOL_LITERAL(TRUE),
    (INT)__GET_VAR(data__->WORD_TO_INT93_OUT,)));
  __SET_VAR(data__->,INT_TO_WORD94_OUT,,INT_TO_WORD(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (INT)__GET_VAR(data__->INC91_OUT,)));
  __SET_EXTERNAL(data__->,PLC_STATE,,__GET_VAR(data__->INT_TO_WORD94_OUT,));

  goto __end;

__end:
  return;
} // MAIN_body__() 





