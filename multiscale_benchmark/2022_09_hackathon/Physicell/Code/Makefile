VERSION := $(shell grep . VERSION.txt | cut -f1 -d:)
PROGRAM_NAME := project

CC := g++
# CC := g++-mp-7 # typical macports compiler name
# CC := g++-7 # typical homebrew compiler name 

# Check for environment definitions of compiler 
# e.g., on CC = g++-7 on OSX
ifdef PHYSICELL_CPP 
	CC := $(PHYSICELL_CPP)
endif

ARCH := native # best auto-tuning

# CFLAGS := -march=$(ARCH) -Ofast -s -fomit-frame-pointer -mfpmath=both -fopenmp -m64 -std=c++11
CFLAGS := -march=$(ARCH) -O3 -fomit-frame-pointer -mfpmath=both -fopenmp -m64 -std=c++11

ifeq ($(OS),Windows_NT)
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Darwin)
		UNAME_P := $(shell uname -p)
		var := $(shell which $(CC) | xargs file)
		ifeq ($(lastword $(var)),arm64)
		  CFLAGS := -march=$(ARCH) -O3 -fomit-frame-pointer -fopenmp -m64 -std=c++11
		endif
	endif
endif

COMPILE_COMMAND := $(CC) $(CFLAGS) 

BioFVM_OBJECTS := BioFVM_vector.o BioFVM_mesh.o BioFVM_microenvironment.o BioFVM_solvers.o BioFVM_matlab.o \
BioFVM_utilities.o BioFVM_basic_agent.o BioFVM_MultiCellDS.o BioFVM_agent_container.o 

PhysiCell_core_OBJECTS := PhysiCell_phenotype.o PhysiCell_cell_container.o PhysiCell_standard_models.o \
PhysiCell_cell.o PhysiCell_custom.o PhysiCell_utilities.o PhysiCell_constants.o PhysiCell_basic_signaling.o \
PhysiCell_signal_behavior.o 

PhysiCell_module_OBJECTS := PhysiCell_SVG.o PhysiCell_pathology.o PhysiCell_MultiCellDS.o PhysiCell_various_outputs.o \
PhysiCell_pugixml.o PhysiCell_settings.o PhysiCell_geometry.o

# put your custom objects here (they should be in the custom_modules directory)

PhysiCell_custom_module_OBJECTS := .o

pugixml_OBJECTS := pugixml.o

PhysiCell_OBJECTS := $(BioFVM_OBJECTS)  $(pugixml_OBJECTS) $(PhysiCell_core_OBJECTS) $(PhysiCell_module_OBJECTS)
ALL_OBJECTS := $(PhysiCell_OBJECTS) $(PhysiCell_custom_module_OBJECTS)


name:
	@echo ""
	@echo "Executable name is" $(PROGRAM_NAME)
	@echo ""

# sample projects 	
# change to the different 
list-projects:
	@echo "Sample projects: template"
	@echo ""
	@echo "Sample intracellular projects: ode-energy-sample physiboss-cell-lines-sample cancer-metabolism-sample"
	@echo ""
	
template:
	cp ./unit_tests/template/custom_modules/* ./custom_modules/
	touch main.cpp && cp main.cpp main-backup.cpp
	cp ./unit_tests/template/main.cpp ./main.cpp 
	cp Makefile Makefile-backup
	cp ./unit_tests/template/Makefile .
	cp ./config/PhysiCell_settings.xml ./config/PhysiCell_settings-backup.xml 
	cp ./unit_tests/template/config/* ./config/
	
# unit_tests
single_diffusion:
	cp ./unit_tests/single_diffusion/custom_modules/* ./custom_modules/
	touch main.cpp && cp main.cpp main-backup.cpp
	cp ./unit_tests/single_diffusion/main.cpp ./main.cpp 
	cp Makefile Makefile-backup
	cp ./unit_tests/single_diffusion/Makefile .
	cp ./config/PhysiCell_settings.xml ./config/PhysiCell_settings-backup.xml 
	cp ./unit_tests/single_diffusion/config/* ./config/

many_diffusion:
	cp ./unit_tests/many_diffusion/custom_modules/* ./custom_modules/
	touch main.cpp && cp main.cpp main-backup.cpp
	cp ./unit_tests/many_diffusion/main.cpp ./main.cpp 
	cp Makefile Makefile-backup
	cp ./unit_tests/many_diffusion/Makefile .
	cp ./config/PhysiCell_settings.xml ./config/PhysiCell_settings-backup.xml 
	cp ./unit_tests/many_diffusion/config/* ./config/
mechanics_movement:
	cp ./unit_tests/mechanics_movement/custom_modules/* ./custom_modules/
	touch main.cpp && cp main.cpp main-backup.cpp
	cp ./unit_tests/mechanics_movement/main.cpp ./main.cpp 
	cp Makefile Makefile-backup
	cp ./unit_tests/mechanics_movement/Makefile .
	cp ./config/PhysiCell_settings.xml ./config/PhysiCell_settings-backup.xml 
	cp ./unit_tests/mechanics_movement/config/* ./config/
mechanics_pushing:
	cp ./unit_tests/mechanics_pushing/custom_modules/* ./custom_modules/
	touch main.cpp && cp main.cpp main-backup.cpp
	cp ./unit_tests/mechanics_pushing/main.cpp ./main.cpp 
	cp Makefile Makefile-backup
	cp ./unit_tests/mechanics_pushing/Makefile .
	cp ./config/PhysiCell_settings.xml ./config/PhysiCell_settings-backup.xml 
	cp ./unit_tests/mechanics_pushing/config/* ./config/
fixed_cell_cycle:
	cp ./unit_tests/fixed_cell_cycle/custom_modules/* ./custom_modules/
	touch main.cpp && cp main.cpp main-backup.cpp
	cp ./unit_tests/fixed_cell_cycle/main.cpp ./main.cpp 
	cp Makefile Makefile-backup
	cp ./unit_tests/fixed_cell_cycle/Makefile .
	cp ./config/PhysiCell_settings.xml ./config/PhysiCell_settings-backup.xml 
	cp ./unit_tests/fixed_cell_cycle/config/* ./config/
stochastic_cell_cylcle:
	cp ./unit_tests/stochastic_cell_cylcle/custom_modules/* ./custom_modules/
	touch main.cpp && cp main.cpp main-backup.cpp
	cp ./unit_tests/stochastic_cell_cylcle/main.cpp ./main.cpp 
	cp Makefile Makefile-backup
	cp ./unit_tests/stochastic_cell_cylcle/Makefile .
	cp ./config/PhysiCell_settings.xml ./config/PhysiCell_settings-backup.xml 
	cp ./unit_tests/stochastic_cell_cylcle/config/* ./config/

# stochastic_cell_cylcle
# use cases
monolayer:
	cp ./use_cases/monolayer/custom_modules/* ./custom_modules/
	touch main.cpp && cp main.cpp main-backup.cpp
	cp ./use_cases/monolayer/main.cpp ./main.cpp 
	cp Makefile Makefile-backup
	cp ./use_cases/monolayer/Makefile .
	cp ./config/PhysiCell_settings.xml ./config/PhysiCell_settings-backup.xml 
	cp ./use_cases/monolayer/config/* ./config/
sphereoid_no_diff:
	cp ./use_cases/sphereoid_no_diff/custom_modules/* ./custom_modules/
	touch main.cpp && cp main.cpp main-backup.cpp
	cp ./use_cases/sphereoid_no_diff/main.cpp ./main.cpp 
	cp Makefile Makefile-backup
	cp ./use_cases/sphereoid_no_diff/Makefile .
	cp ./config/PhysiCell_settings.xml ./config/PhysiCell_settings-backup.xml 
	cp ./use_cases/sphereoid_no_diff/config/* ./config/	
# PhysiCell core components	

PhysiCell_phenotype.o: ./core/PhysiCell_phenotype.cpp
	$(COMPILE_COMMAND) -c ./core/PhysiCell_phenotype.cpp
	
PhysiCell_digital_cell_line.o: ./core/PhysiCell_digital_cell_line.cpp
	$(COMPILE_COMMAND) -c ./core/PhysiCell_digital_cell_line.cpp

PhysiCell_cell.o: ./core/PhysiCell_cell.cpp
	$(COMPILE_COMMAND) -c ./core/PhysiCell_cell.cpp 

PhysiCell_cell_container.o: ./core/PhysiCell_cell_container.cpp
	$(COMPILE_COMMAND) -c ./core/PhysiCell_cell_container.cpp 
	
PhysiCell_standard_models.o: ./core/PhysiCell_standard_models.cpp
	$(COMPILE_COMMAND) -c ./core/PhysiCell_standard_models.cpp 
	
PhysiCell_utilities.o: ./core/PhysiCell_utilities.cpp
	$(COMPILE_COMMAND) -c ./core/PhysiCell_utilities.cpp 
	
PhysiCell_custom.o: ./core/PhysiCell_custom.cpp
	$(COMPILE_COMMAND) -c ./core/PhysiCell_custom.cpp 
	
PhysiCell_constants.o: ./core/PhysiCell_constants.cpp
	$(COMPILE_COMMAND) -c ./core/PhysiCell_constants.cpp 
	
PhysiCell_signal_behavior.o: ./core/PhysiCell_signal_behavior.cpp
	$(COMPILE_COMMAND) -c ./core/PhysiCell_signal_behavior.cpp 

# BioFVM core components (needed by PhysiCell)
	
BioFVM_vector.o: ./BioFVM/BioFVM_vector.cpp
	$(COMPILE_COMMAND) -c ./BioFVM/BioFVM_vector.cpp 

BioFVM_agent_container.o: ./BioFVM/BioFVM_agent_container.cpp
	$(COMPILE_COMMAND) -c ./BioFVM/BioFVM_agent_container.cpp 
	
BioFVM_mesh.o: ./BioFVM/BioFVM_mesh.cpp
	$(COMPILE_COMMAND) -c ./BioFVM/BioFVM_mesh.cpp 

BioFVM_microenvironment.o: ./BioFVM/BioFVM_microenvironment.cpp
	$(COMPILE_COMMAND) -c ./BioFVM/BioFVM_microenvironment.cpp 

BioFVM_solvers.o: ./BioFVM/BioFVM_solvers.cpp
	$(COMPILE_COMMAND) -c ./BioFVM/BioFVM_solvers.cpp 

BioFVM_utilities.o: ./BioFVM/BioFVM_utilities.cpp
	$(COMPILE_COMMAND) -c ./BioFVM/BioFVM_utilities.cpp 
	
BioFVM_basic_agent.o: ./BioFVM/BioFVM_basic_agent.cpp
	$(COMPILE_COMMAND) -c ./BioFVM/BioFVM_basic_agent.cpp 
	
BioFVM_matlab.o: ./BioFVM/BioFVM_matlab.cpp
	$(COMPILE_COMMAND) -c ./BioFVM/BioFVM_matlab.cpp

BioFVM_MultiCellDS.o: ./BioFVM/BioFVM_MultiCellDS.cpp
	$(COMPILE_COMMAND) -c ./BioFVM/BioFVM_MultiCellDS.cpp
	
pugixml.o: ./BioFVM/pugixml.cpp
	$(COMPILE_COMMAND) -c ./BioFVM/pugixml.cpp
	
# standard PhysiCell modules

PhysiCell_SVG.o: ./modules/PhysiCell_SVG.cpp
	$(COMPILE_COMMAND) -c ./modules/PhysiCell_SVG.cpp

PhysiCell_pathology.o: ./modules/PhysiCell_pathology.cpp
	$(COMPILE_COMMAND) -c ./modules/PhysiCell_pathology.cpp

PhysiCell_MultiCellDS.o: ./modules/PhysiCell_MultiCellDS.cpp
	$(COMPILE_COMMAND) -c ./modules/PhysiCell_MultiCellDS.cpp

PhysiCell_various_outputs.o: ./modules/PhysiCell_various_outputs.cpp
	$(COMPILE_COMMAND) -c ./modules/PhysiCell_various_outputs.cpp
	
PhysiCell_pugixml.o: ./modules/PhysiCell_pugixml.cpp
	$(COMPILE_COMMAND) -c ./modules/PhysiCell_pugixml.cpp
	
PhysiCell_settings.o: ./modules/PhysiCell_settings.cpp
	$(COMPILE_COMMAND) -c ./modules/PhysiCell_settings.cpp	
	
PhysiCell_basic_signaling.o: ./core/PhysiCell_basic_signaling.cpp
	$(COMPILE_COMMAND) -c ./core/PhysiCell_basic_signaling.cpp 

PhysiCell_geometry.o: ./modules/PhysiCell_geometry.cpp
	$(COMPILE_COMMAND) -c ./modules/PhysiCell_geometry.cpp 

# user-defined PhysiCell modules

# cleanup

reset:
	rm -f *.cpp PhysiCell_cell.o
	cp ./unit_tests/Makefile-default Makefile 
	rm -f ./custom_modules/*
	touch ./custom_modules/empty.txt 
	touch ALL_CITATIONS.txt 
	touch ./core/PhysiCell_cell.cpp
	rm ALL_CITATIONS.txt 
	cp ./config/PhysiCell_settings-backup.xml ./config/PhysiCell_settings.xml 
	touch ./config/empty.csv
	rm ./config/*.csv	
	
clean:
	rm -f *.o
	rm -f $(PROGRAM_NAME)*
	
data-cleanup:
	rm -rf ./output
	mkdir ./output
	touch ./output/empty.txt

# archival 

checkpoint: 
	zip -r $$(date +%b_%d_%Y_%H%M).zip Makefile *.cpp *.h config/*.xml custom_modules/* 
	
zip:
	zip -r latest.zip Makefile* *.cpp *.h BioFVM/* config/* core/* custom_modules/* matlab/* modules/* sample_projects/* 
	cp latest.zip $$(date +%b_%d_%Y_%H%M).zip
	cp latest.zip VERSION_$(VERSION).zip 
	mv *.zip archives/
	
tar:
	tar --ignore-failed-read -czf latest.tar Makefile* *.cpp *.h BioFVM/* config/* core/* custom_modules/* matlab/* modules/* sample_projects/* 
	cp latest.tar $$(date +%b_%d_%Y_%H%M).tar
	cp latest.tar VERSION_$(VERSION).tar
	mv *.tar archives/

unzip: 
	cp ./archives/latest.zip . 
	unzip latest.zip 
	
untar: 
	cp ./archives/latest.tar .
	tar -xzf latest.tar

# easier animation 

FRAMERATE := 24
OUTPUT := output

jpeg: 
	@magick identify -format "%h" $(OUTPUT)/initial.svg > __H.txt 
	@magick identify -format "%w" $(OUTPUT)/initial.svg > __W.txt 
	@expr 2 \* \( $$(grep . __H.txt) / 2 \) > __H1.txt 
	@expr 2 \* \( $$(grep . __W.txt) / 2 \) > __W1.txt 
	@echo "$$(grep . __W1.txt)!x$$(grep . __H1.txt)!" > __resize.txt 
	@magick mogrify -format jpg -resize $$(grep . __resize.txt) $(OUTPUT)/s*.svg
	rm -f __H*.txt __W*.txt __resize.txt 
	
gif: 
	magick convert $(OUTPUT)/s*.svg $(OUTPUT)/out.gif 
	 
movie:
	ffmpeg -r $(FRAMERATE) -f image2 -i $(OUTPUT)/snapshot%08d.jpg -vcodec libx264 -pix_fmt yuv420p -strict -2 -tune animation -crf 15 -acodec none $(OUTPUT)/out.mp4
	
# upgrade rules 

SOURCE := PhysiCell_upgrade.zip 
get-upgrade: 
	@echo $$(curl https://raw.githubusercontent.com/MathCancer/PhysiCell/master/VERSION.txt) > VER.txt 
	@echo https://github.com/MathCancer/PhysiCell/releases/download/$$(grep . VER.txt)/PhysiCell_V.$$(grep . VER.txt).zip > DL_FILE.txt 
	rm -f VER.txt
	$$(curl -L $$(grep . DL_FILE.txt) --output PhysiCell_upgrade.zip)
	rm -f DL_FILE.txt 

PhysiCell_upgrade.zip: 
	make get-upgrade 

upgrade: $(SOURCE)
	unzip $(SOURCE) PhysiCell/VERSION.txt
	mv -f PhysiCell/VERSION.txt . 
	unzip $(SOURCE) PhysiCell/core/* 
	cp -r PhysiCell/core/* core 
	unzip $(SOURCE) PhysiCell/modules/* 
	cp -r PhysiCell/modules/* modules 
	unzip $(SOURCE) PhysiCell/sample_projects/* 
	cp -r PhysiCell/sample_projects/* sample_projects 
	unzip $(SOURCE) PhysiCell/BioFVM/* 
	cp -r PhysiCell/BioFVM/* BioFVM
	unzip $(SOURCE) PhysiCell/documentation/User_Guide.pdf
	mv -f PhysiCell/documentation/User_Guide.pdf documentation
	rm -f -r PhysiCell
	rm -f $(SOURCE) 
