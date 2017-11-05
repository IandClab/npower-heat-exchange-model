#!/usr/bin/python

import sys
import statistics
from array import array

filename_r=sys.argv[1]
filename_w=sys.argv[2]
scheme=sys.argv[3]
dr=sys.argv[4]
delay=sys.argv[5]

f_r=open(filename_r+"rms_control_result.txt", "r")

lines=f_r.readlines()
RMS_arr=[0.0]*20
IAE_arr=[0.0]*20
MAE_arr=[0.0]*20
RMS=0.0
IAE=0.0
MAE=0.0
count=0
for line in lines:
	tokens=line.split('\t')
	RMS+=float(tokens[0])
	IAE+=float(tokens[1])
	MAE+=float(tokens[2])
	RMS_arr[count]=float(tokens[0])
	IAE_arr[count]=float(tokens[1])
	MAE_arr[count]=float(tokens[2])
	count+=1
f_r.close()
RMS=RMS/count
IAE=IAE/count
MAE=MAE/count
print (RMS_arr)
print (IAE_arr)
print (MAE_arr)
RMS_stdv=statistics.stdev(RMS_arr)
IAE_stdv=statistics.stdev(IAE_arr)
MAE_stdv=statistics.stdev(MAE_arr)
print (RMS_stdv)
print (IAE_stdv)
print (MAE_stdv)
f_w=open(filename_w+"rms_control_result.txt", "a")
f_w.write(scheme)
f_w.write('\t')
f_w.write(str(RMS))
f_w.write('\t')
f_w.write(str(RMS_stdv))
f_w.write('\t')
f_w.write(str(IAE))
f_w.write('\t')
f_w.write(str(IAE_stdv))
f_w.write('\t')
f_w.write(str(MAE))
f_w.write('\t')
f_w.write(str(MAE_stdv))
f_w.write('\n')
f_w.close()





