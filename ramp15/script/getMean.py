import sys

file_name1 = sys.argv[1]

#file_name2 = sys.argv[2]

write_file_name=sys.argv[2]

print "file_name1", file_name1
#print "file_name2", file_name2
print "write_file_name", write_file_name


res_file = open(file_name1, "r")
lines = res_file.readlines()

avg_dr=0.0
avg_delay=0.0
count=0
for line in lines:
	tokens = line.split()
	avg_dr=avg_dr+(float(tokens[0])+float(tokens[1])+float(tokens[2]))
	avg_delay=avg_delay+(float(tokens[3])+float(tokens[4])+float(tokens[5]))
	count = count+1
avg_dr=avg_dr/float(count*3)
avg_delay=avg_delay/float(count*3)

res_file.close()

print "avg_dr: ", avg_dr
print "avg_delay: ", avg_delay

#res_file = open(file_name2, "r")
#lines = res_file.readlines()

#nodes=0
#count=0
#avg_nodes=0.0
#for line in lines:
#	tokens = line.split()
#	nodes=nodes+int(tokens[1])
#	count = count+1
#avg_nodes=float(nodes)/float(count)

#res_file.close()

#print "avg_nodes: ", avg_nodes

write_file = open(write_file_name, "a")
write_file.write(str(avg_dr))
write_file.write('\t')
write_file.write(str(avg_delay))
#write_file.write('\t')
#write_file.write(str(avg_nodes))
write_file.write('\n')

