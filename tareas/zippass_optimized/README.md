# Reporte de Optimizaciones zippass_serial

## Descripcion de la optimizacion realizada

### Caso 000

### Caso 004
Serial sin optimizar:

         10 630,56 msec task-clock                       #    1,000 CPUs utilized             
                31      context-switches                 #    2,916 /sec                      
                 2      cpu-migrations                   #    0,188 /sec                      
               327      page-faults                      #   30,760 /sec                      
    29 806 729 584      cycles                           #    2,804 GHz                       
    91 097 204 108      instructions                     #    3,06  insn per cycle            
    12 590 391 902      branches                         #    1,184 G/sec                     
         2 126 901      branch-misses                    #    0,02% of all branches           

      10,631835528 seconds time elapsed

      10,447105000 seconds user
       0,183984000 seconds sys


Serial optimizado:

         10 092,35 msec task-clock                       #    1,000 CPUs utilized             
                36      context-switches                 #    3,567 /sec                      
                 1      cpu-migrations                   #    0,099 /sec                      
               327      page-faults                      #   32,401 /sec                      
    29 255 267 434      cycles                           #    2,899 GHz                       
    91 127 980 668      instructions                     #    3,11  insn per cycle            
    12 596 471 207      branches                         #    1,248 G/sec                     
         1 865 833      branch-misses                    #    0,01% of all branches           

      10,093436923 seconds time elapsed

       9,916856000 seconds user
       0,176015000 seconds sys

### Caso 006

Serial sin optimizar:

Serial optimizado:

        479 765,19 msec task-clock                       #    1,000 CPUs utilized             
             2 699      context-switches                 #    5,626 /sec                      
                43      cpu-migrations                   #    0,090 /sec                      
               325      page-faults                      #    0,677 /sec                      
 1 398 157 504 892      cycles                           #    2,914 GHz                       
 4 350 567 991 116      instructions                     #    3,11  insn per cycle            
   601 344 177 311      branches                         #    1,253 G/sec                     
        89 120 780      branch-misses                    #    0,01% of all branches           

     479,807441345 seconds time elapsed

     472,110615000 seconds user
       7,639330000 seconds sys