import os
import json
import subprocess
from occam import Occam

# Get information about object
object = Occam.load()

# Gather paths
scripts_path    = os.path.dirname(__file__)
job_path        = os.getcwd()
object_path = "/occam/%s-%s" % (object.id(), object.revision())

dependencies = object.dependencies()
matlab = dependencies[0]
matlab_dir = "/occam/%s-%s"%(matlab.get("id"),matlab.get("revision"))

matlab_app = os.path.join(matlab_dir,"MATLAB","R2014b","bin");

simulation_path = os.path.join(object_path, "ramp15")
simulation_config_path = os.path.join(object_path, "ramp15", "Experiment-Parameters.json")

# Default program (Default wcps output file)
input_file =  "noErrornoDelay.txt"
# Get selected input file from OCCAM
inputs = object.inputs("WCPS Static Output")

if len(inputs) > 0:
   if(inputs[0]._object.get("created")):
       volume_dir_path = inputs[0].volume()
       if os.path.exists(os.path.join(volume_dir_path, 'object.json')):
           with open(os.path.join(volume_dir_path, 'object.json')) as json_file:
               gen_object=json.load(json_file)
               files = gen_object.get("files")
               if len(files) > 0:
                   input_file=os.path.join(volume_dir_path,files[0])
   else:
       files = inputs[0].files()
       if len(files) > 0:
           input_file = files[0]

#Defining OCCAM expected output file and its path
output_file = object.output_path(type="application/jpeg", output_directory='new_output', output_file="f1.jpeg")
output_generated_file = object.output_generated_path(type="application/jpeg", output_directory='new_output', output_file="f1.jpeg")

print("output_path: %s"%(output_file))

#Loading OCCAM parameters into a configuration file that will be read by the matlab simulation script
sim_config = object.configuration("Simulation configuration")
sim_config_file = object.configuration_file("Simulation configuration")


#Defining Matlab actvation ini file
with open(os.path.join(matlab_app, "matlab2014Activate.ini"),"w") as of:
    of.write("isSilent=true\n")
    of.write("licenseFile=%s/%s\n" %(object_path,"license.lic"))
    of.write("activateCommand=activateOffline\n")
    of.write("activationKey=\n")
    of.write("installLicenseFileDir=\n")
    of.write("installLicenseFileName=\n")

# Setup run command /tmp/aws_root.log
run_sim_command = [
    "cp -f %s %s; "%(sim_config_file, simulation_config_path),
    "cd  %s;  "%("/occam"),
    "ls    ;  ",
    "cd  %s;  "%(matlab_app),
    "cat %s;  "%("matlab2014Activate.ini"),
    "sh  %s;  "%("activate_matlab.sh -propertiesFile matlab2014Activate.ini"),
    "cp -r /root/.matlab /local/.; ",
    "cp -f %s %s; "%(input_file,simulation_path),
    "cd  %s;  "%(os.path.join(simulation_path)),
    "echo  %s input file is %s;"%("About to run matlab script",input_file),
    "%s -nodisplay -nosplash -r 'try, filename=%s run hxpumpcode.m; catch e, disp(getReport(e)); end, quit force' | tee matlab_output.log;"%(os.path.join(matlab_app,"matlab"),input_file),
    "cat  matlab_output.log;",
    "date;  ",
    "stat f1.jpeg;  ",
    "echo  %s;"%("After matlab script"),
    "echo output path is %s;"%(output_file),
    "cp -f %s %s;"%("f1.jpeg", output_file),
    "cp -f %s %s;"%("f1.jpeg", output_generated_file)
]

command= ' '.join(run_sim_command)

# Pass run command to OCCAM
subprocess.Popen(command, shell=True)
