# page-fault-library

A C library for estimating page-faults of a program. 

Call init() to set up the recording mechanism, begin_recording() to begin counting page faults, and stop_recording() to return
the number of page-faults expereinced in the interval. 

Of course, this can only approximate page-faults, since the recording code itself may cause faults. 

Inspired by discussion in CSCI 5103 Operating Systems. 
