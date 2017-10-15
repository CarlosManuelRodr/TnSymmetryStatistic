:Begin:
:Function:       mathlink_tn
:Pattern:        Tn[v_List, c_Real]
:Arguments:      { v, c }
:ArgumentTypes:  { Real64List, Real }
:ReturnType:     Real
:End:

:Begin:
:Function:       parallel_mathlink_tn
:Pattern:        ParallelTnExecute[v_List, sizes_List, c_Real]
:Arguments:      { v, sizes, c }
:ArgumentTypes:  { Real64List, Integer32List, Real }
:ReturnType:     Manual
:End: