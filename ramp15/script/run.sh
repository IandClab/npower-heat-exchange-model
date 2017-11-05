#!/bin/bash

#LP_SEED='1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20'
LP_SEED='1'
#DR='5 6 7 8 9'
DR='5'
DELAY='0'
BASE_DIR='/Users/wangwenchen/github/z_proposal_realTime/'
CONTROL_SCHEME=$1
CURR_DIR=$BASE_DIR"simulation/"$CONTROL_SCHEME
DATA_FILE_PATH=$BASE_DIR"fault_injection/test_cases/"
RES_FILE_PATH=$BASE_DIR"simulation/result/"$CONTROL_SCHEME"/"
mkdir $RES_FILE_PATH

cd $CURR_DIR

for dr in $DR
do
{
	for delay in $DELAY
	do
	{
		data_directory=$DATA_FILE_PATH"noncl_randomFI"$dr"_delay"$delay"/"
		echo $data_directory
		res_name=$RES_FILE_PATH"rms_DR"$dr"_Delay"$delay
		echo res_name
		for lp_seed in $LP_SEED
		do
		{			
			# create a simu.cfg file
			./script/simu_setup.sh $data_directory$lp_seed

			cat simu.cfg

			matlab -nodesktop -nosplash -r "HeatExchanger_ps; data1=TotalHeatTransfer.Data; load('noErrornoDelay.mat'); data_nodelay=TotalHeatTransfer.Data; data_abs= abs(data1-data_nodelay); rms= (sum((data1-data_nodelay).^2)/3001)^0.5; fileID = fopen('$res_name','a'); fprintf(fileID,'%f\t%f\t%f\n',rms, sum(data_abs),max(data_abs));fclose(fileID); quit;"
		}
		done
	}
	done
}
done

	



