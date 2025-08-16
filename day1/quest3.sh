sh ai_initial_module.sh
sh ai_door_management_module.sh
mv door_managenent_fi door_management_files
sh ai_door_management_module.sh
cd door_management_files
mkdir door_configuration
mkdir door_logs
mkdir door_map
cd ..
mv door_1.log door_logs/      //all .log
mv door_1.conf door_configuration/        //all .conf
mv door_map_1.1 door_map
sh ai_door_management_module.sh
