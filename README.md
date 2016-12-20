# paho_library
Paho_library to publish, subscribe and do both in same client with MQTT

created by @KarthikeyanPrakash (karthikeyanprakash@outlook.com)

=======================================================================

Source directory 	
- \<paho_library>/src/..

build directory	
- \<paho_library>/build/..

=======================================================================
## To build sample programs

**Donwload paho.mqtt.c source library in you system**

- To Donwload go to [Github location for paho c library] (https://github.com/eclipse/paho.mqtt.c)
- Enter the library path in main.scons file at \<paho_library>/build/main.scons
- Go to \<paho_library_root>/directory and run scons
- Built examples can be found in \<paho_library>/build/

=======================================================================
## Run Sample Programs

- All the program connectes to test.mosquitto.org by default
- Publish and Subscribe topic will be displayed while running program (mostly paho_pub, paho_sub)
- For paho_pub the publish message should be entered in test2.txt file in build directory

=======================================================================
###### Known Issues:
1. pub_sub program
  * Publish - Subscribe synchronization	
2. paho_pub
  * Program sometime shows segmentation fault(core dumped) 

=======================================================================	
